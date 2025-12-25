//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_REF_TYPE_EXPR_HPP
#define INZ_REF_TYPE_EXPR_HPP

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"
#include "stmt/var_mutablity_storage.hpp"

namespace ast
{
    struct RefTypeExpr final : TypeExpr
    {
        Mutability mut_;
        TypeExpr* pointee_;

        RefTypeExpr(TypeExpr* pointee, Mutability mut, const lex::Loc& loc)
            : TypeExpr(TypeExprKind::Ref, loc),
              mut_(mut),
              pointee_(pointee)
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void RefTypeExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_REF_TYPE_EXPR_HPP
