#include "pass9_7_ops.hpp"

#include <sstream>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include "module/module.hpp" // ast::Module (for pathExpr_->path_)

namespace sema
{
    // ------------------------------------------------------------
    // Logging helpers (module-path-first cluster head)
    // ------------------------------------------------------------
    static const std::vector<lex::SymId>& pass9_mod_path(const Pass9_1Result& st)
    {
        static const std::vector<lex::SymId> kEmpty{};
        if (st.log_mod && st.log_mod->pathExpr_)
            return st.log_mod->pathExpr_->path_;
        return kEmpty;
    }

    static void log_begin(LogSequence& seq, const Pass9_1Result& st, const lex::Loc& loc)
    {
        seq.emplace_back(LogPath{SymKind::Ident, pass9_mod_path(st), loc});
    }

    static void log_err(LogSequence& seq, const Pass9_1Result& st, const lex::Loc& loc, std::string msg)
    {
        log_begin(seq, st, loc);
        log_msg(seq, std::move(msg));
        // Anchor node for internal/runtime symbol errors (no SymId)
        seq.emplace_back(LogPath{SymKind::Ident, {}, loc});
    }

    // ------------------------------------------------------------
    // LLVM helpers (type-checked get-or-declare)
    // ------------------------------------------------------------
    static bool same_fty(const llvm::FunctionType* a, const llvm::FunctionType* b)
    {
        if (a == b) return true;
        if (!a || !b) return false;

        if (a->getReturnType() != b->getReturnType()) return false;
        if (a->isVarArg() != b->isVarArg()) return false;
        if (a->getNumParams() != b->getNumParams()) return false;

        for (unsigned i = 0; i < a->getNumParams(); ++i)
            if (a->getParamType(i) != b->getParamType(i))
                return false;

        return true;
    }

    static llvm::Function* get_or_declare_checked(Pass9_7Result& out,
                                                  Pass9_1Result& st,
                                                  llvm::FunctionType* FT,
                                                  llvm::StringRef name,
                                                  const lex::Loc& loc = {})
    {
        if (!st.module)
        {
            log_err(out.errors, st, loc, "pass9.7: internal: st.module is null");
            return nullptr;
        }

        llvm::Module& M = *st.module;

        if (auto* F = M.getFunction(name))
        {
            if (!same_fty(F->getFunctionType(), FT))
            {
                std::ostringstream oss;
                oss << "pass9.7: RuntimeOpTypeMismatch: symbol '" << name.str()
                    << "' already declared with different LLVM function type";
                log_err(out.errors, st, loc, oss.str());
                return nullptr;
            }
            return F;
        }

        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        if (!st.obj_ptr_ty) return nullptr;
        if (auto* PT = llvm::dyn_cast<llvm::PointerType>(st.obj_ptr_ty))
            return llvm::ConstantPointerNull::get(PT);
        return llvm::Constant::getNullValue(st.obj_ptr_ty);
    }

    // ------------------------------------------------------------
    // Pass 9.7: declare/check runtime ops
    // ------------------------------------------------------------
    Pass9_7Result run_pass9_7_rt_ops(Pass9_1Result& st)
    {
        Pass9_7Result out{};

        if (!st.llctx)
        {
            log_err(out.errors, st, lex::Loc{}, "pass9.7: MissingLLVMState: st.llctx is null");
            return out;
        }
        if (!st.module)
        {
            log_err(out.errors, st, lex::Loc{}, "pass9.7: MissingLLVMState: st.module is null");
            return out;
        }
        if (!st.obj_ptr_ty)
        {
            log_err(out.errors, st, lex::Loc{}, "pass9.7: MissingLLVMState: st.obj_ptr_ty is null");
            return out;
        }
        if (!st.i1_ty)
        {
            log_err(out.errors, st, lex::Loc{}, "pass9.7: MissingLLVMState: st.i1_ty (bool) is null");
            return out;
        }

        llvm::Type* Obj = st.obj_ptr_ty;
        llvm::IntegerType* I1 = st.i1_ty;

        auto* bin_obj = llvm::FunctionType::get(Obj, {Obj, Obj}, false);
        auto* un_obj  = llvm::FunctionType::get(Obj, {Obj}, false);
        auto* bin_i1  = llvm::FunctionType::get(I1,  {Obj, Obj}, false);

        // Prefer already-wired pointers from pass9.2, but still verify/declare by name.
        auto take_or_declare = [&](llvm::Function*& slot, llvm::FunctionType* FT, const char* name)
        {
            if (slot)
            {
                if (!same_fty(slot->getFunctionType(), FT))
                {
                    std::ostringstream oss;
                    oss << "pass9.7: RuntimeOpTypeMismatch: st.runtime." << name
                        << " has unexpected LLVM function type";
                    log_err(out.errors, st, lex::Loc{}, oss.str());
                    slot = nullptr;
                    return;
                }
                return;
            }

            slot = get_or_declare_checked(out, st, FT, name);
        };

        // NOTE: these names must match your runtime C ABI.
        take_or_declare(out.ops.add, bin_obj, "rt_add");
        take_or_declare(out.ops.sub, bin_obj, "rt_sub");
        take_or_declare(out.ops.mul, bin_obj, "rt_mul");
        take_or_declare(out.ops.div, bin_obj, "rt_div");
        take_or_declare(out.ops.mod, bin_obj, "rt_mod");
        take_or_declare(out.ops.neg, un_obj,  "rt_neg");

        take_or_declare(out.ops.eq, bin_i1, "rt_eq");
        take_or_declare(out.ops.ne, bin_i1, "rt_ne");
        take_or_declare(out.ops.lt, bin_i1, "rt_lt");
        take_or_declare(out.ops.gt, bin_i1, "rt_gt");
        take_or_declare(out.ops.le, bin_i1, "rt_le");
        take_or_declare(out.ops.ge, bin_i1, "rt_ge");

        return out;
    }

