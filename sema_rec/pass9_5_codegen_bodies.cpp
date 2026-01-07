// sema/pass9_5_codegen_bodies.cpp
#include "pass9_5_codegen_bodies.hpp"

#include <optional>
#include <type_traits>
#include <unordered_set>
#include <variant>
#include <vector>

#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/Casting.h>

// Statements
#include "stmt/block_statement.hpp"
#include "stmt/var_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/while_statement.hpp"
#include "stmt/do_while_statement.hpp"

// Exprs
#include "expr/int_literal_expr.hpp"
#include "expr/float_literal_expr.hpp"
#include "expr/bool_literal_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/assign_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/unary_op_expr.hpp"

// Struct literals
#include "expr/struct_literal_expr.hpp"
#include "expr/field_init_expr.hpp"

namespace sema
{
    // ============================================================
    // Diagnostics
    // ============================================================

    static void push_diag(Pass9_5Result& out,
                          Pass9_5Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        out.diagnostics.push_back(Pass9_5Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    // ============================================================
    // Tags (Pass8 DynTag -> Pass9.5 ABI ValueTag)
    // ============================================================

    static sema::DynTag dyn_tag_of(const Pass8Result& p8, const ast::Expr* e)
    {
        if (!e) return sema::DynTag::void_();

        auto it = p8.tag_of.find(e);
        if (it == p8.tag_of.end())
            return sema::DynTag::obj(); // safe default

        return it->second;
    }

    static ValueTag to_value_tag(const sema::DynTag& t)
    {
        switch (t.kind)
        {
        case sema::DynTagKind::Void: return ValueTag::Void;
        case sema::DynTagKind::Bool: return ValueTag::Bool;
        case sema::DynTagKind::Obj:
        case sema::DynTagKind::StructObj:
        default: return ValueTag::Obj;
        }
    }


    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
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

        const FnBindings* binds = nullptr;

        llvm::Function* F = nullptr;
        llvm::IRBuilder<> B;

        const Pass9_1RuntimeDecls* rt = nullptr;
        std::vector<std::vector<SlotId>> scope_slots;


        // slot allocas: slot.index -> alloca (always Obj* storage)
        std::vector<llvm::AllocaInst*> slot_alloca;

        FnCG(Pass9_1Result& st_,
             const Pass5Result& p5_,
             const Pass6Result& p6_,
             const Pass7Result& p7_,
             const Pass8Result& p8_,
             llvm::Function* F_,
             const Pass9_1RuntimeDecls& rt_)
            : st(st_), p5(p5_), p6(p6_), p7(p7_), p8(p8_), F(F_), B(*st_.llctx), rt(&rt_)
        {
        }

        llvm::Value* box_if_needed(ValueTag tag, llvm::Value* v)
        {
            if (!v)
                return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(st.obj_ptr_ty));

            if (tag != ValueTag::Bool)
                return v; // already Obj*

            // Bool needs boxing if it is i1
            if (v->getType() == st.obj_ptr_ty)
                return v;

            if (v->getType() == st.i1_ty)
            {
                if (!rt || !rt->rt_box_bool)
                    return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
                return B.CreateCall(rt->rt_box_bool, {v}, "box.bool");
            }

            return llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(st.obj_ptr_ty));
        }

        void arc_release_value_if_obj(llvm::Value* v)
        {
            if (!v) return;
            if (v->getType() != st.obj_ptr_ty) return;

            // Avoid calling release on constant nulls.
            if (llvm::isa<llvm::ConstantPointerNull>(v)) return;

            if (rt && rt->rt_release)
                B.CreateCall(rt->rt_release, {v});
        }

        void arc_store_slot(llvm::AllocaInst* slot, llvm::Value* newObj)
        {
            llvm::Value* oldObj = B.CreateLoad(st.obj_ptr_ty, slot, "arc.old");

            if (rt && rt->rt_retain && newObj && !llvm::isa<llvm::ConstantPointerNull>(newObj))
                B.CreateCall(rt->rt_retain, {newObj});

            B.CreateStore(newObj, slot);

            if (rt && rt->rt_release && oldObj && !llvm::isa<llvm::ConstantPointerNull>(oldObj))
                B.CreateCall(rt->rt_release, {oldObj});
        }

        void arc_release_scope(FnCG& cg)
        {
            if (cg.scope_slots.empty()) return;
            auto& v = cg.scope_slots.back();
            for (auto it = v.rbegin(); it != v.rend(); ++it)
            {
                SlotId s = *it;
                llvm::AllocaInst* a = cg.slot_alloca[s.index];
                llvm::Value* oldObj = cg.B.CreateLoad(cg.st.obj_ptr_ty, a);
                cg.B.CreateStore(null_obj(cg.st), a);
                if (cg.rt && cg.rt->rt_release)
                    cg.B.CreateCall(cg.rt->rt_release, {oldObj});
            }
        }

