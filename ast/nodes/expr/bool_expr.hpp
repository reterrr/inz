//
// Created by yhwach on 8/29/25.
//

#ifndef BOOL_EXPR_HPP
#define BOOL_EXPR_HPP
#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct BoolLiteralExpr final : Expr {
        kl_bool value;

        BoolLiteralExpr(const kl_bool value, const lex::Loc& loc)
            : Expr(NodeKind::Expr_BoolLiteral, loc), value(value) {}

        void accept(visitor::ExprVisitor &) override;
    };

    inline void BoolLiteralExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //BOOL_EXPR_HPP
