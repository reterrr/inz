//
// Created by yhwach on 11/28/25.
//

#ifndef INZ_SCOPE_PASS_HPP
#define INZ_SCOPE_PASS_HPP

#include "ast_iterator.hpp"
#include "pass.hpp"
#include "sema/scope_stack.hpp"

namespace sema::pass
{
    struct ScopeAstVisitor final
        : ast::AstIteratorVisitor
    {
        ScopeController& controller_;

        explicit ScopeAstVisitor(ScopeController& controller);
        void visit_block_as_kind(ast::BlockStatement* block, scope::ScopeKind kind);

        void visit(ast::Module&) override;
        void visit(ast::FunctionDecl&) override;
        void visit(ast::BlockStatement&) override;
        void visit(ast::ParamDecl&) override;
        void visit(ast::TypeAliasDecl&) override;
        void visit(ast::ImportDecl&) override;
        void visit(ast::VarStmt&) override;
        void visit(ast::StructDecl&) override;
        void visit(ast::FieldDecl&) override;
        void visit(ast::IntLiteralExpr&) override;
        void visit(ast::FloatLiteralExpr&) override;
        void visit(ast::UnaryExpr&) override;
        void visit(ast::BinaryExpr&) override;
        void visit(ast::StringLiteralExpr&) override;
        void visit(ast::StructLiteralExpr&) override;
        void visit(ast::AssignExpr&) override;
        void visit(ast::FieldExpr&) override;
        void visit(ast::CallExpr&) override;
        void visit(ast::RefExpr&) override;
        void visit(ast::IndexExpr&) override;
        void visit(ast::BoolLiteralExpr&) override;
        void visit(ast::CharLiteralExpr& e) override;
        void visit(ast::FieldInitExpr&) override;
        void visit(ast::IfStatement&) override;
        void visit(ast::ElseIfStatement& s) override;
        void visit(ast::ElseStatement& s) override;
        void visit(ast::WhileStatement&) override;
        void visit(ast::ReturnStatement&) override;
        void visit(ast::ExprStatement&) override;
        void visit(ast::ContinueStatement&) override;
        void visit(ast::BreakStatement&) override;
        void visit(ast::DoWhileStatement&) override;
        void visit_block_as_anon(ast::BlockStatement& block);
        void visit(ast::Project&) override;
        ~ScopeAstVisitor() override;
        void visit(ast::ArrayTypeExpr&) override;
        void visit(ast::PathTypeExpr&) override;
        void visit(ast::RefTypeExpr&) override;
        void visit(ast::BuiltinTypeExpr&) override;
        void visit(ast::TypeParamDecl&) override;
    };

    class ScopePass final : public Pass<ScopeAstVisitor>
    {
    public:
        ScopePass(ast::Project* root, ScopeController& controller);
    };
}

#endif //INZ_SCOPE_PASS_HPP
