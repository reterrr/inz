//
// Created by yhwach on 12/17/25.
//

#ifndef INZ_CAST_EXPR_HPP
#define INZ_CAST_EXPR_HPP

#include "expr.hpp"
#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct TypeExpr;

    struct CastExpr final : Expr
    {
        Expr* source_;
        TypeExpr* targetSyntax_;

        CastExpr(Expr* source, TypeExpr* target_syntax, const lex::Loc& loc)
            : Expr(NodeKind::Expr_Cast, loc),
              source_(source),
              targetSyntax_(target_syntax)
        {
            source_->parent = this;
            targetSyntax_->parent = this;
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void CastExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_CAST_EXPR_HPP
