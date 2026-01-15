#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "module/module.hpp"
#include "translation.hpp"


#include "pass2.hpp"

namespace sema
{
    inline bool is_valid(ModuleId m, const Pass2Result& p2)
    {
        return m.value != kInvalidModuleId.value && m.value < p2.modules.size();
    }

    struct ImportEntry final
    {
        ModuleId importer = kInvalidModuleId;
        ModuleId target = kInvalidModuleId;
        lex::SymId alias{};

        std::string key;
        lex::Loc loc{};
    };

    struct ImportEdge final
    {
        ModuleId from = kInvalidModuleId;
        ModuleId to = kInvalidModuleId;
        lex::Loc loc{};
    };

    struct ImportTable final
    {
        ModuleId importer = kInvalidModuleId;

        std::vector<ImportEntry> entries;
        std::unordered_map<lex::SymId, ModuleId> by_alias;
    };

    struct Pass3Result final
    {
        std::vector<ImportTable> import_tables;


        LogSequence errors;

        bool ok() const { return errors.empty(); }
    };

    class Pass3ImportResolveVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass3ImportResolveVisitor(const Pass2Result& p2, Pass3Result& out, std::uint32_t unit_index);

        void visit(ast::Module& m) override;
        void visit(ast::ImportDecl& i) override;

    private:
        const Pass2Result& p2_;
        Pass3Result& out_;
        std::uint32_t unit_index_ = 0;

        ModuleId module_ = kInvalidModuleId;

        static std::string join_sym_path_numeric(const std::vector<lex::SymId>& segs);
        static std::string make_key_from_path_expr(const ast::PathExpr* p);
        static std::optional<lex::SymId> default_alias_from_path(const ast::PathExpr* p);
    };

    Pass3Result run_pass3_import_resolve(const Translation& tr, const Pass2Result& p2);
}