        void arc_release_slot_list(const std::vector<SlotId>& v)
        {
            for (auto it = v.rbegin(); it != v.rend(); ++it)
            {
                SlotId s = *it;
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
            if (scope_slots.empty()) return;
            arc_release_slot_list(scope_slots.back());
        }

        llvm::Value* unbox_if_needed(ValueTag tag, llvm::Value* v)
        {
            if (!v)
                return llvm::ConstantInt::getFalse(*st.llctx);

            if (tag != ValueTag::Bool)
                return v; // caller expects Obj* or other; do not touch

            // Bool expected:
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
                if (dstTy == st.obj_ptr_ty) return null_obj(st);
                if (dstTy == st.i1_ty) return llvm::ConstantInt::getFalse(*st.llctx);
                return nullptr;
            }

            if (dstTy == st.obj_ptr_ty)
                return box_if_needed(srcTag, v);

            if (dstTy == st.i1_ty)
                return unbox_if_needed(srcTag, v);

            // void destination: just drop
            return nullptr;
        }
    };

    // ============================================================
    // Forward decls: stmt/expr emission
    // ============================================================

    static llvm::Value* emit_expr(FnCG& cg, ast::Expr* e, Pass9_5Result& out);
    static void emit_stmt(FnCG& cg, ast::Statement* s, Pass9_5Result& out);
    static llvm::Value* emit_place_slot_addr(FnCG& cg, ast::Expr* e, Pass9_5Result& out);
    static bool place_is_mutable(FnCG& cg, ast::Expr* e);

    // ============================================================
    // Reserved runtime calls (Box<T>, Str, print<T>, etc.)
    // ============================================================

    static TypeId expr_type_id_or_bad(const Pass7Result& p7, const ast::Expr* e)
    {
        if (!e) return TypeId{UINT32_MAX};
        auto it = p7.expr_type.find(e);
        if (it == p7.expr_type.end()) return TypeId{UINT32_MAX};
        return it->second;
    }

    static bool is_valid_typeid(const Pass5Result& p5, TypeId t)
    {
        return t.value < p5.types.nodes.size();
    }

    static bool is_ref_type(const Pass5Result& p5, TypeId t, TypeId* out_pointee = nullptr)
    {
        if (!is_valid_typeid(p5, t)) return false;
        const TypeNode& n = p5.types.nodes[t.value];
        if (n.kind != TypeKind::Ref) return false;
        if (out_pointee) *out_pointee = n.inner;
        return true;
    }

    static std::optional<TypeId> try_box_elem_type_from_call(const FnCG& cg, const ast::CallExpr& c)
    {
        // We infer T from the *return type* of the call: Box<T>
        TypeId retT = expr_type_id_or_bad(cg.p7, &c);
        if (!is_valid_typeid(cg.p5, retT)) return std::nullopt;

        const TypeNode& n = cg.p5.types.nodes[retT.value];
        if (n.kind != TypeKind::Box) return std::nullopt;

        return n.inner; // T
    }

    enum class RtBoxElemKind : uint64_t
    {
        ObjPtr = 0, // store Obj* elements (your current behavior)
        I32 = 1,
        I64 = 2,
        F64 = 3,
        Bool = 4,
        // Extend as needed (Struct-by-value etc.)
    };

    static void infer_box_elem_layout(const FnCG& cg,
                                      TypeId elemT,
                                      RtBoxElemKind& outKind,
                                      uint64_t& outSize,
                                      uint64_t& outAlign)
    {
        // Default: Obj* elements
        outKind = RtBoxElemKind::ObjPtr;
        outSize = 8; // will be overwritten below for known targets
        outAlign = 8;

        if (!is_valid_typeid(cg.p5, elemT))
            return;

        const TypeNode& tn = cg.p5.types.nodes[elemT.value];

        // You can refine this mapping to your language builtins.
        if (tn.kind == TypeKind::Builtin)
        {
            switch (tn.builtin)
            {
            case BuiltinType::Bool:
                outKind = RtBoxElemKind::Bool;
                outSize = 1;
                outAlign = 1;
                return;

            // If you have i32/i64 as separate builtins, map them here
            case BuiltinType::I32:
                outKind = RtBoxElemKind::I32;
                outSize = 4;
                outAlign = 4;
                return;

            case BuiltinType::I64:
                outKind = RtBoxElemKind::I64;
                outSize = 8;
                outAlign = 8;
                return;

            case BuiltinType::F64:
                outKind = RtBoxElemKind::F64;
                outSize = 8;
                outAlign = 8;
                return;

            default:
                break;
            }
        }

        // For now, keep everything else as ObjPtr until you implement true by-value struct layout.
        outKind = RtBoxElemKind::ObjPtr;
        outSize = 8;
        outAlign = 8;
    }

    // Load through rt_ref_load if the static type is &T / &mut T.
    // This lets reserved APIs declared as taking &Box<T> / &T accept arguments like &mut x.
    static llvm::Value* materialize_value_if_ref(FnCG& cg, ast::Expr* e, Pass9_5Result& out)
    {
        llvm::Value* v = emit_expr(cg, e, out);
        if (!v) return null_obj(cg.st);

        TypeId t = expr_type_id_or_bad(cg.p7, e);
        TypeId pointee{UINT32_MAX};

        if (is_ref_type(cg.p5, t, &pointee))
        {
            // v is a runtime "ref object" (Obj*). Load the underlying value.
            if (!cg.rt || !cg.rt->rt_ref_load)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, e ? e->location_ : lex::Loc{},
                          "reserved call needs rt_ref_load but runtime does not provide it");
                return null_obj(cg.st);
            }

            llvm::FunctionType* wantFT =
                llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);

            llvm::Value* callee = cg.rt->rt_ref_load;
            if (cg.rt->rt_ref_load->getFunctionType() != wantFT)
                callee = cg.B.CreateBitCast(cg.rt->rt_ref_load, wantFT->getPointerTo(), "rt_ref_load.cast");

            llvm::Value* refObj = cg.box_if_needed(ValueTag::Obj, v);
            llvm::CallInst* loaded = cg.B.CreateCall(wantFT, callee, {refObj}, "ref.load.for.reserved");
            cg.arc_release_value_if_obj(refObj);
            return loaded;
        }

        return v;
    }

    // Create a call to a runtime function, but tolerate signature mismatches by bitcasting
    // the callee to the expected function type before calling.
    static llvm::CallInst* call_runtime_erased(FnCG& cg,
                                               llvm::Function* calleeFn,
                                               llvm::FunctionType* expectedFT,
                                               llvm::ArrayRef<llvm::Value*> args,
                                               llvm::StringRef dbgName)
    {
        if (!calleeFn)
            return nullptr;

        llvm::Value* callee = calleeFn;

        if (calleeFn->getFunctionType() != expectedFT)
        {
            callee = cg.B.CreateBitCast(
                calleeFn,
                expectedFT->getPointerTo(),
                (dbgName + ".cast").str()
            );
        }

        // IMPORTANT: you cannot name a void-typed instruction in LLVM IR.
        if (expectedFT->getReturnType()->isVoidTy())
            return cg.B.CreateCall(expectedFT, callee, args);

        return cg.B.CreateCall(expectedFT, callee, args, dbgName);
    }

    static bool is_reserved_runtime_name(llvm::StringRef n)
    {
        return n == "box_new" ||
            n == "box_free" ||
            n == "box_len" ||
            n == "box_get" ||
            n == "box_set" ||
            n == "print";
    }

    // Emit reserved call and return (handled=true) if matched.
    // Returns nullptr for void-return reserved calls.
    static llvm::Value* emit_reserved_call(FnCG& cg,
                                           llvm::StringRef calleeName,
                                           ast::CallExpr& c,
                                           Pass9_5Result& out,
                                           bool& handled)
    {
        handled = true;

        // print<T>(t: &T) -> void
        if (calleeName == "print")
        {
            if (c.args_.size() != 1)
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "print: wrong number of args (expected 1)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->rt_print)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, c.location_,
                          "missing runtime intrinsic rt_print");
                return nullptr;
            }

            llvm::Value* v = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag tag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* obj = cg.box_if_needed(tag, v);

            llvm::FunctionType* FT = llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);
            (void)call_runtime_erased(cg, cg.rt->rt_print, FT, {obj}, "rt_print");
            cg.arc_release_value_if_obj(obj);
            return nullptr;
        }

        // Box APIs: use type-erased ABI:
        // box_new  : Obj* box_new(Obj* count)
        // box_free : void box_free(Obj* box)
        // box_len  : Obj* box_len(Obj* box)
        // box_get  : Obj* box_get(Obj* box, Obj* i)
        // box_set  : void box_set(Obj* box, Obj* i, Obj* v)

        if (calleeName == "box_new")
        {
            if (c.args_.size() != 1)
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "box_new: wrong number of args (expected 1)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_new)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, c.location_,
                          "missing runtime intrinsic box_new");
                return null_obj(cg.st);
            }

            // len argument (still Obj*)
            llvm::Value* cntV = emit_expr(cg, c.args_[0], out);
            ValueTag cntTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* cntObj = cg.box_if_needed(cntTag, cntV);

            // Infer element layout from return type Box<T>
            RtBoxElemKind kind = RtBoxElemKind::ObjPtr;
            uint64_t elemSize = 8;
            uint64_t elemAlign = 8;

            if (auto elemT = try_box_elem_type_from_call(cg, c))
                infer_box_elem_layout(cg, *elemT, kind, elemSize, elemAlign);

            llvm::Value* kindV = llvm::ConstantInt::get(cg.st.i64_ty, static_cast<uint64_t>(kind), /*isSigned=*/false);
            llvm::Value* sizeV = llvm::ConstantInt::get(cg.st.i64_ty, elemSize, /*isSigned=*/false);
            llvm::Value* alignV = llvm::ConstantInt::get(cg.st.i64_ty, elemAlign, /*isSigned=*/false);

            // NEW ABI:
            // Obj* box_new(Obj* count, i64 elem_kind, i64 elem_size, i64 elem_align)
            llvm::FunctionType* FT =
                llvm::FunctionType::get(cg.st.obj_ptr_ty,
                                        {cg.st.obj_ptr_ty, cg.st.i64_ty, cg.st.i64_ty, cg.st.i64_ty},
                                        false);

            llvm::CallInst* call = call_runtime_erased(cg, cg.rt->box_new, FT,
                                                       {cntObj, kindV, sizeV, alignV},
                                                       "box_new");

            cg.arc_release_value_if_obj(cntObj);
            return call ? (llvm::Value*)call : null_obj(cg.st);
        }

        if (calleeName == "box_free")
        {
            if (c.args_.size() != 1)
            {
                /* diag */
                return nullptr;
            }
            if (!cg.rt || !cg.rt->box_free || !cg.rt->rt_ref_load || !cg.rt->rt_ref_store)
            {
                /* diag */
                return nullptr;
            }

            ast::Expr* ae = c.args_[0];

            llvm::Value* argV = emit_expr(cg, ae, out);
            llvm::Value* argObj = cg.box_if_needed(to_value_tag(dyn_tag_of(cg.p8, ae)), argV);

            TypeId t = expr_type_id_or_bad(cg.p7, ae);

            // If it's a ref, load, free, then clear the slot.
            TypeId pointee{UINT32_MAX};
            if (is_ref_type(cg.p5, t, &pointee))
            {
                // load underlying box from ref
                llvm::FunctionType* loadFT =
                    llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);
                llvm::CallInst* loaded = call_runtime_erased(cg, cg.rt->rt_ref_load, loadFT, {argObj},
                                                             "ref.load.for.box_free");

                // free loaded box
                llvm::FunctionType* freeFT =
                    llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);
                (void)call_runtime_erased(cg, cg.rt->box_free, freeFT, {loaded}, "box_free.ref");

                // clear the slot
                llvm::FunctionType* storeFT =
                    llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);
                (void)call_runtime_erased(cg, cg.rt->rt_ref_store, storeFT, {argObj, null_obj(cg.st)},
                                          "ref.store.null");

                // release temps
                cg.arc_release_value_if_obj(loaded);
                cg.arc_release_value_if_obj(argObj);
                return nullptr;
            }

            // Non-ref argument: free directly.
            llvm::FunctionType* freeFT =
                llvm::FunctionType::get(cg.st.void_ty, {cg.st.obj_ptr_ty}, false);
            (void)call_runtime_erased(cg, cg.rt->box_free, freeFT, {argObj}, "box_free");
            cg.arc_release_value_if_obj(argObj);
            return nullptr;
        }

        if (calleeName == "box_len")
        {
            if (c.args_.size() != 1)
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "box_len: wrong number of args (expected 1)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_len)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, c.location_,
                          "missing runtime intrinsic box_len");
                return null_obj(cg.st);
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag boxTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* boxObj = cg.box_if_needed(boxTag, boxV);

            llvm::FunctionType* FT = llvm::FunctionType::get(cg.st.obj_ptr_ty, {cg.st.obj_ptr_ty}, false);
            llvm::CallInst* call = call_runtime_erased(cg, cg.rt->box_len, FT, {boxObj}, "box_len");
            cg.arc_release_value_if_obj(boxObj);
            return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
        }

        if (calleeName == "box_get")
        {
            if (c.args_.size() != 2)
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "box_get: wrong number of args (expected 2)");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->box_get)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, c.location_,
                          "missing runtime intrinsic box_get");
                return null_obj(cg.st);
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag boxTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* boxObj = cg.box_if_needed(boxTag, boxV);

            llvm::Value* idxV = emit_expr(cg, c.args_[1], out);
            ValueTag idxTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[1]));
            llvm::Value* idxObj = cg.box_if_needed(idxTag, idxV);

            llvm::FunctionType* FT = llvm::FunctionType::get(cg.st.obj_ptr_ty,
                                                             {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
                                                             false);

            llvm::CallInst* call = call_runtime_erased(cg, cg.rt->box_get, FT, {boxObj, idxObj}, "box_get");
            if (!call) return null_obj(cg.st);

            // Coerce return based on tag (mainly for Bool return specialization)
            ValueTag retTag = to_value_tag(dyn_tag_of(cg.p8, &c));
            if (retTag == ValueTag::Bool)
            {
                if (!cg.rt || !cg.rt->rt_unbox_bool)
                    return llvm::ConstantInt::getFalse(*cg.st.llctx);

                llvm::FunctionType* unFT =
                    llvm::FunctionType::get(cg.st.i1_ty, {cg.st.obj_ptr_ty}, false);

                llvm::Value* unCallee = cg.rt->rt_unbox_bool;
                if (cg.rt->rt_unbox_bool->getFunctionType() != unFT)
                    unCallee = cg.B.CreateBitCast(cg.rt->rt_unbox_bool, unFT->getPointerTo(), "rt_unbox_bool.cast");

                llvm::Value* b = cg.B.CreateCall(unFT, unCallee, {call}, "unbox.box_get");
                cg.arc_release_value_if_obj(call);
                cg.arc_release_value_if_obj(boxObj);
                cg.arc_release_value_if_obj(idxObj);
                return b;
            }

            cg.arc_release_value_if_obj(boxObj);
            cg.arc_release_value_if_obj(idxObj);
            return call;
        }

        if (calleeName == "box_set")
        {
            if (c.args_.size() != 3)
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "box_set: wrong number of args (expected 3)");
                return nullptr;
            }

            if (!cg.rt || !cg.rt->box_set)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, c.location_,
                          "missing runtime intrinsic box_set");
                return nullptr;
            }

            llvm::Value* boxV = materialize_value_if_ref(cg, c.args_[0], out);
            ValueTag boxTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[0]));
            llvm::Value* boxObj = cg.box_if_needed(boxTag, boxV);

            llvm::Value* idxV = emit_expr(cg, c.args_[1], out);
            ValueTag idxTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[1]));
            llvm::Value* idxObj = cg.box_if_needed(idxTag, idxV);

            llvm::Value* valV = emit_expr(cg, c.args_[2], out);
            ValueTag valTag = to_value_tag(dyn_tag_of(cg.p8, c.args_[2]));
            llvm::Value* valObj = cg.box_if_needed(valTag, valV);

            llvm::FunctionType* FT = llvm::FunctionType::get(cg.st.void_ty,
                                                             {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
                                                             false);

            (void)call_runtime_erased(cg, cg.rt->box_set, FT, {boxObj, idxObj, valObj}, "box_set");
            cg.arc_release_value_if_obj(boxObj);
            cg.arc_release_value_if_obj(idxObj);
            cg.arc_release_value_if_obj(valObj);
            return nullptr;
        }

        // Not reserved after all
        handled = false;
        return nullptr;
    }

    // ============================================================
    // Force condition to i1 (robust against missing/mis-tagging)
    // ============================================================

    static llvm::Value* force_i1_condition(FnCG& cg,
                                           ast::Expr* cond,
                                           const lex::Loc& loc,
                                           Pass9_5Result& out,
                                           llvm::StringRef dbgName = "cond")
    {
        llvm::Value* v = emit_expr(cg, cond, out);
        ValueTag tag = to_value_tag(dyn_tag_of(cg.p8, cond));

        // First pass: use normal coercion rules.
        llvm::Value* b = cg.coerce_to(cg.st.i1_ty, tag, v);
        if (!b)
            b = llvm::ConstantInt::getFalse(*cg.st.llctx);

        // If tags were wrong, b might still be Obj*. For control flow, try unboxing anyway.
        if (b->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
            {
                b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {b}, (dbgName + ".unbox").str());
            }
            else
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, loc,
                          "missing runtime intrinsic rt_unbox_bool required for condition");
                b = llvm::ConstantInt::getFalse(*cg.st.llctx);
            }
        }

        if (b->getType() != cg.st.i1_ty)
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, loc,
                      "internal: condition did not lower to i1");
            b = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (v && v->getType() == cg.st.obj_ptr_ty)
        {
            // If b is still an Obj*, we'll release it below after unboxing.
            if (!(b && b->getType() == cg.st.obj_ptr_ty && b == v))
                cg.arc_release_value_if_obj(v);
        }

        // If coercion returned an Obj* (wrong tag), and we unboxed from it above,
        // ensure it is released.
        if (b && b->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(b);

        return b;
    }

    // ============================================================
    // Literal emission (Pass7 data -> boxed Obj*)
    // ============================================================

    static llvm::Value* emit_int_from_pass7(FnCG& cg,
                                            const ast::IntLiteralExpr& lit,
                                            Pass9_5Result& out)
    {
        auto it = cg.p7.int_id.find(&lit);
        if (it == cg.p7.int_id.end() || it->second >= cg.p7.ints.size())
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, lit.location_,
                      "IntLiteralExpr has no Pass7 lowered entry");
            return null_obj(cg.st);
        }

        const auto& v = cg.p7.ints[it->second];

        llvm::Type* i128 = llvm::Type::getInt128Ty(*cg.st.llctx);

        llvm::Value* boxed = nullptr;

        std::visit([&]<typename T0>(T0 vv)
        {
            using T = T0;

            if constexpr (std::is_same_v<T, std::int8_t> ||
                std::is_same_v<T, std::int16_t> ||
                std::is_same_v<T, std::int32_t> ||
                std::is_same_v<T, std::int64_t>)
            {
                llvm::Value* imm = llvm::ConstantInt::get(cg.st.i64_ty,
                                                          static_cast<std::int64_t>(vv),
                                                          /*isSigned=*/true);
                boxed = cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, "int.i64");
            }
            else if constexpr (std::is_same_v<T, std::uint8_t> ||
                std::is_same_v<T, std::uint16_t> ||
                std::is_same_v<T, std::uint32_t> ||
                std::is_same_v<T, std::uint64_t>)
            {
                llvm::Value* imm = llvm::ConstantInt::get(cg.st.i64_ty,
                                                          static_cast<std::uint64_t>(vv),
                                                          /*isSigned=*/false);

                if (cg.rt && cg.rt->rt_int_from_u64)
                    boxed = cg.B.CreateCall(cg.rt->rt_int_from_u64, {imm}, "int.u64");
                else
                    boxed = cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, "int.u64"); // fallback
            }

