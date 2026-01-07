#include "pass5.hpp"

#include <sstream>
#include "compiler_context.hpp"

namespace sema
{
    Pass5TypeResolveVisitor::Pass5TypeResolveVisitor(const CompilerContext& ctx,
                                                     const Pass4_5Result& p45,
                                                     const Pass5ReservedResult& p5r,
                                                     uint32_t unit_index,
                                                     lex::SymId box_sym,
                                                     lex::SymId str_sym,
                                                     Pass5Result& out)
        : ctx_(ctx)
        , p45_(p45)
        , p5r_(p5r)
        , unit_index_(unit_index)
        , box_sym_(box_sym)
        , str_sym_(str_sym)
        , out_(out)
    {
        // Initialize module_ early if env is already available.
        if (unit_index_ < p45_.envs.size())
            module_ = p45_.envs[unit_index_].module_id;
    }

    void Pass5TypeResolveVisitor::diag(Pass5Diagnostic::Code c,
                                       const lex::Loc& loc,
                                       std::string msg) const
    {
        out_.diagnostics.push_back(Pass5Diagnostic{
            .code = c,
            .module = module_, // NEW
            .loc = loc,
            .message = std::move(msg),
        });
    }

    static std::string strip_underscores(std::string_view s)
    {
        std::string out;
        out.reserve(s.size());
        for (char c : s)
            if (c != '_') out.push_back(c);
        return out;
    }

    static int detect_base(std::string_view s, std::string_view& digits)
    {
        if (s.size() >= 2 && s[0] == '0')
        {
            if (s[1] == 'x' || s[1] == 'X')
            {
                digits = s.substr(2);
                return 16;
            }
            if (s[1] == 'b' || s[1] == 'B')
            {
                digits = s.substr(2);
                return 2;
            }
            if (s[1] == 'o' || s[1] == 'O')
            {
                digits = s.substr(2);
                return 8;
            }
        }
        digits = s;
        return 10;
    }

    static bool parse_u64(std::string_view digits, int base, std::uint64_t& out)
    {
        auto val_of = [&](char c) -> int
        {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
            if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
            return -1;
        };

        if (digits.empty()) return false;

        std::uint64_t v = 0;
        for (char c : digits)
        {
            int d = val_of(c);
            if (d < 0 || d >= base) return false;

            if (v > (UINT64_MAX - static_cast<std::uint64_t>(d)) / static_cast<std::uint64_t>(base))
                return false;

            v = v * static_cast<std::uint64_t>(base) + static_cast<std::uint64_t>(d);
        }

        out = v;
        return true;
    }

    std::optional<std::uint64_t> Pass5TypeResolveVisitor::const_eval_u64(ast::Expr* e)
    {
        if (!e) return std::nullopt;

        if (auto* il = dynamic_cast<ast::IntLiteralExpr*>(e))
        {
            if (il->suffix_.has_value())
                return std::nullopt;

            const std::string_view raw = ctx_.numericInterner.view(il->v_);
            const std::string cleaned = strip_underscores(raw);

            std::string_view digits{};
            int base = detect_base(std::string_view{cleaned}, digits);

            std::uint64_t v = 0;
            if (!parse_u64(digits, base, v))
                return std::nullopt;

            return v;
        }

        return std::nullopt;
    }

    TypeId Pass5TypeResolveVisitor::ty_builtin(BuiltinType b)
    {
        TypeKey k{};
        k.kind = TypeKind::Builtin;
        k.builtin = b;
        return out_.types.get_or_intern(k);
    }

    TypeId Pass5TypeResolveVisitor::ty_void() { return ty_builtin(BuiltinType::Void); }

    TypeId Pass5TypeResolveVisitor::ty_struct(StructId sid)
    {
        TypeKey k{};
        k.kind = TypeKind::Struct;
        k.struct_id = sid;
        return out_.types.get_or_intern(k);
    }

    TypeId Pass5TypeResolveVisitor::ty_reserved_struct(ReservedStructId rid)
    {
        TypeKey k{};
        k.kind = TypeKind::ReservedStruct;
        k.reserved_struct = rid;
        return out_.types.get_or_intern(k);
    }

