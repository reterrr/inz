#ifndef INZ_PRELUDE_INJECTOR_HPP
#define INZ_PRELUDE_INJECTOR_HPP

#include <initializer_list>
#include "sema/scope_pass.hpp" // include the correct pass2 header

namespace sema
{
    class PreludeInjector final
    {
    public:
        explicit PreludeInjector(ScopePass2DB& db)
            : db_(db)
        {
        }

        StructId addIntrinsicType(lex::SymId name,
                                  std::initializer_list<lex::SymId> typeParams = {},
                                  bool exported = true,
                                  lex::Loc loc = {}) const
        {
            // Idempotent: if already present, return existing id
            if (auto it = db_.prelude.types.find(name); it != db_.prelude.types.end())
                return it->second.id;

            const BinderId binder = makeIntrinsicBinder(BinderOwnerKind::Struct,
                                                        /*owner_id*/ (uint32_t)db_.structs.size(),
                                                        loc,
                                                        typeParams);

            const StructId sid = (StructId)db_.structs.size();

            StructRec r{};
            r.owner = kPreludeOwner;
            r.decl_id = ~0u;
            r.name = name;
            r.loc = loc;
            r.exported = exported;
            r.binder = binder;
            r.intrinsic = true;
            r.unit_index = 0;
            r.arena_index = 0;

            db_.structs.push_back(std::move(r));

            db_.prelude.types.try_emplace(name, Symbol{
                                              .kind = SymKind::Struct,
                                              .id = (uint32_t)sid,
                                              .arity = (uint8_t)typeParams.size(),
                                              .loc = loc,
                                              .exported = exported,
                                              .intrinsic = true
                                          });

            return sid;
        }

        TraitId addIntrinsicTrait(lex::SymId name,
                                  std::initializer_list<lex::SymId> typeParams = {},
                                  bool exported = true,
                                  lex::Loc loc = {}) const
        {
            if (auto it = db_.prelude.types.find(name); it != db_.prelude.types.end())
                return (TraitId)it->second.id;

            const BinderId binder = makeIntrinsicBinder(BinderOwnerKind::Trait,
                                                        /*owner_id*/ (uint32_t)db_.traits.size(),
                                                        loc,
                                                        typeParams);

            const TraitId tid = (TraitId)db_.traits.size();

            TraitRec r{};
            r.owner = kPreludeOwner;
            r.decl_id = (hir::DeclId)~0u;
            r.name = name;
            r.loc = loc;
            r.exported = exported;
            r.binder = binder;
            r.intrinsic = true;
            r.unit_index = 0;
            r.arena_index = 0;

            db_.traits.push_back(std::move(r));

            db_.prelude.types.try_emplace(name, Symbol{
                                              .kind = SymKind::Trait,
                                              .id = (uint32_t)tid,
                                              .arity = (uint8_t)typeParams.size(),
                                              .loc = loc,
                                              .exported = exported,
                                              .intrinsic = true
                                          });

            return tid;
        }

    private:
        ScopePass2DB& db_;

        // Intrinsic binder: sema-local only (no HIR ids, no diagnostics needed).
        BinderId makeIntrinsicBinder(BinderOwnerKind ok,
                                     uint32_t owner_id,
                                     const lex::Loc& loc,
                                     std::initializer_list<lex::SymId> params) const
        {
            if (params.size() == 0)
                return kInvalidBinder;

            GenericBinder b{};
            b.owner_kind = ok;
            b.owner_id = owner_id;
            b.loc = loc;

            SemaParamIndex idx = 0;
            for (lex::SymId p : params)
            {
                // Ignore duplicates (prelude bug); keep first
                if (b.params_by_name.find(p) != b.params_by_name.end())
                    continue;

                b.params_by_name.try_emplace(p, idx++);
                b.params_in_order.push_back(p);
            }

            const BinderId bid = (BinderId)db_.binders.size();
            db_.binders.push_back(std::move(b));
            return bid;
        }
    };
} // namespace sema

#endif // INZ_PRELUDE_INJECTOR_HPP
