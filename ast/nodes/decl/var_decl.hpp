//
// Created by yhwach on 9/7/25.
//

#ifndef VAR_DECL_HPP
#define VAR_DECL_HPP

#include "decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct Type;

    struct VarDecl final : Decl
    {
        enum class Mutability { Imm, Mut };

        enum class Storage { Auto, Static };

        lex::SymId name_;
        TypeExpr* type_;
        Mutability mut_;
        Storage storage_;
        Expr* init_; //maybe nullptr

        VarDecl(
            lex::SymId name,
            TypeExpr* type,
            Mutability mut,
            Storage storage,
            Expr* init,
            const lex::Loc& loc)
            : Decl(NodeKind::Decl_Var, loc),
              name_(name),
              type_(type),
              mut_(mut),
              storage_(storage),
              init_(init)
        {
            type_->parent = this;
            if (init_) init_->parent = this;
        }

        void accept(visitor::DeclVisitor& v) override;
    };

    inline void VarDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //VAR_DECL_HPP