    TypeId Pass5TypeResolveVisitor::ty_type_param(lex::SymId name)
    {
        TypeKey k{};
        k.kind = TypeKind::TypeParam;
        k.type_param_name = name;
        return out_.types.get_or_intern(k);
    }

    bool Pass5TypeResolveVisitor::is_type_param(lex::SymId s) const
    {
        for (auto it = type_param_stack_.rbegin(); it != type_param_stack_.rend(); ++it)
            if (*it == s) return true;
        return false;
    }

    void Pass5TypeResolveVisitor::push_type_params(const std::vector<ast::TypeParamDecl*>& tps)
    {
        for (auto* tp : tps)
        {
            if (!tp) continue;
            type_param_stack_.push_back(tp->name_);
        }
    }

    void Pass5TypeResolveVisitor::pop_to_size(size_t sz)
    {
        while (type_param_stack_.size() > sz)
            type_param_stack_.pop_back();
    }

    BuiltinType Pass5TypeResolveVisitor::map_builtin(kl::rt::BuiltinTypeExprKind k,
                                                     const lex::Loc& loc) const
    {
        using K = kl::rt::BuiltinTypeExprKind;
        switch (k)
        {
        case K::I8: return BuiltinType::I8;
        case K::I16: return BuiltinType::I16;
        case K::I32: return BuiltinType::I32;
        case K::I64: return BuiltinType::I64;
        case K::I128: return BuiltinType::I128;

        case K::U8: return BuiltinType::U8;
        case K::U16: return BuiltinType::U16;
        case K::U32: return BuiltinType::U32;
        case K::U64: return BuiltinType::U64;
        case K::U128: return BuiltinType::U128;

        case K::F32: return BuiltinType::F32;
        case K::F64: return BuiltinType::F64;

        case K::Bool: return BuiltinType::Bool;
        case K::Char: return BuiltinType::Char;
        case K::Void: return BuiltinType::Void;

        default:
            diag(Pass5Diagnostic::Code::UnsupportedTypeForm, loc, "unknown builtin type kind");
            return BuiltinType::Void;
        }
    }

    TypeId Pass5TypeResolveVisitor::resolve(ast::TypeExpr* t)
    {
        if (!t) return ty_void();

        if (auto it = out_.type_of.find(t); it != out_.type_of.end())
            return it->second;

        t->accept(*this);

        out_.type_of.emplace(t, last_);
        return last_;
    }

    std::optional<StructId> Pass5TypeResolveVisitor::local_struct_id_of(lex::SymId name) const
    {
        if (!env_) return std::nullopt;

        auto it = env_->local_structs_all.find(name);
        if (it == env_->local_structs_all.end())
            return std::nullopt;

        return it->second;
    }

    void Pass5TypeResolveVisitor::visit(ast::Module& m)
    {
        env_ = nullptr;

        if (unit_index_ < p45_.envs.size())
        {
            env_ = &p45_.envs[unit_index_];
            module_ = env_->module_id; // NEW: refresh from env
        }
        else
        {
            module_ = kInvalidModuleId;
        }

        ast::visitor::OverallVisitor::visit(m);

        env_ = nullptr;
    }

    void Pass5TypeResolveVisitor::visit(ast::CallExpr& c)
    {
        for (auto* ta : c.typeArgs_)
            if (ta) (void)resolve(ta);

        ast::visitor::OverallVisitor::visit(c);
    }

