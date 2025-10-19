//
// Created by yhwach on 8/29/25.
//

#ifndef STRING_EXPR_HPP
#define STRING_EXPR_HPP

#include "expr.hpp"

#include "../visit/expr_visitor.hpp"

namespace ast {
    struct StringLiteralExpr final : Expr {
        lex::SymId value;

        StringLiteralExpr(const lex::SymId value, const lex::Loc &loc)
            : Expr(NodeKind::Expr_StringLiteral, loc),
              value(value) {
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void StringLiteralExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //STRING_EXPR_HPP
