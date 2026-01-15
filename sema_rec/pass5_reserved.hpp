#pragma once

#include "logging_entities.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "translation.hpp"
#include "ast/nodes/visit/overallvisitor.hpp"


#include "decl/struct_decl.hpp"
#include "decl/type_param_decl.hpp"


#include "expr/path_type_expr.hpp"


#include "pass_3.5.hpp"
#include "type_system.hpp"

namespace sema
{
    struct Pass5ReservedResult final
    {
        TypeDB types;


        std::unordered_map<const ast::TypeExpr*, TypeId, PtrHash<ast::TypeExpr>, PtrEq<ast::TypeExpr>> type_of;


        std::unordered_map<lex::SymId, ReservedStructId> reserved_struct_by_name;
        std::vector<ast::StructDecl*> reserved_struct_decls;


        LogSequence errors;

        bool ok() const { return errors.empty(); }
    };

    class Pass5ReservedVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass5ReservedVisitor(const Pass3_5Result& p35,
                             lex::SymId box_sym,
                             lex::SymId str_sym,
                             Pass5ReservedResult& out)
            : p35_(p35), box_sym_(box_sym), str_sym_(str_sym), out_(out)
        {
        }

        void visit(ast::Module& m) override;
        void visit(ast::StructDecl& s) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::ParamDecl& p) override;


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


        std::vector<lex::SymId> type_param_stack_;


        std::vector<lex::SymId> cur_module_path_;
        lex::Loc cur_module_loc_{};


        void log_error_prefix(const lex::Loc& loc, std::string msg) const;
        void log_error_with_ident(const lex::Loc& loc, std::string msg, lex::SymId id) const;
        void log_error_with_path(const lex::Loc& loc, std::string msg, const std::vector<lex::SymId>& path) const;

        static const std::vector<ast::TypeExpr*>& type_args_of(const ast::PathTypeExpr& t) { return t.typeArgs_; }

        TypeId ty_builtin(BuiltinType b) const;
        TypeId ty_void() const;
        TypeId ty_type_param(lex::SymId name) const;
        TypeId resolve(ast::TypeExpr* t);

        BuiltinType map_builtin(kl::rt::BuiltinTypeExprKind k, const lex::Loc& loc);

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
}
