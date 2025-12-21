//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_FUNCTION_BLOCK_STATEMENT_HPP
#define INZ_FUNCTION_BLOCK_STATEMENT_HPP
#include "statement.hpp"
#include "visit/stmt_visitor.hpp"


namespace ast
{
    struct BlockStatement;

    struct FunctionBlockStatement final : Statement
    {
        BlockStatement* block_;

        FunctionBlockStatement(BlockStatement* block, const lex::Loc& loc)
            : Statement(NodeKind::Stmt_FnBlock, loc),
              block_(block)
        {
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void FunctionBlockStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_FUNCTION_BLOCK_STATEMENT_HPP
