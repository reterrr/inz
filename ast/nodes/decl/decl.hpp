//
// Created by yhwach on 8/28/25.
//

#ifndef DECL_HPP
#define DECL_HPP
#include "node.hpp"
#include "visit/visitable.hpp"

namespace ast {
    namespace visitor {
        struct DeclVisitor;
    }

    struct Decl : Node, Visitable<visitor::DeclVisitor> {
        using Node::Node, Visitable::accept;
    };

    typedef Decl *DeclPtr;
}


#endif //DECL_HPP
