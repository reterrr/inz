//
// Created by yhwach on 9/7/25.
//

#ifndef EXPR_STATEMENT_HPP
#define EXPR_STATEMENT_HPP

#include "statement.hpp"
#include "../expr/expr.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct ExprStatement final : Statement {
        ExprPtr expr;

        ExprStatement(ExprPtr expr, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_Expr, loc),
              expr(expr) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void ExprStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //EXPR_STATEMENT_HPP
