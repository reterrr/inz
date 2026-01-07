//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_FN_DECL_HPP
#define INZ_FN_DECL_HPP
#include <algorithm>

#include "decl.hpp"
#include "param_decl.hpp"
#include "expr/type_expr.hpp"
#include "stmt/block_statement.hpp"
#include "type/type_parametrized_decl.hpp"

namespace ast
{
    struct FnDecl final : Decl, TypeParametrizedDecl
    {
        lex::SymId name_;
        std::vector<ParamDecl*> params_;
        TypeExpr* ret_;
        BlockStatement* body_;

        bool isExported_;

        FnDecl(const lex::SymId name,
               std::vector<TypeParamDecl*>&& typeParamDecls,
               std::vector<ParamDecl*>&& params,
               TypeExpr* ret,
               BlockStatement* body,
               bool isExported,
               const lex::Loc& loc)
            : Decl(NodeKind::Decl_Fn, loc),
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

    inline void FnDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}
#endif //INZ_FN_DECL_HPP
