//
// Created by yhwach on 9/26/25.
//

#include "overallvisitor.hpp"

#include <algorithm>

#include "stmt/block_statement.hpp"
#include "decl/param_decl.hpp"
#include "expr/field_init_expr.hpp"
#include "decl/function_decl.hpp"
#include "decl/struct_decl.hpp"
#include "decl/var_decl.hpp"
#include "module/import_decl.hpp"
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"

#include "expr/init_declarator_expr.hpp"
#include "expr/obj_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "module/module.hpp"

#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_decl_statement.hpp"
#include "stmt/while_statement.hpp"

void ast::visitor::OverallVisitor::visit(ParamDecl &p) {
    (void) p;
}

void ast::visitor::OverallVisitor::visit(FunctionDecl &f) {
    if (f.body_) f.body_->accept(*this);
    std::ranges::for_each(f.params_, [this](auto &p) { p->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(TypeAliasDecl &t) {
    (void) t;
}

void ast::visitor::OverallVisitor::visit(ImportDecl &i) {
    (void) i;
}

void ast::visitor::OverallVisitor::visit(VarDecl &v) {
    v.declarator->accept(*this);
}

void ast::visitor::OverallVisitor::visit(StructDecl &s) {
    std::ranges::for_each(s.fields_, [this](auto &f) { f->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(FieldDecl &f) {
    (void) f;
}

void ast::visitor::OverallVisitor::visit(IntLiteralExpr &i) {
    (void) i;
}

void ast::visitor::OverallVisitor::visit(FloatLiteralExpr &f) {
    (void) f;
}

void ast::visitor::OverallVisitor::visit(UnaryExpr &u) {
    if (u.expr_) u.expr_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(BinaryExpr &b) {
    if (b.lhs_) b.lhs_->accept(*this);
    if (b.rhs_) b.rhs_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(StringLiteralExpr &s) {
    (void) s;
}

void ast::visitor::OverallVisitor::visit(ObjLiteralExpr &o) {
    std::ranges::for_each(o.elements_, [this](auto &f) { f->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(AssignExpr &a) {
    if (a.lhs_) a.lhs_->accept(*this);
    if (a.rhs_) a.rhs_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(InitDeclarator &i) {
    if (i.init_) i.init_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(FieldExpr &f) {
    if (f.base_) f.base_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(CallExpr &e) {
    if (e.callee_) e.callee_->accept(*this);
    std::ranges::for_each(e.args_, [this](auto &a) { a->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(RefExpr &r) {
    if (r.binding_) r.binding_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(IndexExpr &i) {
    //TODO: add index expr
    (void) i;
}

void ast::visitor::OverallVisitor::visit(BoolLiteralExpr &b) {
    (void) b;
}

void ast::visitor::OverallVisitor::visit(FieldInitExpr &f) {
    (void) f;
}

void ast::visitor::OverallVisitor::visit(IfStatement &i) {
    if (i.condition_) i.condition_->accept(*this);
    if (i.thenBody_) i.thenBody_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(BlockStatement &b) {
    std::ranges::for_each(b.statements_, [this](auto &s) { s->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(WhileStatement &w) {
    if (w.condition_) w.condition_->accept(*this);
    if (w.body_) w.body_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(ReturnStatement &r) {
    if (r.expr_) r.expr_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(ExprStatement &e) {
    if (e.expr_) e.expr_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(ContinueStatement &c) {
    (void) c;
}

void ast::visitor::OverallVisitor::visit(BreakStatement &b) {
    (void) b;
}

void ast::visitor::OverallVisitor::visit(DoWhileStatement &d) {
    if (d.condition_) d.condition_->accept(*this);
    if (d.body_) d.body_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(VarDeclStatement &v) {
    if (v.decl_) v.decl_->accept(*this);
}

void ast::visitor::OverallVisitor::visit(Module &m) {
    std::ranges::for_each(m.decls, [this](auto &d) { d->accept(*this); });
    std::ranges::for_each(m.imports, [this](auto &i) { i->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(VarsDecl &) {
}

void ast::visitor::OverallVisitor::visit(VarsDeclStatement &) {
}
