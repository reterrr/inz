//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_PATH_TYPE_EXPR_HPP
#define INZ_PATH_TYPE_EXPR_HPP

#include <vector>

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct PathTypeExpr final : TypeExpr
    {
        std::vector<lex::SymId> path_;

        PathTypeExpr(std::vector<lex::SymId>&& path, const lex::Loc& loc)
            : TypeExpr(Kind::Path, loc), path_(std::move(path))
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void PathTypeExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_PATH_TYPE_EXPR_HPP
