#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

#include "translation.hpp"         // lex::Loc
#include "pass9_1_bootstrap.hpp"   // Pass9_1Result (includes st.runtime)
#include "logging_entities.hpp"    // LogSequence, LogPath, SymKind, log_msg

namespace sema
{
    struct Pass9_7RtOps final
    {
        // Obj* ops
        llvm::Function* add = nullptr;
        llvm::Function* sub = nullptr;
        llvm::Function* mul = nullptr;
        llvm::Function* div = nullptr;
        llvm::Function* mod = nullptr;
        llvm::Function* neg = nullptr;

        // i1 comparisons
        llvm::Function* eq  = nullptr;
        llvm::Function* ne  = nullptr;
        llvm::Function* lt  = nullptr;
        llvm::Function* gt  = nullptr;
        llvm::Function* le  = nullptr;
        llvm::Function* ge  = nullptr;
    };

    struct Pass9_7Result final
    {
        Pass9_7RtOps ops{};
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    // Pass 9.7: declare/check runtime ops prototypes (rt_add/rt_eq/rt_neg/...)
    // Logs errors in the required cluster format (module path first).
    Pass9_7Result run_pass9_7_rt_ops(Pass9_1Result& st);

    // Helpers used by Pass9.5
    using EmitExprFn = llvm::Value* (*)(void* user, ast::Expr* e);

    llvm::Value* emit_unary_expr(Pass9_1Result& st,
                                 llvm::IRBuilder<>& B,
                                 const Pass9_7RtOps& rt,
                                 ast::UnaryExpr& u,
                                 EmitExprFn emit_expr,
                                 void* emit_user);

    llvm::Value* emit_binary_expr(Pass9_1Result& st,
                                  llvm::IRBuilder<>& B,
                                  const Pass9_7RtOps& rt,
                                  llvm::Function* cur_fn,
                                  ast::BinaryExpr& b,
                                  EmitExprFn emit_expr,
                                  void* emit_user);
} // namespace sema