    void Pass5TypeResolveVisitor::visit(ast::StructDecl& s)
    {
        const size_t before = type_param_stack_.size();
        push_type_params(s.typeParamsDecls_);

        for (auto* fd : s.fields_)
        {
            if (!fd) continue;
            if (fd->type_) (void)resolve(fd->type_);
        }

        ast::visitor::OverallVisitor::visit(s);

        auto sidOpt = local_struct_id_of(s.name_);
        if (sidOpt.has_value())
        {
            StructLayout lay{};
            lay.fields_in_order.reserve(s.fields_.size());
            lay.field_types_in_order.reserve(s.fields_.size());

            uint32_t idx = 0;
            for (auto* fd : s.fields_)
            {
                if (!fd) continue;

                const lex::SymId fname = fd->name_;

                auto [it, inserted] = lay.name_to_index.emplace(fname, idx);
                if (!inserted)
                {
                    diag(Pass5Diagnostic::Code::UnsupportedTypeForm,
                         fd->location_,
                         "duplicate field name in struct");
                    continue;
                }

                TypeId fty = fd->type_ ? resolve(fd->type_) : ty_void();

                lay.fields_in_order.push_back(fname);
                lay.field_types_in_order.push_back(fty);
                lay.name_to_type.emplace(fname, fty);

                ++idx;
            }

            out_.struct_layout[*sidOpt] = std::move(lay);
        }

        pop_to_size(before);
    }

    void Pass5TypeResolveVisitor::visit(ast::FnDecl& f)
    {
        const size_t before = type_param_stack_.size();
        push_type_params(f.typeParamsDecls_);

        if (f.ret_) (void)resolve(f.ret_);
        for (auto* p : f.params_)
            if (p && p->type_) (void)resolve(p->type_);

        ast::visitor::OverallVisitor::visit(f);

        pop_to_size(before);
    }

    void Pass5TypeResolveVisitor::visit(ast::ParamDecl& p)
    {
        if (p.type_) (void)resolve(p.type_);
        ast::visitor::OverallVisitor::visit(p);
    }

    void Pass5TypeResolveVisitor::visit(ast::VarStmt& v)
    {
        if (v.type_) (void)resolve(v.type_);
        ast::visitor::OverallVisitor::visit(v);
    }

    void Pass5TypeResolveVisitor::visit(ast::LoadFnDecl& lf)
    {
        if (lf.ret_) (void)resolve(lf.ret_);
        for (auto* p : lf.params_)
            if (p && p->type_) (void)resolve(p->type_);

        ast::visitor::OverallVisitor::visit(lf);
    }

    void Pass5TypeResolveVisitor::visit(ast::BuiltinTypeExpr& t)
    {
        last_ = ty_builtin(map_builtin(t.kind_, t.location_));
    }

    void Pass5TypeResolveVisitor::visit(ast::RefTypeExpr& t)
    {
        TypeId inner = resolve(t.pointee_);

        TypeKey k{};
        k.kind = TypeKind::Ref;
        k.inner = inner;
        k.ref_mut = (t.mut_ == ast::Mutability::Mut);

        last_ = out_.types.get_or_intern(k);
    }

    void Pass5TypeResolveVisitor::visit(ast::ArrayTypeExpr& t)
    {
        TypeId elem = resolve(t.type_);

        // ADAPT: your field name
        ast::Expr* len_expr = t.sizeExpr_; // <-- CHANGE if needed

        auto lenOpt = const_eval_u64(len_expr);
        if (!lenOpt.has_value())
        {
            diag(Pass5Diagnostic::Code::IllegalFixedArrayLength,
                 t.location_,
                 "fixed array length must be a compile-time integer literal (Pass5 const-eval MVP)");
            last_ = ty_void();
            return;
        }

        TypeKey k{};
        k.kind = TypeKind::ArrayFixed;
        k.elem = elem;
        k.array_len = *lenOpt;

        last_ = out_.types.get_or_intern(k);
    }

