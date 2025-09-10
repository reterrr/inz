#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <token.hpp>

namespace ast {
    enum class BuiltinTy : uint8_t { Void, Int, BigInt, MagicInt, Double, Bool, String, Char };

    enum class TyKind : uint8_t { Builtin, Path, FixedArray, Slice, Ref, Callable, MagicInt, Struct };

    enum class TypeRegion : uint8_t { Auto, Static };

    enum class TypeSpecifier : uint8_t { Mut, Imm };

    struct Type {
        TyKind kind{};
        lex::Loc loc{};

        explicit Type(const TyKind k, const lex::Loc &L)
            : kind(k), loc(L) {
        }

        virtual ~Type() = default;
    };

    struct TypeWithQual {
        Type *ty{nullptr};
        TypeSpecifier spec{TypeSpecifier::Imm};
        TypeRegion region{TypeRegion::Auto};
        lex::Loc loc{};
    };

    struct BuiltinType final : Type {
        BuiltinTy which{};

        explicit BuiltinType(const BuiltinTy b, const lex::Loc &L)
            : Type(TyKind::Builtin, L), which(b) {
        }
    };

    struct PathType final : Type {
        std::vector<lex::SymId> segments;

        explicit PathType(std::vector<lex::SymId> segs, const lex::Loc &L)
            : Type(TyKind::Path, L), segments(std::move(segs)) {
        }
    };

    struct FixedArrayType final : Type {
        Type *elem;
        std::uint64_t length{0};

        FixedArrayType(Type *e, const std::uint64_t n, const lex::Loc &L)
            : Type(TyKind::FixedArray, L), elem(e), length(n) {
        }
    };

    struct SliceType final : Type {
        Type *elem;

        explicit SliceType(Type *e, const lex::Loc &L)
            : Type(TyKind::Slice, L), elem(e) {
        }
    };

    struct RefType final : Type {
        Type *pointee;

        RefType(Type *p, const lex::Loc &L)
            : Type(TyKind::Ref, L), pointee(p) {
        }
    };

    struct CallableType final : Type {
        std::vector<Type *> params;
        Type *ret;

        CallableType(std::vector<Type *> ps,
                     Type *r,
                     const lex::Loc &L)
            : Type(TyKind::Callable, L),
              params(std::move(ps)), ret(r) {
        }
    };

    struct MagicIntType final : Type {
        explicit MagicIntType(const lex::Loc &L)
            : Type(TyKind::MagicInt, L) {
        }
    };

    using StructType = PathType;
}
