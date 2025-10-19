//
// Created by yhwach on 9/7/25.
//

#ifndef FIELD_EXPR_HPP
#define FIELD_EXPR_HPP

#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct FieldExpr final : Expr {
        ExprPtr base_; // the object expression (value or &ref)
        lex::SymId field; // interned field name
        int32_t cached_index = -1; // filled by semantic pass (optional)

        FieldExpr(ExprPtr base, const lex::SymId fieldName, const lex::Loc &loc)
            : Expr(NodeKind::Expr_Field, loc)
              , base_(base)
              , field(fieldName) {
            base_->parent = this;
        }

        void accept(visitor::ExprVisitor &v) override { v.visit(*this); }
    };
}

#endif //FIELD_EXPR_HPP
