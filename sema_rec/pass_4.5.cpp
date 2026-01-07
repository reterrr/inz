#include "pass_4.5.hpp"

#include <cstdint>
#include <sstream>
#include <utility>

namespace sema
{
    // ------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------

    static void push_diag(std::vector<Pass4_5Diagnostic>& ds,
                          Pass4_5Diagnostic::Code c,
                          ModuleId module,
                          const lex::Loc& loc,
                          std::string msg)
    {
        ds.push_back(Pass4_5Diagnostic{
            .code = c,
            .module = module,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    static std::uint32_t module_to_unit_index(const Pass2Result& p2, ModuleId m)
    {
        if (m.value >= p2.modules.size())
            return UINT32_MAX;
        return p2.modules[m.value].unit_index;
    }

    static bool local_has_any_name(const ModuleVisibleEnv& env, lex::SymId name)
    {
        return env.local_structs_all.contains(name)
            || env.local_fns_all.contains(name)
            || env.local_load_fns_all.contains(name);
    }

    static bool imported_has_any_name(const ModuleVisibleEnv& env, lex::SymId name)
    {
        return env.imported_structs.contains(name)
            || env.imported_fns.contains(name)
            || env.imported_load_fns.contains(name);
    }

    // ------------------------------------------------------------
    // Pass 4.5
    // ------------------------------------------------------------

    Pass4_5Result run_pass4_5_visible_env(const Pass2Result& p2,
                                          const Pass3Result& p3,
                                          const Pass4Result& p4,
                                          const Pass3_5Result& p3_5)
    {
        Pass4_5Result out{};
        const auto n_units = static_cast<std::uint32_t>(p4.modules.size());
        out.envs.resize(n_units);

        // ------------------------------------------------------------
        // Compute global reserved "no literal" structs ONCE
        // ------------------------------------------------------------
        out.reserved_no_lit_structs.reserve(p3_5.sigs.structs.size());
        for (const auto& [name, rs] : p3_5.sigs.structs)
        {
            if (!has_flag(rs.flags, ReservedStructFlags::NoLit))
                continue;

            auto it = p3_5.struct_by_name.find(name);
            if (it != p3_5.struct_by_name.end())
                out.reserved_no_lit_structs.insert(it->second);
        }

        // ------------------------------------------------------------
        // Per-unit environment build
        // ------------------------------------------------------------
        for (std::uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            ModuleVisibleEnv& env = out.envs[unit_i];
            const ModuleGlobals& mg = p4.modules[unit_i];

            env.module_id = mg.module_id;

            // ---------------------------------------
            // Prelude injection helpers (need env.module_id)
            // ---------------------------------------
            auto inject_builtin_struct = [&](lex::SymId name, StructId sid)
            {
                if (local_has_any_name(env, name))
                {
                    std::ostringstream oss;
                    oss << "builtin struct name collides with local name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::ImportedTypeCollidesWithLocal,
                              env.module_id,
                              lex::Loc{}, // implicit prelude
                              oss.str());
                    return;
                }

                if (imported_has_any_name(env, name))
                {
                    std::ostringstream oss;
                    oss << "builtin struct name collides with imported name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::DuplicateImportedTypeName,
                              env.module_id,
                              lex::Loc{},
                              oss.str());
                    return;
                }

                env.visible_structs.emplace(name, sid);
                env.imported_structs.emplace(name, sid);
            };

            auto inject_builtin_load_fn = [&](lex::SymId name, LoadFnId lfid)
            {
                if (local_has_any_name(env, name))
                {
                    std::ostringstream oss;
                    oss << "builtin load fn name collides with local name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::ImportedValueCollidesWithLocal,
                              env.module_id,
                              lex::Loc{},
                              oss.str());
                    return;
                }

                if (env.imported_load_fns.contains(name) || env.imported_fns.contains(name))
                {
                    std::ostringstream oss;
                    oss << "builtin load fn name collides with imported value name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::DuplicateImportedValueName,
                              env.module_id,
                              lex::Loc{},
                              oss.str());
                    return;
                }

                env.visible_load_fns.emplace(name, lfid);
                env.imported_load_fns.emplace(name, lfid);
            };

            auto inject_builtin_intrinsic = [&](lex::SymId name, RuntimeIntrinsic intr)
            {
                if (local_has_any_name(env, name))
                {
                    std::ostringstream oss;
                    oss << "builtin intrinsic name collides with local name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::ImportedValueCollidesWithLocal,
                              env.module_id,
                              lex::Loc{},
                              oss.str());
                    return;
                }

                if (imported_has_any_name(env, name))
                {
                    std::ostringstream oss;
                    oss << "builtin intrinsic name collides with imported name: "
                        << static_cast<std::uint32_t>(name);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::DuplicateImportedValueName,
                              env.module_id,
                              lex::Loc{},
                              oss.str());
                    return;
                }

