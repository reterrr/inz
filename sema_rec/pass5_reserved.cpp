#include "pass5_reserved.hpp"

#include <string>
#include <utility>
#include <vector>

#include "expr/path_expr.hpp"

namespace sema
{
    static inline void log_module_path_first(LogSequence& logs,
                                             const std::vector<lex::SymId>& segs,
                                             const lex::Loc& loc)
    {
        logs.emplace_back(LogPath{SymKind::Ident, segs, loc});
    }

    void Pass5ReservedVisitor::log_error_prefix(const lex::Loc& loc, std::string msg) const
    {
        log_module_path_first(out_.errors, cur_module_path_, loc);
        out_.errors.emplace_back(std::move(msg));
    }

    void Pass5ReservedVisitor::log_error_with_ident(const lex::Loc& loc,
                                                    std::string msg,
                                                    lex::SymId id) const
    {
        log_module_path_first(out_.errors, cur_module_path_, loc);
        out_.errors.emplace_back(std::move(msg));
        out_.errors.emplace_back(Log{SymKind::Ident, id, loc});
    }

    void Pass5ReservedVisitor::log_error_with_path(const lex::Loc& loc,
                                                   std::string msg,
                                                   const std::vector<lex::SymId>& path) const
    {
        log_module_path_first(out_.errors, cur_module_path_, loc);
        out_.errors.emplace_back(std::move(msg));
        out_.errors.emplace_back(LogPath{SymKind::Ident, path, loc});
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
                                                  const lex::Loc& loc)
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
            log_error_prefix(loc, "pass5.reserved: UnsupportedTypeForm: unknown builtin type kind");
            return BuiltinType::Void;
        }
    }


    void Pass5ReservedVisitor::push_type_params(const std::vector<ast::TypeParamDecl*>& tps)
    {
        for (auto* tp : tps)
        {
            if (!tp) continue;

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


        t->accept(*this);

        out_.type_of.emplace(t, last_);
        return last_;
    }


    void Pass5ReservedVisitor::visit(ast::Module& m)
    {
        cur_module_loc_ = m.location_;
        cur_module_path_.clear();
        if (m.pathExpr_)
            cur_module_path_ = m.pathExpr_->path_;


        for (auto* d : m.decls)
        {
            if (!d) continue;


            if (d->nodeType_ == NodeKind::Decl_Struct)
                d->accept(*this);
        }


        ast::visitor::OverallVisitor::visit(m);
    }

    void Pass5ReservedVisitor::visit(ast::StructDecl& s)
    {
        if (!out_.reserved_struct_by_name.contains(s.name_))
        {
            ReservedStructId id{static_cast<uint32_t>(out_.reserved_struct_decls.size())};
            out_.reserved_struct_by_name.emplace(s.name_, id);
            out_.reserved_struct_decls.push_back(&s);
        }


        const size_t before = type_param_stack_.size();


        push_type_params(s.typeParamsDecls_);

        ast::visitor::OverallVisitor::visit(s);

        pop_to_size(before);
    }

    void Pass5ReservedVisitor::visit(ast::FnDecl& f)
    {
        const size_t before = type_param_stack_.size();


        push_type_params(f.typeParamsDecls_);


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
        (void)resolve(t.type_);


        log_error_prefix(t.location_,
                         "pass5.reserved: IllegalFixedArrayLength: fixed array types are not supported in reserved signatures (no const-eval)");
        last_ = ty_void();
    }

    void Pass5ReservedVisitor::visit(ast::PathTypeExpr& t)
    {
        if (!t.pathExpr_)
        {
            log_error_prefix(t.location_, "pass5.reserved: UnknownTypeName: missing type path");
            last_ = ty_void();
            return;
        }

        const auto& segs = t.pathExpr_->path_;


        if (segs.size() != 1)
        {
            log_error_with_path(t.location_,
                                "pass5.reserved: UnsupportedTypePathDepth: reserved type paths must be single-segment: ",
                                segs);
            last_ = ty_void();
            return;
        }

        const lex::SymId name = segs[0];


        if (name == str_sym_)
        {
            last_ = ty_builtin(BuiltinType::Str);
            return;
        }


        if (name == box_sym_)
        {
            const auto& args = type_args_of(t);
            if (args.size() != 1 || !args[0])
            {
                log_error_with_ident(t.location_,
                                     "pass5.reserved: IllegalBoxArity: Box<T> requires exactly one type argument (for type name: ",
                                     name);
                out_.errors.emplace_back(std::string(")"));
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


        if (is_type_param(name))
        {
            last_ = ty_type_param(name);
            return;
        }


        const auto sid = resolve_reserved_struct(name);
        if (!sid.has_value())
        {
            log_error_with_ident(t.location_,
                                 "pass5.reserved: UnknownTypeName: unknown reserved type name: ",
                                 name);
            last_ = ty_void();
            return;
        }

        TypeKey k{};
        k.kind = TypeKind::ReservedStruct;
        k.reserved_struct = *sid;

        last_ = out_.types.get_or_intern(k);
    }


    Pass5ReservedResult run_pass5_reserved_type_resolve(const Translation& reserved_tr,
                                                        const Pass3_5Result& p35,
                                                        lex::SymId box_sym,
                                                        lex::SymId str_sym)
    {
        Pass5ReservedResult out{};

        for (const auto& unit : reserved_tr.units)
        {
            ast::Module* m = unit.module_;
            if (!m)
            {
                out.errors.emplace_back(
                    std::string("pass5.reserved: InternalError: reserved unit has no module AST node"));
                continue;
            }

            Pass5ReservedVisitor vis(p35, box_sym, str_sym, out);
            m->accept(vis);
        }

        return out;
    }
}
