#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "translation.hpp"


#include "module/module.hpp"
#include "decl/fn_decl.hpp"
#include "decl/param_decl.hpp"
#include "stmt/var_statement.hpp"
#include "expr/ref_expr.hpp"


#include "pass4.hpp"
#include "pass_4.5.hpp"
#include "runtime_intrinsics.hpp"

namespace sema
{
    struct SlotId final
    {
        std::uint32_t index = 0;
        friend bool operator==(SlotId, SlotId) = default;
    };

    enum class BindingKind : std::uint8_t
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

        RuntimeIntrinsic intrinsic{};
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

        std::uint32_t slot_count = 0;
        std::vector<LocalSlotInfo> slots;

        std::unordered_map<const ast::RefExpr*, Binding> ref_binding;
        std::unordered_map<const ast::Expr*, Binding> expr_binding;
    };

    struct ModuleBindings final
    {
        ModuleId module_id{};
        std::unordered_map<FnId, FnBindings, LocalIdHash<FnTag>> fns;
    };


    struct Pass6Result final
    {
        std::vector<ModuleBindings> modules;
        LogSequence errors;

        bool ok() const { return errors.empty(); }
    };

    class Pass6LocalBinderVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass6LocalBinderVisitor(const Pass4Result& p4,
                                const Pass4_5Result& p45,
                                Pass6Result& out,
                                std::uint32_t unit_index);

        void visit(ast::Module& m) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::LoadFnDecl& lf) override;

        void visit(ast::BlockStatement& b) override;
        void visit(ast::VarStmt& v) override;
        void visit(ast::StructLiteralExpr& s) override;

        void visit(ast::RefExpr& r) override;
        void visit(ast::PathExpr& p) override;
        void visit(ast::UnaryExpr& u) override;
        void visit(ast::AssignExpr& e) override;

        std::optional<ModuleId> lookup_import_alias_target(lex::SymId alias) const;
        std::optional<FnId> lookup_fn_in_module(ModuleId mid, lex::SymId name) const;
        std::optional<LoadFnId> lookup_load_fn_in_module(ModuleId mid, lex::SymId name) const;

    private:
        const Pass4Result& p4_;
        const Pass4_5Result& p45_;
        Pass6Result& out_;
        std::uint32_t unit_index_ = 0;

        const ModuleGlobals* mg_ = nullptr;
        const ModuleVisibleEnv* env_ = nullptr;

        ModuleId module_ = kInvalidModuleId;

        FnBindings* cur_fn_ = nullptr;
        std::vector<std::unordered_map<lex::SymId, SlotId>> scopes_;


        std::vector<lex::SymId> mod_path_;
        lex::Loc mod_loc_{};

        void push_scope();
        void pop_scope();

        bool declare_in_current_scope(lex::SymId name, SlotId slot);
        std::optional<SlotId> lookup_local(lex::SymId name) const;

        SlotId alloc_slot_for_var(ast::VarStmt& v) const;
        SlotId alloc_slot_for_param(ast::ParamDecl& p) const;

        std::optional<FnId> lookup_global_fn(lex::SymId name) const;
        std::optional<LoadFnId> lookup_global_load_fn(lex::SymId name) const;
        bool is_import_alias(lex::SymId name) const;

        static bool is_place_expr(ast::Expr* e);

        static std::optional<RuntimeIntrinsic> lookup_reserved_intrinsic(const ModuleVisibleEnv* env,
                                                                         lex::SymId name);


        void log_prefix(const lex::Loc& loc) const;
        void log_text(const lex::Loc& loc, std::string msg) const;
        void log_ident_err(const lex::Loc& loc, std::string msg, lex::SymId id) const;
        void log_path_err(const lex::Loc& loc, std::string msg, const std::vector<lex::SymId>& path) const;
    };

    Pass6Result run_pass6_local_binder(const Translation& tr,
                                       const Pass4Result& p4,
                                       const Pass4_5Result& p45);
}
