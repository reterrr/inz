//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_MODULE_PASS_HPP
#define INZ_MODULE_PASS_HPP
#include "ast_iterator.hpp"

namespace sema::pass
{
    class MudulePassAstVisitor final : ast::AstIteratorVisitor
    {
    public:
        void visit(ast::ImportDecl&) override;
        void visit(ast::Module&) override;
    };

    class ModulePass
    {
    };
}


#endif //INZ_MODULE_PASS_HPP
