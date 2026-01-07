#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include <llvm/IR/IRBuilder.h>

#include "translation.hpp"

// AST

#include "expr/ref_expr.hpp"

// Inputs
#include "pass4.hpp"
#include "pass5.hpp"
#include "pass6.hpp"
#include "pass7.hpp"
#include "pass8.hpp"

// Pass 9 state from 9.1/9.2/9.3
#include "pass9_1_bootstrap.hpp"

namespace sema
{
    struct Pass10Runtime;

    // Minimal tag set for codegen decisions.
    enum class ValueTag : uint8_t
    {
        Obj, // Obj*
        Bool, // i1
        Void // void
    };

    // You said pass 8 is "1 i1, 2 no, 3 bool" — this is the minimal interface Pass9.5 needs:

    struct Pass9_5Diagnostic final
    {
        enum class Code : uint8_t
        {
            MissingFnBody,
            MissingFnDeclInIR,
            MissingBindingsForFn,
            UnsupportedStmt,
            UnsupportedExpr,
            MissingRefBinding,
            InvalidCallCallee,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass9_5Result final
    {
        std::vector<Pass9_5Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    struct Pass9_5Options final
    {
        bool dynamic_abi = true; // you are using dynamic Obj* ABI except bool/void
    };

    Pass9_5Result run_pass9_5_emit_bodies(Pass9_1Result& st,
                                          const Translation& tr,
                                          const Pass4Result& p4,
                                          const Pass4_5Result& p45,
                                          const Pass5Result& p5,
                                          const Pass6Result& p6,
                                          const Pass7Result& p7,
                                          const Pass8Result& p8,
                                          const Pass9_1RuntimeDecls& p10);
} // namespace sema
