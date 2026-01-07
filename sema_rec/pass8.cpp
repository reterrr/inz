#include "pass8.hpp"

#include <utility>
#include <sstream>

namespace sema
{
    // ============================================================
    // Helpers
    // ============================================================

    static bool is_void_typeexpr(const ast::TypeExpr* te)
    {
        return te == nullptr;
    }

    // ============================================================
    // Pass8DynTagVisitor
    // ============================================================

    Pass8DynTagVisitor::Pass8DynTagVisitor(const Pass4_5Result& p45,
                                           const Pass6Result& p6,
                                           Pass8Result& out,
                                           std::uint32_t unit_index)
        : p45_(p45)
          , p6_(p6)
          , out_(out)
          , unit_index_(unit_index)
    {
    }

    void Pass8DynTagVisitor::push_diag(Pass8Diagnostic::Code c, const lex::Loc& loc, std::string msg) const
    {
        out_.diagnostics.push_back(Pass8Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    void Pass8DynTagVisitor::cache_expr(const ast::Expr* e)
    {
        if (!e) return;
        out_.tag_of.try_emplace(e, last_);
    }

    DynTag Pass8DynTagVisitor::tag(ast::Expr* e)
    {
        if (!e) return DynTag::void_();

        if (auto it = out_.tag_of.find(e); it != out_.tag_of.end())
            return it->second;

        e->accept(*this);

        // Defensive: ensure cached even if visit() forgot
        out_.tag_of.try_emplace(e, last_);
        return last_;
    }

    // ============================================================
    // Binding lookup
    // ============================================================

    const Binding* Pass8DynTagVisitor::binding_of(ast::Expr* e) const
    {
        if (!e || !fb_) return nullptr;

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

    std::optional<SlotId> Pass8DynTagVisitor::find_slot_for_var(const ast::VarStmt& v) const
    {
        if (!fb_) return std::nullopt;

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

        // Fallback: declared type
        if (!fb_ || s.index >= fb_->slots.size())
            return DynTag::obj();

        const LocalSlotInfo& info = fb_->slots[s.index];

        const ast::TypeExpr* te = nullptr;
        lex::Loc loc{};

        if (info.var_decl)  { te = info.var_decl->type_;  loc = info.var_decl->location_; }
        if (info.param_decl){ te = info.param_decl->type_; loc = info.param_decl->location_; }

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
        if (info.var_decl)   return info.var_decl->type_;
        if (info.param_decl) return info.param_decl->type_;
        return nullptr;
    }

    const ast::TypeExpr* Pass8DynTagVisitor::peel_one_index(const ast::TypeExpr* base_te) const
    {
        if (!base_te) return nullptr;

        // array indexing peels one ArrayTypeExpr layer: T[len] -> T
        if (auto* at = dynamic_cast<const ast::ArrayTypeExpr*>(base_te))
            return at->type_;

        // If you later support indexing into Box<T> etc, extend here.
        return nullptr;
    }

    const ast::TypeExpr* Pass8DynTagVisitor::typeexpr_of_expr(ast::Expr* e) const
    {
        if (!e || !fb_) return nullptr;

        // RefExpr -> slot declared type
        if (auto* r = dynamic_cast<ast::RefExpr*>(e))
        {
            auto it = fb_->ref_binding.find(r);
            if (it == fb_->ref_binding.end()) return nullptr;

            const Binding& b = it->second;
            if (b.kind != BindingKind::LocalSlot) return nullptr;

            return typeexpr_of_slot(b.slot);
        }

        // *ref : peel RefTypeExpr (optional, but useful)
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

        // IndexExpr: peel ArrayTypeExpr
        if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
        {
            const ast::TypeExpr* base_te = typeexpr_of_expr(ix->base_);
            return peel_one_index(base_te);
        }

        return nullptr;
    }

    void Pass8DynTagVisitor::visit(ast::ArrayLiteralExpr& a)
    {
        for (auto& ep : a.v_)
            if (ep) (void)tag(ep); // adjust if not unique_ptr

        last_ = DynTag::obj();
        cache_expr(&a);
    }

    void Pass8DynTagVisitor::visit(ast::IndexExpr& i)
    {
        if (i.base_)  (void)tag(i.base_);
        if (i.index_) (void)tag(i.index_);

        // Default: value is an Obj*
        DynTag out = DynTag::obj();

        // Try recover the declared type expression of the base and peel one array layer
        const ast::TypeExpr* base_te = typeexpr_of_expr(i.base_);
        const ast::TypeExpr* elem_te = peel_one_index(base_te);

        if (elem_te)
        {
            // If element is bool or struct, produce richer tag
            out = tag_from_typeexpr(elem_te, i.location_);
        }

        last_ = out;
        cache_expr(&i);
    }

    void Pass8DynTagVisitor::visit(ast::FnDecl& f)
    {
        fb_ = nullptr;
        slot_tag_.clear();

        // Find FnBindings for this FnDecl in this unit
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

        // Seed parameter slot tags from declared parameter types.
        // This is essential for: consume_s(v: S) -> v.x / v.y
        if (fb_)
        {
            for (const auto& si : fb_->slots)
            {
                if (!si.param_decl) continue;

                DynTag t = tag_from_typeexpr(si.param_decl->type_, si.param_decl->location_);
                // Only store meaningful tags (Bool/StructObj); Obj is default anyway.
                if (t.kind == DynTagKind::Bool || t.kind == DynTagKind::StructObj)
                    slot_tag_[si.slot.index] = t;
            }
        }

        ast::visitor::OverallVisitor::visit(f);

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
                push_diag(Pass8Diagnostic::Code::NonBoolCondition,
                          i.location_,
                          "if condition must be bool (i1)");
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
                push_diag(Pass8Diagnostic::Code::NonBoolCondition,
                          w.location_,
                          "while condition must be bool (i1)");
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
                push_diag(Pass8Diagnostic::Code::NonBoolCondition,
                          d.location_,
                          "do-while condition must be bool (i1)");
            }
        }
    }

    // ============================================================
    // VarStmt: learn slot tag from declared type, else initializer
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::VarStmt& v)
    {
        ast::visitor::OverallVisitor::visit(v);

        if (!fb_) return;

        auto slot = find_slot_for_var(v);
        if (!slot) return;

        if (v.type_)                       // NEW
            slot_typeexpr_[slot->index] = v.type_;

        // existing tag learning logic unchanged...
        DynTag declared = tag_from_typeexpr(v.type_, v.location_);
        DynTag init = DynTag::obj();
        if (v.init_) init = tag(expr_ptr(v.init_));

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
        // Expression path defaults to Obj. (callee / value paths later)
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
        if (u.expr_) (void)tag(u.expr_);

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
        if (b.lhs_) (void)tag(b.lhs_);
        if (b.rhs_) (void)tag(b.rhs_);

        last_ = is_bool_result_binary(b) ? DynTag::boolean() : DynTag::obj();
        cache_expr(&b);
    }

