// sema/pass9_2_declare_user_fns.hpp
#pragma once

// Inputs

// State from Pass 9.1

namespace sema
{
    struct Pass9_1Result;
    struct Pass9_1RuntimeDecls;
    Pass9_1RuntimeDecls& run_pass9_2_declare_runtime(Pass9_1Result& st);
} // namespace sema
