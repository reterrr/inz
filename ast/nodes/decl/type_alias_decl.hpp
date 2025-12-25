//
// Created by yhwach on 9/7/25.
//

#ifndef TYPE_ALIAS_DECL_HPP
#define TYPE_ALIAS_DECL_HPP

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct TypeAliasDecl final : Decl {
        lex::SymId type_name; // correct
        lex::SymId type_alias;

        TypeAliasDecl(const lex::SymId type_name,
                      const lex::SymId type_alias,
                      const lex::Loc &loc)
            : Decl(NodeKind::Decl_TypeAlias, loc),
              type_name(type_name), type_alias(type_alias) {
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void TypeAliasDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //TYPE_ALIAS_DECL_HPP
