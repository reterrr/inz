//
// Created by yhwach on 8/29/25.
//

#ifndef OBJ_EXPR_HPP
#define OBJ_EXPR_HPP

#include "literal_expr.hpp"
#include "types.hpp"
#include "expr/path_type_expr.hpp"
#include "type/type_arged_expr.hpp"

namespace ast
{
    struct StructLiteralExpr final : LiteralExpr, TypeArgedExpr
    {
        Expr* expr_; // will be filtered during sema
        std::vector<FieldInitExpr*> elements_;

        StructLiteralExpr(Expr* type,
                          std::vector<TypeExpr*>&& typeArgs,
                          std::vector<FieldInitExpr*>&& elements,
                          const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Struct, loc),
              TypeArgedExpr(TypeArgedKind::PathType, std::move(typeArgs), this),
              expr_(type), elements_(std::move(elements))
        {
            std::ranges::for_each(elements_, [this](FieldInitExpr*& e)
            {
                e->parent = this;
            });
            expr_->parent = this;
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void StructLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //OBJ_EXPR_HPP
