#pragma once

namespace sema
{
    struct Pass9_1Result;
    struct Pass9_1RuntimeDecls;

    // Declares (and type-checks) all runtime functions into st.module
    // and stores llvm::Function* pointers into st.runtime.
    Pass9_1RuntimeDecls& run_pass9_2_declare_runtime(Pass9_1Result& st);
} // namespace sema
