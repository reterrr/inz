#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <string>
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

    // Strings are interned (you store SymId elsewhere). This is just the runtime representation.
    using string = std::string;

    // =========================================================================
    // Numeric kind enums (used by both builtin numeric types and numeric literals)
    // =========================================================================

    enum class IntKind : std::uint8_t
    {
        I8, U8,
        I16, U16,
        I32, U32,
        I64, U64,
        I128, U128,
    };

    enum class FloatKind : std::uint8_t
    {
        F32, F64
    };

    // =========================================================================
    // Builtin types (ONLY the concrete, primitive types in the language)
    //
    // IMPORTANT: do NOT put "Array" or "Struct" here:
    // - array is a type constructor handled by ArrayTypeExpr
    // - struct is a nominal/user-defined type referenced by PathTypeExpr/PathType
    // =========================================================================

    enum class BuiltinTypeKind : std::uint8_t
    {
        // integers
        I8, U8,
        I16, U16,
        I32, U32,
        I64, U64,
        I128, U128,

        // floats
        F32, F64,

        // other primitives
        Bool,
        Char,
        String,
    };

    // Keep your old name if parser/AST already uses it:
    using BuiltinTypeExprKind = BuiltinTypeKind;

    // =========================================================================
    // Literal node categories (AST-level, not type-level)
    //
    // "Array" and "Struct" are valid here if you have ArrayLiteralExpr/StructLiteralExpr.
    // =========================================================================

    enum class LiteralKind : std::uint8_t
    {
        Int,
        Float,
        String,
        Bool,
        Char,
        Array,
        Struct,
    };

    // Keep old name if already used widely:
    using LiteralExprKind = LiteralKind;

    // =========================================================================
    // Helpers (optional but highly recommended)
    // =========================================================================

    [[nodiscard]] constexpr bool is_int(BuiltinTypeKind k) noexcept
    {
        switch (k)
        {
        case BuiltinTypeKind::I8:
        case BuiltinTypeKind::U8:
        case BuiltinTypeKind::I16:
        case BuiltinTypeKind::U16:
        case BuiltinTypeKind::I32:
        case BuiltinTypeKind::U32:
        case BuiltinTypeKind::I64:
        case BuiltinTypeKind::U64:
        case BuiltinTypeKind::I128:
        case BuiltinTypeKind::U128:
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] constexpr bool is_float(BuiltinTypeKind k) noexcept
    {
        return k == BuiltinTypeKind::F32 || k == BuiltinTypeKind::F64;
    }

    [[nodiscard]] constexpr bool is_signed(IntKind k) noexcept
    {
        switch (k)
        {
        case IntKind::I8:
        case IntKind::I16:
        case IntKind::I32:
        case IntKind::I64:
        case IntKind::I128:
            return true;
        default:
            return false;
        }
    }

    [[nodiscard]] constexpr int bit_width(IntKind k) noexcept
    {
        switch (k)
        {
        case IntKind::I8:
        case IntKind::U8: return 8;
        case IntKind::I16:
        case IntKind::U16: return 16;
        case IntKind::I32:
        case IntKind::U32: return 32;
        case IntKind::I64:
        case IntKind::U64: return 64;
        case IntKind::I128:
        case IntKind::U128: return 128;
        }
        return 0;
    }

    [[nodiscard]] constexpr BuiltinTypeKind to_builtin(IntKind k) noexcept
    {
        switch (k)
        {
        case IntKind::I8: return BuiltinTypeKind::I8;
        case IntKind::U8: return BuiltinTypeKind::U8;
        case IntKind::I16: return BuiltinTypeKind::I16;
        case IntKind::U16: return BuiltinTypeKind::U16;
        case IntKind::I32: return BuiltinTypeKind::I32;
        case IntKind::U32: return BuiltinTypeKind::U32;
        case IntKind::I64: return BuiltinTypeKind::I64;
        case IntKind::U64: return BuiltinTypeKind::U64;
        case IntKind::I128: return BuiltinTypeKind::I128;
        case IntKind::U128: return BuiltinTypeKind::U128;
        }
        return BuiltinTypeKind::I32; // fallback; should never happen if switch is exhaustive
    }

    [[nodiscard]] constexpr BuiltinTypeKind to_builtin(FloatKind k) noexcept
    {
        switch (k)
        {
        case FloatKind::F32: return BuiltinTypeKind::F32;
        case FloatKind::F64: return BuiltinTypeKind::F64;
        }
        return BuiltinTypeKind::F64;
    }

    constexpr const char* builtin_kind_name(BuiltinTypeExprKind k)
    {
        using K = BuiltinTypeExprKind;
        switch (k)
        {
        case K::I8: return "i8";
        case K::U8: return "u8";
        case K::I16: return "i16";
        case K::U16: return "u16";
        case K::I32: return "i32";
        case K::U32: return "u32";
        case K::I64: return "i64";
        case K::U64: return "u64";
        case K::I128: return "i128";
        case K::U128: return "u128";
        case K::F32: return "f32";
        case K::F64: return "f64";
        case K::Bool: return "bool";
        case K::Char: return "char";
        case K::String: return "string";
        }
        return "<?>";
    }
}

#endif // TYPES_HPP
