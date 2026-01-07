#ifndef INZ_SEMA_SCOPE_PASS2_HPP
#define INZ_SEMA_SCOPE_PASS2_HPP

#include <cstdint>
#include <vector>
#include <optional>
#include <variant>
#include <type_traits>
#include <algorithm>
#include <initializer_list>

#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>

#include "sema/module_import_pass.hpp"   // ModulePassDB, ModuleId, ImportId, FileId, kInvalidModule
#include "hir/arena_holder.hpp"
#include "hir/arena.hpp"

namespace sema
{
    // =========================
    // Semantic ids allocated in Pass 2
    // =========================
    using FnId = uint32_t;
    using StructId = uint32_t;
    using TraitId = uint32_t;
    using ImplId = uint32_t;
    using MethodId = uint32_t;
    using TypeAliasId = uint32_t;
    using BinderId = uint32_t;

    static constexpr FnId kInvalidFn = static_cast<FnId>(-1);
    static constexpr StructId kInvalidStruct = static_cast<StructId>(-1);
    static constexpr TraitId kInvalidTrait = static_cast<TraitId>(-1);
    static constexpr ImplId kInvalidImpl = static_cast<ImplId>(-1);
    static constexpr MethodId kInvalidMethod = static_cast<MethodId>(-1);
    static constexpr TypeAliasId kInvalidAlias = static_cast<TypeAliasId>(-1);
    static constexpr BinderId kInvalidBinder = static_cast<BinderId>(-1);

    // "Prelude owner" is a synthetic module id for intrinsic definitions.
    static constexpr ModuleId kPreludeOwner = ~0u;

    using SemaParamIndex = uint16_t;

    // =========================
    // Receiver model (needed in Pass2 for intrinsic method signatures)
    // =========================
    enum class ReceiverKind : uint8_t
    {
        None, // not used in your language (no static methods); reserved
        Value, // self
        RefImm, // &self
        RefMut // &mut self
    };

    // =========================
    // Intrinsic type expressions (no HIR)
    // =========================
    using IntrinsicTypeExprId = uint32_t;
    static constexpr IntrinsicTypeExprId kInvalidIntrinsicTypeExpr = ~0u;

    enum class IntrinsicTypeExprKind : uint8_t
    {
        Builtin, // kl::rt::BuiltinTypeExprKind
        Param, // references a binder param by index
        Struct, // StructId + args
        Trait, // TraitId + args (only if you allow traits as types)
        Ref, // &T / &mut T
        Array // T[N] (optional; keep if you want it for intrinsics)
    };

    struct IntrinsicTypeExpr
    {
        IntrinsicTypeExprKind kind{};
        lex::Loc loc{};

        // Small, explicit payloads:
        kl::rt::BuiltinTypeExprKind builtin{};
        SemaParamIndex param_index{}; // for Param
        StructId struct_id{kInvalidStruct}; // for Struct
        TraitId trait_id{kInvalidTrait}; // for Trait
        ast::Mutability mut{}; // for Ref
        IntrinsicTypeExprId ref_inner{kInvalidIntrinsicTypeExpr}; // for Ref
        IntrinsicTypeExprId array_elem{kInvalidIntrinsicTypeExpr}; // for Array
        uint64_t array_len{}; // for Array (if you want; else remove)

        llvm::SmallVector<IntrinsicTypeExprId, 4> args; // for Struct/Trait
    };

    // =========================
    // Intrinsic type defs (no HIR)
    // =========================
    enum class IntrinsicTypeKind : uint8_t { Box, Vec, Slice, Str };

    struct IntrinsicTypeDef
    {
        IntrinsicTypeKind kind{};
        StructId sid{kInvalidStruct}; // points to a StructRec in db.structs
        lex::SymId name{};
        BinderId binder{kInvalidBinder}; // generic params for the intrinsic type
        lex::Loc loc{};
    };

    // =========================
    // Intrinsic methods & impls (no HIR)
    // =========================
    enum class IntrinsicMethodKind : uint8_t
    {
        // Keep this as a lowering tag for codegen/lowering later.
        // Start with the ones you actually implement.
        BoxIndexRef,
        BoxIndexMutRef,
        BoxLen,

        VecPush,
        VecLen,
        VecIndexRef,
        VecIndexMutRef,

