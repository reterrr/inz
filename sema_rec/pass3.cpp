#include "pass3.hpp"

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "expr/path_expr.hpp"

namespace sema
{
    static inline void log_module_path_first(LogSequence& logs,
                                             const std::vector<lex::SymId>& module_path,
                                             const lex::Loc& loc)
    {
        logs.emplace_back(LogPath{SymKind::Ident, module_path, loc});
    }


    static std::vector<lex::SymId> parse_module_key_numeric_to_syms(const std::string& key)
    {
        std::vector<lex::SymId> segs;

        if (key.empty() || key == "<root>")
            return segs;

        std::size_t i = 0;
        while (i < key.size())
        {
            std::size_t j = key.find("::", i);
            if (j == std::string::npos)
                j = key.size();

            const std::string_view tok(key.data() + i, j - i);
            std::uint32_t v = 0;
            auto [ptr, ec] = std::from_chars(tok.data(), tok.data() + tok.size(), v);
            if (ec == std::errc{} && ptr == tok.data() + tok.size())
            {
                segs.push_back(static_cast<lex::SymId>(v));
            }
            else
            {
                break;
            }

            if (j == key.size())
                break;
            i = j + 2;
        }

        return segs;
    }

    static std::vector<lex::SymId> module_path_from_pass2(const Pass2Result& p2, ModuleId m)
    {
        if (!is_valid(m, p2))
            return {};
        return parse_module_key_numeric_to_syms(p2.modules[m.value].key);
    }


    Pass3ImportResolveVisitor::Pass3ImportResolveVisitor(const Pass2Result& p2,
                                                         Pass3Result& out,
                                                         std::uint32_t unit_index)
        : p2_(p2), out_(out), unit_index_(unit_index)
    {
        if (unit_index_ < p2_.unit_to_module.size())
            module_ = p2_.unit_to_module[unit_index_];
        else
            module_ = kInvalidModuleId;
    }