    // ============================================================
    // Call / Assign / Field / Index
    // ============================================================

    void Pass8DynTagVisitor::visit(ast::CallExpr& c)
    {
        if (c.callee_) (void)tag(c.callee_);
        for (auto* a : c.args_) if (a) (void)tag(a);

        last_ = DynTag::obj();
        cache_expr(&c);
    }

    void Pass8DynTagVisitor::visit(ast::AssignExpr& a)
    {
        if (a.lhs_) (void)tag(a.lhs_);
        if (a.rhs_) (void)tag(a.rhs_);

        last_ = DynTag::obj();
        cache_expr(&a);
    }

    void Pass8DynTagVisitor::visit(ast::FieldExpr& f)
    {
        if (f.base_) (void)tag(f.base_);

        // Field expression itself yields a value (currently model as Obj).
        // IMPORTANT: the base must be StructObj for codegen to know struct_id.
        last_ = DynTag::obj();
        cache_expr(&f);
    }



    void Pass8DynTagVisitor::visit(ast::FieldInitExpr& f)
    {
        if (f.value_) (void)tag(f.value_);
        last_ = DynTag::obj();
        cache_expr(&f);
    }

    // ============================================================
    // Struct lookup (names)
    // ============================================================

    std::optional<StructId> Pass8DynTagVisitor::resolve_struct_simple_name(lex::SymId name) const
    {
        if (!env_) return std::nullopt;
        if (auto it = env_->visible_structs.find(name); it != env_->visible_structs.end())
            return it->second;
        return std::nullopt;
    }

    std::optional<StructId> Pass8DynTagVisitor::resolve_struct_qualified(lex::SymId alias, lex::SymId name) const
    {
        if (!env_) return std::nullopt;

        auto it = env_->imports_by_alias.find(alias);
        if (it == env_->imports_by_alias.end())
            return std::nullopt;

        const ResolvedImport& ri = it->second;
        if (!ri.target_globals)
            return std::nullopt;

        if (auto jt = ri.target_globals->struct_by_name.find(name); jt != ri.target_globals->struct_by_name.end())
            return jt->second;

        return std::nullopt;
    }

    // Resolve StructId from a path (size 1 or 2).
    std::optional<StructId> Pass8DynTagVisitor::resolve_struct_id_from_type_path(const std::vector<lex::SymId>& segs,
                                                                                 const lex::Loc& loc) const
    {
        if (segs.size() == 1)
            return resolve_struct_simple_name(segs[0]);

        if (segs.size() == 2)
            return resolve_struct_qualified(segs[0], segs[1]);

        push_diag(Pass8Diagnostic::Code::UnsupportedTypeExprPathDepth,
                  loc,
                  "type path depth > 2 is not supported (pass8)");
        return std::nullopt;
    }

    // ============================================================
    // TypeExpr -> DynTag  (ADAPT POINT)
    // ============================================================

