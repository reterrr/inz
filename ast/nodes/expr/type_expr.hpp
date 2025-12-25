//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_TYPE_EXPR_HPP
#define INZ_TYPE_EXPR_HPP

#include "expr.hpp"
#include "type_expr_kind.hpp"

namespace ast
{
    struct TypeExpr : Expr
    {
        TypeExprKind kind_;

        TypeExpr(TypeExprKind kind, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Type, loc), kind_(kind)
        {
        }
    };
}

#endif //INZ_TYPE_EXPR_HPP
