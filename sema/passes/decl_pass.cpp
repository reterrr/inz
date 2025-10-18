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
#include "ast/nodes/decl/field_decl.hpp"
#include "ast/nodes/module/import_decl.hpp"
#include "ast/nodes/stmt/var_decl_statement.hpp"

#include "ast/nodes/expr/init_declarator_expr.hpp"

using sema::Symbol;
using sema::SymbolKind;
using sema::Visibility;
using sema::Mutability;
using sema::Storage;

namespace sema::pass {
    // -------- ctor --------
    DeclPassAstIteratorVisitor::DeclPassAstIteratorVisitor(SymbolTable &symtab)
        : symbol_table(symtab) {
    }

    // -------- ParamDecl --------
    void DeclPassAstIteratorVisitor::visit(ast::ParamDecl &p) {
        Symbol sym;
        sym.id = p.name;
        sym.kind = SymbolKind::Param;
        sym.loc = p.location_;
        sym.type = p.type;
        sym.decl = &p;
        // Optional mutability if you carry it on ParamDecl (spec/qual):
        // sym.mut = (p.spec == ast::TypeSpecifier::Mut) ? Mutability::Mut : Mutability::Imm;

        (void) symbol_table.declare(sym);
        // Do not recurse; parameters don't have nested decls.
    }

    // -------- FunctionDecl --------
    void DeclPassAstIteratorVisitor::visit(ast::FunctionDecl &f) {
        Symbol sym;
        sym.id = f.name;
        sym.kind = SymbolKind::Func;
        sym.loc = f.location_;
        // If your FunctionDecl stores a CallableType* as `type`:
        sym.type = f.type; // adjust if your field is differently named (e.g. f.fn_type)
        sym.decl = &f;

        // Visibility (if you track it on decls; otherwise leave Private)
        // sym.vis = f.is_public ? Visibility::Public : Visibility::Private;

        (void) symbol_table.declare(sym);

        // If your base iterator doesn’t automatically walk params/body and you want it,
        // you could iterate f.params here. Usually Decl pass registers the function,
        // and a separate pass/type pass handles the body.
    }

    // -------- TypeAliasDecl --------

    // -------- ImportDecl --------
    void DeclPassAstIteratorVisitor::visit(ast::ImportDecl &i) {
        // If the import has an alias, declare that alias in the current scope.
        if (i.alias.has_value()) {
            Symbol sym;
            sym.id = *i.alias;
            sym.kind = SymbolKind::ImportAlias;
            sym.loc = i.location_;
            sym.type = nullptr;
            sym.decl = &i;
            // You might also store a pointer to the imported module or export table on the symbol.

            (void) symbol_table.declare(sym);
        }
        // If no alias, you might still expose the last path segment as a namespace symbol,
        // depending on language design. Otherwise, do nothing here.
    }

    // -------- VarDecl (top-level) --------
    void DeclPassAstIteratorVisitor::visit(ast::VarDecl &v) {
        // Assuming VarDecl aggregates multiple declarators (each has a name + optional init).
        // And VarDecl carries the declared type + spec/region.
        for (auto *init: v.declarators) {
            if (!init) continue;

            Symbol sym;
            sym.id = init->name; // or however you store the identifier on the declarator
            sym.kind = SymbolKind::Var;
            sym.loc = init->location_;
            sym.type = v.type; // declared type is on the VarDecl
            sym.decl = &v;

            // Attributes (if present on VarDecl)
            // sym.mut  = to_mutability(static_cast<int>(v.spec));
            // sym.stor = to_storage(static_cast<int>(v.reg));
            sym.mutability = Mutability::Imm;
            sym.storage = Storage::Auto;

            (void) symbol_table.declare(sym);
        }
    }

    // -------- StructDecl --------
    void DeclPassAstIteratorVisitor::visit(ast::StructDecl &s) {
        Symbol sym;
        sym.id = s.name;
        sym.kind = SymbolKind::Struct;
        sym.loc = s.location_;
        // If you have a distinct Type node for struct (e.g., StructType or a path type),
        // you can hang it here; otherwise leave null and resolve later.
        sym.type = nullptr;
        sym.decl = &s;

        (void) symbol_table.declare(sym);

        // NOTE: Don't dump fields into the *global* symbol table.
        // Usually, a struct has its own member table. If/when you add that,
        // you’ll declare its FieldDecls in that member table, not here.
    }

    // -------- FieldDecl (struct member) --------
    void DeclPassAstIteratorVisitor::visit(ast::FieldDecl &f) {
        // Intentionally NO-OP for a *global* SymbolTable.
        // When you give each StructDecl a member table, declare there instead.
        (void) f;
    }

    // -------- VarDeclStatement (local) -------
} // namespace sema::pass
