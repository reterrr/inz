#ifndef INZ_SEMA_PASS3_RESOLVE_HPP
#define INZ_SEMA_PASS3_RESOLVE_HPP

#include <cstdint>
#include <vector>
#include <optional>
#include <variant>
#include <algorithm>

#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/Hashing.h>

#include "hir/arena_holder.hpp"
#include "hir/arena.hpp"

// You already have these from pass1/pass2:
#include "sema/module_import_pass.hpp"   // ModulePassDB, ModuleId, FileId, kInvalidModule
#include "sema/scope_pass.hpp"       // your Pass2 DB

namespace sema
{
    // ============================================================
    // Pass 3 errors
    // ============================================================
    enum class Resolve3ErrKind : uint8_t
    {
        UnknownImportTargetModule, // import binding exists but target module not known to compilation unit
        UnknownModuleInPath, // a::b where a resolved but a::b module missing
        UnknownTypeName, // last segment not found in type namespace
        WrongKindUsedAsType, // e.g. fn used where type expected
        WrongKindUsedAsTrait, // e.g. struct used in trait position
        TraitNotFound, // trait path missing/unknown
        InvalidImplSelfType, // impl Trait for <non-nominal>
        DuplicateImpl, // same trait + same self-type key

        AliasCycle // type alias cycles (if aliases are present in pass2)
    };

    enum class TypeLookupExpect : uint8_t
    {
        TypeOnly, // structs / aliases / type params only
        TraitOnly, // traits only
        Any // allow structs / aliases / traits (still disallow type params unless single segment)
    };

    struct Resolve3Error
    {
        Resolve3ErrKind kind{};
        FileId file{};
        ModuleId module{kInvalidModule};
        lex::Loc loc{};
        lex::SymId name{}; // best-effort (segment)
        ModuleId other_module{kInvalidModule}; // for some diagnostics
    };

    // ============================================================
    // Semantic type interner
    // ============================================================
    using SemaTypeId = uint32_t;
    static constexpr SemaTypeId kInvalidSemaType = static_cast<SemaTypeId>(-1);

    enum class SemaTypeKind : uint8_t
    {
        Builtin,
        TypeParam, // generic parameter
        Struct, // nominal (struct) + args
        Ref,
        Array,
        Trait
        // (Extend later: Enum, TraitObject, FunctionType, etc.)
    };

    struct ReceiverSig
    {
        ReceiverKind kind{ReceiverKind::None};

        // Optional explicit receiver type override if you allow it (your ParamSelf has explicit_type).
        // If nullopt, later pass computes it from impl self type / trait self type.
        std::optional<SemaTypeId> explicit_type;

        lex::Loc loc{};
    };

    struct ParamSig
    {
        lex::SymId name{}; // for diagnostics and named-arg features later
        SemaTypeId type{kInvalidSemaType};
        lex::Loc loc{};
    };

    struct CallableSig
    {
        // Generic binder for this callable (fn or method).
        // IMPORTANT: this binder is the callable-level binder only.
        // If methods live inside trait/impl, you will have an "outer binder stack" elsewhere.
        uint32_t binder{0}; // BinderId (kInvalidBinder allowed if no generics)

        ReceiverSig receiver{};
        llvm::SmallVector<ParamSig, 8> params;
        SemaTypeId ret{kInvalidSemaType}; // use Builtin::Void if no explicit ret type

        // Useful for later passes
        bool is_variadic{false}; // if you add it in the future
        lex::Loc loc{};
    };

    struct FnSig
    {
        uint32_t fn_id{0}; // FnId from Pass 2
        ModuleId owner{kInvalidModule};

        CallableSig sig{};

        bool exported{false}; // from FnDecl.exported / LoadFnDecl.exported
        bool is_load{false}; // distinguishes LoadFnDecl vs FnDecl (optional)

        // Optional: HIR source anchors
        hir::DeclId hir_decl{(~0u)};
    };

    enum class MethodOwnerKind : uint8_t
    {
        Trait,
        Impl
    };

    struct MethodOwnerRef
    {
        MethodOwnerKind kind{MethodOwnerKind::Trait};
        uint32_t owner_id{0}; // TraitId or ImplId
    };

    struct MethodSig
    {
        uint32_t method_id{0}; // MethodId from Pass 2
        ModuleId module{kInvalidModule};

        MethodOwnerRef owner{};

        // Outer binder stack (container binder + callable binder) matters for resolving type params later.
        // Store them explicitly so later passes do not reconstruct stacks repeatedly.
        uint32_t container_binder{0}; // BinderId for trait/impl (kInvalidBinder if none)
        uint32_t method_binder{0}; // BinderId for method itself (kInvalidBinder if none)

        CallableSig sig{};

        // Policy:
        // - For TraitMethod: exported defaults to trait.exported unless explicitly set (your earlier discussion).
        // - For ImplMethod: exported depends on syntax rules; trait-impl methods should match trait method vis.
        bool exported{false};

        // Trait methods can be abstract.
        bool has_body{false};

        lex::Loc loc{};

        // Optional: HIR anchor
        hir::MethodId hir_method{(hir::MethodId)~0u};
    };


    struct SemaTypeTrait
    {
        uint32_t trait_id; // TraitId
        llvm::SmallVector<SemaTypeId, 4> args;
    };

    struct SemaTypeBuiltin
    {
        kl::rt::BuiltinTypeExprKind kind;
    };

