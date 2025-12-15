//
// Created by yhwach on 8/21/25.
//

#ifndef EXPR_HPP
#define EXPR_HPP

#include "../../node.hpp"
#include "../visit/visitable.hpp"


namespace ast
{
    namespace visitor
    {
        struct ExprVisitor;
    }

    struct Expr : Node, Visitable<visitor::ExprVisitor>
    {
        using Node::Node, Visitable::accept;

        virtual ~Expr() = default;
    };

    typedef Expr* ExprPtr;
}


#endif //EXPR_HPP
