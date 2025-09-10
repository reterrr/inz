//
// Created by yhwach on 8/28/25.
//

#ifndef COMPOUND_STATEMENT_HPP
#define COMPOUND_STATEMENT_HPP
#include <token.hpp>
#include <vector>

#include "statement.hpp"
#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct BlockStatement final : Statement {
        std::vector<StatementPtr> statements;

        // lex::Loc lbrace;
        // lex::Loc rbrace;

        // BlockStatement(std::vector<StatementPtr> &&statements, const lex::Loc &loc,
        //                const lex::Loc &lbrace, const lex::Loc &rbrace)
        //     : Statement(NodeKind::Stmt_Block, loc), statements(std::move(statements)),
        //       lbrace(lbrace), rbrace(rbrace) {
        // }

        BlockStatement(std::vector<StatementPtr> &&statements, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_Block, loc), statements(std::move(statements)){
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void BlockStatement::accept(visitor::StmtVisitor & v) {
        v.visit(*this);
    }

}

#endif //COMPOUND_STATEMENT_HPP
