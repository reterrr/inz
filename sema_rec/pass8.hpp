// sema/pass8.hpp
#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "translation.hpp"

// Exprs
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/bool_literal_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/char_literal_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/float_literal_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/int_literal_expr.hpp"
#include "expr/path_expr.hpp"
#include "expr/ref_expr.hpp"
#include "expr/string_literal_expr.hpp"
#include "expr/unary_op_expr.hpp"

// Struct literals
#include "expr/array_literal_expr.hpp"
#include "expr/field_init_expr.hpp"
#include "expr/struct_literal_expr.hpp"

// Stmts
#include "stmt/block_statement.hpp"
#include "stmt/do_while_statement.hpp"
#include "stmt/expr_statement.hpp"
#include "stmt/if_statement.hpp"
#include "stmt/return_statement.hpp"
#include "stmt/var_statement.hpp"
#include "stmt/while_statement.hpp"

// TypeExpr (ADAPT: include your real typeexpr headers)
#include "expr/type_expr.hpp"

// Passes
#include "pass6.hpp"
#include "pass_4.5.hpp"

namespace sema
{
    template <typename T>
    struct Pass8PtrHash final
    {
        size_t operator()(const T* p) const noexcept
        {
            return std::hash<const void*>{}(p);
        }
    };

    template <typename T>
    struct Pass8PtrEq final
    {
        bool operator()(const T* a, const T* b) const noexcept { return a == b; }
    };

    enum class DynTagKind : std::uint8_t
    {
        Obj, // runtime Obj*
        Bool, // native i1
        Void, // no value
        StructObj // Obj + StructId metadata
    };

    struct DynTag final
    {
        DynTagKind kind = DynTagKind::Obj;
        std::optional<StructId> struct_id;

        static DynTag obj()
        {
            return DynTag{.kind = DynTagKind::Obj, .struct_id = std::nullopt};
        }

        static DynTag boolean()
        {
            return DynTag{.kind = DynTagKind::Bool, .struct_id = std::nullopt};
        }

        static DynTag void_()
        {
            return DynTag{.kind = DynTagKind::Void, .struct_id = std::nullopt};
        }

        static DynTag struct_obj(StructId id)
        {
            return DynTag{.kind = DynTagKind::StructObj, .struct_id = id};
        }
    };

    struct Pass8Result final
    {
        std::unordered_map<const ast::Expr*, DynTag, Pass8PtrHash<ast::Expr>,
                           Pass8PtrEq<ast::Expr>>
        tag_of;

        // Logging-as-errors
        LogSequence errors;
        bool ok() const { return errors.empty(); }
    };

    class Pass8DynTagVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass8DynTagVisitor(const Pass4_5Result& p45, const Pass6Result& p6,
                           Pass8Result& out, std::uint32_t unit_index);

        void visit(ast::Module& m) override;

        // context setup
        void visit(ast::FnDecl& f) override;

        // stmts with bool condition requirement
        void visit(ast::IfStatement& i) override;
        void visit(ast::WhileStatement& w) override;
        void visit(ast::DoWhileStatement& d) override;

        // return checking
        void visit(ast::ReturnStatement& r) override;

        // locals (learn slot tags)
        void visit(ast::VarStmt& v) override;

        // expr tagging
        void visit(ast::BoolLiteralExpr& b) override;
        void visit(ast::IntLiteralExpr& i) override;
        void visit(ast::FloatLiteralExpr& f) override;
        void visit(ast::CharLiteralExpr& c) override;
        void visit(ast::StringLiteralExpr& s) override;

        void visit(ast::RefExpr& r) override;
        void visit(ast::PathExpr& p) override;

        void visit(ast::UnaryExpr& u) override;
        void visit(ast::BinaryExpr& b) override;
        void visit(ast::CallExpr& c) override;
        void visit(ast::AssignExpr& a) override;
        void visit(ast::FieldExpr& f) override;
        void visit(ast::IndexExpr& i) override;
        void visit(ast::ArrayLiteralExpr& a) override;

        void visit(ast::StructLiteralExpr& s) override;
        void visit(ast::FieldInitExpr& f) override;

        // typeexpr helpers (used by IndexExpr and return logic)
        const ast::TypeExpr* typeexpr_of_slot(SlotId s) const;
        const ast::TypeExpr* peel_one_index(const ast::TypeExpr* base_te) const;
        const ast::TypeExpr* typeexpr_of_expr(ast::Expr* e) const;

    private:
        const Pass4_5Result& p45_;
        const Pass6Result& p6_;
        Pass8Result& out_;
        std::uint32_t unit_index_ = 0;

        // slot_index -> declared TypeExpr (optional cache)
        std::unordered_map<std::uint32_t, const ast::TypeExpr*> slot_typeexpr_;

        const ModuleVisibleEnv* env_ = nullptr;
        const FnBindings* fb_ = nullptr;

        DynTag last_{};

        // slot_index -> tag (learned from declared type and/or initializer)
        std::unordered_map<std::uint32_t, DynTag> slot_tag_;

        // per-function return context
        const ast::FnDecl* cur_fn_ = nullptr;
        const ast::TypeExpr* cur_ret_te_ = nullptr;
        bool cur_fn_is_void_ = true;

        // logging
        void log_path(std::string msg, const lex::Loc& loc) const;
        void log_ident(std::string msg, lex::SymId name, const lex::Loc& loc) const;

        void cache_expr(const ast::Expr* e);
        DynTag tag(ast::Expr* e);

        const Binding* binding_of(ast::Expr* e) const;

        // slot support
        std::optional<SlotId> find_slot_for_var(const ast::VarStmt& v) const;
        DynTag tag_of_slot(SlotId s) const;

        // typeexpr -> tag
        DynTag tag_from_typeexpr(const ast::TypeExpr* te, const lex::Loc& loc) const;

        // classification helpers
        static bool is_bool_result_unary(const ast::UnaryExpr& u);
        static bool is_bool_result_binary(const ast::BinaryExpr& b);

        // resolve struct from a *name path*
        std::optional<StructId> resolve_struct_simple_name(lex::SymId name) const;
        std::optional<StructId> resolve_struct_qualified(lex::SymId alias,
                                                         lex::SymId name) const;

        // struct literal head resolver (Expr-head)
        std::optional<StructId>
        resolve_struct_id_from_head(ast::Expr* head, const lex::Loc& loc) const;

        // typeexpr path resolver (Type-head)
        std::optional<StructId>
        resolve_struct_id_from_type_path(const std::vector<lex::SymId>& segs,
                                         const lex::Loc& loc) const;

        // ADAPT LAYER:
        // Implement these against your TypeExpr AST.
        static bool typeexpr_is_builtin_bool(const ast::TypeExpr* te);
        static bool typeexpr_is_builtin_void(const ast::TypeExpr* te);
        static bool typeexpr_try_get_path2(const ast::TypeExpr* te,
                                           std::vector<lex::SymId>& out_segs);

        // CFG/must-return (structural)
        static bool stmt_must_return(ast::Statement* s);
        static bool block_must_return(ast::BlockStatement* b);

        // return typeexpr discovery
        static const ast::TypeExpr* fn_ret_typeexpr_ptr(const ast::FnDecl& f);

        static ast::Expr* expr_ptr(ast::Expr* p) { return p; }
    };

    Pass8Result run_pass8_dyn_tag(const Translation& tr, const Pass4_5Result& p45,
                                  const Pass6Result& p6);
} // namespace sema
