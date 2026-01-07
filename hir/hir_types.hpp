#ifndef INZ_TYPES_HPP
#define INZ_TYPES_HPP

#include <variant>
#include <vector>

#include "ids.hpp"
#include "token.hpp"
#include "types.hpp"
#include "typ_res_kind.hpp"
#include "stmt/var_mutablity_storage.hpp"

namespace hir
{
    struct TypeRes
    {
        TypeResKind kind;
        TypeResId id;
        ModuleId module;
    };

    struct TypeBuiltin
    {
        kl::rt::BuiltinTypeExprKind kind;
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypeBox
    {
        TypeId inner;
        //shouldnt we place holder object here
        lex::Loc loc;
    };

    struct TypeStr
    {
        //shouldnt we place holder object here
        lex::Loc loc;
    };

    struct TypeVec
    {
        TypeId inner;
        //shouldnt we place holder object here
        lex::Loc loc;
    };

    struct TypePath
    {
        ExprId path;
        std::vector<TypeId> targs;
        lex::Loc loc;

        TypeRes res{};

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
        lex::Loc loc;

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
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    using TypeKind = std::variant<TypeBuiltin, TypePath, TypeRef, TypeArray>;

    struct Type
    {
        TypeKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
