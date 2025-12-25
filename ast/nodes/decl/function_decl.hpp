//
// Created by yhwach on 8/28/25.
//

#ifndef FUNCTION_DECL_HPP
#define FUNCTION_DECL_HPP


#include "decl.hpp"

#include "visit/decl_visitor.hpp"
#include "expr/type_expr.hpp"
#include "decl/param_decl.hpp"
#include "type/type_parametrized_decl.hpp"
#include "stmt/block_statement.hpp"

namespace ast
{
    struct FunctionDecl final : Decl, TypeParametrizedDecl
    {
        lex::SymId name_;
        std::vector<ParamDecl*> params_;
        TypeExpr* ret_;
        BlockStatement* body_;

        bool isExported_;

        FunctionDecl(const lex::SymId name,
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
            if (body_) body_->parent = this;
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void FunctionDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //FUNCTION_DECL_HPP
