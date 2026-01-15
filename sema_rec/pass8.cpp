// sema/pass8.cpp
#include "pass8.hpp"

#include <sstream>
#include <utility>

namespace sema
{
    // ============================================================
    // Per-unit module stamping + REQUIRED module-path-first logging
    // ============================================================
    static thread_local ModuleId g_pass8_unit_module = kInvalidModuleId;

    static constexpr std::vector<lex::SymId> kPass8EmptyPath{};
    static thread_local const std::vector<lex::SymId>* g_pass8_unit_path = &kPass8EmptyPath;

    struct Pass8UnitModuleScope final
    {
        ModuleId prev_mid{};
        const std::vector<lex::SymId>* prev_path = &kPass8EmptyPath;

        Pass8UnitModuleScope(ModuleId m, const std::vector<lex::SymId>* path)
            : prev_mid(g_pass8_unit_module), prev_path(g_pass8_unit_path)
        {
            g_pass8_unit_module = m;
            g_pass8_unit_path = (path ? path : &kPass8EmptyPath);
        }

        ~Pass8UnitModuleScope()
        {
            g_pass8_unit_module = prev_mid;
            g_pass8_unit_path = prev_path;
        }
    };

    static std::string pass8_module_prefix()
    {
        std::ostringstream oss;
        oss << "pass8[m=" << g_pass8_unit_module.value << "]: ";
        return oss.str();
    }

    // "void" if:
    //  - te == nullptr (your existing convention)
    //  - OR explicit builtin void (handled by typeexpr_is_builtin_void)
    static bool is_void_typeexpr(const ast::TypeExpr* te) { return te == nullptr; }

    // REQUIRED: each error log cluster begins with module path as LogPath{Ident, mod->pathExpr_->path_, loc}
    static inline void pass8_log_begin(LogSequence& logs, const lex::Loc& loc)
    {
        sema::log_path(logs, *g_pass8_unit_path, loc, /*also_log_idents=*/false);
    }

    static inline void pass8_log_text(LogSequence& logs, const lex::Loc& loc, std::string msg)
    {
        pass8_log_begin(logs, loc);
        sema::log_msg(logs, std::move(msg));
    }

    static int count_top_level_returns(ast::BlockStatement* b)
    {
        if (!b)
            return 0;

        int count = 0;
        for (auto* st : b->statements_)
        {
            if (!st)
                continue;
            if (dynamic_cast<ast::ReturnStatement*>(st))
                ++count;
        }
        return count;
    }


    static inline void pass8_log_ident_err(LogSequence& logs,
                                           const lex::Loc& loc,
                                           std::string msg,
                                           lex::SymId id)
    {
        pass8_log_begin(logs, loc);
        sema::log_msg(logs, std::move(msg));
        sema::log_ident(logs, id, loc);
    }

    static inline void pass8_log_path_err(LogSequence& logs,
                                          const lex::Loc& loc,
                                          std::string msg,
                                          const std::vector<lex::SymId>& path)
    {
        pass8_log_begin(logs, loc);
        sema::log_msg(logs, std::move(msg));
        sema::log_path(logs, path, loc, /*also_log_idents=*/false);
    }

    // ============================================================
    // Pass8DynTagVisitor
    // ============================================================

    Pass8DynTagVisitor::Pass8DynTagVisitor(const Pass4_5Result& p45,
                                           const Pass6Result& p6,
                                           Pass8Result& out,
                                           std::uint32_t unit_index)
        : p45_(p45), p6_(p6), out_(out), unit_index_(unit_index)
    {
    }

    void Pass8DynTagVisitor::log_path(std::string msg, const lex::Loc& loc) const
    {
        pass8_log_begin(out_.errors, loc);
        sema::log_msg(out_.errors, pass8_module_prefix() + std::move(msg));
        // Preserve the historical “path-like” secondary token for location anchoring.
        sema::log_path(out_.errors, kPass8EmptyPath, loc, /*also_log_idents=*/false);
    }

    void Pass8DynTagVisitor::log_ident(std::string msg, lex::SymId name,
                                       const lex::Loc& loc) const
    {
        pass8_log_begin(out_.errors, loc);
        sema::log_msg(out_.errors, pass8_module_prefix() + std::move(msg));
        sema::log_ident(out_.errors, name, loc);
    }

    void Pass8DynTagVisitor::cache_expr(const ast::Expr* e)
    {
        if (!e)
            return;
        out_.tag_of.try_emplace(e, last_);
    }

