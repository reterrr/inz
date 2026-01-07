// sema/pass11.hpp
#pragma once

#include <string>
#include <vector>

#include "pass9_1_bootstrap.hpp" // Pass9_1Result

namespace sema
{
    struct Pass11Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            LlvmFunctionVerifyFailed,
            LlvmModuleVerifyFailed,
        };

        Code code{};
        std::string subject;   // function name or "<module>"
        std::string message;   // verifier message
    };

    struct Pass11Result final
    {
        std::vector<Pass11Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    // Pass 11:
    //  - verify IR produced by Pass9.* and runtime wiring (Pass10)
    //  - produce diagnostics that block codegen/run if invalid
    Pass11Result run_pass11_verify_llvm_ir(const Pass9_1Result& st);
} // namespace sema
