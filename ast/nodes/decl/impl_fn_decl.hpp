//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_IMPL_FN_DECL_HPP
#define INZ_IMPL_FN_DECL_HPP
#include <algorithm>

#include "method_decl.hpp"
#include "expr/type_expr.hpp"
#include "stmt/block_statement.hpp"
#include "decl/param_decl.hpp"
#include "type/type_parametrized_decl.hpp"

namespace ast
{

    struct ImplFnDecl final : MethodDecl, TypeParametrizedDecl
    {
        lex::SymId name_;
        std::vector<ParamDecl*> params_;
        TypeExpr* ret_;
        BlockStatement* body_;

        bool isExported_;

        ImplFnDecl(const lex::SymId name,
                   std::vector<TypeParamDecl*>&& typeParamDecls,
                   std::vector<ParamDecl*>&& params,
                   TypeExpr* ret,
                   BlockStatement* body,
                   bool isExported,
                   const lex::Loc& loc)
            : MethodDecl(NodeKind::Decl_ImplFn, loc),
              TypeParametrizedDecl(TypeParametrizedKind::Function,
                                   std::move(typeParamDecls), this),
              name_(name),
              params_(std::move(params)),
              ret_(ret),
              body_(body),
              isExported_(isExported)
        {
            std::ranges::for_each(params_, [this](ParamDecl*& p)
            {
                p->parent = this;
            });

            ret_->parent = this;
            body_->parent = this;
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void ImplFnDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }

}

#endif //INZ_IMPL_FN_DECL_HPP