#ifndef INZ_TYPES_HPP
#define INZ_TYPES_HPP

#include <variant>
#include <vector>

#include "ids.hpp"
#include "token.hpp"
#include "types.hpp"
#include "stmt/var_mutablity_storage.hpp"

namespace hir
{
    struct TypeBuiltin
    {
        kl::rt::BuiltinTypeExprKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypePath
    {
        ExprId path;
        std::vector<TypeId> targs;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypeRef
    {
        ast::Mutability mut;
        TypeId inner;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypeArray
    {
        TypeId elem;
        ExprId size;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    using TypeKind = std::variant<TypeBuiltin, TypePath, TypeRef, TypeArray>;

    struct Type
    {
        lex::Loc loc;
        TypeKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
