//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_PATH_EXPR_HPP
#define INZ_PATH_EXPR_HPP
#include <vector>

#include "expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct PathExpr final : Expr
    {
        std::vector<lex::SymId> path_;

        PathExpr(std::vector<lex::SymId>&& path, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Path, loc), path_(std::move(path))
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void PathExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_PATH_EXPR_HPP