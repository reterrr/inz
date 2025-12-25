//
// Created by yhwach on 12/21/25.
//

#include "module_pass.hpp"

void sema::pass::MudulePassAstVisitor::visit(ast::ImportDecl& import_decl)
{
    AstIteratorVisitor::visit(import_decl);
}

void sema::pass::MudulePassAstVisitor::visit(ast::Module& module)
{
    AstIteratorVisitor::visit(module);
}