        SliceLen,
        SliceIndexRef,
        SliceIndexMutRef,

        StrLen,
        StrIndexRef
    };

    struct IntrinsicMethod
    {
        lex::SymId name{};
        lex::Loc loc{};

        bool exported{true};

        ReceiverKind receiver{ReceiverKind::RefImm};

        // method-level generics (usually none for your intrinsics initially)
        BinderId binder{kInvalidBinder};

        llvm::SmallVector<IntrinsicTypeExprId, 8> param_types; // does NOT include receiver
        IntrinsicTypeExprId ret_type{kInvalidIntrinsicTypeExpr};

        IntrinsicMethodKind kind{};
    };

    struct IntrinsicImplRec
    {
        ModuleId owner{kPreludeOwner};
        lex::Loc loc{};
        bool intrinsic{true};

        // Trait implemented OR nullopt for inherent methods.
        std::optional<TraitId> trait;

        // Self type expressed as IntrinsicTypeExpr.
        IntrinsicTypeExprId self_type{kInvalidIntrinsicTypeExpr};

        llvm::SmallVector<IntrinsicMethod, 16> methods;
    };

    // =========================
    // Pass 2 errors (scope-level only)
    // =========================
    enum class Scope2ErrKind : uint8_t
    {
        DuplicateTypeName,
        DuplicateValueName,
        DeclNameConflictsWithImport,

        DuplicateTypeParamName,

        DuplicateStructFieldName,
        DuplicateTraitMethodName,
        DuplicateImplMethodName,

        TypeAliasMissingName,
        InternalMissingRequiredField
    };

    struct Scope2Error
    {
        Scope2ErrKind kind{};
        FileId file{};
        ModuleId module{kInvalidModule};
        lex::SymId name{};
        lex::Loc loc{};
    };

    // =========================
    // Symbols & scopes
    // =========================
    enum class SymKind : uint8_t { Fn, LoadFn, Struct, Trait, TypeAlias };

    struct Symbol
    {
        SymKind kind{};
        uint32_t id{};
        uint8_t arity{}; // generic arity for types (0 for values)
        lex::Loc loc{};
        bool exported{};
        bool intrinsic{};
    };

    struct ImportBinding
    {
        ImportId pass1_import{};
        ModuleId target{kInvalidModule};
        lex::Loc loc{};
    };

    struct ModuleScope
    {
        llvm::DenseMap<lex::SymId, ImportBinding> imports; // bound name -> import binding
        llvm::DenseMap<lex::SymId, Symbol> types; // type namespace
        llvm::DenseMap<lex::SymId, Symbol> values; // value namespace
        llvm::SmallVector<ImplId, 4> impls; // impl blocks in this module
    };

    // =========================
    // Generic binders
    // =========================
    enum class BinderOwnerKind : uint8_t { Fn, Struct, Trait, Impl, TraitMethod, ImplMethod, Intrinsic };

    struct GenericBinder
    {
        BinderOwnerKind owner_kind{};
        uint32_t owner_id{};
        lex::Loc loc{};

        llvm::DenseMap<lex::SymId, SemaParamIndex> params_by_name{};
        llvm::SmallVector<lex::SymId, 4> params_in_order{};

        // Anchors for non-intrinsic binders:
        llvm::SmallVector<hir::TypeParamId, 4> hir_param_ids{};
    };

    // =========================
    // Records captured for later passes
    // =========================
    struct FnRec
    {
        ModuleId owner{};
        hir::DeclId decl_id{};
        lex::SymId name{};
        lex::Loc loc{};
        bool exported{};
        bool is_load{};
        bool intrinsic{false};
        BinderId binder{kInvalidBinder};

        uint32_t unit_index{};
        uint32_t arena_index{};
        hir::BlockId body{};
    };

    struct StructRec
    {
        ModuleId owner{};
        hir::DeclId decl_id{};
        lex::SymId name{};
        lex::Loc loc{};
        bool exported{};
        BinderId binder{kInvalidBinder};
        bool intrinsic{false};
        uint32_t unit_index{};
        uint32_t arena_index{};

        llvm::SmallVector<hir::FieldDeclId, 8> fields_in_order{};
        llvm::DenseMap<lex::SymId, hir::FieldDeclId> field_by_name{};
    };

