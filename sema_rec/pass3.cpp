#include "pass3.hpp"

#include <sstream>

#include "expr/path_expr.hpp"

namespace sema
{
    Pass3ImportResolveVisitor::Pass3ImportResolveVisitor(const Pass2Result& p2,
                                                         Pass3Result& out,
                                                         std::uint32_t unit_index)
        : p2_(p2), out_(out), unit_index_(unit_index)
    {
        // Determine importer module id from Pass2 (unit -> module mapping)
        if (unit_index_ < p2_.unit_to_module.size())
            module_ = p2_.unit_to_module[unit_index_];
        else
            module_ = kInvalidModuleId;
    }

    void Pass3ImportResolveVisitor::push_diag(Pass3Diagnostic::Code c,
                                              const lex::Loc& loc,
                                              std::string msg) const
    {
        out_.diagnostics.push_back(Pass3Diagnostic{
            .code = c,
            .module = module_,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    std::string Pass3ImportResolveVisitor::join_sym_path(const std::vector<lex::SymId>& segs)
    {
        std::ostringstream oss;
        for (std::size_t i = 0; i < segs.size(); ++i)
        {
            if (i) oss << "::";
            // If SymId has no stream operator, keep it numeric:
            oss << static_cast<std::uint32_t>(segs[i]);
        }
        return oss.str();
    }

    std::string Pass3ImportResolveVisitor::make_key_from_path_expr(const ast::PathExpr* p)
    {
        if (!p) return "<root>";
        const auto& segs = p->path_;
        if (segs.empty()) return "<root>";
        return join_sym_path(segs);
    }

    std::optional<lex::SymId> Pass3ImportResolveVisitor::default_alias_from_path(const ast::PathExpr* p)
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

        // Stamp table with importer module id (useful later, and for sanity checks)
        ImportTable& table = out_.import_tables[unit_index_];
        table.importer = module_;

        // OverallVisitor will visit imports + decls; OK for now.
        ast::visitor::OverallVisitor::visit(m);
    }

    void Pass3ImportResolveVisitor::visit(ast::ImportDecl& i)
    {
        // 1) key from import path
        const std::string key = make_key_from_path_expr(i.pathExpr_);

        // 2) resolve key -> ModuleId via Pass2 map
        ModuleId target = kInvalidModuleId;
        if (const auto it = p2_.by_key.find(key); it != p2_.by_key.end())
        {
            target = it->second;
        }
        else
        {
            push_diag(Pass3Diagnostic::Code::UnresolvedImport,
                      i.location_,
                      "unresolved import: " + key);
        }

        // 3) alias: explicit OR default(last segment)
        std::optional<lex::SymId> alias_opt = i.alias;
        if (!alias_opt.has_value())
            alias_opt = default_alias_from_path(i.pathExpr_);

        if (!alias_opt)
        {
            push_diag(Pass3Diagnostic::Code::MissingAliasForEmptyPath,
                      i.location_,
                      "import has empty path and no alias");

            if (i.pathExpr_) i.pathExpr_->accept(*this);
            return;
        }

        const lex::SymId alias = *alias_opt;

        // 4) Insert into import table (alias uniqueness enforced)
        ImportTable& table = out_.import_tables[unit_index_];

        if (table.by_alias.contains(alias))
        {
            std::ostringstream oss;
            oss << "duplicate import alias in module: " << static_cast<std::uint32_t>(alias);
            push_diag(Pass3Diagnostic::Code::DuplicateImportAlias, i.location_, oss.str());
        }
        else
        {
            table.by_alias.emplace(alias, target);

            ImportEntry e{};
            e.importer = module_;
            e.target = target;
            e.alias = alias;
            e.key = key;
            e.loc = i.location_;
            table.entries.push_back(std::move(e));
        }

        if (i.pathExpr_) i.pathExpr_->accept(*this);
    }

    Pass3Result run_pass3_import_resolve(const Translation& tr, const Pass2Result& p2)
    {
        Pass3Result out{};
        out.import_tables.resize(tr.units.size());

        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass3ImportResolveVisitor vis(p2, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
} // namespace sema
