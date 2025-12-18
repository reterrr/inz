#include "scope_pass.hpp"

#include "function_decl.hpp"
#include "param_decl.hpp"
#include "type_alias_decl.hpp"
#include "var_decl.hpp"
#include "module/import_decl.hpp"
#include "sema/scope_guard.hpp"
#include "stmt/block_statement.hpp"
#include "decl/struct_decl.hpp"

namespace sema::pass
{
    ScopeAstVisitor::ScopeAstVisitor(ScopeController& controller)
        : controller_(controller)
    {
    }

    void ScopeAstVisitor::visit(ast::Module& m)
    {
        ScopeGuard guard{controller_};
        m.id = controller_.enterScope(m.package_path, scope::ScopeKind::Module);


        for (auto* decl : m.decls)
            decl->accept(*this);

        for (auto* imp : m.imports)
            imp->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::FunctionDecl& decl)
    {
        ScopeGuard guard{controller_};
        decl.id = controller_.enterScope(decl.name_, scope::ScopeKind::Function);


        for (auto* param : decl.params_)
            param->accept(*this);

        if (decl.body_)
            decl.body_->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::BlockStatement& stmt)
    {
        ScopeGuard guard{controller_};
        stmt.id = controller_.enterScope(AnonymousScopeTag{}, scope::ScopeKind::Anon);

        for (auto* s : stmt.statements_)
            s->accept(*this);
    }

    void ScopeAstVisitor::visit(ast::StructDecl& struct_decl)
    {
        ScopeGuard guard{controller_};
        struct_decl.id =
            controller_.enterScope(struct_decl.name, scope::ScopeKind::Struct);


        AstIteratorVisitor::visit(struct_decl);
    }

    void ScopeAstVisitor::visit(ast::ParamDecl& param_decl)
    {
        param_decl.id = controller_.current();
        AstIteratorVisitor::visit(param_decl);
    }

    void ScopeAstVisitor::visit(ast::TypeAliasDecl& type_alias_decl)
    {
        type_alias_decl.id = controller_.current();
        AstIteratorVisitor::visit(type_alias_decl);
    }

    void ScopeAstVisitor::visit(ast::ImportDecl& import_decl)
    {
        import_decl.id = controller_.current();
        AstIteratorVisitor::visit(import_decl);
    }

    void ScopeAstVisitor::visit(ast::VarDecl& var_decl)
    {
        var_decl.id = controller_.current();
        AstIteratorVisitor::visit(var_decl);
    }

    void ScopeAstVisitor::visit(ast::FieldDecl& field_decl)
    {
        field_decl.id = controller_.current();
        AstIteratorVisitor::visit(field_decl);
    }

    void ScopeAstVisitor::visit(ast::IntLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FloatLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::UnaryExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::BinaryExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::StringLiteralExpr& e) { AstIteratorVisitor::visit(e); }

    void ScopeAstVisitor::visit(ast::StructLiteralExpr& struct_literal_expr)
    {
        AstIteratorVisitor::visit(struct_literal_expr);
    }

    void ScopeAstVisitor::visit(ast::AssignExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FieldExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::CallExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::RefExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::IndexExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::BoolLiteralExpr& e) { AstIteratorVisitor::visit(e); }
    void ScopeAstVisitor::visit(ast::FieldInitExpr& e) { AstIteratorVisitor::visit(e); }

    void ScopeAstVisitor::visit(ast::IfStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::WhileStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::DoWhileStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ReturnStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ExprStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::ContinueStatement& s) { AstIteratorVisitor::visit(s); }
    void ScopeAstVisitor::visit(ast::BreakStatement& s) { AstIteratorVisitor::visit(s); }

    void ScopeAstVisitor::visit(ast::VarDeclStatement& s) { AstIteratorVisitor::visit(s); }

    void ScopeAstVisitor::visit(ast::Project& project)
    {
        ScopeGuard guard{controller_};
        project.id = controller_.enterProject();

        std::ranges::for_each(project.modules, [this](auto& module)
        {
            module->accept(*this);
        });
    }

    ScopeAstVisitor::~ScopeAstVisitor()
    = default;

    void ScopeAstVisitor::visit(ast::ArrayTypeExpr&)
    {
    }

    void ScopeAstVisitor::visit(ast::PathTypeExpr&)
    {
    }

    void ScopeAstVisitor::visit(ast::RefTypeExpr&)
    {
    }

    void ScopeAstVisitor::visit(ast::BuiltinTypeExpr&)
    {
    }

    ScopePass::ScopePass(ast::Project* root, ScopeController& controller)
        : Pass(root, ScopeAstVisitor{controller})
    {
    }
}
