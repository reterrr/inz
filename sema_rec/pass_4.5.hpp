#pragma once

#include "logging_entities.hpp"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pass2.hpp"
#include "pass3.hpp"
#include "pass4.hpp"
#include "pass_3.5.hpp"
#include "runtime_intrinsics.hpp"
#include "translation.hpp"

namespace sema
{
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


        std::unordered_map<lex::SymId, StructId> local_structs_all;
        std::unordered_map<lex::SymId, FnId> local_fns_all;
        std::unordered_map<lex::SymId, LoadFnId> local_load_fns_all;


        std::unordered_map<lex::SymId, StructId> imported_structs;
        std::unordered_map<lex::SymId, FnId> imported_fns;
        std::unordered_map<lex::SymId, LoadFnId> imported_load_fns;


        std::unordered_map<lex::SymId, StructId> visible_structs;
        std::unordered_map<lex::SymId, FnId> visible_fns;
        std::unordered_map<lex::SymId, LoadFnId> visible_load_fns;


        std::unordered_map<lex::SymId, ResolvedImport> imports_by_alias;


        std::unordered_map<lex::SymId, RuntimeIntrinsic> reserved_intrinsics;
    };

    struct Pass4_5Result final
    {
        std::vector<ModuleVisibleEnv> envs;


        LogSequence logs;


        std::unordered_set<StructId, LocalIdHash<StructTag>> reserved_no_lit_structs;

        bool ok() const { return logs.empty(); }
    };

    Pass4_5Result run_pass4_5_visible_env(const Translation& tr,
                                          const Pass2Result& p2,
                                          const Pass3Result& p3,
                                          const Pass4Result& p4,
                                          const Pass3_5Result& p3_5);
}