    // ------------------------------------------------------------
    // ABI coercion helpers (Obj* <-> i1)
    // ------------------------------------------------------------
    static llvm::Value* coerce_to_obj(Pass9_1Result& st, llvm::IRBuilder<>& B, llvm::Value* v)
    {
        if (!v) return null_obj(st);
        if (v->getType() == st.obj_ptr_ty) return v;

        if (v->getType() == st.i1_ty)
        {
            if (st.runtime.rt_box_bool)
                return B.CreateCall(st.runtime.rt_box_bool, {v}, "box.bool");
            return null_obj(st);
        }

        // Unknown -> null
        return null_obj(st);
    }

    static llvm::Value* coerce_to_i1(Pass9_1Result& st, llvm::IRBuilder<>& B, llvm::Value* v)
    {
        if (!st.llctx) return nullptr;
        if (!v) return llvm::ConstantInt::getFalse(*st.llctx);

        if (v->getType() == st.i1_ty) return v;

        if (v->getType() == st.obj_ptr_ty)
        {
            if (st.runtime.rt_unbox_bool)
                return B.CreateCall(st.runtime.rt_unbox_bool, {v}, "unbox.bool");
            return llvm::ConstantInt::getFalse(*st.llctx);
        }

        return llvm::ConstantInt::getFalse(*st.llctx);
    }

