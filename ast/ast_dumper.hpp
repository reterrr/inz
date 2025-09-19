//
// Created by yhwach on 9/10/25.
//

#ifndef AST_DUMPER_HPP
#define AST_DUMPER_HPP

#include "ast.hpp"
#include "node.hpp"
#include "nodes/visit/dump_visitor.hpp"

namespace ast {
    enum class DumpType {
        Expr, Decl, Stmt, Module, Type
    };

    class AstDumper {
    public:
        const AST &ast;
        visitor::ExprVisitor expr_visitor;
        visitor::DeclVisitor decl_visitor;
        visitor::StmtVisitor stmt_visitor;
        visitor::ModuleVisitor module_visitor;

        explicit AstDumper(const AST &ast)
            : ast(ast) {
        }


        void dump() {
            visitor::DumpVisitor visitor{};
            Project *root = ast.get_project();
            for (const auto module: root->modules) {
                module->accept(visitor);
            }

            switch (node_type(root)) {
                case DumpType::Expr:
                    static_cast<ExprPtr>(root)->accept(expr_visitor);
                    break;

                case DumpType::Decl:
                    static_cast<DeclPtr>(root)->accept(decl_visitor);
                    break;

                case DumpType::Stmt:
                    static_cast<StatementPtr>(root)->accept(stmt_visitor);
                    break;

                case DumpType::Module:

                    break;

                case DumpType::Type:

                    break;
            }
        }


        ~AstDumper() = default;

    private:
        DumpType node_type(const NodePtr node) const {
            switch (node->nodeType_) {
                case NodeKind::Expr_IntLiteral ||
                     NodeKind::Expr_FloatLiteral ||
                     NodeKind::Expr_BoolLiteral ||
                     NodeKind::Expr_StringLiteral ||
                     NodeKind::Expr_ObjLiteral ||
                     NodeKind::Expr_Var ||
                     NodeKind::Expr_Ref ||
                     NodeKind::Expr_Deref ||
                     NodeKind::Expr_Unary ||
                     NodeKind::Expr_Binary ||
                     NodeKind::Expr_Assign ||
                     NodeKind::Expr_Postfix ||
                     NodeKind::Expr_Field ||
                     NodeKind::Expr_FieldInit ||
                     NodeKind::Expr_Index ||
                     NodeKind::Expr_Call ||
                     NodeKind::Expr_Cond ||
                     NodeKind::Expr_StructInit ||
                     NodeKind::Expr_DeclInit:
                    return DumpType::Expr;
                    break;

                case NodeKind::Stmt_VarDecl ||
                     NodeKind::Stmt_Return ||
                     NodeKind::Stmt_If ||
                     NodeKind::Stmt_While ||
                     NodeKind::Stmt_DoWhile ||
                     NodeKind::Stmt_Break ||
                     NodeKind::Stmt_Continue ||
                     NodeKind::Stmt_Block ||
                     NodeKind::Stmt_Expr:
                    return DumpType::Stmt;
                    break;

                case NodeKind::Decl_Struct ||
                     NodeKind::Decl_Enum ||
                     NodeKind::Decl_Fn ||
                     NodeKind::Decl_TypeAlias ||
                     NodeKind::Decl_Import ||
                     NodeKind::Decl_Export ||
                     NodeKind::Decl_Module ||
                     NodeKind::Decl_Package ||
                     NodeKind::Decl_Param ||
                     NodeKind::Decl_Var:
                    return DumpType::Decl;
                    break;

                case NodeKind::Type_Builtin ||
                     NodeKind::Type_Path ||
                     NodeKind::Type_Array:
                    return DumpType::Type;
                    break;
            }
        }
    };
}

#endif //AST_DUMPER_HPP
