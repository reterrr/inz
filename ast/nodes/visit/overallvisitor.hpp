//
// Created by yhwach on 9/26/25.
//

#ifndef VISIT_OVERALLVISITOR_H
#define VISIT_OVERALLVISITOR_H

#include "decl_visitor.hpp"
#include "expr_visitor.hpp"
#include "stmt_visitor.hpp"
#include "module/module.hpp"


namespace ast::visitor {
    struct OverallVisitor :
            DeclVisitor,
            ExprVisitor,
            StmtVisitor,
            ModuleVisitor {
        void visit(ParamDecl &) override;

        void visit(FunctionDecl &) override;

        void visit(TypeAliasDecl &) override;

        void visit(ImportDecl &) override;

        void visit(VarDecl &) override;

        void visit(StructDecl &) override;

        void visit(FieldDecl &) override;

        void visit(IntLiteralExpr &) override;

        void visit(FloatLiteralExpr &) override;

        void visit(UnaryExpr &) override;

        void visit(BinaryExpr &) override;

        void visit(StringLiteralExpr &) override;

        void visit(ObjLiteralExpr &) override;

        void visit(AssignExpr &) override;

        void visit(InitDeclarator &) override;

        void visit(FieldExpr &) override;

        void visit(CallExpr &) override;

        void visit(RefExpr &) override;

        void visit(IndexExpr &) override;

        void visit(BoolLiteralExpr &) override;

        void visit(FieldInitExpr &) override;

        void visit(IfStatement &) override;

        void visit(BlockStatement &) override;

        void visit(WhileStatement &) override;

        void visit(VarDeclStatement &) override;

        void visit(ReturnStatement &) override;

        void visit(ExprStatement &) override;

        void visit(ContinueStatement &) override;

        void visit(BreakStatement &) override;

        void visit(DoWhileStatement &) override;

        void visit(Module &) override;
    };
}


#endif
