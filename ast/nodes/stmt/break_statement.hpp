//
// Created by yhwach on 9/7/25.
//

#ifndef BREAK_STATEMENT_HPP
#define BREAK_STATEMENT_HPP
#include "statement.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct BreakStatement final : Statement {
        explicit BreakStatement(const lex::Loc &loc)
            : Statement(NodeKind::Stmt_Break, loc) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void BreakStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //BREAK_STATEMENT_HPP
