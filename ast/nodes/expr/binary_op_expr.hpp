//
// Created by yhwach on 8/22/25.
//

#ifndef BINARY_OP_EXPR_HPP
#define BINARY_OP_EXPR_HPP
#include "binary_op_exression_kind.hpp"

#include "expr.hpp"

#include "../visit/expr_visitor.hpp"


namespace ast {
    struct BinaryExpr final : Expr {
        BinaryOp op;
        ExprPtr lhs, rhs;

        BinaryExpr(const BinaryOp op, ExprPtr lhs, ExprPtr rhs, const lex::Loc& loc) :
            Expr(NodeKind::Expr_Binary, loc), op(op), lhs(lhs), rhs(rhs) {}

        void accept(visitor::ExprVisitor &) override;
    };

    inline void BinaryExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}


#endif //BINARY_OP_EXPR_HPP
