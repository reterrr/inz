//
// Created by yhwach on 9/12/25.
//

#ifndef DUMP_VISITOR_HPP
#define DUMP_VISITOR_HPP

#include "decl_visitor.hpp"
#include "expr_visitor.hpp"
#include "function_decl.hpp"
#include "module_visitor.hpp"
#include "param_decl.hpp"
#include "project.hpp"
#include "project_visitor.hpp"
#include "stmt_visitor.hpp"
#include "struct_decl.hpp"
#include "type_alias_decl.hpp"
#include "var_decl.hpp"
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/bool_literal_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/field_init_expr.hpp"
#include "expr/float_literal_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/int_literal_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/path_type_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/string_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "module/import_decl.hpp"
#include "module/module.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_decl_statement.hpp"
#include "stmt/while_statement.hpp"
#include "expr/cast_expr.hpp"

namespace ast::visitor
{
    struct DumpVisitor final
    : ProjectVisitor,
      ExprVisitor,
      DeclVisitor,
      StmtVisitor,
      ModuleVisitor
{
    explicit DumpVisitor(std::ostream& os)
        : os(os)
    {
    }

    std::ostream& os;
    int indent = 0;

    void pad() const
    {
        for (int i = 0; i < indent; i++)
            os << ' ';
    }

    // -------------------- helpers --------------------

    void print_path(const std::vector<lex::SymId>& p)
    {
        for (size_t i = 0; i < p.size(); ++i)
        {
            if (i) os << ".";
            os << "#" << p[i];
        }
    }

    static const char* builtin_kind_name(kl::rt::BuiltinTypeExprKind k)
    {
        using K = kl::rt::BuiltinTypeExprKind;
        switch (k)
        {
            case K::I8:   return "i8";
            case K::U8:   return "u8";
            case K::I16:  return "i16";
            case K::U16:  return "u16";
            case K::I32:  return "i32";
            case K::U32:  return "u32";
            case K::I64:  return "i64";
            case K::U64:  return "u64";
            case K::I128: return "i128";
            case K::U128: return "u128";
            case K::F32:  return "f32";
            case K::F64:  return "f64";
            case K::Bool: return "bool";
            case K::Char: return "char";
        }
        return "<?>";
    }

    // -------------------- Expr --------------------

    void visit(ast::IntLiteralExpr& n) override
    {
        pad();
        os << "IntLiteral sym#" << n.v_;
        // if you store parsed kind on node, print it:
        // os << " kind=" << static_cast<int>(n.kind_);
        os << "\n";
    }

    void visit(ast::FloatLiteralExpr& n) override
    {
        pad();
        os << "FloatLiteral sym#" << n.v_;
        // if node has kind_:
        // os << " kind=" << static_cast<int>(n.kind_);
        os << "\n";
    }

    void visit(ast::BoolLiteralExpr& n) override
    {
        pad();
        os << "BoolLiteral " << (n.v_ ? "true" : "false") << "\n";
    }

    void visit(ast::CharLiteralExpr& n) override
    {
        pad();
        os << "CharLiteral U+"
           << std::hex << static_cast<std::uint32_t>(n.v_) << std::dec
           << "\n";
    }

    void visit(ast::StringLiteralExpr& n) override
    {
        pad();
        os << "StringLiteral sym#" << n.value_ << "\n";
    }

    void visit(ast::RefExpr& n) override
    {
        pad();
        os << "Ref name#" << n.name << "\n";
    }

    void visit(ast::UnaryExpr& n) override
    {
        pad();
        os << "UnaryExpr op=" << static_cast<int>(n.op) << "\n";
        if (n.expr_)
        {
            ++indent;
            n.expr_->accept(*this);
            --indent;
        }
    }

    void visit(ast::BinaryExpr& n) override
    {
        pad();
        os << "BinaryExpr op=" << static_cast<int>(n.op) << "\n";
        ++indent;

        if (n.lhs_)
        {
            pad();
            os << "lhs:\n";
            ++indent;
            n.lhs_->accept(*this);
            --indent;
        }

        if (n.rhs_)
        {
            pad();
            os << "rhs:\n";
            ++indent;
            n.rhs_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::AssignExpr& n) override
    {
        pad();
        os << "AssignExpr op=" << static_cast<int>(n.op) << "\n";
        ++indent;

        if (n.lhs_)
        {
            pad();
            os << "lhs:\n";
            ++indent;
            n.lhs_->accept(*this);
            --indent;
        }

        if (n.rhs_)
        {
            pad();
            os << "rhs:\n";
            ++indent;
            n.rhs_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::FieldExpr& n) override
    {
        pad();
        os << "FieldExpr .#" << n.field << "\n";
        if (n.base_)
        {
            ++indent;
            n.base_->accept(*this);
            --indent;
        }
    }

    void visit(ast::IndexExpr& n) override
    {
        pad();
        os << "IndexExpr\n";
        ++indent;

        if (n.base_)
        {
            pad();
            os << "base:\n";
            ++indent;
            n.base_->accept(*this);
            --indent;
        }

        if (n.index_)
        {
            pad();
            os << "index:\n";
            ++indent;
            n.index_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::CallExpr& n) override
    {
        pad();
        os << "CallExpr\n";
        ++indent;

        if (n.callee_)
        {
            pad();
            os << "callee:\n";
            ++indent;
            n.callee_->accept(*this);
            --indent;
        }

        pad();
        os << "args:\n";
        ++indent;
        for (auto* a : n.args_)
            if (a) a->accept(*this);
        --indent;

        --indent;
    }

    void visit(ast::StructLiteralExpr& n) override
    {
        pad();
        os << "StructLiteral\n";
        ++indent;

        if (n.type_)
        {
            pad();
            os << "type:\n";
            ++indent;
            n.type_->accept(*this);
            --indent;
        }

        pad();
        os << "fields:\n";
        ++indent;
        for (auto* f : n.elements_)
            if (f) f->accept(*this);
        --indent;

        --indent;
    }

    void visit(ast::FieldInitExpr& n) override
    {
        pad();
        os << "FieldInit name#" << n.name << "\n";
        if (n.value_)
        {
            ++indent;
            n.value_->accept(*this);
            --indent;
        }
    }

    void visit(ast::ArrayLiteralExpr& n) override
    {
        pad();
        os << "ArrayLiteral\n";
        ++indent;

        pad();
        os << "elements:\n";
        ++indent;
        for (auto* e : n.v_)
            if (e) e->accept(*this);
        --indent;

        --indent;
    }

    void visit(ast::CastExpr& n) override
    {
        pad();
        os << "CastExpr\n";
        ++indent;

        if (n.source_)
        {
            pad();
            os << "source:\n";
            ++indent;
            n.source_->accept(*this);
            --indent;
        }

        if (n.targetSyntax_)
        {
            pad();
            os << "type:\n";
            ++indent;
            n.targetSyntax_->accept(*this);
            --indent;
        }

        --indent;
    }

    // -------------------- Types --------------------

    void visit(ast::BuiltinTypeExpr& n) override
    {
        pad();
        os << "BuiltinType " << builtin_kind_name(n.kind_);
    }

    void visit(ast::PathExpr& n) override
    {
        pad();
        os << "Path ";
        print_path(n.path_);
    }

    void visit(ast::PathTypeExpr& n) override
    {
        pad();
        os << "PathType\n";
        ++indent;
        if (n.pathExpr_)
        {
            n.pathExpr_->accept(*this);
            os << "\n";
        }
        --indent;
    }

    void visit(ast::ArrayTypeExpr& n) override
    {
        pad();
        os << "ArrayType\n";
        ++indent;

        if (n.type_)
        {
            pad();
            os << "element:\n";
            ++indent;
            n.type_->accept(*this);
            os << "\n";
            --indent;
        }

        if (n.sizeExpr_)
        {
            pad();
            os << "size:\n";
            ++indent;
            n.sizeExpr_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::RefTypeExpr& n) override
    {
        pad();
        os << "RefType mut=" << static_cast<int>(n.mut_) << "\n";
        ++indent;
        if (n.pointee_)
            n.pointee_->accept(*this);
        --indent;
    }

    // -------------------- Statements --------------------

    void visit(ast::BlockStatement& n) override
    {
        pad();
        os << "Block\n";
        ++indent;
        for (auto* s : n.statements_)
            if (s) s->accept(*this);
        --indent;
    }

    void visit(ast::IfStatement& n) override
    {
        pad();
        os << "IfStatement\n";
        ++indent;

        if (n.condition_)
        {
            pad();
            os << "cond:\n";
            ++indent;
            n.condition_->accept(*this);
            --indent;
        }

        if (n.thenBody_)
        {
            pad();
            os << "then:\n";
            ++indent;
            n.thenBody_->accept(*this);
            --indent;
        }

        if (!n.elseIfs_.empty())
        {
            pad();
            os << "else-if:\n";
            ++indent;
            for (auto* eif : n.elseIfs_)
                if (eif) eif->accept(*this);
            --indent;
        }

        if (n.else_)
        {
            pad();
            os << "else:\n";
            ++indent;
            n.else_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::ElseIfStatement& n) override
    {
        pad();
        os << "ElseIf\n";
        ++indent;

        if (n.condition_)
        {
            pad();
            os << "cond:\n";
            ++indent;
            n.condition_->accept(*this);
            --indent;
        }

        if (n.then_)
        {
            pad();
            os << "then:\n";
            ++indent;
            n.then_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::ElseStatement& n) override
    {
        pad();
        os << "Else\n";
        ++indent;

        if (n.then_)
            n.then_->accept(*this);

        --indent;
    }

    void visit(ast::WhileStatement& n) override
    {
        pad();
        os << "While\n";
        ++indent;

        if (n.condition_)
        {
            pad();
            os << "cond:\n";
            ++indent;
            n.condition_->accept(*this);
            --indent;
        }

        if (n.body_)
        {
            pad();
            os << "body:\n";
            ++indent;
            n.body_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::DoWhileStatement& n) override
    {
        pad();
        os << "DoWhile\n";
        ++indent;

        if (n.body_)
        {
            pad();
            os << "body:\n";
            ++indent;
            n.body_->accept(*this);
            --indent;
        }

        if (n.condition_)
        {
            pad();
            os << "cond:\n";
            ++indent;
            n.condition_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::ReturnStatement& n) override
    {
        pad();
        os << "Return\n";
        if (n.expr_)
        {
            ++indent;
            n.expr_->accept(*this);
            --indent;
        }
    }

    void visit(ast::ExprStatement& n) override
    {
        pad();
        os << "ExprStmt\n";
        if (n.expr_)
        {
            ++indent;
            n.expr_->accept(*this);
            --indent;
        }
    }

    void visit(ast::ContinueStatement&) override
    {
        pad();
        os << "Continue\n";
    }

    void visit(ast::BreakStatement&) override
    {
        pad();
        os << "Break\n";
    }

    void visit(ast::VarDeclStatement& v) override
    {
        if (v.decl_) v.decl_->accept(*this);
    }

    // -------------------- Decls --------------------

    void visit(ast::ParamDecl& n) override
    {
        pad();
        os << "ParamDecl name#" << n.name_ << "\n";
        if (n.type_)
        {
            ++indent;
            pad();
            os << "type:\n";
            ++indent;
            n.type_->accept(*this);
            os << "\n";
            --indent;
            --indent;
        }
    }

    void visit(ast::FunctionDecl& n) override
    {
        pad();
        os << "FunctionDecl name#" << n.name_ << "\n";
        ++indent;

        if (n.ret_)
        {
            pad();
            os << "ret:\n";
            ++indent;
            n.ret_->accept(*this);
            os << "\n";
            --indent;
        }

        pad();
        os << "params:\n";
        ++indent;
        for (auto* p : n.params_)
            if (p) p->accept(*this);
        --indent;

        if (n.body_)
        {
            pad();
            os << "body:\n";
            ++indent;
            n.body_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::TypeAliasDecl& n) override
    {

    }

    void visit(ast::ImportDecl& n) override
    {
        pad();
        os << "ImportDecl ";
        if (n.is_public) os << "pub ";
        print_path(n.path);
        if (n.alias.has_value()) os << " as #" << *n.alias;
        os << "\n";
    }

    void visit(ast::VarDecl& n) override
    {
        pad();
        os << "VarDecl name#" << n.name_ << " mut=" << static_cast<int>(n.mut_) << "\n";
        ++indent;

        if (n.type_)
        {
            pad();
            os << "type:\n";
            ++indent;
            n.type_->accept(*this);
            os << "\n";
            --indent;
        }

        if (n.init_)
        {
            pad();
            os << "init:\n";
            ++indent;
            n.init_->accept(*this);
            --indent;
        }

        --indent;
    }

    void visit(ast::StructDecl& n) override
    {
        pad();
        os << "StructDecl name#" << n.name << "\n";
        ++indent;

        pad();
        os << "fields:\n";
        ++indent;
        for (auto* f : n.fields_)
            if (f) f->accept(*this);
        --indent;

        --indent;
    }

    void visit(ast::FieldDecl& n) override
    {
        pad();
        os << "FieldDecl ";
        if (n.visibility_ == ast::FieldDecl::Visibility::Publ) os << "pub ";
        os << "name#" << n.name_ << "\n";

        if (n.type_)
        {
            ++indent;
            pad();
            os << "type:\n";
            ++indent;
            n.type_->accept(*this);
            os << "\n";
            --indent;
            --indent;
        }
    }

    // -------------------- Module / Project --------------------

    void visit(ast::Module& m) override
    {
        pad();
        os << "Module\n";
        ++indent;

        pad();
        os << "package: ";
        print_path(m.package_path);
        os << "\n";

        pad();
        os << "imports:\n";
        ++indent;
        for (auto* imp : m.imports)
            if (imp) imp->accept(*this);
        --indent;

        pad();
        os << "decls:\n";
        ++indent;
        for (auto* d : m.decls)
            if (d) d->accept(*this);
        --indent;

        --indent;
    }

    void visit(ast::Project& p) override
    {
        pad();
        os << "Project\n";
        ++indent;

        for (const auto& module : p.modules)
        {
            pad();
            os << "module:\n";
            ++indent;
            if (module) module->accept(*this);
            --indent;
        }

        --indent;
    }
};

}

#endif //DUMP_VISITOR_HPP
