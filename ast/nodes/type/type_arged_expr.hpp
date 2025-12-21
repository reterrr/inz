//
// Created by yhwach on 12/20/25.
//

#ifndef INZ_TYPE_ARGED_EXPR_HPP
#define INZ_TYPE_ARGED_EXPR_HPP
#include <algorithm>
#include <vector>

#include "expr/type_expr.hpp"

namespace ast
{
    struct TypeArgedExpr
    {
        enum class TypeArgedKind { PathType, Call };

        TypeArgedKind kind_;
        std::vector<TypeExpr*> typeArgs_;


        explicit TypeArgedExpr(TypeArgedKind kind,
                               std::vector<TypeExpr*>&& typeArgs,
                               Expr* parent)
            : kind_(kind), typeArgs_(std::move(typeArgs))
        {
            std::ranges::for_each(typeArgs_, [parent](Expr* expr)
            {
                expr->parent = parent;
            });
        }
    };
}

#endif //INZ_TYPE_ARGED_EXPR_HPP
