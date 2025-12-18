//
// Created by yhwach on 8/21/25.
//

#ifndef FLOAT_EXPR_HPP
#define FLOAT_EXPR_HPP

#include "literal_expr.hpp"
#include "types.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct FloatLiteralExpr final : LiteralExpr
    {
        lex::SymId v_;
        std::optional<kl::rt::FloatKind> suffix_;

        FloatLiteralExpr(lex::SymId v,
                         std::optional<kl::rt::FloatKind> suffix,
                         const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Float, loc),
              v_(v), suffix_(suffix)
        {
        }

        void accept(visitor::ExprVisitor& v) override;
    };

    inline void FloatLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //FLOAT_EXPR_HPP
