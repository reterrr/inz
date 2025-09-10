//
// Created by yhwach on 9/8/25.
//

#ifndef INDEX_EXPR_HPP
#define INDEX_EXPR_HPP

#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct IndexExpr final : Expr {
        ExprPtr base;
        ExprPtr index;

        IndexExpr(ExprPtr b, ExprPtr i, const lex::Loc &loc)
            : Expr(NodeKind::Expr_Index, loc),
              base(b), index(i) {
        }

        void accept(visitor::ExprVisitor &v) override { v.visit(*this); }
    };
}

#endif //INDEX_EXPR_HPP
