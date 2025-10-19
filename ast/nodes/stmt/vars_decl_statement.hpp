//
// Created by yhwach on 10/19/25.
//

#ifndef VARS_DECL_STMT_HPP
#define VARS_DECL_STMT_HPP
#include "statement.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast {
    struct VarsDecl;

    struct VarsDeclStatement final : Statement {
        VarsDecl *varsDecl;

        VarsDeclStatement(VarsDecl *varsDecl, const lex::Loc &loc)
            : Statement(NodeKind::Stmt_VarsDecl_Sugar, loc),
              varsDecl(varsDecl) {
        }

        void accept(visitor::StmtVisitor &) override;
    };

    inline void VarsDeclStatement::accept(visitor::StmtVisitor &v) {
        v.visit(*this);
    }
}

#endif //VARS_DECL_STMT_HPP
