#include "pass_4.5.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace sema
{
    static inline std::vector<lex::SymId> unit_module_path(const Translation& tr,
                                                           std::uint32_t unit_i)
    {
        if (unit_i >= static_cast<std::uint32_t>(tr.units.size()))
            return {};

        ast::Module* mod = tr.units[unit_i].module_;
        if (!mod || !mod->pathExpr_)
            return {};

        return mod->pathExpr_->path_;
    }

    static inline lex::Loc unit_module_loc(const Translation& tr, std::uint32_t unit_i)
    {
        if (unit_i >= static_cast<std::uint32_t>(tr.units.size()))
            return lex::Loc{};

        ast::Module* mod = tr.units[unit_i].module_;
        if (!mod)
            return lex::Loc{};
        return mod->location_;
    }

    static inline void log_module_path_first(LogSequence& logs,
                                             const std::vector<lex::SymId>& segs,
                                             const lex::Loc& loc,
                                             bool also_log_idents = false)
    {
        logs.emplace_back(LogPath{SymKind::Ident, segs, loc});


        if (also_log_idents)
        {
            for (lex::SymId s : segs)
                logs.emplace_back(Log{SymKind::Ident, s, loc});
        }
    }


    static std::uint32_t module_to_unit_index(const Pass2Result& p2, ModuleId m)
    {
        if (m.value >= p2.modules.size())
            return UINT32_MAX;
        return p2.modules[m.value].unit_index;
    }

    static bool local_has_any_name(const ModuleVisibleEnv& env, lex::SymId name)
    {
        return env.local_structs_all.contains(name) ||
            env.local_fns_all.contains(name) ||
            env.local_load_fns_all.contains(name);
    }

    static bool imported_has_any_name(const ModuleVisibleEnv& env, lex::SymId name)
    {
        return env.imported_structs.contains(name) ||
            env.imported_fns.contains(name) ||
            env.imported_load_fns.contains(name);
    }


    static inline void log_err(Pass4_5Result& out,
                               const std::vector<lex::SymId>& mod_path,
                               const lex::Loc& anchor_loc,
                               std::string msg_prefix,
                               std::optional<LogEntity> focus = std::nullopt,
                               std::string msg_suffix = {})
    {
        log_module_path_first(out.logs, mod_path, anchor_loc, /*also_log_idents=*/false);
        out.logs.emplace_back(std::move(msg_prefix));
        if (focus.has_value())
            out.logs.emplace_back(std::move(*focus));
        if (!msg_suffix.empty())
            out.logs.emplace_back(std::move(msg_suffix));
    }


    Pass4_5Result run_pass4_5_visible_env(const Translation& tr,
                                          const Pass2Result& p2,
                                          const Pass3Result& p3,
                                          const Pass4Result& p4,
                                          const Pass3_5Result& p3_5)
    {
        Pass4_5Result out{};

        const auto n_units = static_cast<std::uint32_t>(p4.modules.size());
        out.envs.resize(n_units);


        out.reserved_no_lit_structs.reserve(p3_5.sigs.structs.size());
        for (const auto& [name, rs] : p3_5.sigs.structs)
        {
            if (!has_flag(rs.flags, ReservedStructFlags::NoLit))
                continue;

            auto it = p3_5.struct_by_name.find(name);
            if (it != p3_5.struct_by_name.end())
                out.reserved_no_lit_structs.insert(it->second);
        }


        for (std::uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            ModuleVisibleEnv& env = out.envs[unit_i];
            const ModuleGlobals& mg = p4.modules[unit_i];

            env.module_id = mg.module_id;


            const std::vector<lex::SymId> importer_path = unit_module_path(tr, unit_i);
            const lex::Loc importer_loc = unit_module_loc(tr, unit_i);


            auto inject_builtin_struct = [&](lex::SymId name, StructId sid)
            {
                if (local_has_any_name(env, name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: BuiltinTypeCollidesWithLocal: builtin struct collides with local name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                if (imported_has_any_name(env, name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: DuplicateImportedTypeName: builtin struct collides with imported name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                env.visible_structs.emplace(name, sid);
                env.imported_structs.emplace(name, sid);
            };

            auto inject_builtin_load_fn = [&](lex::SymId name, LoadFnId lfid)
            {
                if (local_has_any_name(env, name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: BuiltinValueCollidesWithLocal: builtin load fn collides with local name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                if (env.imported_load_fns.contains(name) || env.imported_fns.contains(name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: DuplicateImportedValueName: builtin load fn collides with imported value name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                env.visible_load_fns.emplace(name, lfid);
                env.imported_load_fns.emplace(name, lfid);
            };

            auto inject_builtin_intrinsic = [&](lex::SymId name, RuntimeIntrinsic intr)
            {
                if (local_has_any_name(env, name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: BuiltinIntrinsicCollidesWithLocal: builtin intrinsic collides with local name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                if (imported_has_any_name(env, name))
                {
                    log_module_path_first(out.logs, importer_path, importer_loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(std::string(
                        "pass4.5: DuplicateImportedValueName: builtin intrinsic collides with imported name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, name, importer_loc});
                    return;
                }

                env.reserved_intrinsics.emplace(name, intr);
            };


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


            env.visible_structs = env.local_structs_all;
            env.visible_fns = env.local_fns_all;
            env.visible_load_fns = env.local_load_fns_all;


            env.imports_by_alias.clear();
            env.imported_structs.clear();
            env.imported_fns.clear();
            env.imported_load_fns.clear();
            env.reserved_intrinsics.clear();


            for (const auto& [name, sid] : p3_5.struct_by_name)
                inject_builtin_struct(name, sid);


            for (const auto& [name, intr] : p3_5.intrinsic_by_name)
                inject_builtin_intrinsic(name, intr);


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
                    log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                    out.logs.emplace_back(
                        std::string("pass4.5: ImportAliasCollidesWithLocal: import alias collides with local name: "));
                    out.logs.emplace_back(Log{SymKind::Ident, alias, imp.loc});
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


                for (const auto& [name, sid] : imported.struct_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue;

                    if (local_has_any_name(env, name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: ImportedTypeCollidesWithLocal: imported public struct collides with local name: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    if (imported_has_any_name(env, name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: DuplicateImportedTypeName: duplicate imported public type name from multiple imports: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    env.imported_structs.emplace(name, sid);
                    env.visible_structs.emplace(name, sid);
                }


                for (const auto& [name, lfid] : imported.load_fn_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue;

                    if (local_has_any_name(env, name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: ImportedValueCollidesWithLocal: imported public load fn collides with local name: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    if (env.imported_load_fns.contains(name) || env.imported_fns.contains(name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: DuplicateImportedValueName: duplicate imported public value name from multiple imports: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    env.imported_load_fns.emplace(name, lfid);
                    env.visible_load_fns.emplace(name, lfid);
                }


                for (const auto& [name, fid] : imported.fn_by_name)
                {
                    if (!imported.exported_names.contains(name))
                        continue;

                    if (local_has_any_name(env, name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: ImportedValueCollidesWithLocal: imported public fn collides with local name: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    if (imported_has_any_name(env, name))
                    {
                        log_module_path_first(out.logs, importer_path, imp.loc, /*also_log_idents=*/true);
                        out.logs.emplace_back(std::string(
                            "pass4.5: DuplicateImportedValueName: duplicate imported public value name from multiple imports: "));
                        out.logs.emplace_back(Log{SymKind::Ident, name, imp.loc});
                        continue;
                    }

                    env.imported_fns.emplace(name, fid);
                    env.visible_fns.emplace(name, fid);
                }
            }
        }

        return out;
    }
}
