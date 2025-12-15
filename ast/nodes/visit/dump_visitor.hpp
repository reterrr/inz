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
#include "expr/bool_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/field_init_expr.hpp"
#include "expr/float_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/init_declarator_expr.hpp"
#include "expr/int_expr.hpp"
#include "expr/obj_expr.hpp"
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
            {
                os << ' ';
            }
        }

        void visit(ast::IntLiteralExpr& n) override
        {
            pad();
            os << "IntLiteral " << n.v_ << "\n";
        }

        void visit(ast::FloatLiteralExpr& n) override
        {
            pad();
            os << "FloatLiteral " << n.v_ << "\n";
        }

        void visit(ast::UnaryExpr& n) override
        {
            pad();
            os << "UnaryExpr op=" << static_cast<int>(n.op) << "\n";
            if (n.expr_)
            {
                indent++;
                n.expr_->accept(*this);
                indent--;
            }
        }

        void visit(ast::BinaryExpr& n) override
        {
            pad();
            os << "BinaryExpr op=" << static_cast<int>(n.op) << "\n";
            indent++;
            if (n.lhs_)
            {
                pad();
                os << "lhs:\n";
                indent++;
                n.lhs_->accept(*this);
                indent--;
            }
            if (n.rhs_)
            {
                pad();
                os << "rhs:\n";
                indent++;
                n.rhs_->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::StringLiteralExpr& n) override
        {
            pad();
            os << "StringLiteral sym#" << n.value << "\n";
        }

        void visit(ast::PathLiteralExpr& n) override
        {
            pad();
            os << "ObjLiteral\n";
            indent++;
            if (n.type_)
            {
                pad();
                os << "type_-path: ";
                for (size_t i = 0; i < n.type_->path_.size(); ++i)
                {
                    if (i) os << ".";
                    os << n.type_->path_[i];
                }
                os << "\n";
            }
            pad();
            os << "fields:\n";
            indent++;
            for (auto* f : n.elements_) if (f) f->accept(*this);
            indent--;
            indent--;
        }

        void visit(ast::AssignExpr& n) override
        {
            pad();
            os << "AssignExpr op=" << static_cast<int>(n.op) << "\n";
            indent++;
            // If your AssignExpr stores a name instead of LHS expr, print that here
            // pad(); os << "lhs-name sym#" << n.name << "\n";
            if (n.lhs_)
            {
                pad();
                os << "lhs:\n";
                indent++;
                n.lhs_->accept(*this);
                indent--;
            }
            if (n.rhs_)
            {
                pad();
                os << "rhs:\n";
                indent++;
                n.rhs_->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::InitDeclarator& n) override
        {
            pad();
            os << "InitDeclarator name#" << n.name << "\n";
            if (n.init_)
            {
                indent++;
                n.init_->accept(*this);
                indent--;
            }
        }

        void visit(ast::FieldExpr& n) override
        {
            pad();
            os << "FieldExpr .#" << n.field << "\n";
            if (n.base_)
            {
                indent++;
                n.base_->accept(*this);
                indent--;
            }
        }

        void visit(ast::CallExpr& n) override
        {
            pad();
            os << "CallExpr\n";
            indent++;
            if (n.callee_)
            {
                pad();
                os << "callee:\n";
                indent++;
                n.callee_->accept(*this);
                indent--;
            }
            pad();
            os << "args:\n";
            indent++;
            for (auto* a : n.args_) if (a) a->accept(*this);
            indent--;
            indent--;
        }

        void visit(ast::RefExpr& n) override
        {
            pad();
            os << "Ref name#" << n.name << "\n";
        }

        void visit(ast::IndexExpr& n) override
        {
            pad();
            os << "IndexExpr\n";
            indent++;
            if (n.base_)
            {
                pad();
                os << "base:\n";
                indent++;
                n.base_->accept(*this);
                indent--;
            }
            if (n.index_)
            {
                pad();
                os << "index:\n";
                indent++;
                n.index_->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::BoolLiteralExpr& n) override
        {
            pad();
            os << "BoolLiteral " << (n.value ? "true" : "false") << "\n";
        }

        void visit(ast::FieldInitExpr& n) override
        {
            pad();
            os << "FieldInit name#" << n.name << "\n";
            if (n.value_)
            {
                indent++;
                n.value_->accept(*this);
                indent--;
            }
        }

        void visit(ast::ParamDecl& n) override
        {
            pad();
            os << "ParamDecl name#" << n.name_ << '\n';

            if (n.type_)
            {
                indent++;
                pad();
                os << "type@" << n.type_ << "\n";
                indent--;
            }
        }

        void visit(ast::FunctionDecl& n) override
        {
            pad();
            os << "FunctionDecl name#" << n.name_ << "\n";
            indent++;
            if (n.ret_)
            {
                pad();
                os << "ret-type@" << n.ret_ << "\n";
            }
            pad();
            os << "params:\n";
            indent++;
            for (auto* p : n.params_) if (p) p->accept(*this);
            indent--;
            if (n.body_)
            {
                pad();
                os << "body:\n";
                indent++;
                n.body_->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::TypeAliasDecl& n) override
        {
            pad();
            os << "TypeAliasDecl name#" << n.type_name << "\n";
            if (n.type_alias)
            {
                indent++;
                pad();
                os << "aliased-type@" << n.type_alias << "\n";
                indent--;
            }
        }

        void visit(ast::ImportDecl& n) override
        {
            pad();
            os << "ImportDecl ";
            if (n.is_public) os << "pub ";
            for (size_t i = 0; i < n.path.size(); ++i)
            {
                if (i) os << ".";
                os << n.path[i];
            }
            if (n.alias.has_value()) os << " as #" << *n.alias;
            os << "\n";
        }

        void visit(ast::VarDecl& n) override
        {
            pad();
            indent++;
            if (n.type_)
            {
                pad();
                os << "type@" << n.type_ << "\n";
            }
            pad();
            os << "declarators:\n";
            indent++;
            indent--;
        }

        void visit(ast::IfStatement& n) override
        {
            pad();
            os << "IfStatement\n";
            indent++;
            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                indent++;
                n.condition_->accept(*this);
                indent--;
            }
            if (n.thenBody_)
            {
                pad();
                os << "then:\n";
                indent++;
                n.thenBody_->accept(*this);
                indent--;
            }
            // if (n.else_branch) {
            //     pad();
            //     os << "else:\n";
            //     indent++;
            //     n.else_branch->accept(*this);
            //     indent--;
            // }
            indent--;
        }

        void visit(VarDeclStatement& v) override
        {
            v.decl_->accept(*this);
        }

        void visit(ast::BlockStatement& n) override
        {
            pad();
            os << "Block\n";
            indent++;
            for (auto* s : n.statements_) if (s) s->accept(*this);
            indent--;
        }

        void visit(ast::WhileStatement& n) override
        {
            pad();
            os << "While\n";
            indent++;
            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                indent++;
                n.condition_->accept(*this);
                indent--;
            }
            if (n.body_)
            {
                pad();
                os << "body:\n";
                indent++;
                n.body_->accept(*this);
                indent--;
            }
            indent--;
        }


        void visit(ast::ReturnStatement& n) override
        {
            pad();
            os << "Return\n";
            if (n.expr_)
            {
                indent++;
                n.expr_->accept(*this);
                indent--;
            }
        }

        void visit(ast::ExprStatement& n) override
        {
            pad();
            os << "ExprStmt\n";
            if (n.expr_)
            {
                indent++;
                n.expr_->accept(*this);
                indent--;
            }
        }

        void visit(ast::ContinueStatement& /*n*/) override
        {
            pad();
            os << "Continue\n";
        }

        void visit(ast::BreakStatement& /*n*/) override
        {
            pad();
            os << "Break\n";
        }

        void visit(ast::DoWhileStatement& n) override
        {
            pad();
            os << "DoWhile\n";
            indent++;
            if (n.body_)
            {
                pad();
                os << "body:\n";
                indent++;
                n.body_->accept(*this);
                indent--;
            }
            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                indent++;
                n.condition_->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::Module& m) override
        {
            pad();
            os << "Module\n";
            indent++;
            // package
            pad();
            os << "package: ";
            for (size_t i = 0; i < m.package_path.size(); ++i)
            {
                if (i) os << ".";
                os << m.package_path[i];
            }
            os << "\n";

            // imports
            pad();
            os << "imports:\n";
            indent++;
            for (auto* imp : m.imports) if (imp) imp->accept(*this);
            indent--;

            // decls
            pad();
            os << "decls:\n";
            indent++;
            for (auto* d : m.decls) if (d) d->accept(*this);
            indent--;

            indent--;
        }

        void visit(StructDecl& n) override
        {
            pad();
            os << "struct " << (n.name) << " {\n";
            ++indent;

            for (auto* d : n.fields_)
            {
                if (!d) continue;
                d->accept(*this); // Will dispatch to visit(FieldDecl&) below
            }

            --indent;
            pad();
            os << "}\n";
        }

        void visit(FieldDecl& n) override
        {
            pad();

            if (n.visibility_ == FieldDecl::Visibility::Publ)
            {
                os << "pub ";
            }

            if (n.type_)
            {
                pad();
                os << "type@" << n.type_ << "\n";
            }
            os << ' ' << n.name_ << ";\n";
        }

        void visit(Project& p) override
        {
            pad();
            os << "project \n";

            for (const auto& module : p.modules)
            {
                pad();
                os << "module: " << "\n";
                module->accept(*this);
            }
        }

        void visit(ArrayTypeExpr&) override {}
        void visit(PathTypeExpr&) override {}
        void visit(RefTypeExpr&) override {}
        void visit(BuiltinTypeExpr&) override {}
    };
}

#endif //DUMP_VISITOR_HPP
