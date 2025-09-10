//
// Created by yhwach on 8/30/25.
//

#ifndef FIELD_INIT_EXPR_HPP
#define FIELD_INIT_EXPR_HPP

#include "expr.hpp"

namespace ast {
    struct FieldInitExpr final : Expr {
        lex::SymId name;
        ExprPtr value;

        FieldInitExpr(const lex::SymId name, ExprPtr value, const lex::Loc &loc)
            : Expr(NodeKind::Expr_FieldInit, loc),
              name(name), value(value) {
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void FieldInitExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //FIELD_INIT_EXPR_HPP
