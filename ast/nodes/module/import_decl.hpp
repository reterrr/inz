//
// Created by yhwach on 9/7/25.
//

#ifndef IMPORT_DECL_HPP
#define IMPORT_DECL_HPP

#include <optional>
#include "decl/decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct ImportDecl final : Decl
    {
        PathExpr* pathExpr_;
        std::optional<lex::SymId> alias;

        bool is_public = false;

        ImportDecl(PathExpr* pathExpr, const std::optional<lex::SymId> alias, bool is_public,
                   const lex::Loc& loc)
            : Decl(NodeKind::Decl_Import, loc),
              pathExpr_(pathExpr),
              alias(alias),
              is_public(is_public)
        {
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void ImportDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //IMPORT_DECL_HPP
