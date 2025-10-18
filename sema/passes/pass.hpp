//
// Created by yhwach on 9/26/25.
//

#ifndef PASSES_HPP
#define PASSES_HPP
#include "project.hpp"
#include "module/module.hpp"

namespace ast {
    struct Project;
}

namespace sema::pass {
    template<typename VisitorT>
    class Pass {
        ast::Project *root;
        VisitorT visitor;

        Pass(ast::Project *root, VisitorT &&visitor);

    public:
        void run() {
            for (auto *m: root->modules) m->accept(visitor);
        }
    };
}

#endif //PASSES_HPP
