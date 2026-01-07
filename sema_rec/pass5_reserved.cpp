// sema/pass5_reserved.cpp
#include "pass5_reserved.hpp"

#include <sstream>

namespace sema
{
    // ------------------------------------------------------------
    // diagnostics + intern
    // ------------------------------------------------------------

    void Pass5ReservedVisitor::diag(Pass5ReservedDiagnostic::Code c,
                                    const lex::Loc& loc,
                                    std::string msg) const
    {
        out_.diagnostics.push_back(Pass5ReservedDiagnostic{
            .code = c,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    TypeId Pass5ReservedVisitor::ty_builtin(BuiltinType b) const
    {
        TypeKey k{};
        k.kind = TypeKind::Builtin;
        k.builtin = b;
        return out_.types.get_or_intern(k);
    }

    TypeId Pass5ReservedVisitor::ty_void() const
    {
        return ty_builtin(BuiltinType::Void);
    }

    TypeId Pass5ReservedVisitor::ty_type_param(lex::SymId name) const
    {
        TypeKey k{};
        k.kind = TypeKind::TypeParam;
        k.type_param_name = name;
        return out_.types.get_or_intern(k);
    }

    BuiltinType Pass5ReservedVisitor::map_builtin(kl::rt::BuiltinTypeExprKind k,
                                                  const lex::Loc& loc) const
    {
        using K = kl::rt::BuiltinTypeExprKind;
        switch (k)
        {
            case K::I8:   return BuiltinType::I8;
            case K::I16:  return BuiltinType::I16;
            case K::I32:  return BuiltinType::I32;
            case K::I64:  return BuiltinType::I64;
            case K::I128: return BuiltinType::I128;

            case K::U8:   return BuiltinType::U8;
            case K::U16:  return BuiltinType::U16;
            case K::U32:  return BuiltinType::U32;
            case K::U64:  return BuiltinType::U64;
            case K::U128: return BuiltinType::U128;

            case K::F32:  return BuiltinType::F32;
            case K::F64:  return BuiltinType::F64;

            case K::Bool: return BuiltinType::Bool;
            case K::Char: return BuiltinType::Char;
            case K::Void: return BuiltinType::Void;

            default:
                diag(Pass5ReservedDiagnostic::Code::UnsupportedTypeForm,
                     loc,
                     "unknown builtin type kind");
                return BuiltinType::Void;
        }
    }

    // ------------------------------------------------------------
    // type param scope
    // ------------------------------------------------------------

    void Pass5ReservedVisitor::push_type_params(const std::vector<ast::TypeParamDecl*>& tps)
    {
        for (auto* tp : tps)
        {
            if (!tp) continue;
            // ADAPT if your TypeParamDecl stores name differently
            type_param_stack_.push_back(tp->name_);
        }
    }

    void Pass5ReservedVisitor::pop_to_size(size_t sz)
    {
        while (type_param_stack_.size() > sz)
            type_param_stack_.pop_back();
    }

    bool Pass5ReservedVisitor::is_type_param(lex::SymId s) const
    {
        for (auto it = type_param_stack_.rbegin(); it != type_param_stack_.rend(); ++it)
            if (*it == s) return true;
        return false;
    }

    // ------------------------------------------------------------
    // helpers
    // ------------------------------------------------------------

    bool Pass5ReservedVisitor::is_box(const ast::PathTypeExpr& t) const
    {
        if (!t.pathExpr_) return false;
        const auto& segs = t.pathExpr_->path_;
        return (segs.size() == 1 && segs[0] == box_sym_);
    }

    bool Pass5ReservedVisitor::is_str_single_segment(const ast::PathTypeExpr& t) const
    {
        if (!t.pathExpr_) return false;
        const auto& segs = t.pathExpr_->path_;
        return (segs.size() == 1 && segs[0] == str_sym_);
    }

    std::optional<ReservedStructId> Pass5ReservedVisitor::resolve_reserved_struct(lex::SymId name) const
    {
        if (auto it = out_.reserved_struct_by_name.find(name); it != out_.reserved_struct_by_name.end())
            return it->second;
        return std::nullopt;
    }

    TypeId Pass5ReservedVisitor::resolve(ast::TypeExpr* t)
    {
        if (!t) return ty_void();

        if (auto it = out_.type_of.find(t); it != out_.type_of.end())
            return it->second;

        // accept-based dispatch (no casts)
        t->accept(*this);

        out_.type_of.emplace(t, last_);
        return last_;
    }

    // ------------------------------------------------------------
    // visitor overrides
    // ------------------------------------------------------------

    void Pass5ReservedVisitor::visit(ast::Module& m)
    {
        // Phase 1: collect ALL struct ids first (do NOT resolve fn types yet)
        for (auto* d : m.decls)
        {
            if (!d) continue;

            // Prefer NodeKind check; ADAPT enum constant to your codebase.
            if (d->nodeType_ == NodeKind::Decl_Struct)
                d->accept(*this); // visit(StructDecl&)
        }

        // Phase 2: traverse module, resolving types
        ast::visitor::OverallVisitor::visit(m);
    }

    void Pass5ReservedVisitor::visit(ast::StructDecl& s)
    {
        // reserve struct id (always)
        if (!out_.reserved_struct_by_name.contains(s.name_))
        {
            ReservedStructId id{ static_cast<uint32_t>(out_.reserved_struct_decls.size()) };
            out_.reserved_struct_by_name.emplace(s.name_, id);
            out_.reserved_struct_decls.push_back(&s);
        }

        // push struct type params if present (Box<T> declares T here)
        const size_t before = type_param_stack_.size();

        // ADAPT if your StructDecl stores type params differently.
        // If it has no type params, just remove this line.
        push_type_params(s.typeParamsDecls_);

        ast::visitor::OverallVisitor::visit(s);

        pop_to_size(before);
    }

    void Pass5ReservedVisitor::visit(ast::FnDecl& f)
    {
        const size_t before = type_param_stack_.size();

        // ADAPT if your FnDecl stores type params differently.
        // If it has no type params vector, remove this line.
        push_type_params(f.typeParamsDecls_);

        // resolve signature types
        if (f.ret_) (void)resolve(f.ret_);
        for (auto* p : f.params_)
            if (p && p->type_) (void)resolve(p->type_);

        ast::visitor::OverallVisitor::visit(f);

        pop_to_size(before);
    }

    void Pass5ReservedVisitor::visit(ast::ParamDecl& p)
    {
        if (p.type_) (void)resolve(p.type_);
        ast::visitor::OverallVisitor::visit(p);
    }

    // ---- type expr nodes ----

    void Pass5ReservedVisitor::visit(ast::BuiltinTypeExpr& t)
    {
        last_ = ty_builtin(map_builtin(t.kind_, t.location_));
    }

    void Pass5ReservedVisitor::visit(ast::RefTypeExpr& t)
    {
        TypeId inner = resolve(t.pointee_);

        TypeKey k{};
        k.kind = TypeKind::Ref;
        k.inner = inner;
        k.ref_mut = (t.mut_ == ast::Mutability::Mut);

        last_ = out_.types.get_or_intern(k);
    }

    void Pass5ReservedVisitor::visit(ast::ArrayTypeExpr& t)
    {
        // Without SymId->text (or parsed integer stored in AST),
        // you cannot compute N from sizeExpr_.
        (void)resolve(t.type_);

        diag(Pass5ReservedDiagnostic::Code::IllegalFixedArrayLength,
             t.location_,
             "fixed array types are not supported in reserved signatures (no const-eval)");

        last_ = ty_void();
    }

    void Pass5ReservedVisitor::visit(ast::PathTypeExpr& t)
    {
        if (!t.pathExpr_)
        {
            diag(Pass5ReservedDiagnostic::Code::UnknownTypeName,
                 t.location_,
                 "missing type path");
            last_ = ty_void();
            return;
        }

        const auto& segs = t.pathExpr_->path_;

        // reserved world: only single-segment type paths
        if (segs.size() != 1)
        {
            diag(Pass5ReservedDiagnostic::Code::UnsupportedTypePathDepth,
                 t.location_,
                 "reserved type paths must be single-segment");
            last_ = ty_void();
            return;
        }

        const lex::SymId name = segs[0];

        // Str (builtin-like)
        if (name == str_sym_)
        {
            last_ = ty_builtin(BuiltinType::Str);
            return;
        }

        // Box<T>
        if (name == box_sym_)
        {
            const auto& args = type_args_of(t);
            if (args.size() != 1 || !args[0])
            {
                diag(Pass5ReservedDiagnostic::Code::IllegalBoxArity,
                     t.location_,
                     "Box<T> requires exactly one type argument");
                last_ = ty_void();
                return;
            }

            TypeId inner = resolve(args[0]);

            TypeKey k{};
            k.kind = TypeKind::Box;
            k.inner = inner;

            last_ = out_.types.get_or_intern(k);
            return;
        }

        // TypeParam (T)
        if (is_type_param(name))
        {
            last_ = ty_type_param(name);
            return;
        }

        // Reserved struct
        const auto sid = resolve_reserved_struct(name);
        if (!sid.has_value())
        {
            std::ostringstream oss;
            oss << "unknown reserved type name: " << name;
            diag(Pass5ReservedDiagnostic::Code::UnknownTypeName,
                 t.location_,
                 oss.str());
            last_ = ty_void();
            return;
        }

        TypeKey k{};
        k.kind = TypeKind::ReservedStruct;
        k.reserved_struct = *sid;

        last_ = out_.types.get_or_intern(k);
    }

    // ------------------------------------------------------------
    // driver
    // ------------------------------------------------------------

    Pass5ReservedResult run_pass5_reserved_type_resolve(const Translation& reserved_tr,
                                                        const Pass3_5Result& p35,
                                                        lex::SymId box_sym,
                                                        lex::SymId str_sym)
    {
        Pass5ReservedResult out{};

        for (const auto& unit : reserved_tr.units)
        {
            ast::Module* m = unit.module_;
            if (!m) continue;

            Pass5ReservedVisitor vis(p35, box_sym, str_sym, out);
            m->accept(vis);
        }

        return out;
    }

} // namespace sema
