// sema/pass9_3.hpp
#pragma once

#include "logging_entities.hpp" // LogSequence, LogPath, Log, SymKind

#include "pass9_1_bootstrap.hpp"
#include "pass2.hpp"
#include "pass5.hpp"

namespace sema
{
    struct Pass9_3Result final
    {
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    // Declares:
    //  - all user functions (mangled; entrypoint uses stable public IR name)
    //  - all load-fns (externals by their declared name)
    //
    // Fills:
    //  - st.fn_decls
    //  - st.load_fn_decls
    Pass9_3Result run_pass9_3_declare_user_and_load_fns(Pass9_1Result& st,
                                                        const Pass2Result& p2,
                                                        const Pass4Result& p4,
                                                        const Pass5Result& p5,
                                                        CompilerContext& ctx,
                                                        lex::SymId entrypoint);
} // namespace sema
