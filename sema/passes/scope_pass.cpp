// scope_pass.cpp
//
// Builds a scope tree and annotates AST nodes with the scope they belong to.
// Key policy implemented here:
//
// 1) Project -> Module -> (Struct | Function) create named scopes.
// 2) Function parameters live in the Function scope.
// 3) Function body does NOT implicitly create an extra anonymous scope
//    (that is the purpose of FunctionBlockStatement).
// 4) Ordinary `{ ... }` blocks create Anon scopes.
// 5) Control-flow bodies create *typed* scopes on their body blocks:
//    - if-then block  => ScopeKind::If
//    - else-if block  => ScopeKind::ElseIf
//    - else block     => ScopeKind::Else
//    - while body     => ScopeKind::While
//    - do-while body  => ScopeKind::DoWhile
//
// NOTE: This file assumes FunctionBlockStatement has a `BlockStatement* block_`
// (or similar) that holds the underlying parsed `{ ... }` body.
// If your member name differs, rename `block_` accordingly.

#include "scope_pass.hpp"

#include "decl/struct_decl.hpp"
#include "function_decl.hpp"
#include "module/import_decl.hpp"
#include "param_decl.hpp"
#include "sema/scope_guard.hpp"
#include "stmt/block_statement.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/while_statement.hpp"
#include "type_alias_decl.hpp"
#include "var_decl.hpp"

// If these are separate headers in your project, include them explicitly.
// If they are nested in if_statement.hpp, remove these.
// #include "stmt/else_if_statement.hpp"
// #include "stmt/else_statement.hpp"
#include "stmt/function_block_statement.hpp"

namespace sema::pass
{
    ScopeAstVisitor::ScopeAstVisitor(ScopeController& controller)
        : controller_(controller)
    {
    }

    // -------------------------------------------------------------------------
    // Helpers
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit_block_as_kind(ast::BlockStatement* block, scope::ScopeKind kind)
    {
        if (!block)
            return;

        ScopeGuard guard{controller_};
        block->id = controller_.enterScope(AnonymousScopeTag{}, kind);

        for (auto* s : block->statements_)
            if (s) s->accept(*this);
    }

    void ScopeAstVisitor::visit_block_as_anon(ast::BlockStatement& block)
    {
        ScopeGuard guard{controller_};
        block.id = controller_.enterScope(AnonymousScopeTag{}, scope::ScopeKind::Anon);

        for (auto* s : block.statements_)
            if (s) s->accept(*this);
    }

