// sema/pass11.hpp
#pragma once

#include "pass9_1_bootstrap.hpp"   // Pass9_1Result
#include "logging_entities.hpp"    // Log / LogPath / LogSequence
#include "compiler_context.hpp"    // for interning strings -> SymId (adjust include to your project)

namespace sema
{
    struct Pass11Result final
    {
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    // Pass 11:
    //  - verify IR produced by Pass9.* and runtime wiring
    //  - produce LogSequence errors that block codegen/run if invalid
    //
    // NOTE: we take CompilerContext to intern verifier subjects (function names, module names)
    // into SymId so "cause" can be logged as Ident/String path.
    Pass11Result run_pass11_verify_llvm_ir(const Pass9_1Result& st, CompilerContext& cc);
} // namespace sema
