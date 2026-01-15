#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "visit/overallvisitor.hpp"
#include "translation.hpp"

#include "module/module.hpp"
#include "decl/fn_decl.hpp"
#include "decl/struct_decl.hpp"

#include "pass2.hpp"
#include "pass_3.5.hpp"
#include "type_system.hpp"

namespace sema
{
    struct StructSym final
    {
        StructId id{};
        ModuleId module = kInvalidModuleId;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::StructDecl* decl = nullptr;
    };

    struct FnSym final
    {
        FnId id{};
        ModuleId module = kInvalidModuleId;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::FnDecl* decl = nullptr;
    };

    struct LoadFnSym final
    {
        LoadFnId id{};
        ModuleId module = kInvalidModuleId;
        lex::SymId name{};
        lex::Loc loc{};
        bool is_public = false;
        ast::LoadFnDecl* decl = nullptr;
    };

    struct ModuleGlobals final
    {
        ModuleId module_id = kInvalidModuleId;

        std::vector<StructSym> structs;
        std::vector<FnSym> fns;
        std::vector<LoadFnSym> load_fns;


        std::unordered_map<lex::SymId, StructId> struct_by_name;
        std::unordered_map<lex::SymId, FnId> fn_by_name;
        std::unordered_map<lex::SymId, LoadFnId> load_fn_by_name;


        std::unordered_set<lex::SymId> exported_names;
    };

    struct Pass4Result final
    {
        std::vector<ModuleGlobals> modules;


        LogSequence errors;

        bool ok() const { return errors.empty(); }
    };

    class Pass4GlobalSymbolIndexVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass4GlobalSymbolIndexVisitor(const Pass2Result& p2,
                                      const Pass3_5Result& p35,
                                      Pass4Result& out,
                                      std::uint32_t unit_index);

        void visit(ast::Module& m) override;
        void visit(ast::StructDecl& s) override;
        void visit(ast::FnDecl& f) override;
        void visit(ast::LoadFnDecl& lf) override;

    private:
        const Pass2Result& p2_;
        const Pass3_5Result& p35_;
        Pass4Result& out_;
        std::uint32_t unit_index_ = 0;

        ModuleGlobals* cur_ = nullptr;
        ModuleId cur_mid_ = kInvalidModuleId;

        void add_struct(ast::StructDecl& s) const;
        void add_fn(ast::FnDecl& f) const;
        void add_load_fn(ast::LoadFnDecl& lf) const;


        std::string module_label() const;
        void log_reserved(const lex::Loc& loc, lex::SymId name, const char* ns) const;
        void log_dup_type(const lex::Loc& loc, lex::SymId name) const;
        void log_dup_value(const lex::Loc& loc, lex::SymId name) const;
        void log_internal(const lex::Loc& loc, std::string msg) const;
    };

    Pass4Result run_pass4_global_symbol_index(const Translation& tr,
                                              const Pass2Result& p2,
                                              const Pass3_5Result& p35);
}
