#pragma once
#include <string>
#include <vector>
#include "pass9_1_bootstrap.hpp"
#include "pass2.hpp"
#include "pass5.hpp"
#include "compiler_context.hpp"

namespace sema
{
    struct Pass9_3Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            DuplicateLlvmFunctionName,
            LlvmFunctionTypeMismatch,
            DuplicateEntrypoint,
            MissingEntrypoint,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass9_3Result final
    {
        std::vector<Pass9_3Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    Pass9_3Result run_pass9_3_declare_user_and_load_fns(Pass9_1Result& st,
                                                        const Pass2Result& p2,
                                                        const Pass4Result& p4,
                                                        const Pass5Result& p5,
                                                        CompilerContext& ctx,
                                                        lex::SymId entrypoint);
}
