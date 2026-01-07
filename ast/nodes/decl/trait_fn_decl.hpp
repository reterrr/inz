//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_TRAIT_FN_DECL_HPP
#define INZ_TRAIT_FN_DECL_HPP
#include <algorithm>

#include "expr/type_expr.hpp"
#include "stmt/block_statement.hpp"
#include "type/type_parametrized_decl.hpp"
#include "decl/param_decl.hpp"

#include "method_decl.hpp"

namespace ast
{
    struct TraitFnDecl final : MethodDecl, TypeParametrizedDecl
    {
        lex::SymId name_;
        std::vector<ParamDecl*> params_;
        TypeExpr* ret_;
        BlockStatement* body_;
        bool exported_;

        TraitFnDecl(const lex::SymId name,
                    std::vector<TypeParamDecl*>&& typeParamDecls,
                    std::vector<ParamDecl*>&& params,
                    TypeExpr* ret,
                    BlockStatement* body,
                    bool exported,
                    const lex::Loc& loc)
            : MethodDecl(NodeKind::Decl_TraitFn, loc),
              TypeParametrizedDecl(TypeParametrizedKind::Function,
                                   std::move(typeParamDecls), this),
              name_(name),
              params_(std::move(params)),
              ret_(ret),
              body_(body),
              exported_(exported)
        {
            std::ranges::for_each(params_, [this](ParamDecl*& p)
            {
                p->parent = this;
            });

            ret_->parent = this;

            if (body_)
            {
                body_->parent = this;
            }
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void TraitFnDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}
#endif //INZ_TRAIT_FN_DECL_HPP
