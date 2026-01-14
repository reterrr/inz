// ============================================================================
// pass7.hpp
// ============================================================================

#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#include "translation.hpp"

#include "expr/float_literal_expr.hpp"
#include "expr/int_literal_expr.hpp"

#include "pass4.hpp"
#include "pass5.hpp"
#include "pass6.hpp"
#include "pass_3.5.hpp"

struct CompilerContext;

namespace sema
{
    using I8   = kl::rt::i8;
    using I16  = kl::rt::i16;
    using I32  = kl::rt::i32;
    using I64  = kl::rt::i64;
    using I128 = kl::rt::i128;

    using U8   = kl::rt::u8;
    using U16  = kl::rt::u16;
    using U32  = kl::rt::u32;
    using U64  = kl::rt::u64;
    using U128 = kl::rt::u128;
    using CH   = kl::rt::character;

    using F32 = kl::rt::f32;
    using F64 = kl::rt::f64;

    using IntLitValue   = std::variant<I8, I16, I32, I64, I128, U8, U16, U32, U64, U128>;
    using FloatLitValue = std::variant<F32, F64>;
    using CharLitValue  = CH;

    struct FnSig
    {
        std::vector<TypeId> params;
        TypeId ret{UINT32_MAX};
        bool ok = false;

        std::vector<lex::SymId> type_params;
    };

    template <typename T>
    struct Pass7PtrHash final
    {
        size_t operator()(const T* p) const noexcept { return std::hash<const void*>{}(p); }
    };

    template <typename T>
    struct Pass7PtrEq final
    {
        bool operator()(const T* a, const T* b) const noexcept { return a == b; }
    };

    struct Pass7Result final
    {
        std::vector<IntLitValue> ints;
        std::vector<FloatLitValue> floats;
        std::vector<CharLitValue> chars;

        std::unordered_map<const ast::IntLiteralExpr*, std::uint32_t> int_id;
        std::unordered_map<const ast::FloatLiteralExpr*, std::uint32_t> float_id;
        std::unordered_map<const ast::CharLiteralExpr*, std::uint32_t> char_id;

        std::unordered_map<const ast::Expr*, TypeId, Pass7PtrHash<ast::Expr>, Pass7PtrEq<ast::Expr>> expr_type;

        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    Pass7Result run_pass7(const Translation& tr,
                          const CompilerContext& ctx,
                          const Pass4Result& p4,
                          Pass5Result& p5,
                          const Pass6Result& p6,
                          const Pass3_5Result* p3_5 = nullptr);
}
