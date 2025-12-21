//
// Created by yhwach on 8/21/25.
//

#ifndef INT_EXPR_HPP
#define INT_EXPR_HPP

#include "visit/expr_visitor.hpp"
#include "types.hpp"
#include "literal_expr.hpp"
#include <optional>

namespace ast
{
    struct IntLiteralExpr final : LiteralExpr
    {
        lex::SymId v_;
        std::optional<kl::rt::IntKind> suffix_;

        IntLiteralExpr(lex::SymId v,
                       std::optional<kl::rt::IntKind> suffix,
                       const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Int, loc),
              v_(v), suffix_(suffix)
        {
        }

        void accept(visitor::ExprVisitor& v) override;
    };

    inline void IntLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INT_EXPR_HPP
