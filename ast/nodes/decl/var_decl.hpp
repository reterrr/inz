//
// Created by yhwach on 9/7/25.
//

#ifndef VAR_DECL_HPP
#define VAR_DECL_HPP

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct Type;
    struct InitDeclarator;

    struct VarDecl final : Decl {
        Type *type{nullptr};
        TypeRegion region{TypeRegion::Auto};
        InitDeclarator *declarator;

        VarDecl(InitDeclarator *decl,
                Type *ty,
                const TypeRegion reg,
                const lex::Loc &loc)
            : Decl(NodeKind::Decl_Var, loc)
              , type(ty)
              , region(reg)
              , declarator(decl) {
        }

        void accept(visitor::DeclVisitor &v) override;
    };

    inline void VarDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //VAR_DECL_HPP
