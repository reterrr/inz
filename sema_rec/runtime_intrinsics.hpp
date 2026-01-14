#pragma once

#include <cstdint>

namespace sema
{
    enum class RuntimeIntrinsic : std::uint8_t
    {
        box_new,
        box_free,
        box_len,
        box_get,
        box_set,
        print,
        put,
        nl
    };
} // namespace sema
