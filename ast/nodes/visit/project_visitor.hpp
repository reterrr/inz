//
// Created by yhwach on 12/5/25.
//

#ifndef INZ_PROJECT_VISITOR_HPP
#define INZ_PROJECT_VISITOR_HPP
#include "visitor.hpp"

namespace ast
{
    struct Project;
}

namespace ast::visitor
{
    struct ProjectVisitor :
        Visitor<Project>
    {
    };
}

#endif //INZ_PROJECT_VISITOR_HPP
