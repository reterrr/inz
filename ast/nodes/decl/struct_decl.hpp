//
// Created by yhwach on 9/14/25.
//

#ifndef STRUCT_DECL_HPP
#define STRUCT_DECL_HPP

#include <vector>

#include "decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct StructDecl final : Decl {
        lex::SymId name;
        std::vector<FieldDecl*> fields;

        StructDecl(const lex::SymId name, std::vector<FieldDecl*> &&fields, const lex::Loc &loc)
            : Decl(NodeKind::Decl_Struct, loc),
              name(name), fields(std::move(fields)) {
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void StructDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //STRUCT_DECL_HPP
