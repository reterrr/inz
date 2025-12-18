//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_CHAR_LITERAL_EXPR_HPP
#define INZ_CHAR_LITERAL_EXPR_HPP

#include "expr.hpp"
#include "literal_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct CharLiteralExpr final : LiteralExpr
    {
        kl::rt::character v_;

        CharLiteralExpr(kl::rt::character v, const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Char, loc),
              v_(v)
        {
        }

        void accept(visitor::ExprVisitor& v) override;
    };

    inline void CharLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_CHAR_LITERAL_EXPR_HPP
