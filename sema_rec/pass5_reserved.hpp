// sema/pass5_reserved.hpp
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "translation.hpp"
#include "ast/nodes/visit/overallvisitor.hpp"

// module + decls
#include "decl/struct_decl.hpp"
#include "decl/type_param_decl.hpp"

// type exprs
#include "expr/path_type_expr.hpp"

// pass3.5 (only for earlier duplicate diagnostics; not required for type resolution)
#include "pass_3.5.hpp"
#include "type_system.hpp"

namespace sema
{
    struct Pass5ReservedDiagnostic final
    {
        enum class Code : uint8_t
        {
            UnknownTypeName,
            IllegalBoxArity,
            IllegalFixedArrayLength,
            UnsupportedTypePathDepth,
            UnsupportedTypeForm,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass5ReservedResult final
    {
        TypeDB types;

        // TypeExpr* -> TypeId
        std::unordered_map<const ast::TypeExpr*, TypeId, PtrHash<ast::TypeExpr>, PtrEq<ast::TypeExpr>> type_of;

        // reserved struct name -> id
        std::unordered_map<lex::SymId, ReservedStructId> reserved_struct_by_name;
        std::vector<ast::StructDecl*> reserved_struct_decls;

        std::vector<Pass5ReservedDiagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    class Pass5ReservedVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass5ReservedVisitor(const Pass3_5Result& p35,
                             lex::SymId box_sym,
                             lex::SymId str_sym,
                             Pass5ReservedResult& out)
            : p35_(p35), box_sym_(box_sym), str_sym_(str_sym), out_(out)
        {}

        void visit(ast::Module& m) override;
        void visit(ast::StructDecl& s) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::ParamDecl& p) override;

        // type expr nodes
        void visit(ast::BuiltinTypeExpr& t) override;
        void visit(ast::PathTypeExpr& t) override;
        void visit(ast::ArrayTypeExpr& t) override;
        void visit(ast::RefTypeExpr& t) override;

    private:
        const Pass3_5Result& p35_;
        lex::SymId box_sym_{};
        lex::SymId str_sym_{};
        Pass5ReservedResult& out_;

        TypeId last_{};

        // current generic scope: stack of visible type params (SymId)
        std::vector<lex::SymId> type_param_stack_;

        void diag(Pass5ReservedDiagnostic::Code c, const lex::Loc& loc, std::string msg) const;

        static const std::vector<ast::TypeExpr*>& type_args_of(const ast::PathTypeExpr& t)
        {
            return t.typeArgs_;
        }

        TypeId ty_builtin(BuiltinType b) const;
        TypeId ty_void() const;
        TypeId ty_type_param(lex::SymId name) const;
        TypeId resolve(ast::TypeExpr* t);

        BuiltinType map_builtin(kl::rt::BuiltinTypeExprKind k, const lex::Loc& loc) const;

        bool is_box(const ast::PathTypeExpr& t) const;
        bool is_str_single_segment(const ast::PathTypeExpr& t) const;

        bool is_type_param(lex::SymId s) const;
        void push_type_params(const std::vector<ast::TypeParamDecl*>& tps);
        void pop_to_size(size_t sz);

        std::optional<ReservedStructId> resolve_reserved_struct(lex::SymId name) const;
    };

    Pass5ReservedResult run_pass5_reserved_type_resolve(const Translation& reserved_tr,
                                                        const Pass3_5Result& p35,
                                                        lex::SymId box_sym,
                                                        lex::SymId str_sym);
} // namespace sema
