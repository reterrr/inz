//
// Created by yhwach on 9/7/25.
//

#ifndef VAR_DECL_HPP
#define VAR_DECL_HPP

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast
{
    struct Type;
    struct InitDeclarator;

    struct VarDecl final : Decl
    {
        enum class Mutability { Imm, Mut };

        lex::SymId name_;
        TypeExpr* type_;
        Mutability mut_;

        VarDecl(
            lex::SymId name,
            TypeExpr* type,
            Mutability mut,
            const lex::Loc& loc)
            : Decl(NodeKind::Decl_Var, loc),
              name_(name), type_(type), mut_(mut)
        {
            type_->parent = this;
        }

        void accept(visitor::DeclVisitor& v) override;
    };

    inline void VarDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //VAR_DECL_HPP
