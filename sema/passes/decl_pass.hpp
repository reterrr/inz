//
// Created by yhwach on 9/26/25.
//

#ifndef DECL_PASS_HPP
#define DECL_PASS_HPP

#include "ast_iterator.hpp"
#include "param_decl.hpp"
#include "pass.hpp"


namespace ast {
    struct Project;
}

namespace sema {
    class ScopeStack;
    class SymbolTable;

    namespace pass {
        struct DeclPassAstIteratorVisitor final : ast::AstIteratorVisitor {
            SymbolTable &symbol_table;
            ScopeStack &scope_stack;

            void visit(ast::ParamDecl &p) override;

            void visit(ast::FunctionDecl &f) override;

            void visit(ast::ImportDecl &i) override;

            void visit(ast::VarDecl &v) override;

            void visit(ast::StructDecl &s) override;

            void visit(ast::FieldDecl &f) override;


            void visit(ast::Module &) override;

            void visit(ast::BlockStatement &) override;

            explicit DeclPassAstIteratorVisitor(SymbolTable &symbol_table);
        };

        struct DeclPass final : Pass<DeclPassAstIteratorVisitor> {
            DeclPass(ast::Project *root, SymbolTable &symbol_table)
                : Pass(root, DeclPassAstIteratorVisitor{symbol_table}) {
            }
        };
    }
}

#endif //DECL_PASS_HPP
