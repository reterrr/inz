//
// Created by yhwach on 9/8/25.
//

#ifndef INIT_DECLARATOR_EXPR_HPP
#define INIT_DECLARATOR_EXPR_HPP

#include "expr.hpp"
#include "../visit/expr_visitor.hpp"

namespace ast {
    struct InitDeclarator final : Expr {
        lex::SymId name;
        ExprPtr init;

        InitDeclarator(const lex::SymId name, ExprPtr init, const lex::Loc &loc)
            : Expr(NodeKind::Expr_DeclInit, loc), name(name), init(init) {
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void InitDeclarator::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //INIT_DECLARATOR_EXPR_HPP
