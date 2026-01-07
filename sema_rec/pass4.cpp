#include "pass4.hpp"

#include <sstream>

namespace sema
{
    Pass4Diagnostic Pass4GlobalSymbolIndexVisitor::diag(Pass4Diagnostic::Code c, const lex::Loc& loc, std::string msg) const
    {
        return Pass4Diagnostic{
            .code = c,
            .module = unit_index_,
            .loc = loc,
            .message = std::move(msg)
        };
    }

    void Pass4GlobalSymbolIndexVisitor::diag_dup_type(const lex::Loc& loc, lex::SymId name, ModuleId module) const
    {
        std::ostringstream oss;
        oss << "duplicate type name " << name << "in module: " << module.value;
        out_.diagnostics.push_back(diag(Pass4Diagnostic::Code::DuplicateTypeName, loc, oss.str()));
    }

    void Pass4GlobalSymbolIndexVisitor::diag_dup_value(const lex::Loc& loc, lex::SymId name, ModuleId module) const
    {
        std::ostringstream oss;
        oss << "duplicate value name (fn) " << name << "in module: " << module.value;
        out_.diagnostics.push_back(diag(Pass4Diagnostic::Code::DuplicateValueName, loc, oss.str()));
    }

    void Pass4GlobalSymbolIndexVisitor::diag_reserved(const lex::Loc& loc, lex::SymId name,
                                                      const char* ns) const
    {
        std::ostringstream oss;
        oss << "reserved builtin/intrinsic name in " << ns
            << " namespace: " << name;
        out_.diagnostics.push_back(diag(Pass4Diagnostic::Code::ReservedName, loc, oss.str()));
    }


    void Pass4GlobalSymbolIndexVisitor::visit(ast::Module& m)
    {
        if (unit_index_ >= out_.modules.size())
            out_.modules.resize(unit_index_ + 1);

        ModuleGlobals& mg = out_.modules[unit_index_];
        mg.module_id = p2_.unit_to_module[unit_index_];

        cur_ = &mg;

        ast::visitor::OverallVisitor::visit(m);

        cur_ = nullptr;
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

    void Pass4GlobalSymbolIndexVisitor::add_load_fn(ast::LoadFnDecl& lf) const
    {
        const lex::SymId name = lf.name_;
        const lex::Loc loc = lf.location_;
        const bool is_public = lf.exported_; // or lf.exported_ depending on your AST

        // reserved value namespace
        if (p35_.reserved.is_reserved_value(name))
        {
            diag_reserved(loc, name, "value");
            return;
        }

        // IMPORTANT: duplicate check is against BOTH fn and load fn
        // Because value namespace is shared.
        if (cur_->fn_by_name.contains(name) || cur_->load_fn_by_name.contains(name))
        {
            diag_dup_value(loc, name, cur_->module_id);
            return;
        }

        const LoadFnId id{cur_->module_id, static_cast<uint32_t>(cur_->load_fns.size())};

        // your policy: only public in hash tables
        if (is_public)
            cur_->load_fn_by_name.emplace(name, id);

        LoadFnSym sym{};
        sym.id = id;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &lf;
        sym.module = cur_->module_id;

        cur_->load_fns.push_back(sym);
    }


    void Pass4GlobalSymbolIndexVisitor::add_struct(ast::StructDecl& s) const
    {
        const lex::SymId name = s.name_;
        const lex::Loc loc = s.location_;
        const bool is_public = s.isExported_;

        // Reserved type namespace
        if (p35_.reserved.is_reserved_type(name))
        {
            diag_reserved(loc, name, "type");
            return;
        }

        // Duplicate type name in this module
        if (cur_->struct_by_name.contains(name))
        {
            diag_dup_type(loc, name, cur_->module_id);
            return;
        }

        const StructId id{cur_->module_id, static_cast<uint32_t>(cur_->structs.size())};
        if (is_public)
        {
            cur_->struct_by_name.emplace(name, id);
            cur_->exported_names.insert(name);
        }

        StructSym sym{};
        sym.id = id;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &s;
        sym.module = cur_->module_id;

        cur_->structs.push_back(sym);
    }

    void Pass4GlobalSymbolIndexVisitor::add_fn(ast::FnDecl& f) const
    {
        const lex::SymId name = f.name_;
        const lex::Loc loc = f.location_;
        const bool is_public = f.isExported_;

        // Reserved value namespace
        if (p35_.reserved.is_reserved_value(name))
        {
            diag_reserved(loc, name, "value");
            return;
        }

        // Duplicate value name in this module
        if (cur_->fn_by_name.contains(name) || cur_->load_fn_by_name.contains(name))
        {
            diag_dup_value(loc, name, cur_->module_id);
            return;
        }

        const FnId id{cur_->module_id, static_cast<uint32_t>(cur_->fns.size())};
        if (is_public)
        {
            cur_->fn_by_name.emplace(name, id);
            cur_->exported_names.insert(name);
        }

        FnSym sym{};
        sym.id = id;
        sym.name = name;
        sym.loc = loc;
        sym.is_public = is_public;
        sym.decl = &f;
        sym.module = cur_->module_id;

        cur_->fns.push_back(sym);
    }


    Pass4Result run_pass4_global_symbol_index(const Translation& tr,
                                              const Pass2Result& p2,
                                              const Pass3_5Result& p35)
    {
        Pass4Result out{};
        out.modules.resize(tr.units.size());

        for (uint32_t unit_i = 0; unit_i < static_cast<uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_; // your accessor
            if (!m) continue;

            Pass4GlobalSymbolIndexVisitor vis(p2, p35, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
} // namespace sema
