//
// Created by yhwach on 11/2/25.
//

#ifndef SEMA_H
#define SEMA_H

#include "ast.hpp"
#include "scope_stack.hpp"
#include "passes/decl_pass.hpp"
#include "passes/pass.hpp"

namespace sema {
    class Sema final {
        ast::AST &ast_;
        ScopeStack stack_;


    public:
        explicit Sema(ast::AST &ast)
            : ast_(ast) {
        }
    };
}


#endif
