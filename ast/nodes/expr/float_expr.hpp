//
// Created by yhwach on 8/21/25.
//

#ifndef FLOAT_EXPR_HPP
#define FLOAT_EXPR_HPP
#include "expr.hpp"

#include "../types.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct FloatLiteralExpr final : Expr {
        kl_float v_;

        FloatLiteralExpr(const kl_float v, const lex::Loc &loc)
            : Expr(NodeKind::Expr_FloatLiteral, loc), v_(v) {
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void FloatLiteralExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //FLOAT_EXPR_HPP
