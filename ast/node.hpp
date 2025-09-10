//
// Created by yhwach on 8/20/25.
//

#ifndef NODE_HPP
#define NODE_HPP
#include <token.hpp>

#include "node_type .hpp"

namespace ast {
    struct Node;
    typedef Node* NodePtr;

    struct Node {
        virtual ~Node() = default;

        Node(const NodeKind nodeType, const lex::Loc &loc) :
            nodeType_(nodeType), location_(loc) {}

        NodeKind nodeType_;
        lex::Loc location_;
    };
}


#endif //NODE_HPP
