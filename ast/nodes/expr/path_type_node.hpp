//
// Created by yhwach on 8/25/25.
//

#ifndef PATH_TYPE_NODE_HPP
#define PATH_TYPE_NODE_HPP
#include <token.hpp>
#include <vector>

#include "type_node.hpp"

namespace ast {
    struct PathTypeNode : TypeNode {
        std::vector<lex::SymId> segments;
    };
}

#endif //PATH_TYPE_NODE_HPP
