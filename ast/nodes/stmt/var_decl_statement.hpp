//
// Created by yhwach on 8/29/25.
//

#ifndef VAR_DECL_STATEMENT_HPP
#define VAR_DECL_STATEMENT_HPP

#include <token.hpp>

#include "statement.hpp"
#include "../expr/expr.hpp"

#include "../visit/stmt_visitor.hpp"

namespace ast {
    struct Type;
    struct InitDeclarator;

    struct VarDeclStatement final : Statement {
        Type *type{nullptr};
        TypeSpecifier specifier;
        TypeRegion region;
        std::vector<InitDeclarator *> declarators;

        VarDeclStatement(std::vector<InitDeclarator *> &&declarators,
                         Type *type,
                         const lex::Loc &loc,
                         const TypeSpecifier specifier = TypeSpecifier::Imm,
                         const TypeRegion region = TypeRegion::Auto
        )
            : Statement(NodeKind::Stmt_VarDecl, loc),
              type(type), specifier(specifier), region(region),
              declarators(std::move(declarators)) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void VarDeclStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //VAR_DECL_STATEMENT_HPP
