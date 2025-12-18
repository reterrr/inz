//
// Created by yhwach on 8/29/25.
//

#ifndef BOOL_EXPR_HPP
#define BOOL_EXPR_HPP

#include "literal_expr.hpp"
#include "visit/expr_visitor.hpp"
#include "types.hpp"

namespace ast
{
    struct BoolLiteralExpr final : LiteralExpr
    {
        kl::rt::boolean v_;

        BoolLiteralExpr(kl::rt::boolean v, const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Bool, loc),
              v_(v)
        {
        }

        void accept(visitor::ExprVisitor& v) override;
    };

    inline void BoolLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //BOOL_EXPR_HPP
