//
// Created by yhwach on 9/10/25.
//

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <algorithm>
#include <vector>

#include "../node.hpp"

#include "visit/project_visitor.hpp"
#include "ast/nodes/module/module.hpp"

namespace ast
{
    struct Module;
    using ModulePtr = Module*;

    struct Project final
        : Node, Visitable<visitor::ProjectVisitor>
    {
        std::vector<ModulePtr> modules;

        Project(std::vector<ModulePtr>&& modules,
                const lex::Loc& loc)
            : Node(NodeKind::Project, loc),
              modules(std::move(modules))
        {
            std::ranges::for_each(modules, [this](auto& m)
            {
                m->parent = this;
            });
        }

        void accept(visitor::ProjectVisitor& v) override
        {
            v.visit(*this);
        }
    };
}

#endif //PROJECT_HPP