#if defined(__SIZEOF_INT128__)
            else if constexpr (std::is_same_v<T, unsigned __int128>)
            {
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
        }, v);

        return boxed ? boxed : null_obj(cg.st);
    }

    static llvm::Value* emit_float_from_pass7(FnCG& cg,
                                              const ast::FloatLiteralExpr& lit,
                                              Pass9_5Result& out)
    {
        auto it = cg.p7.float_id.find(&lit);
        if (it == cg.p7.float_id.end() || it->second >= cg.p7.floats.size())
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, lit.location_,
                      "FloatLiteralExpr has no Pass7 lowered entry");
            return null_obj(cg.st);
        }

        const auto& v = cg.p7.floats[it->second];

        llvm::Value* boxed = nullptr;

        std::visit([&]<typename T0>(T0 vv)
        {
            using T = T0;

            if constexpr (std::is_same_v<T, float>)
            {
                llvm::Type* f32_ty = llvm::Type::getFloatTy(*cg.st.llctx);
                llvm::Value* imm = llvm::ConstantFP::get(f32_ty, static_cast<double>(vv));
                boxed = cg.B.CreateCall(cg.rt->rt_float_from_f32, {imm}, "f32");
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                llvm::Type* f64_ty = llvm::Type::getDoubleTy(*cg.st.llctx);
                llvm::Value* imm = llvm::ConstantFP::get(f64_ty, vv);
                boxed = cg.B.CreateCall(cg.rt->rt_float_from_f64, {imm}, "f64");
            }
            else
            {
                boxed = null_obj(cg.st);
            }
        }, v);

        return boxed ? boxed : null_obj(cg.st);
    }

    // ============================================================
    // Struct literal support
    // ============================================================

    static std::optional<uint32_t> try_field_index_from_pass5(const Pass5Result& p5,
                                                              StructId sid,
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

    static llvm::StringRef reserved_name_from_intrinsic(RuntimeIntrinsic k)
    {
        switch (k)
        {
        case RuntimeIntrinsic::box_new: return "box_new";
        case RuntimeIntrinsic::box_free: return "box_free";
        case RuntimeIntrinsic::box_len: return "box_len";
        case RuntimeIntrinsic::box_get: return "box_get";
        case RuntimeIntrinsic::box_set: return "box_set";
        case RuntimeIntrinsic::print: return "print";
        default: return "";
        }
    }

    static llvm::Value* emit_struct_lit(FnCG& cg, ast::StructLiteralExpr& s, Pass9_5Result& out)
    {
        const DynTag dt = dyn_tag_of(cg.p8, static_cast<const ast::Expr*>(&s));
        if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, s.location_,
                      "struct literal has no StructId tag (Pass8 missing StructObj tag?)");
            return null_obj(cg.st);
        }

        const StructId sid = *dt.struct_id;

        const auto sid_i64 = static_cast<std::int64_t>(sid.index);
        llvm::Value* sidV = llvm::ConstantInt::get(cg.st.i64_ty, sid_i64);

        const auto n_inits = static_cast<std::int64_t>(s.elements_.size());
        llvm::Value* nFieldsV = llvm::ConstantInt::get(cg.st.i64_ty, n_inits);

        llvm::Value* obj = cg.B.CreateCall(cg.rt->rt_struct_new, {sidV, nFieldsV}, "struct.new");

        std::unordered_set<lex::SymId> seen;
        std::int64_t fallback_index = 0;

        for (auto* fi : s.elements_)
        {
            if (!fi) continue;

            const lex::SymId fname = fi->name;
            if (!seen.insert(fname).second)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, fi->location_,
                          "duplicate field initializer in struct literal");
                continue;
            }

            std::optional<uint32_t> idx = try_field_index_from_pass5(cg.p5, sid, fname);
            std::int64_t idx_i64 = idx.has_value()
                                       ? static_cast<std::int64_t>(*idx)
                                       : fallback_index++;

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
    // Expression emission
    // ============================================================

    static llvm::Value* emit_ref(FnCG& cg, ast::RefExpr& r, Pass9_5Result& out)
    {
        if (!cg.binds)
        {
            push_diag(out, Pass9_5Diagnostic::Code::MissingBindingsForFn, r.location_,
                      "internal: missing FnBindings when emitting RefExpr");
            return null_obj(cg.st);
        }

        auto it = cg.binds->ref_binding.find(&r);
        if (it == cg.binds->ref_binding.end())
        {
            push_diag(out, Pass9_5Diagnostic::Code::MissingRefBinding, r.location_,
                      "RefExpr has no binding entry (Pass6 missing?)");
            return null_obj(cg.st);
        }

        const Binding& b = it->second;

        switch (b.kind)
        {
        case BindingKind::LocalSlot:
            {
                llvm::Value* v = cg.B.CreateLoad(cg.st.obj_ptr_ty, cg.slot_alloca[b.slot.index], "ld.slot");
                if (cg.rt && cg.rt->rt_retain)
                    cg.B.CreateCall(cg.rt->rt_retain, {v});
                return v; // owned
            }

        case BindingKind::GlobalFn:
        case BindingKind::GlobalLoadFn:
        case BindingKind::ImportAlias:
        case BindingKind::Unresolved:
        default:
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, r.location_,
                      "RefExpr used as a value is only supported for locals (functions must be called)");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_assign(FnCG& cg, ast::AssignExpr& a, Pass9_5Result& out)
    {
        if (!cg.binds)
            return null_obj(cg.st);

        llvm::Value* rhs = emit_expr(cg, a.rhs_, out);
        ValueTag rhsTag = to_value_tag(dyn_tag_of(cg.p8, a.rhs_));
        llvm::Value* rhsObj = cg.box_if_needed(rhsTag, rhs);

        // Case 1: local slot assignment
        if (auto* lhs_ref = dynamic_cast<ast::RefExpr*>(a.lhs_))
        {
            auto it = cg.binds->ref_binding.find(lhs_ref);
            if (it == cg.binds->ref_binding.end() || it->second.kind != BindingKind::LocalSlot)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                          "assignment LHS must be a bound local slot");
                return null_obj(cg.st);
            }

            const SlotId slot = it->second.slot;
            if (slot.index >= cg.slot_alloca.size() || !cg.slot_alloca[slot.index])
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                          "internal: local slot has no alloca in pass9.5 prologue");
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
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                          "assignment supports only RefExpr or deref (*expr) on LHS");
                return null_obj(cg.st);
            }

            if (!cg.rt || !cg.rt->rt_ref_store)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                          "missing runtime intrinsic rt_ref_store");
                return null_obj(cg.st);
            }

            llvm::Value* refVal = emit_expr(cg, lhs_u->expr_, out);
            ValueTag refTag = to_value_tag(dyn_tag_of(cg.p8, lhs_u->expr_));
            llvm::Value* refObj = cg.box_if_needed(refTag, refVal);

            cg.B.CreateCall(cg.rt->rt_ref_store, {refObj, rhsObj});
            cg.arc_release_value_if_obj(refObj);
            return rhsObj;
        }

        if (auto* lhs_ix = dynamic_cast<ast::IndexExpr*>(a.lhs_))
        {
            if (!cg.rt || !cg.rt->box_set)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                          "missing runtime intrinsic box_set (needed for index assignment)");
                return null_obj(cg.st);
            }

            // Load base if it is a ref (&T), same as reserved calls.
            llvm::Value* baseV = materialize_value_if_ref(cg, lhs_ix->base_, out);
            ValueTag baseTag = to_value_tag(dyn_tag_of(cg.p8, lhs_ix->base_));
            llvm::Value* baseObj = cg.box_if_needed(baseTag, baseV);

            llvm::Value* idxV = emit_expr(cg, lhs_ix->index_, out);
            ValueTag idxTag = to_value_tag(dyn_tag_of(cg.p8, lhs_ix->index_));
            llvm::Value* idxObj = cg.box_if_needed(idxTag, idxV);

            llvm::FunctionType* setFT = llvm::FunctionType::get(
                cg.st.void_ty,
                {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
                false);

            (void)call_runtime_erased(cg, cg.rt->box_set, setFT, {baseObj, idxObj, rhsObj}, "box_set.index.assign");
            cg.arc_release_value_if_obj(baseObj);
            cg.arc_release_value_if_obj(idxObj);
            return rhsObj;
        }

        push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                  "assignment supports only local refs (x=) or deref (*p=) on LHS");
        return null_obj(cg.st);
    }

    static llvm::Value* emit_call(FnCG& cg, ast::CallExpr& c, Pass9_5Result& out)
    {
        if (!cg.binds)
        {
            push_diag(out, Pass9_5Diagnostic::Code::MissingBindingsForFn, c.location_,
                      "internal: missing FnBindings when emitting CallExpr");
            return null_obj(cg.st);
        }

        if (!c.callee_)
        {
            push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                      "call has null callee");
            return null_obj(cg.st);
        }

        // Resolve call target via Pass6 expr_binding (RefExpr OR PathExpr)
        const Binding* b = nullptr;

        if (auto it = cg.binds->expr_binding.find(c.callee_); it != cg.binds->expr_binding.end())
            b = &it->second;

        if (!b)
        {
            if (auto* callee_ref = dynamic_cast<ast::RefExpr*>(c.callee_))
            {
                if (auto it = cg.binds->ref_binding.find(callee_ref); it != cg.binds->ref_binding.end())
                    b = &it->second;
            }
        }

        if (!b)
        {
            push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                      "call callee is not bound (Pass6 did not add an expr_binding entry)");
            return null_obj(cg.st);
        }

        // ------------------------------------------------------------
        // IMPORTANT FIX:
        // If Pass6 bound this as a RuntimeIntrinsic, emit the reserved call
        // directly (do NOT resolve a mangled user fn, and do NOT arity-check
        // against the user fn signature).
        // ------------------------------------------------------------
        if (b->kind == BindingKind::RuntimeIntrinsic)
        {
            const llvm::StringRef nm = reserved_name_from_intrinsic(b->intrinsic);
            if (nm.empty())
            {
                push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                          "unknown runtime intrinsic bound in call callee");
                return null_obj(cg.st);
            }

            bool handled = false;
            llvm::Value* r = emit_reserved_call(cg, nm, c, out, handled);
            if (handled)
                return r; // may be nullptr for void

            // Should not happen, but keep a hard diagnostic.
            push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                      "runtime intrinsic was not handled by reserved lowering");
            return null_obj(cg.st);
        }

        // ------------------------------------------------------------
        // Normal callable path (GlobalFn / GlobalLoadFn)
        // ------------------------------------------------------------
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
            push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                      "call callee is bound, but not as a callable (expected GlobalFn, GlobalLoadFn, or RuntimeIntrinsic)");
            return null_obj(cg.st);
        }

        if (!target)
        {
            push_diag(out, Pass9_5Diagnostic::Code::MissingFnDeclInIR, c.location_,
                      "call target not declared in IR (Pass9.3 missing fn/load-fn decl?)");
            return null_obj(cg.st);
        }

        // Optional safety: if you ever declare runtime functions unmangled in IR,
        // this still works (but the intrinsic path above is the real fix).
        {
            llvm::StringRef calleeName = target->getName();

            if (is_reserved_runtime_name(calleeName))
            {
                bool handled = false;
                llvm::Value* r = emit_reserved_call(cg, calleeName, c, out, handled);
                if (handled)
                    return r; // may be nullptr for void
            }
        }

        // Arity check against the LLVM function type
        llvm::FunctionType* FT = target->getFunctionType();
        const unsigned nParams = FT->getNumParams();
        const unsigned nArgs = static_cast<unsigned>(c.args_.size());

        if (nArgs != nParams)
        {
            push_diag(out, Pass9_5Diagnostic::Code::InvalidCallCallee, c.location_,
                      "call argument count does not match callee signature");
            return null_obj(cg.st);
        }

        // Emit args with coercion to LLVM param types
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

        // Box/unbox return as needed
        ValueTag retTag = to_value_tag(dyn_tag_of(cg.p8, &c));

        if (call->getType()->isVoidTy())
            return nullptr;

        if (call->getType() == cg.st.i1_ty && retTag == ValueTag::Obj)
            return cg.B.CreateCall(cg.rt->rt_box_bool, {call}, "box.ret.bool");

        if (call->getType() == cg.st.obj_ptr_ty && retTag == ValueTag::Bool)
        {
            llvm::Value* b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {call}, "unbox.ret.bool");
            cg.arc_release_value_if_obj(call);
            return b;
        }

        return call;
    }

    static llvm::Value* emit_logical_and(FnCG& cg, ast::BinaryExpr& b, Pass9_5Result& out)
    {
        llvm::Function* F = cg.B.GetInsertBlock() ? cg.B.GetInsertBlock()->getParent() : cg.F;
        if (!F)
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, b.location_,
                      "internal: missing current function for &&");
            return llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        llvm::BasicBlock* condBB = cg.B.GetInsertBlock(); // predecessor BEFORE branching

        // LHS -> i1 robustly
        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        ValueTag lhsT = to_value_tag(dyn_tag_of(cg.p8, b.lhs_));
        llvm::Value* lhsB = cg.coerce_to(cg.st.i1_ty, lhsT, lhsV);
        if (!lhsB) lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (lhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                lhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {lhsB}, "land.lhs.unbox");
            else
                lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (lhsB->getType() != cg.st.i1_ty)
            lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*cg.st.llctx, "land.rhs", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "land.end", F);

        if (lhsV && lhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(lhsV);

        cg.B.CreateCondBr(lhsB, rhsBB, endBB);

        // rhs
        cg.B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);
        ValueTag rhsT = to_value_tag(dyn_tag_of(cg.p8, b.rhs_));
        llvm::Value* rhsB = cg.coerce_to(cg.st.i1_ty, rhsT, rhsV);
        if (!rhsB) rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (rhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                rhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {rhsB}, "land.rhs.unbox");
            else
                rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (rhsB->getType() != cg.st.i1_ty)
            rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);


        if (rhsV && rhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(rhsV);

        cg.B.CreateBr(endBB);

        // end + phi
        cg.B.SetInsertPoint(endBB);
        auto* phi = cg.B.CreatePHI(cg.st.i1_ty, 2, "land");
        phi->addIncoming(llvm::ConstantInt::getFalse(*cg.st.llctx), condBB);
        phi->addIncoming(rhsB, rhsBB);

        return phi;
    }

    static llvm::Value* emit_logical_or(FnCG& cg, ast::BinaryExpr& b, Pass9_5Result& out)
    {
        llvm::Function* F = cg.B.GetInsertBlock() ? cg.B.GetInsertBlock()->getParent() : cg.F;
        if (!F)
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, b.location_,
                      "internal: missing current function for ||");
            return llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        llvm::BasicBlock* condBB = cg.B.GetInsertBlock(); // predecessor BEFORE branching

        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        ValueTag lhsT = to_value_tag(dyn_tag_of(cg.p8, b.lhs_));
        llvm::Value* lhsB = cg.coerce_to(cg.st.i1_ty, lhsT, lhsV);
        if (!lhsB) lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (lhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                lhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {lhsB}, "lor.lhs.unbox");
            else
                lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (lhsB->getType() != cg.st.i1_ty)
            lhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*cg.st.llctx, "lor.rhs", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "lor.end", F);

        if (lhsV && lhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(lhsV);

        cg.B.CreateCondBr(lhsB, endBB, rhsBB);

        // rhs
        cg.B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);
        ValueTag rhsT = to_value_tag(dyn_tag_of(cg.p8, b.rhs_));
        llvm::Value* rhsB = cg.coerce_to(cg.st.i1_ty, rhsT, rhsV);
        if (!rhsB) rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (rhsB->getType() == cg.st.obj_ptr_ty)
        {
            if (cg.rt && cg.rt->rt_unbox_bool)
                rhsB = cg.B.CreateCall(cg.rt->rt_unbox_bool, {rhsB}, "lor.rhs.unbox");
            else
                rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);
        }

        if (rhsB->getType() != cg.st.i1_ty)
            rhsB = llvm::ConstantInt::getFalse(*cg.st.llctx);

        if (rhsV && rhsV->getType() == cg.st.obj_ptr_ty)
            cg.arc_release_value_if_obj(rhsV);

        cg.B.CreateBr(endBB);

        // end + phi
        cg.B.SetInsertPoint(endBB);
        auto* phi = cg.B.CreatePHI(cg.st.i1_ty, 2, "lor");
        phi->addIncoming(llvm::ConstantInt::getTrue(*cg.st.llctx), condBB);
        phi->addIncoming(rhsB, rhsBB);

        return phi;
    }

    static llvm::Value* emit_binary(FnCG& cg, ast::BinaryExpr& b, Pass9_5Result& out)
    {
        using Op = ast::BinaryOp;

        if (b.op == Op::logical_and)
            return emit_logical_and(cg, b, out);

        if (b.op == Op::logical_or)
            return emit_logical_or(cg, b, out);

        llvm::Value* lhsV = emit_expr(cg, b.lhs_, out);
        llvm::Value* rhsV = emit_expr(cg, b.rhs_, out);

        ValueTag lt = to_value_tag(dyn_tag_of(cg.p8, b.lhs_));
        ValueTag rt = to_value_tag(dyn_tag_of(cg.p8, b.rhs_));

        llvm::Value* lhsObj = cg.box_if_needed(lt, lhsV);
        llvm::Value* rhsObj = cg.box_if_needed(rt, rhsV);

        auto call2_and_release = [&](llvm::FunctionCallee callee, const char* name) -> llvm::Value*
        {
            llvm::Value* res = cg.B.CreateCall(callee, {lhsObj, rhsObj}, name);
            cg.arc_release_value_if_obj(lhsObj);
            cg.arc_release_value_if_obj(rhsObj);
            return res;
        };

        switch (b.op)
        {
        case Op::add: return call2_and_release(cg.rt->rt_add, "add");
        case Op::subtract: return call2_and_release(cg.rt->rt_sub, "sub");
        case Op::multiply: return call2_and_release(cg.rt->rt_mul, "mul");
        case Op::divide: return call2_and_release(cg.rt->rt_div, "div");
        case Op::modulo: return call2_and_release(cg.rt->rt_mod, "mod");

        case Op::equal: return call2_and_release(cg.rt->rt_eq, "eq");
        case Op::not_equal: return call2_and_release(cg.rt->rt_ne, "ne");
        case Op::less: return call2_and_release(cg.rt->rt_lt, "lt");
        case Op::less_equal: return call2_and_release(cg.rt->rt_le, "le");
        case Op::greater: return call2_and_release(cg.rt->rt_gt, "gt");
        case Op::greater_equal: return call2_and_release(cg.rt->rt_ge, "ge");

        default:
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, b.location_,
                      "unsupported binary operator in pass9.5");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_unary(FnCG& cg, ast::UnaryExpr& u, Pass9_5Result& out)
    {
        using U = ast::UnaryOp;

        switch (u.op)
        {
        case U::logical_not:
            {
                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                ValueTag innerTag = to_value_tag(dyn_tag_of(cg.p8, u.expr_));

                llvm::Value* b = cg.coerce_to(cg.st.i1_ty, innerTag, inner);
                if (!b) b = llvm::ConstantInt::getFalse(*cg.st.llctx);

                // If coercion produced Obj*, unbox it to i1.
                if (b->getType() == cg.st.obj_ptr_ty)
                {
                    if (cg.rt && cg.rt->rt_unbox_bool)
                        b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {b}, "not.unbox");
                    else
                        b = llvm::ConstantInt::getFalse(*cg.st.llctx);
                }

                if (b->getType() != cg.st.i1_ty)
                    b = llvm::ConstantInt::getFalse(*cg.st.llctx);

                // Release the produced value if it was Obj*.
                cg.arc_release_value_if_obj(inner);

                return cg.B.CreateNot(b, "not");
            }

        case U::negation:
            {
                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                ValueTag innerTag = to_value_tag(dyn_tag_of(cg.p8, u.expr_));

                if (innerTag == ValueTag::Bool)
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "unary '-' is not valid for bool");
                    cg.arc_release_value_if_obj(inner);
                    return null_obj(cg.st);
                }

                llvm::Value* xObj = cg.box_if_needed(innerTag, inner);
                // If inner was Obj* already, box_if_needed returns it; if it was i1, it boxes.
                // Either way, we should not separately release `inner` now, because xObj may == inner.
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

                if (!cg.rt || !cg.rt->rt_sub)
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "missing runtime intrinsic for unary '-' (need rt_neg or rt_sub)");
                    cg.arc_release_value_if_obj(xObj);
                    return null_obj(cg.st);
                }

                // Synthesize 0 and compute 0 - x
                llvm::Value* zeroObj = nullptr;
                if (cg.rt->rt_int_from_i64)
                {
                    llvm::Value* z = llvm::ConstantInt::get(cg.st.i64_ty, 0, /*isSigned=*/true);
                    zeroObj = cg.B.CreateCall(cg.rt->rt_int_from_i64, {z}, "int.zero");
                }
                else if (cg.rt->rt_int_from_u64)
                {
                    llvm::Value* z = llvm::ConstantInt::get(cg.st.i64_ty, 0, /*isSigned=*/false);
                    zeroObj = cg.B.CreateCall(cg.rt->rt_int_from_u64, {z}, "uint.zero");
                }
                else
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "cannot synthesize 0 for unary '-' (missing rt_int_from_i64/rt_int_from_u64)");
                    cg.arc_release_value_if_obj(xObj);
                    return null_obj(cg.st);
                }

                llvm::Value* res = cg.B.CreateCall(cg.rt->rt_sub, {zeroObj, xObj}, "neg.sub");
                cg.arc_release_value_if_obj(zeroObj);
                cg.arc_release_value_if_obj(xObj);
                return res;
            }

        case U::deref:
            {
                llvm::Value* inner = emit_expr(cg, u.expr_, out);
                ValueTag innerTag = to_value_tag(dyn_tag_of(cg.p8, u.expr_));
                ValueTag resTag = to_value_tag(dyn_tag_of(cg.p8, &u));

                if (!cg.rt || !cg.rt->rt_ref_load)
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "missing runtime intrinsic rt_ref_load");
                    cg.arc_release_value_if_obj(inner);
                    return null_obj(cg.st);
                }

                llvm::Value* refObj = cg.box_if_needed(innerTag, inner);
                if (inner && inner->getType() == cg.st.obj_ptr_ty && refObj != inner)
                    cg.arc_release_value_if_obj(inner);

                llvm::Value* loadedObj = cg.B.CreateCall(cg.rt->rt_ref_load, {refObj}, "ref.load");
                cg.arc_release_value_if_obj(refObj);

                if (resTag == ValueTag::Bool)
                {
                    if (!cg.rt || !cg.rt->rt_unbox_bool)
                    {
                        push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                                  "missing runtime intrinsic rt_unbox_bool (needed for deref bool)");
                        cg.arc_release_value_if_obj(loadedObj);
                        return llvm::ConstantInt::getFalse(*cg.st.llctx);
                    }

                    llvm::Value* b = cg.B.CreateCall(cg.rt->rt_unbox_bool, {loadedObj}, "unbox.deref.bool");
                    cg.arc_release_value_if_obj(loadedObj);
                    return b;
                }

                // Default: deref returns an Obj*.
                return loadedObj;
            }

        case U::addr_of:
        case U::addr_of_mut:
            {
                // Optimization: &(*p) == p (same for &mut *p)
                if (auto* innerU = dynamic_cast<ast::UnaryExpr*>(u.expr_))
                    if (innerU->op == U::deref)
                        return emit_expr(cg, innerU->expr_, out);

                const bool wantMut = (u.op == U::addr_of_mut);
                if (wantMut && !place_is_mutable(cg, u.expr_))
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "cannot take &mut of an immutable place");
                    return null_obj(cg.st);
                }

                llvm::Value* slotAddr = emit_place_slot_addr(cg, u.expr_, out);
                if (!slotAddr)
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "address-of supported only for places (locals, fields, indexing) in pass9.5");
                    return null_obj(cg.st);
                }

                if (!cg.rt || !cg.rt->rt_ref_from_slot)
                {
                    push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                              "missing runtime intrinsic rt_ref_from_slot");
                    return null_obj(cg.st);
                }

                // IMPORTANT: do NOT load/retain the pointee here.
                return cg.B.CreateCall(cg.rt->rt_ref_from_slot, {slotAddr}, "ref.from.slot");
            }

        default:
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, u.location_,
                      "unsupported unary operator in pass9.5");
            return null_obj(cg.st);
        }
    }

    static llvm::Value* emit_u64_as_obj(FnCG& cg, std::uint64_t v, const lex::Loc& loc, Pass9_5Result& out,
                                        llvm::StringRef dbg = "u64")
    {
        if (!cg.rt || (!cg.rt->rt_int_from_u64 && !cg.rt->rt_int_from_i64))
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, loc,
                      "missing runtime intrinsic rt_int_from_u64/rt_int_from_i64 (needed for array literal/index)");
            return null_obj(cg.st);
        }

        // Your runtime uses i64 params for int constructors.
        // We pass the value as i64 (unsigned) to rt_int_from_u64 when available.
        llvm::Value* imm = llvm::ConstantInt::get(cg.st.i64_ty, static_cast<std::uint64_t>(v), /*isSigned=*/false);

        if (cg.rt->rt_int_from_u64)
            return cg.B.CreateCall(cg.rt->rt_int_from_u64, {imm}, (dbg + ".u64").str());

        // fallback
        return cg.B.CreateCall(cg.rt->rt_int_from_i64, {imm}, (dbg + ".i64").str());
    }

    static llvm::Value* emit_array_literal(FnCG& cg, ast::ArrayLiteralExpr& a, Pass9_5Result& out)
    {
        if (!cg.rt || !cg.rt->box_new || !cg.rt->box_set)
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, a.location_,
                      "missing runtime intrinsic box_new/box_set (needed for array literal)");
            return null_obj(cg.st);
        }

        const auto n = static_cast<std::uint64_t>(a.v_.size());

        // box_new(len: Obj*) -> Obj*
        llvm::Value* lenObj = emit_u64_as_obj(cg, n, a.location_, out, "arr.len");
        auto* I64 = cg.st.i64_ty;
        llvm::Value* kind = llvm::ConstantInt::get(I64, 0); // ObjPtr
        llvm::Value* esz = llvm::ConstantInt::get(I64, 8); // sizeof(void*) on x86_64
        llvm::Value* eal = llvm::ConstantInt::get(I64, 8); // alignof(void*) on x86_64

        llvm::FunctionType* newFT =
            llvm::FunctionType::get(cg.st.obj_ptr_ty,
                                    {cg.st.obj_ptr_ty, I64, I64, I64}, false);

        llvm::CallInst* box =
            call_runtime_erased(cg, cg.rt->box_new, newFT, {lenObj, kind, esz, eal}, "box_new.arrlit");
        llvm::Value* arrObj = box ? static_cast<llvm::Value*>(box) : null_obj(cg.st);
        cg.arc_release_value_if_obj(lenObj);

        // for i: box_set(arr, i, value)
        llvm::FunctionType* setFT = llvm::FunctionType::get(
            cg.st.void_ty,
            {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
            false);

        for (std::uint64_t i = 0; i < n; ++i)
        {
            ast::Expr* el = a.v_[static_cast<size_t>(i)];
            if (!el) continue;

            llvm::Value* idxObj = emit_u64_as_obj(cg, i, el->location_, out, "arr.idx");

            llvm::Value* v = emit_expr(cg, el, out);
            ValueTag vTag = to_value_tag(dyn_tag_of(cg.p8, el));
            llvm::Value* vObj = cg.box_if_needed(vTag, v);

            (void)call_runtime_erased(cg, cg.rt->box_set, setFT, {arrObj, idxObj, vObj}, "box_set.arrlit");
            cg.arc_release_value_if_obj(idxObj);
            cg.arc_release_value_if_obj(vObj);
        }

        return arrObj;
    }

    static llvm::Value* emit_index_expr(FnCG& cg, ast::IndexExpr& ix, Pass9_5Result& out)
    {
        if (!cg.rt || !cg.rt->box_get)
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, ix.location_,
                      "missing runtime intrinsic box_get (needed for index expression)");
            return null_obj(cg.st);
        }

        // If base is a ref type (&T), load it (same logic as reserved calls).
        llvm::Value* baseV = materialize_value_if_ref(cg, ix.base_, out);
        ValueTag baseTag = to_value_tag(dyn_tag_of(cg.p8, ix.base_));
        llvm::Value* baseObj = cg.box_if_needed(baseTag, baseV);

        llvm::Value* idxV = emit_expr(cg, ix.index_, out);
        ValueTag idxTag = to_value_tag(dyn_tag_of(cg.p8, ix.index_));
        llvm::Value* idxObj = cg.box_if_needed(idxTag, idxV);

        llvm::FunctionType* getFT = llvm::FunctionType::get(
            cg.st.obj_ptr_ty,
            {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty},
            false);

        llvm::CallInst* call = call_runtime_erased(cg, cg.rt->box_get, getFT, {baseObj, idxObj}, "box_get.index");
        cg.arc_release_value_if_obj(baseObj);
        cg.arc_release_value_if_obj(idxObj);
        return call ? static_cast<llvm::Value*>(call) : null_obj(cg.st);
    }

    static llvm::Value* emit_field(FnCG& cg, ast::FieldExpr& f, Pass9_5Result& out)
    {
        llvm::Value* baseV = emit_expr(cg, f.base_, out);
        ValueTag baseTag = to_value_tag(dyn_tag_of(cg.p8, f.base_));
        llvm::Value* baseObj = cg.box_if_needed(baseTag, baseV);

        DynTag dt = dyn_tag_of(cg.p8, f.base_);
        if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, f.location_,
                      "field access on non-struct value (Pass8 missing StructObj tag?)");
            return null_obj(cg.st);
        }
        StructId sid = *dt.struct_id;

        const lex::SymId field_name = f.field;

        auto idxOpt = try_field_index_from_pass5(cg.p5, sid, field_name);
        if (!idxOpt.has_value())
        {
            push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, f.location_,
                      "unknown field name for struct in field expression");
            return null_obj(cg.st);
        }

        llvm::Value* idxV = llvm::ConstantInt::get(cg.st.i64_ty, static_cast<std::int64_t>(*idxOpt));
        llvm::Value* res = cg.B.CreateCall(cg.rt->rt_struct_get_field, {baseObj, idxV}, "struct.get");
        cg.arc_release_value_if_obj(baseObj);
        return res;
    }

    static llvm::Value* emit_expr(FnCG& cg, ast::Expr* e, Pass9_5Result& out)
    {
        if (!e) return nullptr;

        if (auto* i = dynamic_cast<ast::IntLiteralExpr*>(e)) return emit_int_from_pass7(cg, *i, out);
        if (auto* f = dynamic_cast<ast::FloatLiteralExpr*>(e)) return emit_float_from_pass7(cg, *f, out);
        if (auto* b = dynamic_cast<ast::BoolLiteralExpr*>(e)) return llvm::ConstantInt::get(cg.st.i1_ty, b->v_ ? 1 : 0);
        if (auto* r = dynamic_cast<ast::RefExpr*>(e)) return emit_ref(cg, *r, out);
        if (auto* a = dynamic_cast<ast::AssignExpr*>(e)) return emit_assign(cg, *a, out);
        if (auto* c = dynamic_cast<ast::CallExpr*>(e)) return emit_call(cg, *c, out);
        if (auto* bi = dynamic_cast<ast::BinaryExpr*>(e)) return emit_binary(cg, *bi, out);
        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e)) return emit_unary(cg, *u, out);
        if (auto* st = dynamic_cast<ast::StructLiteralExpr*>(e)) return emit_struct_lit(cg, *st, out);
        if (auto* fe = dynamic_cast<ast::FieldExpr*>(e)) return emit_field(cg, *fe, out);
        if (auto* al = dynamic_cast<ast::ArrayLiteralExpr*>(e)) return emit_array_literal(cg, *al, out);
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e)) return emit_index_expr(cg, *ix, out);

        push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, e->location_,
                  "unsupported expression in pass9.5");
        return null_obj(cg.st);
    }

    // ============================================================
    // Statement emission
    // ============================================================

    static void emit_block(FnCG& cg, ast::BlockStatement& b, Pass9_5Result& out)
    {
        cg.scope_slots.emplace_back(); // push scope

        for (auto* s : b.statements_)
        {
            if (!s) continue;

            // If we already emitted a terminator (return/br), stop emitting.
            if (cg.B.GetInsertBlock() && cg.B.GetInsertBlock()->getTerminator())
                break;

            emit_stmt(cg, s, out);
        }

        // Only release locals on fallthrough.
        if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
            cg.arc_release_current_scope();

        cg.scope_slots.pop_back(); // pop scope (now always safe)
    }

    static std::optional<SlotId> find_slot_for_var(const FnBindings& binds, const ast::VarStmt& v)
    {
        for (const auto& si : binds.slots)
            if (si.var_decl == &v)
                return si.slot;
        return std::nullopt;
    }

    static const LocalSlotInfo* find_slot_info_by_slot(const FnBindings& binds, SlotId s)
    {
        for (const auto& si : binds.slots)
            if (si.slot.index == s.index)
                return &si;
        return nullptr;
    }

    static bool is_ref_mutable_type(const Pass5Result& p5, TypeId t)
    {
        if (t.value >= p5.types.nodes.size()) return false;
        const TypeNode& n = p5.types.nodes[t.value];
        return (n.kind == TypeKind::Ref) && n.ref_mut;
    }

    static bool place_is_mutable(FnCG& cg, ast::Expr* e)
    {
        if (!e || !cg.binds) return false;

        // local variable
        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = cg.binds->ref_binding.find(r);
            if (it == cg.binds->ref_binding.end()) return false;
            if (it->second.kind != BindingKind::LocalSlot) return false;

            const SlotId slot = it->second.slot;
            const LocalSlotInfo* si = find_slot_info_by_slot(*cg.binds, slot);
            return si && (si->mut_ == ast::Mutability::Mut);
        }

        // deref place: mutability comes from the ref type (&mut T vs &T)
        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
        {
            if (u->op == ast::UnaryOp::deref)
            {
                TypeId innerT = expr_type_id_or_bad(cg.p7, u->expr_);
                return is_ref_mutable_type(cg.p5, innerT);
            }
        }

        // field / index: inherits from base place
        if (auto* f = dynamic_cast<ast::FieldExpr*>(e))
            return place_is_mutable(cg, f->base_);
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
            return place_is_mutable(cg, ix->base_);

        return false;
    }

    static llvm::Value* emit_place_slot_addr(FnCG& cg, ast::Expr* e, Pass9_5Result& out)
    {
        if (!e || !cg.binds) return nullptr;

        // 1) local slot -> alloca Obj* (i.e. Obj**)
        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = cg.binds->ref_binding.find(r);
            if (it == cg.binds->ref_binding.end()) return nullptr;
            if (it->second.kind != BindingKind::LocalSlot) return nullptr;

            const SlotId slot = it->second.slot;
            if (slot.index >= cg.slot_alloca.size()) return nullptr;
            return cg.slot_alloca[slot.index]; // Obj**
        }

        // 2) field place -> runtime returns Obj** for the field cell
        if (auto* fe = dynamic_cast<ast::FieldExpr*>(e))
        {
            if (!cg.rt || !cg.rt->rt_struct_field_slot)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, fe->location_,
                          "missing runtime intrinsic rt_struct_field_slot (needed for &struct.field)");
                return nullptr;
            }

            // base struct object (if base is a ref, load it)
            llvm::Value* baseV = materialize_value_if_ref(cg, fe->base_, out);
            ValueTag baseTag = to_value_tag(dyn_tag_of(cg.p8, fe->base_));
            llvm::Value* baseObj = cg.box_if_needed(baseTag, baseV);

            DynTag dt = dyn_tag_of(cg.p8, fe->base_);
            if (dt.kind != DynTagKind::StructObj || !dt.struct_id.has_value())
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, fe->location_,
                          "cannot take address of field on non-struct base (Pass8 missing StructObj tag?)");
                return nullptr;
            }

            StructId sid = *dt.struct_id;
            auto idxOpt = try_field_index_from_pass5(cg.p5, sid, fe->field);
            if (!idxOpt.has_value())
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, fe->location_,
                          "unknown field name for struct in address-of");
                return nullptr;
            }

            llvm::Value* idxV = llvm::ConstantInt::get(cg.st.i64_ty, *idxOpt);

            // Signature we *want* in LLVM: Obj** rt_struct_field_slot(Obj* structObj, i64 idx)
            llvm::Type* objSlotPtrTy = llvm::PointerType::getUnqual(cg.st.obj_ptr_ty);
            llvm::FunctionType* FT = llvm::FunctionType::get(objSlotPtrTy, {cg.st.obj_ptr_ty, cg.st.i64_ty}, false);

            llvm::CallInst* call = call_runtime_erased(cg, cg.rt->rt_struct_field_slot, FT, {baseObj, idxV},
                                                       "struct.field.slot");
            cg.arc_release_value_if_obj(baseObj);
            return call;
        }

        // 3) index place -> runtime returns Obj** for element cell (Box/array)
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
        {
            if (!cg.rt || !cg.rt->rt_box_elem_slot)
            {
                push_diag(out, Pass9_5Diagnostic::Code::UnsupportedExpr, ix->location_,
                          "missing runtime intrinsic rt_box_elem_slot (needed for &arr[i])");
                return nullptr;
            }

            llvm::Value* baseV = materialize_value_if_ref(cg, ix->base_, out);
            ValueTag baseTag = to_value_tag(dyn_tag_of(cg.p8, ix->base_));
            llvm::Value* baseObj = cg.box_if_needed(baseTag, baseV);

            llvm::Value* idxV = emit_expr(cg, ix->index_, out);
            ValueTag idxTag = to_value_tag(dyn_tag_of(cg.p8, ix->index_));
            llvm::Value* idxObj = cg.box_if_needed(idxTag, idxV);

            llvm::Type* objSlotPtrTy = llvm::PointerType::getUnqual(cg.st.obj_ptr_ty);
            llvm::FunctionType* FT = llvm::FunctionType::get(objSlotPtrTy, {cg.st.obj_ptr_ty, cg.st.obj_ptr_ty}, false);

            llvm::CallInst* call = call_runtime_erased(cg, cg.rt->rt_box_elem_slot, FT, {baseObj, idxObj},
                                                       "box.elem.slot");
            cg.arc_release_value_if_obj(baseObj);
            cg.arc_release_value_if_obj(idxObj);
            return call;
        }

        return nullptr;
    }

    static void emit_var(FnCG& cg, ast::VarStmt& v, Pass9_5Result& out)
    {
        if (!cg.binds) return;

        auto slot = find_slot_for_var(*cg.binds, v);
        if (!slot.has_value())
            return;

        llvm::Value* rhs = nullptr;
        ValueTag rhsTag = ValueTag::Void;

        if (v.init_)
        {
            rhs = emit_expr(cg, v.init_, out);
            rhsTag = to_value_tag(dyn_tag_of(cg.p8, v.init_));
        }
        else
        {
            rhs = null_obj(cg.st);
            rhsTag = ValueTag::Obj;
        }

        llvm::Value* rhsObj = cg.box_if_needed(rhsTag, rhs);

        if (slot->index < cg.slot_alloca.size() && cg.slot_alloca[slot->index])
        {
            // Track the slot in the CURRENT scope so it gets released at block end.
            if (!cg.scope_slots.empty())
                cg.scope_slots.back().push_back(*slot);

            cg.arc_store_slot(cg.slot_alloca[slot->index], rhsObj);
            cg.arc_release_value_if_obj(rhsObj);
        }
    }


    static void emit_return(FnCG& cg, ast::ReturnStatement& r, Pass9_5Result& out)
    {
        (void)out;

        llvm::Type* RT = cg.F->getReturnType();

        // void return
        if (!r.expr_ || RT->isVoidTy())
        {
            // Release all active scopes (innermost -> outermost)
            if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
            {
                for (auto it = cg.scope_slots.rbegin(); it != cg.scope_slots.rend(); ++it)
                    cg.arc_release_slot_list(*it);
            }

            cg.B.CreateRetVoid();
            return;
        }

        llvm::Value* v = emit_expr(cg, r.expr_, out);
        ValueTag t = to_value_tag(dyn_tag_of(cg.p8, r.expr_));
        llvm::Value* coerced = cg.coerce_to(RT, t, v);
        if (!coerced) coerced = llvm::UndefValue::get(RT);

        // If returning Obj*, retain it so scope teardown doesn't free it.
        // if (RT == cg.st.obj_ptr_ty && cg.rt && cg.rt->rt_retain)
        //     cg.B.CreateCall(cg.rt->rt_retain, {coerced});

        // Release all active scopes (innermost -> outermost)
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

        llvm::Value* cndB = force_i1_condition(cg, i.condition_, i.location_, out, "if.cond");

        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(*cg.st.llctx, "if.then", F);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(*cg.st.llctx, "if.else", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "if.end", F);

        cg.B.CreateCondBr(cndB, thenBB, elseBB);

        // then
        cg.B.SetInsertPoint(thenBB);
        if (i.thenBody_) emit_block(cg, *i.thenBody_, out);
        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(endBB);

        // else chain
        cg.B.SetInsertPoint(elseBB);
        llvm::BasicBlock* curElse = elseBB;

        for (auto* eif : i.elseIfs_)
        {
            if (!eif) continue;

            llvm::BasicBlock* eifThen = llvm::BasicBlock::Create(*cg.st.llctx, "elseif.then", F);
            llvm::BasicBlock* eifNext = llvm::BasicBlock::Create(*cg.st.llctx, "elseif.next", F);

            cg.B.SetInsertPoint(curElse);

            llvm::Value* eb = force_i1_condition(cg, eif->condition_, eif->location_, out, "elseif.cond");
            cg.B.CreateCondBr(eb, eifThen, eifNext);

            cg.B.SetInsertPoint(eifThen);
            if (eif->then_) emit_block(cg, *eif->then_, out);
            if (!cg.B.GetInsertBlock()->getTerminator())
                cg.B.CreateBr(endBB);

            curElse = eifNext;
        }

        // final else
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

        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(*cg.st.llctx, "while.cond", F);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(*cg.st.llctx, "while.body", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "while.end", F);

        cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(condBB);
        llvm::Value* cndB = force_i1_condition(cg, w.condition_, w.location_, out, "while.cond");
        cg.B.CreateCondBr(cndB, bodyBB, endBB);

        cg.B.SetInsertPoint(bodyBB);
        if (w.body_) emit_block(cg, *w.body_, out);
        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(endBB);
    }

    static void emit_do_while(FnCG& cg, ast::DoWhileStatement& d, Pass9_5Result& out)
    {
        llvm::Function* F = cg.F;

        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(*cg.st.llctx, "do.body", F);
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(*cg.st.llctx, "do.cond", F);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*cg.st.llctx, "do.end", F);

        cg.B.CreateBr(bodyBB);

        cg.B.SetInsertPoint(bodyBB);
        if (d.body_) emit_block(cg, *d.body_, out);
        if (!cg.B.GetInsertBlock()->getTerminator())
            cg.B.CreateBr(condBB);

        cg.B.SetInsertPoint(condBB);
        llvm::Value* cndB = force_i1_condition(cg, d.condition_, d.location_, out, "do.cond");
        cg.B.CreateCondBr(cndB, bodyBB, endBB);

        cg.B.SetInsertPoint(endBB);
    }

    static void emit_stmt(FnCG& cg, ast::Statement* s, Pass9_5Result& out)
    {
        if (!s) return;

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
            cg.arc_release_value_if_obj(v); // release if Obj*
            return;
        }

        push_diag(out, Pass9_5Diagnostic::Code::UnsupportedStmt, s->location_,
                  "unsupported statement in pass9.5");
    }

    // ============================================================
    // Prologue: entry block + alloc slots + store params
    // ============================================================

    static void clear_function_body(llvm::Function* F)
    {
        if (!F) return;

        // Drop references first to avoid use-after-free of instruction operands
        for (auto& BB : *F)
            BB.dropAllReferences();

        while (!F->empty())
            F->begin()->eraseFromParent();
    }

    static void build_prologue(FnCG& cg)
    {
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(*cg.st.llctx, "entry", cg.F);
        cg.B.SetInsertPoint(entry);

        const uint32_t nSlots = cg.binds ? cg.binds->slot_count : 0;
        cg.slot_alloca.assign(nSlots, nullptr);

        for (uint32_t i = 0; i < nSlots; ++i)
        {
            cg.slot_alloca[i] = cg.B.CreateAlloca(cg.st.obj_ptr_ty, nullptr, "slot");
            cg.B.CreateStore(null_obj(cg.st), cg.slot_alloca[i]);
        }

        // Function scope: holds params + any locals you want to live until function end.
        cg.scope_slots.clear();
        cg.scope_slots.push_back({});

        if (!cg.binds) return;

        // Store parameters into their bound slots using ARC barrier.
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
                stored = &arg;
            else if (arg.getType() == cg.st.i1_ty)
                stored = (cg.rt && cg.rt->rt_box_bool)
                             ? cg.B.CreateCall(cg.rt->rt_box_bool, {&arg}, "box.param.bool")
                             : null_obj(cg.st);
            else
                stored = null_obj(cg.st);

            if (si.slot.index < cg.slot_alloca.size() && cg.slot_alloca[si.slot.index])
            {
                // Track param slot in function scope so it is released at return/fallthrough.
                cg.scope_slots.back().push_back(si.slot);

                // ARC store (retain new, release old)
                cg.arc_store_slot(cg.slot_alloca[si.slot.index], stored);
            }
        }
    }


    // ============================================================
    // Main driver
    // ============================================================

    Pass9_5Result run_pass9_5_emit_bodies(Pass9_1Result& st,
                                          const Translation& tr,
                                          const Pass4Result& p4,
                                          const Pass4_5Result& p45,
                                          const Pass5Result& p5,
                                          const Pass6Result& p6,
                                          const Pass7Result& p7,
                                          const Pass8Result& p8,
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

            for (const auto& [fnid, binds] : mb.fns)
            {
                auto itF = st.fn_decls.find(fnid);
                if (itF == st.fn_decls.end() || !itF->second)
                {
                    push_diag(out,
                              Pass9_5Diagnostic::Code::MissingFnDeclInIR,
                              binds.decl ? binds.decl->location_ : lex::Loc{},
                              "function missing in IR (did you run pass9.2/pass9.3?)");
                    continue;
                }

                llvm::Function* F = itF->second;

                if (!binds.decl || !binds.decl->body_)
                {
                    push_diag(out,
                              Pass9_5Diagnostic::Code::MissingFnBody,
                              binds.decl ? binds.decl->location_ : lex::Loc{},
                              "missing function body for codegen (is this a load fn?)");
                    continue;
                }

                // Important: allow re-running pass9.5 without accumulating blocks.
                clear_function_body(F);

                FnCG cg(st, p5, p6, p7, p8, F, rt);
                cg.binds = &binds;

                build_prologue(cg);


                emit_block(cg, *binds.decl->body_, out);

                if (cg.B.GetInsertBlock() && !cg.B.GetInsertBlock()->getTerminator())
                {
                    while (!cg.scope_slots.empty())
                    {
                        cg.arc_release_scope(cg);
                        cg.scope_slots.pop_back();
                    }
                }

                // Ensure terminator
                if (!cg.B.GetInsertBlock()->getTerminator())
                {
                    llvm::Type* RT = F->getReturnType();
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
