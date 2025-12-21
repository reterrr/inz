//
// Created by yhwach on 9/26/25.
//

#include "overallvisitor.hpp"

#include "project.hpp"

// decls
#include "decl/function_decl.hpp"
#include "decl/param_decl.hpp"
#include "decl/struct_decl.hpp"
#include "decl/var_decl.hpp"

// exprs
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/field_init_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "expr/index_expr.hpp"

// module
#include "module/module.hpp"

// stmts
#include "expr/array_type_expr.hpp"
#include "expr/cast_expr.hpp"
#include "expr/ref_type_expr.hpp"
#include "stmt/block_statement.hpp"
#include "stmt/break_statement.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_decl_statement.hpp"
#include "stmt/while_statement.hpp"

namespace ast::visitor
{
    void OverallVisitor::visit(ParamDecl& p)
    {
        if (p.type_) p.type_->accept(*this);
    }

    void OverallVisitor::visit(FunctionDecl& f)
    {
        // Convention: signature first, then body
        if (f.ret_) f.ret_->accept(*this);

        for (auto* p : f.params_)
        {
            if (p) p->accept(*this);
        }

        if (f.body_) f.body_->accept(*this);
    }

    void OverallVisitor::visit(TypeAliasDecl& t)
    {
        // If you store aliased type expr, traverse it here.
        // if (t.type_alias) t.type_alias->accept(*this);
        (void)t;
    }

    void OverallVisitor::visit(ImportDecl& i)
    {
        (void)i;
    }

    void OverallVisitor::visit(VarDecl& v)
    {
        // Traverse syntactic children only (type + init).
        if (v.type_) v.type_->accept(*this);
        if (v.init_) v.init_->accept(*this);
    }

    void OverallVisitor::visit(StructDecl& s)
    {
        for (auto* f : s.fields_)
        {
            if (f) f->accept(*this);
        }
    }

    void OverallVisitor::visit(FieldDecl& f)
    {
        if (f.type_) f.type_->accept(*this);
    }

    void OverallVisitor::visit(IntLiteralExpr& i)
    {
        (void)i;
    }

    void OverallVisitor::visit(FloatLiteralExpr& f)
    {
        (void)f;
    }

    void OverallVisitor::visit(UnaryExpr& u)
    {
        if (u.expr_) u.expr_->accept(*this);
    }

    void OverallVisitor::visit(BinaryExpr& b)
    {
        if (b.lhs_) b.lhs_->accept(*this);
        if (b.rhs_) b.rhs_->accept(*this);
    }

    void OverallVisitor::visit(StringLiteralExpr& s)
    {
        (void)s;
    }

    void OverallVisitor::visit(StructLiteralExpr& o)
    {
        if (o.expr_) o.expr_->accept(*this);

        for (auto* e : o.elements_)
        {
            if (e) e->accept(*this);
        }
    }

    void OverallVisitor::visit(AssignExpr& a)
    {
        if (a.lhs_) a.lhs_->accept(*this);
        if (a.rhs_) a.rhs_->accept(*this);
    }

    void OverallVisitor::visit(FieldExpr& f)
    {
        if (f.base_) f.base_->accept(*this);
    }

    void OverallVisitor::visit(CallExpr& e)
    {
        if (e.callee_) e.callee_->accept(*this);

        for (auto* a : e.args_)
        {
            if (a) a->accept(*this);
        }
    }

    void OverallVisitor::visit(RefExpr& r)
    {
        // Important: do NOT follow semantic binding edges by default,
        // otherwise this visitor can walk a graph (and can create cycles),
        // not the syntax tree.
        (void)r;
    }

    void OverallVisitor::visit(IndexExpr& i)
    {
        if (i.base_) i.base_->accept(*this);
        if (i.index_) i.index_->accept(*this);
    }

    void OverallVisitor::visit(BoolLiteralExpr& b)
    {
        (void)b;
    }

    void OverallVisitor::visit(CharLiteralExpr& c)
    {
        (void)c;
    }

    void OverallVisitor::visit(FieldInitExpr& f)
    {
        if (f.value_) f.value_->accept(*this);
    }

    void OverallVisitor::visit(IfStatement& i)
    {
        if (i.condition_) i.condition_->accept(*this);
        if (i.thenBody_) i.thenBody_->accept(*this);

        for (auto* eif : i.elseIfs_)
        {
            if (eif) eif->accept(*this);
        }

        if (i.else_) i.else_->accept(*this);
    }

    void OverallVisitor::visit(ElseIfStatement& e)
    {
        if (e.condition_) e.condition_->accept(*this);
        if (e.then_) e.then_->accept(*this);
    }

    void OverallVisitor::visit(ElseStatement& e)
    {
        if (e.then_) e.then_->accept(*this);
    }

    void OverallVisitor::visit(TypeParamDecl&)
    {
    }

    void OverallVisitor::visit(FunctionBlockStatement&)
    {
    }

    void OverallVisitor::visit(BlockStatement& b)
    {
        for (auto* s : b.statements_)
        {
            if (s) s->accept(*this);
        }
    }

    void OverallVisitor::visit(WhileStatement& w)
    {
        if (w.condition_) w.condition_->accept(*this);
        if (w.body_) w.body_->accept(*this);
    }

    void OverallVisitor::visit(ReturnStatement& r)
    {
        if (r.expr_) r.expr_->accept(*this);
    }

    void OverallVisitor::visit(ExprStatement& e)
    {
        if (e.expr_) e.expr_->accept(*this);
    }

    void OverallVisitor::visit(ContinueStatement& c)
    {
        (void)c;
    }

    void OverallVisitor::visit(BreakStatement& b)
    {
        (void)b;
    }

    void OverallVisitor::visit(DoWhileStatement& d)
    {
        if (d.body_) d.body_->accept(*this);
        if (d.condition_) d.condition_->accept(*this);
    }

    void OverallVisitor::visit(VarDeclStatement& v)
    {
        if (v.decl_) v.decl_->accept(*this);
    }

    void OverallVisitor::visit(Module& m)
    {
        // Convention: imports first, then decls
        for (auto* i : m.imports)
        {
            if (i) i->accept(*this);
        }

        for (auto* d : m.decls)
        {
            if (d) d->accept(*this);
        }
    }

    void OverallVisitor::visit(Project& p)
    {
        for (auto* m : p.modules)
        {
            if (m) m->accept(*this);
        }
    }

    // ---- Types / misc nodes: keep as leaves unless you want deeper traversal ----

    void OverallVisitor::visit(CastExpr& c)
    {
        c.source_->accept(*this);
        c.targetSyntax_->accept(*this);
    }

    void OverallVisitor::visit(ArrayTypeExpr& t)
    {
        t.type_->accept(*this);
        t.sizeExpr_->accept(*this);
    }

    void OverallVisitor::visit(PathTypeExpr& t)
    {
        t.pathExpr_->accept(*this);
    }

    void OverallVisitor::visit(RefTypeExpr& t)
    {
        t.pointee_->accept(*this);
    }

    void OverallVisitor::visit(PathExpr& p)
    {
        (void)p;
    }

    void OverallVisitor::visit(BuiltinTypeExpr& t)
    {
        (void)t;
    }

    void OverallVisitor::visit(ArrayLiteralExpr& a)
    {
        (void)a;
    }
} // namespace ast::visitor
