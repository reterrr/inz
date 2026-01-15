#include "pass2.hpp"

#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include "expr/path_expr.hpp"

namespace sema
{
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

    std::string Pass2ModuleIndexVisitor::join_sym_path_numeric(
        const std::vector<lex::SymId>& segs)
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < segs.size(); ++i)
        {
            if (i)
                oss << "::";
            oss << static_cast<std::uint32_t>(segs[i]);
        }
        return oss.str();
    }

    std::string Pass2ModuleIndexVisitor::make_module_key_from_path(
        const std::vector<lex::SymId>& segs)
    {
        if (segs.empty())
            return "<root>";
        return join_sym_path_numeric(segs);
    }

    void Pass2ModuleIndexVisitor::visit(ast::Module& m)
    {
        std::vector<lex::SymId> segs;
        if (m.pathExpr_)
            segs = m.pathExpr_->path_;

        const std::string key = make_module_key_from_path(segs);


        if (unit_index_ >= out_.unit_to_module.size())
            out_.unit_to_module.resize(unit_index_ + 1, kInvalidModuleId);


        if (const auto it = out_.by_key.find(key); it != out_.by_key.end())
        {
            const ModuleId first_seen = it->second;


            log_module_path_first(out_.errors, segs, m.location_,
                                  /*also_log_idents=*/true);

            out_.errors.emplace_back(std::string(
                "pass2: DuplicateModuleName: duplicate module/package name across files/units"));

            {
                std::ostringstream tail;
                tail << " (key='" << key << "', first_seen_module_id=" << first_seen.value
                    << ", this_unit_index=" << unit_index_ << ")";
                out_.errors.emplace_back(tail.str());
            }


            out_.unit_to_module[unit_index_] = first_seen;
            return;
        }


        const ModuleId id{static_cast<std::uint32_t>(out_.modules.size())};
        out_.by_key.emplace(key, id);

        out_.modules.push_back(ModuleEntry{
            .id = id,
            .unit_index = unit_index_,
            .key = key,
            .loc = m.location_,
        });

        out_.unit_to_module[unit_index_] = id;
    }

    Pass2Result run_pass2_module_index(const Translation& tr)
    {
        Pass2Result out{};
        out.unit_to_module.assign(tr.units.size(), kInvalidModuleId);

        for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(tr.units.size());
             ++i)
        {
            ast::Module* mod = tr.units[i].module_;
            if (!mod)
            {
                log_module_path_first(out.errors,
                                      /*segs=*/{},
                                      /*loc=*/lex::Loc{},
                                      /*also_log_idents=*/false);

                std::ostringstream oss;
                oss << "pass2: internal error: unit " << i
                    << " has no module AST node";
                out.errors.emplace_back(oss.str());
                continue;
            }

            Pass2ModuleIndexVisitor vis(out, i);
            mod->accept(vis);
        }


        out.module_to_unit.assign(out.modules.size(),
                                  std::numeric_limits<std::uint32_t>::max());
        for (const auto& e : out.modules)
        {
            if (e.id.value < out.module_to_unit.size())
                out.module_to_unit[e.id.value] = e.unit_index;
        }

        return out;
    }
}
