//
// Created by yhwach on 9/12/25.
//

#ifndef DUMP_VISITOR_HPP
#define DUMP_VISITOR_HPP

#include <cstdint>
#include <ostream>
#include <string_view>
#include <type_traits>
#include <vector>

/* visitors */
#include "decl_visitor.hpp"
#include "expr_visitor.hpp"
#include "module_visitor.hpp"
#include "project_visitor.hpp"
#include "stmt_visitor.hpp"

/* decls */
#include "decl/fn_decl.hpp"
#include "decl/param_decl.hpp"
#include "decl/struct_decl.hpp"
#include "decl/type_param_decl.hpp"

/* expr */
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/bool_literal_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/cast_expr.hpp"
#include "expr/char_literal_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/field_init_expr.hpp"
#include "expr/float_literal_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/int_literal_expr.hpp"
#include "expr/path_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/string_literal_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/unary_op_expr.hpp"

/* types (still visited through ExprVisitor in your design) */
#include "expr/array_type_expr.hpp"
#include "expr/builtin_type_expr.hpp"
#include "expr/path_type_expr.hpp"
#include "expr/ref_type_expr.hpp"

/* module/project */
#include "module/import_decl.hpp"
#include "module/module.hpp"
#include "project.hpp"

/* stmts */
#include "stmt/block_statement.hpp"
#include "stmt/break_statement.hpp"
#include "stmt/continue_statement.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_statement.hpp"
#include "stmt/while_statement.hpp"

#include "node_type.hpp"