    struct TraitRec
    {
        ModuleId owner{};
        hir::DeclId decl_id{};
        lex::SymId name{};
        lex::Loc loc{};
        bool exported{};
        BinderId binder{kInvalidBinder};
        bool intrinsic{false};

        uint32_t unit_index{};
        uint32_t arena_index{};

        llvm::SmallVector<MethodId, 8> methods{};
        llvm::DenseMap<lex::SymId, MethodId> method_by_name{};
    };

    struct ImplRec
    {
        ModuleId owner{};
        hir::DeclId decl_id{};
        lex::Loc loc{};
        BinderId binder{kInvalidBinder};

        uint32_t unit_index{};
        bool intrinsic{false};
        uint32_t arena_index{};

        std::optional<hir::ExprId> trait_path;
        hir::TypeId for_type{};

        llvm::SmallVector<MethodId, 8> methods{};
        llvm::DenseMap<lex::SymId, MethodId> method_by_name{};
    };

    struct TypeAliasRec
    {
        ModuleId owner{};
        hir::DeclId decl_id{};
        lex::SymId name{};
        lex::Loc loc{};
        bool exported{};
        BinderId binder{kInvalidBinder};

        uint32_t unit_index{};
        uint32_t arena_index{};

        hir::TypeId aliased{};
    };

    enum class MethodKind : uint8_t { TraitMethod, ImplMethod };

    struct MethodRec
    {
        MethodKind kind{};
        ModuleId owner{};
        MethodId id{};
        lex::SymId name{};
        lex::Loc loc{};
        bool exported{};
        BinderId binder{kInvalidBinder};

        uint32_t unit_index{};
        uint32_t arena_index{};

        std::optional<TraitId> trait;
        std::optional<ImplId> impl;

        hir::MethodId hir_id{};
    };

    // =========================
    // Pass 2 DB
    // =========================
    struct ScopePass2DB
    {
        std::vector<ModuleScope> module_scopes; // indexed by ModuleId
        ModuleScope prelude;

        std::vector<GenericBinder> binders;

        std::vector<FnRec> fns;
        std::vector<StructRec> structs;
        std::vector<TraitRec> traits;
        std::vector<ImplRec> impls;
        std::vector<TypeAliasRec> aliases;
        std::vector<MethodRec> methods;

        llvm::DenseMap<hir::DeclId, FnId> fn_by_decl;
        llvm::DenseMap<hir::DeclId, StructId> struct_by_decl;
        llvm::DenseMap<hir::DeclId, TraitId> trait_by_decl;
        llvm::DenseMap<hir::DeclId, ImplId> impl_by_decl;
        llvm::DenseMap<hir::DeclId, TypeAliasId> alias_by_decl;

        // Intrinsics live here (filled by an injector/registry AFTER runScopePass2()).
        std::vector<IntrinsicTypeExpr> intrinsic_type_exprs;
        std::vector<IntrinsicTypeDef> intrinsic_types;
        std::vector<IntrinsicImplRec> intrinsic_impls;

        std::vector<Scope2Error> errors;
    };

    // =========================
    // Pass 2 configuration
    // =========================
    struct ScopePass2Config
    {
        bool disallowDeclImportCollision = true;
        bool trustPass1ImportBindingChecks = true;
    };

    // =========================
    // Internal helpers
    // =========================
    static inline void pushError(ScopePass2DB& out, Scope2ErrKind k,
                                 FileId file, ModuleId mod, lex::SymId name, const lex::Loc& loc)
    {
        out.errors.push_back(Scope2Error{
            .kind = k,
            .file = file,
            .module = mod,
            .name = name,
            .loc = loc
        });
    }

    static inline uint8_t arityFromBinder(const ScopePass2DB& out, BinderId b)
    {
        if (b == kInvalidBinder) return 0;
        return static_cast<uint8_t>(out.binders[(size_t)b].params_in_order.size());
    }

    static inline bool insertSym(llvm::DenseMap<lex::SymId, Symbol>& ns,
                                 lex::SymId name, const Symbol& sym)
    {
        return ns.try_emplace(name, sym).second;
    }