    struct SemaTypeParam
    {
        uint32_t binder; // BinderId
        SemaParamIndex index; // Stable semantic index within binder
    };

    struct SemaTypeStruct
    {
        uint32_t struct_id; // StructId (from pass2)
        llvm::SmallVector<SemaTypeId, 4> args;
    };

    struct SemaTypeRef
    {
        ast::Mutability mut;
        SemaTypeId inner;
    };

    struct SemaTypeArray
    {
        SemaTypeId elem;
        hir::ExprId size_expr; // keep raw expr; const-fold later
    };

    struct SemaTypeNode
    {
        SemaTypeKind kind{};
        std::variant<
            SemaTypeBuiltin,
            SemaTypeParam,
            SemaTypeStruct,
            SemaTypeRef,
            SemaTypeArray,
            SemaTypeTrait
        > data;
    };

    // Structural key for interning
    struct SemaTypeKey
    {
        SemaTypeKind kind{};
        kl::rt::BuiltinTypeExprKind builtin{};
        uint32_t a{0}, b{0}; // binder/param or struct_id/mut etc.
        llvm::SmallVector<SemaTypeId, 4> vec;
        hir::ExprId size_expr{};

        friend bool operator==(const SemaTypeKey& x, const SemaTypeKey& y)
        {
            if (x.kind != y.kind) return false;
            switch (x.kind)
            {
            case SemaTypeKind::Builtin: return x.builtin == y.builtin;
            case SemaTypeKind::TypeParam: return x.a == y.a && x.b == y.b;
            case SemaTypeKind::Struct: return x.a == y.a && x.vec == y.vec;
            case SemaTypeKind::Trait: return x.a == y.a && x.vec == y.vec;
            case SemaTypeKind::Ref: return x.a == y.a && x.b == y.b;
            case SemaTypeKind::Array: return x.a == y.a && x.size_expr == y.size_expr;
            default: return false;
            }
        }
    };

    struct SemaTypeKeyInfo
    {
        static inline SemaTypeKey getEmptyKey()
        {
            SemaTypeKey k{};
            k.kind = static_cast<SemaTypeKind>(0xFF);
            return k;
        }

        static inline SemaTypeKey getTombstoneKey()
        {
            SemaTypeKey k{};
            k.kind = static_cast<SemaTypeKind>(0xFE);
            return k;
        }

        static llvm::hash_code getHashValue(const SemaTypeKey& k)
        {
            using llvm::hash_combine;

            switch (k.kind)
            {
            case SemaTypeKind::Builtin:
                return hash_combine((uint8_t)k.kind, (uint32_t)k.builtin);
            case SemaTypeKind::TypeParam:
                return hash_combine((uint8_t)k.kind, k.a, k.b);
            case SemaTypeKind::Struct:
                {
                    llvm::hash_code h = hash_combine((uint8_t)k.kind, k.a);
                    for (auto t : k.vec) h = hash_combine(h, t);
                    return h;
                }
            case SemaTypeKind::Trait:
                {
                    llvm::hash_code h = hash_combine((uint8_t)k.kind, k.a);
                    for (auto t : k.vec) h = hash_combine(h, t);
                    return h;
                }
            case SemaTypeKind::Ref:
                return hash_combine((uint8_t)k.kind, k.a, k.b);
            case SemaTypeKind::Array:
                return hash_combine((uint8_t)k.kind, k.a, (uint32_t)k.size_expr);
            }
            return hash_combine((uint8_t)k.kind);
        }


        static bool isEqual(const SemaTypeKey& a, const SemaTypeKey& b)
        {
            if (a.kind == (SemaTypeKind)0xFF || a.kind == (SemaTypeKind)0xFE ||
                b.kind == (SemaTypeKind)0xFF || b.kind == (SemaTypeKind)0xFE)
                return a.kind == b.kind;
            return a == b;
        }
    };

    struct TypeInterner
    {
        std::vector<SemaTypeNode> nodes;
        llvm::DenseMap<SemaTypeKey, SemaTypeId, SemaTypeKeyInfo> map;

        SemaTypeId internBuiltin(kl::rt::BuiltinTypeExprKind k)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::Builtin;
            key.builtin = k;

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = (SemaTypeId)nodes.size();
            nodes.push_back(SemaTypeNode{SemaTypeKind::Builtin, SemaTypeBuiltin{k}});
            map.try_emplace(std::move(key), id);
            return id;
        }

        SemaTypeId internTrait(uint32_t trait_id, llvm::ArrayRef<SemaTypeId> args)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::Trait;
            key.a = trait_id;
            key.vec.assign(args.begin(), args.end());

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = (SemaTypeId)nodes.size();

            SemaTypeTrait tr{};
            tr.trait_id = trait_id;
            tr.args.assign(args.begin(), args.end());