namespace ast::visitor
{
    struct DumpVisitor final
        : ProjectVisitor,
          ExprVisitor,
          DeclVisitor,
          StmtVisitor,
          ModuleVisitor
    {
        explicit DumpVisitor(std::ostream& os,
                             CompilerContext& context)
            : os(os),
              stringInterner_(context.stringInterner),
              identInterner_(context.identInterner),
              numericInterner_(context.numericInterner)
        {
        }

        std::ostream& os;
        const ast::Interner<>& stringInterner_;
        const ast::Interner<>& identInterner_;
        const ast::Interner<>& numericInterner_;

        int indent = 0;

        // -------------------- indentation --------------------

        void pad() const
        {
            // 2 spaces per level (readability)
            for (int i = 0; i < indent * 2; ++i) os << ' ';
        }

        struct IndentGuard
        {
            DumpVisitor& self;
            explicit IndentGuard(DumpVisitor& self) : self(self) { ++self.indent; }
            ~IndentGuard() { --self.indent; }
        };

        // -------------------- interner helpers --------------------
        //
        // Your interners are passed in; lex::SymId is the key.
        // Since your Interner<> API isn’t shown here, resolve_sym()
        // uses C++20 detection to call a reasonable method if it exists.
        //

        template <class InternerT>
        static decltype(auto) resolve_sym(const InternerT& interner, lex::SymId id)
        {
            if constexpr (requires { interner.view(id); })
            {
                return interner.view(id); // string_view / similar
            }
            else if constexpr (requires { interner.get(id); })
            {
                return interner.get(id);
            }
            else if constexpr (requires { interner.at(id); })
            {
                return interner.at(id);
            }
            else if constexpr (requires { interner.resolve(id); })
            {
                return interner.resolve(id);
            }
            else if constexpr (requires { interner[id]; })
            {
                return interner[id];
            }
            else
            {
                // Fallback: we cannot resolve to text; caller should print the numeric id
                return std::string_view{};
            }
        }

        void print_ident_sym(lex::SymId id) const
        {
            const auto s = resolve_sym(identInterner_, id);
            if constexpr (std::is_convertible_v<decltype(s), std::string_view>)
            {
                if (!std::string_view(s).empty())
                {
                    os << std::string_view(s);
                    return;
                }
            }
            // fallback
            os << '#' << id;
        }

        void print_string_sym(lex::SymId id) const
        {
            const auto s = resolve_sym(stringInterner_, id);
            if constexpr (std::is_convertible_v<decltype(s), std::string_view>)
            {
                if (!std::string_view(s).empty())
                {
                    os << std::string_view(s);
                    return;
                }
            }
            os << '#' << id;
        }

        void print_numeric_sym(lex::SymId id) const
        {
            const auto s = resolve_sym(numericInterner_, id);
            if constexpr (std::is_convertible_v<decltype(s), std::string_view>)
            {
                if (!std::string_view(s).empty())
                {
                    os << std::string_view(s);
                    return;
                }
            }
            os << '#' << id;
        }

        void print_path(const std::vector<lex::SymId>& p) const
        {
            for (size_t i = 0; i < p.size(); ++i)
            {
                if (i) os << "::";
                print_ident_sym(p[i]);
            }
        }

        // -------------------- enum pretty printers --------------------

        static const char* unary_op_name(ast::UnaryOp op)
        {
            switch (op)
            {
            case ast::UnaryOp::negation: return "negation";
            case ast::UnaryOp::logical_not: return "logical_not";
            case ast::UnaryOp::preincrement: return "preincrement";
            case ast::UnaryOp::predecrement: return "predecrement";
            case ast::UnaryOp::postincrement: return "postincrement";
            case ast::UnaryOp::postdecrement: return "postdecrement";
            default: return "unknown_unary_op";
            }
        }

        static const char* binary_op_name(ast::BinaryOp op)
        {
            switch (op)
            {
            case ast::BinaryOp::add: return "add";
            case ast::BinaryOp::subtract: return "subtract";
            case ast::BinaryOp::multiply: return "multiply";
            case ast::BinaryOp::divide: return "divide";
            case ast::BinaryOp::modulo: return "modulo";
            case ast::BinaryOp::less: return "less";
            case ast::BinaryOp::less_equal: return "less_equal";
            case ast::BinaryOp::greater: return "greater";
            case ast::BinaryOp::greater_equal: return "greater_equal";
            case ast::BinaryOp::equal: return "equal";
            case ast::BinaryOp::not_equal: return "not_equal";
            case ast::BinaryOp::logical_and: return "logical_and";
            case ast::BinaryOp::logical_or: return "logical_or";
            default: return "unknown_binary_op";
            }
        }

        static const char* assign_op_name(AssignOp op)
        {
            switch (op)
            {
            case AssignOp::Assign: return "assign";
            case AssignOp::Add: return "add_assign";
            case AssignOp::Subtract: return "sub_assign";
            case AssignOp::Multiply: return "mul_assign";
            case AssignOp::Divide: return "div_assign";
            default: return "unknown_assign_op";
            }
        }


        // Print type-args if a node exposes them (API is not shown; use detection)
        template <class NodeT>
        void maybe_print_type_args(const NodeT& n)
        {
            auto print_vec = [this](const auto& vec)
            {
                if (vec.empty()) return;
                pad();
                os << "type_args:\n";
                IndentGuard ig(*this);
                for (auto* t : vec)
                {
                    if (!t) continue;
                    pad();
                    t->accept(*this);
                    os << '\n';
                }
            };

            if constexpr (requires { n.typeArgs_; })
            {
                print_vec(n.typeArgs_);
            }
            else if constexpr (requires { n.typeArgs; })
            {
                print_vec(n.typeArgs);
            }
            else if constexpr (requires { n.type_args_; })
            {
                print_vec(n.type_args_);
            }
            else if constexpr (requires { n.type_args; })
            {
                print_vec(n.type_args);
            }
            else
            {
                // no type args on this node
            }
        }

        // -------------------- Expr --------------------

        void visit(ast::IntLiteralExpr& n) override
        {
            pad();
            os << "IntLiteral value=";
            print_numeric_sym(n.v_);
            os << " (sym#" << n.v_ << ")\n";
        }

        void visit(ast::FloatLiteralExpr& n) override
        {
            pad();
            os << "FloatLiteral value=";
            print_numeric_sym(n.v_);
            os << " (sym#" << n.v_ << ")\n";
        }

        void visit(ast::BoolLiteralExpr& n) override
        {
            pad();
            os << "BoolLiteral " << (n.v_ ? "true" : "false") << '\n';
        }

        void visit(ast::CharLiteralExpr& n) override
        {
            pad();
            os << "CharLiteral U+"
                << std::hex << static_cast<std::uint32_t>(n.v_) << std::dec
                << '\n';
        }

        void visit(ast::StringLiteralExpr& n) override
        {
            pad();
            os << "StringLiteral value=\"";
            print_string_sym(n.v_);
            os << "\" (sym#" << n.v_ << ")\n";
        }

        void visit(ast::RefExpr& n) override
        {
            pad();
            os << "Ref name=";
            print_ident_sym(n.name);
            os << " (sym#" << n.name << ")\n";
        }

        void visit(ast::PathExpr& n) override
        {
            pad();
            os << "Path ";
            print_path(n.path_);
            os << '\n';
        }

        void visit(ast::UnaryExpr& n) override
        {
            pad();
            os << "UnaryExpr op=" << unary_op_name(n.op) << " (" << static_cast<int>(n.op) << ")\n";
            if (n.expr_)
            {
                IndentGuard ig(*this);
                n.expr_->accept(*this);
            }
        }

        void visit(ast::BinaryExpr& n) override
        {
            pad();
            os << "BinaryExpr op=" << binary_op_name(n.op) << " (" << static_cast<int>(n.op) << ")\n";

            IndentGuard ig(*this);

            if (n.lhs_)
            {
                pad();
                os << "lhs:\n";
                {
                    IndentGuard ig2(*this);
                    n.lhs_->accept(*this);
                }
            }

            if (n.rhs_)
            {
                pad();
                os << "rhs:\n";
                {
                    IndentGuard ig2(*this);
                    n.rhs_->accept(*this);
                }
            }
        }

        void visit(ast::AssignExpr& n) override
        {
            pad();
            os << "AssignExpr op=" << assign_op_name(n.op) << " (" << static_cast<int>(n.op) << ")\n";

            IndentGuard ig(*this);

            if (n.lhs_)
            {
                pad();
                os << "lhs:\n";
                {
                    IndentGuard ig2(*this);
                    n.lhs_->accept(*this);
                }
            }

            if (n.rhs_)
            {
                pad();
                os << "rhs:\n";
                {
                    IndentGuard ig2(*this);
                    n.rhs_->accept(*this);
                }
            }
        }

        void visit(ast::FieldExpr& n) override
        {
            pad();
            os << "FieldExpr field=";
            print_ident_sym(n.field);
            os << " (sym#" << n.field << ")\n";

            if (n.base_)
            {
                IndentGuard ig(*this);
                pad();
                os << "base:\n";
                {
                    IndentGuard ig2(*this);
                    n.base_->accept(*this);
                }
            }
        }

        void visit(ast::IndexExpr& n) override
        {
            pad();
            os << "IndexExpr\n";
            IndentGuard ig(*this);

            if (n.base_)
            {
                pad();
                os << "base:\n";
                {
                    IndentGuard ig2(*this);
                    n.base_->accept(*this);
                }
            }

            if (n.index_)
            {
                pad();
                os << "index:\n";
                {
                    IndentGuard ig2(*this);
                    n.index_->accept(*this);
                }
            }
        }

        void visit(ast::CallExpr& n) override
        {
            pad();
            os << "CallExpr\n";
            IndentGuard ig(*this);

            // Type arguments if present (turbofish)
            maybe_print_type_args(n);

            if (n.callee_)
            {
                pad();
                os << "callee:\n";
                {
                    IndentGuard ig2(*this);
                    n.callee_->accept(*this);
                }
            }

            pad();
            os << "args:\n";
            {
                IndentGuard ig2(*this);
                for (auto* a : n.args_)
                    if (a) a->accept(*this);
            }
        }

        void visit(ast::StructLiteralExpr& n) override
        {
            pad();
            os << "StructLiteral\n";
            IndentGuard ig(*this);

            maybe_print_type_args(n);

            if (n.expr_)
            {
                pad();
                os << "type:\n";
                {
                    IndentGuard ig2(*this);
                    n.expr_->accept(*this);
                }
            }

            pad();
            os << "fields:\n";
            {
                IndentGuard ig2(*this);
                for (auto* f : n.elements_)
                    if (f) f->accept(*this);
            }
        }

        void visit(ast::FieldInitExpr& n) override
        {
            pad();
            os << "FieldInit name=";
            print_ident_sym(n.name);
            os << " (sym#" << n.name << ")\n";
            if (n.value_)
            {
                IndentGuard ig(*this);
                n.value_->accept(*this);
            }
        }

        void visit(ast::ArrayLiteralExpr& n) override
        {
            pad();
            os << "ArrayLiteral\n";
            IndentGuard ig(*this);

            pad();
            os << "elements:\n";
            {
                IndentGuard ig2(*this);
                for (auto* e : n.v_)
                    if (e) e->accept(*this);
            }
        }

        void visit(ast::CastExpr& n) override
        {
            pad();
            os << "CastExpr\n";
            IndentGuard ig(*this);

            if (n.source_)
            {
                pad();
                os << "source:\n";
                {
                    IndentGuard ig2(*this);
                    n.source_->accept(*this);
                }
            }

            if (n.targetSyntax_)
            {
                pad();
                os << "type:\n";
                {
                    IndentGuard ig2(*this);
                    n.targetSyntax_->accept(*this);
                }
            }
        }

        // -------------------- Types --------------------

        void visit(ast::BuiltinTypeExpr& n) override
        {
            pad();
            os << "BuiltinType " << builtin_kind_name(n.kind_) << " (" << static_cast<int>(n.kind_) << ")\n";
        }

        void visit(ast::PathTypeExpr& n) override
        {
            pad();
            os << "PathType\n";
            IndentGuard ig(*this);

            // If the node carries type args, show them.
            maybe_print_type_args(n);

            if (n.pathExpr_)
            {
                pad();
                os << "path:\n";
                {
                    IndentGuard ig2(*this);
                    n.pathExpr_->accept(*this);
                }
            }
        }

        void visit(ast::ArrayTypeExpr& n) override
        {
            pad();
            os << "ArrayType\n";
            IndentGuard ig(*this);

            if (n.type_)
            {
                pad();
                os << "element:\n";
                {
                    IndentGuard ig2(*this);
                    n.type_->accept(*this);
                }
            }

            if (n.sizeExpr_)
            {
                pad();
                os << "size:\n";
                {
                    IndentGuard ig2(*this);
                    n.sizeExpr_->accept(*this);
                }
            }
        }

        void visit(ast::RefTypeExpr& n) override
        {
            pad();
            os << "RefType mut=" << static_cast<int>(n.mut_) << '\n';
            IndentGuard ig(*this);
            if (n.pointee_)
                n.pointee_->accept(*this);
        }

        // -------------------- Statements --------------------

        void visit(ast::BlockStatement& n) override
        {
            pad();
            os << "Block\n";
            IndentGuard ig(*this);
            for (auto* s : n.statements_)
                if (s) s->accept(*this);
        }

        void visit(ast::IfStatement& n) override
        {
            pad();
            os << "IfStatement\n";
            IndentGuard ig(*this);

            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                {
                    IndentGuard ig2(*this);
                    n.condition_->accept(*this);
                }
            }

            if (n.thenBody_)
            {
                pad();
                os << "then:\n";
                {
                    IndentGuard ig2(*this);
                    n.thenBody_->accept(*this);
                }
            }

            if (!n.elseIfs_.empty())
            {
                pad();
                os << "else_if:\n";
                {
                    IndentGuard ig2(*this);
                    for (auto* eif : n.elseIfs_)
                        if (eif) eif->accept(*this);
                }
            }

            if (n.else_)
            {
                pad();
                os << "else:\n";
                {
                    IndentGuard ig2(*this);
                    n.else_->accept(*this);
                }
            }
        }

