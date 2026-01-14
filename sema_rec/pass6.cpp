#include "pass6.hpp"

#include <sstream>
#include <string>
#include <utility>
#include <vector>


#include "expr/assign_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/path_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "stmt/block_statement.hpp"

namespace sema
{
    static inline void log_module_path_first(LogSequence& logs,
                                             const std::vector<lex::SymId>& segs,
                                             const lex::Loc& loc)
    {
        logs.emplace_back(LogPath{SymKind::Ident, segs, loc});
    }


    Pass6LocalBinderVisitor::Pass6LocalBinderVisitor(const Pass4Result& p4,
                                                     const Pass4_5Result& p45,
                                                     Pass6Result& out,
                                                     std::uint32_t unit_index)
        : p4_(p4)
          , p45_(p45)
          , out_(out)
          , unit_index_(unit_index)
    {
        if (unit_index_ < p45_.envs.size())
            module_ = p45_.envs[unit_index_].module_id;
        else if (unit_index_ < p4_.modules.size())
            module_ = p4_.modules[unit_index_].module_id;
    }


    void Pass6LocalBinderVisitor::log_prefix(const lex::Loc& loc) const
    {
        log_module_path_first(out_.errors, mod_path_, loc);
    }

    void Pass6LocalBinderVisitor::log_text(const lex::Loc& loc, std::string msg) const
    {
        log_prefix(loc);
        out_.errors.emplace_back(std::move(msg));
    }

    void Pass6LocalBinderVisitor::log_ident_err(const lex::Loc& loc, std::string msg, lex::SymId id) const
    {
        log_prefix(loc);
        out_.errors.emplace_back(std::move(msg));
        out_.errors.emplace_back(Log{SymKind::Ident, id, loc});
    }

    void Pass6LocalBinderVisitor::log_path_err(const lex::Loc& loc,
                                               std::string msg,
                                               const std::vector<lex::SymId>& path) const
    {
        log_prefix(loc);
        out_.errors.emplace_back(std::move(msg));
        out_.errors.emplace_back(LogPath{SymKind::Ident, path, loc});
    }


    void Pass6LocalBinderVisitor::push_scope() { scopes_.emplace_back(); }

    void Pass6LocalBinderVisitor::pop_scope()
    {
        if (!scopes_.empty()) scopes_.pop_back();
    }

    bool Pass6LocalBinderVisitor::declare_in_current_scope(lex::SymId name, SlotId slot)
    {
        if (scopes_.empty()) push_scope();
        auto& cur = scopes_.back();
        auto [it, inserted] = cur.emplace(name, slot);
        return inserted;
    }

