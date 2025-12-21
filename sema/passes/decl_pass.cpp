//
// Created by yhwach on 10/3/25.
//
// decl_pass_visitor.cpp

#include "sema/passes/decl_pass.hpp"

#include "sema/symbol_table.hpp"
#include "sema/symbol.hpp"

#include "ast/nodes/decl/function_decl.hpp"
#include "ast/nodes/decl/param_decl.hpp"

#include "ast/nodes/decl/var_decl.hpp"
#include "ast/nodes/decl/struct_decl.hpp"
#include "ast/nodes/module/import_decl.hpp"
#include "ast/nodes/stmt/var_decl_statement.hpp"

#include "ast/nodes/expr/init_declarator_expr.hpp"

#include "stmt/block_statement.hpp"

using sema::Symbol;
using sema::SymbolKind;
using sema::Visibility;
using sema::Mutability;
using sema::Storage;

namespace sema::pass
{
    DeclPassAstIteratorVisitor::DeclPassAstIteratorVisitor(SymbolTable& symbol_table)
        : symbol_table(symbol_table)
    {
    }

    void DeclPassAstIteratorVisitor::visit(ast::ParamDecl& p)
    {
        Symbol sym;
        sym.id = p.name;
        sym.kind = SymbolKind::Param;
        sym.loc = p.location_;
        sym.type = p.type;
        sym.decl = &p;
        sym.mutability = (p.type->specifier == ast::TypeSpecifier::Imm)
                             ? Mutability::Imm
                             : Mutability::Mut;


        (void)symbol_table.declare(sym);
    }

    void DeclPassAstIteratorVisitor::visit(ast::FunctionDecl& f)
    {
        Symbol sym;
        sym.id = f.name;
        sym.kind = SymbolKind::Func;
        sym.loc = f.location_;

        sym.type = f.type;
        sym.decl = &f;


        (void)symbol_table.declare(sym);
    }

    void DeclPassAstIteratorVisitor::visit(ast::ImportDecl& i)
    {
        if (i.alias.has_value())
        {
            Symbol sym;
            sym.id = *i.alias;
            sym.kind = SymbolKind::ImportAlias;
            sym.loc = i.location_;
            sym.type = nullptr;
            sym.decl = &i;

            (void)symbol_table.declare(sym);
        }
    }

    void DeclPassAstIteratorVisitor::visit(ast::VarDecl& v)
    {
        auto* init = v.declarator;
        if (!init) return;

        Symbol sym;
        sym.id = init->name;
        sym.kind = SymbolKind::Var;
        sym.loc = init->location_;
        sym.type = v.type_;
        sym.decl = &v;

        sym.mutability = Mutability::Imm;
        sym.storage = Storage::Auto;

        (void)symbol_table.declare(sym);
    }

    void DeclPassAstIteratorVisitor::visit(ast::StructDecl& s)
    {
        Symbol sym;
        sym.id = s.name_;
        sym.kind = SymbolKind::Struct;
        sym.loc = s.location_;

        sym.type = nullptr;
        sym.decl = &s;

        (void)symbol_table.declare(sym);
    }

    void DeclPassAstIteratorVisitor::visit(ast::FieldDecl& f)
    {
        Symbol sym;
        sym.id = f.name;
        sym.kind = SymbolKind::Field;
        sym.loc = f.location_;
        sym.type = f.type;
        sym.decl = &f;
        sym.mutability = (f.type->specifier == ast::TypeSpecifier::Imm)
                             ? Mutability::Imm
                             : Mutability::Mut;

        (void)symbol_table.declare(sym);
    }

    void DeclPassAstIteratorVisitor::visit(ast::Module& module)
    {
    }

    void DeclPassAstIteratorVisitor::visit(ast::BlockStatement& b)
    {
    }
}
