// sema/pass9_5_codegen_bodies.cpp
//
// Pass 9.5: emit LLVM IR *bodies* for functions using:
//  - Pass6 slot bindings + ref bindings
//  - Pass7 literal side tables
//  - Pass8 dynamic tagging (Obj* vs Bool vs Void; StructObj tagging)
//  - Pass9.1 runtime intrinsics decls
//
// IMPORTANT: Error reporting in this file uses the project's LogSequence API
// (Log / LogPath / string). No ad-hoc stderr logging is performed here.

#include "pass9_5_codegen_bodies.hpp"

#include <cstdint>
#include <optional>
#include <type_traits>
#include <unordered_set>
#include <variant>
#include <vector>

#include <llvm/ADT/APInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/Casting.h>

// ---- Statements ----
#include "stmt/block_statement.hpp"
#include "stmt/break_statement.hpp"
#include "stmt/continue_statement.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_statement.hpp"
#include "stmt/while_statement.hpp"

// ---- Exprs ----
#include "expr/array_literal_expr.hpp"
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/bool_literal_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/char_literal_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/float_literal_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/int_literal_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/unary_op_expr.hpp"

// Struct literal fields
#include "expr/field_init_expr.hpp"

namespace sema
{
    // ============================================================
    // Logging (INZ_LOG_HPP contract)
    //
    // Every error cluster is emitted as:
    //
    //   1) module     : LogPath{SymKind::Ident, <module::path>, loc}
    //   2) message    : std::string
    //   3) cause      : optional identifier/path (log_ident / log_path)
    //
    // This matches the required UI structure:
    //   module
    //   message
    //   what caused error (identifier/path)
    // ============================================================

    namespace
    {
        struct Pass9_5LogCtx final
        {
            const std::vector<lex::SymId>* module_path = nullptr;
        };

        static thread_local Pass9_5LogCtx g_p95_logctx;

        static inline const std::vector<lex::SymId>& current_module_path()
        {
            static const std::vector<lex::SymId> empty;
            return g_p95_logctx.module_path ? *g_p95_logctx.module_path : empty;
        }

        // Best-effort extraction of a module path from ModuleBindings.
        // Primary expected shape (per your requirement):
        //   mb.mod->pathExpr_->path_
        static const std::vector<lex::SymId>* try_get_module_path(const ModuleBindings& mb, const Pass9_1Result& st)
        {
            return &st.unit_mods[mb.module_id.value]->pathExpr_->path_;
        }

        struct ScopedModuleLog final
        {
            const std::vector<lex::SymId>* prev = nullptr;

            explicit ScopedModuleLog(const std::vector<lex::SymId>* p)
                : prev(g_p95_logctx.module_path)
            {
                g_p95_logctx.module_path = p;
            }

            ~ScopedModuleLog() { g_p95_logctx.module_path = prev; }
        };

        static inline LogSequence& error_seq(Pass9_5Result& out) { return out.errors; }

        static inline void log_module_anchor(LogSequence& seq, const lex::Loc& loc)
        {
            // Required cluster head: module path at the error location.
            seq.emplace_back(LogPath{SymKind::Ident, current_module_path(), loc});
        }

        static void log_error(Pass9_5Result& out, const lex::Loc& loc, std::string msg)
        {
            LogSequence& seq = error_seq(out);
            log_module_anchor(seq, loc);
            log_msg(seq, std::move(msg));
        }

        static void log_error_ident(Pass9_5Result& out, const lex::Loc& loc, lex::SymId id,
                                    std::string msg)
        {
            LogSequence& seq = error_seq(out);
            log_module_anchor(seq, loc);
            log_msg(seq, std::move(msg));
            log_ident(seq, id, loc);
        }

        static void log_error_path(Pass9_5Result& out, const lex::Loc& loc,
                                   const std::vector<lex::SymId>& path, std::string msg)
        {
            LogSequence& seq = error_seq(out);
            log_module_anchor(seq, loc);
            log_msg(seq, std::move(msg));
            log_path(seq, path, loc, /*also_log_idents=*/true);
        }
    } // namespace

    // ============================================================
    // Tags (Pass8 DynTag -> Pass9.5 ABI ValueTag)
    // ============================================================

    static sema::DynTag dyn_tag_of(const Pass8Result& p8, const ast::Expr* e)
    {
        if (!e)
            return sema::DynTag::void_();

        const auto it = p8.tag_of.find(e);
        if (it == p8.tag_of.end())
            return sema::DynTag::obj(); // conservative fallback

        return it->second;
    }

    static ValueTag to_value_tag(const sema::DynTag& t)
    {
        switch (t.kind)
        {
        case sema::DynTagKind::Void:
            return ValueTag::Void;
        case sema::DynTagKind::Bool:
            return ValueTag::Bool;
        case sema::DynTagKind::Obj:
        case sema::DynTagKind::StructObj:
        default:
            return ValueTag::Obj;
        }
    }

    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        return llvm::ConstantPointerNull::get(
            llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
    }

    // ============================================================
    // IR emission context per function
    // ============================================================

    struct FnCG final
    {
        Pass9_1Result& st;
        const Pass5Result& p5;
        const Pass6Result& p6;
        const Pass7Result& p7;
        const Pass8Result& p8;

        struct LoopCtx
        {
            llvm::BasicBlock* breakBB = nullptr;
            llvm::BasicBlock* continueBB = nullptr;
            size_t scope_depth = 0; // cg.scope_slots.size() at loop entry (outside body)
        };

        std::vector<LoopCtx> loop_stack;

        const FnBindings* binds = nullptr;

        llvm::Function* F = nullptr;
        llvm::IRBuilder<> B;

        const Pass9_1RuntimeDecls* rt = nullptr;

        // Stack of scopes; each scope records which slots were introduced inside it.
        std::vector<std::vector<SlotId>> scope_slots;

        // slot allocas: slot.index -> alloca (Obj* storage)
        std::vector<llvm::AllocaInst*> slot_alloca;

        FnCG(Pass9_1Result& st_, const Pass5Result& p5_, const Pass6Result& p6_,
             const Pass7Result& p7_, const Pass8Result& p8_, llvm::Function* F_,
             const Pass9_1RuntimeDecls& rt_)
            : st(st_), p5(p5_), p6(p6_), p7(p7_), p8(p8_), F(F_), B(*st_.llctx),
              rt(&rt_)
        {
        }

