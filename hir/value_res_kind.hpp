//
// Created by yhwach on 12/28/25.
//

#ifndef INZ_VALUE_RES_KIND_HPP
#define INZ_VALUE_RES_KIND_HPP
#include <cstdint>

namespace hir
{
    using ValueResId = uint32_t;

    enum class ValueResKind : uint8_t { Unresolved, Local, Param, Def, Error, TypeName, LoadFn, Fn };
}

#endif //INZ_VALUE_RES_KIND_HPP