    std::optional<SlotId> Pass6LocalBinderVisitor::lookup_local(lex::SymId name) const
    {
        for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it)
        {
            const auto& scope = *it;
            if (auto f = scope.find(name); f != scope.end())
                return f->second;
        }
        return std::nullopt;
    }


    SlotId Pass6LocalBinderVisitor::alloc_slot_for_param(ast::ParamDecl& p) const
    {
        SlotId slot{cur_fn_->slot_count++};

        LocalSlotInfo info{};
        info.slot = slot;
        info.name = p.name_;
        info.mut_ = ast::Mutability::Imm;
        info.storage_ = ast::Storage{};
        info.param_decl = &p;

        if (slot.index >= cur_fn_->slots.size())
            cur_fn_->slots.resize(slot.index + 1);
        cur_fn_->slots[slot.index] = info;

        return slot;
    }

    SlotId Pass6LocalBinderVisitor::alloc_slot_for_var(ast::VarStmt& v) const
    {
        SlotId slot{cur_fn_->slot_count++};

        LocalSlotInfo info{};
        info.slot = slot;
        info.name = v.name_;
        info.mut_ = v.mut_;
        info.storage_ = v.storage_;
        info.var_decl = &v;

        if (slot.index >= cur_fn_->slots.size())
            cur_fn_->slots.resize(slot.index + 1);
        cur_fn_->slots[slot.index] = info;

        return slot;
    }


    std::optional<RuntimeIntrinsic> Pass6LocalBinderVisitor::lookup_reserved_intrinsic(const ModuleVisibleEnv* env,
        lex::SymId name)
    {
        if (!env) return std::nullopt;
        auto it = env->reserved_intrinsics.find(name);
        if (it == env->reserved_intrinsics.end())
            return std::nullopt;
        return it->second;
    }

    std::optional<FnId> Pass6LocalBinderVisitor::lookup_global_fn(lex::SymId name) const
    {
        if (!env_) return std::nullopt;
        if (auto it = env_->visible_fns.find(name); it != env_->visible_fns.end())
            return it->second;
        return std::nullopt;
    }

    std::optional<LoadFnId> Pass6LocalBinderVisitor::lookup_global_load_fn(lex::SymId name) const
    {
        if (!env_) return std::nullopt;
        if (auto it = env_->visible_load_fns.find(name); it != env_->visible_load_fns.end())
            return it->second;
        return std::nullopt;
    }

    bool Pass6LocalBinderVisitor::is_import_alias(lex::SymId name) const
    {
        if (!env_) return false;
        return env_->imports_by_alias.contains(name);
    }

    bool Pass6LocalBinderVisitor::is_place_expr(ast::Expr* e)
    {
        if (dynamic_cast<ast::RefExpr*>(e))
            return true;

        if (dynamic_cast<ast::FieldExpr*>(e))
            return true;

        if (dynamic_cast<ast::IndexExpr*>(e))
            return true;

        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
            return u->op == ast::UnaryOp::deref;

        return false;
    }


    void Pass6LocalBinderVisitor::visit(ast::Module& m)
    {
        mod_loc_ = m.location_;
        mod_path_.clear();
        if (m.pathExpr_)
            mod_path_ = m.pathExpr_->path_;

        if (unit_index_ >= out_.modules.size())
            out_.modules.resize(unit_index_ + 1);

        mg_ = nullptr;
        env_ = nullptr;
        module_ = kInvalidModuleId;

        if (unit_index_ < p4_.modules.size())
            mg_ = &p4_.modules[unit_index_];

        if (unit_index_ < p45_.envs.size())
            env_ = &p45_.envs[unit_index_];


        if (mg_) module_ = mg_->module_id;
        else if (env_) module_ = env_->module_id;

        ModuleBindings& mb = out_.modules[unit_index_];
        mb.module_id = module_;

        ast::visitor::OverallVisitor::visit(m);

        mg_ = nullptr;
        env_ = nullptr;
        module_ = kInvalidModuleId;
    }

    void Pass6LocalBinderVisitor::visit(ast::FnDecl& f)
    {
        if (!mg_)
        {
            ast::visitor::OverallVisitor::visit(f);
            return;
        }

        std::optional<FnId> fnid;
        for (const auto& sym : mg_->fns)
        {
            if (sym.decl == &f)
            {
                fnid = sym.id;
                break;
            }
        }

        if (!fnid.has_value())
        {
            ast::visitor::OverallVisitor::visit(f);
            return;
        }

        ModuleBindings& mb = out_.modules[unit_index_];
        FnBindings& fb = mb.fns[*fnid];

        fb.id = *fnid;
        fb.decl = &f;
        fb.slot_count = 0;
        fb.slots.clear();
        fb.ref_binding.clear();
        fb.expr_binding.clear();

        cur_fn_ = &fb;

        scopes_.clear();
        push_scope();

        for (auto* p : f.params_)
        {
            if (!p) continue;
            const SlotId s = alloc_slot_for_param(*p);

            if (!declare_in_current_scope(p->name_, s))
            {
                log_ident_err(p->location_,
                              "pass6: DuplicateLocalNameInScope: duplicate local name in same scope: ",
                              p->name_);
            }
        }

        if (f.body_)
            f.body_->accept(*this);

        scopes_.clear();
        cur_fn_ = nullptr;
    }

    void Pass6LocalBinderVisitor::visit(ast::LoadFnDecl& lf)
    {
        (void)lf;
    }

    void Pass6LocalBinderVisitor::visit(ast::BlockStatement& b)
    {
        push_scope();
        for (auto* s : b.statements_)
            if (s) s->accept(*this);
        pop_scope();
    }

    void Pass6LocalBinderVisitor::visit(ast::VarStmt& v)
    {
        if (!cur_fn_)
        {
            ast::visitor::OverallVisitor::visit(v);
            return;
        }

        const SlotId s = alloc_slot_for_var(v);

        if (!declare_in_current_scope(v.name_, s))
        {
            log_ident_err(v.location_,
                          "pass6: DuplicateLocalNameInScope: duplicate local name in same scope: ",
                          v.name_);
        }

        ast::visitor::OverallVisitor::visit(v);
    }

    void Pass6LocalBinderVisitor::visit(ast::StructLiteralExpr& s)
    {
        for (auto* fi : s.elements_)
            if (fi) fi->accept(*this);
    }


    void Pass6LocalBinderVisitor::visit(ast::RefExpr& r)
    {
        if (!cur_fn_) return;

        Binding bnd{};

        if (auto slot = lookup_local(r.name); slot.has_value())
        {
            bnd.kind = BindingKind::LocalSlot;
            bnd.slot = *slot;
            cur_fn_->ref_binding.emplace(&r, bnd);
            cur_fn_->expr_binding.emplace(&r, bnd);
            return;
        }

        if (auto k = lookup_reserved_intrinsic(env_, r.name); k.has_value())
        {
            bnd.kind = BindingKind::RuntimeIntrinsic;
            bnd.intrinsic = *k;
            cur_fn_->ref_binding.emplace(&r, bnd);
            cur_fn_->expr_binding.emplace(&r, bnd);
            return;
        }

        if (auto fn = lookup_global_fn(r.name); fn.has_value())
        {
            bnd.kind = BindingKind::GlobalFn;
            bnd.fn = *fn;
            cur_fn_->ref_binding.emplace(&r, bnd);
            cur_fn_->expr_binding.emplace(&r, bnd);
            return;
        }

        if (auto lf = lookup_global_load_fn(r.name); lf.has_value())
        {
            bnd.kind = BindingKind::GlobalLoadFn;
            bnd.load_fn = *lf;
            cur_fn_->ref_binding.emplace(&r, bnd);
            cur_fn_->expr_binding.emplace(&r, bnd);
            return;
        }

        if (is_import_alias(r.name))
        {
            bnd.kind = BindingKind::ImportAlias;
            bnd.import_alias = r.name;
            cur_fn_->ref_binding.emplace(&r, bnd);
            cur_fn_->expr_binding.emplace(&r, bnd);
            return;
        }

        log_ident_err(r.location_,
                      "pass6: UnresolvedName: unresolved name: ",
                      r.name);

        bnd.kind = BindingKind::Unresolved;
        cur_fn_->ref_binding.emplace(&r, bnd);
        cur_fn_->expr_binding.emplace(&r, bnd);
    }

    std::optional<ModuleId> Pass6LocalBinderVisitor::lookup_import_alias_target(lex::SymId alias) const
    {
        if (!env_) return std::nullopt;
        auto it = env_->imports_by_alias.find(alias);
        if (it == env_->imports_by_alias.end())
            return std::nullopt;
        return it->second.target;
    }

    std::optional<FnId> Pass6LocalBinderVisitor::lookup_fn_in_module(ModuleId mid, lex::SymId name) const
    {
        for (const auto& mg : p4_.modules)
        {
            if (mg.module_id != mid)
                continue;

            for (const auto& sym : mg.fns)
            {
                if (sym.decl && sym.decl->name_ == name)
                    return sym.id;
            }
            return std::nullopt;
        }
        return std::nullopt;
    }

    std::optional<LoadFnId> Pass6LocalBinderVisitor::lookup_load_fn_in_module(ModuleId mid, lex::SymId name) const
    {
        for (const auto& mg : p4_.modules)
        {
            if (mg.module_id != mid)
                continue;

            for (const auto& sym : mg.load_fns)
            {
                if (sym.decl && sym.decl->name_ == name)
                    return sym.id;
            }
            return std::nullopt;
        }
        return std::nullopt;
    }


    void Pass6LocalBinderVisitor::visit(ast::PathExpr& p)
    {
        ast::visitor::OverallVisitor::visit(p);

        if (!cur_fn_ || !env_)
            return;

        Binding bnd{};

        auto bind = [&](Binding&& b)
        {
            cur_fn_->expr_binding[&p] = b;
        };

        const auto& segs = p.path_;
        if (segs.empty())
            return;

        if (segs.size() == 1)
        {
            const lex::SymId name = segs[0];

            if (auto slot = lookup_local(name); slot.has_value())
            {
                bnd.kind = BindingKind::LocalSlot;
                bnd.slot = *slot;
                bind(std::move(bnd));
                return;
            }

            if (auto k = lookup_reserved_intrinsic(env_, name); k.has_value())
            {
                bnd.kind = BindingKind::RuntimeIntrinsic;
                bnd.intrinsic = *k;
                bind(std::move(bnd));
                return;
            }

            if (auto fn = lookup_global_fn(name); fn.has_value())
            {
                bnd.kind = BindingKind::GlobalFn;
                bnd.fn = *fn;
                bind(std::move(bnd));
                return;
            }

            if (auto lf = lookup_global_load_fn(name); lf.has_value())
            {
                bnd.kind = BindingKind::GlobalLoadFn;
                bnd.load_fn = *lf;
                bind(std::move(bnd));
                return;
            }

            if (auto it = env_->visible_structs.find(name); it != env_->visible_structs.end())
            {
                bnd.kind = BindingKind::GlobalStruct;
                bnd.struct_id = it->second;
                bind(std::move(bnd));
                return;
            }

            if (is_import_alias(name))
            {
                bnd.kind = BindingKind::ImportAlias;
                bnd.import_alias = name;
                bind(std::move(bnd));
                return;
            }

            log_ident_err(p.location_,
                          "pass6: UnresolvedName: unresolved path name: ",
                          name);

            bnd.kind = BindingKind::Unresolved;
            bind(std::move(bnd));
            return;
        }

        if (segs.size() != 2)
        {
            log_path_err(p.location_,
                         "pass6: UnresolvedName: unsupported path depth (expected Name or alias::Name): ",
                         segs);

            bnd.kind = BindingKind::Unresolved;
            bind(std::move(bnd));
            return;
        }

        const lex::SymId alias = segs[0];
        const lex::SymId leaf = segs[1];

        auto itImp = env_->imports_by_alias.find(alias);
        if (itImp == env_->imports_by_alias.end() || !itImp->second.target_globals)
        {
            log_ident_err(p.location_,
                          "pass6: UnresolvedName: unknown import alias in path: ",
                          alias);

            bnd.kind = BindingKind::Unresolved;
            bind(std::move(bnd));
            return;
        }

        const ModuleGlobals& imported = *itImp->second.target_globals;

        auto is_exported = [&](lex::SymId nm) -> bool
        {
            return imported.exported_names.contains(nm);
        };

        if (auto it = imported.fn_by_name.find(leaf);
            it != imported.fn_by_name.end() && is_exported(leaf))
        {
            bnd.kind = BindingKind::GlobalFn;
            bnd.fn = it->second;
            bind(std::move(bnd));
            return;
        }

        if (auto it = imported.load_fn_by_name.find(leaf);
            it != imported.load_fn_by_name.end() && is_exported(leaf))
        {
            bnd.kind = BindingKind::GlobalLoadFn;
            bnd.load_fn = it->second;
            bind(std::move(bnd));
            return;
        }

        if (auto it = imported.struct_by_name.find(leaf);
            it != imported.struct_by_name.end() && is_exported(leaf))
        {
            bnd.kind = BindingKind::GlobalStruct;
            bnd.struct_id = it->second;
            bind(std::move(bnd));
            return;
        }

        log_path_err(p.location_,
                     "pass6: UnresolvedName: unresolved imported name in path: ",
                     segs);

        bnd.kind = BindingKind::Unresolved;
        bind(std::move(bnd));
    }

    void Pass6LocalBinderVisitor::visit(ast::UnaryExpr& u)
    {
        if (u.expr_) u.expr_->accept(*this);

        if (!cur_fn_)
            return;

        if (u.op != ast::UnaryOp::addr_of_mut)
            return;

        auto* r = dynamic_cast<ast::RefExpr*>(u.expr_);
        if (!r)
        {
            log_text(u.location_,
                     "pass6: InvalidMutBorrow: cannot take mutable reference of non-place expression");
            return;
        }

        auto itb = cur_fn_->ref_binding.find(r);
        if (itb == cur_fn_->ref_binding.end())
            return;

        const Binding& b = itb->second;
        if (b.kind != BindingKind::LocalSlot)
        {
            log_ident_err(u.location_,
                          "pass6: InvalidMutBorrow: cannot take mutable reference of non-local binding: ",
                          r->name);
            return;
        }

        if (b.slot.index >= cur_fn_->slots.size())
            return;

        const LocalSlotInfo& info = cur_fn_->slots[b.slot.index];
        if (info.mut_ != ast::Mutability::Mut)
        {
            log_ident_err(u.location_,
                          "pass6: InvalidMutBorrow: cannot take mutable reference of immutable binding: ",
                          info.name);
        }
    }

    void Pass6LocalBinderVisitor::visit(ast::AssignExpr& a)
    {
        if (a.lhs_) a.lhs_->accept(*this);
        if (a.rhs_) a.rhs_->accept(*this);

        if (!cur_fn_ || !a.lhs_)
            return;

        if (!is_place_expr(a.lhs_))
        {
            log_text(a.location_,
                     "pass6: InvalidAssignTarget: invalid assignment target (expected place expression)");
            return;
        }

        auto* lhs_ref = dynamic_cast<ast::RefExpr*>(a.lhs_);
        if (!lhs_ref)
            return;

        auto itb = cur_fn_->ref_binding.find(lhs_ref);
        if (itb == cur_fn_->ref_binding.end())
            return;

        const Binding& b = itb->second;

        if (b.kind == BindingKind::Unresolved)
            return;

        if (b.kind != BindingKind::LocalSlot)
        {
            log_ident_err(a.location_,
                          "pass6: InvalidAssignTarget: invalid assignment target (not a local slot): ",
                          lhs_ref->name);
            return;
        }

        if (b.slot.index >= cur_fn_->slots.size())
            return;

        const LocalSlotInfo& info = cur_fn_->slots[b.slot.index];
        if (info.mut_ != ast::Mutability::Mut)
        {
            log_ident_err(a.location_,
                          "pass6: ImmutableAssign: cannot assign to immutable binding: ",
                          info.name);
        }
    }


    Pass6Result run_pass6_local_binder(const Translation& tr,
                                       const Pass4Result& p4,
                                       const Pass4_5Result& p45)
    {
        Pass6Result out{};
        out.modules.resize(tr.units.size());

        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass6LocalBinderVisitor vis(p4, p45, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
}