        void visit(ast::ElseIfStatement& n) override
        {
            pad();
            os << "ElseIf\n";
            IndentGuard ig(*this);

            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                {
                    IndentGuard ig2(*this);
                    n.condition_->accept(*this);
                }
            }

            if (n.then_)
            {
                pad();
                os << "then:\n";
                {
                    IndentGuard ig2(*this);
                    n.then_->accept(*this);
                }
            }
        }

        void visit(ast::ElseStatement& n) override
        {
            pad();
            os << "Else\n";
            IndentGuard ig(*this);

            if (n.then_)
                n.then_->accept(*this);
        }

        void visit(ast::WhileStatement& n) override
        {
            pad();
            os << "While\n";
            IndentGuard ig(*this);

            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                {
                    IndentGuard ig2(*this);
                    n.condition_->accept(*this);
                }
            }

            if (n.body_)
            {
                pad();
                os << "body:\n";
                {
                    IndentGuard ig2(*this);
                    n.body_->accept(*this);
                }
            }
        }

        void visit(ast::DoWhileStatement& n) override
        {
            pad();
            os << "DoWhile\n";
            IndentGuard ig(*this);

            if (n.body_)
            {
                pad();
                os << "body:\n";
                {
                    IndentGuard ig2(*this);
                    n.body_->accept(*this);
                }
            }

            if (n.condition_)
            {
                pad();
                os << "cond:\n";
                {
                    IndentGuard ig2(*this);
                    n.condition_->accept(*this);
                }
            }
        }

        void visit(ast::ReturnStatement& n) override
        {
            pad();
            os << "Return\n";
            if (n.expr_)
            {
                IndentGuard ig(*this);
                n.expr_->accept(*this);
            }
        }

        void visit(ast::ExprStatement& n) override
        {
            pad();
            os << "ExprStmt\n";
            if (n.expr_)
            {
                IndentGuard ig(*this);
                n.expr_->accept(*this);
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

        // -------------------- Decls --------------------

        void visit(ast::TypeParamDecl& n) override
        {
            pad();
            os << "TypeParamDecl name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")\n";
        }

        void visit(ast::ParamDecl& n) override
        {
            pad();
            os << "ParamDecl name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")\n";

            if (n.type_)
            {
                pad();
                os << "type:\n";
                IndentGuard ig(*this);
                n.type_->accept(*this);
            }
        }

        void visit(ast::FnDecl& n) override
        {
            pad();
            os << "FunctionDecl name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")\n";

            IndentGuard ig(*this);

            // Type parameters (if present; API unknown, use detection)
            if constexpr (requires { n.typeParamsDecls_; })
            {
                if (!n.typeParamsDecls_.empty())
                {
                    pad();
                    os << "type_params:\n";
                    IndentGuard ig2(*this);
                    for (auto* tp : n.typeParamsDecls_)
                        if (tp) tp->accept(*this);
                }
            }

            if (n.ret_)
            {
                pad();
                os << "ret:\n";
                {
                    IndentGuard ig2(*this);
                    n.ret_->accept(*this);
                }
            }

            pad();
            os << "params:\n";
            {
                IndentGuard ig2(*this);
                for (auto* p : n.params_)
                    if (p) p->accept(*this);
            }

            if (n.body_)
            {
                pad();
                os << "body:\n";
                {
                    IndentGuard ig2(*this);
                    n.body_->accept(*this);
                }
            }
        }

        void visit(ast::TypeAliasDecl& n) override
        {
            pad();
            os << "TypeAliasDecl\n";
            (void)n;
        }

        void visit(ast::ImportDecl& n) override
        {
            pad();
            os << "ImportDecl ";
            if (n.is_public) os << "pub ";

            n.pathExpr_->accept(*this);

            if (n.alias.has_value())
            {
                os << " as ";
                print_ident_sym(*n.alias);
                os << " (sym#" << *n.alias << ")";
            }

            os << '\n';
        }

        void visit(ast::VarStmt& n) override
        {
            pad();
            os << "VarStmt name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")"
                << " mut=" << static_cast<int>(n.mut_) << '\n';

            IndentGuard ig(*this);

            if (n.type_)
            {
                pad();
                os << "type:\n";
                {
                    IndentGuard ig2(*this);
                    n.type_->accept(*this);
                }
            }

            if (n.init_)
            {
                pad();
                os << "init:\n";
                {
                    IndentGuard ig2(*this);
                    n.init_->accept(*this);
                }
            }
        }

        void visit(ast::StructDecl& n) override
        {
            pad();
            os << "StructDecl name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")\n";

            IndentGuard ig(*this);

            // Type parameters (if present; API unknown, use detection)
            if constexpr (requires { n.typeParamsDecls_; })
            {
                if (!n.typeParamsDecls_.empty())
                {
                    pad();
                    os << "type_params:\n";
                    IndentGuard ig2(*this);
                    for (auto* tp : n.typeParamsDecls_)
                        if (tp) tp->accept(*this);
                }
            }

            pad();
            os << "fields:\n";
            {
                IndentGuard ig2(*this);
                for (auto* f : n.fields_)
                    if (f) f->accept(*this);
            }
        }

        void visit(ast::FieldDecl& n) override
        {
            pad();
            os << "FieldDecl ";
            if (n.visibility_ == ast::Visibility::Publ) os << "pub ";

            os << "name=";
            print_ident_sym(n.name_);
            os << " (sym#" << n.name_ << ")\n";

            if (n.type_)
            {
                pad();
                os << "type:\n";
                IndentGuard ig(*this);
                n.type_->accept(*this);
            }
        }

        // -------------------- Module / Project --------------------

        void visit(ast::Module& m) override
        {
            pad();
            os << "Module\n";
            IndentGuard ig(*this);

            pad();
            os << "package: ";
            m.pathExpr_->accept(*this);
            os << '\n';

            pad();
            os << "imports:\n";
            {
                IndentGuard ig2(*this);
                for (auto* imp : m.imports)
                    if (imp) imp->accept(*this);
            }

            pad();
            os << "decls:\n";
            {
                IndentGuard ig2(*this);
                for (auto* d : m.decls)
                    if (d) d->accept(*this);
            }
        }

        void visit(ast::Project& p) override
        {
            pad();
            os << "Project\n";
            IndentGuard ig(*this);

            for (const auto& module : p.modules)
            {
                pad();
                os << "module:\n";
                IndentGuard ig2(*this);
                if (module) module->accept(*this);
            }
        }
    };
}

#endif // DUMP_VISITOR_HPP
