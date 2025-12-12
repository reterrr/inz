//
// Created by yhwach on 11/2/25.
//

#ifndef SEMA_H
#define SEMA_H

#include "ast.hpp"
#include "scope_stack.hpp"
#include "passes/scope_pass.hpp"

namespace sema
{
    class Sema final
    {
        ast::AST& ast_;
        ScopeController controller_;

        /// passes
        pass::ScopePass scopePass_;
        std::vector<scope::Scope> scopeTable_;
        scope::Scope2SymbolMap map_;

    public:
        explicit Sema(ast::AST& ast)
            : ast_(ast),
              controller_(map_, scopeTable_),
              scopePass_(ast_.get_project(), controller_)
        {
        }

        void run()
        {
            scopePass_.run();
        }
    };
}


#endif
