//
// Created by yhwach on 8/28/25.
//

#ifndef PARAM_DECL_HPP
#define PARAM_DECL_HPP

#include "decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct TypeExpr;
    struct ParamDecl final : Decl
    {
        TypeExpr* type_;
        lex::SymId name_;

        ParamDecl(const lex::SymId name, TypeExpr* type, const lex::Loc& L)
            : Decl(NodeKind::Decl_Param, L),
              type_(type), name_(name)
        {
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void ParamDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //PARAM_DECL_HPP
