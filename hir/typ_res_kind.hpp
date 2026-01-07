//
// Created by yhwach on 12/28/25.
//

#ifndef INZ_TYP_RES_KIND_HPP
#define INZ_TYP_RES_KIND_HPP
#include <cstdint>

namespace hir
{
    using TypeResId = uint32_t;

    enum class TypeResKind : uint8_t
    {
        Unresolved, Trait, Struct, TypeParam, Def, Error
    };
}
#endif //INZ_TYP_RES_KIND_HPP