    DynTag Pass8DynTagVisitor::tag_from_typeexpr(const ast::TypeExpr* te, const lex::Loc& loc) const
    {
        if (is_void_typeexpr(te))
            return DynTag::void_();

        // builtin bool?
        if (typeexpr_is_builtin_bool(te))
            return DynTag::boolean();

        // Try resolve struct by type path
        std::vector<lex::SymId> segs;
        if (typeexpr_try_get_path2(te, segs))
        {
            if (auto sid = resolve_struct_id_from_type_path(segs, loc); sid.has_value())
                return DynTag::struct_obj(*sid);

            // If it looks like a type path but does not resolve, you can choose:
            //  - diagnose (helps catch missing imports)
            //  - or silently fall back to Obj.
            //
            // I recommend diagnose during bring-up:
            std::ostringstream oss;
            oss << "unknown struct name in type expression";
            push_diag(Pass8Diagnostic::Code::UnknownStructInTypeExpr, loc, oss.str());

            return DynTag::obj();
        }

        // Everything else (Box<T>, refs, builtins like i32/u128, etc.)
        return DynTag::obj();
    }

    // ============================================================
    // Struct literal tagging
    // ============================================================

    std::optional<StructId> Pass8DynTagVisitor::resolve_struct_id_from_head(ast::Expr* head, const lex::Loc& loc) const
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

            push_diag(Pass8Diagnostic::Code::UnsupportedStructLiteralHead,
                      loc,
                      "struct literal head path depth > 2 is not supported");
            return std::nullopt;
        }

        if (auto* r = dynamic_cast<ast::RefExpr*>(head))
            return resolve_struct_simple_name(r->name);

        push_diag(Pass8Diagnostic::Code::UnsupportedStructLiteralHead,
                  loc,
                  "unsupported struct literal head expression kind");
        return std::nullopt;
    }

    void Pass8DynTagVisitor::visit(ast::StructLiteralExpr& s)
    {
        // IMPORTANT: do NOT use tag(s.expr_) to decide the struct.
        // s.expr_ is the *head name*, and will be tagged Obj by PathExpr/RefExpr.
        // We must resolve the StructId directly from the head.
        for (auto* e : s.elements_) if (e) (void)tag(e);

        const auto sid = resolve_struct_id_from_head(s.expr_, s.location_);
        if (!sid)
        {
            push_diag(Pass8Diagnostic::Code::UnknownStructInStructLiteral,
                      s.location_,
                      "unknown struct name in struct literal");
            last_ = DynTag::obj();
            cache_expr(&s);
            return;
        }

        if (p45_.reserved_no_lit_structs.contains(*sid))
        {
            push_diag(Pass8Diagnostic::Code::ReservedStructLiteralForbidden,
                      s.location_,
                      "struct literal syntax is forbidden for this reserved type");
            last_ = DynTag::obj();
            cache_expr(&s);
            return;
        }

        last_ = DynTag::struct_obj(*sid);
        cache_expr(&s);
    }

    // ============================================================
    // ADAPT LAYER (YOU MUST IMPLEMENT THESE AGAINST YOUR TypeExpr AST)
    // ============================================================

    bool Pass8DynTagVisitor::typeexpr_is_builtin_bool(const ast::TypeExpr* te)
    {
        (void)te;

        // ADAPT OPTION A (common):
        if (auto* b = dynamic_cast<const ast::BuiltinTypeExpr*>(te))
            return b->kind_ == kl::rt::BuiltinTypeKind::Bool;

        // ADAPT OPTION B:
        // if (te->kind_ == ast::TypeExprKind::Builtin && te->builtin_ == BuiltinType::Bool) return true;

        return false;
    }

    bool Pass8DynTagVisitor::typeexpr_try_get_path2(const ast::TypeExpr* te, std::vector<lex::SymId>& out_segs)
    {
        (void)te;
        out_segs.clear();

        // ADAPT OPTION A (common):
        if (auto* p = dynamic_cast<const ast::PathTypeExpr*>(te))
        {
            out_segs = p->pathExpr_->path_; // vector<SymId>
            return true;
        }

        // ADAPT OPTION B:
        // if (auto* n = dynamic_cast<const ast::NamedTypeExpr*>(te))
        // {
        //     out_segs.push_back(n->name_);
        //     return true;
        // }

        // IMPORTANT:
        // - For Box::<T>, return false here (so it becomes DynTag::obj()).
        // - For &mut T, return false here (still DynTag::obj()).

        return false;
    }

    // ============================================================
    // Driver
    // ============================================================

    Pass8Result run_pass8_dyn_tag(const Translation& tr,
                                  const Pass4_5Result& p45,
                                  const Pass6Result& p6)
    {
        Pass8Result out{};

        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass8DynTagVisitor vis(p45, p6, out, unit_i);
            m->accept(vis);
        }

        return out;
    }
} // namespace sema