        llvm::Value* box_if_needed(ValueTag tag, llvm::Value* v)
        {
            if (!v)
                return llvm::ConstantPointerNull::get(
                    llvm::cast<llvm::PointerType>(st.obj_ptr_ty));

            if (tag != ValueTag::Bool)
                return v; // already Obj*

            // Bool needs boxing if it is i1
            if (v->getType() == st.obj_ptr_ty)
                return v;

            if (v->getType() == st.i1_ty)
            {
                if (!rt || !rt->rt_box_bool)
                    return llvm::ConstantPointerNull::get(
                        llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
                return B.CreateCall(rt->rt_box_bool, {v}, "box.bool");
            }

            return llvm::ConstantPointerNull::get(
                llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
        }

        void arc_release_value_if_obj(llvm::Value* v)
        {
            if (!v)
                return;
            if (v->getType() != st.obj_ptr_ty)
                return;
            if (llvm::isa<llvm::ConstantPointerNull>(v))
                return;
            if (rt && rt->rt_release)
                B.CreateCall(rt->rt_release, {v});
        }

        void arc_store_slot(llvm::AllocaInst* slot, llvm::Value* newObj)
        {
            llvm::Value* oldObj = B.CreateLoad(st.obj_ptr_ty, slot, "arc.old");

            if (rt && rt->rt_retain && newObj &&
                !llvm::isa<llvm::ConstantPointerNull>(newObj))
                B.CreateCall(rt->rt_retain, {newObj});

            B.CreateStore(newObj, slot);

            if (rt && rt->rt_release && oldObj &&
                !llvm::isa<llvm::ConstantPointerNull>(oldObj))
                B.CreateCall(rt->rt_release, {oldObj});
        }

        void arc_release_slot_list(const std::vector<SlotId>& v)
        {
            for (auto it = v.rbegin(); it != v.rend(); ++it)
            {
                const SlotId s = *it;
                if (s.index >= slot_alloca.size() || !slot_alloca[s.index])
                    continue;

                llvm::AllocaInst* a = slot_alloca[s.index];
                llvm::Value* oldObj = B.CreateLoad(st.obj_ptr_ty, a);
                B.CreateStore(null_obj(st), a);

                if (rt && rt->rt_release)
                    B.CreateCall(rt->rt_release, {oldObj});
            }
        }

        void arc_release_current_scope()
        {
            if (scope_slots.empty())
                return;
            arc_release_slot_list(scope_slots.back());
        }

        llvm::Value* unbox_if_needed(ValueTag tag, llvm::Value* v)
        {
            if (!v)
                return llvm::ConstantInt::getFalse(*st.llctx);

            if (tag != ValueTag::Bool)
                return v;

            if (v->getType() == st.i1_ty)
                return v;

            if (v->getType() == st.obj_ptr_ty)
            {
                if (!rt || !rt->rt_unbox_bool)
                    return llvm::ConstantInt::getFalse(*st.llctx);
                return B.CreateCall(rt->rt_unbox_bool, {v}, "unbox.bool");
            }

            return llvm::ConstantInt::getFalse(*st.llctx);
        }

        llvm::Value* coerce_to(llvm::Type* dstTy, ValueTag srcTag, llvm::Value* v)
        {
            if (!v && srcTag == ValueTag::Void)
            {
                if (dstTy == st.obj_ptr_ty)
                    return null_obj(st);
                if (dstTy == st.i1_ty)
                    return llvm::ConstantInt::getFalse(*st.llctx);
                return nullptr;
            }

            if (dstTy == st.obj_ptr_ty)
                return box_if_needed(srcTag, v);

            if (dstTy == st.i1_ty)
                return unbox_if_needed(srcTag, v);

            // void destination: drop
            return nullptr;
        }
    };

    static void release_scopes_for_jump(FnCG& cg, size_t keep_depth)
    {
        // Release locals in scopes that will be exited by a jump.
        for (size_t i = cg.scope_slots.size(); i > keep_depth; --i)
            cg.arc_release_slot_list(cg.scope_slots[i - 1]);
    }

    // ============================================================
    // Forward decls
    // ============================================================

    static llvm::Value* emit_expr(FnCG& cg, ast::Expr* e, Pass9_5Result& out);
    static void emit_stmt(FnCG& cg, ast::Statement* s, Pass9_5Result& out);
    static llvm::Value* emit_place_slot_addr(FnCG& cg, ast::Expr* e,
                                             Pass9_5Result& out);
    static bool place_is_mutable(FnCG& cg, ast::Expr* e);

    // ============================================================
    // Helpers: runtime call with tolerant signature (bitcast callee)
    // ============================================================

    static llvm::CallInst* call_runtime_erased(FnCG& cg, llvm::Function* calleeFn,
                                               llvm::FunctionType* expectedFT,
                                               llvm::ArrayRef<llvm::Value*> args,
                                               llvm::StringRef dbgName)
    {
        if (!calleeFn)
            return nullptr;

        llvm::Value* callee = calleeFn;

        if (calleeFn->getFunctionType() != expectedFT)
        {
            callee = cg.B.CreateBitCast(calleeFn, expectedFT->getPointerTo(),
                                        (dbgName + ".cast").str());
        }

        if (expectedFT->getReturnType()->isVoidTy())
            return cg.B.CreateCall(expectedFT, callee, args);

        return cg.B.CreateCall(expectedFT, callee, args, dbgName);
    }

    // ============================================================
    // Type helpers (Pass5/Pass7)
    // ============================================================

    static TypeId expr_type_id_or_bad(const Pass7Result& p7, const ast::Expr* e)
    {
        if (!e)
            return TypeId{UINT32_MAX};
        auto it = p7.expr_type.find(e);
        if (it == p7.expr_type.end())
            return TypeId{UINT32_MAX};
        return it->second;
    }

    static bool is_valid_typeid(const Pass5Result& p5, TypeId t)
    {
        return t.value < p5.types.nodes.size();
    }

    static bool is_ref_type(const Pass5Result& p5, TypeId t,
                            TypeId* out_pointee = nullptr)
    {
        if (!is_valid_typeid(p5, t))
            return false;
        const TypeNode& n = p5.types.nodes[t.value];
        if (n.kind != TypeKind::Ref)
            return false;
        if (out_pointee)
            *out_pointee = n.inner;
        return true;
    }

    // Load through rt_ref_load if the static type is &T / &mut T.
    static llvm::Value* materialize_value_if_ref(FnCG& cg, ast::Expr* e,
                                                 Pass9_5Result& out)
    {
        llvm::Value* v = emit_expr(cg, e, out);
        if (!v)
            return null_obj(cg.st);

        TypeId t = expr_type_id_or_bad(cg.p7, e);
        TypeId pointee{UINT32_MAX};

        if (is_ref_type(cg.p5, t, &pointee))
        {
            if (!cg.rt || !cg.rt->rt_ref_load)
            {
                log_error(out, e ? e->location_ : lex::Loc{},
                          "pass9.5: reserved/reference call needs rt_ref_load but runtime "
                          "does not provide it");
                return null_obj(cg.st);
            }

            llvm::FunctionType* wantFT =
                llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);

            llvm::Value* callee = cg.rt->rt_ref_load;
            if (cg.rt->rt_ref_load->getFunctionType() != wantFT)
                callee = cg.B.CreateBitCast(cg.rt->rt_ref_load, wantFT->getPointerTo(),
                                            "rt_ref_load.cast");

            llvm::Value* refObj = cg.box_if_needed(ValueTag::Obj, v);
            llvm::CallInst* loaded =
                cg.B.CreateCall(wantFT, callee, {refObj}, "ref.load.for.reserved");
            cg.arc_release_value_if_obj(refObj);
            return loaded;
        }

        return v;
    }

    // ============================================================
    // Force condition to i1 (robust)
    // ============================================================

    static llvm::Value* force_i1_condition(FnCG& cg, ast::Expr* cond,
                                           const lex::Loc& loc, Pass9_5Result& out,
                                           llvm::StringRef dbgName = "cond")
    {
        llvm::Value* v = emit_expr(cg, cond, out);
        ValueTag tag = to_value_tag(dyn_tag_of(cg.p8, cond));

        llvm::Value* b = cg.coerce_to(cg.st.i1_ty, tag, v);
        if (!b)
            b = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (b->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
            {
                b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {b},
                                    (dbgName + ".unbox").str());
            }
            else
            {
                log_error(out, loc,
                          "pass9.5: missing runtime intrinsic rt_unbox_bool required for "
                          "condition");
                b = llvm::ConstantInt::getFalse(*cg.st.llctx);
            }
        }

        if (b->getType() != cg.st.i1_ty)
        {
            log_error(out, loc, "pass9.5: internal: condition did not lower to i1");
            b = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        // release if v produced an Obj* and it isn't directly used as b
        if (v && v->getType() == cg.st.obj_ptr_ty)
        {
            if (!(b && b->getType() == cg.st.obj_ptr_ty && b == v))
                cg.arc_release_value_if_obj(v);
        }

        return b;
    }

    // ============================================================
    // Literal emission (Pass7 side tables -> boxed Obj*)
    // ============================================================

    static llvm::Value* emit_char_from_pass7(FnCG& cg,
                                             const ast::CharLiteralExpr& lit,
                                             Pass9_5Result& out)
    {
        auto it = cg.p7.char_id.find(&lit);
        if (it == cg.p7.char_id.end() || it->second >= cg.p7.chars.size())
        {
            log_error(out, lit.location_,
                      "pass9.5: CharLiteralExpr has no Pass7 lowered entry");
            return null_obj(cg.st);
        }

        if (!cg.rt || !cg.rt->rt_char_from_u32)
        {
            log_error(out, lit.location_,
                      "pass9.5: missing runtime intrinsic rt_char_from_u32");
            return null_obj(cg.st);
        }

        const CharLitValue cv = cg.p7.chars[it->second];
        llvm::Value* imm = llvm::ConstantInt::get(
            cg.st.i32_ty, static_cast<std::uint32_t>(cv), false);

        llvm::FunctionType* FT =
            llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.i32_ty}, false);

        llvm::CallInst* call =
            call_runtime_erased(cg, cg.rt->rt_char_from_u32, FT, {imm}, "char.u32");

