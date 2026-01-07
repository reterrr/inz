//
// Created by yhwach on 9/26/25.
//

#ifndef DECL_PASS_HPP
#define DECL_PASS_HPP

#include "ast_iterator.hpp"
#include "param_decl.hpp"
#include "pass.hpp"
#include "sema/scope_info.hpp"

namespace ast
{
    struct Project;
}

namespace sema
{
    class ScopeController;
    class SymbolTable;

    namespace pass
    {
        /**
         * symbols
         */
        class DeclPassAstIteratorVisitor final
            : ast::AstIteratorVisitor
        {
            SymbolTable& symbol_table;

        public:
            explicit DeclPassAstIteratorVisitor(SymbolTable& symbol_table);

            void visit(ast::BlockStatement&) override;

            void visit(ast::Module&) override;

            void visit(ast::ParamDecl& p) override;

            void visit(ast::FnDecl& f) override;

            void visit(ast::ImportDecl& i) override;

            void visit(ast::VarStmt& v) override;

            void visit(ast::StructDecl& s) override;

            void visit(ast::FieldDecl& f) override;
        };

        struct DeclPass final : Pass<DeclPassAstIteratorVisitor>
        {
            DeclPass(ast::Project* root, SymbolTable& symbol_table)
                : Pass(root, DeclPassAstIteratorVisitor{symbol_table})
            {
            }
        };
    }
}

#endif //DECL_PASS_HPP
