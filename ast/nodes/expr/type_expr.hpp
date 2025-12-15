//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_TYPE_EXPR_HPP
#define INZ_TYPE_EXPR_HPP

#include "expr.hpp"

namespace ast
{
    struct TypeExpr : Expr
    {
        enum class Kind
        {
            Builtin, Array, Path, Ref, Callable
        };

        Kind kind_;

        TypeExpr(Kind kind, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Type, loc), kind_(kind)
        {
        }
    };
}

#endif //INZ_TYPE_EXPR_HPP
