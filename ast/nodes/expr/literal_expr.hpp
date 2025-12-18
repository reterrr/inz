//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_LITERAL_EXPR_HPP
#define INZ_LITERAL_EXPR_HPP

#include "types.hpp"
#include "expr.hpp"

namespace ast
{
    struct LiteralExpr : Expr
    {
        kl::rt::LiteralExprKind kind_;

    protected:
        LiteralExpr(kl::rt::LiteralExprKind kind, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Literal, loc),
              kind_(kind)
        {
        }
    };
}

#endif //INZ_LITERAL_EXPR_HPP
