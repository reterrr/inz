//
// Created by yhwach on 9/8/25.
//

#ifndef INDEX_EXPR_HPP
#define INDEX_EXPR_HPP

#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct IndexExpr final : Expr {
        ExprPtr base_;
        ExprPtr index_;

        IndexExpr(ExprPtr base, ExprPtr index, const lex::Loc &loc)
            : Expr(NodeKind::Expr_Index, loc),
              base_(base), index_(index) {
            base_->parent = this;
            index_->parent = this;
        }

        void accept(visitor::ExprVisitor &v) override { v.visit(*this); }
    };
}

#endif //INDEX_EXPR_HPP
