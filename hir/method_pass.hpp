#ifndef INZ_SEMA_PASS4_BUILD_HPP
#define INZ_SEMA_PASS4_BUILD_HPP

#include <vector>
#include <optional>

#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/Hashing.h>

#include "sema/decl_bind_pass.hpp"
#include "sema/module_import_pass.hpp"   // ModulePassDB, ModuleId, FileId, kInvalidModule
#include "sema/scope_pass.hpp"          // ScopePass2DB (your Pass2 DB)

// Pass 4 goal:
// - NO name/type resolution (that is Pass 3).
// - Consume Pass2 + Pass3 outputs and build method/impl indices:
//   * trait impl -> vtable slots (trait method order -> implementing method)
//   * inherent methods -> lookup table (Self struct -> method name -> method id)
// - Validate trait impl completeness (missing required trait methods).
// - Optionally report duplicates (even if Pass3 already did).

namespace sema
{
    // ============================================================
    // Pass 4 errors
    // ============================================================
    enum class Pass4ErrKind : uint8_t
    {
        InvalidImplHeader,              // Pass3 did not produce a usable self_type for an impl
        ImplSelfNotStruct,              // inherent method indexing requires nominal struct self
        DuplicateTraitImplForType,      // (trait,self_type) repeated
        MissingTraitImplMethod,         // trait method not implemented in impl
        DuplicateInherentMethod         // same (struct_id, method_name) defined twice
        // (Extend later:)
        // SignatureMismatch,
        // ReceiverMismatch,
        // ExtraImplMethodNotInTrait,
    };

    struct Pass4Error
    {
        Pass4ErrKind kind{};
        FileId file{};
        ModuleId module{kInvalidModule};
        lex::Loc loc{};
        lex::SymId name{};              // method name or type name (best-effort)
        uint32_t a{~0u};                // e.g. TraitId / ImplId / StructId (best-effort)
        uint32_t b{~0u};                // e.g. MethodId / other (best-effort)
    };

    // ============================================================
    // Pass 4 outputs
    // ============================================================

    // For trait impls we key by (trait_id, self_type) where self_type is already a SemaTypeId.
    struct TraitImplKey
    {
        uint32_t trait_id{};
        SemaTypeId self_type{kInvalidSemaType};

        friend bool operator==(const TraitImplKey& x, const TraitImplKey& y)
        {
            return x.trait_id == y.trait_id && x.self_type == y.self_type;
        }
    };

    struct TraitImplKeyInfo
    {
        static TraitImplKey getEmptyKey() { return {~0u, kInvalidSemaType}; }
        static TraitImplKey getTombstoneKey() { return {~0u - 1, (SemaTypeId)(~0u)}; }

        static llvm::hash_code getHashValue(const TraitImplKey& k)
        {
            return llvm::hash_combine(k.trait_id, (uint32_t)k.self_type);
        }

        static bool isEqual(const TraitImplKey& a, const TraitImplKey& b)
        {
            if (a.trait_id == ~0u || a.trait_id == (~0u - 1) ||
                b.trait_id == ~0u || b.trait_id == (~0u - 1))
                return a.trait_id == b.trait_id;
            return a == b;
        }
    };

    // Inherent lookup key: (struct_id, method_name).
    // NOTE: if you later allow overloading, add arity/receiver/where-clause fingerprint here.
    struct InherentMethodKey
    {
        uint32_t struct_id{};
        lex::SymId name{};

        friend bool operator==(const InherentMethodKey& x, const InherentMethodKey& y)
        {
            return x.struct_id == y.struct_id && x.name == y.name;
        }
    };

    struct InherentMethodKeyInfo
    {
        static InherentMethodKey getEmptyKey() { return {~0u, lex::SymId{}}; }
        static InherentMethodKey getTombstoneKey() { return {~0u - 1, lex::SymId{(uint32_t)~0u}}; }

        static llvm::hash_code getHashValue(const InherentMethodKey& k)
        {
            return llvm::hash_combine(k.struct_id, (uint32_t)k.name);
        }

