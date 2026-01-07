#pragma once
#include <string>
#include <vector>

#include "token.hpp"


namespace sema
{
    struct Pass9_1Result;

    struct Pass12Diagnostic final
    {
        enum class Code : uint8_t
        {
            MissingEntrySymbol,
            JitCreateFailed,
            ExternalSymbolMissing,
            ExternalSymbolDefineFailed,
            AddModuleFailed,
            LookupFailed,
            InvokeFailed,
            OwnershipError,
            MissingExternalSymbol,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass12Result final
    {
        std::vector<Pass12Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    // Executes the LLVM module contained in pass9_1 using ORC LLJIT.
    // IMPORTANT: This pass moves pass9_1.module and pass9_1.llctx into the JIT.
    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    std::string entry_symbol,
                                    bool make_wrapper_if_needed = true,
                                    std::string wrapper_name = "__kl_entry");
}
