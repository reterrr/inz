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
    };

    struct TypePath
    {
        ExprId path;
        std::vector<TypeId> targs;
    };

    struct TypeRef
    {
        ast::Mutability mut;
        TypeId inner;
    };

    struct TypeArray
    {
        TypeId elem;
        ExprId size;
    };

    using TypeKind = std::variant<TypeBuiltin, TypePath, TypeRef, TypeArray>;

    struct Type
    {
        lex::Loc loc;
        TypeKind kind;
    };
}

#endif
