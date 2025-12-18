//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_ELSE_STATEMENT_HPP
#define INZ_ELSE_STATEMENT_HPP

#include "statement.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast
{
    struct BlockStatement;

    struct ElseStatement final : Statement
    {
        BlockStatement* then_;

        ElseStatement(BlockStatement* then, const lex::Loc& loc)
            : Statement(NodeKind::Stmt_Else, loc),
              then_(then)
        {
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void ElseStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_ELSE_STATEMENT_HPP
