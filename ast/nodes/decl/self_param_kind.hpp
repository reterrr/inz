//
// Created by yhwach on 12/26/25.
//

#ifndef INZ_SELF_PARAM_KIND_HPP
#define INZ_SELF_PARAM_KIND_HPP
#include <cstdint>

namespace ast
{
    enum class SelfParamKind : uint8_t
    {
        Value, // self
        Ref, // &self
        RefMut // &mut self
    };
}

#endif //INZ_SELF_PARAM_KIND_HPP
