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
        ExprPtr condition_;
        StatementPtr thenBody_;

        IfStatement(ExprPtr condition, StatementPtr thenBody, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_If, loc),
              condition_(condition), thenBody_(thenBody) {
            condition_->parent = this;
            thenBody_->parent = this;
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void IfStatement::accept(visitor::StmtVisitor & v) {
        v.visit(*this);
    }

}

#endif //IF_STATEMENT_HPP