    DynTag Pass8DynTagVisitor::tag(ast::Expr* e)
    {
        if (!e)
            return DynTag::void_();

        if (auto it = out_.tag_of.find(e); it != out_.tag_of.end())
            return it->second;

        e->accept(*this);

        out_.tag_of.try_emplace(e, last_);
        return last_;
    }

    // ============================================================
    // Binding lookup
    // ============================================================

    const Binding* Pass8DynTagVisitor::binding_of(ast::Expr* e) const
    {
        if (!e || !fb_)
            return nullptr;

        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = fb_->ref_binding.find(r);
            if (it != fb_->ref_binding.end())
                return &it->second;
        }

        auto it = fb_->expr_binding.find(e);
        if (it != fb_->expr_binding.end())
            return &it->second;

        return nullptr;
    }

    // ============================================================
    // Slot utilities
    // ============================================================

    std::optional<SlotId>
    Pass8DynTagVisitor::find_slot_for_var(const ast::VarStmt& v) const
    {
        if (!fb_)
            return std::nullopt;

        for (const auto& si : fb_->slots)
        {
            if (si.var_decl == &v)
                return si.slot;
        }
        return std::nullopt;
    }

    DynTag Pass8DynTagVisitor::tag_of_slot(SlotId s) const
    {
        if (auto it = slot_tag_.find(s.index); it != slot_tag_.end())
            return it->second;

        if (!fb_ || s.index >= fb_->slots.size())
            return DynTag::obj();

        const LocalSlotInfo& info = fb_->slots[s.index];

        const ast::TypeExpr* te = nullptr;
        lex::Loc loc{};

        if (info.var_decl)
        {
            te = info.var_decl->type_;
            loc = info.var_decl->location_;
        }
        if (info.param_decl)
        {
            te = info.param_decl->type_;
            loc = info.param_decl->location_;
        }

        return tag_from_typeexpr(te, loc);
    }

    // ============================================================
    // Module and function context
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::Module& m)
    {
        if (unit_index_ < p45_.envs.size())
            env_ = &p45_.envs[unit_index_];
        else
            env_ = nullptr;

        ast::visitor::OverallVisitor::visit(m);

        env_ = nullptr;
    }

    const ast::TypeExpr* Pass8DynTagVisitor::typeexpr_of_slot(SlotId s) const
    {
        if (auto it = slot_typeexpr_.find(s.index); it != slot_typeexpr_.end())
            return it->second;

        if (!fb_ || s.index >= fb_->slots.size())
            return nullptr;

        const LocalSlotInfo& info = fb_->slots[s.index];
        if (info.var_decl)
            return info.var_decl->type_;
        if (info.param_decl)
            return info.param_decl->type_;
        return nullptr;
    }

    const ast::TypeExpr*
    Pass8DynTagVisitor::peel_one_index(const ast::TypeExpr* base_te) const
    {
        if (!base_te)
            return nullptr;

        if (auto* at = dynamic_cast<const ast::ArrayTypeExpr*>(base_te))
            return at->type_;

        return nullptr;
    }

    const ast::TypeExpr* Pass8DynTagVisitor::typeexpr_of_expr(ast::Expr* e) const
    {
        if (!e || !fb_)
            return nullptr;

        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = fb_->ref_binding.find(r);
            if (it == fb_->ref_binding.end())
                return nullptr;

            const Binding& b = it->second;
            if (b.kind != BindingKind::LocalSlot)
                return nullptr;

            return typeexpr_of_slot(b.slot);
        }

        if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
        {
            if (u->op == ast::UnaryOp::deref)
            {
                const ast::TypeExpr* inner = typeexpr_of_expr(u->expr_);
                if (auto* rt = dynamic_cast<const ast::RefTypeExpr*>(inner))
                    return rt->pointee_;
                return nullptr;
            }
        }

        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
        {
            const ast::TypeExpr* base_te = typeexpr_of_expr(ix->base_);
            return peel_one_index(base_te);
        }

        return nullptr;
    }

    // ============================================================
    // CFG / must-return (structural)
    // ============================================================

    bool Pass8DynTagVisitor::stmt_must_return(ast::Statement* s)
    {
        if (!s)
            return false;

        if (dynamic_cast<ast::ReturnStatement*>(s))
            return true;

        if (auto* b = dynamic_cast<ast::BlockStatement*>(s))
            return block_must_return(b);

        if (auto* i = dynamic_cast<ast::IfStatement*>(s))
        {
            const bool thenR = block_must_return(i->thenBody_);

            bool elseIfAll = true;
            for (auto* eif : i->elseIfs_)
            {
                if (!eif)
                    continue;
                elseIfAll = elseIfAll && block_must_return(eif->then_);
            }

            if (!i->else_ || !i->else_->then_)
                return false;

            const bool elseR = block_must_return(i->else_->then_);
            return thenR && elseIfAll && elseR;
        }

        // MVP: loops do not guarantee return
        if (dynamic_cast<ast::WhileStatement*>(s))
            return false;
        if (dynamic_cast<ast::DoWhileStatement*>(s))
            return false;

        return false;
    }

    bool Pass8DynTagVisitor::block_must_return(ast::BlockStatement* b)
    {
        if (!b)
            return false;

        for (auto* st : b->statements_)
        {
            if (!st)
                continue;
            if (stmt_must_return(st))
                return true;
        }

        return false;
    }

    // ============================================================
    // FnDecl return typeexpr discovery
    // ============================================================

    const ast::TypeExpr*
    Pass8DynTagVisitor::fn_ret_typeexpr_ptr(const ast::FnDecl& f)
    {
        return f.ret_;
    }

    // ============================================================
    // Function context + must-return check
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::FnDecl& f)
    {
        fb_ = nullptr;
        slot_tag_.clear();
        slot_typeexpr_.clear();

        if (unit_index_ < p6_.modules.size())
        {
            const ModuleBindings& mb = p6_.modules[unit_index_];
            for (const auto& [fnid, binds] : mb.fns)
            {
                (void)fnid;
                if (binds.decl == &f)
                {
                    fb_ = &binds;
                    break;
                }
            }
        }

        cur_fn_ = &f;
        cur_ret_te_ = fn_ret_typeexpr_ptr(f);
        cur_fn_is_void_ = is_void_typeexpr(cur_ret_te_) || typeexpr_is_builtin_void(cur_ret_te_);

        // Seed parameter slot tags from declared parameter types.
        if (fb_)
        {
            for (const auto& si : fb_->slots)
            {
                if (!si.param_decl)
                    continue;

                DynTag t = tag_from_typeexpr(si.param_decl->type_, si.param_decl->location_);
                slot_tag_[si.slot.index] = t;              // <-- ADD THIS
                slot_typeexpr_[si.slot.index] = si.param_decl->type_;
            }
        }

        ast::visitor::OverallVisitor::visit(f);

        // must-return check (only for non-void functions)
        if (!cur_fn_is_void_)
        {
            const int n = count_top_level_returns(f.body_);
            if (n == 0)
                log_path("MissingTopLevelReturn: non-void function must have exactly one top-level return", f.location_);
            else if (n > 1)
                log_path("MultipleTopLevelReturns: non-void function must have exactly one top-level return", f.location_);
        }

        cur_fn_ = nullptr;
        cur_ret_te_ = nullptr;
        cur_fn_is_void_ = true;

        fb_ = nullptr;
        slot_tag_.clear();
    }

    // ============================================================
    // Condition checks
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::IfStatement& i)
    {
        ast::visitor::OverallVisitor::visit(i);

        if (i.condition_)
        {
            const DynTag ct = tag(expr_ptr(i.condition_));
            if (ct.kind != DynTagKind::Bool)
            {
                log_path("NonBoolCondition: if condition must be bool (i1)", i.location_);
            }
        }
    }

    void Pass8DynTagVisitor::visit(ast::WhileStatement& w)
    {
        ast::visitor::OverallVisitor::visit(w);

        if (w.condition_)
        {
            const DynTag ct = tag(expr_ptr(w.condition_));
            if (ct.kind != DynTagKind::Bool)
            {
                log_path("NonBoolCondition: while condition must be bool (i1)", w.location_);
            }
        }
    }

    void Pass8DynTagVisitor::visit(ast::DoWhileStatement& d)
    {
        ast::visitor::OverallVisitor::visit(d);

        if (d.condition_)
        {
            const DynTag ct = tag(expr_ptr(d.condition_));
            if (ct.kind != DynTagKind::Bool)
            {
                log_path("NonBoolCondition: do-while condition must be bool (i1)", d.location_);
            }
        }
    }

    // ============================================================
    // Return checking
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::ReturnStatement& r)
    {
        ast::visitor::OverallVisitor::visit(r);

        if (!cur_fn_)
            return;

        if (cur_fn_is_void_)
        {
            if (r.expr_)
            {
                log_path("ReturnValueInVoidFn: returning a value from a void function is not allowed",
                         r.location_);
            }
            return;
        }

        if (!r.expr_)
        {
            log_path("MissingReturnValue: missing return value in non-void function",
                     r.location_);
        }
    }

    // ============================================================
    // VarStmt: learn slot tag from declared type, else initializer
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::VarStmt& v)
    {
        ast::visitor::OverallVisitor::visit(v);

        if (!fb_)
            return;

        auto slot = find_slot_for_var(v);
        if (!slot)
            return;

        if (v.type_)
            slot_typeexpr_[slot->index] = v.type_;

        DynTag declared = tag_from_typeexpr(v.type_, v.location_);
        DynTag init = DynTag::obj();
        if (v.init_)
            init = tag(expr_ptr(v.init_));

        DynTag t = DynTag::obj();

        if (declared.kind == DynTagKind::Bool || declared.kind == DynTagKind::StructObj)
            t = declared;
        else if (init.kind == DynTagKind::StructObj)
            t = init;
        else if (init.kind == DynTagKind::Bool)
            t = DynTag::boolean();
        else
            t = DynTag::obj();

        slot_tag_[slot->index] = t;
    }

    // ============================================================
    // Literals
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::BoolLiteralExpr& b)
    {
        (void)b;
        last_ = DynTag::boolean();
        cache_expr(&b);
    }

    void Pass8DynTagVisitor::visit(ast::IntLiteralExpr& i)
    {
        (void)i;
        last_ = DynTag::obj();
        cache_expr(&i);
    }

    void Pass8DynTagVisitor::visit(ast::FloatLiteralExpr& f)
    {
        (void)f;
        last_ = DynTag::obj();
        cache_expr(&f);
    }

    void Pass8DynTagVisitor::visit(ast::CharLiteralExpr& c)
    {
        (void)c;
        last_ = DynTag::obj();
        cache_expr(&c);
    }

    void Pass8DynTagVisitor::visit(ast::StringLiteralExpr& s)
    {
        (void)s;
        last_ = DynTag::obj();
        cache_expr(&s);
    }

    // ============================================================
    // RefExpr / PathExpr
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::RefExpr& r)
    {
        last_ = DynTag::obj();

        if (const Binding* b = binding_of(&r))
        {
            if (b->kind == BindingKind::LocalSlot)
                last_ = tag_of_slot(b->slot);
        }

        cache_expr(&r);
    }

    void Pass8DynTagVisitor::visit(ast::PathExpr& p)
    {
        last_ = DynTag::obj();
        cache_expr(&p);
    }

    // ============================================================
    // Unary / Binary
    // ============================================================

    bool Pass8DynTagVisitor::is_bool_result_unary(const ast::UnaryExpr& u)
    {
        return u.op == ast::UnaryOp::logical_not;
    }

    void Pass8DynTagVisitor::visit(ast::UnaryExpr& u)
    {
        if (u.expr_)
            (void)tag(u.expr_);

        last_ = is_bool_result_unary(u) ? DynTag::boolean() : DynTag::obj();
        cache_expr(&u);
    }

    bool Pass8DynTagVisitor::is_bool_result_binary(const ast::BinaryExpr& b)
    {
        using Op = ast::BinaryOp;
        switch (b.op)
        {
        case Op::logical_and:
        case Op::logical_or:
        case Op::equal:
        case Op::not_equal:
        case Op::less:
        case Op::less_equal:
        case Op::greater:
        case Op::greater_equal:
            return true;
        default:
            return false;
        }
    }

    void Pass8DynTagVisitor::visit(ast::BinaryExpr& b)
    {
        if (b.lhs_)
            (void)tag(b.lhs_);
        if (b.rhs_)
            (void)tag(b.rhs_);

        last_ = is_bool_result_binary(b) ? DynTag::boolean() : DynTag::obj();
        cache_expr(&b);
    }

    // ============================================================
    // Call / Assign / Field / Index / ArrayLiteral
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::CallExpr& c)
    {
        if (c.callee_)
            (void)tag(c.callee_);
        for (auto* a : c.args_)
            if (a)
                (void)tag(a);

        last_ = DynTag::obj();
        cache_expr(&c);
    }

    void Pass8DynTagVisitor::visit(ast::AssignExpr& a)
    {
        if (a.lhs_)
            (void)tag(a.lhs_);
        if (a.rhs_)
            (void)tag(a.rhs_);

        last_ = DynTag::obj();
        cache_expr(&a);
    }

    void Pass8DynTagVisitor::visit(ast::FieldExpr& f)
    {
        if (f.base_)
            (void)tag(f.base_);

        last_ = DynTag::obj();
        cache_expr(&f);
    }

    void Pass8DynTagVisitor::visit(ast::ArrayLiteralExpr& a)
    {
        for (auto* ep : a.v_)
            if (ep)
                (void)tag(ep);

        last_ = DynTag::obj();
        cache_expr(&a);
    }

    void Pass8DynTagVisitor::visit(ast::IndexExpr& i)
    {
        if (i.base_)
            (void)tag(i.base_);
        if (i.index_)
            (void)tag(i.index_);

        DynTag out = DynTag::obj();

        const ast::TypeExpr* base_te = typeexpr_of_expr(i.base_);
        const ast::TypeExpr* elem_te = peel_one_index(base_te);

        if (elem_te)
        {
            out = tag_from_typeexpr(elem_te, i.location_);
        }

        last_ = out;
        cache_expr(&i);
    }

    void Pass8DynTagVisitor::visit(ast::FieldInitExpr& f)
    {
        if (f.value_)
            (void)tag(f.value_);
        last_ = DynTag::obj();
        cache_expr(&f);
    }

    // ============================================================
    // Struct lookup (names)
    // ============================================================

    std::optional<StructId>
    Pass8DynTagVisitor::resolve_struct_simple_name(lex::SymId name) const
    {
        if (!env_)
            return std::nullopt;
        if (auto it = env_->visible_structs.find(name); it != env_->visible_structs.end())
            return it->second;
        return std::nullopt;
    }

    std::optional<StructId>
    Pass8DynTagVisitor::resolve_struct_qualified(lex::SymId alias, lex::SymId name) const
    {
        if (!env_)
            return std::nullopt;

        auto it = env_->imports_by_alias.find(alias);
        if (it == env_->imports_by_alias.end())
            return std::nullopt;

        const ResolvedImport& ri = it->second;
        if (!ri.target_globals)
            return std::nullopt;

        if (auto jt = ri.target_globals->struct_by_name.find(name);
            jt != ri.target_globals->struct_by_name.end())
            return jt->second;

        return std::nullopt;
    }

    std::optional<StructId>
    Pass8DynTagVisitor::resolve_struct_id_from_type_path(const std::vector<lex::SymId>& segs,
                                                         const lex::Loc& loc) const
    {
        if (segs.size() == 1)
            return resolve_struct_simple_name(segs[0]);

        if (segs.size() == 2)
            return resolve_struct_qualified(segs[0], segs[1]);

        log_path("UnsupportedTypeExprPathDepth: type path depth > 2 is not supported (pass8)", loc);
        return std::nullopt;
    }

    // ============================================================
    // TypeExpr -> DynTag  (ADAPT POINT)
    // ============================================================

    DynTag Pass8DynTagVisitor::tag_from_typeexpr(const ast::TypeExpr* te,
                                                 const lex::Loc& loc) const
    {
        if (is_void_typeexpr(te) || typeexpr_is_builtin_void(te))
            return DynTag::void_();

        if (typeexpr_is_builtin_bool(te))
            return DynTag::boolean();

        // NEW: peel one ref layer
        if (auto* rt = dynamic_cast<const ast::RefTypeExpr*>(te))
            return tag_from_typeexpr(rt->pointee_, loc);

        // (optional) if you want: peel arrays etc similarly

        std::vector<lex::SymId> segs;
        if (typeexpr_try_get_path2(te, segs))
        {
            if (auto sid = resolve_struct_id_from_type_path(segs, loc); sid.has_value())
                return DynTag::struct_obj(*sid);

            if (!segs.empty())
                log_ident("UnknownStructInTypeExpr: unknown struct name in type expression", segs.back(), loc);
            else
                log_path("UnknownStructInTypeExpr: unknown struct name in type expression", loc);

            return DynTag::obj();
        }

        return DynTag::obj();
    }


    // ============================================================
    // Struct literal tagging
    // ============================================================

    std::optional<StructId>
    Pass8DynTagVisitor::resolve_struct_id_from_head(ast::Expr* head,
                                                    const lex::Loc& loc) const
    {
        if (!head)
            return std::nullopt;

        if (auto* p = dynamic_cast<ast::PathExpr*>(head))
        {
            const auto& segs = p->path_;

            if (segs.size() == 1)
                return resolve_struct_simple_name(segs[0]);

            if (segs.size() == 2)
                return resolve_struct_qualified(segs[0], segs[1]);

            log_path("UnsupportedStructLiteralHead: struct literal head path depth > 2 is not supported", loc);
            return std::nullopt;
        }

        if (auto* r = dynamic_cast<ast::RefExpr*>(head))
            return resolve_struct_simple_name(r->name);

        log_path("UnsupportedStructLiteralHead: unsupported struct literal head expression kind", loc);
        return std::nullopt;
    }

    void Pass8DynTagVisitor::visit(ast::StructLiteralExpr& s)
    {
        for (auto* e : s.elements_)
            if (e)
                (void)tag(e);

        const auto sid = resolve_struct_id_from_head(s.expr_, s.location_);
        if (!sid)
        {
            if (auto* r = dynamic_cast<ast::RefExpr*>(s.expr_))
            {
                log_ident("UnknownStructInStructLiteral: unknown struct name in struct literal",
                          r->name, s.location_);
            }
            else if (auto* p = dynamic_cast<ast::PathExpr*>(s.expr_))
            {
                if (!p->path_.empty())
                    log_ident("UnknownStructInStructLiteral: unknown struct name in struct literal",
                              p->path_.back(), s.location_);
                else
                    log_path("UnknownStructInStructLiteral: unknown struct name in struct literal",
                             s.location_);
            }
            else
            {
                log_path("UnknownStructInStructLiteral: unknown struct name in struct literal",
                         s.location_);
            }

            last_ = DynTag::obj();
            cache_expr(&s);
            return;
        }

        if (p45_.reserved_no_lit_structs.contains(*sid))
        {
            log_path("ReservedStructLiteralForbidden: struct literal syntax is forbidden for this reserved type",
                     s.location_);
            last_ = DynTag::obj();
            cache_expr(&s);
            return;
        }

        last_ = DynTag::struct_obj(*sid);
        cache_expr(&s);
    }

    // ============================================================
    // ADAPT LAYER (IMPLEMENT AGAINST YOUR TypeExpr AST)
    // ============================================================

    bool Pass8DynTagVisitor::typeexpr_is_builtin_bool(const ast::TypeExpr* te)
    {
        // Optional: explicit builtin node.
        // ADAPT: if this doesn't exist in your AST, remove this block.
        if (auto* b = dynamic_cast<const ast::BuiltinTypeExpr*>(te))
            return b->kind_ == kl::rt::BuiltinTypeExprKind::Bool; // ADAPT names

        return false;
    }

    bool Pass8DynTagVisitor::typeexpr_is_builtin_void(const ast::TypeExpr* te)
    {
        // Optional: if you have an explicit builtin node.
        // ADAPT: if this doesn't exist in your AST, remove this block.
        if (auto* b = dynamic_cast<const ast::BuiltinTypeExpr*>(te))
            return b->kind_ == kl::rt::BuiltinTypeExprKind::Void; // ADAPT names

        return false;
    }

    bool Pass8DynTagVisitor::typeexpr_try_get_path2(const ast::TypeExpr* te,
                                                    std::vector<lex::SymId>& out_segs)
    {
        out_segs.clear();
        if (!te)
            return false;

        // ADAPT: if your AST has a different node name than PathTypeExpr, change it here.
        if (auto* p = dynamic_cast<const ast::PathTypeExpr*>(te))
        {
            out_segs = p->pathExpr_->path_; // ADAPT: member name if different
            return out_segs.size() == 1 || out_segs.size() == 2;
        }

        return false;
    }

    // ============================================================
    // Driver
    // ============================================================

    static ModuleId pass8_unit_module_id(const Pass4_5Result& p45,
                                         const Pass6Result& p6,
                                         std::uint32_t unit_i)
    {
        if (unit_i < p45.envs.size())
            return p45.envs[unit_i].module_id;

        if (unit_i < p6.modules.size())
            return p6.modules[unit_i].module_id;

        return kInvalidModuleId;
    }

    Pass8Result run_pass8_dyn_tag(const Translation& tr,
                                  const Pass4_5Result& p45,
                                  const Pass6Result& p6)
    {
        Pass8Result out{};

        for (std::uint32_t unit_i = 0;
             unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m)
                continue;

            const std::vector<lex::SymId>* mod_path = &kPass8EmptyPath;
            if (m->pathExpr_)
                mod_path = &m->pathExpr_->path_;

            Pass8UnitModuleScope scope(pass8_unit_module_id(p45, p6, unit_i), mod_path);

            Pass8DynTagVisitor vis(p45, p6, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
} // namespace sema
