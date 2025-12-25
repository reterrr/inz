//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_ARRAY_TYPE_EXPRESSION_HPP
#define INZ_ARRAY_TYPE_EXPRESSION_HPP

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct ArrayTypeExpr final : TypeExpr
    {
        TypeExpr* type_;
        ExprPtr sizeExpr_;

        ArrayTypeExpr(TypeExpr* type, ExprPtr sizeExpr, const lex::Loc& loc)
            : TypeExpr(TypeExprKind::Array, loc), type_(type), sizeExpr_(sizeExpr)
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void ArrayTypeExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_ARRAY_TYPE_EXPRESSION_HPP
