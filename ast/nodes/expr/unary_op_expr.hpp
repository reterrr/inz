//
// Created by yhwach on 8/22/25.
//

#ifndef UNARY_OP_EXPR_HPP
#define UNARY_OP_EXPR_HPP
#include "expr.hpp"

#include "unary_op_expression_kind.hpp"

#include "../visit/expr_visitor.hpp"

namespace ast {
    struct UnaryExpr final : Expr {
        UnaryOp op;
        ExprPtr expr;

        UnaryExpr(const UnaryOp op, ExprPtr expr, const lex::Loc &loc)
            : Expr(NodeKind::Expr_Unary, loc), op(op), expr(expr) {
            expr->parent = this;
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void UnaryExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //UNARY_OP_EXPR_HPP
