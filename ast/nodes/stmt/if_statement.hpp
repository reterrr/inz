//
// Created by yhwach on 8/29/25.
//

#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP

#include "statement.hpp"
#include "../expr/expr.hpp"

#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct IfStatement final : Statement {
        ExprPtr condition;
        StatementPtr thenBody;

        IfStatement(ExprPtr condition, StatementPtr thenBody, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_If, loc),
              condition(condition), thenBody(thenBody) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void IfStatement::accept(visitor::StmtVisitor & v) {
        v.visit(*this);
    }

}

#endif //IF_STATEMENT_HPP