        static bool isEqual(const InherentMethodKey& a, const InherentMethodKey& b)
        {
            if (a.struct_id == ~0u || a.struct_id == (~0u - 1) ||
                b.struct_id == ~0u || b.struct_id == (~0u - 1))
                return a.struct_id == b.struct_id;
            return a == b;
        }
    };

    struct Pass4DB
    {
        // For each ImplId (Pass2), if it is a trait impl, we store vtable slots aligned to TraitRec.methods order.
        // If it is inherent, the vector is empty.
        std::vector<llvm::SmallVector<MethodId, 8>> impl_vtables; // [ImplId] -> slots (MethodId)

        // Index for coherence/lookup:
        // (trait_id, self_type) -> ImplId
        llvm::DenseMap<TraitImplKey, ImplId, TraitImplKeyInfo> trait_impl_index;

        // Inherent method index:
        // (struct_id, method_name) -> MethodId
        llvm::DenseMap<InherentMethodKey, MethodId, InherentMethodKeyInfo> inherent_method_index;

        std::vector<Pass4Error> errors;
    };

    // ============================================================
    // Pass 4 builder (consumes Pass2 + Pass3; does not run Pass3)
    // ============================================================
    struct Pass4Builder
    {
        const ModulePassDB& p1;
        const ScopePass2DB& p2;
        const Pass3DB& p3;
        Pass4DB& out;

        explicit Pass4Builder(const ModulePassDB& p1_, const ScopePass2DB& p2_, const Pass3DB& p3_, Pass4DB& o)
            : p1(p1_), p2(p2_), p3(p3_), out(o)
        {
        }

        void err(Pass4ErrKind k, ModuleId m, const lex::Loc& loc,
                 lex::SymId name = {}, uint32_t a = ~0u, uint32_t b = ~0u)
        {
            FileId file{};
            if (m != kPreludeOwner && (size_t)m < p1.modules.size())
                file = p1.modules[(size_t)m].file;

            out.errors.push_back(Pass4Error{
                .kind = k,
                .file = file,
                .module = m,
                .loc = loc,
                .name = name,
                .a = a,
                .b = b
            });
        }

        std::optional<uint32_t> extractStructIdFromSema(SemaTypeId t) const
        {
            if (t == kInvalidSemaType) return std::nullopt;
            if ((size_t)t >= p3.types.nodes.size()) return std::nullopt;

            const auto& n = p3.types.nodes[(size_t)t];
            if (n.kind != SemaTypeKind::Struct) return std::nullopt;

            const auto& st = std::get<SemaTypeStruct>(n.data);
            return st.struct_id;
        }

