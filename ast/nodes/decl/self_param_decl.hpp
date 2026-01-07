//
// Created by yhwach on 12/26/25.
//

#ifndef INZ_SELF_PARAM_DECL_HPP
#define INZ_SELF_PARAM_DECL_HPP

#include "param_decl.hpp"          // ParamDecl
#include "self_param_kind.hpp"
#include "visit/decl_visitor.hpp"  // visitor::DeclVisitor

namespace ast
{
    struct SelfParamDecl final : ParamDecl
    {
        SelfParamKind self_kind_;

        SelfParamDecl(lex::SymId self_sym, SelfParamKind kind, const lex::Loc& loc)
            : ParamDecl(self_sym, loc),
              self_kind_(kind)
        {
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void SelfParamDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
} // namespace ast
#endif //INZ_SELF_PARAM_DECL_HPP
