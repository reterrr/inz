//
// Created by yhwach on 8/29/25.
//

#ifndef OBJ_EXPR_HPP
#define OBJ_EXPR_HPP

#include "literal_expr.hpp"
#include "types.hpp"
#include "expr/path_type_expr.hpp"

namespace ast
{
    // when we write e.g. Obj eg = Obj{ a, b, 1 };
    struct StructLiteralExpr final : LiteralExpr
    {
        PathTypeExpr* type_;
        std::vector<FieldInitExpr*> elements_;

        StructLiteralExpr(PathTypeExpr* type, std::vector<FieldInitExpr*>&& elements, const lex::Loc& loc)
            : LiteralExpr(kl::rt::LiteralExprKind::Struct, loc),
              type_(type), elements_(std::move(elements))
        {
            std::ranges::for_each(elements_, [this](FieldInitExpr*& e)
            {
                e->parent = this;
            });
            type_->parent = this;
        }

        void accept(visitor::ExprVisitor&) override;
    };

    inline void StructLiteralExpr::accept(visitor::ExprVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //OBJ_EXPR_HPP
