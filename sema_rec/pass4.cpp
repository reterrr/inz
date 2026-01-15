#include "pass4.hpp"

#include <charconv>
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace sema
{
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
            if (ec != std::errc{} || ptr != tok.data() + tok.size())
            {
                break;
            }

            segs.push_back(static_cast<lex::SymId>(v));

            if (j == key.size())
                break;
            i = j + 2;
        }

        return segs;
    }

    static std::vector<lex::SymId> module_path_from_pass2(const Pass2Result& p2, ModuleId mid)
    {
        if (mid.value == kInvalidModuleId.value || mid.value >= p2.modules.size())
            return {};
        return parse_module_key_numeric_to_syms(p2.modules[mid.value].key);
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


    Pass4GlobalSymbolIndexVisitor::Pass4GlobalSymbolIndexVisitor(const Pass2Result& p2,
                                                                 const Pass3_5Result& p35,
                                                                 Pass4Result& out,
                                                                 std::uint32_t unit_index)
        : p2_(p2), p35_(p35), out_(out), unit_index_(unit_index)
    {
    }


    std::string Pass4GlobalSymbolIndexVisitor::module_label() const
    {
        if (cur_mid_.value != kInvalidModuleId.value && cur_mid_.value < p2_.modules.size())
        {
            const auto& me = p2_.modules[cur_mid_.value];
            std::ostringstream oss;
            oss << "module_id=" << cur_mid_.value << " key='" << me.key << "'";
            return oss.str();
        }

        std::ostringstream oss;
        oss << "module_id=" << cur_mid_.value;
        return oss.str();
    }


    void Pass4GlobalSymbolIndexVisitor::log_internal(const lex::Loc& loc, std::string msg) const
    {
        log_module_path_first(out_.errors, module_path_from_pass2(p2_, cur_mid_), loc);

        out_.errors.emplace_back(std::string("pass4: InternalError: "));
        out_.errors.emplace_back(std::move(msg));
    }

    void Pass4GlobalSymbolIndexVisitor::log_reserved(const lex::Loc& loc, lex::SymId name, const char* ns) const
    {
        log_module_path_first(out_.errors, module_path_from_pass2(p2_, cur_mid_), loc);

        out_.errors.emplace_back(std::string("pass4: ReservedName: reserved name in "));
        out_.errors.emplace_back(std::string(ns));
        out_.errors.emplace_back(std::string(" namespace: "));
        out_.errors.emplace_back(Log{SymKind::Ident, name, loc});
        out_.errors.emplace_back(std::string(" ("));
        out_.errors.emplace_back(module_label());
        out_.errors.emplace_back(std::string(")"));
    }

    void Pass4GlobalSymbolIndexVisitor::log_dup_type(const lex::Loc& loc, lex::SymId name) const
    {
        log_module_path_first(out_.errors, module_path_from_pass2(p2_, cur_mid_), loc);

        out_.errors.emplace_back(std::string("pass4: DuplicateTypeName: duplicate type name: "));
        out_.errors.emplace_back(Log{SymKind::Ident, name, loc});
        out_.errors.emplace_back(std::string(" ("));
        out_.errors.emplace_back(module_label());
        out_.errors.emplace_back(std::string(")"));
    }

    void Pass4GlobalSymbolIndexVisitor::log_dup_value(const lex::Loc& loc, lex::SymId name) const
    {
        log_module_path_first(out_.errors, module_path_from_pass2(p2_, cur_mid_), loc);

        out_.errors.emplace_back(std::string("pass4: DuplicateValueName: duplicate value name: "));
        out_.errors.emplace_back(Log{SymKind::Ident, name, loc});
        out_.errors.emplace_back(std::string(" ("));
        out_.errors.emplace_back(module_label());
        out_.errors.emplace_back(std::string(")"));
    }


    void Pass4GlobalSymbolIndexVisitor::visit(ast::Module& m)
    {
        if (unit_index_ >= out_.modules.size())
            out_.modules.resize(unit_index_ + 1);

        ModuleGlobals& mg = out_.modules[unit_index_];

        if (unit_index_ < p2_.unit_to_module.size())
            mg.module_id = p2_.unit_to_module[unit_index_];
        else
            mg.module_id = kInvalidModuleId;

        cur_ = &mg;
        cur_mid_ = mg.module_id;

        if (cur_mid_.value == kInvalidModuleId.value)
        {
            std::vector<lex::SymId> segs;
            if (m.pathExpr_)
                segs = m.pathExpr_->path_;


            log_module_path_first(out_.errors, segs, m.location_);

            out_.errors.emplace_back(std::string("pass4: InternalError: unit has invalid ModuleId mapping from pass2"));
        }

        ast::visitor::OverallVisitor::visit(m);

        cur_ = nullptr;
        cur_mid_ = kInvalidModuleId;
    }

    void Pass4GlobalSymbolIndexVisitor::visit(ast::StructDecl& s)
    {
        if (cur_) add_struct(s);
        ast::visitor::OverallVisitor::visit(s);
    }

    void Pass4GlobalSymbolIndexVisitor::visit(ast::FnDecl& f)
    {
        if (cur_) add_fn(f);
        ast::visitor::OverallVisitor::visit(f);
    }

    void Pass4GlobalSymbolIndexVisitor::visit(ast::LoadFnDecl& lf)
    {
        if (cur_) add_load_fn(lf);
        ast::visitor::OverallVisitor::visit(lf);
    }


    void Pass4GlobalSymbolIndexVisitor::add_struct(ast::StructDecl& s) const
    {
        const lex::SymId name = s.name_;
        const lex::Loc loc = s.location_;
        const bool is_public = s.isExported_;

        if (p35_.reserved.is_reserved_type(name))
        {
            log_reserved(loc, name, "type");
            return;
        }


        if (cur_->struct_by_name.contains(name))
        {
            log_dup_type(loc, name);
            return;
        }

        const StructId id{cur_mid_, static_cast<std::uint32_t>(cur_->structs.size())};


        cur_->struct_by_name.emplace(name, id);
        if (is_public)
            cur_->exported_names.insert(name);

        StructSym sym{};
        sym.id = id;
        sym.module = cur_mid_;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &s;

        cur_->structs.push_back(sym);
    }

    void Pass4GlobalSymbolIndexVisitor::add_fn(ast::FnDecl& f) const
    {
        const lex::SymId name = f.name_;
        const lex::Loc loc = f.location_;
        const bool is_public = f.isExported_;

        if (p35_.reserved.is_reserved_value(name))
        {
            log_reserved(loc, name, "value");
            return;
        }


        if (cur_->fn_by_name.contains(name) || cur_->load_fn_by_name.contains(name))
        {
            log_dup_value(loc, name);
            return;
        }

        const FnId id{cur_mid_, static_cast<std::uint32_t>(cur_->fns.size())};


        cur_->fn_by_name.emplace(name, id);
        if (is_public)
            cur_->exported_names.insert(name);

        FnSym sym{};
        sym.id = id;
        sym.module = cur_mid_;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &f;

        cur_->fns.push_back(sym);
    }

    void Pass4GlobalSymbolIndexVisitor::add_load_fn(ast::LoadFnDecl& lf) const
    {
        const lex::SymId name = lf.name_;
        const lex::Loc loc = lf.location_;
        const bool is_public = lf.exported_;

        if (p35_.reserved.is_reserved_value(name))
        {
            log_reserved(loc, name, "value");
            return;
        }


        if (cur_->fn_by_name.contains(name) || cur_->load_fn_by_name.contains(name))
        {
            log_dup_value(loc, name);
            return;
        }

        const LoadFnId id{cur_mid_, static_cast<std::uint32_t>(cur_->load_fns.size())};


        cur_->load_fn_by_name.emplace(name, id);
        if (is_public)
            cur_->exported_names.insert(name);

        LoadFnSym sym{};
        sym.id = id;
        sym.module = cur_mid_;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &lf;

        cur_->load_fns.push_back(sym);
    }


    Pass4Result run_pass4_global_symbol_index(const Translation& tr,
                                              const Pass2Result& p2,
                                              const Pass3_5Result& p35)
    {
        Pass4Result out{};
        out.modules.resize(tr.units.size());

        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m)
            {
                out.errors.emplace_back(std::string("pass4: InternalError: unit has no module AST node (unit_index=")
                    + std::to_string(unit_i) + ")");
                continue;
            }

            Pass4GlobalSymbolIndexVisitor vis(p2, p35, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
}
