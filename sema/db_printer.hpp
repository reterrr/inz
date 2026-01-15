//
// Created by yhwach on 12/30/25.
//

#ifndef INZ_DB_PRINTER_HPP
#define INZ_DB_PRINTER_HPP
// db_printer.hpp
// Header-only debug printer for: ModulePassDB, ScopePass2DB, Pass3DB (+ key nested types shown).
// Usage:
//   #include "db_printer.hpp"
//   kl::db::print_db(std::cout, compilerCtx, moduleDb);
//   kl::db::print_db(std::cout, compilerCtx, scope2Db);
//   kl::db::print_db(std::cout, compilerCtx, pass3Db);


#include <ostream>
#include <string>
#include <string_view>
#include <optional>
#include <variant>
#include <type_traits>

#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>

#include "decl_bind_pass.hpp"
#include "module_import_pass.hpp"

// --- Forward decls (adjust namespaces if needed) ---
namespace lex { struct Loc; using SymId = uint32_t; }
namespace hir { using DeclId = uint32_t; using TypeId = uint32_t; using ExprId = uint32_t; using BlockId = uint32_t; using FieldDeclId = uint32_t; using TypeParamId = uint32_t; using MethodId = uint32_t; }
namespace ast { enum class Mutability : int; }

// Your types (must be included before this header OR forward-declared similarly):
// struct CompilerContext;
// struct ModulePassDB; struct ScopePass2DB; struct Pass3DB;
// ... plus all nested records/enums shown in your snippet.

