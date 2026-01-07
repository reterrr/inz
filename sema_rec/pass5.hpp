#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "translation.hpp"
#include "ast/nodes/visit/overallvisitor.hpp"

// module/decls/stmts
#include "decl/type_param_decl.hpp"

// inputs
#include "pass_4.5.hpp"       // Pass4_5Result, ModuleVisibleEnv, ResolvedImport
#include "pass5_reserved.hpp" // Pass5ReservedResult, ReservedStructId

struct CompilerContext;

namespace sema
{
    struct Pass5Diagnostic final
    {
        enum class Code : uint8_t
        {
            UnknownTypeName,
            UnknownImportAlias,
            IllegalBoxArity,
            IllegalFixedArrayLength,
            UnsupportedTypePathDepth,
            UnsupportedTypeForm,
        };

        Code code{};
        ModuleId module = kInvalidModuleId; // NEW: module where diagnostic originates
        lex::Loc loc{};
        std::string message;
    };

    struct StructLayout final
    {
        std::vector<lex::SymId> fields_in_order;
        std::vector<TypeId> field_types_in_order;
        std::unordered_map<lex::SymId, TypeId> name_to_type;
        std::unordered_map<lex::SymId, uint32_t> name_to_index;
    };

    struct StructIdHash final
    {
        size_t operator()(const StructId& s) const noexcept
        {
            return (static_cast<size_t>(s.module.value) << 32) ^ static_cast<size_t>(s.index);
        }
    };

    struct Pass5Result final
    {
        TypeDB types;

        // TypeExpr* -> TypeId
        std::unordered_map<const ast::TypeExpr*, TypeId, PtrHash<ast::TypeExpr>, PtrEq<ast::TypeExpr>> type_of;

        // struct-id -> layout
        std::unordered_map<StructId, StructLayout, StructIdHash> struct_layout;

        std::vector<Pass5Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    class Pass5TypeResolveVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass5TypeResolveVisitor(const CompilerContext& ctx,
                                const Pass4_5Result& p45,
                                const Pass5ReservedResult& p5r,
                                uint32_t unit_index,
                                lex::SymId box_sym,
                                lex::SymId str_sym,
                                Pass5Result& out);

        void visit(ast::Module& m) override;

        // decls/stmts where types appear
        void visit(ast::StructDecl& s) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::ParamDecl& p) override;
        void visit(ast::VarStmt& v) override;
        void visit(ast::LoadFnDecl& lf) override;
        void visit(ast::CallExpr& c) override; // NEW: for f::<T>(...)

        // type expr nodes
        void visit(ast::BuiltinTypeExpr& t) override;
        void visit(ast::PathTypeExpr& t) override;
        void visit(ast::ArrayTypeExpr& t) override;
        void visit(ast::RefTypeExpr& t) override;

    private:
        const CompilerContext& ctx_;
        const Pass4_5Result& p45_;
        const Pass5ReservedResult& p5r_;
        uint32_t unit_index_ = 0;

        lex::SymId box_sym_{};
        lex::SymId str_sym_{};

        Pass5Result& out_;
        const ModuleVisibleEnv* env_ = nullptr;

        // NEW: current module id (source for diagnostics)
        ModuleId module_ = kInvalidModuleId;

        TypeId last_{};

        // generic scope: visible type params (SymId)
        std::vector<lex::SymId> type_param_stack_;

        void diag(Pass5Diagnostic::Code c, const lex::Loc& loc, std::string msg) const;

        std::optional<std::uint64_t> const_eval_u64(ast::Expr* e);
        TypeId ty_builtin(BuiltinType b);
        TypeId ty_void();
        TypeId ty_struct(StructId sid);
        TypeId ty_reserved_struct(ReservedStructId rid);
        TypeId ty_type_param(lex::SymId name);

        TypeId resolve(ast::TypeExpr* t);

        bool is_type_param(lex::SymId s) const;
        void push_type_params(const std::vector<ast::TypeParamDecl*>& tps);
        void pop_to_size(size_t sz);

        BuiltinType map_builtin(kl::rt::BuiltinTypeExprKind k, const lex::Loc& loc) const;

        std::optional<StructId> local_struct_id_of(lex::SymId name) const;
    };

    Pass5Result run_pass5_type_resolve(const Translation& tr,
                                       const CompilerContext& ctx,
                                       const Pass4_5Result& p45,
                                       const Pass5ReservedResult& p5r,
                                       lex::SymId box_sym,
                                       lex::SymId str_sym);
} // namespace sema