    // ------------------------------------------------------------
    // Short-circuit lowering (robust i1 coercion)
    // ------------------------------------------------------------
    static llvm::Value* emit_short_circuit_and(Pass9_1Result& st,
                                               llvm::IRBuilder<>& B,
                                               llvm::Function* cur_fn,
                                               ast::BinaryExpr& b,
                                               EmitExprFn emit_expr,
                                               void* emit_user)
    {
        if (!st.llctx || !cur_fn)
            return st.llctx ? llvm::ConstantInt::getFalse(*st.llctx) : nullptr;

        llvm::BasicBlock* curBB = B.GetInsertBlock();
        if (!curBB)
            return llvm::ConstantInt::getFalse(*st.llctx);

        llvm::Value* lhsV = emit_expr(emit_user, b.lhs_);
        llvm::Value* lhsB = coerce_to_i1(st, B, lhsV);

        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*st.llctx, "and.rhs", cur_fn);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*st.llctx, "and.end", cur_fn);

        B.CreateCondBr(lhsB, rhsBB, endBB);

        B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(emit_user, b.rhs_);
        llvm::Value* rhsB = coerce_to_i1(st, B, rhsV);
        B.CreateBr(endBB);

        B.SetInsertPoint(endBB);
        auto* phi = B.CreatePHI(st.i1_ty, 2, "and");
        phi->addIncoming(llvm::ConstantInt::getFalse(*st.llctx), curBB);
        phi->addIncoming(rhsB, rhsBB);
        return phi;
    }

    static llvm::Value* emit_short_circuit_or(Pass9_1Result& st,
                                              llvm::IRBuilder<>& B,
                                              llvm::Function* cur_fn,
                                              ast::BinaryExpr& b,
                                              EmitExprFn emit_expr,
                                              void* emit_user)
    {
        if (!st.llctx || !cur_fn)
            return st.llctx ? llvm::ConstantInt::getFalse(*st.llctx) : nullptr;

        llvm::BasicBlock* curBB = B.GetInsertBlock();
        if (!curBB)
            return llvm::ConstantInt::getFalse(*st.llctx);

        llvm::Value* lhsV = emit_expr(emit_user, b.lhs_);
        llvm::Value* lhsB = coerce_to_i1(st, B, lhsV);

        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*st.llctx, "or.rhs", cur_fn);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*st.llctx, "or.end", cur_fn);

        B.CreateCondBr(lhsB, endBB, rhsBB);

        B.SetInsertPoint(rhsBB);
        llvm::Value* rhsV = emit_expr(emit_user, b.rhs_);
        llvm::Value* rhsB = coerce_to_i1(st, B, rhsV);
        B.CreateBr(endBB);

        B.SetInsertPoint(endBB);
        auto* phi = B.CreatePHI(st.i1_ty, 2, "or");
        phi->addIncoming(llvm::ConstantInt::getTrue(*st.llctx), curBB);
        phi->addIncoming(rhsB, rhsBB);
        return phi;
    }

    // ------------------------------------------------------------
    // Helpers used by Pass9.5 (now take prepared ops)
    // ------------------------------------------------------------
    llvm::Value* emit_unary_expr(Pass9_1Result& st,
                                 llvm::IRBuilder<>& B,
                                 const Pass9_7RtOps& rt,
                                 ast::UnaryExpr& u,
                                 EmitExprFn emit_expr,
                                 void* emit_user)
    {
        if (!st.llctx || !st.obj_ptr_ty || !st.i1_ty)
            return null_obj(st);

        switch (u.op)
        {
        case ast::UnaryOp::negation:
        {
            llvm::Value* x = emit_expr(emit_user, u.expr_);
            llvm::Value* xObj = coerce_to_obj(st, B, x);
            if (!rt.neg) return null_obj(st);
            return B.CreateCall(rt.neg, {xObj}, "neg");
        }

        case ast::UnaryOp::logical_not:
        {
            llvm::Value* x = emit_expr(emit_user, u.expr_);
            llvm::Value* b = coerce_to_i1(st, B, x);
            return B.CreateNot(b, "not");
        }

        default:
            return null_obj(st);
        }
    }

    llvm::Value* emit_binary_expr(Pass9_1Result& st,
                                  llvm::IRBuilder<>& B,
                                  const Pass9_7RtOps& rt,
                                  llvm::Function* cur_fn,
                                  ast::BinaryExpr& b,
                                  EmitExprFn emit_expr,
                                  void* emit_user)
    {
        if (!st.llctx || !st.obj_ptr_ty || !st.i1_ty)
            return null_obj(st);

        switch (b.op)
        {
        // arithmetic: Obj* (Obj*,Obj*) -> Obj*
        case ast::BinaryOp::add:
        case ast::BinaryOp::subtract:
        case ast::BinaryOp::multiply:
        case ast::BinaryOp::divide:
        case ast::BinaryOp::modulo:
        {
            llvm::Function* callee = nullptr;
            const char* nm = "";

            switch (b.op)
            {
            case ast::BinaryOp::add:      callee = rt.add; nm = "add"; break;
            case ast::BinaryOp::subtract: callee = rt.sub; nm = "sub"; break;
            case ast::BinaryOp::multiply: callee = rt.mul; nm = "mul"; break;
            case ast::BinaryOp::divide:   callee = rt.div; nm = "div"; break;
            case ast::BinaryOp::modulo:   callee = rt.mod; nm = "mod"; break;
            default: break;
            }

            if (!callee) return null_obj(st);

            llvm::Value* L = coerce_to_obj(st, B, emit_expr(emit_user, b.lhs_));
            llvm::Value* R = coerce_to_obj(st, B, emit_expr(emit_user, b.rhs_));
            return B.CreateCall(callee, {L, R}, nm);
        }

        // logical short-circuit: i1
        case ast::BinaryOp::logical_and:
            return emit_short_circuit_and(st, B, cur_fn, b, emit_expr, emit_user);

        case ast::BinaryOp::logical_or:
            return emit_short_circuit_or(st, B, cur_fn, b, emit_expr, emit_user);

        // comparisons: i1 (Obj*,Obj*)
        case ast::BinaryOp::equal:
        case ast::BinaryOp::not_equal:
        case ast::BinaryOp::less:
        case ast::BinaryOp::greater:
        case ast::BinaryOp::less_equal:
        case ast::BinaryOp::greater_equal:
        {
            llvm::Function* callee = nullptr;
            const char* nm = "";

            switch (b.op)
            {
            case ast::BinaryOp::equal:          callee = rt.eq; nm = "eq"; break;
            case ast::BinaryOp::not_equal:      callee = rt.ne; nm = "ne"; break;
            case ast::BinaryOp::less:           callee = rt.lt; nm = "lt"; break;
            case ast::BinaryOp::greater:        callee = rt.gt; nm = "gt"; break;
            case ast::BinaryOp::less_equal:     callee = rt.le; nm = "le"; break;
            case ast::BinaryOp::greater_equal:  callee = rt.ge; nm = "ge"; break;
            default: break;
            }

            if (!callee) return llvm::ConstantInt::getFalse(*st.llctx);

            llvm::Value* L = coerce_to_obj(st, B, emit_expr(emit_user, b.lhs_));
            llvm::Value* R = coerce_to_obj(st, B, emit_expr(emit_user, b.rhs_));
            return B.CreateCall(callee, {L, R}, nm);
        }

        default:
            return null_obj(st);
        }
    }
} // namespace sema