    // Build a binder from HIR type params.
    static inline BinderId buildBinder(ScopePass2DB& out,
                                       BinderOwnerKind ok,
                                       uint32_t owner_id,
                                       const lex::Loc& loc,
                                       const std::vector<hir::TypeParamId>& tparams,
                                       const hir::Arena& ar,
                                       FileId file,
                                       ModuleId mod)
    {
        if (tparams.empty())
            return kInvalidBinder;

        GenericBinder b{};
        b.owner_kind = ok;
        b.owner_id = owner_id;
        b.loc = loc;

        b.params_in_order.reserve(tparams.size());
        b.hir_param_ids.reserve(tparams.size());

        SemaParamIndex idx = 0;
        for (hir::TypeParamId tpId : tparams)
        {
            const auto& tp = ar.tparams[(size_t)tpId];
            const lex::SymId n = tp.name;

            if (b.params_by_name.find(n) != b.params_by_name.end())
            {
                pushError(out, Scope2ErrKind::DuplicateTypeParamName, file, mod, n, tp.loc);
                continue; // recovery: first wins
            }

            b.params_by_name.try_emplace(n, idx++);
            b.params_in_order.push_back(n);
            b.hir_param_ids.push_back(tpId);
        }

        const BinderId bid = static_cast<BinderId>(out.binders.size());
        out.binders.push_back(std::move(b));
        return bid;
    }

    // Build a binder for intrinsics (no HIR anchors). Names must already be interned SymIds.
    static inline BinderId buildIntrinsicBinder(ScopePass2DB& out,
                                                uint32_t owner_id,
                                                const lex::Loc& loc,
                                                std::initializer_list<lex::SymId> params)
    {
        if (params.size() == 0)
            return kInvalidBinder;

        GenericBinder b{};
        b.owner_kind = BinderOwnerKind::Intrinsic;
        b.owner_id = owner_id;
        b.loc = loc;

        b.params_in_order.reserve(params.size());

        SemaParamIndex idx = 0;
        for (lex::SymId p : params)
        {
            if (b.params_by_name.find(p) != b.params_by_name.end())
            {
                // Intrinsic param duplicate is a programming bug; ignore (first wins).
                continue;
            }
            b.params_by_name.try_emplace(p, idx++);
            b.params_in_order.push_back(p);
        }

        const BinderId bid = static_cast<BinderId>(out.binders.size());
        out.binders.push_back(std::move(b));
        return bid;
    }

