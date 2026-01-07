// sema/pass2.cpp
#include "pass2.hpp"

#include <sstream>

#include "expr/path_expr.hpp"

namespace sema
{
    static Pass2Diagnostic mkdiag(Pass2Diagnostic::Code c,
                                  ModuleId module,
                                  const lex::Loc& loc,
                                  std::string msg)
    {
        return Pass2Diagnostic{
            .code = c,
            .module = module,
            .loc = loc,
            .message = std::move(msg),
        };
    }

    std::string Pass2ModuleIndexVisitor::join_sym_path(const std::vector<lex::SymId>& segs)
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < segs.size(); ++i)
        {
            if (i) oss << "::";
            // ADAPT: replace with interner view(sym) when you have access to it.
            oss << static_cast<std::uint32_t>(segs[i]);
        }
        return oss.str();
    }

    std::string Pass2ModuleIndexVisitor::make_module_key(const ast::Module& m)
    {
        if (!m.pathExpr_)
            return "<root>";

        const auto& segs = m.pathExpr_->path_;
        if (segs.empty())
            return "<root>";

        return join_sym_path(segs);
    }

    void Pass2ModuleIndexVisitor::visit(ast::Module& m)
    {
        const std::string key = make_module_key(m);

        // Ensure vector is present and initialized (in case caller didn't size it).
        if (unit_index_ >= out_.unit_to_module.size())
            out_.unit_to_module.resize(unit_index_ + 1, kInvalidModuleId);

        // Duplicate module name across units
        if (const auto it = out_.by_key.find(key); it != out_.by_key.end())
        {
            const ModuleId first_seen = it->second;

            out_.diagnostics.push_back(mkdiag(
                Pass2Diagnostic::Code::DuplicateModuleName,
                first_seen,
                m.location_,
                "duplicate module/package name across files/units: " + key));

            // Bind this unit to the first-seen module id to keep compilation deterministic.
            out_.unit_to_module[unit_index_] = first_seen;
            return;
        }

        // New module
        const ModuleId id{ static_cast<std::uint32_t>(out_.modules.size()) };
        out_.by_key.emplace(key, id);

        out_.modules.push_back(ModuleEntry{
            .id = id,
            .unit_index = unit_index_,
            .key = key,
            .loc = m.location_,
        });

        out_.unit_to_module[unit_index_] = id;

        // Pass2 does not need to recurse.
        // ast::visitor::OverallVisitor::visit(m);
    }

    Pass2Result run_pass2_module_index(const Translation& tr)
    {
        Pass2Result out{};

        out.unit_to_module.assign(tr.units.size(), kInvalidModuleId);

        for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(tr.units.size()); ++i)
        {
            ast::Module* mod = tr.units[i].module_;
            if (!mod)
                continue;

            Pass2ModuleIndexVisitor vis(out, i);
            mod->accept(vis);

            // If a unit had a module node, it should have been assigned.
            // If not, keep it invalid (safe default).
        }

        // module_to_unit must be sized after we know module count
        out.module_to_unit.assign(out.modules.size(), std::numeric_limits<std::uint32_t>::max());
        for (const auto& e : out.modules)
        {
            if (e.id.value < out.module_to_unit.size())
                out.module_to_unit[e.id.value] = e.unit_index;
        }

        return out;
    }

} // namespace sema