        // ------------------------------------------------------------
        // Phase: Build indices and vtables
        // ------------------------------------------------------------
        void run()
        {
            // Defensive sizing
            out.impl_vtables.clear();
            out.impl_vtables.resize(p2.impls.size());

            // Build indices
            out.trait_impl_index.clear();
            out.inherent_method_index.clear();

            // If Pass3 did not compute impl headers, this is an internal pipeline error.
            // We will still attempt to proceed safely.
            if (p3.impl_headers.size() != p2.impls.size())
            {
                // Best-effort: mark all impl headers invalid (do not crash).
                for (uint32_t iid = 0; iid < (uint32_t)p2.impls.size(); ++iid)
                {
                    const auto& im = p2.impls[(size_t)iid];
                    err(Pass4ErrKind::InvalidImplHeader, im.owner, im.loc, {}, /*a=*/iid);
                }
                return;
            }

            // --------------------------------------------------------
            // For each impl:
            // - if trait impl: build vtable slots and index (trait,self_type)->impl
            // - else inherent: index methods under the nominal struct id
            // --------------------------------------------------------
            for (uint32_t iid = 0; iid < (uint32_t)p2.impls.size(); ++iid)
            {
                const auto& im = p2.impls[(size_t)iid];
                const auto& hdr = p3.impl_headers[(size_t)iid];

                const ModuleId mod = im.owner;

                // self type must exist
                if (hdr.self_type == kInvalidSemaType)
                {
                    err(Pass4ErrKind::InvalidImplHeader, mod, im.loc, {}, /*a=*/iid);
                    continue;
                }

                // ---- Trait impl ----
                if (hdr.trait_id.has_value())
                {
                    const uint32_t traitId = *hdr.trait_id;

                    // Index coherence key
                    {
                        TraitImplKey key{traitId, hdr.self_type};
                        auto it = out.trait_impl_index.find(key);
                        if (it != out.trait_impl_index.end())
                        {
                            // Even if Pass3 already reported DuplicateImpl, keep Pass4 robust.
                            err(Pass4ErrKind::DuplicateTraitImplForType, mod, im.loc, {}, /*a=*/traitId, /*b=*/iid);
                        }
                        else
                        {
                            out.trait_impl_index.try_emplace(key, (ImplId)iid);
                        }
                    }

                    // Build vtable slots in trait method order
                    if ((size_t)traitId >= p2.traits.size())
                    {
                        // Pass3 said trait id exists, but DB mismatch; treat as invalid.
                        err(Pass4ErrKind::InvalidImplHeader, mod, im.loc, {}, /*a=*/iid);
                        continue;
                    }

                    const auto& tr = p2.traits[(size_t)traitId];
                    auto& slots = out.impl_vtables[(size_t)iid];
                    slots.clear();
                    slots.reserve(tr.methods.size());

                    for (MethodId tm : tr.methods)
                    {
                        if ((size_t)tm >= p2.methods.size())
                            continue; // defensive

                        const auto& traitMeth = p2.methods[(size_t)tm];
                        const lex::SymId mname = traitMeth.name;

                        auto itM = im.method_by_name.find(mname);
                        if (itM == im.method_by_name.end())
                        {
                            err(Pass4ErrKind::MissingTraitImplMethod, mod, im.loc,
                                mname, /*a=*/traitId, /*b=*/(uint32_t)tm);
                            // Fill with invalid to keep slot count stable.
                            slots.push_back(kInvalidMethod);
                            continue;
                        }

                        slots.push_back((MethodId)itM->second);
                    }

                    // Optional (future):
                    // - validate signature compatibility using p3.method_sigs (if you fill them in Pass3)
                    // - validate receiver kind compatibility
                    continue;
                }

                // ---- Inherent impl ----
                // We require nominal struct self to index methods; otherwise, you need a more general key.
                auto sidOpt = extractStructIdFromSema(hdr.self_type);
                if (!sidOpt.has_value())
                {
                    err(Pass4ErrKind::ImplSelfNotStruct, mod, im.loc, {}, /*a=*/iid);
                    continue;
                }
                const uint32_t selfSid = *sidOpt;

                // Index each method under (self struct id, name)
                for (MethodId mid : im.methods)
                {
                    if ((size_t)mid >= p2.methods.size())
                        continue; // defensive

                    const auto& mrec = p2.methods[(size_t)mid];
                    InherentMethodKey k{selfSid, mrec.name};

                    auto it = out.inherent_method_index.find(k);
                    if (it != out.inherent_method_index.end())
                    {
                        err(Pass4ErrKind::DuplicateInherentMethod, mod, mrec.loc,
                            mrec.name, /*a=*/selfSid, /*b=*/(uint32_t)mid);
                        continue;
                    }

                    out.inherent_method_index.try_emplace(k, mid);
                }
            }
        }
    };

    // ============================================================
    // Public entry
    // ============================================================
    inline Pass4DB runPass4Build(const ModulePassDB& p1,
                                 const ScopePass2DB& p2,
                                 const Pass3DB& p3)
    {
        Pass4DB out;
        Pass4Builder b(p1, p2, p3, out);
        b.run();

        return out;
    }

} // namespace sema

#endif // INZ_SEMA_PASS4_BUILD_HPP
