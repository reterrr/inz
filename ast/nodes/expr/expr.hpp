//
// Created by yhwach on 8/21/25.
//

#ifndef EXPR_HPP
#define EXPR_HPP

#include "../../node.hpp"
#include "../visit/visitable.hpp"
#include "../visit/expr_visitor.hpp"

#include "../type/type.hpp"

namespace ast {
    enum class ExprRole {
        Unknown, Place, Value
    };

    struct Expr : Node, Visitable<visitor::ExprVisitor> {
        using Node::Node, Visitable::accept;

        Type *type_;
        ExprRole role{ExprRole::Unknown};

        virtual ~Expr() = default;
    };

    typedef Expr *ExprPtr;
}


#endif //EXPR_HPP
