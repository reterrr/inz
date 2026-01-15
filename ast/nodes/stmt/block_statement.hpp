//
// Created by yhwach on 8/28/25.
//

#ifndef COMPOUND_STATEMENT_HPP
#define COMPOUND_STATEMENT_HPP
#include <token.hpp>
#include <vector>
#include <algorithm>

#include "block_stmt_kind.hpp"
#include "statement.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast
{
    struct BlockStatement final : Statement
    {
        std::vector<Statement*> statements_;
        BlockKind kind_;

        BlockStatement(std::vector<Statement*>&& statements,
                       BlockKind kind,
                       const lex::Loc& loc)
            : Statement(NodeKind::Stmt_Block, loc),
              statements_(std::move(statements)), kind_(kind)
        {
            std::ranges::for_each(statements, [this](auto& stmt)
            {
                stmt->parent = this;
            });
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void BlockStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //COMPOUND_STATEMENT_HPP
