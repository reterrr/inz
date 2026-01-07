#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "visit/overallvisitor.hpp"
#include "translation.hpp"

#include "module/module.hpp"
#include "decl/fn_decl.hpp"
#include "decl/struct_decl.hpp"

#include "pass2.hpp"              // Pass2Result + ModuleId
#include "pass_3.5.hpp"   // Pass3_5Result (reserved sets)
#include "pass4.hpp"
#include "type_system.hpp"

namespace sema
{
    struct StructSym final
    {
        StructId id{};
        ModuleId module;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::StructDecl* decl = nullptr;
    };

    struct FnSym final
    {
        FnId id{};
        ModuleId module;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::FnDecl* decl = nullptr;
    };

    struct LoadFnSym final
    {
        LoadFnId id{};
        ModuleId module;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::LoadFnDecl* decl = nullptr;
    };

    struct ModuleGlobals final
    {
        ModuleId module_id{};

        std::vector<StructSym> structs;
        std::vector<FnSym> fns;
        std::vector<LoadFnSym> load_fns;

        std::unordered_map<lex::SymId, StructId> struct_by_name;
        std::unordered_map<lex::SymId, FnId> fn_by_name;
        std::unordered_map<lex::SymId, LoadFnId> load_fn_by_name;

        std::unordered_set<lex::SymId> exported_names;
    };

    struct Pass4Diagnostic final
    {
        enum class Code : uint8_t
        {
            DuplicateTypeName,
            DuplicateValueName,
            ReservedName
        };

        Code code{};
        uint32_t module;
        lex::Loc loc{};
        std::string message;
    };

    struct Pass4Result final
    {
        std::vector<ModuleGlobals> modules; // indexed by unit index
        std::vector<Pass4Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
    };

    class Pass4GlobalSymbolIndexVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass4GlobalSymbolIndexVisitor(const Pass2Result& p2,
                                      const Pass3_5Result& p35,
                                      Pass4Result& out,
                                      uint32_t unit_index)
            : p2_(p2), p35_(p35), out_(out), unit_index_(unit_index)
        {
        }

        void visit(ast::Module& m) override;
        void visit(ast::StructDecl& s) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::LoadFnDecl& lf) override;

    private:
        const Pass2Result& p2_;
        const Pass3_5Result& p35_;
        Pass4Result& out_;
        uint32_t unit_index_ = 0;

        ModuleGlobals* cur_ = nullptr;

        void add_struct(ast::StructDecl& s) const;
        void add_fn(ast::FnDecl& f) const;
        void add_load_fn(ast::LoadFnDecl& lf) const;

        Pass4Diagnostic diag(Pass4Diagnostic::Code c, const lex::Loc& loc, std::string msg) const;
        void diag_dup_type(const lex::Loc& loc, lex::SymId name, ModuleId module) const;
        void diag_dup_value(const lex::Loc& loc, lex::SymId name, ModuleId module) const;
        void diag_reserved(const lex::Loc& loc, lex::SymId name, const char* ns) const;
    };

    Pass4Result run_pass4_global_symbol_index(const Translation& tr,
                                              const Pass2Result& p2,
                                              const Pass3_5Result& p35);
} // namespace sema
