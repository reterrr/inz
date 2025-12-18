//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_ARRAY_LITERAL_EXPR_HPP
#define INZ_ARRAY_LITERAL_EXPR_HPP

#include <vector>
#include "literal_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct ArrayLiteralExpr final : LiteralExpr
    {
        std::vector<ExprPtr> v_;

        ArrayLiteralExpr(std::vector<ExprPtr>&& v, const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Array, loc),
              v_(std::move(v))
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void ArrayLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}


#endif //INZ_ARRAY_LITERAL_EXPR_HPP
