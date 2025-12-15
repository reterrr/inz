//
// Created by yhwach on 8/29/25.
//

#ifndef VAR_DECL_STATEMENT_HPP
#define VAR_DECL_STATEMENT_HPP

#include <token.hpp>

#include "statement.hpp"

#include "../visit/stmt_visitor.hpp"

namespace ast
{
    struct VarDecl;

    struct VarDeclStatement final : Statement
    {
        VarDecl* decl_;

        VarDeclStatement(VarDecl* decl, const lex::Loc& loc)
            : Statement(NodeKind::Stmt_VarDecl, loc),
              decl_(decl)
        {
            decl_->parent = this;
        }

        void accept(visitor::StmtVisitor&) override;
    };

    inline void VarDeclStatement::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //VAR_DECL_STATEMENT_HPP
