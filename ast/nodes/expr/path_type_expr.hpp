//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_PATH_TYPE_EXPR_HPP
#define INZ_PATH_TYPE_EXPR_HPP

#include "path_expr.hpp"
#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct PathTypeExpr final : TypeExpr
    {
        PathExpr* pathExpr_;

        PathTypeExpr(PathExpr* pathExpr, const lex::Loc& loc)
            : TypeExpr(Kind::Path, loc),
              pathExpr_(pathExpr)
        {
            pathExpr_->parent = this;
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void PathTypeExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_PATH_TYPE_EXPR_HPP
