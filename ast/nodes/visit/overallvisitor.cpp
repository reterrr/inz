//
// Created by yhwach on 9/26/25.
//

#include "overallvisitor.hpp"

#include <algorithm>

#include "function_decl.hpp"
#include "struct_decl.hpp"
#include "var_decl.hpp"
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/init_declarator_expr.hpp"
#include "expr/obj_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/unary_op_expr.hpp"
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
    if (f.body) f.body->accept(*this);
    std::ranges::for_each(f.params, [this](auto &p) { p->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(TypeAliasDecl &t) {
    (void) t;
}

void ast::visitor::OverallVisitor::visit(ImportDecl &i) {
    (void) i;
}

void ast::visitor::OverallVisitor::visit(VarDecl &v) {
    std::ranges::for_each(v.declarators, [this](auto &d) { d->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(StructDecl &s) {
    std::ranges::for_each(s.fields, [this](auto &f) { f->accept(*this); });
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
    if (u.expr) u.expr->accept(*this);
}

void ast::visitor::OverallVisitor::visit(BinaryExpr &b) {
    if (b.lhs) b.lhs->accept(*this);
    if (b.rhs) b.rhs->accept(*this);
}

void ast::visitor::OverallVisitor::visit(StringLiteralExpr &s) {
    (void) s;
}

void ast::visitor::OverallVisitor::visit(ObjLiteralExpr &o) {
    std::ranges::for_each(o.elements, [this](auto &f) { f->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(AssignExpr &a) {
    if (a.lhs) a.lhs->accept(*this);
    if (a.rhs) a.rhs->accept(*this);
}

void ast::visitor::OverallVisitor::visit(InitDeclarator &i) {
    if (i.init) i.init->accept(*this);
}

void ast::visitor::OverallVisitor::visit(FieldExpr &f) {
    if (f.base) f.base->accept(*this);
}

void ast::visitor::OverallVisitor::visit(CallExpr &e) {
    if (e.callee) e.callee->accept(*this);
    std::ranges::for_each(e.args, [this](auto &a) { a->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(RefExpr &r) {
    if (r.binding) r.binding->accept(*this);
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
    if (i.condition) i.condition->accept(*this);
    if (i.thenBody) i.thenBody->accept(*this);
}

void ast::visitor::OverallVisitor::visit(BlockStatement &b) {
    std::ranges::for_each(b.statements, [this](auto &s) { s.accept(*this); });
}

void ast::visitor::OverallVisitor::visit(WhileStatement &w) {
    if (w.condition) w.condition->accept(*this);
    if (w.body) w.body->accept(*this);
}

void ast::visitor::OverallVisitor::visit(VarDeclStatement &v) {
    std::ranges::for_each(v.declarators, [this](auto &d) { d->accept(*this); });
}

void ast::visitor::OverallVisitor::visit(ReturnStatement &r) {
    if (r.expr) r.expr->accept(*this);
}

void ast::visitor::OverallVisitor::visit(ExprStatement &e) {
    if (e.expr) e.expr->accept(*this);
}

void ast::visitor::OverallVisitor::visit(ContinueStatement &c) {
    (void) c;
}

void ast::visitor::OverallVisitor::visit(BreakStatement &b) {
    (void) b;
}

void ast::visitor::OverallVisitor::visit(DoWhileStatement &d) {
    if (d.condition) d.condition->accept(*this);
    if (d.body) d.body->accept(*this);
}

void ast::visitor::OverallVisitor::visit(Module &m) {
    std::ranges::for_each(m.decls, [this](auto &d) { d->accept(*this); });
    std::ranges::for_each(m.imports, [this](auto &i) { i->accept(*this); });
}
