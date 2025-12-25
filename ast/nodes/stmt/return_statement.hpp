//
// Created by yhwach on 8/29/25.
//

#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP
#include "statement.hpp"
#include "expr/expr.hpp"

#include "visit/stmt_visitor.hpp"

namespace ast {
    struct ReturnStatement final : Statement {
        ExprPtr expr_;

        ReturnStatement(ExprPtr expr, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_Return, loc),
              expr_(expr) {
            if (expr_) expr_->parent = this;
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void ReturnStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}


#endif //RETURN_STATEMENT_HPP
