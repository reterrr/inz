//
// Created by yhwach on 9/12/25.
//

#ifndef DUMP_VISITOR_HPP
#define DUMP_VISITOR_HPP

#include "decl_visitor.hpp"
#include "expr_visitor.hpp"
#include "module_visitor.hpp"
#include "stmt_visitor.hpp"

namespace ast::visitor {
    struct DumpVisitor final
            : ExprVisitor,
              DeclVisitor,
              StmtVisitor,
              ModuleVisitor {
        explicit DumpVisitor(std::ostream &os)
            : os(os) {
        }

        std::ostream &os;
        int indent = 0;

        void pad() const {
            for (int i = 0; i < indent; i++) {
                os << ' ';
            }
        }

        void visit(ast::IntLiteralExpr &n) override {
            pad();
            os << "IntLiteral " << n.v_ << "\n";
        }

        void visit(ast::FloatLiteralExpr &n) override {
            pad();
            os << "FloatLiteral " << n.v_ << "\n";
        }

        void visit(ast::UnaryExpr &n) override {
            pad();
            os << "UnaryExpr op=" << static_cast<int>(n.op) << "\n";
            if (n.expr) {
                indent++;
                n.expr->accept(*this);
                indent--;
            }
        }

        void visit(ast::BinaryExpr &n) override {
            pad();
            os << "BinaryExpr op=" << static_cast<int>(n.op) << "\n";
            indent++;
            if (n.lhs) {
                pad();
                os << "lhs:\n";
                indent++;
                n.lhs->accept(*this);
                indent--;
            }
            if (n.rhs) {
                pad();
                os << "rhs:\n";
                indent++;
                n.rhs->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::StringLiteralExpr &n) override {
            pad();
            os << "StringLiteral sym#" << n.value << "\n";
        }

        void visit(ast::ObjLiteralExpr &n) override {
            pad();
            os << "ObjLiteral\n";
            indent++;
            if (n.type) {
                pad();
                os << "type-path: ";
                for (size_t i = 0; i < n.type->segments.size(); ++i) {
                    if (i) os << ".";
                    os << n.type->segments[i];
                }
                os << "\n";
            }
            pad();
            os << "fields:\n";
            indent++;
            for (auto *f: n.elements) if (f) f->accept(*this);
            indent--;
            indent--;
        }

        void visit(ast::AssignExpr &n) override {
            pad();
            os << "AssignExpr op=" << static_cast<int>(n.op) << "\n";
            indent++;
            // If your AssignExpr stores a name instead of LHS expr, print that here
            // pad(); os << "lhs-name sym#" << n.name << "\n";
            if (n.lhs) {
                pad();
                os << "lhs:\n";
                indent++;
                n.lhs->accept(*this);
                indent--;
            }
            if (n.rhs) {
                pad();
                os << "rhs:\n";
                indent++;
                n.rhs->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::InitDeclarator &n) override {
            pad();
            os << "InitDeclarator name#" << n.name << "\n";
            if (n.init) {
                indent++;
                n.init->accept(*this);
                indent--;
            }
        }

        void visit(ast::FieldExpr &n) override {
            pad();
            os << "FieldExpr .#" << n.field << "\n";
            if (n.base) {
                indent++;
                n.base->accept(*this);
                indent--;
            }
        }

        void visit(ast::CallExpr &n) override {
            pad();
            os << "CallExpr\n";
            indent++;
            if (n.callee) {
                pad();
                os << "callee:\n";
                indent++;
                n.callee->accept(*this);
                indent--;
            }
            pad();
            os << "args:\n";
            indent++;
            for (auto *a: n.args) if (a) a->accept(*this);
            indent--;
            indent--;
        }

        void visit(ast::RefExpr &n) override {
            pad();
            os << "Ref name#" << n.name << "\n";
        }

        void visit(ast::IndexExpr &n) override {
            pad();
            os << "IndexExpr\n";
            indent++;
            if (n.base) {
                pad();
                os << "base:\n";
                indent++;
                n.base->accept(*this);
                indent--;
            }
            if (n.index) {
                pad();
                os << "index:\n";
                indent++;
                n.index->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::BoolLiteralExpr &n) override {
            pad();
            os << "BoolLiteral " << (n.value ? "true" : "false") << "\n";
        }

        void visit(ast::FieldInitExpr &n) override {
            pad();
            os << "FieldInit name#" << n.name << "\n";
            if (n.value) {
                indent++;
                n.value->accept(*this);
                indent--;
            }
        }

        void visit(ast::ParamDecl &n) override {
            pad();
            os << "ParamDecl name#" << n.name
                    << " qual=" << static_cast<int>(n.qual) << "\n";
            if (n.type) {
                indent++;
                pad();
                os << "type@" << n.type << "\n";
                indent--;
            }
        }

        void visit(ast::FunctionDecl &n) override {
            pad();
            os << "FunctionDecl name#" << n.name << "\n";
            indent++;
            if (n.type) {
                pad();
                os << "callable-type@" << n.type << "\n";
            }
            if (n.ret) {
                pad();
                os << "ret-type@" << n.ret << "\n";
            }
            pad();
            os << "params:\n";
            indent++;
            for (auto *p: n.params) if (p) p->accept(*this);
            indent--;
            if (n.body) {
                pad();
                os << "body:\n";
                indent++;
                n.body->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::TypeAliasDecl &n) override {
            pad();
            os << "TypeAliasDecl name#" << n.type_name << "\n";
            if (n.type_alias) {
                indent++;
                pad();
                os << "aliased-type@" << n.type_alias << "\n";
                indent--;
            }
        }

        void visit(ast::ImportDecl &n) override {
            pad();
            os << "ImportDecl ";
            if (n.is_public) os << "pub ";
            for (size_t i = 0; i < n.path.size(); ++i) {
                if (i) os << ".";
                os << n.path[i];
            }
            if (n.alias.has_value()) os << " as #" << *n.alias;
            os << "\n";
        }

        void visit(ast::VarDecl &n) override {
            pad();
            os << "VarDecl spec=" << static_cast<int>(n.specifier)
                    << " region=" << static_cast<int>(n.region) << "\n";
            indent++;
            if (n.type) {
                pad();
                os << "type@" << n.type << "\n";
            }
            pad();
            os << "declarators:\n";
            indent++;
            for (auto *d: n.declarators) if (d) d->accept(*this);
            indent--;
            indent--;
        }

        void visit(ast::IfStatement &n) override {
            pad();
            os << "IfStatement\n";
            indent++;
            if (n.condition) {
                pad();
                os << "cond:\n";
                indent++;
                n.condition->accept(*this);
                indent--;
            }
            if (n.thenBody) {
                pad();
                os << "then:\n";
                indent++;
                n.thenBody->accept(*this);
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

        void visit(VarDeclStatement &v) override {
            v.decl->accept(*this);
        }

        void visit(ast::BlockStatement &n) override {
            pad();
            os << "Block\n";
            indent++;
            for (auto *s: n.statements) if (s) s->accept(*this);
            indent--;
        }

        void visit(ast::WhileStatement &n) override {
            pad();
            os << "While\n";
            indent++;
            if (n.condition) {
                pad();
                os << "cond:\n";
                indent++;
                n.condition->accept(*this);
                indent--;
            }
            if (n.body) {
                pad();
                os << "body:\n";
                indent++;
                n.body->accept(*this);
                indent--;
            }
            indent--;
        }


        void visit(ast::ReturnStatement &n) override {
            pad();
            os << "Return\n";
            if (n.expr) {
                indent++;
                n.expr->accept(*this);
                indent--;
            }
        }

        void visit(ast::ExprStatement &n) override {
            pad();
            os << "ExprStmt\n";
            if (n.expr) {
                indent++;
                n.expr->accept(*this);
                indent--;
            }
        }

        void visit(ast::ContinueStatement & /*n*/) override {
            pad();
            os << "Continue\n";
        }

        void visit(ast::BreakStatement & /*n*/) override {
            pad();
            os << "Break\n";
        }

        void visit(ast::DoWhileStatement &n) override {
            pad();
            os << "DoWhile\n";
            indent++;
            if (n.body) {
                pad();
                os << "body:\n";
                indent++;
                n.body->accept(*this);
                indent--;
            }
            if (n.condition) {
                pad();
                os << "cond:\n";
                indent++;
                n.condition->accept(*this);
                indent--;
            }
            indent--;
        }

        void visit(ast::Module &m) override {
            pad();
            os << "Module\n";
            indent++;
            // package
            pad();
            os << "package: ";
            for (size_t i = 0; i < m.package_path.size(); ++i) {
                if (i) os << ".";
                os << m.package_path[i];
            }
            os << "\n";

            // imports
            pad();
            os << "imports:\n";
            indent++;
            for (auto *imp: m.imports) if (imp) imp->accept(*this);
            indent--;

            // decls
            pad();
            os << "decls:\n";
            indent++;
            for (auto *d: m.decls) if (d) d->accept(*this);
            indent--;

            indent--;
        }

        void visit(StructDecl &n) override {
            pad();
            os << "struct " << (n.name) << " {\n";
            ++indent;

            for (auto *d: n.fields) {
                if (!d) continue;
                d->accept(*this); // Will dispatch to visit(FieldDecl&) below
            }

            --indent;
            pad();
            os << "}\n";
        }

        void visit(FieldDecl &n) override {
            pad();

            if (n.is_public) {
                os << "pub ";
            }

            if (n.type) {
                pad();
                os << "type@" << n.type << "\n";
            }
            os << ' ' << n.name << ";\n";
        }
    };
}

#endif //DUMP_VISITOR_HPP
