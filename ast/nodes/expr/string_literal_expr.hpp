//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_STRING_LITERAL_EXPR_HPP
#define INZ_STRING_LITERAL_EXPR_HPP

#include "literal_expr.hpp"
#include "visit/expr_visitor.hpp"
#include "types.hpp"

namespace ast
{
    struct StringLiteralExpr final : LiteralExpr
    {
        lex::SymId v_;

        StringLiteralExpr(lex::SymId v, const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::String, loc),
              v_(v)
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void StringLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_STRING_LITERAL_EXPR_HPP
