//
// Created by yhwach on 9/10/25.
//

#ifndef AST_ITERATOR_HPP
#define AST_ITERATOR_HPP

#include "visit/overallvisitor.hpp"

namespace ast {
    struct AstIteratorVisitor : visitor::OverallVisitor {
        using OverallVisitor::visit;
    };
}

#endif //AST_ITERATOR_HPP
