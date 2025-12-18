//
// Created by yhwach on 8/21/25.
//

#ifndef FLOAT_EXPR_HPP
#define FLOAT_EXPR_HPP

#include "expr.hpp"
#include "types.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct FloatLiteralExpr final : Expr
    {
        kl::rt::FloatValue v_;
        BuiltinTypeExpr::Kind kind_;

        FloatLiteralExpr(kl::rt::FloatValue v, BuiltinTypeExpr::Kind kind, const lex::Loc& loc)
            : Expr(NodeKind::Expr_FloatLiteral, loc),
              v_(std::move(v)),
              kind_(kind)
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
