//
// Created by yhwach on 8/29/25.
//

#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP

#include "statement.hpp"
#include "visit/stmt_visitor.hpp"

#include "else_if_statement.hpp"
#include "else_statement.hpp"

namespace ast
{
    struct IfStatement final : Statement
    {
        ExprPtr condition_;
        BlockStatement* thenBody_;
        std::vector<ElseIfStatement*> elseIfs_;
        ElseStatement* else_;

        IfStatement(ExprPtr condition, BlockStatement* thenBody,
                    std::vector<ElseIfStatement*>&& elseIfs,
                    ElseStatement* else__,
                    const lex::Loc& loc)
            : Statement(NodeKind::Stmt_If, loc),
              condition_(condition), thenBody_(thenBody),
              elseIfs_(std::move(elseIfs)), else_(else__)
        {
            condition_->parent = this;
            if (thenBody_) thenBody_->parent = this;
            if (else_) else_->parent = this;

            std::ranges::for_each(elseIfs_, [this](auto& elseIf)
            {
                if (elseIf) elseIf->parent = this;
            });
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void IfStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //IF_STATEMENT_HPP
