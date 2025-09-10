//
// Created by yhwach on 9/7/25.
//

#ifndef CONTINUE_STATEMENT_HPP
#define CONTINUE_STATEMENT_HPP
#include "statement.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct ContinueStatement final : Statement {
        explicit ContinueStatement(const lex::Loc &loc)
            : Statement(NodeKind::Stmt_Continue, loc) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void ContinueStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //CONTINUE_STATEMENT_HPP
