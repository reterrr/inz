//
// Created by yhwach on 8/21/25.
//

#ifndef INT_EXPR_HPP
#define INT_EXPR_HPP
#include <token.hpp>

#include "../types.hpp"
#include "expr.hpp"

#include "../visit/expr_visitor.hpp"

namespace ast {
    struct IntLiteralExpr final : Expr {
        kl_int v_;

        IntLiteralExpr(const kl_int v, const lex::Loc &location)
            : Expr(NodeKind::Expr_IntLiteral, location), v_(v) {
        }

        void accept(visitor::ExprVisitor &v) override;
    };

    inline void IntLiteralExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //INT_EXPR_HPP
