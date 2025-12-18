#ifndef AST_TYPE_HPP
#define AST_TYPE_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include <token.hpp>
#include <boost/container_hash/hash.hpp>

namespace ast
{
    enum class BuiltinTy : uint8_t { Void, Int, BigInt, MagicInt, Double, Bool, String, Char };

    enum class TyKind : uint8_t { Builtin, Path, FixedArray, Slice, Ref, Callable, MagicInt, Struct };

    enum class TypeRegion : uint8_t { Auto, Static };

    enum class TypeSpecifier : uint8_t { Mut, Imm };

    struct Type
    {
        TyKind kind{};
        lex::Loc loc{};
        TypeSpecifier specifier{TypeSpecifier::Imm};

        explicit Type(const TyKind k, const lex::Loc& L)
            : kind(k), loc(L)
        {
        }

        virtual ~Type() = default;

        virtual bool equals(const Type& other) const
        {
            return kind == other.kind;
        }

        virtual std::size_t hash() const
        {
            std::size_t h = 0;
            boost::hash_combine(h, static_cast<std::underlying_type_t<TyKind>>(kind));
            return h;
        }
    };

    struct BuiltinType final : Type
    {
        BuiltinTy which{};

        explicit BuiltinType(BuiltinTy b, const lex::Loc& L)
            : Type(TyKind::Builtin, L), which(b)
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::Builtin) return false;
            auto& o = static_cast<const BuiltinType&>(other);
            return which == o.which;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            boost::hash_combine(h, static_cast<std::underlying_type_t<BuiltinTy>>(which));
            return h;
        }
    };

    struct PathType final : Type
    {
        std::vector<lex::SymId> segments;

        explicit PathType(std::vector<lex::SymId> segs, const lex::Loc& L)
            : Type(TyKind::Path, L), segments(std::move(segs))
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::Path) return false;
            auto& o = static_cast<const PathType&>(other);
            return segments == o.segments;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            boost::hash_range(h, segments.begin(), segments.end());
            return h;
        }
    };

    struct FixedArrayType final : Type
    {
        Type* elem{};
        std::uint64_t length{0};

        FixedArrayType(Type* e, std::uint64_t n, const lex::Loc& L)
            : Type(TyKind::FixedArray, L), elem(e), length(n)
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::FixedArray) return false;
            auto& o = static_cast<const FixedArrayType&>(other);

            return elem == o.elem && length == o.length;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            boost::hash_combine(h, reinterpret_cast<std::uintptr_t>(elem));
            boost::hash_combine(h, length);
            return h;
        }
    };

    struct SliceType final : Type
    {
        Type* elem{};
        std::uint64_t capacity{0};
        std::uint64_t count{0};

        explicit SliceType(Type* e, const lex::Loc& L)
            : Type(TyKind::Slice, L), elem(e)
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::Slice) return false;
            auto& o = static_cast<const SliceType&>(other);
            return elem == o.elem && capacity == o.capacity && count == o.count;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            boost::hash_combine(h, reinterpret_cast<std::uintptr_t>(elem));
            boost::hash_combine(h, capacity);
            boost::hash_combine(h, count);
            return h;
        }
    };

    struct RefType final : Type
    {
        Type* pointee{};

        RefType(Type* p, const lex::Loc& L)
            : Type(TyKind::Ref, L), pointee(p)
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::Ref) return false;
            auto& o = static_cast<const RefType&>(other);
            return pointee == o.pointee;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            boost::hash_combine(h, reinterpret_cast<std::uintptr_t>(pointee));
            return h;
        }
    };

    struct CallableType final : Type
    {
        std::vector<Type*> params;
        Type* ret{};

        CallableType(std::vector<Type*> ps, Type* r, const lex::Loc& L)
            : Type(TyKind::Callable, L), params(std::move(ps)), ret(r)
        {
        }

        bool equals(const Type& other) const override
        {
            if (other.kind != TyKind::Callable) return false;
            auto& o = static_cast<const CallableType&>(other);
            return params == o.params && ret == o.ret;
        }

        std::size_t hash() const override
        {
            std::size_t h = Type::hash();
            for (auto* p : params)
                boost::hash_combine(h, reinterpret_cast<std::uintptr_t>(p));
            boost::hash_combine(h, reinterpret_cast<std::uintptr_t>(ret));
            return h;
        }
    };

    struct MagicIntType final : Type
    {
        explicit MagicIntType(const lex::Loc& L)
            : Type(TyKind::MagicInt, L)
        {
        }
    };

    using StructType = PathType;
}

#endif
