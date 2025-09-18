//
// Created by yhwach on 9/10/25.
//

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <vector>

#include "../node.hpp"

namespace ast {
    struct Module; using ModulePtr = Module*;
    struct Project final : Node {
        std::vector<ModulePtr> modules;

        Project(std::vector<ModulePtr>&& modules, const lex::Loc &loc)
            : Node(NodeKind::Project, loc),
              modules(std::move(modules)) {
        }
    };
}

#endif //PROJECT_HPP
