#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "translation.hpp"
#include "module/module.hpp"

// Pass 2
#include "pass2.hpp"

namespace sema
{
    // Explicit invalid ModuleId so unresolved imports do NOT map to module 0.
    inline bool is_valid(ModuleId m, const Pass2Result& p2)
    {
        return m.value != kInvalidModuleId.value && m.value < p2.modules.size();
    }

    struct ImportEntry final
    {
        ModuleId importer = kInvalidModuleId; // module that contains this import (NEW)
        ModuleId target = kInvalidModuleId;   // resolved ModuleId OR kInvalidModuleId
        lex::SymId alias{};

        std::string key; // resolved path key (same scheme as pass2)
        lex::Loc loc{};
    };

    struct ImportTable final
    {
        ModuleId importer = kInvalidModuleId; // importer module id for this unit (NEW)

        std::vector<ImportEntry> entries;                  // preserve order
        std::unordered_map<lex::SymId, ModuleId> by_alias; // alias -> ModuleId (may be invalid)
    };

    struct Pass3Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            UnresolvedImport,
            DuplicateImportAlias,
            MissingAliasForEmptyPath,
        };

        Code code{};
        ModuleId module = kInvalidModuleId; // module where diagnostic originates (NEW)
        lex::Loc loc{};
        std::string message;
    };

    struct Pass3Result final
    {
        std::vector<ImportTable> import_tables; // indexed by unit index
        std::vector<Pass3Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
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

        ModuleId module_ = kInvalidModuleId; // importer module id for this visitor (NEW)

        void push_diag(Pass3Diagnostic::Code c, const lex::Loc& loc, std::string msg) const;

        static std::string join_sym_path(const std::vector<lex::SymId>& segs);
        static std::string make_key_from_path_expr(const ast::PathExpr* p);
        static std::optional<lex::SymId> default_alias_from_path(const ast::PathExpr* p);
    };

    Pass3Result run_pass3_import_resolve(const Translation& tr, const Pass2Result& p2);

} // namespace sema