        return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
    }

    static llvm::Value* emit_int_from_pass7(FnCG& cg,
                                            const ast::IntLiteralExpr& lit,
                                            Pass9_5Result& out)
    {
        auto it = cg.p7.int_id.find(&lit);
        if (it == cg.p7.int_id.end() || it->second >= cg.p7.ints.size())
        {
            log_error(out, lit.location_,
                      "pass9.5: IntLiteralExpr has no Pass7 lowered entry");
            return null_obj(cg.st);
        }

        const auto& v = cg.p7.ints[it->second];
        llvm::Type* i128 = llvm::Type::getInt128Ty(*cg.st.llctx);

        llvm::Value* boxed = nullptr;

        std::visit(
            [&]<typename T0>(T0 vv)
            {
                using T = T0;

                if constexpr (std::is_same_v<T, std::int8_t> ||
                    std::is_same_v<T, std::int16_t> ||
                    std::is_same_v<T, std::int32_t> ||
                    std::is_same_v<T, std::int64_t>)
                {
                    if (!cg.rt || !cg.rt->rt_int_from_i64)
                    {
                        boxed = null_obj(cg.st);
                        return;
                    }
                    llvm::Value* imm = llvm::ConstantInt::get(
                        cg.st.i64_ty, static_cast<std::int64_t>(vv), true);
                    boxed = cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, "int.i64");
                }
                else if constexpr (std::is_same_v<T, std::uint8_t> ||
                    std::is_same_v<T, std::uint16_t> ||
                    std::is_same_v<T, std::uint32_t> ||
                    std::is_same_v<T, std::uint64_t>)
                {
                    if (!cg.rt || (!cg.rt->rt_int_from_u64 && !cg.rt->rt_int_from_i64))
                    {
                        boxed = null_obj(cg.st);
                        return;
                    }
                    llvm::Value* imm = llvm::ConstantInt::get(
                        cg.st.i64_ty, static_cast<std::uint64_t>(vv), false);

                    if (cg.rt->rt_int_from_u64)
                        boxed = cg.B.CreateCall(cg.rt->rt_int_from_u64, {imm}, "int.u64");
                    else
                        boxed = cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, "int.u64");
                }

#if defined(__SIZEOF_INT128__)
                else if constexpr (std::is_same_v<T, unsigned __int128>)
                {
                    if (!cg.rt || !cg.rt->rt_int_from_u128)
                    {
                        boxed = null_obj(cg.st);
                        return;
                    }
                    const auto lo = static_cast<std::uint64_t>(vv);
                    const auto hi = static_cast<std::uint64_t>(vv >> 64);

                    llvm::APInt ap(128, 0);
                    ap.insertBits(llvm::APInt(64, lo), 0);
                    ap.insertBits(llvm::APInt(64, hi), 64);

                    llvm::Value* imm = llvm::ConstantInt::get(i128, ap);
                    boxed = cg.B.CreateCall(cg.rt->rt_int_from_u128, {imm}, "int.u128");
                }
#endif
                else
                {
                    boxed = null_obj(cg.st);
                }
            },
            v);

        return boxed ? boxed : null_obj(cg.st);
    }

    static llvm::Value* emit_float_from_pass7(FnCG& cg,
                                              const ast::FloatLiteralExpr& lit,
                                              Pass9_5Result& out)
    {
        auto it = cg.p7.float_id.find(&lit);
        if (it == cg.p7.float_id.end() || it->second >= cg.p7.floats.size())
        {
            log_error(out, lit.location_,
                      "pass9.5: FloatLiteralExpr has no Pass7 lowered entry");
            return null_obj(cg.st);
        }

        const auto& v = cg.p7.floats[it->second];
        llvm::Value* boxed = nullptr;

        std::visit(
            [&]<typename T0>(T0 vv)
            {
                using T = T0;

                if constexpr (std::is_same_v<T, float>)
                {
                    if (!cg.rt || !cg.rt->rt_float_from_f32)
                    {
                        boxed = null_obj(cg.st);
                        return;
                    }
                    llvm::Type* f32_ty = llvm::Type::getFloatTy(*cg.st.llctx);
                    llvm::Value* imm = llvm::ConstantFP::get(f32_ty, (double)vv);
                    boxed = cg.B.CreateCall(cg.rt->rt_float_from_f32, {imm}, "f32");
                }
                else if constexpr (std::is_same_v<T, double>)
                {
                    if (!cg.rt || !cg.rt->rt_float_from_f64)
                    {
                        boxed = null_obj(cg.st);
                        return;
                    }
                    llvm::Type* f64_ty = llvm::Type::getDoubleTy(*cg.st.llctx);
                    llvm::Value* imm = llvm::ConstantFP::get(f64_ty, vv);
                    boxed = cg.B.CreateCall(cg.rt->rt_float_from_f64, {imm}, "f64");
                }
                else
                {
                    boxed = null_obj(cg.st);
                }
            },
            v);

        return boxed ? boxed : null_obj(cg.st);
    }

    // ============================================================
    // Struct literal support
    // ============================================================

    static std::optional<uint32_t>
    try_field_index_from_pass5(const Pass5Result& p5, StructId sid,
                               lex::SymId field_name)
    {
        auto itL = p5.struct_layout.find(sid);
        if (itL == p5.struct_layout.end())
            return std::nullopt;

        const auto& layout = itL->second;
        auto itF = layout.name_to_index.find(field_name);
        if (itF == layout.name_to_index.end())
            return std::nullopt;

        return itF->second;
    }

    static llvm::Value* emit_struct_lit(FnCG& cg, ast::StructLiteralExpr& s,
                                        Pass9_5Result& out)
    {
        const DynTag dt = dyn_tag_of(cg.p8, static_cast<const ast::Expr*>(&s));
        if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
        {
            log_error(out, s.location_,
                      "pass9.5: struct literal has no StructId tag (Pass8 missing "
                      "StructObj tag?)");
            return null_obj(cg.st);
        }

        if (!cg.rt || !cg.rt->rt_struct_new || !cg.rt->rt_struct_set_field)
        {
            log_error(out, s.location_,
                      "pass9.5: missing runtime intrinsic(s) for struct literal "
                      "(need rt_struct_new, rt_struct_set_field)");
            return null_obj(cg.st);
        }

        const StructId sid = *dt.struct_id;

        const auto sid_i64 = static_cast<std::int64_t>(sid.index);
        llvm::Value* sidV = llvm::ConstantInt::get(cg.st.i64_ty, sid_i64);
        const auto n_inits = static_cast<std::int64_t>(s.elements_.size());
        llvm::Value* nFieldsV = llvm::ConstantInt::get(cg.st.i64_ty, n_inits);

        llvm::Value* obj =
            cg.B.CreateCall(cg.rt->rt_struct_new, {sidV, nFieldsV}, "struct.new");

        std::unordered_set<lex::SymId> seen;
        std::int64_t fallback_index = 0;

        for (auto* fi : s.elements_)
        {
            if (!fi)
                continue;

            const lex::SymId fname = fi->name;
            if (!seen.insert(fname).second)
            {
                log_error_ident(out, fi->location_, fname,
                                "pass9.5: duplicate field initializer in struct literal");
                continue;
            }

            std::optional<uint32_t> idx = try_field_index_from_pass5(cg.p5, sid, fname);
            std::int64_t idx_i64 =
                idx.has_value() ? static_cast<std::int64_t>(*idx) : fallback_index++;

            llvm::Value* idxV = llvm::ConstantInt::get(cg.st.i64_ty, idx_i64);

            llvm::Value* rhs = emit_expr(cg, fi->value_, out);
            ValueTag rhsTag = to_value_tag(dyn_tag_of(cg.p8, fi->value_));
            llvm::Value* rhsObj = cg.box_if_needed(rhsTag, rhs);

            cg.B.CreateCall(cg.rt->rt_struct_set_field, {obj, idxV, rhsObj});
            cg.arc_release_value_if_obj(rhsObj);
        }

        return obj;
    }

    // ============================================================
    // Reserved runtime intrinsics lowering (print / box_*)
    // ============================================================

    static llvm::Value* emit_reserved_call(FnCG& cg, llvm::StringRef calleeName,
                                           ast::CallExpr& c, Pass9_5Result& out,
                                           bool& handled)
    {
        handled = true;

        // print<T>(t: &T) -> void
        if (calleeName == "print")
        {
            if (c.args_.size() != 1)
            {
                log_error(out, c.location_,
                          "pass9.5: print: wrong number of args (expected 1)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->rt_print)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic rt_print");
                return nullptr;
            }

            llvm::Value* v = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag tag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* obj = cg.box_if_needed(tag, v);

            llvm::FunctionType* FT =
                llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);

            (void)call_runtime_erased(cg, cg.rt->rt_print, FT, {obj}, "rt_print");
            cg.arc_release_value_if_obj(obj);
            return nullptr;
        }

        if (calleeName == "put")
        {
            if (c.args_.size() != 1)
            {
                log_error(out, c.location_,
                          "pass9.5: put: wrong number of args (expected 1)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->rt_put)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic rt_put");
                return nullptr;
            }

            llvm::Value* v = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag tag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* obj = cg.box_if_needed(tag, v);

            llvm::FunctionType* FT =
                llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);

            (void)call_runtime_erased(cg, cg.rt->rt_put, FT, {obj}, "rt_put");
            cg.arc_release_value_if_obj(obj);
            return nullptr;
        }

        // nl() -> void
        if (calleeName == "nl")
        {
            if (!c.args_.empty())
            {
                log_error(out, c.location_,
                          "pass9.5: nl: wrong number of args (expected 0)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->rt_nl)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic rt_nl");
                return nullptr;
            }

            llvm::FunctionType* FT =
                llvm::FunctionType::get(cg.st.void_ty, {}, false);

            (void)call_runtime_erased(cg, cg.rt->rt_nl, FT, {}, "rt_nl");
            return nullptr;
        }

        // Erased Box ABI:
        // box_new  : Obj* box_new(Obj* count, i64 kind, i64 elem_size, i64 elem_align)
        // box_free : void box_free(Obj* box)
        // box_len  : Obj* box_len(Obj* box)
        // box_get  : Obj* box_get(Obj* box, Obj* i)
        // box_set  : void box_set(Obj* box, Obj* i, Obj* v)

        if (calleeName == "box_new")
        {
            if (c.args_.size() != 1)
            {
                log_error(out, c.location_,
                          "pass9.5: box_new: wrong number of args (expected 1)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_new)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic box_new");
                return null_obj(cg.st);
            }

            llvm::Value* cntV = emit_expr(cg, c.args_[0], out);
            ValueTag cntTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* cntObj = cg.box_if_needed(cntTag, cntV);

            // Default layout: Obj* elements
            llvm::Value* kindV = llvm::ConstantInt::get(cg.st.i64_ty, 0);
            llvm::Value* sizeV = llvm::ConstantInt::get(cg.st.i64_ty, 8);
            llvm::Value* alignV = llvm::ConstantInt::get(cg.st.i64_ty, 8);

            llvm::FunctionType* FT = llvm::FunctionType::get(
                cg.st.obj_ptr_ty,
                {cg.st.obj_ptr_ty, cg.st.i64_ty, cg.st.i64_ty, cg.st.i64_ty}, false);

            llvm::CallInst* call = call_runtime_erased(
                cg, cg.rt->box_new, FT, {cntObj, kindV, sizeV, alignV}, "box_new");

            cg.arc_release_value_if_obj(cntObj);
            return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
        }

        if (calleeName == "box_free")
        {
            if (c.args_.size() != 1)
            {
                log_error(out, c.location_,
                          "pass9.5: box_free: wrong number of args (expected 1)");
                return nullptr;
            }
            if (!cg.rt || !cg.rt->box_free || !cg.rt->rt_ref_load ||
                !cg.rt->rt_ref_store)
            {
                log_error(out, c.location_,
                          "pass9.5: missing runtime intrinsic(s) for box_free "
                          "(need box_free, rt_ref_load, rt_ref_store)");
                return nullptr;
            }

            ast::Expr* ae = c.args_[0];

            llvm::Value* argV = emit_expr(cg, ae, out);
            llvm::Value* argObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ae)), argV);

            TypeId t = expr_type_id_or_bad(cg.p7, ae);
            TypeId pointee{UINT32_MAX};

            if (is_ref_type(cg.p5, t, &pointee))
            {
                llvm::FunctionType* loadFT =
                    llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);
                llvm::CallInst* loaded = call_runtime_erased(
                    cg, cg.rt->rt_ref_load, loadFT, {argObj}, "ref.load.for.box_free");

                llvm::FunctionType* freeFT =
                    llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);
                (void)call_runtime_erased(cg, cg.rt->box_free, freeFT, {loaded},
                                          "box_free.ref");

                llvm::FunctionType* storeFT = llvm::FunctionType::get(
                    cg.st.void_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);
                (void)call_runtime_erased(cg, cg.rt->rt_ref_store, storeFT,
                                          {argObj, null_obj(cg.st)}, "ref.store.null");

                cg.arc_release_value_if_obj(loaded);
                cg.arc_release_value_if_obj(argObj);
                return nullptr;
            }

            llvm::FunctionType* freeFT =
                llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);
            (void)call_runtime_erased(cg, cg.rt->box_free, freeFT, {argObj},
                                      "box_free");
            cg.arc_release_value_if_obj(argObj);
            return nullptr;
        }

        if (calleeName == "box_len")
        {
            if (c.args_.size() != 1)
            {
                log_error(out, c.location_,
                          "pass9.5: box_len: wrong number of args (expected 1)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_len)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic box_len");
                return null_obj(cg.st);
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            llvm::Value* boxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[0])), boxV);

            llvm::FunctionType* FT =
                llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);
            llvm::CallInst* call =
                call_runtime_erased(cg, cg.rt->box_len, FT, {boxObj}, "box_len");
            cg.arc_release_value_if_obj(boxObj);
            return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
        }

        if (calleeName == "box_get")
        {
            if (c.args_.size() != 2)
            {
                log_error(out, c.location_,
                          "pass9.5: box_get: wrong number of args (expected 2)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_get)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic box_get");
                return null_obj(cg.st);
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            llvm::Value* boxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[0])), boxV);

            llvm::Value* idxV = emit_expr(cg, c.args_[1], out);
            llvm::Value* idxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[1])), idxV);

            llvm::FunctionType* FT = llvm::FunctionType::get(
                cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);

            llvm::CallInst* call = call_runtime_erased(
                cg, cg.rt->box_get, FT, {boxObj, idxObj}, "box_get");

            cg.arc_release_value_if_obj(boxObj);
            cg.arc_release_value_if_obj(idxObj);
            return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
        }

        if (calleeName == "box_set")
        {
            if (c.args_.size() != 3)
            {
                log_error(out, c.location_,
                          "pass9.5: box_set: wrong number of args (expected 3)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->box_set)
            {
                log_error(out, c.location_, "pass9.5: missing runtime intrinsic box_set");
                return nullptr;
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            llvm::Value* boxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[0])), boxV);

            llvm::Value* idxV = emit_expr(cg, c.args_[1], out);
            llvm::Value* idxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[1])), idxV);

            llvm::Value* valV = emit_expr(cg, c.args_[2], out);
            llvm::Value* valObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, c.args_[2])), valV);

            llvm::FunctionType* FT = llvm::FunctionType::get(
                cg.st.void_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
                false);

            (void)call_runtime_erased(cg, cg.rt->box_set, FT, {boxObj, idxObj, valObj},
                                      "box_set");

            cg.arc_release_value_if_obj(boxObj);
            cg.arc_release_value_if_obj(idxObj);
            cg.arc_release_value_if_obj(valObj);
            return nullptr;
        }

        handled = false;
        return nullptr;
    }

    // ============================================================
    // Expression emission
    // ============================================================

    static llvm::Value* emit_ref(FnCG& cg, ast::RefExpr& r, Pass9_5Result& out)
    {
        if (!cg.binds)
        {
            log_error(out, r.location_,
                      "pass9.5: internal: missing FnBindings when emitting RefExpr");
            return null_obj(cg.st);
        }

        auto it = cg.binds->ref_binding.find(&r);
        if (it == cg.binds->ref_binding.end())
        {
            log_error(out, r.location_,
                      "pass9.5: RefExpr has no binding entry (Pass6 missing?)");
            return null_obj(cg.st);
        }

        const Binding& b = it->second;

        switch (b.kind)
        {
        case BindingKind::LocalSlot:
            {
                llvm::Value* v = cg.B.CreateLoad(cg.st.obj_ptr_ty,
                                                 cg.slot_alloca[b.slot.index], "ld.slot");
                if (cg.rt && cg.rt->rt_retain)
                    cg.B.CreateCall(cg.rt->rt_retain, {v});
                return v; // owned
            }

        default:
            log_error(out, r.location_,
                      "pass9.5: RefExpr used as a value is only supported for locals");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_assign(FnCG& cg, ast::AssignExpr& a,
                                    Pass9_5Result& out)
    {
        llvm::Value* rhs = emit_expr(cg, a.rhs_, out);
        llvm::Value* rhsObj =
            cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, a.rhs_)), rhs);

        // Case 1: local slot assignment
        if (auto* lhs_ref = dynamic_cast<ast::RefExpr*>(a.lhs_))
        {
            if (!cg.binds)
            {
                log_error(out, a.location_,
                          "pass9.5: internal: missing FnBindings in assignment");
                return null_obj(cg.st);
            }

            auto it = cg.binds->ref_binding.find(lhs_ref);
            if (it == cg.binds->ref_binding.end() ||
                it->second.kind != BindingKind::LocalSlot)
            {
                log_error(out, a.location_,
                          "pass9.5: assignment LHS must be a bound local slot");
                return null_obj(cg.st);
            }

            const SlotId slot = it->second.slot;
            if (slot.index >= cg.slot_alloca.size() || !cg.slot_alloca[slot.index])
            {
                log_error(out, a.location_,
                          "pass9.5: internal: local slot has no alloca in prologue");
                return null_obj(cg.st);
            }

            cg.arc_store_slot(cg.slot_alloca[slot.index], rhsObj);
            return rhsObj;
        }

        // Case 2: deref assignment: *p = rhs;
        if (auto* lhs_u = dynamic_cast<ast::UnaryExpr*>(a.lhs_))
        {
            if (lhs_u->op != ast::UnaryOp::deref)
            {
                log_error(out, a.location_,
                          "pass9.5: assignment supports only RefExpr or deref (*expr) on "
                          "LHS");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->rt_ref_store)
            {
                log_error(out, a.location_,
                          "pass9.5: missing runtime intrinsic rt_ref_store");
                return null_obj(cg.st);
            }

            llvm::Value* refVal = emit_expr(cg, lhs_u->expr_, out);
            llvm::Value* refObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, lhs_u->expr_)), refVal);

            cg.B.CreateCall(cg.rt->rt_ref_store, {refObj, rhsObj});
            cg.arc_release_value_if_obj(refObj);
            return rhsObj;
        }

        // Case 3: index assignment: base[i] = rhs;
        if (auto* lhs_ix = dynamic_cast<ast::IndexExpr*>(a.lhs_))
        {
            if (!cg.rt || !cg.rt->box_set)
            {
                log_error(out, a.location_,
                          "pass9.5: missing runtime intrinsic box_set (needed for index "
                          "assignment)");
                return null_obj(cg.st);
            }

            llvm::Value* baseV = materialize_value_if_ref(cg, lhs_ix->base_, out);
            llvm::Value* baseObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, lhs_ix->base_)), baseV);

            llvm::Value* idxV = emit_expr(cg, lhs_ix->index_, out);
            llvm::Value* idxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, lhs_ix->index_)), idxV);

            llvm::FunctionType* setFT = llvm::FunctionType::get(
                cg.st.void_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
                false);

            (void)call_runtime_erased(cg, cg.rt->box_set, setFT,
                                      {baseObj, idxObj, rhsObj},
                                      "box_set.index.assign");
            cg.arc_release_value_if_obj(baseObj);
            cg.arc_release_value_if_obj(idxObj);
            return rhsObj;
        }

        log_error(out, a.location_,
                  "pass9.5: assignment supports only local refs (x=), deref (*p=), "
                  "or index (a[i]=) on LHS");
        return null_obj(cg.st);
    }

    static llvm::Value* emit_call(FnCG& cg, ast::CallExpr& c, Pass9_5Result& out)
    {
        if (!cg.binds)
        {
            log_error(out, c.location_,
                      "pass9.5: internal: missing FnBindings when emitting CallExpr");
            return null_obj(cg.st);
        }

        if (!c.callee_)
        {
            log_error(out, c.location_, "pass9.5: call has null callee");
            return null_obj(cg.st);
        }

        const Binding* b = nullptr;

        if (auto it = cg.binds->expr_binding.find(c.callee_);
            it != cg.binds->expr_binding.end())
            b = &it->second;

        if (!b)
        {
            if (auto* callee_ref = dynamic_cast<ast::RefExpr*>(c.callee_))
            {
                if (auto it2 = cg.binds->ref_binding.find(callee_ref);
                    it2 != cg.binds->ref_binding.end())
                    b = &it2->second;
            }
        }

        if (!b)
        {
            log_error(out, c.location_,
                      "pass9.5: call callee is not bound (Pass6 missing expr_binding)");
            return null_obj(cg.st);
        }

        // RuntimeIntrinsic path: route by the intrinsic target name
        if (b->kind == BindingKind::RuntimeIntrinsic)
        {
            // Map enum -> string name; keep local to avoid relying on other utilities.
            auto intrinsic_name = [](RuntimeIntrinsic k) -> llvm::StringRef
            {
                switch (k)
                {
                case RuntimeIntrinsic::box_new:
                    return "box_new";
                case RuntimeIntrinsic::box_free:
                    return "box_free";
                case RuntimeIntrinsic::box_len:
                    return "box_len";
                case RuntimeIntrinsic::box_get:
                    return "box_get";
                case RuntimeIntrinsic::box_set:
                    return "box_set";
                case RuntimeIntrinsic::print:
                    return "print";
                case RuntimeIntrinsic::put:
                    return "put";
                case RuntimeIntrinsic::nl:
                    return "nl";
                default:
                    return "";
                }
            };

            llvm::StringRef nm = intrinsic_name(b->intrinsic);
            if (nm.empty())
            {
                log_error(out, c.location_,
                          "pass9.5: unknown runtime intrinsic bound in call callee");
                return null_obj(cg.st);
            }

            bool handled = false;
            llvm::Value* r = emit_reserved_call(cg, nm, c, out, handled);
            if (handled)
                return r; // may be nullptr for void-return
            log_error(out, c.location_,
                      "pass9.5: runtime intrinsic was not handled by reserved lowering");
            return null_obj(cg.st);
        }

        // Normal callable path: GlobalFn / GlobalLoadFn
        llvm::Function* target = nullptr;

        switch (b->kind)
        {
        case BindingKind::GlobalFn:
            {
                auto it = cg.st.fn_decls.find(b->fn);
                if (it != cg.st.fn_decls.end())
                    target = it->second;
            }
            break;

        case BindingKind::GlobalLoadFn:
            {
                auto it = cg.st.load_fn_decls.find(b->load_fn);
                if (it != cg.st.load_fn_decls.end())
                    target = it->second;
            }
            break;

        default:
            log_error(out, c.location_,
                      "pass9.5: call callee is not callable (expected GlobalFn, "
                      "GlobalLoadFn, or RuntimeIntrinsic)");
            return null_obj(cg.st);
        }

        if (!target)
        {
            log_error(out, c.location_,
                      "pass9.5: call target not declared in IR (Pass9.3 missing?)");
            return null_obj(cg.st);
        }

        // Treat unmangled runtime functions as reserved if they appear directly
        {
            llvm::StringRef calleeName = target->getName();
            bool handled = false;
            if (calleeName == "print" || calleeName == "box_new" ||
                calleeName == "box_free" || calleeName == "box_len" ||
                calleeName == "box_get" || calleeName == "box_set"
                || calleeName == "put" || calleeName == "nl")
            {
                llvm::Value* r = emit_reserved_call(cg, calleeName, c, out, handled);
                if (handled)
                    return r;
            }
        }

        llvm::FunctionType* FT = target->getFunctionType();
        const unsigned nParams = FT->getNumParams();
        const unsigned nArgs = static_cast<unsigned>(c.args_.size());

        if (nArgs != nParams)
        {
            log_error(out, c.location_,
                      "pass9.5: call argument count does not match callee signature");
            return null_obj(cg.st);
        }

        std::vector<llvm::Value*> args;
        args.reserve(nParams);

        std::vector<llvm::Value*> release_after;
        release_after.reserve(nParams);

        for (unsigned i = 0; i < nParams; ++i)
        {
            llvm::Type* PT = FT->getParamType(i);
            ast::Expr* ae = c.args_[i];

            llvm::Value* av = emit_expr(cg, ae, out);
            ValueTag at = to_value_tag(dyn_tag_of(cg.p8, ae));

            llvm::Value* coerced = cg.coerce_to(PT, at, av);
            if (!coerced)
                coerced = llvm::UndefValue::get(PT);

            if (coerced && coerced->getType() == cg.st.obj_ptr_ty)
                release_after.push_back(coerced);
            else if (av && av->getType() == cg.st.obj_ptr_ty)
                release_after.push_back(av);

            args.push_back(coerced);
        }

        llvm::CallInst* call = cg.B.CreateCall(target, args);
        for (llvm::Value* x : release_after)
            cg.arc_release_value_if_obj(x);

        // Return coercion to match the dynamic tag
        ValueTag retTag = to_value_tag(dyn_tag_of(cg.p8, &c));

        if (call->getType()->isVoidTy())
            return nullptr;

        if (call->getType() == cg.st.i1_ty && retTag == ValueTag::Obj)
        {
            if (!cg.rt || !cg.rt->rt_box_bool)
            {
                log_error(out, c.location_,
                          "pass9.5: missing rt_box_bool to box bool return");
                return null_obj(cg.st);
            }
            return cg.B.CreateCall(cg.rt->rt_box_bool, {call}, "box.ret.bool");
        }

        if (call->getType() == cg.st.obj_ptr_ty && retTag == ValueTag::Bool)
        {
            if (!cg.rt || !cg.rt->rt_unbox_bool)
            {
                log_error(out, c.location_,
                          "pass9.5: missing rt_unbox_bool to unbox bool return");
                cg.arc_release_value_if_obj(call);
                return llvm::ConstantInt::getFalse(*cg.st.llctx);
            }
            llvm::Value* b =
                cg.B.CreateCall(cg.rt->rt_unbox_bool, {call}, "unbox.ret.bool");
            cg.arc_release_value_if_obj(call);
            return b;
        }

        return call;
    }

    static llvm::Value* emit_logical_and(FnCG& cg, ast::BinaryExpr& b,
                                         Pass9_5Result& out)
    {
        llvm::Function* F = cg.B.GetInsertBlock()
                                ? cg.B.GetInsertBlock()->getParent()
                                : cg.F;
        if (!F)
        {
            log_error(out, b.location_, "pass9.5: internal: missing current function");
            return llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        llvm::BasicBlock* predBB = cg.B.GetInsertBlock();

        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        llvm::Value* lhsB = cg.coerce_to(cg.st.i1_ty,
                                         to_value_tag(dyn_tag_of(cg.p8, b.lhs_)),
                                         lhsV);
        if (!lhsB)
            lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (lhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                lhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {lhsB}, "land.lhs.unbox");
            else
                lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (lhsV && lhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(lhsV);

        llvm::BasicBlock* rhsBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "land.rhs", F);
        llvm::BasicBlock* endBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "land.end", F);

        cg.B.CreateCondBr(lhsB, rhsBB, endBB);

        cg.B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);
        llvm::Value* rhsB = cg.coerce_to(cg.st.i1_ty,
                                         to_value_tag(dyn_tag_of(cg.p8, b.rhs_)),
                                         rhsV);
        if (!rhsB)
            rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (rhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                rhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {rhsB}, "land.rhs.unbox");
            else
                rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (rhsV && rhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(rhsV);

        cg.B.CreateBr(endBB);

        cg.B.SetInsertPoint(endBB);
        auto* phi = cg.B.CreatePHI(cg.st.i1_ty, 2, "land");
        phi->addIncoming(llvm::ConstantInt::getFalse(*cg.st.llctx), predBB);
        phi->addIncoming(rhsB, rhsBB);
        return phi;
    }

    static llvm::Value* emit_logical_or(FnCG& cg, ast::BinaryExpr& b,
                                        Pass9_5Result& out)
    {
        llvm::Function* F = cg.B.GetInsertBlock()
                                ? cg.B.GetInsertBlock()->getParent()
                                : cg.F;
        if (!F)
        {
            log_error(out, b.location_, "pass9.5: internal: missing current function");
            return llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        llvm::BasicBlock* predBB = cg.B.GetInsertBlock();

        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        llvm::Value* lhsB = cg.coerce_to(cg.st.i1_ty,
                                         to_value_tag(dyn_tag_of(cg.p8, b.lhs_)),
                                         lhsV);
        if (!lhsB)
            lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (lhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                lhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {lhsB}, "lor.lhs.unbox");
            else
                lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (lhsV && lhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(lhsV);

        llvm::BasicBlock* rhsBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "lor.rhs", F);
        llvm::BasicBlock* endBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "lor.end", F);

        cg.B.CreateCondBr(lhsB, endBB, rhsBB);

        cg.B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);
        llvm::Value* rhsB = cg.coerce_to(cg.st.i1_ty,
                                         to_value_tag(dyn_tag_of(cg.p8, b.rhs_)),
                                         rhsV);
        if (!rhsB)
            rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (rhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                rhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {rhsB}, "lor.rhs.unbox");
            else
                rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (rhsV && rhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(rhsV);

        cg.B.CreateBr(endBB);

        cg.B.SetInsertPoint(endBB);
        auto* phi = cg.B.CreatePHI(cg.st.i1_ty, 2, "lor");
        phi->addIncoming(llvm::ConstantInt::getTrue(*cg.st.llctx), predBB);
        phi->addIncoming(rhsB, rhsBB);
        return phi;
    }

    static llvm::Value* emit_binary(FnCG& cg, ast::BinaryExpr& b,
                                    Pass9_5Result& out)
    {
        using Op = ast::BinaryOp;

        if (b.op == Op::logical_and)
            return emit_logical_and(cg, b, out);
        if (b.op == Op::logical_or)
            return emit_logical_or(cg, b, out);

        if (!cg.rt)
        {
            log_error(out, b.location_,
                      "pass9.5: internal: missing runtime decls in FnCG");
            return null_obj(cg.st);
        }

        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);

        llvm::Value* lhsObj = cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, b.lhs_)),
                                               lhsV);
        llvm::Value* rhsObj = cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, b.rhs_)),
                                               rhsV);

        auto call2_and_release = [&](llvm::FunctionCallee callee,
                                     const char* name) -> llvm::Value*
        {
            llvm::Value* res = cg.B.CreateCall(callee, {lhsObj, rhsObj}, name);
            cg.arc_release_value_if_obj(lhsObj);
            cg.arc_release_value_if_obj(rhsObj);
            return res;
        };

        switch (b.op)
        {
        case Op::add:
            return call2_and_release(cg.rt->rt_add, "add");
        case Op::subtract:
            return call2_and_release(cg.rt->rt_sub, "sub");
        case Op::multiply:
            return call2_and_release(cg.rt->rt_mul, "mul");
        case Op::divide:
            return call2_and_release(cg.rt->rt_div, "div");
        case Op::modulo:
            return call2_and_release(cg.rt->rt_mod, "mod");

        case Op::equal:
            return call2_and_release(cg.rt->rt_eq, "eq");
        case Op::not_equal:
            return call2_and_release(cg.rt->rt_ne, "ne");
        case Op::less:
            return call2_and_release(cg.rt->rt_lt, "lt");
        case Op::less_equal:
            return call2_and_release(cg.rt->rt_le, "le");
        case Op::greater:
            return call2_and_release(cg.rt->rt_gt, "gt");
        case Op::greater_equal:
            return call2_and_release(cg.rt->rt_ge, "ge");

        default:
            log_error(out, b.location_, "pass9.5: unsupported binary operator");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_unary(FnCG& cg, ast::UnaryExpr& u,
                                   Pass9_5Result& out)
    {
        using U = ast::UnaryOp;

        switch (u.op)
        {
        case U::logical_not:
            {
                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                llvm::Value* b = cg.coerce_to(cg.st.i1_ty,
                                              to_value_tag(dyn_tag_of(cg.p8, u.expr_)),
                                              inner);
                if (!b)
                    b = llvm::ConstantInt::getFalse(*cg.st.llctx);

                if (b->getType() == cg.st.obj_ptr_ty)
                {
                    if (cg.rt && cg.rt->rt_unbox_bool)
                        b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {b}, "not.unbox");
                    else
                        b = llvm::ConstantInt::getFalse(*cg.st.llctx);
                }

                cg.arc_release_value_if_obj(inner);
                return cg.B.CreateNot(b, "not");
            }

        case U::negation:
            {
                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                llvm::Value* xObj = cg.box_if_needed(
                    to_value_tag(dyn_tag_of(cg.p8, u.expr_)), inner);
                if (inner && inner->getType() == cg.st.obj_ptr_ty && xObj != inner)
                    cg.arc_release_value_if_obj(inner);

                if (!xObj)
                    return null_obj(cg.st);

                if (cg.rt && cg.rt->rt_neg)
                {
                    llvm::Value* res = cg.B.CreateCall(cg.rt->rt_neg, {xObj}, "neg");
                    cg.arc_release_value_if_obj(xObj);
                    return res;
                }

                log_error(out, u.location_,
                          "pass9.5: unary '-' requires rt_neg (or extend this pass to "
                          "synthesize via rt_sub)");
                cg.arc_release_value_if_obj(xObj);
                return null_obj(cg.st);
            }

        case U::deref:
            {
                if (!cg.rt || !cg.rt->rt_ref_load)
                {
                    log_error(out, u.location_,
                              "pass9.5: missing runtime intrinsic rt_ref_load");
                    return null_obj(cg.st);
                }

                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                llvm::Value* refObj = cg.box_if_needed(
                    to_value_tag(dyn_tag_of(cg.p8, u.expr_)), inner);
                if (inner && inner->getType() == cg.st.obj_ptr_ty && refObj != inner)
                    cg.arc_release_value_if_obj(inner);

                llvm::Value* loadedObj =
                    cg.B.CreateCall(cg.rt->rt_ref_load, {refObj}, "ref.load");
                cg.arc_release_value_if_obj(refObj);

                ValueTag resTag = to_value_tag(dyn_tag_of(cg.p8, &u));
                if (resTag == ValueTag::Bool)
                {
                    if (!cg.rt || !cg.rt->rt_unbox_bool)
                    {
                        log_error(out, u.location_,
                                  "pass9.5: missing rt_unbox_bool for deref bool");
                        cg.arc_release_value_if_obj(loadedObj);
                        return llvm::ConstantInt::getFalse(*cg.st.llctx);
                    }
                    llvm::Value* b =
                        cg.B.CreateCall(cg.rt->rt_unbox_bool, {loadedObj}, "unbox.deref.bool");
                    cg.arc_release_value_if_obj(loadedObj);
                    return b;
                }

                return loadedObj;
            }

        case U::addr_of:
        case U::addr_of_mut:
            {
                // &(*p) == p
                if (auto* innerU = dynamic_cast<ast::UnaryExpr*>(u.expr_))
                    if (innerU->op == U::deref)
                        return emit_expr(cg, innerU->expr_, out);

                const bool wantMut = (u.op == U::addr_of_mut);
                if (wantMut && !place_is_mutable(cg, u.expr_))
                {
                    log_error(out, u.location_,
                              "pass9.5: cannot take &mut of an immutable place");
                    return null_obj(cg.st);
                }

                llvm::Value* slotAddr = emit_place_slot_addr(cg, u.expr_, out);
                if (!slotAddr)
                {
                    log_error(out, u.location_,
                              "pass9.5: address-of supported only for places "
                              "(locals/fields/index) in this pass");
                    return null_obj(cg.st);
                }

                if (!cg.rt || !cg.rt->rt_ref_from_slot)
                {
                    log_error(out, u.location_,
                              "pass9.5: missing runtime intrinsic rt_ref_from_slot");
                    return null_obj(cg.st);
                }

                return cg.B.CreateCall(cg.rt->rt_ref_from_slot, {slotAddr}, "ref.from.slot");
            }

        default:
            log_error(out, u.location_, "pass9.5: unsupported unary operator");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_field(FnCG& cg, ast::FieldExpr& f,
                                   Pass9_5Result& out)
    {
        if (!cg.rt || !cg.rt->rt_struct_get_field)
        {
            log_error(out, f.location_,
                      "pass9.5: missing runtime intrinsic rt_struct_get_field");
            return null_obj(cg.st);
        }

        // NEW: load through rt_ref_load if base is &T / &mut T
        llvm::Value* baseV = materialize_value_if_ref(cg, f.base_, out);

        llvm::Value* baseObj =
            cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, f.base_)), baseV);

        DynTag dt = dyn_tag_of(cg.p8, f.base_);
        if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
        {
            log_error(out, f.location_,
                      "pass9.5: field access on non-struct value (Pass8 missing StructObj tag?)");
            cg.arc_release_value_if_obj(baseObj);
            return null_obj(cg.st);
        }

        StructId sid = *dt.struct_id;
        auto idxOpt = try_field_index_from_pass5(cg.p5, sid, f.field);
        if (!idxOpt.has_value())
        {
            log_error_ident(out, f.location_, f.field,
                            "pass9.5: unknown field name for struct");
            cg.arc_release_value_if_obj(baseObj);
            return null_obj(cg.st);
        }

        llvm::Value* idxV =
            llvm::ConstantInt::get(cg.st.i64_ty, static_cast<std::int64_t>(*idxOpt));

        llvm::Value* res =
            cg.B.CreateCall(cg.rt->rt_struct_get_field, {baseObj, idxV}, "struct.get");

        cg.arc_release_value_if_obj(baseObj);
        return res;
    }

    static llvm::Value* emit_index_expr(FnCG& cg, ast::IndexExpr& ix,
                                        Pass9_5Result& out)
    {
        if (!cg.rt || !cg.rt->box_get)
        {
            log_error(out, ix.location_,
                      "pass9.5: missing runtime intrinsic box_get (index expression)");
            return null_obj(cg.st);
        }

        llvm::Value* baseV = materialize_value_if_ref(cg, ix.base_, out);
        llvm::Value* baseObj =
            cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ix.base_)), baseV);

        llvm::Value* idxV = emit_expr(cg, ix.index_, out);
        llvm::Value* idxObj =
            cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ix.index_)), idxV);

        llvm::FunctionType* getFT = llvm::FunctionType::get(
            cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);

        llvm::CallInst* call = call_runtime_erased(
            cg, cg.rt->box_get, getFT, {baseObj, idxObj}, "box_get.index");

        cg.arc_release_value_if_obj(baseObj);
        cg.arc_release_value_if_obj(idxObj);

        return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
    }

    static llvm::Value* emit_array_literal(FnCG& cg, ast::ArrayLiteralExpr& a,
                                           Pass9_5Result& out)
    {
        if (!cg.rt || !cg.rt->box_new || !cg.rt->box_set)
        {
            log_error(out, a.location_,
                      "pass9.5: missing runtime intrinsic box_new/box_set (array "
                      "literal)");
            return null_obj(cg.st);
        }

        auto emit_u64_as_obj = [&](std::uint64_t v, const lex::Loc& loc,
                                   llvm::StringRef dbg) -> llvm::Value*
        {
            if (!cg.rt || (!cg.rt->rt_int_from_u64 && !cg.rt->rt_int_from_i64))
            {
                log_error(out, loc,
                          "pass9.5: missing rt_int_from_u64/rt_int_from_i64 (needed for "
                          "array literal/index)");
                return null_obj(cg.st);
            }
            llvm::Value* imm =
                llvm::ConstantInt::get(cg.st.i64_ty, (uint64_t)v, false);
            if (cg.rt->rt_int_from_u64)
                return cg.B.CreateCall(cg.rt->rt_int_from_u64, {imm}, (dbg + ".u64").str());
            return cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, (dbg + ".i64").str());
        };

        const auto n = (std::uint64_t)a.v_.size();

        llvm::Value* lenObj = emit_u64_as_obj(n, a.location_, "arr.len");
        llvm::Value* kind = llvm::ConstantInt::get(cg.st.i64_ty, 0); // ObjPtr
        llvm::Value* esz = llvm::ConstantInt::get(cg.st.i64_ty, 8);
        llvm::Value* eal = llvm::ConstantInt::get(cg.st.i64_ty, 8);

        llvm::FunctionType* newFT = llvm::FunctionType::get(
            cg.st.obj_ptr_ty,
            {cg.st.obj_ptr_ty, cg.st.i64_ty, cg.st.i64_ty, cg.st.i64_ty}, false);

        llvm::CallInst* box = call_runtime_erased(
            cg, cg.rt->box_new, newFT, {lenObj, kind, esz, eal}, "box_new.arrlit");
        llvm::Value* arrObj = box ? (llvm::Value*)box : null_obj(cg.st);

        cg.arc_release_value_if_obj(lenObj);

        llvm::FunctionType* setFT = llvm::FunctionType::get(
            cg.st.void_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
            false);

        for (std::uint64_t i = 0; i < n; ++i)
        {
            ast::Expr* el = a.v_[(size_t)i];
            if (!el)
                continue;

            llvm::Value* idxObj = emit_u64_as_obj(i, el->location_, "arr.idx");

            llvm::Value* v = emit_expr(cg, el, out);
            llvm::Value* vObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, el)), v);

            (void)call_runtime_erased(cg, cg.rt->box_set, setFT, {arrObj, idxObj, vObj},
                                      "box_set.arrlit");

            cg.arc_release_value_if_obj(idxObj);
            cg.arc_release_value_if_obj(vObj);
        }

        return arrObj;
    }

    static llvm::Value* emit_expr(FnCG& cg, ast::Expr* e, Pass9_5Result& out)
    {
        if (!e)
            return nullptr;

        if (auto* ch = dynamic_cast<ast::CharLiteralExpr*>(e))
            return emit_char_from_pass7(cg, *ch, out);
        if (auto* i = dynamic_cast<ast::IntLiteralExpr*>(e))
            return emit_int_from_pass7(cg, *i, out);
        if (auto* f = dynamic_cast<ast::FloatLiteralExpr*>(e))
            return emit_float_from_pass7(cg, *f, out);
        if (auto* b = dynamic_cast<ast::BoolLiteralExpr*>(e))
            return llvm::ConstantInt::get(cg.st.i1_ty, b->v_ ? 1 : 0);

        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
            return emit_ref(cg, *r, out);
        if (auto* a = dynamic_cast<ast::AssignExpr*>(e))
            return emit_assign(cg, *a, out);
        if (auto* c = dynamic_cast<ast::CallExpr*>(e))
            return emit_call(cg, *c, out);
        if (auto* bi = dynamic_cast<ast::BinaryExpr*>(e))
            return emit_binary(cg, *bi, out);
        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
            return emit_unary(cg, *u, out);
        if (auto* st = dynamic_cast<ast::StructLiteralExpr*>(e))
            return emit_struct_lit(cg, *st, out);
        if (auto* fe = dynamic_cast<ast::FieldExpr*>(e))
            return emit_field(cg, *fe, out);
        if (auto* al = dynamic_cast<ast::ArrayLiteralExpr*>(e))
            return emit_array_literal(cg, *al, out);
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
            return emit_index_expr(cg, *ix, out);

        log_error(out, e->location_, "pass9.5: unsupported expression");
        return null_obj(cg.st);
    }

    // ============================================================
    // Place analysis: mutability + slot address (for & / &mut)
    // ============================================================

    static const LocalSlotInfo* find_slot_info_by_slot(const FnBindings& binds,
                                                       SlotId s)
    {
        for (const auto& si : binds.slots)
            if (si.slot.index == s.index)
                return &si;
        return nullptr;
    }

    static bool is_ref_mutable_type(const Pass5Result& p5, TypeId t)
    {
        if (t.value >= p5.types.nodes.size())
            return false;
        const TypeNode& n = p5.types.nodes[t.value];
        return (n.kind == TypeKind::Ref) && n.ref_mut;
    }

    static bool place_is_mutable(FnCG& cg, ast::Expr* e)
    {
        if (!e || !cg.binds)
            return false;

        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = cg.binds->ref_binding.find(r);
            if (it == cg.binds->ref_binding.end())
                return false;
            if (it->second.kind != BindingKind::LocalSlot)
                return false;

            const SlotId slot = it->second.slot;
            const LocalSlotInfo* si = find_slot_info_by_slot(*cg.binds, slot);
            return si && (si->mut_ == ast::Mutability::Mut);
        }

        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
        {
            if (u->op == ast::UnaryOp::deref)
            {
                TypeId innerT = expr_type_id_or_bad(cg.p7, u->expr_);
                return is_ref_mutable_type(cg.p5, innerT);
            }
        }

        if (auto* f = dynamic_cast<ast::FieldExpr*>(e))
            return place_is_mutable(cg, f->base_);
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
            return place_is_mutable(cg, ix->base_);

        return false;
    }

    static llvm::Value* emit_place_slot_addr(FnCG& cg, ast::Expr* e,
                                             Pass9_5Result& out)
    {
        if (!e || !cg.binds)
            return nullptr;

        // local slot -> alloca Obj* (Obj**)
        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = cg.binds->ref_binding.find(r);
            if (it == cg.binds->ref_binding.end())
                return nullptr;
            if (it->second.kind != BindingKind::LocalSlot)
                return nullptr;

            const SlotId slot = it->second.slot;
            if (slot.index >= cg.slot_alloca.size())
                return nullptr;
            return cg.slot_alloca[slot.index];
        }

        // field place -> runtime returns Obj** for the field cell
        if (auto* fe = dynamic_cast<ast::FieldExpr*>(e))
        {
            if (!cg.rt || !cg.rt->rt_struct_field_slot)
            {
                log_error(out, fe->location_,
                          "pass9.5: missing runtime intrinsic rt_struct_field_slot (needed "
                          "for &struct.field)");
                return nullptr;
            }

            llvm::Value* baseV = materialize_value_if_ref(cg, fe->base_, out);
            llvm::Value* baseObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, fe->base_)), baseV);

            DynTag dt = dyn_tag_of(cg.p8, fe->base_);
            if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
            {
                log_error(out, fe->location_,
                          "pass9.5: cannot take address of field on non-struct base");
                return nullptr;
            }

            auto idxOpt = try_field_index_from_pass5(cg.p5, *dt.struct_id, fe->field);
            if (!idxOpt.has_value())
            {
                log_error_ident(out, fe->location_, fe->field,
                                "pass9.5: unknown field name in address-of");
                return nullptr;
            }

            llvm::Value* idxV = llvm::ConstantInt::get(cg.st.i64_ty, *idxOpt);

            llvm::Type* objSlotPtrTy = llvm::PointerType::getUnqual(cg.st.obj_ptr_ty);
            llvm::FunctionType* FT = llvm::FunctionType::get(
                objSlotPtrTy, {cg.st.obj_ptr_ty, cg.st.i64_ty}, false);

            llvm::CallInst* call =
                call_runtime_erased(cg, cg.rt->rt_struct_field_slot, FT,
                                    {baseObj, idxV}, "struct.field.slot");
            cg.arc_release_value_if_obj(baseObj);
            return call;
        }

        // index place -> runtime returns Obj** for element cell
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
        {
            if (!cg.rt || !cg.rt->rt_box_elem_slot)
            {
                log_error(out, ix->location_,
                          "pass9.5: missing runtime intrinsic rt_box_elem_slot (needed for "
                          "&arr[i])");
                return nullptr;
            }

            llvm::Value* baseV = materialize_value_if_ref(cg, ix->base_, out);
            llvm::Value* baseObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ix->base_)), baseV);

            llvm::Value* idxV = emit_expr(cg, ix->index_, out);
            llvm::Value* idxObj =
                cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ix->index_)), idxV);

            llvm::Type* objSlotPtrTy = llvm::PointerType::getUnqual(cg.st.obj_ptr_ty);
            llvm::FunctionType* FT = llvm::FunctionType::get(
                objSlotPtrTy, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);

            llvm::CallInst* call = call_runtime_erased(
                cg, cg.rt->rt_box_elem_slot, FT, {baseObj, idxObj}, "box.elem.slot");
            cg.arc_release_value_if_obj(baseObj);
            cg.arc_release_value_if_obj(idxObj);
            return call;
        }

        return nullptr;
    }

    // ============================================================
    // Statement emission
    // ============================================================

    static void emit_block(FnCG& cg, ast::BlockStatement& b, Pass9_5Result& out)
    {
        cg.scope_slots.emplace_back(); // push

        for (auto* s : b.statements_)
        {
            if (!s)
                continue;
            if (cg.B.GetInsertBlock() && cg.B.GetInsertBlock()->getTerminator())
                break;
            emit_stmt(cg, s, out);
        }

        if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
            cg.arc_release_current_scope();

        cg.scope_slots.pop_back();
    }

    static std::optional<SlotId> find_slot_for_var(const FnBindings& binds,
                                                   const ast::VarStmt& v)
    {
        for (const auto& si : binds.slots)
            if (si.var_decl == &v)
                return si.slot;
        return std::nullopt;
    }

    static void emit_var(FnCG& cg, ast::VarStmt& v, Pass9_5Result& out)
    {
        if (!cg.binds)
            return;

        auto slot = find_slot_for_var(*cg.binds, v);
        if (!slot.has_value())
            return;

        llvm::Value* rhs = nullptr;
        if (v.init_)
            rhs = emit_expr(cg, v.init_, out);
        else
            rhs = null_obj(cg.st);

        llvm::Value* rhsObj =
            cg.box_if_needed(v.init_
                                 ? to_value_tag(dyn_tag_of(cg.p8, v.init_))
                                 : ValueTag::Obj,
                             rhs);

        if (slot->index < cg.slot_alloca.size() && cg.slot_alloca[slot->index])
        {
            if (!cg.scope_slots.empty())
                cg.scope_slots.back().push_back(*slot);

            cg.arc_store_slot(cg.slot_alloca[slot->index], rhsObj);
            cg.arc_release_value_if_obj(rhsObj);
        }
    }

    static void emit_return(FnCG& cg, ast::ReturnStatement& r, Pass9_5Result& out)
    {
        llvm::Type* RT = cg.F->getReturnType();

        // void return
        if (!r.expr_ || RT->isVoidTy())
        {
            if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
            {
                for (auto it = cg.scope_slots.rbegin(); it != cg.scope_slots.rend(); ++it)
                    cg.arc_release_slot_list(*it);
            }
            cg.B.CreateRetVoid();
            return;
        }

        llvm::Value* v = emit_expr(cg, r.expr_, out);
        llvm::Value* coerced =
            cg.coerce_to(RT, to_value_tag(dyn_tag_of(cg.p8, r.expr_)), v);
        if (!coerced)
            coerced = llvm::UndefValue::get(RT);

        if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
        {
            for (auto it = cg.scope_slots.rbegin(); it != cg.scope_slots.rend(); ++it)
                cg.arc_release_slot_list(*it);
        }

        cg.B.CreateRet(coerced);
    }

    static void emit_if(FnCG& cg, ast::IfStatement& i, Pass9_5Result& out)
    {
        llvm::Function* F = cg.F;

        llvm::Value* cndB =
            force_i1_condition(cg, i.condition_, i.location_, out, "if.cond");

        llvm::BasicBlock* thenBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "if.then", F);
        llvm::BasicBlock* elseBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "if.else", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "if.end", F);

        cg.B.CreateCondBr(cndB, thenBB, elseBB);

        cg.B.SetInsertPoint(thenBB);
        if (i.thenBody_)
            emit_block(cg, *i.thenBody_, out);
        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(endBB);

        cg.B.SetInsertPoint(elseBB);
        llvm::BasicBlock* curElse = elseBB;

        for (auto* eif : i.elseIfs_)
        {
            if (!eif)
                continue;

            llvm::BasicBlock* eifThen =
                llvm::BasicBlock::Create(*cg.st.llctx, "elseif.then", F);
            llvm::BasicBlock* eifNext =
                llvm::BasicBlock::Create(*cg.st.llctx, "elseif.next", F);

            cg.B.SetInsertPoint(curElse);

            llvm::Value* eb =
                force_i1_condition(cg, eif->condition_, eif->location_, out,
                                   "elseif.cond");
            cg.B.CreateCondBr(eb, eifThen, eifNext);

            cg.B.SetInsertPoint(eifThen);
            if (eif->then_)
                emit_block(cg, *eif->then_, out);
            if (!cg.B.GetInsertBlock()->getTerminator())
                cg.B.CreateBr(endBB);

            curElse = eifNext;
        }

        cg.B.SetInsertPoint(curElse);
        if (i.else_ && i.else_->then_)
            emit_block(cg, *i.else_->then_, out);
        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(endBB);

        cg.B.SetInsertPoint(endBB);
    }

    static void emit_while(FnCG& cg, ast::WhileStatement& w, Pass9_5Result& out)
    {
        llvm::Function* F = cg.F;

        llvm::BasicBlock* condBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "while.cond", F);
        llvm::BasicBlock* bodyBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "while.body", F);
        llvm::BasicBlock* endBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "while.end", F);

        cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(condBB);
        llvm::Value* cndB =
            force_i1_condition(cg, w.condition_, w.location_, out, "while.cond");
        cg.B.CreateCondBr(cndB, bodyBB, endBB);

        cg.B.SetInsertPoint(bodyBB);
        {
            FnCG::LoopCtx lc;
            lc.breakBB = endBB;
            lc.continueBB = condBB;
            lc.scope_depth = cg.scope_slots.size();
            cg.loop_stack.push_back(lc);

            if (w.body_)
                emit_block(cg, *w.body_, out);

            cg.loop_stack.pop_back();
        }

        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(endBB);
    }

    static void emit_do_while(FnCG& cg, ast::DoWhileStatement& d,
                              Pass9_5Result& out)
    {
        llvm::Function* F = cg.F;

        llvm::BasicBlock* bodyBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "do.body", F);
        llvm::BasicBlock* condBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "do.cond", F);
        llvm::BasicBlock* endBB =
            llvm::BasicBlock::Create(*cg.st.llctx, "do.end", F);

        cg.B.CreateBr(bodyBB);

        cg.B.SetInsertPoint(bodyBB);
        {
            FnCG::LoopCtx lc;
            lc.breakBB = endBB;
            lc.continueBB = condBB;
            lc.scope_depth = cg.scope_slots.size();
            cg.loop_stack.push_back(lc);

            if (d.body_)
                emit_block(cg, *d.body_, out);

            cg.loop_stack.pop_back();
        }

        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(condBB);
        llvm::Value* cndB =
            force_i1_condition(cg, d.condition_, d.location_, out, "do.cond");
        cg.B.CreateCondBr(cndB, bodyBB, endBB);

        cg.B.SetInsertPoint(endBB);
    }

    static void emit_break(FnCG& cg, ast::BreakStatement& b, Pass9_5Result& out)
    {
        if (!cg.B.GetInsertBlock() || cg.B.GetInsertBlock()->getTerminator())
            return;

        if (cg.loop_stack.empty() || !cg.loop_stack.back().breakBB)
        {
            log_error(out, b.location_, "pass9.5: break used outside of a loop");
            return;
        }

        const auto& L = cg.loop_stack.back();
        release_scopes_for_jump(cg, L.scope_depth);
        cg.B.CreateBr(L.breakBB);
    }

    static void emit_continue(FnCG& cg, ast::ContinueStatement& c,
                              Pass9_5Result& out)
    {
        if (!cg.B.GetInsertBlock() || cg.B.GetInsertBlock()->getTerminator())
            return;

        if (cg.loop_stack.empty() || !cg.loop_stack.back().continueBB)
        {
            log_error(out, c.location_, "pass9.5: continue used outside of a loop");
            return;
        }

        const auto& L = cg.loop_stack.back();
        release_scopes_for_jump(cg, L.scope_depth);
        cg.B.CreateBr(L.continueBB);
    }

    static void emit_stmt(FnCG& cg, ast::Statement* s, Pass9_5Result& out)
    {
        if (!s)
            return;

        if (auto* b = dynamic_cast<ast::BlockStatement*>(s))
        {
            emit_block(cg, *b, out);
            return;
        }
        if (auto* v = dynamic_cast<ast::VarStmt*>(s))
        {
            emit_var(cg, *v, out);
            return;
        }
        if (auto* r = dynamic_cast<ast::ReturnStatement*>(s))
        {
            emit_return(cg, *r, out);
            return;
        }
        if (auto* i = dynamic_cast<ast::IfStatement*>(s))
        {
            emit_if(cg, *i, out);
            return;
        }
        if (auto* w = dynamic_cast<ast::WhileStatement*>(s))
        {
            emit_while(cg, *w, out);
            return;
        }
        if (auto* d = dynamic_cast<ast::DoWhileStatement*>(s))
        {
            emit_do_while(cg, *d, out);
            return;
        }
        if (auto* e = dynamic_cast<ast::ExprStatement*>(s))
        {
            llvm::Value* v = emit_expr(cg, e->expr_, out);
            cg.arc_release_value_if_obj(v);
            return;
        }
        if (auto* br = dynamic_cast<ast::BreakStatement*>(s))
        {
            emit_break(cg, *br, out);
            return;
        }
        if (auto* ct = dynamic_cast<ast::ContinueStatement*>(s))
        {
            emit_continue(cg, *ct, out);
            return;
        }

        log_error(out, s->location_, "pass9.5: unsupported statement");
    }

    // ============================================================
    // Prologue: entry block + alloc slots + store params
    // ============================================================

    static void clear_function_body(llvm::Function* F)
    {
        if (!F)
            return;
        for (auto& BB : *F)
            BB.dropAllReferences();
        while (!F->empty())
            F->begin()->eraseFromParent();
    }

    static void build_prologue(FnCG& cg)
    {
        llvm::BasicBlock* entry =
            llvm::BasicBlock::Create(*cg.st.llctx, "entry", cg.F);
        cg.B.SetInsertPoint(entry);

        const uint32_t nSlots = cg.binds ? cg.binds->slot_count : 0;
        cg.slot_alloca.assign(nSlots, nullptr);

        for (uint32_t i = 0; i < nSlots; ++i)
        {
            cg.slot_alloca[i] = cg.B.CreateAlloca(cg.st.obj_ptr_ty, nullptr, "slot");
            cg.B.CreateStore(null_obj(cg.st), cg.slot_alloca[i]);
        }

        cg.scope_slots.clear();
        cg.scope_slots.push_back({}); // function scope

        if (!cg.binds)
            return;

        // Store parameters into their bound slots using ARC store barriers.
        unsigned argIndex = 0;
        for (auto& arg : cg.F->args())
        {
            if (argIndex >= cg.binds->slots.size())
                break;

            const LocalSlotInfo& si = cg.binds->slots[argIndex];
            ++argIndex;

            if (!si.param_decl)
                continue;

            llvm::Value* stored = nullptr;

            if (arg.getType() == cg.st.obj_ptr_ty)
            {
                stored = &arg;
            }
            else if (arg.getType() == cg.st.i1_ty)
            {
                if (cg.rt && cg.rt->rt_box_bool)
                    stored = cg.B.CreateCall(cg.rt->rt_box_bool, {&arg}, "box.param.bool");
                else
                    stored = null_obj(cg.st);
            }
            else
            {
                stored = null_obj(cg.st);
            }

            if (si.slot.index < cg.slot_alloca.size() &&
                cg.slot_alloca[si.slot.index])
            {
                cg.scope_slots.back().push_back(si.slot);
                cg.arc_store_slot(cg.slot_alloca[si.slot.index], stored);
            }
        }
    }

    // ============================================================
    // Main driver
    // ============================================================

    Pass9_5Result
    run_pass9_5_emit_bodies(Pass9_1Result& st, const Translation& tr,
                            const Pass4Result& p4, const Pass4_5Result& p45,
                            const Pass5Result& p5, const Pass6Result& p6,
                            const Pass7Result& p7, const Pass8Result& p8,
                            const Pass9_1RuntimeDecls& rt)
    {
        (void)tr;
        (void)p4;
        (void)p45;

        Pass9_5Result out{};

        const auto n_units = static_cast<uint32_t>(p6.modules.size());

        for (uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            const ModuleBindings& mb = p6.modules[unit_i];

            // Required: every error cluster begins with module path.
            // We set module scope per-module so all nested log_error(...) calls
            // emit LogPath{SymKind::Ident, mod->pathExpr_->path_, loc} first.
            ScopedModuleLog mod_scope(try_get_module_path(mb, st));

            for (const auto& [fnid, binds] : mb.fns)
            {
                auto itF = st.fn_decls.find(fnid);
                if (itF == st.fn_decls.end() || !itF->second)
                {
                    log_error(out, binds.decl ? binds.decl->location_ : lex::Loc{},
                              "pass9.5: function missing in IR (did you run pass9.3?)");
                    continue;
                }

                llvm::Function* F = itF->second;

                if (!binds.decl || !binds.decl->body_)
                {
                    log_error(out, binds.decl ? binds.decl->location_ : lex::Loc{},
                              "pass9.5: missing function body for codegen");
                    continue;
                }

                clear_function_body(F);

                FnCG cg(st, p5, p6, p7, p8, F, rt);
                cg.binds = &binds;

                build_prologue(cg);

                emit_block(cg, *binds.decl->body_, out);

                // Function fallthrough cleanup (if reachable)
                if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
                {
                    while (!cg.scope_slots.empty())
                    {
                        cg.arc_release_slot_list(cg.scope_slots.back());
                        cg.scope_slots.pop_back();
                    }
                }

                // Ensure terminator
                if (!cg.B.GetInsertBlock()->getTerminator())
                {
                    const llvm::Type* RT = F->getReturnType();
                    if (RT->isVoidTy())
                        cg.B.CreateRetVoid();
                    else if (RT == st.i1_ty)
                        cg.B.CreateRet(llvm::ConstantInt::getFalse(*st.llctx));
                    else
                        cg.B.CreateRet(null_obj(st));
                }
            }
        }

        return out;
    }
} // namespace sema
