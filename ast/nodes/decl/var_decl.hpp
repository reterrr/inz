//
// Created by yhwach on 9/7/25.
//

#ifndef VAR_DECL_HPP
#define VAR_DECL_HPP

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct Type;
    struct InitDeclarator; // defined in stmt/var_decl_statement.hpp, pointer is fine here

    // Top-level variable declaration (globals). Do NOT use inside blocks.
    struct VarDecl final : Decl {
        Type *type{nullptr}; // declared type
        TypeSpecifier specifier{TypeSpecifier::Imm}; // default: immutable
        TypeRegion region{TypeRegion::Static}; // top-level vars are static by nature
        std::vector<InitDeclarator *> declarators; // int a=1, b=2;

        VarDecl(std::vector<InitDeclarator *> &&decls,
                Type *ty,
                TypeSpecifier spec,
                TypeRegion reg,
                const lex::Loc &loc)
            : Decl(NodeKind::Decl_Var, loc)
              , type(ty)
              , specifier(spec)
              , region(reg)
              , declarators(std::move(decls)) {
        }

        void accept(visitor::DeclVisitor &v) override { v.visit(*this); }
    };
}

#endif //VAR_DECL_HPP
