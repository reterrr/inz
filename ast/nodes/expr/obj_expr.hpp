//
// Created by yhwach on 8/29/25.
//

#ifndef OBJ_EXPR_HPP
#define OBJ_EXPR_HPP

#include "expr.hpp"

namespace ast {
    // when we write e.g. Obj eg = Obj{a, b, 1 };
    struct ObjLiteralExpr final : Expr {
        PathType *type;
        std::vector<FieldInitExpr *> elements_;

        ObjLiteralExpr(PathType *type, std::vector<FieldInitExpr *> &&elements, const lex::Loc &loc)
            : Expr(NodeKind::Expr_ObjLiteral, loc),
              type(type), elements_(std::move(elements)) {
            std::ranges::for_each(elements_, [this](FieldInitExpr *&e) {
                e->parent = this;
            });
        }

        void accept(visitor::ExprVisitor &) override;
    };

    inline void ObjLiteralExpr::accept(visitor::ExprVisitor &v) {
        v.visit(*this);
    }
}

#endif //OBJ_EXPR_HPP
