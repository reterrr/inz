//
// Created by yhwach on 9/14/25.
//

#ifndef FIELD_DECL_HPP
#define FIELD_DECL_HPP

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct FieldDecl final : Decl {
        lex::SymId name;
        Type *type;
        bool is_public{false};

        FieldDecl(const lex::SymId name, Type *type, const bool is_public,
                  const lex::Loc &loc)
            : Decl(NodeKind::Decl_Field, loc), name(name),
              type(type), is_public(is_public) {
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void FieldDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //FIELD_DECL_HPP