    // -------------------------------------------------------------------------
    // Project / module / decl scopes
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::Project& project)
    {
        ScopeGuard guard{controller_};
        project.id = controller_.enterProject();

        for (auto& m : project.modules)
            if (m) m->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::Module& m)
    {
        ScopeGuard guard{controller_};
        m.id = controller_.enterScope(m.package_path, scope::ScopeKind::Module);

        // Imports typically affect name resolution in the module scope; visit first.
        for (auto* imp : m.imports)
            if (imp) imp->accept(*this);

        for (auto* decl : m.decls)
            if (decl) decl->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::StructDecl& decl)
    {
        ScopeGuard guard{controller_};
        decl.id = controller_.enterScope(decl.name_, scope::ScopeKind::Struct);

        // Fields (and later: methods/associated items) are within the struct scope.
        AstIteratorVisitor::visit(decl);
    }

    void ScopeAstVisitor::visit(ast::FunctionDecl& decl)
    {
        ScopeGuard guard{controller_};
        decl.id = controller_.enterScope(decl.name_, scope::ScopeKind::Function);

        // Parameters belong to the Function scope.
        for (auto* p : decl.params_)
            if (p) p->accept(*this);

        if (decl.body_)
            decl.body_->accept(*this);
    }

    // -------------------------------------------------------------------------
    // Blocks
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::BlockStatement& stmt)
    {
        // Generic `{ ... }` in statements: anonymous scope.
        // Control-flow bodies are handled by their statement visitors (If/While/DoWhile),
        // which *do not* call BlockStatement::accept() for their bodies.
        visit_block_as_anon(stmt);
    }

    void ScopeAstVisitor::visit(ast::FunctionBlockStatement& s)
    {
        // Function body is NOT a new anonymous scope.
        // It is executed "in" the function scope (locals declared at top level of the
        // body belong to the function scope), while nested blocks still create Anon scopes.

        s.id = controller_.current();

        // IMPORTANT:
        // Do NOT call `s.block_->accept(*this)` if that would route to visit(BlockStatement)
        // and create an Anon scope. Instead, traverse statements directly.
        //
        // Rename `block_` to your actual member name.
        if (s.block_)
        {
            s.block_->id = controller_.current();
            for (auto* st : s.block_->statements_)
                if (st) st->accept(*this);
        }
    }

    // -------------------------------------------------------------------------
    // Control-flow statements: create scope on the body block with a specific kind
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::IfStatement& s)
    {
        // The "if" statement itself is not a scope; each branch body is.
        s.id = controller_.current();

        if (s.condition_)
            s.condition_->accept(*this);

        // then-body gets ScopeKind::If
        visit_block_as_kind(s.thenBody_, scope::ScopeKind::If);

        // else-if bodies
        for (auto* eif : s.elseIfs_)
            if (eif) eif->accept(*this);

        // else body
        if (s.else_)
            s.else_->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::ElseIfStatement& s)
    {
        s.id = controller_.current();

        if (s.condition_)
            s.condition_->accept(*this);

        visit_block_as_kind(s.then_, scope::ScopeKind::ElseIf);
    }

    void ScopeAstVisitor::visit(ast::ElseStatement& s)
    {
        s.id = controller_.current();
        visit_block_as_kind(s.then_, scope::ScopeKind::Else);
    }

    void ScopeAstVisitor::visit(ast::WhileStatement& s)
    {
        s.id = controller_.current();

        if (s.condition_)
            s.condition_->accept(*this);

        visit_block_as_kind(s.body_, scope::ScopeKind::While);
    }

    void ScopeAstVisitor::visit(ast::DoWhileStatement& s)
    {
        s.id = controller_.current();

        // Body scope first (as DoWhile)
        visit_block_as_kind(s.body_, scope::ScopeKind::DoWhile);

        // Condition is evaluated after the body; it should not see body-local vars.
        if (s.condition_)
            s.condition_->accept(*this);
    }

    // -------------------------------------------------------------------------
    // Leaf-ish decls: bind to current scope
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::ParamDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    void ScopeAstVisitor::visit(ast::TypeParamDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    void ScopeAstVisitor::visit(ast::TypeAliasDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    void ScopeAstVisitor::visit(ast::ImportDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    void ScopeAstVisitor::visit(ast::VarDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    void ScopeAstVisitor::visit(ast::FieldDecl& d)
    {
        d.id = controller_.current();
        AstIteratorVisitor::visit(d);
    }

    // -------------------------------------------------------------------------
    // Statements that do not introduce scope (delegated)
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::VarDeclStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ReturnStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ExprStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ContinueStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::BreakStatement& s) { AstIteratorVisitor::visit(s); }

    // -------------------------------------------------------------------------
    // Exprs: no scope (delegated)
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::IntLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FloatLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::BoolLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::CharLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::StringLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::UnaryExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::BinaryExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::AssignExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FieldExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::CallExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::RefExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::IndexExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FieldInitExpr& e) { AstIteratorVisitor::visit(e); }

    void ScopeAstVisitor::visit(ast::StructLiteralExpr& e) { AstIteratorVisitor::visit(e); }

    // -------------------------------------------------------------------------
    // Type syntax: if you want IDs on type nodes, add them here.
    // For now, no-op is acceptable if types do not carry scope IDs.
    // -------------------------------------------------------------------------

    void ScopeAstVisitor::visit(ast::ArrayTypeExpr&) {}
    void ScopeAstVisitor::visit(ast::PathTypeExpr&) {}
    void ScopeAstVisitor::visit(ast::RefTypeExpr&) {}
    void ScopeAstVisitor::visit(ast::BuiltinTypeExpr&) {}

    // -------------------------------------------------------------------------

    ScopeAstVisitor::~ScopeAstVisitor() = default;

    ScopePass::ScopePass(ast::Project* root, ScopeController& controller)
        : Pass(root, ScopeAstVisitor{controller})
    {
    }
} // namespace sema::pass
