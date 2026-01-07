#include "pass9_7_ops.hpp"

#include <cassert>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

namespace sema
{
    static void push_diag(Pass9_7Result& out,
                          Pass9_7Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        out.diagnostics.push_back(Pass9_7Diagnostic{
            .code = c,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    static llvm::Function* get_or_declare(llvm::Module& M,
                                          llvm::FunctionType* FT,
                                          llvm::StringRef name)
    {
        if (auto* F = M.getFunction(name))
            return F;
        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        if (!st.obj_ptr_ty) return nullptr;
        if (auto* PT = llvm::dyn_cast<llvm::PointerType>(st.obj_ptr_ty))
            return llvm::ConstantPointerNull::get(PT);
        return llvm::Constant::getNullValue(st.obj_ptr_ty);
    }

    // Declare once, reuse thereafter (Module::getFunction prevents duplicates).
    static Pass9_7RtOps ensure_rt_ops(Pass9_1Result& st)
    {
        llvm::Module& M = *st.module;

        Pass9_7RtOps rt{};

        auto* obj = st.obj_ptr_ty;
        auto* i1  = st.i1_ty;

        // Obj* (Obj*, Obj*) -> Obj*
        auto* bin_obj = llvm::FunctionType::get(obj, {obj, obj}, false);
        rt.add = get_or_declare(M, bin_obj, "rt_add");
        rt.sub = get_or_declare(M, bin_obj, "rt_sub");
        rt.mul = get_or_declare(M, bin_obj, "rt_mul");
        rt.div = get_or_declare(M, bin_obj, "rt_div");
        rt.mod = get_or_declare(M, bin_obj, "rt_mod");

        // Obj* (Obj*) -> Obj*
        auto* un_obj = llvm::FunctionType::get(obj, {obj}, false);
        rt.neg = get_or_declare(M, un_obj, "rt_neg");

        // i1 (Obj*, Obj*)
        auto* bin_i1 = llvm::FunctionType::get(i1, {obj, obj}, false);
        rt.eq = get_or_declare(M, bin_i1, "rt_eq");
        rt.ne = get_or_declare(M, bin_i1, "rt_ne");
        rt.lt = get_or_declare(M, bin_i1, "rt_lt");
        rt.gt = get_or_declare(M, bin_i1, "rt_gt");
        rt.le = get_or_declare(M, bin_i1, "rt_le");
        rt.ge = get_or_declare(M, bin_i1, "rt_ge");

        return rt;
    }

    Pass9_7Result run_pass9_7_rt_ops(Pass9_1Result& st)
    {
        Pass9_7Result out{};

        if (!st.llctx)
        {
            push_diag(out, Pass9_7Diagnostic::Code::MissingLlvmContext, lex::Loc{},
                      "Pass9.7 requires Pass9.1 to provide llctx");
            return out;
        }

        if (!st.module)
        {
            push_diag(out, Pass9_7Diagnostic::Code::MissingLlvmModule, lex::Loc{},
                      "Pass9.7 requires Pass9.1 to provide module");
            return out;
        }

        if (!st.obj_ptr_ty)
        {
            push_diag(out, Pass9_7Diagnostic::Code::MissingObjPtrType, lex::Loc{},
                      "Pass9.7 requires Pass9.1 to provide obj_ptr_ty");
            return out;
        }

        if (!st.i1_ty)
        {
            push_diag(out, Pass9_7Diagnostic::Code::MissingBoolType, lex::Loc{},
                      "Pass9.7 requires Pass9.1 to provide i1_ty");
            return out;
        }

        out.ops = ensure_rt_ops(st);
        return out;
    }

    // -------------------------------
    // Helpers (used by Pass9.5)
    // -------------------------------

    llvm::Value* emit_unary_expr(Pass9_1Result& st,
                                 llvm::IRBuilder<>& B,
                                 ast::UnaryExpr& u,
                                 EmitExprFn emit_expr,
                                 void* emit_user)
    {
        // No diagnostics here; Pass9.7 already validated state.
        if (!st.module || !st.i1_ty || !st.obj_ptr_ty || !st.llctx)
            return null_obj(st);

        const Pass9_7RtOps rt = ensure_rt_ops(st);

        switch (u.op)
        {
        case ast::UnaryOp::negation:
        {
            llvm::Value* x = emit_expr(emit_user, u.expr_);
            if (!x) return null_obj(st);
            return B.CreateCall(rt.neg, {x}, "neg");
        }

        case ast::UnaryOp::logical_not:
        {
            llvm::Value* x = emit_expr(emit_user, u.expr_);

            // strict mode: if not i1, treat as false
            llvm::Value* b = (x && x->getType() == st.i1_ty)
                                 ? x
                                 : llvm::ConstantInt::getFalse(*st.llctx);

            return B.CreateNot(b, "not");
        }

        // Not implemented yet:
        case ast::UnaryOp::preincrement:
        case ast::UnaryOp::predecrement:
        case ast::UnaryOp::postincrement:
        case ast::UnaryOp::postdecrement:
        case ast::UnaryOp::deref:
        default:
            return null_obj(st);
        }
    }

    static llvm::Value* emit_short_circuit_and(Pass9_1Result& st,
                                               llvm::IRBuilder<>& B,
                                               llvm::Function* cur_fn,
                                               ast::BinaryExpr& b,
                                               EmitExprFn emit_expr,
                                               void* emit_user)
    {
        if (!st.llctx) return nullptr;
        if (!cur_fn)   return llvm::ConstantInt::getFalse(*st.llctx);

        llvm::Value* lhs = emit_expr(emit_user, b.lhs_);
        if (!lhs || lhs->getType() != st.i1_ty)
            lhs = llvm::ConstantInt::getFalse(*st.llctx);

        llvm::BasicBlock* curBB = B.GetInsertBlock();
        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*st.llctx, "and.rhs", cur_fn);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*st.llctx, "and.end", cur_fn);

        B.CreateCondBr(lhs, rhsBB, endBB);

        B.SetInsertPoint(rhsBB);
        llvm::Value* rhs = emit_expr(emit_user, b.rhs_);
        if (!rhs || rhs->getType() != st.i1_ty)
            rhs = llvm::ConstantInt::getFalse(*st.llctx);
        B.CreateBr(endBB);

        B.SetInsertPoint(endBB);
        auto* phi = B.CreatePHI(st.i1_ty, 2, "and.phi");
        phi->addIncoming(llvm::ConstantInt::getFalse(*st.llctx), curBB);
        phi->addIncoming(rhs, rhsBB);
        return phi;
    }

    static llvm::Value* emit_short_circuit_or(Pass9_1Result& st,
                                              llvm::IRBuilder<>& B,
                                              llvm::Function* cur_fn,
                                              ast::BinaryExpr& b,
                                              EmitExprFn emit_expr,
                                              void* emit_user)
    {
        if (!st.llctx) return nullptr;
        if (!cur_fn)   return llvm::ConstantInt::getFalse(*st.llctx);

        llvm::Value* lhs = emit_expr(emit_user, b.lhs_);
        if (!lhs || lhs->getType() != st.i1_ty)
            lhs = llvm::ConstantInt::getFalse(*st.llctx);

        llvm::BasicBlock* curBB = B.GetInsertBlock();
        llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*st.llctx, "or.rhs", cur_fn);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(*st.llctx, "or.end", cur_fn);

        B.CreateCondBr(lhs, endBB, rhsBB);

        B.SetInsertPoint(rhsBB);
        llvm::Value* rhs = emit_expr(emit_user, b.rhs_);
        if (!rhs || rhs->getType() != st.i1_ty)
            rhs = llvm::ConstantInt::getFalse(*st.llctx);
        B.CreateBr(endBB);

        B.SetInsertPoint(endBB);
        auto* phi = B.CreatePHI(st.i1_ty, 2, "or.phi");
        phi->addIncoming(llvm::ConstantInt::getTrue(*st.llctx), curBB);
        phi->addIncoming(rhs, rhsBB);
        return phi;
    }

