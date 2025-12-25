//
// Created by yhwach on 9/7/25.
//

#ifndef VAR_STATEMENT_HPP
#define VAR_STATEMENT_HPP

#include "statement.hpp"
#include "var_mutablity_storage.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast
{
    struct VarStmt final : Statement
    {
        lex::SymId name_;
        TypeExpr* type_;
        Mutability mut_;
        Storage storage_;
        Expr* init_; //maybe nullptr

        VarStmt(
            lex::SymId name,
            TypeExpr* type,
            Mutability mut,
            Storage storage,
            Expr* init,
            const lex::Loc& loc)
            : Statement(NodeKind::Stmt_Var, loc),
              name_(name),
              type_(type),
              mut_(mut),
              storage_(storage),
              init_(init)
        {
            type_->parent = this;
            if (init_) init_->parent = this;
        }

        void accept(visitor::StmtVisitor& v) override;
    };

    inline void VarStmt::accept(visitor::StmtVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //VAR_STATEMENT_HPP
