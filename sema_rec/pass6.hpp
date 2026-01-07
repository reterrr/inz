#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "translation.hpp"

// AST nodes we bind
#include "module/module.hpp"
#include "decl/fn_decl.hpp"
#include "decl/param_decl.hpp"
#include "stmt/var_statement.hpp"

#include "expr/ref_expr.hpp"

// IMPORTANT: add these if they exist in your AST

// Inputs
#include "pass4.hpp"
#include "pass_4.5.hpp"

namespace sema
{
    struct SlotId final
    {
        uint32_t index = 0;
        friend bool operator==(SlotId, SlotId) = default;
    };

    enum class BindingKind : uint8_t
    {
        LocalSlot,
        GlobalFn,
        GlobalLoadFn,
        ImportAlias,
        Unresolved,
        RuntimeIntrinsic,
        GlobalStruct
    };

    struct Binding final
    {
        BindingKind kind{BindingKind::Unresolved};
        RuntimeIntrinsic intrinsic;
        SlotId slot{};
        StructId struct_id{};
        FnId fn{};
        LoadFnId load_fn{};
        lex::SymId import_alias{};
    };

    struct LocalSlotInfo final
    {
        SlotId slot{};
        lex::SymId name{};
        ast::Mutability mut_{};
        ast::Storage storage_{};

        ast::VarStmt* var_decl = nullptr;
        ast::ParamDecl* param_decl = nullptr;
    };

    struct FnBindings final
    {
        FnId id{};
        ast::FnDecl* decl = nullptr;

        uint32_t slot_count = 0;
        std::vector<LocalSlotInfo> slots;

        std::unordered_map<const ast::RefExpr*, Binding> ref_binding;
        std::unordered_map<const ast::Expr*, Binding> expr_binding;
    };

    struct ModuleBindings final
    {
        ModuleId module_id{};
        std::unordered_map<FnId, FnBindings, LocalIdHash<FnTag>> fns;
    };

    struct Pass6Diagnostic final
    {
        enum class Code : uint8_t
        {
            DuplicateLocalNameInScope,
            UnresolvedName,

            // NEW:
            ImmutableAssign,
            InvalidAssignTarget,
            InvalidMutBorrow,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass6Result final
    {
        std::vector<ModuleBindings> modules;
        std::vector<Pass6Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    class Pass6LocalBinderVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass6LocalBinderVisitor(const Pass4Result& p4,
                                const Pass4_5Result& p45,
                                Pass6Result& out,
                                uint32_t unit_index)
            : p4_(p4), p45_(p45), out_(out), unit_index_(unit_index)
        {
        }

        void visit(ast::Module& m) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::LoadFnDecl& lf) override;

        void visit(ast::BlockStatement& b) override;
        void visit(ast::VarStmt& v) override;
        void visit(ast::StructLiteralExpr& s) override;

        void visit(ast::RefExpr& r) override;
        std::optional<ModuleId> lookup_import_alias_target(lex::SymId alias) const;
        std::optional<FnId> lookup_fn_in_module(ModuleId mid, lex::SymId name) const;
        std::optional<LoadFnId> lookup_load_fn_in_module(ModuleId mid, lex::SymId name) const;
        void visit(ast::PathExpr& p) override;
        void visit(ast::UnaryExpr& u) override;
        void visit(ast::AssignExpr& e) override;

    private:
        const Pass4Result& p4_;
        const Pass4_5Result& p45_;
        Pass6Result& out_;
        uint32_t unit_index_ = 0;

        const ModuleGlobals* mg_ = nullptr;
        const ModuleVisibleEnv* env_ = nullptr;

        FnBindings* cur_fn_ = nullptr;

        std::vector<std::unordered_map<lex::SymId, SlotId>> scopes_;

        void push_scope();
        void pop_scope();

        bool declare_in_current_scope(lex::SymId name, SlotId slot);
        std::optional<SlotId> lookup_local(lex::SymId name) const;

        SlotId alloc_slot_for_var(ast::VarStmt& v);
        SlotId alloc_slot_for_param(ast::ParamDecl& p) const;

        void diag_dup_local(const lex::Loc& loc, lex::SymId name) const;
        void diag_unresolved(const lex::Loc& loc, lex::SymId name) const;

        // NEW diagnostics
        void diag_immutable_assign(const lex::Loc& loc, lex::SymId name) const;
        void diag_invalid_assign_target(const lex::Loc& loc) const;
        void diag_invalid_mut_borrow(const lex::Loc& loc, lex::SymId name) const;

        std::optional<FnId> lookup_global_fn(lex::SymId name) const;
        std::optional<LoadFnId> lookup_global_load_fn(lex::SymId name) const;
        bool is_import_alias(lex::SymId name) const;

        // NEW: syntactic “place expression” predicate
        bool is_place_expr(ast::Expr* e) const;
    };

    Pass6Result run_pass6_local_binder(const Translation& tr,
                                       const Pass4Result& p4,
                                       const Pass4_5Result& p45);
} // namespace sema
