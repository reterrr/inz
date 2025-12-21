//
// Created by yhwach on 12/12/25.
//

#ifndef INZ_TYPE_PARAM_DECL_HPP
#define INZ_TYPE_PARAM_DECL_HPP

#include "decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct TypeParamDecl final : Decl
    {
        lex::SymId name_;

        TypeParamDecl(lex::SymId name, const lex::Loc& loc)
            : Decl(NodeKind::Decl_TypeParam, loc), name_(name)
        {
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void TypeParamDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_TYPE_PARAM_DECL_HPP