            nodes.push_back(SemaTypeNode{SemaTypeKind::Trait, std::move(tr)});
            map.try_emplace(std::move(key), id);
            return id;
        }


        SemaTypeId internTypeParam(uint32_t binder, SemaParamIndex index)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::TypeParam;
            key.a = binder;
            key.b = (uint32_t)index;

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = (SemaTypeId)nodes.size();
            nodes.push_back(SemaTypeNode{
                SemaTypeKind::TypeParam,
                SemaTypeParam{binder, index}
            });
            map.try_emplace(std::move(key), id);
            return id;
        }


        SemaTypeId internStruct(uint32_t sid, llvm::ArrayRef<SemaTypeId> args)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::Struct;
            key.a = sid;
            key.vec.assign(args.begin(), args.end());

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = (SemaTypeId)nodes.size();
            SemaTypeStruct st{};
            st.struct_id = sid;
            st.args.assign(args.begin(), args.end());
            nodes.push_back(SemaTypeNode{SemaTypeKind::Struct, std::move(st)});
            map.try_emplace(std::move(key), id);
            return id;
        }

        SemaTypeId internRef(ast::Mutability mut, SemaTypeId inner)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::Ref;
            key.a = static_cast<uint32_t>(mut);
            key.b = inner;

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = static_cast<SemaTypeId>(nodes.size());
            nodes.push_back(SemaTypeNode{SemaTypeKind::Ref, SemaTypeRef{mut, inner}});
            map.try_emplace(std::move(key), id);
            return id;
        }

        SemaTypeId internArray(SemaTypeId elem, hir::ExprId size_expr)
        {
            SemaTypeKey key{};
            key.kind = SemaTypeKind::Array;
            key.a = elem;
            key.size_expr = size_expr;

            auto it = map.find(key);
            if (it != map.end()) return it->second;

            const SemaTypeId id = static_cast<SemaTypeId>(nodes.size());
            nodes.push_back(SemaTypeNode{SemaTypeKind::Array, SemaTypeArray{elem, size_expr}});
            map.try_emplace(std::move(key), id);
            return id;
        }
    };

    // ============================================================
    // Pass 3 DB (outputs)
    // ============================================================
    struct ResolvedImplHeader
    {
        std::optional<uint32_t> trait_id; // TraitId
        SemaTypeId self_type{kInvalidSemaType};
    };

    struct Pass3DB
    {
        TypeInterner types;

        // alias resolution (only if your pass2 has aliases)
        std::vector<SemaTypeId> alias_target; // [TypeAliasId] -> canonical sema type

        // struct field types
        std::vector<std::vector<SemaTypeId>> struct_field_types; // [StructId] parallel to fields_in_order

        // fn/method signatures (optional, but recommended)
        // Fill once you expose FnHeader param/ret representation.
        std::vector<FnSig> fn_sigs;
        std::vector<MethodSig> method_sigs;

        // impl headers
        std::vector<ResolvedImplHeader> impl_headers; // [ImplId]

        std::vector<Resolve3Error> errors;
    };

    // ============================================================
    // View over Pass 2 DB (ADAPT THESE GETTERS TO YOUR PASS2)
    // ============================================================
    // You can keep your existing pass2 DB; just implement these accessors.
    struct Pass2View
    {
        // required references
        const ModulePassDB& p1;
        const ScopePass2DB& p2; // <- your pass2 db type
        hir::ArenaHolder& holder;

        // --- module scopes
        const ModuleScope& modScope(ModuleId m) const { return p2.module_scopes[(size_t)m]; }

        // --- binder lookup
        const GenericBinder* binder(uint32_t bid) const
        {
            if (bid == kInvalidBinder) return nullptr;
            return &p2.binders[(size_t)bid];
        }

        // --- module path segs
        llvm::ArrayRef<lex::SymId> modulePath(ModuleId m) const
        {
            return p1.pool.view(p1.modules[(size_t)m].package_path);
        }

        // --- resolve nested module: base module + extra module segments
        ModuleId findChildModule(ModuleId base, llvm::ArrayRef<lex::SymId> extraSegs) const
        {
            llvm::SmallVector<lex::SymId, 8> full;
            auto baseSegs = modulePath(base);
            full.append(baseSegs.begin(), baseSegs.end());
            full.append(extraSegs.begin(), extraSegs.end());

            auto mid = p1.tree.find(full);
            return mid.has_value() ? *mid : kInvalidModule;
        }
    };

    // ============================================================
    // Path resolution results (type context)
    // ============================================================
    enum class TypeTargetKind : uint8_t { TypeParam, Struct, TypeAlias, Trait, Invalid };

    struct TypeTarget
    {
        TypeTargetKind kind{TypeTargetKind::Invalid};
        uint32_t id{0}; // StructId/TraitId/TypeAliasId OR TypeParamId
        uint32_t binder{0}; // for TypeParam
        ModuleId module{kInvalidModule};
    };

    // ============================================================
    // Pass 3 resolver
    // ============================================================
    struct Pass3Config
    {
        // Provide SymId for token `self` if you want self:: paths to work.
        // If unset (0), self:: is not treated specially.
        lex::SymId symSelf{};

        // Restrict impl targets to nominal structs (recommended initial rule).
        bool implSelfMustBeStruct = true;

        // If true, allow trait names in type position (usually false unless you have trait objects).
        bool allowTraitAsType = true;
    };

    struct Resolver
    {
        Pass2View view;
        Pass3DB& out;
        Pass3Config cfg;

        // Memoization: (TypeId, envHash) -> SemaTypeId
        struct TypeMemoKey
        {
            ModuleId mod;
            hir::TypeId tid;
            uint64_t env;

            friend bool operator==(const TypeMemoKey& a, const TypeMemoKey& b)
            {
                return a.mod == b.mod && a.tid == b.tid && a.env == b.env;
            }
        };

        struct TypeMemoKeyInfo
        {
            static TypeMemoKey getEmptyKey() { return {kInvalidModule, (hir::TypeId)~0u, 0}; }
            static TypeMemoKey getTombstoneKey() { return {kInvalidModule, (hir::TypeId)~0u - 1, 0}; }

            static llvm::hash_code getHashValue(const TypeMemoKey& k)
            {
                return llvm::hash_combine((uint32_t)k.mod, (uint32_t)k.tid, k.env);
            }

            static bool isEqual(const TypeMemoKey& a, const TypeMemoKey& b)
            {
                if (a.tid == ~0u || a.tid == ~0u - 1 ||
                    b.tid == ~0u || b.tid == ~0u - 1)
                    return a.tid == b.tid;
                return a == b;
            }
        };

        llvm::DenseMap<TypeMemoKey, SemaTypeId, TypeMemoKeyInfo> typeMemo;

        // Alias DFS state (optional)
        enum class AliasState : uint8_t { Unvisited, Visiting, Done };

        std::vector<AliasState> aliasState;

        explicit Resolver(Pass2View v, Pass3DB& o, Pass3Config c)
            : view(v), out(o), cfg(c)
        {
        }

        static uint64_t envHash(const llvm::SmallVectorImpl<uint32_t>& binders)
        {
            uint64_t h = 1469598103934665603ull;
            for (auto b : binders)
            {
                h ^= static_cast<uint64_t>(b);
                h *= 1099511628211ull;
            }
            return h;
        }

        void err(Resolve3ErrKind k, FileId f, ModuleId m, const lex::Loc& loc, lex::SymId name = {},
                 ModuleId other = kInvalidModule) const
        {
            out.errors.push_back(Resolve3Error{
                .kind = k,
                .file = f,
                .module = m,
                .loc = loc,
                .name = name,
                .other_module = other
            });
        }

        const Symbol* findTypeSymbol(ModuleId mod, lex::SymId name) const
        {
            if (mod != kPreludeOwner)
            {
                const auto& ms = view.modScope(mod);
                if (auto it = ms.types.find(name); it != ms.types.end())
                    return &it->second;
            }

            if (auto it = view.p2.prelude.types.find(name); it != view.p2.prelude.types.end())
                return &it->second;

            return nullptr;
        }

        std::optional<TypeTarget> tryResolvePreludeType(lex::SymId name, TypeLookupExpect expect) const
        {
            auto it = view.p2.prelude.types.find(name);
            if (it == view.p2.prelude.types.end())
                return std::nullopt;

            const Symbol& sym = it->second;

            switch (sym.kind)
            {
            case SymKind::Struct:
                if (expect == TypeLookupExpect::TraitOnly) return std::nullopt;
                return TypeTarget{TypeTargetKind::Struct, sym.id, 0, kPreludeOwner};

            case SymKind::TypeAlias:
                if (expect == TypeLookupExpect::TraitOnly) return std::nullopt;
                return TypeTarget{TypeTargetKind::TypeAlias, sym.id, 0, kPreludeOwner};

            case SymKind::Trait:
                if (expect == TypeLookupExpect::TypeOnly) return std::nullopt;
                return TypeTarget{TypeTargetKind::Trait, sym.id, 0, kPreludeOwner};

            default:
                return std::nullopt;
            }
        }


        // -------------------------
        // Resolve a path in TYPE context:
        // - uses binder stack (innermost first)
        // - uses module imports/types
        // - returns a TypeTarget (Struct/Trait/Alias/TypeParam)
        // Also fills TypePath.res and (optionally) ExprPath.res at call sites.
        // -------------------------
        TypeTarget resolveTypeTarget(
            ModuleId curMod,
            FileId file,
            const llvm::SmallVectorImpl<uint32_t>& binderStack,
            hir::Arena& ar,
            hir::ExprId pathExprId,
            const lex::Loc& useLoc,
            TypeLookupExpect expect
        )
        {
            auto errNotFound = [&](lex::SymId name, ModuleId otherMod = kInvalidModule)
            {
                err(expect == TypeLookupExpect::TraitOnly
                        ? Resolve3ErrKind::TraitNotFound
                        : Resolve3ErrKind::UnknownTypeName,
                    file, curMod, useLoc, name, otherMod);
            };

            auto errWrongKindAsType = [&](lex::SymId name)
            {
                err(Resolve3ErrKind::WrongKindUsedAsType, file, curMod, useLoc, name);
            };

            auto errWrongKindAsTrait = [&](lex::SymId name)
            {
                err(Resolve3ErrKind::WrongKindUsedAsTrait, file, curMod, useLoc, name);
            };

            // Expect ExprPath
            auto& ex = ar.exprs[(size_t)pathExprId];
            auto* ep = std::get_if<hir::ExprPath>(&ex.kind);
            if (!ep)
            {
                // Not a path expression
                errNotFound(lex::SymId{});
                return {};
            }

            const auto& segs = ar.paths[(size_t)ep->path].path;
            if (segs.empty())
            {
                errNotFound(lex::SymId{});
                return {};
            }

            // -----------------------------
            // 1) Single-segment: allow TypeParam lookup (only in TypeOnly/Any)
            // -----------------------------
            if (segs.size() == 1)
            {
                const lex::SymId s0 = segs[0];

                // 1a) binder stack lookup (innermost first)
                if (expect != TypeLookupExpect::TraitOnly)
                {
                    for (uint32_t bid : binderStack)
                    {
                        const GenericBinder* b = view.binder(bid);
                        if (!b) continue;

                        auto it = b->params_by_name.find(s0);
                        if (it != b->params_by_name.end())
                        {
                            // NOTE: your params_by_name maps SymId -> SemaParamIndex
                            return TypeTarget{
                                TypeTargetKind::TypeParam,
                                (uint32_t)it->second, // SemaParamIndex encoded in uint32_t
                                bid, // binder id
                                curMod
                            };
                        }
                    }
                }

                // 1b) module-local types
                {
                    const auto& sc = view.modScope(curMod);
                    if (auto itType = sc.types.find(s0); itType != sc.types.end())
                    {
                        const Symbol& sym = itType->second;
                        switch (sym.kind)
                        {
                        case SymKind::Struct:
                            if (expect == TypeLookupExpect::TraitOnly)
                            {
                                errWrongKindAsTrait(s0);
                                return {};
                            }
                            return TypeTarget{TypeTargetKind::Struct, sym.id, 0, curMod};

                        case SymKind::TypeAlias:
                            if (expect == TypeLookupExpect::TraitOnly)
                            {
                                errWrongKindAsTrait(s0);
                                return {};
                            }
                            return TypeTarget{TypeTargetKind::TypeAlias, sym.id, 0, curMod};

                        case SymKind::Trait:
                            if (expect == TypeLookupExpect::TypeOnly)
                            {
                                errWrongKindAsType(s0);
                                return {};
                            }
                            return TypeTarget{TypeTargetKind::Trait, sym.id, 0, curMod};

                        default:
                            // a value symbol in type position
                            if (expect == TypeLookupExpect::TraitOnly) errWrongKindAsTrait(s0);
                            else errWrongKindAsType(s0);
                            return {};
                        }
                    }
                }

                // 1c) prelude fallback
                if (auto pre = tryResolvePreludeType(s0, expect))
                    return *pre;

                // 1d) not found
                errNotFound(s0);
                return {};
            }

            // -----------------------------
            // 2) Multi-segment: determine base module via self:: or import
            // -----------------------------
            ModuleId baseMod = curMod;
            size_t idx = 0;

            if (cfg.symSelf != lex::SymId{} && segs[0] == cfg.symSelf)
            {
                baseMod = curMod;
                idx = 1;
                if (idx >= segs.size())
                {
                    errNotFound(segs[0]);
                    return {};
                }
            }
            else
            {
                const auto& sc = view.modScope(curMod);
                if (auto itImp = sc.imports.find(segs[0]); itImp != sc.imports.end())
                {
                    baseMod = itImp->second.target;
                    idx = 1;

                    if (baseMod == kInvalidModule)
                    {
                        err(Resolve3ErrKind::UnknownImportTargetModule, file, curMod, itImp->second.loc, segs[0]);
                        return {};
                    }
                }
            }

            // -----------------------------
            // 3) Traverse submodules: segs[idx .. last-1)
            // -----------------------------
            ModuleId lookupMod = baseMod;
            if (idx + 1 < segs.size())
            {
                llvm::ArrayRef<lex::SymId> extra(&segs[idx], segs.size() - idx - 1);
                lookupMod = view.findChildModule(baseMod, extra);
                if (lookupMod == kInvalidModule)
                {
                    err(Resolve3ErrKind::UnknownModuleInPath, file, curMod, useLoc, segs[idx], baseMod);
                    return {};
                }
                idx = segs.size() - 1;
            }

            const lex::SymId last = segs[idx];

            // -----------------------------
            // 4) Lookup in type namespace (module + prelude fallback)
            // -----------------------------
            const Symbol* symPtr = findTypeSymbol(lookupMod, last);
            if (!symPtr)
            {
                errNotFound(last, lookupMod);
                return {};
            }

            const Symbol& sym = *symPtr;

            switch (sym.kind)
            {
            case SymKind::Struct:
                if (expect == TypeLookupExpect::TraitOnly)
                {
                    errWrongKindAsTrait(last);
                    return {};
                }
                return TypeTarget{TypeTargetKind::Struct, sym.id, 0, lookupMod};

            case SymKind::TypeAlias:
                if (expect == TypeLookupExpect::TraitOnly)
                {
                    errWrongKindAsTrait(last);
                    return {};
                }
                return TypeTarget{TypeTargetKind::TypeAlias, sym.id, 0, lookupMod};

            case SymKind::Trait:
                if (expect == TypeLookupExpect::TypeOnly)
                {
                    errWrongKindAsType(last);
                    return {};
                }
                return TypeTarget{TypeTargetKind::Trait, sym.id, 0, lookupMod};

            default:
                if (expect == TypeLookupExpect::TraitOnly) errWrongKindAsTrait(last);
                else errWrongKindAsType(last);
                return {};
            }
        }


        // -------------------------
        // Resolve a HIR TypeId -> SemaTypeId
        // Also fills TypePath.res where applicable.
        // -------------------------
        SemaTypeId resolveType(
            ModuleId curMod,
            FileId file,
            const llvm::SmallVectorImpl<uint32_t>& binderStack,
            hir::Arena& ar,
            hir::TypeId tid
        )
        {
            const uint64_t env = envHash(binderStack);
            TypeMemoKey key{curMod, tid, env};

            if (auto itM = typeMemo.find(key); itM != typeMemo.end())
                return itM->second;

            auto& t = ar.types[(size_t)tid];
            SemaTypeId result = kInvalidSemaType;

            std::visit([&]<typename T0>(T0&& node)
            {
                using T = std::decay_t<T0>;

                if constexpr (std::is_same_v<T, hir::TypeBuiltin>)
                {
                    result = out.types.internBuiltin(node.kind);
                }
                else if constexpr (std::is_same_v<T, hir::TypeRef>)
                {
                    SemaTypeId inner = resolveType(curMod, file, binderStack, ar, node.inner);
                    result = out.types.internRef(node.mut, inner);
                }
                else if constexpr (std::is_same_v<T, hir::TypeArray>)
                {
                    SemaTypeId elem = resolveType(curMod, file, binderStack, ar, node.elem);
                    result = out.types.internArray(elem, node.size);
                }
                else if constexpr (std::is_same_v<T, hir::TypePath>)
                {
                    // IMPORTANT POLICY:
                    // - If traits are not first-class types yet, use TypeOnly.
                    // - If you want trait paths to create a SemaTypeKind::Trait node, use Any.
                    const TypeLookupExpect expect = TypeLookupExpect::TypeOnly; // or Any

                    TypeTarget tgt = resolveTypeTarget(
                        curMod, file, binderStack, ar,
                        node.path, node.loc,
                        expect
                    );

                    llvm::SmallVector<SemaTypeId, 4> args;
                    args.reserve(node.targs.size());
                    for (auto ta : node.targs)
                        args.push_back(resolveType(curMod, file, binderStack, ar, ta));

                    switch (tgt.kind)
                    {
                    case TypeTargetKind::TypeParam:
                        node.res.kind = hir::TypeResKind::TypeParam;
                        node.res.id = tgt.id;
                        node.res.module = tgt.module;
                        result = out.types.internTypeParam(
                            tgt.binder,
                            static_cast<SemaParamIndex>(tgt.id) // tgt.id is SemaParamIndex in uint32_t
                        );
                        break;

                    case TypeTargetKind::Struct:
                        node.res.kind = hir::TypeResKind::Struct;
                        node.res.id = tgt.id;
                        node.res.module = tgt.module;
                        result = out.types.internStruct(tgt.id, args);
                        break;

                    case TypeTargetKind::Trait:
                        node.res.kind = hir::TypeResKind::Trait;
                        node.res.id = tgt.id;
                        node.res.module = tgt.module;
                        result = out.types.internTrait(tgt.id, args);
                        break;

                    case TypeTargetKind::TypeAlias:
                        // If you do not support aliases yet, keep invalid or add alias expansion.
                        // For now:
                        result = kInvalidSemaType;
                        break;

                    default:
                        result = kInvalidSemaType;
                        break;
                    }
                }
                else
                {
                    // Unhandled type node kinds -> invalid
                    result = kInvalidSemaType;
                }
            }, t.kind);

            typeMemo.try_emplace(key, result);
            return result;
        }

        // -------------------------
        // Alias resolution (optional)
        // Requires your pass2 to provide alias records with: owner module + aliased TypeId.
        // If your pass2 currently rejects aliases due to missing name, you can skip this phase.
        // -------------------------
        void ensureAliasStorage()
        {
            // If your pass2 has aliases: out.alias_target.resize(p2.aliases.size())
            out.alias_target.resize(view.p2.aliases.size(), kInvalidSemaType);
            aliasState.resize(view.p2.aliases.size(), AliasState::Unvisited);
        }

        SemaTypeId resolveAlias(uint32_t aliasId)
        {
            if ((size_t)aliasId >= aliasState.size()) return kInvalidSemaType;

            if (aliasState[(size_t)aliasId] == AliasState::Done)
                return out.alias_target[(size_t)aliasId];

            if (aliasState[(size_t)aliasId] == AliasState::Visiting)
            {
                // cycle
                auto& ar = view.holder.arenas_[view.p2.aliases[(size_t)aliasId].owner];
                (void)ar;
                // best-effort loc:
                err(Resolve3ErrKind::AliasCycle,
                    view.p1.modules[(size_t)view.p2.aliases[(size_t)aliasId].owner].file,
                    view.p2.aliases[(size_t)aliasId].owner,
                    view.p2.aliases[(size_t)aliasId].loc);
                return kInvalidSemaType;
            }

            aliasState[(size_t)aliasId] = AliasState::Visiting;

            const auto& a = view.p2.aliases[(size_t)aliasId];
            const ModuleId mod = a.owner;
            const FileId file = view.p1.modules[(size_t)mod].file;
            hir::Arena& ar = view.holder.arenas_[(size_t)mod];

            llvm::SmallVector<uint32_t, 2> binders;
            if (a.binder != kInvalidBinder) binders.push_back(a.binder);

            SemaTypeId rhs = resolveType(mod, file, binders, ar, a.aliased);
            out.alias_target[(size_t)aliasId] = rhs;

            aliasState[(size_t)aliasId] = AliasState::Done;
            return rhs;
        }

        // -------------------------
        // Impl self-type key extraction (restrict to nominal struct)
        // -------------------------
        struct ImplSelfKey
        {
            uint32_t struct_id{};
            llvm::SmallVector<SemaTypeId, 4> args;

            friend bool operator==(const ImplSelfKey& a, const ImplSelfKey& b)
            {
                return a.struct_id == b.struct_id && a.args == b.args;
            }
        };

        struct ImplKey
        {
            uint32_t trait_id{};
            ImplSelfKey self;

            friend bool operator==(const ImplKey& a, const ImplKey& b)
            {
                return a.trait_id == b.trait_id && a.self == b.self;
            }
        };

        struct ImplKeyInfo
        {
            static ImplKey getEmptyKey()
            {
                return {~0u, ImplSelfKey{~0u, {}}};
            }

            static ImplKey getTombstoneKey()
            {
                return {~0u - 1, ImplSelfKey{~0u - 1, {}}};
            }

            static llvm::hash_code getHashValue(const ImplKey& k)
            {
                llvm::hash_code h = llvm::hash_combine(k.trait_id, k.self.struct_id);
                for (auto a : k.self.args) h = llvm::hash_combine(h, a);
                return h;
            }

            static bool isEqual(const ImplKey& a, const ImplKey& b)
            {
                if (a.trait_id == ~0u || a.trait_id == (~0u - 1) ||
                    b.trait_id == ~0u || b.trait_id == (~0u - 1))
                    return a.trait_id == b.trait_id;
                return a == b;
            }
        };

        std::optional<ImplSelfKey> extractStructSelfKey(SemaTypeId t) const
        {
            if (t == kInvalidSemaType) return std::nullopt;
            const auto& n = out.types.nodes[(size_t)t];
            if (n.kind != SemaTypeKind::Struct) return std::nullopt;

            const auto& st = std::get<SemaTypeStruct>(n.data);
            ImplSelfKey k{};
            k.struct_id = st.struct_id;
            k.args = st.args;
            return k;
        }

        // ============================================================
        // RUN phases
        // ============================================================
        void phaseAliases()
        {
            if (view.p2.aliases.empty()) return;
            ensureAliasStorage();
            for (uint32_t aid = 0; aid < (uint32_t)view.p2.aliases.size(); ++aid)
                (void)resolveAlias(aid);
        }

        void phaseStructFields()
        {
            out.struct_field_types.resize(view.p2.structs.size());
            for (uint32_t sid = 0; sid < (uint32_t)view.p2.structs.size(); ++sid)
            {
                const auto& s = view.p2.structs[(size_t)sid];
                if (s.intrinsic) continue;
                const ModuleId mod = s.owner;
                const FileId file = view.p1.modules[(size_t)mod].file;
                hir::Arena& ar = view.holder.arenas_[(size_t)mod];

                llvm::SmallVector<uint32_t, 2> binders;
                if (s.binder != kInvalidBinder) binders.push_back(s.binder);

                auto& outVec = out.struct_field_types[(size_t)sid];
                outVec.reserve(s.fields_in_order.size());

                for (auto fId : s.fields_in_order)
                {
                    const auto& f = ar.field_decls[(size_t)fId];
                    SemaTypeId ft = resolveType(mod, file, binders, ar, f.type);
                    outVec.push_back(ft);
                }
            }
        }

        static ReceiverKind toReceiverKind(ast::SelfParamKind k)
        {
            switch (k)
            {
            case ast::SelfParamKind::Value: return ReceiverKind::Value;
            case ast::SelfParamKind::Ref: return ReceiverKind::RefImm;
            case ast::SelfParamKind::RefMut: return ReceiverKind::RefMut;
            default: return ReceiverKind::None;
            }
        }

        void phaseFnSigs()
        {
            out.fn_sigs.clear();
            out.fn_sigs.reserve(view.p2.fns.size());

            auto set_void_ret = [&]()
            {
                // Adjust if your builtin enum differs
                return out.types.internBuiltin(kl::rt::BuiltinTypeExprKind::Void);
            };

            for (uint32_t fid = 0; fid < (uint32_t)view.p2.fns.size(); ++fid)
            {
                const auto& fr = view.p2.fns[(size_t)fid];
                const ModuleId mod = fr.owner;

                // IMPORTANT: prelude/intrinsic functions cannot read HIR via holder.arenas_[~0u]
                // If you add intrinsic/prelude fns later, either:
                //   (a) store them in pass2 as "intrinsic" and build sigs from intrinsic metadata, or
                //   (b) keep a dedicated prelude arena.
                if (mod == kPreludeOwner)
                {
                    // For now: skip (or build from intrinsic DB if you have it)
                    continue;
                }

                // Safety: module index must exist in arenas_
                if ((size_t)mod >= view.holder.arenas_.size())
                {
                    // You may want to emit an internal error here
                    continue;
                }

                const FileId file = view.p1.modules[(size_t)mod].file;
                hir::Arena& ar = view.holder.arenas_[(size_t)mod];

                // Read the decl by DeclId stored in pass2
                const auto& decl = ar.decls[(size_t)fr.decl_id];

                CallableSig cs{};
                cs.binder = fr.binder;
                cs.receiver.kind = ReceiverKind::None;
                cs.receiver.explicit_type.reset();
                cs.loc = fr.loc;

                // binder stack for resolving TypeParam in signature
                llvm::SmallVector<uint32_t, 4> binders;
                if (fr.binder != kInvalidBinder) binders.push_back(fr.binder);

                auto resolve_ret = [&](hir::TypeId ret_tid) -> SemaTypeId
                {
                    return resolveType(mod, file, binders, ar, ret_tid);
                };

                std::visit([&]<typename T0>(T0 const& node)
                {
                    using T = std::decay_t<T0>;

                    if constexpr (std::is_same_v<T, hir::FnDecl>)
                    {
                        cs.params.clear();
                        cs.params.reserve(node.header.params.size());

                        bool sawSelf = false;

                        for (auto pid : node.header.params)
                        {
                            const auto& param = ar.params[(size_t)pid]; // <-- FIX #1

                            std::visit([&]<typename P0>(P0 const& pk)
                            {
                                using P = std::decay_t<P0>;

                                if constexpr (std::is_same_v<P, hir::ParamNamed>)
                                {
                                    ParamSig ps{};
                                    ps.name = pk.name;
                                    ps.loc = pk.loc;
                                    ps.type = resolveType(mod, file, binders, ar, pk.type);
                                    cs.params.push_back(ps);
                                }
                                else if constexpr (std::is_same_v<P, hir::ParamSelf>)
                                {
                                    if (sawSelf)
                                    {
                                        // Optional: emit a diagnostic (Pass2 is also a good place)
                                        // err(Resolve3ErrKind::..., file, mod, pk.loc, pk.name);
                                        return;
                                    }
                                    sawSelf = true;

                                    cs.receiver.kind = toReceiverKind(pk.kind);
                                    cs.receiver.loc = pk.loc;

                                    if (pk.explicit_type.has_value())
                                    {
                                        cs.receiver.explicit_type =
                                            resolveType(mod, file, binders, ar, *pk.explicit_type);
                                    }
                                }
                            }, param.kind);
                        }

                        // Return type
                        if (node.header.return_type.has_value())
                            cs.ret = resolve_ret(*node.header.return_type);
                        else
                            cs.ret = set_void_ret();
                    }
                    else if constexpr (std::is_same_v<T, hir::LoadFnDecl>)
                    {
                        cs.params.clear();
                        cs.receiver.kind = ReceiverKind::None;
                        cs.receiver.explicit_type.reset();

                        if (node.header.return_type.has_value())
                            cs.ret = resolve_ret(*node.header.return_type);
                        else
                            cs.ret = set_void_ret();
                    }
                    else
                    {
                        // Should not happen if pass2 stored only fn decls
                        cs.params.clear();
                        cs.ret = set_void_ret();
                    }
                }, decl.kind);

                FnSig sig{};
                sig.fn_id = fid;
                sig.owner = mod;
                sig.sig = std::move(cs);
                sig.exported = fr.exported;
                sig.is_load = fr.is_load;
                sig.hir_decl = fr.decl_id;

                out.fn_sigs.push_back(std::move(sig));
            }
        }


        void phaseImplHeaders()
        {
            out.impl_headers.resize(view.p2.impls.size());

            llvm::DenseMap<ImplKey, uint32_t, ImplKeyInfo> seen; // ImplKey -> ImplId

            for (uint32_t iid = 0; iid < (uint32_t)view.p2.impls.size(); ++iid)
            {
                const auto& im = view.p2.impls[(size_t)iid];
                const ModuleId mod = im.owner;
                const FileId file = view.p1.modules[(size_t)mod].file;
                hir::Arena& ar = view.holder.arenas_[static_cast<size_t>(mod)];

                llvm::SmallVector<uint32_t, 2> binders;
                if (im.binder != kInvalidBinder) binders.push_back(im.binder);

                // 1) Resolve trait path (if any)
                std::optional<uint32_t> traitId;
                if (im.trait_path.has_value())
                {
                    TypeTarget tgt = resolveTypeTarget(mod, file, binders, ar, *im.trait_path, im.loc, /*expectTrait=*/
                                                       TypeLookupExpect::TraitOnly);
                    if (tgt.kind == TypeTargetKind::Trait)
                        traitId = tgt.id;
                    else
                    {
                        // error already emitted
                        traitId.reset();
                    }
                }

                // 2) Resolve self type
                SemaTypeId selfT = resolveType(mod, file, binders, ar, im.for_type);

                out.impl_headers[static_cast<size_t>(iid)] = ResolvedImplHeader{traitId, selfT};

                // 3) Validate impl target + duplicate check only for trait impls
                if (traitId.has_value())
                {
                    // enforce nominal struct for now
                    auto selfKey = extractStructSelfKey(selfT);
                    if (!selfKey.has_value())
                    {
                        err(Resolve3ErrKind::InvalidImplSelfType, file, mod, im.loc);
                        continue;
                    }

                    ImplKey key{*traitId, *selfKey};

                    auto it = seen.find(key);
                    if (it != seen.end())
                    {
                        // duplicate impl
                        err(Resolve3ErrKind::DuplicateImpl, file, mod, im.loc);
                    }
                    else
                    {
                        seen.try_emplace(std::move(key), iid);
                    }
                }
            }
        }
    };

    // ============================================================
    // Public entry point
    // ============================================================
    inline Pass3DB runPass3Resolve(const ModulePassDB& p1,
                                   const ScopePass2DB& p2,
                                   hir::ArenaHolder& holder,
                                   Pass3Config cfg = {})
    {
        Pass3DB out;

        Pass2View v{p1, p2, holder};
        Resolver r(v, out, cfg);

        // Phase order: aliases -> struct fields -> impl headers
        // You can insert fn/method signature phases once FnHeader is exposed.
        r.phaseAliases();
        r.phaseStructFields();
        r.phaseFnSigs();
        r.phaseImplHeaders();

        return out;
    }
} // namespace sema

#endif // INZ_SEMA_PASS3_RESOLVE_HPP
