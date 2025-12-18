//
// Created by yhwach on 8/21/25.
//

#ifndef INT_EXPR_HPP
#define INT_EXPR_HPP
#include <token.hpp>

#include "types.hpp"
#include "expr.hpp"

#include "visit/expr_visitor.hpp"

namespace ast
{
    struct IntLiteralExpr final : Expr
    {
        kl::rt::IntValue v_;
        kl::rt::Kind kind_;

        IntLiteralExpr(kl::rt::IntValue v, BuiltinTypeExpr::Kind kind, const lex::Loc& loc)
            : Expr(NodeKind::Expr_IntLiteral, loc),
              v_(std::move(v)),
              kind_(kind)
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
