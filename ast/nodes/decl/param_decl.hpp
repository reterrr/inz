//
// Created by yhwach on 8/28/25.
//

#ifndef PARAM_DECL_HPP
#define PARAM_DECL_HPP
#include "decl.hpp"
#include "../type/type.hpp"
#include "../visit/decl_visitor.hpp"


namespace ast {
    struct ParamDecl final : Decl {
        Type *type{nullptr};
        lex::SymId name;
        TypeSpecifier qual{TypeSpecifier::Imm};

        ParamDecl(const lex::SymId name, Type *ty, const TypeSpecifier q, const lex::Loc &L)
            : Decl(NodeKind::Decl_Param, L), type(ty), name(name), qual(q) {
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void ParamDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //PARAM_DECL_HPP