    // =========================
    // PASS 2 runner (clean, non-visitor)
    // =========================
    inline ScopePass2DB runScopePass2(const ModulePassDB& p1,
                                      hir::ArenaHolder& holder,
                                      const ScopePass2Config& cfg = {})
    {
        ScopePass2DB out;
        out.module_scopes.resize(p1.modules.size());

        const size_t nmods = p1.modules.size();

        for (size_t mi = 0; mi < nmods; ++mi)
        {
            const ModuleId mid = static_cast<ModuleId>(mi);
            const auto& mr = p1.modules[mi];

            const FileId file = mr.file;
            hir::Arena& ar = holder.arenas_[mi];
            ModuleScope& scope = out.module_scopes[mi];

            // ------------------------------------------------------------
            // Step 1: import bindings from Pass 1
            // ------------------------------------------------------------
            for (uint32_t k = 0; k < mr.import_count; ++k)
            {
                const ImportId iid = mr.import_begin + k;
                const auto& imp = p1.imports[(size_t)iid];

                auto segs = p1.pool.view(imp.path);
                const lex::SymId bound = imp.alias.has_value()
                                             ? *imp.alias
                                             : (segs.empty() ? lex::SymId{} : segs.back());

                if (bound == lex::SymId{})
                    continue;

                ImportBinding bnd{
                    .pass1_import = iid,
                    .target = imp.target,
                    .loc = imp.loc
                };

                const bool inserted = scope.imports.try_emplace(bound, bnd).second;
                if (!inserted && !cfg.trustPass1ImportBindingChecks)
                {
                    // Optional: if you really want Pass2 to diagnose import binding collisions.
                    pushError(out, Scope2ErrKind::DuplicateValueName, file, mid, bound, imp.loc);
                }
            }

            // ------------------------------------------------------------
            // Step 2: top-level declarations (types/values + containers)
            // ------------------------------------------------------------
            for (hir::DeclId did : ar.module.decls)
            {
                const auto& d = ar.decls[(size_t)did];

                std::visit([&]<typename T0>(T0&& node)
                {
                    using T = std::decay_t<T0>;

                    // -------------------------
                    // fn
                    // -------------------------
                    if constexpr (std::is_same_v<T, hir::FnDecl>)
                    {
                        const lex::SymId name = node.header.name;

                        if (cfg.disallowDeclImportCollision && scope.imports.find(name) != scope.imports.end())
                            pushError(out, Scope2ErrKind::DeclNameConflictsWithImport, file, mid, name, node.loc);

                        if (scope.values.find(name) != scope.values.end())
                        {
                            pushError(out, Scope2ErrKind::DuplicateValueName, file, mid, name, node.loc);
                            return;
                        }

                        const FnId fid = (FnId)out.fns.size();
                        const BinderId binder = buildBinder(out, BinderOwnerKind::Fn, fid, node.loc,
                                                            node.tparams, ar, file, mid);

                        out.fns.push_back(FnRec{
                            .owner = mid,
                            .decl_id = did,
                            .name = name,
                            .loc = node.loc,
                            .exported = node.exported,
                            .is_load = false,
                            .intrinsic = false,
                            .binder = binder,
                            .unit_index = mr.unit_index,
                            .arena_index = mr.arena_index,
                            .body = node.body
                        });

                        out.fn_by_decl.try_emplace(did, fid);

                        insertSym(scope.values, name, Symbol{
                                      .kind = SymKind::Fn,
                                      .id = fid,
                                      .arity = 0,
                                      .loc = node.loc,
                                      .exported = node.exported,
                                      .intrinsic = false
                                  });
                    }
                    else if constexpr (std::is_same_v<T, hir::LoadFnDecl>)
                    {
                        const lex::SymId name = node.header.name;

                        if (cfg.disallowDeclImportCollision && scope.imports.find(name) != scope.imports.end())
                            pushError(out, Scope2ErrKind::DeclNameConflictsWithImport, file, mid, name, node.loc);

                        if (scope.values.find(name) != scope.values.end())
                        {
                            pushError(out, Scope2ErrKind::DuplicateValueName, file, mid, name, node.loc);
                            return;
                        }

                        const FnId fid = (FnId)out.fns.size();

                        out.fns.push_back(FnRec{
                            .owner = mid,
                            .decl_id = did,
                            .name = name,
                            .loc = node.loc,
                            .exported = node.exported,
                            .is_load = true,
                            .intrinsic = false,
                            .binder = kInvalidBinder,
                            .unit_index = mr.unit_index,
                            .arena_index = mr.arena_index,
                            .body = {} // none
                        });

                        out.fn_by_decl.try_emplace(did, fid);

                        insertSym(scope.values, name, Symbol{
                                      .kind = SymKind::LoadFn,
                                      .id = fid,
                                      .arity = 0,
                                      .loc = node.loc,
                                      .exported = node.exported,
                                      .intrinsic = false
                                  });
                    }

                    // -------------------------
                    // struct
                    // -------------------------
                    else if constexpr (std::is_same_v<T, hir::StructDecl>)
                    {
                        const lex::SymId name = node.name;

                        if (cfg.disallowDeclImportCollision && scope.imports.find(name) != scope.imports.end())
                            pushError(out, Scope2ErrKind::DeclNameConflictsWithImport, file, mid, name, node.loc);

                        if (scope.types.find(name) != scope.types.end())
                        {
                            pushError(out, Scope2ErrKind::DuplicateTypeName, file, mid, name, node.loc);
                            return;
                        }

                        const StructId sid = (StructId)out.structs.size();
                        const BinderId binder = buildBinder(out, BinderOwnerKind::Struct, sid, node.loc,
                                                            node.tparams, ar, file, mid);

                        StructRec rec{};
                        rec.owner = mid;
                        rec.decl_id = did;
                        rec.name = name;
                        rec.loc = node.loc;
                        rec.exported = node.exported;
                        rec.binder = binder;
                        rec.intrinsic = false;
                        rec.unit_index = mr.unit_index;
                        rec.arena_index = mr.arena_index;

                        rec.fields_in_order.reserve(node.fields.size());
                        for (auto fid : node.fields)
                        {
                            const auto& f = ar.field_decls[(size_t)fid];
                            const lex::SymId fn = f.name;

                            if (!rec.field_by_name.try_emplace(fn, fid).second)
                                pushError(out, Scope2ErrKind::DuplicateStructFieldName, file, mid, fn, f.loc);

                            rec.fields_in_order.push_back(fid);
                        }

                        out.structs.push_back(std::move(rec));
                        out.struct_by_decl.try_emplace(did, sid);

                        insertSym(scope.types, name, Symbol{
                                      .kind = SymKind::Struct,
                                      .id = sid,
                                      .arity = arityFromBinder(out, binder),
                                      .loc = node.loc,
                                      .exported = node.exported,
                                      .intrinsic = false
                                  });
                    }

                    // -------------------------
                    // trait
                    // -------------------------
                    else if constexpr (std::is_same_v<T, hir::TraitDecl>)
                    {
                        const lex::SymId name = node.name;

                        if (cfg.disallowDeclImportCollision && scope.imports.find(name) != scope.imports.end())
                            pushError(out, Scope2ErrKind::DeclNameConflictsWithImport, file, mid, name, node.loc);

                        if (scope.types.find(name) != scope.types.end())
                        {
                            pushError(out, Scope2ErrKind::DuplicateTypeName, file, mid, name, node.loc);
                            // recovery continues: still create trait so later passes have stable IDs
                        }

                        const TraitId tid = (TraitId)out.traits.size();
                        const BinderId binder = buildBinder(out, BinderOwnerKind::Trait, tid, node.loc,
                                                            node.tparams, ar, file, mid);

                        TraitRec tr{};
                        tr.owner = mid;
                        tr.decl_id = did;
                        tr.name = name;
                        tr.loc = node.loc;
                        tr.exported = node.exported;
                        tr.binder = binder;
                        tr.intrinsic = false;
                        tr.unit_index = mr.unit_index;
                        tr.arena_index = mr.arena_index;

                        out.traits.push_back(std::move(tr));
                        out.trait_by_decl.try_emplace(did, tid);

                        insertSym(scope.types, name, Symbol{
                                      .kind = SymKind::Trait,
                                      .id = tid,
                                      .arity = arityFromBinder(out, binder),
                                      .loc = node.loc,
                                      .exported = node.exported,
                                      .intrinsic = false
                                  });
                    }

                    // -------------------------
                    // impl
                    // -------------------------
                    else if constexpr (std::is_same_v<T, hir::ImplDecl>)
                    {
                        const ImplId iid = (ImplId)out.impls.size();
                        const BinderId binder = buildBinder(out, BinderOwnerKind::Impl, iid, node.loc,
                                                            node.tparams, ar, file, mid);

                        ImplRec im{};
                        im.owner = mid;
                        im.decl_id = did;
                        im.loc = node.loc;
                        im.binder = binder;
                        im.unit_index = mr.unit_index;
                        im.intrinsic = false;
                        im.arena_index = mr.arena_index;
                        im.trait_path = node.trait_path;
                        im.for_type = node.for_type;

                        out.impls.push_back(std::move(im));
                        out.impl_by_decl.try_emplace(did, iid);
                        scope.impls.push_back(iid);
                    }

                    // (type alias currently disabled in your HIR; keep it disabled here)
                    else
                    {
                        // If you add new decl kinds, handle them here.
                    }
                }, d.kind);
            }

            // ------------------------------------------------------------
            // Step 3: methods inside trait/impl declarations
            // ------------------------------------------------------------
            for (hir::DeclId did : ar.module.decls)
            {
                const auto& d = ar.decls[(size_t)did];

                std::visit([&]<typename T0>(T0&& node)
                {
                    using T = std::decay_t<T0>;

                    if constexpr (std::is_same_v<T, hir::TraitDecl>)
                    {
                        auto itT = out.trait_by_decl.find(did);
                        if (itT == out.trait_by_decl.end())
                            return;

                        TraitId tid = itT->second;
                        auto& tr = out.traits[(size_t)tid];

                        for (hir::MethodId hm : node.methods)
                        {
                            auto& mk = ar.methods[(size_t)hm];
                            std::visit([&]<typename T1>(T1&& mnode)
                            {
                                using MT = std::decay_t<T1>;
                                if constexpr (std::is_same_v<MT, hir::TraitMethod>)
                                {
                                    const lex::SymId mn = mnode.header.name;

                                    if (tr.method_by_name.find(mn) != tr.method_by_name.end())
                                    {
                                        pushError(out, Scope2ErrKind::DuplicateTraitMethodName, file, mid, mn,
                                                  mnode.loc);
                                        return;
                                    }

                                    const MethodId mid2 = (MethodId)out.methods.size();
                                    const BinderId binder = buildBinder(out, BinderOwnerKind::TraitMethod, mid2,
                                                                        mnode.loc,
                                                                        mnode.tparams, ar, file, mid);

                                    out.methods.push_back(MethodRec{
                                        .kind = MethodKind::TraitMethod,
                                        .owner = mid,
                                        .id = mid2,
                                        .name = mn,
                                        .loc = mnode.loc,
                                        .exported = mnode.exported,
                                        .binder = binder,
                                        .unit_index = mr.unit_index,
                                        .arena_index = mr.arena_index,
                                        .trait = tid,
                                        .impl = std::nullopt,
                                        .hir_id = hm
                                    });

                                    tr.method_by_name.try_emplace(mn, mid2);
                                    tr.methods.push_back(mid2);
                                }
                            }, mk.kind);
                        }
                    }
                    else if constexpr (std::is_same_v<T, hir::ImplDecl>)
                    {
                        auto itI = out.impl_by_decl.find(did);
                        if (itI == out.impl_by_decl.end())
                            return;

                        ImplId iid = itI->second;
                        auto& imr = out.impls[(size_t)iid];

                        for (hir::MethodId hm : node.methods)
                        {
                            auto& mk = ar.methods[(size_t)hm];
                            std::visit([&]<typename T2>(T2&& mnode)
                            {
                                using MT = std::decay_t<T2>;
                                if constexpr (std::is_same_v<MT, hir::ImplMethod>)
                                {
                                    const lex::SymId mn = mnode.header.name;

                                    if (imr.method_by_name.find(mn) != imr.method_by_name.end())
                                    {
                                        pushError(out, Scope2ErrKind::DuplicateImplMethodName, file, mid, mn,
                                                  mnode.loc);
                                        return;
                                    }

                                    const MethodId mid2 = (MethodId)out.methods.size();
                                    const BinderId binder = buildBinder(out, BinderOwnerKind::ImplMethod, mid2,
                                                                        mnode.loc,
                                                                        mnode.tparams, ar, file, mid);

                                    out.methods.push_back(MethodRec{
                                        .kind = MethodKind::ImplMethod,
                                        .owner = mid,
                                        .id = mid2,
                                        .name = mn,
                                        .loc = mnode.loc,
                                        .exported = mnode.exported,
                                        .binder = binder,
                                        .unit_index = mr.unit_index,
                                        .arena_index = mr.arena_index,
                                        .trait = std::nullopt, // resolved in Pass3
                                        .impl = iid,
                                        .hir_id = hm
                                    });

                                    imr.method_by_name.try_emplace(mn, mid2);
                                    imr.methods.push_back(mid2);
                                }
                            }, mk.kind);
                        }
                    }
                }, d.kind);
            }
        }

        return out;
    }

    // =========================
    // Optional: lightweight view helpers (for later passes)
    // =========================
    struct ScopePass2View
    {
        const ModulePassDB& p1;
        const ScopePass2DB& p2;

        const ModuleScope& scope(ModuleId m) const { return p2.module_scopes[(size_t)m]; }

        llvm::ArrayRef<lex::SymId> modulePath(ModuleId m) const
        {
            return p1.pool.view(p1.modules[(size_t)m].package_path);
        }

        ModuleId importedModule(ModuleId m, lex::SymId bound) const
        {
            auto& sc = scope(m);
            auto it = sc.imports.find(bound);
            if (it == sc.imports.end()) return kInvalidModule;
            return it->second.target;
        }

        const GenericBinder* binder(BinderId bid) const
        {
            if (bid == kInvalidBinder) return nullptr;
            return &p2.binders[(size_t)bid];
        }
    };
} // namespace sema

#endif // INZ_SEMA_SCOPE_PASS2_HPP
