#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pass2.hpp"
#include "pass3.hpp"
#include "pass4.hpp"
#include "pass_3.5.hpp"
#include "runtime_intrinsics.hpp" // NEW

namespace sema
{
    struct Pass4_5Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            ImportAliasCollidesWithLocal,

            ImportedTypeCollidesWithLocal,
            ImportedValueCollidesWithLocal,

            DuplicateImportedTypeName,
            DuplicateImportedValueName,
        };

        Code code{};
        ModuleId module = kInvalidModuleId; // NEW: module where the diagnostic originates (importer)
        lex::Loc loc{};
        std::string message;
    };

    struct ResolvedImport final
    {
        lex::SymId alias{};
        ModuleId target{};
        std::uint32_t target_unit = UINT32_MAX;
        bool is_public = false;

        const ModuleGlobals* target_globals = nullptr;
        lex::Loc import_loc{};
    };

    struct ModuleVisibleEnv final
    {
        ModuleId module_id{};

        // locals (public+private)
        std::unordered_map<lex::SymId, StructId> local_structs_all;
        std::unordered_map<lex::SymId, FnId> local_fns_all;
        std::unordered_map<lex::SymId, LoadFnId> local_load_fns_all;

        // imported public-only (flattened unqualified)
        std::unordered_map<lex::SymId, StructId> imported_structs;
        std::unordered_map<lex::SymId, FnId> imported_fns;
        std::unordered_map<lex::SymId, LoadFnId> imported_load_fns;

        // visible = locals + imported public
        std::unordered_map<lex::SymId, StructId> visible_structs;
        std::unordered_map<lex::SymId, FnId> visible_fns;
        std::unordered_map<lex::SymId, LoadFnId> visible_load_fns;

        // qualified access
        std::unordered_map<lex::SymId, ResolvedImport> imports_by_alias;

        // reserved runtime intrinsics (value namespace, but not FnId-backed)
        std::unordered_map<lex::SymId, RuntimeIntrinsic> reserved_intrinsics;
    };

    struct Pass4_5Result final
    {
        std::vector<ModuleVisibleEnv> envs; // indexed by unit index
        std::vector<Pass4_5Diagnostic> diagnostics;

        // Global set: structs that cannot be written as literals (e.g., Box<T>, Str)
        std::unordered_set<StructId, LocalIdHash<StructTag>> reserved_no_lit_structs;

        bool ok() const { return diagnostics.empty(); }
    };

    Pass4_5Result run_pass4_5_visible_env(const Pass2Result& p2,
                                          const Pass3Result& p3,
                                          const Pass4Result& p4,
                                          const Pass3_5Result& p3_5);
} // namespace sema
