//
// Created by yhwach on 8/16/25.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <variant>

#if defined(__SIZEOF_INT128__)
#define KL_HAS_NATIVE_INT128 1
#else
#define KL_HAS_NATIVE_INT128 0
#endif


#if !KL_HAS_NATIVE_INT128
#include <boost/multiprecision/cpp_int.hpp>
#endif

namespace kl::rt
{
    using i8 = std::int8_t;
    using u8 = std::uint8_t;
    using i16 = std::int16_t;
    using u16 = std::uint16_t;
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;

#if KL_HAS_NATIVE_INT128
    using i128 = __int128_t;
    using u128 = __uint128_t;
#else
    using i128 = boost::multiprecision::int128_t;
    using u128 = boost::multiprecision::uint128_t;
#endif

    using f32 = float;
    using f64 = double;

    using boolean = bool;
    using character = char32_t;

    using IntValue = std::variant<i8, u8, i16, u16, i32, u32, i64, u64, i128, u128>;
    using FloatValue = std::variant<f32, f64>;

    using string = std::string; // string are interned

    enum class BuiltinTypeExprKind
    {
        I8, U8,
        I16, U16,
        I32, U32,
        I64, U64,
        I128, U128,

        F32, F64,

        String,
        Array,
        Bool,
        Char,
        Struct,
    };

    enum class LiteralExprKind
    {
        Int,
        Float,
        String,
        Array,
        Bool,
        Char,
        Struct,
    };

    enum class IntKind
    {
        I8, U8,
        I16, U16,
        I32, U32,
        I64, U64,
        I128, U128,
    };

    enum class FloatKind
    {
        F32, F64
    };
}

#endif //TYPES_HPP