namespace sema {

// ---------------------------
// Small formatting utilities
// ---------------------------
inline bool is_invalid_u32(uint32_t v) { return v == 0xFFFFFFFFu; }

template <class T>
concept StreamInsertable = requires(std::ostream& os, const T& v) {
    { os << v } -> std::same_as<std::ostream&>;
};

template <class Ctx>
concept HasIdentView = requires(const Ctx& c, lex::SymId s) {
    { c.identInterner.view(s) } -> std::convertible_to<std::string_view>;
};

template <class Pool, class Ref>
concept PoolHasView = requires(const Pool& p, Ref r) {
    p.view(r);
};

template <class T>
inline std::string_view sym_name(const T& compiler, lex::SymId s) {
    if constexpr (HasIdentView<T>) return compiler.identInterner.view(s);
    (void)compiler; (void)s;
    return "<sym>";
}

inline void indent(std::ostream& os, int n) {
    for (int i = 0; i < n; ++i) os << "  ";
}

template <class T>
inline void print_loc(std::ostream& os, const T& /*compiler*/, const lex::Loc& loc) {
    if constexpr (StreamInsertable<lex::Loc>) {
        os << loc;
    } else {
        (void)loc;
        os << "<loc>";
    }
}

// ---------------------------
// Enum stringifiers (extend as needed)
// ---------------------------
inline const char* to_cstr(ModulePassErrKind k) {
    switch (k) {
        case ModulePassErrKind::DuplicateModulePath:      return "DuplicateModulePath";
        case ModulePassErrKind::DuplicateFile:            return "DuplicateFile";
        case ModulePassErrKind::DuplicateImportBinding:   return "DuplicateImportBinding";
        case ModulePassErrKind::UnknownImportTarget:      return "UnknownImportTarget";
        case ModulePassErrKind::SelfImport:               return "SelfImport";
    }
    return "<ModulePassErrKind?>";
}

inline const char* to_cstr(Scope2ErrKind k) {
    switch (k) {
        case Scope2ErrKind::DuplicateTypeName:              return "DuplicateTypeName";
        case Scope2ErrKind::DuplicateValueName:             return "DuplicateValueName";
        case Scope2ErrKind::DeclNameConflictsWithImport:    return "DeclNameConflictsWithImport";
        case Scope2ErrKind::DuplicateTypeParamName:         return "DuplicateTypeParamName";
        case Scope2ErrKind::DuplicateStructFieldName:       return "DuplicateStructFieldName";
        case Scope2ErrKind::DuplicateTraitMethodName:       return "DuplicateTraitMethodName";
        case Scope2ErrKind::DuplicateImplMethodName:        return "DuplicateImplMethodName";
        case Scope2ErrKind::TypeAliasMissingName:           return "TypeAliasMissingName";
        case Scope2ErrKind::InternalMissingRequiredField:   return "InternalMissingRequiredField";
    }
    return "<Scope2ErrKind?>";
}

inline const char* to_cstr(Resolve3ErrKind k) {
    switch (k) {
        case Resolve3ErrKind::UnknownImportTargetModule: return "UnknownImportTargetModule";
        case Resolve3ErrKind::UnknownModuleInPath:       return "UnknownModuleInPath";
        case Resolve3ErrKind::UnknownTypeName:           return "UnknownTypeName";
        case Resolve3ErrKind::WrongKindUsedAsType:       return "WrongKindUsedAsType";
        case Resolve3ErrKind::WrongKindUsedAsTrait:      return "WrongKindUsedAsTrait";
        case Resolve3ErrKind::TraitNotFound:             return "TraitNotFound";
        case Resolve3ErrKind::InvalidImplSelfType:       return "InvalidImplSelfType";
        case Resolve3ErrKind::DuplicateImpl:             return "DuplicateImpl";
        case Resolve3ErrKind::AliasCycle:                return "AliasCycle";
    }
    return "<Resolve3ErrKind?>";
}

inline const char* to_cstr(SymKind k) {
    switch (k) {
        case SymKind::Fn:        return "Fn";
        case SymKind::LoadFn:    return "LoadFn";
        case SymKind::Struct:    return "Struct";
        case SymKind::Trait:     return "Trait";
        case SymKind::TypeAlias: return "TypeAlias";
    }
    return "<SymKind?>";
}

inline const char* to_cstr(ReceiverKind k) {
    switch (k) {
        case ReceiverKind::None:   return "None";
        case ReceiverKind::Value:  return "Value";
        case ReceiverKind::RefImm: return "RefImm";
        case ReceiverKind::RefMut: return "RefMut";
    }
    return "<ReceiverKind?>";
}

inline const char* to_cstr(BinderOwnerKind k) {
    switch (k) {
        case BinderOwnerKind::Fn:          return "Fn";
        case BinderOwnerKind::Struct:      return "Struct";
        case BinderOwnerKind::Trait:       return "Trait";
        case BinderOwnerKind::Impl:        return "Impl";
        case BinderOwnerKind::TraitMethod: return "TraitMethod";
        case BinderOwnerKind::ImplMethod:  return "ImplMethod";
        case BinderOwnerKind::Intrinsic:   return "Intrinsic";
    }
    return "<BinderOwnerKind?>";
}

inline const char* to_cstr(MethodKind k) {
    switch (k) {
        case MethodKind::TraitMethod: return "TraitMethod";
        case MethodKind::ImplMethod:  return "ImplMethod";
    }
    return "<MethodKind?>";
}

inline const char* to_cstr(SemaTypeKind k) {
    switch (k) {
        case SemaTypeKind::Builtin:   return "Builtin";
        case SemaTypeKind::TypeParam: return "TypeParam";
        case SemaTypeKind::Struct:    return "Struct";
        case SemaTypeKind::Ref:       return "Ref";
        case SemaTypeKind::Array:     return "Array";
        case SemaTypeKind::Trait:     return "Trait";
    }
    return "<SemaTypeKind?>";
}

// ---------------------------
// Printer config
// ---------------------------
struct PrintCfg {
    uint32_t max_items = 200;          // cap long vectors/maps
    bool print_densemap_entries = true;
    bool print_typeinterner_nodes = true;
    bool print_module_tree = false;    // can be very large/noisy
};

// ---------------------------
// Core printer object (single entry for all DBs)
// ---------------------------
template <class CompilerCtx>
struct Printer {
    std::ostream& os;
    const CompilerCtx& cc;
    PrintCfg cfg;
    int ind = 0;

    void nl() { os << '\n'; }
    void line_prefix() { indent(os, ind); }

    template <class T>
    void kv(std::string_view key, const T& v) {
        line_prefix();
        os << key << ": " << v;
        nl();
    }

    void kv_sym(std::string_view key, lex::SymId s) {
        line_prefix();
        os << key << ": " << sym_name(cc, s) << " (#" << static_cast<uint32_t>(s) << ")";
        nl();
    }

    template <class IdT>
    void kv_id(std::string_view key, IdT id) {
        line_prefix();
        os << key << ": ";
        const uint32_t u = static_cast<uint32_t>(id);
        if (is_invalid_u32(u)) os << "<invalid>";
        else os << u;
        nl();
    }

    template <class T>
    void kv_opt_u32(std::string_view key, const std::optional<T>& v) {
        line_prefix();
        os << key << ": ";
        if (!v.has_value()) os << "<none>";
        else {
            const uint32_t u = static_cast<uint32_t>(*v);
            if (is_invalid_u32(u)) os << "<invalid>";
            else os << u;
        }
        nl();
    }

