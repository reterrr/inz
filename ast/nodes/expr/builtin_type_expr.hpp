//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_BUILTIN_TYPE_EXPR_HPP
#define INZ_BUILTIN_TYPE_EXPR_HPP

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

#include "types.hpp"


namespace ast
{
    struct BuiltinTypeExpr final : TypeExpr
    {
        kl::rt::BuiltinTypeExprKind kind_;

        BuiltinTypeExpr(kl::rt::BuiltinTypeExprKind kind, const lex::Loc& loc)
            : TypeExpr(TypeExprKind::Builtin, loc),
              kind_(kind)
        {
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void BuiltinTypeExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //INZ_BUILTIN_TYPE_EXPR_HPP
