//
// Created by yhwach on 9/7/25.
//

#ifndef DO_WHILE_STATEMENT_HPP
#define DO_WHILE_STATEMENT_HPP
#include "statement.hpp"
#include "../expr/expr.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct Expr;
    typedef Expr *ExprPtr;
    struct BlockStatement;

    struct DoWhileStatement final : Statement {
        ExprPtr condition_;
        BlockStatement *body_;

        DoWhileStatement(ExprPtr condition,
                         BlockStatement *body,
                         const lex::Loc &loc)
            : Statement(NodeKind::Stmt_DoWhile, loc),
              condition_(condition),
              body_(body) {
            body_->parent = this;
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void DoWhileStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //DO_WHILE_STATEMENT_HPP
