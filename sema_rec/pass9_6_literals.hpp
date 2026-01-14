#pragma once

#include <llvm/IR/IRBuilder.h>

#include "logging_entities.hpp"       // LogSequence, LogPath, SymKind, log_msg, log_path/ident
#include "pass7.hpp"                  // Pass7Result, IntLitValue, FloatLitValue
#include "pass9_1_bootstrap.hpp"      // Pass9_1Result
#include "module/module.hpp"          // ast::Module (for pathExpr_)

namespace sema
{
    struct Pass9_6RtCtors final
    {
        llvm::Function* int_i64  = nullptr; // Obj* rt_int_from_i64(i64)
        llvm::Function* int_u64  = nullptr; // Obj* rt_int_from_u64(i64)
        llvm::Function* int_i128 = nullptr; // Obj* rt_int_from_i128(i128)
        llvm::Function* int_u128 = nullptr; // Obj* rt_int_from_u128(i128)

        llvm::Function* f32 = nullptr; // Obj* rt_float_from_f32(float)
        llvm::Function* f64 = nullptr; // Obj* rt_float_from_f64(double)
    };

    struct Pass9_6Result final
    {
        Pass9_6RtCtors ctors{};
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    // Declares (or reuses) ctor symbols in st.module, BUT verifies their LLVM types match.
    // Logs errors in the required cluster format (module path first).
    Pass9_6Result run_pass9_6_prepare(Pass9_1Result& st);

    // Returns boxed Obj* for the literal, or null Obj* if missing Pass7 entry or missing ctor.
    // These helpers do NOT do declaration. Call run_pass9_6_prepare once and pass ctors in.
    llvm::Value* emit_int_literal_obj(Pass9_1Result& st,
                                      llvm::IRBuilder<>& B,
                                      const Pass7Result& p7,
                                      const ast::IntLiteralExpr& lit,
                                      const Pass9_6RtCtors& rt);

    llvm::Value* emit_float_literal_obj(Pass9_1Result& st,
                                        llvm::IRBuilder<>& B,
                                        const Pass7Result& p7,
                                        const ast::FloatLiteralExpr& lit,
                                        const Pass9_6RtCtors& rt);
} // namespace sema