    std::string Pass3ImportResolveVisitor::join_sym_path_numeric(
        const std::vector<lex::SymId>& segs)
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < segs.size(); ++i)
        {
            if (i) oss << "::";
            oss << static_cast<std::uint32_t>(segs[i]);
        }
        return oss.str();
    }

    std::string Pass3ImportResolveVisitor::make_key_from_path_expr(const ast::PathExpr* p)
    {
        if (!p) return "<root>";
        const auto& segs = p->path_;
        if (segs.empty()) return "<root>";
        return join_sym_path_numeric(segs);
    }

    std::optional<lex::SymId>
    Pass3ImportResolveVisitor::default_alias_from_path(const ast::PathExpr* p)
    {
        if (!p) return std::nullopt;
        const auto& segs = p->path_;
        if (segs.empty()) return std::nullopt;
        return segs.back();
    }

    void Pass3ImportResolveVisitor::visit(ast::Module& m)
    {
        if (unit_index_ >= out_.import_tables.size())
            out_.import_tables.resize(unit_index_ + 1);


        ImportTable& table = out_.import_tables[unit_index_];
        table.importer = module_;

        ast::visitor::OverallVisitor::visit(m);
    }

    void Pass3ImportResolveVisitor::visit(ast::ImportDecl& i)
    {
        const std::vector<lex::SymId> importer_path = module_path_from_pass2(p2_, module_);


        const std::string key = make_key_from_path_expr(i.pathExpr_);


        std::vector<lex::SymId> import_segs;
        if (i.pathExpr_)
            import_segs = i.pathExpr_->path_;


        ModuleId target = kInvalidModuleId;
        if (const auto it = p2_.by_key.find(key); it != p2_.by_key.end())
        {
            target = it->second;
        }
        else
        {
            log_module_path_first(out_.errors, importer_path, i.location_);

            out_.errors.emplace_back(std::string("pass3: UnresolvedImport: unresolved import: "));
            out_.errors.emplace_back(LogPath{SymKind::Ident, import_segs, i.location_});
            {
                std::ostringstream tail;
                tail << " (key='" << key << "')";
                out_.errors.emplace_back(tail.str());
            }
        }


        std::optional<lex::SymId> alias_opt = i.alias;
        if (!alias_opt.has_value())
            alias_opt = default_alias_from_path(i.pathExpr_);

        if (!alias_opt)
        {
            log_module_path_first(out_.errors, importer_path, i.location_);

            out_.errors.emplace_back(std::string(
                "pass3: MissingAliasForEmptyPath: import has empty path and no alias"));

            out_.errors.emplace_back(LogPath{SymKind::Ident, import_segs, i.location_});
            return;
        }

        const lex::SymId alias = *alias_opt;


        ImportTable& table = out_.import_tables[unit_index_];

        if (table.by_alias.contains(alias))
        {
            log_module_path_first(out_.errors, importer_path, i.location_);

            out_.errors.emplace_back(
                std::string("pass3: DuplicateImportAlias: duplicate import alias: "));
            out_.errors.emplace_back(Log{SymKind::Ident, alias, i.location_});


            out_.errors.emplace_back(std::string(" for import path: "));
            out_.errors.emplace_back(LogPath{SymKind::Ident, import_segs, i.location_});


            return;
        }

        table.by_alias.emplace(alias, target);

        ImportEntry e{};
        e.importer = module_;
        e.target = target;
        e.alias = alias;
        e.key = key;
        e.loc = i.location_;
        table.entries.push_back(std::move(e));
    }


    static std::uint32_t to_index(ModuleId id)
    {
        return static_cast<std::uint32_t>(id.value);
    }

    static bool is_valid_mid(ModuleId id)
    {
        return id.value != kInvalidModuleId.value;
    }

    static std::vector<ImportEdge> collect_import_edges(const Pass3Result& p3)
    {
        std::vector<ImportEdge> edges;
        edges.reserve(256);

        for (const auto& tbl : p3.import_tables)
        {
            const ModuleId importer = tbl.importer;
            if (!is_valid_mid(importer))
                continue;

            for (const auto& e : tbl.entries)
            {
                if (!is_valid_mid(e.target))
                    continue;

                edges.push_back(ImportEdge{
                    .from = importer,
                    .to = e.target,
                    .loc = e.loc,
                });
            }
        }

        return edges;
    }

    static std::string module_key_or_fallback(const Pass2Result& p2, ModuleId m)
    {
        if (is_valid(m, p2))
            return p2.modules[m.value].key;
        return "module#" + std::to_string(static_cast<std::uint32_t>(m.value));
    }

    static void log_cycle_scc_edges(Pass3Result& out,
                                    const Pass2Result& p2,
                                    const std::vector<ImportEdge>& edges,
                                    const std::vector<ModuleId>& scc_nodes)
    {
        std::unordered_set<std::uint32_t> in_scc;
        in_scc.reserve(scc_nodes.size() * 2);
        for (ModuleId m : scc_nodes)
            in_scc.insert(to_index(m));


        std::string members;
        for (std::size_t i = 0; i < scc_nodes.size(); ++i)
        {
            if (i) members += ", ";
            members += module_key_or_fallback(p2, scc_nodes[i]);
        }


        for (const auto& ed : edges)
        {
            if (!is_valid_mid(ed.from) || !is_valid_mid(ed.to))
                continue;
            if (!in_scc.contains(to_index(ed.from)) || !in_scc.contains(to_index(ed.to)))
                continue;


            const std::vector<lex::SymId> from_path = module_path_from_pass2(p2, ed.from);
            log_module_path_first(out.errors, from_path, ed.loc);

            out.errors.emplace_back(std::string("pass3: ImportCycle: import cycle detected: "));
            {
                std::ostringstream oss;
                oss << module_key_or_fallback(p2, ed.from)
                    << " imports "
                    << module_key_or_fallback(p2, ed.to)
                    << " (cycle group: " << members << ")";
                out.errors.emplace_back(oss.str());
            }


            const std::vector<lex::SymId> to_path = module_path_from_pass2(p2, ed.to);
            out.errors.emplace_back(std::string(" cycle target module path: "));
            out.errors.emplace_back(LogPath{SymKind::Ident, to_path, ed.loc});
        }
    }

    static void detect_import_cycles_tarjan(const Pass2Result& p2, Pass3Result& out)
    {
        const std::vector<ImportEdge> edges = collect_import_edges(out);

        const std::uint32_t VN = static_cast<std::uint32_t>(p2.modules.size());
        if (VN == 0 || edges.empty())
            return;

        std::vector<std::vector<ImportEdge>> adj(VN);
        for (const auto& e : edges)
        {
            const auto f = to_index(e.from);
            if (f < VN)
                adj[f].push_back(e);
        }


        std::vector<int> index(VN, -1);
        std::vector<int> low(VN, -1);
        std::vector<std::uint32_t> st;
        st.reserve(VN);
        std::vector<bool> onstack(VN, false);
        int cur = 0;

        auto strongconnect = [&](auto&& self, std::uint32_t v) -> void
        {
            index[v] = cur;
            low[v] = cur;
            ++cur;

            st.push_back(v);
            onstack[v] = true;

            for (const auto& ed : adj[v])
            {
                const std::uint32_t w = to_index(ed.to);
                if (w >= VN)
                    continue;

                if (index[w] == -1)
                {
                    self(self, w);
                    low[v] = std::min(low[v], low[w]);
                }
                else if (onstack[w])
                {
                    low[v] = std::min(low[v], index[w]);
                }
            }


            if (low[v] == index[v])
            {
                std::vector<ModuleId> scc_nodes;
                for (;;)
                {
                    const std::uint32_t w = st.back();
                    st.pop_back();
                    onstack[w] = false;

                    scc_nodes.push_back(ModuleId{w});
                    if (w == v)
                        break;
                }


                bool is_cycle = false;
                if (scc_nodes.size() > 1)
                {
                    is_cycle = true;
                }
                else
                {
                    const std::uint32_t only = to_index(scc_nodes[0]);
                    for (const auto& ed : adj[only])
                    {
                        if (to_index(ed.to) == only)
                        {
                            is_cycle = true;
                            break;
                        }
                    }
                }

                if (is_cycle)
                {
                    log_cycle_scc_edges(out, p2, edges, scc_nodes);
                }
            }
        };

        for (std::uint32_t v = 0; v < VN; ++v)
        {
            if (index[v] == -1)
                strongconnect(strongconnect, v);
        }
    }

    Pass3Result run_pass3_import_resolve(const Translation& tr, const Pass2Result& p2)
    {
        Pass3Result out{};
        out.import_tables.resize(tr.units.size());

        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m)
            {
                continue;
            }

            Pass3ImportResolveVisitor vis(p2, out, unit_i);
            m->accept(vis);
        }

        detect_import_cycles_tarjan(p2, out);
        return out;
    }
}
