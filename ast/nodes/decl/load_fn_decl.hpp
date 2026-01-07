//
// Created by yhwach on 12/29/25.
//

#ifndef INZ_LOAD_FN_DECL_HPP
#define INZ_LOAD_FN_DECL_HPP

#include <vector>

#include "param_decl.hpp"
#include "token.hpp"
#include "expr/type_expr.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct LoadFnDecl final : Decl
    {
        lex::SymId name_;
        std::vector<ParamDecl*> params_;
        bool exported_ = false;
        TypeExpr* ret_;

        LoadFnDecl(lex::SymId name,
                   std::vector<ParamDecl*>&& params,
                   TypeExpr* ret,
                   bool exported,
                   const lex::Loc& loc)
            : Decl(NodeKind::Decl_LoadFn, loc),
              name_(name),
              params_(std::move(params)),
              exported_(exported),
              ret_(ret)
        {
            std::ranges::for_each(params_, [this](auto& param)
            {
                param->parent = this;
            });

            ret_->parent = this;
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void LoadFnDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}


#endif //INZ_LOAD_FN_DECL_HPP
