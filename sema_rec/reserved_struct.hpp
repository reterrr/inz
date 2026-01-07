//
// Created by yhwach on 1/3/26.
//

#ifndef INZ_RESERVED_STRUCT_HPP
#define INZ_RESERVED_STRUCT_HPP
#include "struct_decl.hpp"


namespace sema
{
    enum class ReservedStructFlags : uint16_t
    {
        None = 0,
        NoLit = 1 << 0,
    };

    inline ReservedStructFlags operator|(ReservedStructFlags a, ReservedStructFlags b)
    {
        return static_cast<ReservedStructFlags>(
            static_cast<uint16_t>(a) | static_cast<uint16_t>(b)
        );
    }

    inline ReservedStructFlags& operator|=(ReservedStructFlags& a, ReservedStructFlags b)
    {
        a = a | b;
        return a;
    }

    inline bool has_flag(ReservedStructFlags a, ReservedStructFlags b)
    {
        return (static_cast<uint16_t>(a) & static_cast<uint16_t>(b)) != 0;
    }

    struct ReservedStruct final
    {
        ast::StructDecl* decl = nullptr;
        ReservedStructFlags flags = ReservedStructFlags::None;
    };
}

#endif //INZ_RESERVED_STRUCT_HPP
