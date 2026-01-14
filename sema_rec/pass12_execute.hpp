// pass12_execute.hpp
#pragma once

#include <string>
#include <vector>

#include "logging_entities.hpp" // Log / LogPath / LogSequence
#include "compiler_context.hpp" // CompilerContext (for interning SymId)

namespace sema
{
    struct Pass9_1Result;

    struct Pass12Result final
    {
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    // Executes the LLVM module contained in pass9_1 using ORC LLJIT.
    // IMPORTANT: This pass moves pass9_1.module and pass9_1.llctx into the JIT.
    //
    // NOTE: CompilerContext is required to intern "cause" symbols (entry name, extern names, etc.)
    // into lex::SymId for Log / LogPath.
    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    CompilerContext& cc,
                                    std::string entry_symbol,
                                    bool make_wrapper_if_needed = true,
                                    std::string wrapper_name = "__kl_entry");

    // Same as above, but also loads shared libraries into the current process BEFORE resolving externs.
    // This makes declarations created as:
    //   llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    // resolvable via llvm::sys::DynamicLibrary::SearchForAddressOfSymbol(name).
    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    CompilerContext& cc,
                                    std::string entry_symbol,
                                    const std::vector<std::string>& shared_libs,
                                    bool make_wrapper_if_needed = true,
                                    std::string wrapper_name = "__kl_entry");
} // namespace sema