                env.reserved_intrinsics.emplace(name, intr);
            };

            // ------------------------------------------------------------
            // 1) Locals (public + private)
            // ------------------------------------------------------------
            env.local_structs_all.clear();
            env.local_fns_all.clear();
            env.local_load_fns_all.clear();

            env.local_structs_all.reserve(mg.structs.size());
            env.local_fns_all.reserve(mg.fns.size());
            env.local_load_fns_all.reserve(mg.load_fns.size());

            for (const StructSym& s : mg.structs)
                env.local_structs_all.emplace(s.name, s.id);

            for (const FnSym& f : mg.fns)
                env.local_fns_all.emplace(f.name, f.id);

            for (const LoadFnSym& lf : mg.load_fns)
                env.local_load_fns_all.emplace(lf.name, lf.id);

            // Visible begins as locals
            env.visible_structs = env.local_structs_all;
            env.visible_fns = env.local_fns_all;
            env.visible_load_fns = env.local_load_fns_all;

            // Reset import-derived maps and alias table
            env.imports_by_alias.clear();
            env.imported_structs.clear();
            env.imported_fns.clear();
            env.imported_load_fns.clear();
            env.reserved_intrinsics.clear();

            // ------------------------------------------------------------
            // 1.5) IMPLICIT BUILTIN PRELUDE (unqualified)
            // ------------------------------------------------------------

            for (const auto& [name, sid] : p3_5.struct_by_name)
                inject_builtin_struct(name, sid);

            // If you use builtin load-fns:
            // for (const auto& [name, lfid] : p3_5.load_fn_by_name)
            //     inject_builtin_load_fn(name, lfid);

            // Intrinsics (value namespace, but not FnId-backed)
            // Requires: p3_5.intrinsic_by_name : map<SymId, RuntimeIntrinsic>
            for (const auto& [name, intr] : p3_5.intrinsic_by_name)
                inject_builtin_intrinsic(name, intr);

            // ------------------------------------------------------------
            // 2) Imports: resolve and flatten PUBLIC symbols only
            // ------------------------------------------------------------
            if (unit_i >= p3.import_tables.size())
                continue;

            const ImportTable& itab = p3.import_tables[unit_i];
            env.imports_by_alias.reserve(itab.entries.size());

            for (const ImportEntry& imp : itab.entries)
            {
                const lex::SymId alias = imp.alias;
                const ModuleId target = imp.target;

                if (target.value == kInvalidModuleId.value)
                    continue;

                if (local_has_any_name(env, alias))
                {
                    std::ostringstream oss;
                    oss << "import alias collides with local name: "
                        << static_cast<std::uint32_t>(alias);
                    push_diag(out.diagnostics,
                              Pass4_5Diagnostic::Code::ImportAliasCollidesWithLocal,
                              env.module_id,
                              imp.loc,
                              oss.str());
                    continue;
                }

                const std::uint32_t target_unit = module_to_unit_index(p2, target);
                if (target_unit == UINT32_MAX || target_unit >= p4.modules.size())
                    continue;

                const ModuleGlobals& imported = p4.modules[target_unit];

                ResolvedImport ri{};
                ri.alias = alias;
                ri.target = target;
                ri.target_unit = target_unit;
                ri.target_globals = &imported;
                ri.import_loc = imp.loc;
                env.imports_by_alias.emplace(alias, ri);

                if (imported.exported_names.empty())
                    continue;

                // ---- PUBLIC structs ----
                for (const auto& [name, sid] : imported.struct_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue;

                    if (local_has_any_name(env, name))
                    {
                        std::ostringstream oss;
                        oss << "imported public struct collides with local name: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::ImportedTypeCollidesWithLocal,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    if (imported_has_any_name(env, name))
                    {
                        std::ostringstream oss;
                        oss << "duplicate imported public type name from multiple imports: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::DuplicateImportedTypeName,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    env.imported_structs.emplace(name, sid);
                    env.visible_structs.emplace(name, sid);
                }

                // ---- PUBLIC load-fns ----
                for (const auto& [name, lfid] : imported.load_fn_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue; // require export

                    if (local_has_any_name(env, name))
                    {
                        std::ostringstream oss;
                        oss << "imported public load fn collides with local name: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::ImportedValueCollidesWithLocal,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    if (env.imported_load_fns.contains(name) || env.imported_fns.contains(name))
                    {
                        std::ostringstream oss;
                        oss << "duplicate imported public value name from multiple imports: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::DuplicateImportedValueName,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    env.imported_load_fns.emplace(name, lfid);
                    env.visible_load_fns.emplace(name, lfid);
                }

                // ---- PUBLIC fns ----
                for (const auto& [name, fid] : imported.fn_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue;

                    if (local_has_any_name(env, name))
                    {
                        std::ostringstream oss;
                        oss << "imported public fn collides with local name: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::ImportedValueCollidesWithLocal,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    if (imported_has_any_name(env, name))
                    {
                        std::ostringstream oss;
                        oss << "duplicate imported public value name from multiple imports: "
                            << static_cast<std::uint32_t>(name);
                        push_diag(out.diagnostics,
                                  Pass4_5Diagnostic::Code::DuplicateImportedValueName,
                                  env.module_id,
                                  imp.loc,
                                  oss.str());
                        continue;
                    }

                    env.imported_fns.emplace(name, fid);
                    env.visible_fns.emplace(name, fid);
                }
            }
        }

        return out;
    }
} // namespace sema
