// sema/pass9_5_codegen_bodies.hpp
#pragma once

#include <cstdint>

#include "translation.hpp"

// Inputs
#include "pass4.hpp"
#include "pass5.hpp"
#include "pass6.hpp"
#include "pass7.hpp"
#include "pass8.hpp"

// Pass 9 state from 9.1/9.2/9.3
#include "pass9_1_bootstrap.hpp"

// Project logging API
#include "logging_entities.hpp"

namespace sema
{
    // Minimal tag set for codegen decisions.
    enum class ValueTag : std::uint8_t
    {
        Obj,   // Obj*
        Bool,  // i1
        Void   // void
    };

    struct Pass9_5Result final
    {
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    struct Pass9_5Options final
    {
        bool dynamic_abi = true; // dynamic Obj* ABI except bool/void
    };

    Pass9_5Result run_pass9_5_emit_bodies(Pass9_1Result& st,
                                          const Translation& tr,
                                          const Pass4Result& p4,
                                          const Pass4_5Result& p45,
                                          const Pass5Result& p5,
                                          const Pass6Result& p6,
                                          const Pass7Result& p7,
                                          const Pass8Result& p8,
                                          const Pass9_1RuntimeDecls& rt);
} // namespace sema
