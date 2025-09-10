//
// Created by yhwach on 9/1/25.
//

#ifndef MODULE_VISITOR_HPP
#define MODULE_VISITOR_HPP
#include "visitor.hpp"

namespace ast {
    struct Module;
}

namespace ast::visitor {
    struct ModuleVisitor : Visitor<Module> {};
}

#endif //MODULE_VISITOR_HPP
