//
// Created by yhwach on 12/26/25.
//

#ifndef INZ_TRAIT_DECL_HPP
#define INZ_TRAIT_DECL_HPP
#include <vector>

#include "decl.hpp"
#include "trait_fn_decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct TraitDecl final : Decl
    {
        lex::SymId name_{};
        bool isExported_{false};

        std::vector<TypeParamDecl*> typeParamsDecls_;
        std::vector<TraitFnDecl*> methods_; // signatures or default methods

        TraitDecl(lex::SymId name,
                  std::vector<TypeParamDecl*>&& tparams,
                  std::vector<TraitFnDecl*>&& methods,
                  bool isExported,
                  const lex::Loc& loc)
            : Decl(NodeKind::Decl_Trait, loc),
              name_(name),
              isExported_(isExported),
              typeParamsDecls_(std::move(tparams)),
              methods_(std::move(methods))
        {
            for (auto* tp : typeParamsDecls_) if (tp) tp->parent = this;
            for (auto* m : methods_) if (m) m->parent = this;
        }

        void accept(visitor::DeclVisitor& v) override { v.visit(*this); }
    };
}


#endif //INZ_TRAIT_DECL_HPP
