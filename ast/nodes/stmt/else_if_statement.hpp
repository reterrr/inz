//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_ELSE_IF_STATEMENT_HPP
#define INZ_ELSE_IF_STATEMENT_HPP

#include "statement.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast
{
    struct BlockStatement;
    struct Expr;

    struct ElseIfStatement final : Statement
    {
        Expr* condition_;
        BlockStatement* then_;

        ElseIfStatement(Expr* condition, BlockStatement* then, const lex::Loc& loc)
            : Statement(NodeKind::Stmt_ElseIf, loc),
              condition_(condition),
              then_(then)
        {
            condition_->parent = this;
            then_->parent = this;
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void ElseIfStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_ELSE_IF_STATEMENT_HPP