    void Pass5TypeResolveVisitor::visit(ast::PathTypeExpr& t)
    {
        if (!env_)
        {
            diag(Pass5Diagnostic::Code::UnsupportedTypeForm,
                 t.location_,
                 "internal error: missing module env");
            last_ = ty_void();
            return;
        }

        if (!t.pathExpr_)
        {
            diag(Pass5Diagnostic::Code::UnknownTypeName, t.location_, "missing type path");
            last_ = ty_void();
            return;
        }

        const auto& segs = t.pathExpr_->path_;
        if (segs.empty())
        {
            diag(Pass5Diagnostic::Code::UnknownTypeName, t.location_, "empty type path");
            last_ = ty_void();
            return;
        }

        if (!t.typeArgs_.empty() && !(segs.size() == 1 && segs[0] == box_sym_))
        {
            diag(Pass5Diagnostic::Code::UnsupportedTypeForm,
                 t.location_,
                 "type arguments are only supported for Box<T>");
            last_ = ty_void();
            return;
        }

        if (segs.size() == 1)
        {
            const lex::SymId name = segs[0];

            if (name == box_sym_)
            {
                if (t.typeArgs_.size() != 1 || !t.typeArgs_[0])
                {
                    diag(Pass5Diagnostic::Code::IllegalBoxArity,
                         t.location_,
                         "Box<T> requires exactly one type argument");
                    last_ = ty_void();
                    return;
                }

                TypeId inner = resolve(t.typeArgs_[0]);

                TypeKey k{};
                k.kind = TypeKind::Box;
                k.inner = inner;

                last_ = out_.types.get_or_intern(k);
                return;
            }

            if (is_type_param(name))
            {
                last_ = ty_type_param(name);
                return;
            }

            if (auto it = p5r_.reserved_struct_by_name.find(name);
                it != p5r_.reserved_struct_by_name.end())
            {
                last_ = ty_reserved_struct(it->second);
                return;
            }

            if (auto it = env_->visible_structs.find(name);
                it != env_->visible_structs.end())
            {
                last_ = ty_struct(it->second);
                return;
            }

            std::ostringstream oss;
            oss << "unknown type name: " << static_cast<uint32_t>(name);
            diag(Pass5Diagnostic::Code::UnknownTypeName, t.location_, oss.str());
            last_ = ty_void();
            return;
        }

        if (segs.size() == 2)
        {
            const lex::SymId alias = segs[0];
            const lex::SymId name = segs[1];

            auto it_alias = env_->imports_by_alias.find(alias);
            if (it_alias == env_->imports_by_alias.end())
            {
                std::ostringstream oss;
                oss << "unknown import alias in type path: " << static_cast<uint32_t>(alias);
                diag(Pass5Diagnostic::Code::UnknownImportAlias, t.location_, oss.str());
                last_ = ty_void();
                return;
            }

            const ResolvedImport& ri = it_alias->second;
            if (!ri.target_globals)
            {
                diag(Pass5Diagnostic::Code::UnsupportedTypeForm,
                     t.location_,
                     "internal error: resolved import missing target module globals");
                last_ = ty_void();
                return;
            }

            const ModuleGlobals& imported = *ri.target_globals;

            auto it_ty = imported.struct_by_name.find(name);
            if (it_ty == imported.struct_by_name.end())
            {
                std::ostringstream oss;
                oss << "unknown imported public type: "
                    << static_cast<uint32_t>(alias) << "::" << static_cast<uint32_t>(name);
                diag(Pass5Diagnostic::Code::UnknownTypeName, t.location_, oss.str());
                last_ = ty_void();
                return;
            }

            last_ = ty_struct(it_ty->second);
            return;
        }

        diag(Pass5Diagnostic::Code::UnsupportedTypePathDepth,
             t.location_,
             "type paths deeper than alias::Name are not supported");
        last_ = ty_void();
    }

    // ------------------------------------------------------------
    // driver
    // ------------------------------------------------------------

    Pass5Result run_pass5_type_resolve(const Translation& tr,
                                       const CompilerContext& ctx,
                                       const Pass4_5Result& p45,
                                       const Pass5ReservedResult& p5r,
                                       lex::SymId box_sym,
                                       lex::SymId str_sym)
    {
        Pass5Result out{};

        out.types = p5r.types;
        out.type_of.insert(p5r.type_of.begin(), p5r.type_of.end());

        const uint32_t n_units = static_cast<uint32_t>(tr.units.size());

        for (uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass5TypeResolveVisitor vis(ctx, p45, p5r, unit_i, box_sym, str_sym, out);
            m->accept(vis);
        }

        return out;
    }
} // namespace sema
