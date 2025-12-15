//
// Created by yhwach on 9/14/25.
//

#ifndef STRUCT_DECL_HPP
#define STRUCT_DECL_HPP

#include <utility>
#include <vector>
#include <bits/ranges_algo.h>

#include "decl.hpp"
#include "field_decl.hpp"
#include "../visit/decl_visitor.hpp"


namespace ast {
    struct StructDecl final : Decl {
        lex::SymId name;
        std::vector<FieldDecl *> fields_;

        StructDecl(const lex::SymId name,
                   std::vector<FieldDecl *> &&fields,
                   const lex::Loc &loc)
            : Decl(NodeKind::Decl_Struct, loc),
              name(name), fields_(std::move(fields)) {
            std::ranges::for_each(fields_, [this](FieldDecl *field) {
                field->parent = this;
            });
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void StructDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //STRUCT_DECL_HPP
