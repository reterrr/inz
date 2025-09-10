//
// Created by yhwach on 8/20/25.
//


#ifndef NODE_H
#define NODE_H
#include <token.hpp>


class node {
    node_kind kind_;
    lex::Loc loc_;
    std::remove
    type *type_{nullptr};

    node(node_kind kind, const lex::Loc &loc)
        : kind_(kind), loc_(loc) {
    }

    virtual ~node() = default;
};


#endif
