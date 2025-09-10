//
// Created by yhwach on 8/27/25.
//

#ifndef REF_EXPR_HPP
#define REF_EXPR_HPP

#include <token.hpp>
#include "expr.hpp"
#include "../visit/expr_visitor.hpp"
#include "../decl/decl.hpp"

namespace ast {
    struct RefExpr final : Expr {
        lex::SymId name{};
        Decl *binding;

        RefExpr(const lex::SymId name, const lex::Loc &loc)
            : Expr(NodeKind::Expr_Ref, loc), name(name), binding(nullptr) {
        }

        void accept(visitor::ExprVisitor &v) override { v.visit(*this); }
    };
}

#endif