    // -------- Path printing (best-effort; requires PathPool::view(PathRef) to work) --------
    template <class Pool, class Ref>
    void print_path(std::string_view key, const Pool& pool, Ref ref) {
        line_prefix();
        os << key << ": ";
        if constexpr (PoolHasView<Pool, Ref>) {
            auto segs = pool.view(ref); // expected iterable of lex::SymId
            bool first = true;
            for (auto s : segs) {
                if (!first) os << "::";
                first = false;
                os << sym_name(cc, static_cast<lex::SymId>(s));
            }
        } else {
            if constexpr (StreamInsertable<Ref>) os << ref;
            else os << "<path>";
        }
        nl();
    }

    // -------- Common container printing helpers --------
    template <class VecT, class Fn>
    void for_each_limited(const VecT& v, Fn&& fn) {
        const uint32_t n = static_cast<uint32_t>(v.size());
        const uint32_t limit = (n > cfg.max_items) ? cfg.max_items : n;
        for (uint32_t i = 0; i < limit; ++i) fn(i, v[i]);
        if (n > limit) {
            line_prefix();
            os << "... (" << (n - limit) << " more)";
            nl();
        }
    }

    template <class MapT, class Fn>
    void for_each_densemap_limited(const MapT& m, Fn&& fn) {
        if (!cfg.print_densemap_entries) {
            line_prefix();
            os << "<entries suppressed> size=" << m.size();
            nl();
            return;
        }
        uint32_t i = 0;
        for (const auto& it : m) {
            if (i++ >= cfg.max_items) break;
            fn(it);
        }
        if (m.size() > cfg.max_items) {
            line_prefix();
            os << "... (" << (m.size() - cfg.max_items) << " more)";
            nl();
        }
    }

    // ---------------------------
    // Low-level record printers
    // ---------------------------
    void print(const ImportRec& r, const ModulePassDB& owner) {
        line_prefix(); os << "ImportRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("target", r.target);
        print_path("path", owner.pool, r.path);
        if (r.alias.has_value()) kv_sym("alias", *r.alias); else kv("alias", "<none>");
        kv_sym("bound_name", r.bound_name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        ind--;
    }

    void print(const ModuleRec& r, const ModulePassDB& owner) {
        line_prefix(); os << "ModuleRec"; nl();
        ind++;
        kv_id("file", r.file);
        print_path("package_path", owner.pool, r.package_path);
        kv_sym("leaf_name", r.leaf_name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("import_begin", r.import_begin);
        kv("import_count", r.import_count);
        kv("edge_begin", r.edge_begin);
        kv("edge_count", r.edge_count);
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);
        kv("valid", static_cast<uint32_t>(r.valid));
        ind--;
    }

    void print(const ModulePassError& e) {
        line_prefix(); os << "ModulePassError"; nl();
        ind++;
        kv("kind", to_cstr(e.kind));
        kv_id("file", e.file);
        kv_id("owner", e.owner);
        kv_id("existing", e.existing);
        kv_id("duplicate", e.duplicate);
        kv_id("import_id", e.import_id);
        line_prefix(); os << "loc: "; print_loc(os, cc, e.loc); nl();
        ind--;
    }

    void print(const Scope2Error& e) {
        line_prefix(); os << "Scope2Error"; nl();
        ind++;
        kv("kind", to_cstr(e.kind));
        kv_id("file", e.file);
        kv_id("module", e.module);
        kv_sym("name", e.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, e.loc); nl();
        ind--;
    }

    void print(const Resolve3Error& e) {
        line_prefix(); os << "Resolve3Error"; nl();
        ind++;
        kv("kind", to_cstr(e.kind));
        kv_id("file", e.file);
        kv_id("module", e.module);
        kv_sym("name", e.name);
        kv_id("other_module", e.other_module);
        line_prefix(); os << "loc: "; print_loc(os, cc, e.loc); nl();
        ind--;
    }

    void print(const Symbol& s) {
        line_prefix(); os << "Symbol"; nl();
        ind++;
        kv("kind", to_cstr(s.kind));
        kv("id", s.id);
        kv("arity", static_cast<uint32_t>(s.arity));
        kv("exported", static_cast<uint32_t>(s.exported));
        kv("intrinsic", static_cast<uint32_t>(s.intrinsic));
        line_prefix(); os << "loc: "; print_loc(os, cc, s.loc); nl();
        ind--;
    }

    void print(const ImportBinding& b) {
        line_prefix(); os << "ImportBinding"; nl();
        ind++;
        kv_id("pass1_import", b.pass1_import);
        kv_id("target", b.target);
        line_prefix(); os << "loc: "; print_loc(os, cc, b.loc); nl();
        ind--;
    }

    void print(const ModuleScope& s) {
        line_prefix(); os << "ModuleScope"; nl();
        ind++;

        line_prefix(); os << "imports (bound_name -> ImportBinding): size=" << s.imports.size(); nl();
        ind++;
        for_each_densemap_limited(s.imports, [&](const auto& it) {
            line_prefix();
            os << sym_name(cc, it.first) << " ->"; nl();
            ind++;
            print(it.second);
            ind--;
        });
        ind--;

        line_prefix(); os << "types (name -> Symbol): size=" << s.types.size(); nl();
        ind++;
        for_each_densemap_limited(s.types, [&](const auto& it) {
            line_prefix();
            os << sym_name(cc, it.first) << " ->"; nl();
            ind++;
            print(it.second);
            ind--;
        });
        ind--;

        line_prefix(); os << "values (name -> Symbol): size=" << s.values.size(); nl();
        ind++;
        for_each_densemap_limited(s.values, [&](const auto& it) {
            line_prefix();
            os << sym_name(cc, it.first) << " ->"; nl();
            ind++;
            print(it.second);
            ind--;
        });
        ind--;

        line_prefix(); os << "impls: count=" << s.impls.size(); nl();
        ind++;
        for_each_limited(s.impls, [&](uint32_t i, auto implId) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(implId) << std::endl;
        });
        ind--;

        ind--;
    }

