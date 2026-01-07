#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "translation.hpp"
#include "ast/nodes/visit/overallvisitor.hpp"

// Exprs
#include "expr/char_literal_expr.hpp"
#include "expr/ref_expr.hpp"

// Stmts

// Decls

// Passes
#include "pass6.hpp"
#include "pass_4.5.hpp"

namespace sema
{
    template <typename T>
    struct Pass8PtrHash final
    {
        size_t operator()(const T* p) const noexcept { return std::hash<const void*>{}(p); }
    };

    template <typename T>
    struct Pass8PtrEq final
    {
        bool operator()(const T* a, const T* b) const noexcept { return a == b; }
    };

    enum class DynTagKind : std::uint8_t
    {
        Obj,       // runtime Obj*
        Bool,      // native i1
        Void,      // no value
        StructObj  // Obj + StructId metadata
    };

    struct DynTag final
    {
        DynTagKind kind = DynTagKind::Obj;
        std::optional<StructId> struct_id;

        static DynTag obj() { return DynTag{.kind = DynTagKind::Obj, .struct_id = std::nullopt}; }
        static DynTag boolean() { return DynTag{.kind = DynTagKind::Bool, .struct_id = std::nullopt}; }
        static DynTag void_() { return DynTag{.kind = DynTagKind::Void, .struct_id = std::nullopt}; }
        static DynTag struct_obj(StructId id) { return DynTag{.kind = DynTagKind::StructObj, .struct_id = id}; }
    };

    struct Pass8Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            NonBoolCondition,
            UnknownStructInStructLiteral,
            UnsupportedStructLiteralHead,
            ReservedStructLiteralForbidden,

            // Optional but useful for bring-up:
            UnsupportedTypeExprPathDepth,
            UnknownStructInTypeExpr
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass8Result final
    {
        std::unordered_map<const ast::Expr*, DynTag, Pass8PtrHash<ast::Expr>, Pass8PtrEq<ast::Expr>> tag_of;
        std::vector<Pass8Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
    };

    class Pass8DynTagVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass8DynTagVisitor(const Pass4_5Result& p45, const Pass6Result& p6, Pass8Result& out, std::uint32_t unit_index);

        void visit(ast::Module& m) override;
        const ast::TypeExpr* typeexpr_of_slot(SlotId s) const;
        const ast::TypeExpr* peel_one_index(const ast::TypeExpr* base_te) const;
        const ast::TypeExpr* typeexpr_of_expr(ast::Expr* e) const;
        void visit(ast::ArrayLiteralExpr& a);
        void visit(ast::FnDecl& f) override;

        // stmts with bool condition requirement
        void visit(ast::IfStatement& i) override;
        void visit(ast::WhileStatement& w) override;
        void visit(ast::DoWhileStatement& d) override;

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

        void visit(ast::StructLiteralExpr& s) override;
        void visit(ast::FieldInitExpr& f) override;

    private:
        const Pass4_5Result& p45_;
        const Pass6Result& p6_;
        Pass8Result& out_;
        std::uint32_t unit_index_ = 0;

        std::unordered_map<std::uint32_t, const ast::TypeExpr*> slot_typeexpr_;

        const ModuleVisibleEnv* env_ = nullptr;
        const FnBindings* fb_ = nullptr;

        DynTag last_{};

        // slot_index -> tag (learned from declared type and/or initializer)
        std::unordered_map<std::uint32_t, DynTag> slot_tag_;

        void push_diag(Pass8Diagnostic::Code c, const lex::Loc& loc, std::string msg) const;

        void cache_expr(const ast::Expr* e);
        DynTag tag(ast::Expr* e);

        const Binding* binding_of(ast::Expr* e) const;

        // slot support
        std::optional<SlotId> find_slot_for_var(const ast::VarStmt& v) const;
        DynTag tag_of_slot(SlotId s) const;

        // typeexpr -> tag (THIS is what you must connect to your TypeExpr AST)
        DynTag tag_from_typeexpr(const ast::TypeExpr* te, const lex::Loc& loc) const;

        // classification helpers
        static bool is_bool_result_unary(const ast::UnaryExpr& u);
        static bool is_bool_result_binary(const ast::BinaryExpr& b);

        // resolve struct from a *name path*
        std::optional<StructId> resolve_struct_simple_name(lex::SymId name) const;
        std::optional<StructId> resolve_struct_qualified(lex::SymId alias, lex::SymId name) const;

        // struct literal head resolver (Expr-head)
        std::optional<StructId> resolve_struct_id_from_head(ast::Expr* head, const lex::Loc& loc) const;

        // typeexpr path resolver (Type-head)
        std::optional<StructId> resolve_struct_id_from_type_path(const std::vector<lex::SymId>& segs,
                                                                 const lex::Loc& loc) const;

        // ADAPT LAYER:
        // Implement these two helpers to match your TypeExpr nodes.
        static bool typeexpr_is_builtin_bool(const ast::TypeExpr* te);
        static bool typeexpr_try_get_path2(const ast::TypeExpr* te, std::vector<lex::SymId>& out_segs);

        static ast::Expr* expr_ptr(ast::Expr* p) { return p; }
    };

    Pass8Result run_pass8_dyn_tag(const Translation& tr,
                                  const Pass4_5Result& p45,
                                  const Pass6Result& p6);
} // namespace sema
