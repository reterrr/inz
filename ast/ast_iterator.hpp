//
// Created by yhwach on 9/10/25.
//

#ifndef AST_ITERATOR_HPP
#define AST_ITERATOR_HPP

#include "visit/decl_visitor.hpp"
#include "visit/expr_visitor.hpp"
#include "visit/module_visitor.hpp"
#include "visit/overallvisitor.hpp"
#include "visit/stmt_visitor.hpp"

namespace ast {
    struct AstIteratorVisitor : visitor::OverallVisitor {
        using OverallVisitor::visit;
    };
}

#endif //AST_ITERATOR_HPP
