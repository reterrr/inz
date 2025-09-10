//
// Created by yhwach on 9/7/25.
//

#ifndef IMPORT_DECL_HPP
#define IMPORT_DECL_HPP

#include <optional>
#include <vector>

#include "../decl/decl.hpp"
#include "../visit/decl_visitor.hpp"

namespace ast {
    struct ImportDecl final : Decl {
        std::vector<lex::SymId> path;
        std::optional<lex::SymId> alias;

        bool is_public = false;

        ImportDecl(std::vector<lex::SymId> &&path, const std::optional<lex::SymId> alias, bool is_public,
                   const lex::Loc &loc)
            : Decl(NodeKind::Decl_Import, loc),
              path(std::move(path)),
              alias(alias),
              is_public(is_public) {
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void ImportDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //IMPORT_DECL_HPP