    void print(const GenericBinder& b) {
        line_prefix(); os << "GenericBinder"; nl();
        ind++;
        kv("owner_kind", to_cstr(b.owner_kind));
        kv("owner_id", b.owner_id);
        line_prefix(); os << "loc: "; print_loc(os, cc, b.loc); nl();

        line_prefix(); os << "params_in_order: count=" << b.params_in_order.size(); nl();
        ind++;
        for_each_limited(b.params_in_order, [&](uint32_t i, auto s) {
            line_prefix(); os << "[" << i << "] " << sym_name(cc, s) << std::endl;
        });
        ind--;

        line_prefix(); os << "params_by_name: size=" << b.params_by_name.size(); nl();
        ind++;
        for_each_densemap_limited(b.params_by_name, [&](const auto& it) {
            line_prefix();
            os << sym_name(cc, it.first) << " -> " << static_cast<uint32_t>(it.second) << std::endl;
        });
        ind--;

        line_prefix(); os << "hir_param_ids: count=" << b.hir_param_ids.size(); nl();
        ind++;
        for_each_limited(b.hir_param_ids, [&](uint32_t i, auto id) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(id) << std::endl;
        });
        ind--;

        ind--;
    }

    void print(const FnRec& r) {
        line_prefix(); os << "FnRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("decl_id", r.decl_id);
        kv_sym("name", r.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("exported", static_cast<uint32_t>(r.exported));
        kv("is_load", static_cast<uint32_t>(r.is_load));
        kv("intrinsic", static_cast<uint32_t>(r.intrinsic));
        kv_id("binder", r.binder);
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);
        kv_id("body", r.body);
        ind--;
    }

    void print(const StructRec& r) {
        line_prefix(); os << "StructRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("decl_id", r.decl_id);
        kv_sym("name", r.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("exported", static_cast<uint32_t>(r.exported));
        kv_id("binder", r.binder);
        kv("intrinsic", static_cast<uint32_t>(r.intrinsic));
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);

        line_prefix(); os << "fields_in_order: count=" << r.fields_in_order.size(); nl();
        ind++;
        for_each_limited(r.fields_in_order, [&](uint32_t i, auto fid) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(fid) << std::endl;
        });
        ind--;

        line_prefix(); os << "field_by_name: size=" << r.field_by_name.size(); nl();
        ind++;
        for_each_densemap_limited(r.field_by_name, [&](const auto& it) {
            line_prefix(); os << sym_name(cc, it.first) << " -> " << static_cast<uint32_t>(it.second) << std::endl;
        });
        ind--;

