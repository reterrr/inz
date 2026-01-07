#pragma once

#include <llvm/IR/IRBuilder.h>

#include "pass7.hpp"              // Pass7Result, IntLitValue, FloatLitValue
#include "pass9_1_bootstrap.hpp"  // Pass9_1Result (llctx, module, obj_ptr_ty, i64_ty, etc.)

namespace sema
{
    struct Pass9_6RtCtors final
    {
        llvm::Function* int_i64 = nullptr; // Obj* rt_int_from_i64(i64)
        llvm::Function* int_u64 = nullptr; // Obj* rt_int_from_u64(i64)
        llvm::Function* int_i128 = nullptr; // Obj* rt_int_from_i128(i128)
        llvm::Function* int_u128 = nullptr; // Obj* rt_int_from_u128(i128)

        llvm::Function* f32 = nullptr; // Obj* rt_float_from_f32(float)
        llvm::Function* f64 = nullptr; // Obj* rt_float_from_f64(double)
    };

    struct Pass9_6Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            MissingLLVMState, // st.llctx or st.module is null
        };

        Code code{};
        lex::Loc loc{}; // no source loc -> keep default
        std::string message;
    };

    struct Pass9_6Result final
    {
        Pass9_6RtCtors ctors{};
        std::vector<Pass9_6Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    Pass9_6Result run_pass9_6_prepare(Pass9_1Result& st);

    // Returns Obj* for the literal (boxed), or null Obj* if missing Pass7 entry.
    llvm::Value* emit_int_literal_obj(Pass9_1Result& st,
                                      llvm::IRBuilder<>& B,
                                      const Pass7Result& p7,
                                      const ast::IntLiteralExpr& lit);

    // Returns Obj* for the literal (boxed), or null Obj* if missing Pass7 entry.
    llvm::Value* emit_float_literal_obj(Pass9_1Result& st,
                                        llvm::IRBuilder<>& B,
                                        const Pass7Result& p7,
                                        const ast::FloatLiteralExpr& lit);
} // namespace sema
