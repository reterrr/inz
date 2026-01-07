#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

#include "translation.hpp"         // lex::Loc, etc.
#include "pass9_1_bootstrap.hpp"   // Pass9_1Result

namespace sema
{
    struct Pass9_7Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            MissingLlvmContext,
            MissingLlvmModule,
            MissingObjPtrType,
            MissingBoolType,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

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
        std::vector<Pass9_7Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
    };

    // Pass 9.7: declare runtime ops prototypes (rt_add/rt_eq/rt_neg/...)
    Pass9_7Result run_pass9_7_rt_ops(Pass9_1Result& st);

    // Helpers used by Pass9.5
    using EmitExprFn = llvm::Value* (*)(void* user, ast::Expr* e);

    llvm::Value* emit_unary_expr(Pass9_1Result& st,
                                 llvm::IRBuilder<>& B,
                                 ast::UnaryExpr& u,
                                 EmitExprFn emit_expr,
                                 void* emit_user);

    llvm::Value* emit_binary_expr(Pass9_1Result& st,
                                  llvm::IRBuilder<>& B,
                                  llvm::Function* cur_fn,
                                  ast::BinaryExpr& b,
                                  EmitExprFn emit_expr,
                                  void* emit_user);
} // namespace sema
