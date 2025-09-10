//
// Created by yhwach on 8/29/25.
//

#ifndef WHILE_STATEMENT_HPP
#define WHILE_STATEMENT_HPP

#include "statement.hpp"
#include "../expr/expr.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct BlockStatement;

    struct WhileStatement final : Statement {
        ExprPtr condition;
        BlockStatement *body;

        WhileStatement(ExprPtr condition, BlockStatement *body, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_While, loc),
              condition(condition), body(body) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void WhileStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //WHILE_STATEMENT_HPP
