//
// Created by yhwach on 12/26/25.
//

#ifndef INZ_IMPL_DECL_HPP
#define INZ_IMPL_DECL_HPP


#include <vector>

#include "decl.hpp"
#include "impl_fn_decl.hpp"
#include "expr/path_expr.hpp"
#include "expr/type_expr.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct ImplDecl final : Decl
    {
        TypeExpr* traitPath_ = nullptr; // optional
        TypeExpr* forType_;

        std::vector<TypeParamDecl*> typeParamsDecls_    ;
        std::vector<ImplFnDecl*> methods_;

        ImplDecl(std::vector<TypeParamDecl*>&& tparams,
                 TypeExpr* traitType, // nullable (inherent impl)
                 TypeExpr* selfType, // required
                 std::vector<ImplFnDecl*>&& methods,
                 const lex::Loc& loc)
            : Decl(NodeKind::Decl_Impl, loc),
              traitPath_(traitType),
              forType_(selfType),
              typeParamsDecls_(std::move(tparams)),
              methods_(std::move(methods))
        {
            if (traitPath_) traitPath_->parent = this;
            if (forType_) forType_->parent = this;

            for (auto* tp : typeParamsDecls_) if (tp) tp->parent = this;
            for (auto* m : methods_) if (m) m->parent = this;
        }

        void accept(visitor::DeclVisitor& v) override { v.visit(*this); }
    };
} // namespace ast

#endif //INZ_IMPL_DECL_HPP
