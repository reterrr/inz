//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_REF_TYPE_EXPR_HPP
#define INZ_REF_TYPE_EXPR_HPP

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"

namespace ast
{
    struct RefTypeExpr final : TypeExpr
    {
        enum class Mutability { Imm, Mut };

        Mutability mut_;
        TypeExpr* pointee_;

        RefTypeExpr(TypeExpr* pointee, Mutability mut, const lex::Loc& loc)
            : TypeExpr(Kind::Ref, loc),
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
