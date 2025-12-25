//
// Created by yhwach on 9/3/25.
//

#ifndef ASSIGN_EXPR_HPP
#define ASSIGN_EXPR_HPP

#include "assign_op.hpp"
#include "expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct AssignExpr final : Expr
    {
        ExprPtr lhs_;
        ExprPtr rhs_;
        AssignOp op;

        AssignExpr(ExprPtr lhs, ExprPtr rhs, AssignOp op, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Assign, loc), lhs_(lhs), rhs_(rhs), op(op)
        {
            lhs_->parent = this;
            rhs_->parent = this;
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void AssignExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //ASSIGN_EXPR_HPP