        ind--;
    }

    void print(const TraitRec& r) {
        line_prefix(); os << "TraitRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("decl_id", r.decl_id);
        kv_sym("name", r.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("exported", static_cast<uint32_t>(r.exported));
        kv_id("binder", r.binder);
        kv("intrinsic", static_cast<uint32_t>(r.intrinsic));
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);

        line_prefix(); os << "methods: count=" << r.methods.size(); nl();
        ind++;
        for_each_limited(r.methods, [&](uint32_t i, auto mid) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(mid) << std::endl;
        });
        ind--;

        line_prefix(); os << "method_by_name: size=" << r.method_by_name.size(); nl();
        ind++;
        for_each_densemap_limited(r.method_by_name, [&](const auto& it) {
            line_prefix(); os << sym_name(cc, it.first) << " -> " << static_cast<uint32_t>(it.second) << std::endl;
        });
        ind--;

        ind--;
    }

    void print(const ImplRec& r) {
        line_prefix(); os << "ImplRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("decl_id", r.decl_id);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv_id("binder", r.binder);
        kv("unit_index", r.unit_index);
        kv("intrinsic", static_cast<uint32_t>(r.intrinsic));
        kv("arena_index", r.arena_index);

        line_prefix(); os << "trait_path: ";
        if (r.trait_path.has_value()) os << static_cast<uint32_t>(*r.trait_path);
        else os << "<none>";
        nl();

        kv_id("for_type", r.for_type);

        line_prefix(); os << "methods: count=" << r.methods.size(); nl();
        ind++;
        for_each_limited(r.methods, [&](uint32_t i, auto mid) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(mid) << std::endl;
        });
        ind--;

        line_prefix(); os << "method_by_name: size=" << r.method_by_name.size(); nl();
        ind++;
        for_each_densemap_limited(r.method_by_name, [&](const auto& it) {
            line_prefix(); os << sym_name(cc, it.first) << " -> " << static_cast<uint32_t>(it.second) << std::endl;
        });
        ind--;

        ind--;
    }

    void print(const TypeAliasRec& r) {
        line_prefix(); os << "TypeAliasRec"; nl();
        ind++;
        kv_id("owner", r.owner);
        kv_id("decl_id", r.decl_id);
        kv_sym("name", r.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("exported", static_cast<uint32_t>(r.exported));
        kv_id("binder", r.binder);
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);
        kv_id("aliased", r.aliased);
        ind--;
    }

    void print(const MethodRec& r) {
        line_prefix(); os << "MethodRec"; nl();
        ind++;
        kv("kind", to_cstr(r.kind));
        kv_id("owner", r.owner);
        kv_id("id", r.id);
        kv_sym("name", r.name);
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        kv("exported", static_cast<uint32_t>(r.exported));
        kv_id("binder", r.binder);
        kv("unit_index", r.unit_index);
        kv("arena_index", r.arena_index);

        line_prefix(); os << "trait: ";
        if (r.trait.has_value()) os << static_cast<uint32_t>(*r.trait); else os << "<none>";
        nl();

        line_prefix(); os << "impl: ";
        if (r.impl.has_value()) os << static_cast<uint32_t>(*r.impl); else os << "<none>";
        nl();

        kv_id("hir_id", r.hir_id);
        ind--;
    }

    // ---------------------------
    // Pass3 type printing
    // ---------------------------
    void print(const ReceiverSig& r) {
        line_prefix(); os << "ReceiverSig"; nl();
        ind++;
        kv("kind", to_cstr(r.kind));
        line_prefix(); os << "explicit_type: ";
        if (r.explicit_type.has_value()) os << static_cast<uint32_t>(*r.explicit_type);
        else os << "<none>";
        nl();
        line_prefix(); os << "loc: "; print_loc(os, cc, r.loc); nl();
        ind--;
    }

    void print(const ParamSig& p) {
        line_prefix(); os << "ParamSig"; nl();
        ind++;
        kv_sym("name", p.name);
        kv_id("type", p.type);
        line_prefix(); os << "loc: "; print_loc(os, cc, p.loc); nl();
        ind--;
    }

    void print(const CallableSig& c) {
        line_prefix(); os << "CallableSig"; nl();
        ind++;
        kv_id("binder", c.binder);
        print(c.receiver);
        line_prefix(); os << "params: count=" << c.params.size(); nl();
        ind++;
        for_each_limited(c.params, [&](uint32_t i, const ParamSig& ps) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++;
            print(ps);
            ind--;
        });
        ind--;
        kv_id("ret", c.ret);
        kv("is_variadic", static_cast<uint32_t>(c.is_variadic));
        line_prefix(); os << "loc: "; print_loc(os, cc, c.loc); nl();
        ind--;
    }

    void print(const FnSig& s) {
        line_prefix(); os << "FnSig"; nl();
        ind++;
        kv_id("fn_id", s.fn_id);
        kv_id("owner", s.owner);
        print(s.sig);
        kv("exported", static_cast<uint32_t>(s.exported));
        kv("is_load", static_cast<uint32_t>(s.is_load));
        kv_id("hir_decl", s.hir_decl);
        ind--;
    }

    void print(const MethodOwnerRef& r) {
        line_prefix(); os << "MethodOwnerRef"; nl();
        ind++;
        kv("kind", (r.kind == MethodOwnerKind::Trait) ? "Trait" : "Impl");
        kv("owner_id", r.owner_id);
        ind--;
    }

    void print(const MethodSig& s) {
        line_prefix(); os << "MethodSig"; nl();
        ind++;
        kv_id("method_id", s.method_id);
        kv_id("module", s.module);
        print(s.owner);
        kv_id("container_binder", s.container_binder);
        kv_id("method_binder", s.method_binder);
        print(s.sig);
        kv("exported", static_cast<uint32_t>(s.exported));
        kv("has_body", static_cast<uint32_t>(s.has_body));
        line_prefix(); os << "loc: "; print_loc(os, cc, s.loc); nl();
        kv_id("hir_method", s.hir_method);
        ind--;
    }

    void print(const SemaTypeNode& n) {
        line_prefix(); os << "SemaTypeNode kind=" << to_cstr(n.kind); nl();
        ind++;

        std::visit([&]<typename T0>(const T0& payload) {
            using P = std::decay_t<T0>;

            if constexpr (std::is_same_v<P, SemaTypeBuiltin>) {
                line_prefix(); os << "builtin.kind=" << static_cast<uint32_t>(payload.kind); nl();
            } else if constexpr (std::is_same_v<P, SemaTypeParam>) {
                line_prefix(); os << "param.binder=" << payload.binder
                                  << " index=" << static_cast<uint32_t>(payload.index) << std::endl;
            } else if constexpr (std::is_same_v<P, SemaTypeStruct>) {
                line_prefix(); os << "struct_id=" << payload.struct_id << " args=" << payload.args.size(); nl();
                ind++;
                for_each_limited(payload.args, [&](uint32_t i, auto tid) {
                    line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(tid) << std::endl;
                });
                ind--;
            } else if constexpr (std::is_same_v<P, SemaTypeRef>) {
                line_prefix(); os << "ref.mut=" << static_cast<uint32_t>(payload.mut)
                                  << " inner=" << static_cast<uint32_t>(payload.inner) << std::endl;
            } else if constexpr (std::is_same_v<P, SemaTypeArray>) {
                line_prefix(); os << "array.elem=" << static_cast<uint32_t>(payload.elem)
                                  << " size_expr=" << static_cast<uint32_t>(payload.size_expr) << std::endl;
            } else if constexpr (std::is_same_v<P, SemaTypeTrait>) {
                line_prefix(); os << "trait_id=" << payload.trait_id << " args=" << payload.args.size(); nl();
                ind++;
                for_each_limited(payload.args, [&](uint32_t i, auto tid) {
                    line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(tid) << std::endl;
                });
                ind--;
            } else {
                line_prefix(); os << "<unknown SemaType payload>"; nl();
            }
        }, n.data);

        ind--;
    }

    void print(const TypeInterner& ti) {
        line_prefix(); os << "TypeInterner"; nl();
        ind++;
        kv("nodes.size", static_cast<uint32_t>(ti.nodes.size()));
        kv("map.size", static_cast<uint32_t>(ti.map.size()));

        if (cfg.print_typeinterner_nodes) {
            line_prefix(); os << "nodes:"; nl();
            ind++;
            for_each_limited(ti.nodes, [&](uint32_t i, const SemaTypeNode& n) {
                line_prefix(); os << "[" << i << "]"; nl();
                ind++;
                print(n);
                ind--;
            });
            ind--;
        } else {
            line_prefix(); os << "<nodes suppressed>"; nl();
        }
        ind--;
    }

    void print(const ResolvedImplHeader& h) {
        line_prefix(); os << "ResolvedImplHeader"; nl();
        ind++;
        kv_opt_u32("trait_id", h.trait_id);
        kv_id("self_type", h.self_type);
        ind--;
    }

    // ---------------------------
    // Top-level DB printers
    // ---------------------------
    void print(const ModulePassDB& db) {
        line_prefix(); os << "ModulePassDB"; nl();
        ind++;

        kv("modules.size", static_cast<uint32_t>(db.modules.size()));
        kv("imports.size", static_cast<uint32_t>(db.imports.size()));
        kv("graph.edges.size", static_cast<uint32_t>(db.graph.edges.size()));
        kv("graph.edge_import.size", static_cast<uint32_t>(db.graph.edge_import.size()));
        kv("module_by_file.size", static_cast<uint32_t>(db.module_by_file.size()));
        kv("modules_by_hash.size", static_cast<uint32_t>(db.modules_by_hash.size()));
        kv("tree.nodes.size", static_cast<uint32_t>(db.tree.nodes.size()));
        kv("errors.size", static_cast<uint32_t>(db.errors.size()));

        line_prefix(); os << "modules:"; nl();
        ind++;
        for_each_limited(db.modules, [&](uint32_t i, const ModuleRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++;
            print(r, db);
            ind--;
        });
        ind--;

        line_prefix(); os << "imports:"; nl();
        ind++;
        for_each_limited(db.imports, [&](uint32_t i, const ImportRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++;
            print(r, db);
            ind--;
        });
        ind--;

        line_prefix(); os << "module_by_file (FileId -> ModuleId): size=" << db.module_by_file.size(); nl();
        ind++;
        for_each_densemap_limited(db.module_by_file, [&](const auto& it) {
            line_prefix(); os << static_cast<uint32_t>(it.first) << " -> " << static_cast<uint32_t>(it.second) << std::endl;
        });
        ind--;

        line_prefix(); os << "modules_by_hash: size=" << db.modules_by_hash.size(); nl();
        ind++;
        for_each_densemap_limited(db.modules_by_hash, [&](const auto& it) {
            line_prefix(); os << "hash=" << static_cast<uint64_t>(it.first) << " mids=[";
            bool first = true;
            for (auto mid : it.second) { if (!first) os << ","; first = false; os << static_cast<uint32_t>(mid); }
            os << "]"; nl();
        });
        ind--;

        if (cfg.print_module_tree) {
            line_prefix(); os << "tree:"; nl();
            ind++;
            for_each_limited(db.tree.nodes, [&](uint32_t i, const ModuleTreeNode& n) {
                line_prefix(); os << "node[" << i << "] module=";
                if (n.module.has_value()) os << static_cast<uint32_t>(*n.module); else os << "<none>";
                os << " children=" << n.child.size(); nl();

                ind++;
                for_each_densemap_limited(n.child, [&](const auto& it) {
                    line_prefix();
                    os << sym_name(cc, it.first) << " -> node[" << it.second << "]"; nl();
                });
                ind--;
            });
            ind--;
        }

        line_prefix(); os << "errors:"; nl();
        ind++;
        for_each_limited(db.errors, [&](uint32_t i, const ModulePassError& e) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++;
            print(e);
            ind--;
        });
        ind--;

        ind--;
    }

    void print(const ScopePass2DB& db) {
        line_prefix(); os << "ScopePass2DB"; nl();
        ind++;

        kv("module_scopes.size", static_cast<uint32_t>(db.module_scopes.size()));
        kv("binders.size", static_cast<uint32_t>(db.binders.size()));
        kv("fns.size", static_cast<uint32_t>(db.fns.size()));
        kv("structs.size", static_cast<uint32_t>(db.structs.size()));
        kv("traits.size", static_cast<uint32_t>(db.traits.size()));
        kv("impls.size", static_cast<uint32_t>(db.impls.size()));
        kv("aliases.size", static_cast<uint32_t>(db.aliases.size()));
        kv("methods.size", static_cast<uint32_t>(db.methods.size()));
        kv("fn_by_decl.size", static_cast<uint32_t>(db.fn_by_decl.size()));
        kv("struct_by_decl.size", static_cast<uint32_t>(db.struct_by_decl.size()));
        kv("trait_by_decl.size", static_cast<uint32_t>(db.trait_by_decl.size()));
        kv("impl_by_decl.size", static_cast<uint32_t>(db.impl_by_decl.size()));
        kv("alias_by_decl.size", static_cast<uint32_t>(db.alias_by_decl.size()));
        kv("intrinsic_type_exprs.size", static_cast<uint32_t>(db.intrinsic_type_exprs.size()));
        kv("intrinsic_types.size", static_cast<uint32_t>(db.intrinsic_types.size()));
        kv("intrinsic_impls.size", static_cast<uint32_t>(db.intrinsic_impls.size()));
        kv("errors.size", static_cast<uint32_t>(db.errors.size()));

        line_prefix(); os << "prelude:"; nl();
        ind++; print(db.prelude); ind--;

        line_prefix(); os << "module_scopes:"; nl();
        ind++;
        for_each_limited(db.module_scopes, [&](uint32_t i, const ModuleScope& s) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(s); ind--;
        });
        ind--;

        line_prefix(); os << "binders:"; nl();
        ind++;
        for_each_limited(db.binders, [&](uint32_t i, const GenericBinder& b) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(b); ind--;
        });
        ind--;

        line_prefix(); os << "fns:"; nl();
        ind++;
        for_each_limited(db.fns, [&](uint32_t i, const FnRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "structs:"; nl();
        ind++;
        for_each_limited(db.structs, [&](uint32_t i, const StructRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "traits:"; nl();
        ind++;
        for_each_limited(db.traits, [&](uint32_t i, const TraitRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "impls:"; nl();
        ind++;
        for_each_limited(db.impls, [&](uint32_t i, const ImplRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "aliases:"; nl();
        ind++;
        for_each_limited(db.aliases, [&](uint32_t i, const TypeAliasRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "methods:"; nl();
        ind++;
        for_each_limited(db.methods, [&](uint32_t i, const MethodRec& r) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(r); ind--;
        });
        ind--;

        line_prefix(); os << "errors:"; nl();
        ind++;
        for_each_limited(db.errors, [&](uint32_t i, const Scope2Error& e) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(e); ind--;
        });
        ind--;

        ind--;
    }

    void print(const Pass3DB& db) {
        line_prefix(); os << "Pass3DB"; nl();
        ind++;

        line_prefix(); os << "types:"; nl();
        ind++;
        print(db.types);
        ind--;

        kv("alias_target.size", static_cast<uint32_t>(db.alias_target.size()));
        kv("struct_field_types.size", static_cast<uint32_t>(db.struct_field_types.size()));
        kv("fn_sigs.size", static_cast<uint32_t>(db.fn_sigs.size()));
        kv("method_sigs.size", static_cast<uint32_t>(db.method_sigs.size()));
        kv("impl_headers.size", static_cast<uint32_t>(db.impl_headers.size()));
        kv("errors.size", static_cast<uint32_t>(db.errors.size()));

        line_prefix(); os << "alias_target:"; nl();
        ind++;
        for_each_limited(db.alias_target, [&](uint32_t i, auto tid) {
            line_prefix(); os << "[" << i << "] " << static_cast<uint32_t>(tid) << std::endl;
        });
        ind--;

        line_prefix(); os << "struct_field_types:"; nl();
        ind++;
        for_each_limited(db.struct_field_types, [&](uint32_t sid, const auto& vec) {
            line_prefix(); os << "StructId[" << sid << "] field_types=" << vec.size(); nl();
            ind++;
            for_each_limited(vec, [&](uint32_t fi, auto tid) {
                line_prefix(); os << "[" << fi << "] " << static_cast<uint32_t>(tid) << std::endl;
            });
            ind--;
        });
        ind--;

        line_prefix(); os << "fn_sigs:"; nl();
        ind++;
        for_each_limited(db.fn_sigs, [&](uint32_t i, const FnSig& s) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(s); ind--;
        });
        ind--;

        line_prefix(); os << "method_sigs:"; nl();
        ind++;
        for_each_limited(db.method_sigs, [&](uint32_t i, const MethodSig& s) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(s); ind--;
        });
        ind--;

        line_prefix(); os << "impl_headers:"; nl();
        ind++;
        for_each_limited(db.impl_headers, [&](uint32_t i, const ResolvedImplHeader& h) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(h); ind--;
        });
        ind--;

        line_prefix(); os << "errors:"; nl();
        ind++;
        for_each_limited(db.errors, [&](uint32_t i, const Resolve3Error& e) {
            line_prefix(); os << "[" << i << "]"; nl();
            ind++; print(e); ind--;
        });
        ind--;

        ind--;
    }
};

// ---------------------------
// One entry-point function (works for ModulePassDB, ScopePass2DB, Pass3DB)
// ---------------------------
template <class CompilerCtx, class DB>
inline void print_db(std::ostream& os, const CompilerCtx& cc, const DB& db, PrintCfg cfg = {}) {
    Printer<CompilerCtx> p{os, cc, cfg, 0};
    p.print(db);
}

} // namespace kl::db

#endif //INZ_DB_PRINTER_HPP