//
// Created by yhwach on 9/8/25.
//

#ifndef CALL_EXPR_HPP
#define CALL_EXPR_HPP

#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct CallExpr final : Expr {
        ExprPtr callee; // foo(...) or obj.method(...): callee is an Expr
        std::vector<ExprPtr> args; // positional arguments, in order

        CallExpr(ExprPtr callee,
                 std::vector<ExprPtr> &&args,
                 const lex::Loc &loc)
            : Expr(NodeKind::Expr_Call, loc),
              callee(callee),
              args(std::move(args)) {
            callee->parent = this;
            std::ranges::for_each(args, [this](ExprPtr &e) { e->parent = this; });
        }

        void accept(visitor::ExprVisitor &v) override;
    };

    inline void CallExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //CALL_EXPR_HPP
