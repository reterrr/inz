//
// Created by yhwach on 8/28/25.
//

#ifndef STATEMENT_HPP
#define STATEMENT_HPP
#include "../../node.hpp"
#include "../visit/visitable.hpp"

namespace ast {
    namespace visitor {
        struct StmtVisitor;
    }

    struct Statement : Node, Visitable<visitor::StmtVisitor> {
        using Node::Node, Visitable::accept;

        virtual ~Statement() = default;
    };

    typedef Statement *StatementPtr;
}


#endif //STATEMENT_HPP