    llvm::Value* emit_binary_expr(Pass9_1Result& st,
                                  llvm::IRBuilder<>& B,
                                  llvm::Function* cur_fn,
                                  ast::BinaryExpr& b,
                                  EmitExprFn emit_expr,
                                  void* emit_user)
    {
        if (!st.module || !st.i1_ty || !st.obj_ptr_ty || !st.llctx)
            return null_obj(st);

        const Pass9_7RtOps rt = ensure_rt_ops(st);

        switch (b.op)
        {
        // arithmetic: Obj* -> Obj*
        case ast::BinaryOp::add:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return null_obj(st);
            return B.CreateCall(rt.add, {L, R}, "add");
        }
        case ast::BinaryOp::subtract:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return null_obj(st);
            return B.CreateCall(rt.sub, {L, R}, "sub");
        }
        case ast::BinaryOp::multiply:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return null_obj(st);
            return B.CreateCall(rt.mul, {L, R}, "mul");
        }
        case ast::BinaryOp::divide:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return null_obj(st);
            return B.CreateCall(rt.div, {L, R}, "div");
        }
        case ast::BinaryOp::modulo:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return null_obj(st);
            return B.CreateCall(rt.mod, {L, R}, "mod");
        }

        // logical short-circuit: i1
        case ast::BinaryOp::logical_and:
            return emit_short_circuit_and(st, B, cur_fn, b, emit_expr, emit_user);

        case ast::BinaryOp::logical_or:
            return emit_short_circuit_or(st, B, cur_fn, b, emit_expr, emit_user);

        // comparisons: Obj* -> i1
        case ast::BinaryOp::equal:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.eq, {L, R}, "eq");
        }
        case ast::BinaryOp::not_equal:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.ne, {L, R}, "ne");
        }
        case ast::BinaryOp::less:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.lt, {L, R}, "lt");
        }
        case ast::BinaryOp::greater:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.gt, {L, R}, "gt");
        }
        case ast::BinaryOp::less_equal:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.le, {L, R}, "le");
        }
        case ast::BinaryOp::greater_equal:
        {
            llvm::Value* L = emit_expr(emit_user, b.lhs_);
            llvm::Value* R = emit_expr(emit_user, b.rhs_);
            if (!L || !R) return llvm::ConstantInt::getFalse(*st.llctx);
            return B.CreateCall(rt.ge, {L, R}, "ge");
        }

        default:
            return null_obj(st);
        }
    }

} // namespace sema
