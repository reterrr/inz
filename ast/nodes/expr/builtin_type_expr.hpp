//
// Created by yhwach on 12/15/25.
//

#ifndef INZ_BUILTIN_TYPE_EXPR_HPP
#define INZ_BUILTIN_TYPE_EXPR_HPP

#include "type_expr.hpp"
#include "visit/expr_visitor.hpp"


namespace ast
{
    struct BuiltinTypeExpr final : TypeExpr
    {
        enum class Kind
        {
            I8, U8,
            I16, U16,
            I32, U32,
            I64, U64,
            I128, U128,

            F32, F64,

            Bool,

            Char
        };

        Kind kind_;

        BuiltinTypeExpr(Kind kind, const lex::Loc& loc)
            : TypeExpr(TypeExpr::Kind::Builtin, loc),
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
