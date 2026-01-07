//
// Created by yhwach on 8/28/25.
//

#ifndef PARAM_DECL_HPP
#define PARAM_DECL_HPP

#include "decl.hpp"
#include "visit/decl_visitor.hpp"

#include "expr/type_expr.hpp"

namespace ast
{
    struct ParamDecl : Decl
    {
        TypeExpr* type_; //can be nullptr
        lex::SymId name_;

        ParamDecl(const lex::SymId name, TypeExpr* type, const lex::Loc& L)
            : Decl(NodeKind::Decl_Param, L),
              type_(type), name_(name)
        {
            type_->parent = this;
        }

        ParamDecl(const lex::SymId name, const lex::Loc& L)
            : Decl(NodeKind::Decl_SelfParam, L),
              type_(nullptr), name_(name)
        {
            if (type_) type_->parent = this;
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void ParamDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //PARAM_DECL_HPP
