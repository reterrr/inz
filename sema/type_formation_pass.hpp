//
// Created by yhwach on 12/29/25.
//

#ifndef INZ_TYPE_FORMATION_PASS_HPP
#define INZ_TYPE_FORMATION_PASS_HPP
#include <llvm/ADT/SmallVector.h>

#include "decl_bind_pass.hpp"
#include "module_import_pass.hpp"
#include "scope_pass.hpp"
#include "hir/arena_holder.hpp"
#include "hir/ids.hpp"

namespace sema
{
    // ----------------------------
    // Errors
    // ----------------------------
    enum class TypeFormErrKind : uint8_t
    {
        UnresolvedType, // TypePath.res.kind == Error
        NonTypeDefInTypePos, // DefKind not a type (should not happen if Pass2 type-namespace is correct)
        WrongTypeArgCount, // arity mismatch
        TypeParamWithTypeArgs, // T::<...> not allowed
        ArraySizeNotConstInt, // TypeArray.size is not ExprLitInt (minimal rule)
        BadTypePathExpr, // TypePath.path not ExprPath (sanity; should be caught in pass4)
        BadStructLitTypeExpr // ExprLitStruct.type not ExprPath (if you check it here)
    };

    struct TypeFormError
    {
        TypeFormErrKind kind{};
        hir::ModuleId module{};
        lex::Loc loc{};
    };

    struct TypeFormPassDB
    {
        llvm::SmallVector<TypeFormError, 64> errors;
    };

    // ----------------------------
    // Builder
    // ----------------------------
    struct TypeFormBuilder
    {
        hir::ArenaHolder& holder;
        ModulePassDB& pass1;
        ScopePassDB& pass2;
        DeclBindPassDB& pass3;
        TypeFormPassDB& out;

        // ---------- PASS 3 accessors (ADAPT to your real DeclBindPassDB layout) ----------

        // Must return the GenericScopeId for a given *type decl* (struct/trait/typealias),
        // or std::nullopt if it has no generic params.
        std::optional<GenericScopeId> declGeneric(ModuleId owner, hir::DeclId did) const
        {
            // ADAPT:
            // return pass3.perModule[(size_t)owner].decl_generic[(size_t)did];
            return pass3.perModule[(size_t)owner].genericByDecl[(size_t)did];
        }

        const GenericScopeRec& genericScope(GenericScopeId gid) const
        {
            // ADAPT:
            return pass3.generics[(size_t)gid];
        }

        // ---------- expected arity for a DefId ----------
        std::optional<uint32_t> expectedArityForTypeDef(DefId def) const
        {
            if ((size_t)def >= pass2.defs.size())
                return std::nullopt;

            const auto dref = pass2.defs[(size_t)def];

            // Only types should be in the type namespace; still validate defensively.
            switch (dref.kind)
            {
            case DefKind::Struct:
                {
                    const auto& si = pass2.structs[(size_t)dref.index];
                    const ModuleId owner = si.owner;
                    const hir::DeclId did = si.decl;

                    if (auto g = declGeneric(owner, did))
                        return (uint32_t)genericScope(*g).ordered.size();
                    return 0u;
                }
            case DefKind::Trait:
                {
                    const auto& ti = pass2.traits[(size_t)dref.index];
                    const ModuleId owner = ti.owner;
                    const hir::DeclId did = ti.decl;

                    if (auto g = declGeneric(owner, did))
                        return (uint32_t)genericScope(*g).ordered.size();
                    return 0u;
                }
            case DefKind::TypeAlias:
                {
                    const auto& ai = pass2.typeAliases[(size_t)dref.index];
                    const ModuleId owner = ai.owner;
                    const hir::DeclId did = ai.decl;

                    if (auto g = declGeneric(owner, did))
                        return (uint32_t)genericScope(*g).ordered.size();
                    return 0u;
                }

            // Not valid in type position
            default:
                return std::nullopt;
            }
        }

        bool defIsType(DefId def) const
        {
            if ((size_t)def >= pass2.defs.size())
                return false;

            const auto dref = pass2.defs[(size_t)def];
            return dref.kind == DefKind::Struct ||
                dref.kind == DefKind::Trait ||
                dref.kind == DefKind::TypeAlias;
        }

        // ---------- HIR helper: ensure tp.path is ExprPath if you want to sanity-check ----------
        static bool isExprPath(hir::Arena& ar, hir::ExprId eid)
        {
            auto& e = ar.exprs[(size_t)eid];
            return std::holds_alternative<hir::ExprPath>(e.kind);
        }

        // ---------- minimal const-int check for TypeArray.size ----------
        static bool isConstIntExpr(hir::Arena& ar, hir::ExprId eid)
        {
            auto& e = ar.exprs[(size_t)eid];
            return std::holds_alternative<hir::ExprLitInt>(e.kind);
        }
    };

    // ----------------------------
    // Metadata
    // ----------------------------
    struct TypeFormMetaData
    {
        TypeFormBuilder& b;
        ModuleId module{};
        hir::BlockId block{~0u}; // only to help block visitor if your iterator doesn't pass IDs
    };

    // ============================================================
    // Deferring visitor (manual; no Base::visit)
    // Traverses ONLY what is needed to reach types.
    // ============================================================
    template <typename It>
    struct TypeFormDeferringVisitor final : hir::CoreDeferringVisitor<It, TypeFormMetaData>
    {
        using Base = hir::CoreDeferringVisitor<It, TypeFormMetaData>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        // ---- module ----
        void visit(hir::Module& m, TypeFormMetaData md) override
        {
            for (int32_t i = (int32_t)m.decls.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::decls, m.decls[(size_t)i], md);
        }

        // ---- decls ----
        void visit(hir::FnDecl& f, TypeFormMetaData md) override
        {
            // ADAPT if FnHeader contains return type / param types stored as TypeId somewhere.
            // If you have those, defer them here.
            //
            // Example:
            // it_.defer(hir::ArenaKinds::types, f.header.ret, md);
            // for each param: defer param.type TypeId

            md.block = f.body;
            it_.defer(hir::ArenaKinds::blocks, f.body, md);
        }

        void visit(hir::StructDecl& s, TypeFormMetaData md) override
        {
            for (int32_t i = (int32_t)s.fields.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::field_decls, s.fields[(size_t)i], md);
        }

        void visit(hir::TypeAliasDecl& a, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::types, a.aliased, md);
        }

        void visit(hir::TraitDecl& tr, TypeFormMetaData md) override
        {
            for (int32_t i = (int32_t)tr.methods.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::methods, tr.methods[(size_t)i], md);
        }

        void visit(hir::ImplDecl& im, TypeFormMetaData md) override
        {
            // `for_type` is a TypeId => must be formed
            it_.defer(hir::ArenaKinds::types, im.for_type, md);

            // trait_path is optional ExprId but semantically a type/trait path.
            // Pass5 does not validate it as a type here unless you model it explicitly as TypePath.
            if (im.trait_path)
                it_.defer(hir::ArenaKinds::exprs, *im.trait_path, md);

            for (int32_t i = (int32_t)im.methods.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::methods, im.methods[(size_t)i], md);
        }

        // ---- methods ----
        void visit(hir::TraitMethod& m, TypeFormMetaData md) override
        {
            // ADAPT: if header contains return/param types, defer them here.
            if (m.body)
            {
                md.block = *m.body;
                it_.defer(hir::ArenaKinds::blocks, *m.body, md);
            }
        }

        void visit(hir::ImplMethod& m, TypeFormMetaData md) override
        {
            // ADAPT: if header contains return/param types, defer them here.
            md.block = m.body;
            it_.defer(hir::ArenaKinds::blocks, m.body, md);
        }

        // ---- fields ----
        void visit(hir::StructFieldDecl& fd, TypeFormMetaData md) override
        {
            // ADAPT: field decl should have TypeId field type
            it_.defer(hir::ArenaKinds::types, fd.type, md);
        }

        void visit(hir::StructFieldInit& fi, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, fi.value, md);
        }

        // ---- blocks / stmts ----
        void visit(hir::Block&, TypeFormMetaData md) override
        {
            auto& ar = it_.a;
            const hir::BlockId bid = md.block;

            auto& blk = ar.blocks[(size_t)bid];
            for (int32_t i = (int32_t)blk.stmts.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::stmts, blk.stmts[(size_t)i], md);
        }

        void visit(hir::StmtVar& sv, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::types, sv.type, md);
            if (sv.init) it_.defer(hir::ArenaKinds::exprs, *sv.init, md);
        }

        void visit(hir::StmtExpr& se, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, se.expr, md);
        }

        void visit(hir::StmtReturn& sr, TypeFormMetaData md) override
        {
            if (sr.value) it_.defer(hir::ArenaKinds::exprs, *sr.value, md);
        }

        void visit(hir::StmtIf& si, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, si.cond, md);

            {
                auto child = md;
                child.block = si.then_blk;
                it_.defer(hir::ArenaKinds::blocks, si.then_blk, child);
            }

            for (int32_t i = (int32_t)si.elseifs.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::stmts, si.elseifs[(size_t)i], md);

            if (si.else_) it_.defer(hir::ArenaKinds::stmts, *si.else_, md);
        }

        void visit(hir::StmtElseIf& s, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, s.cond, md);
            {
                auto child = md;
                child.block = s.blk;
                it_.defer(hir::ArenaKinds::blocks, s.blk, child);
            }
        }

        void visit(hir::StmtElse& s, TypeFormMetaData md) override
        {
            {
                auto child = md;
                child.block = s.blk;
                it_.defer(hir::ArenaKinds::blocks, s.blk, child);
            }
        }

        void visit(hir::StmtWhile& sw, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, sw.cond, md);
            {
                auto child = md;
                child.block = sw.body;
                it_.defer(hir::ArenaKinds::blocks, sw.body, child);
            }
        }

        void visit(hir::StmtDoWhile& sd, TypeFormMetaData md) override
        {
            {
                auto child = md;
                child.block = sd.body;
                it_.defer(hir::ArenaKinds::blocks, sd.body, child);
            }
            it_.defer(hir::ArenaKinds::exprs, sd.cond, md);
        }

        void visit(hir::StmtBlock& sb, TypeFormMetaData md) override
        {
            {
                auto child = md;
                child.block = sb.block;
                it_.defer(hir::ArenaKinds::blocks, sb.block, child);
            }
        }

        void visit(hir::StmtBreak&, TypeFormMetaData) override
        {
        }

        void visit(hir::StmtContinue&, TypeFormMetaData) override
        {
        }

        // ---- expressions that carry types ----
        void visit(hir::ExprCast& c, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::types, c.type, md);
            it_.defer(hir::ArenaKinds::exprs, c.expr, md);
        }

        void visit(hir::ExprLitStruct& s, TypeFormMetaData md) override
        {
            // Do NOT defer s.type as Expr if it’s semantically a type-path (you already fixed this pattern in pass4).
            for (int32_t i = (int32_t)s.fields.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::field_inits, s.fields[(size_t)i], md);
        }

        // Generic expression traversal so we reach casts/struct lits in nested expressions
        void visit(hir::ExprCall& c, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, c.callee, md);
            for (int32_t i = (int32_t)c.args.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::exprs, c.args[(size_t)i], md);
        }

        void visit(hir::ExprUnary& u, TypeFormMetaData md) override { it_.defer(hir::ArenaKinds::exprs, u.rhs, md); }

        void visit(hir::ExprBinary& b, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, b.rhs, md);
            it_.defer(hir::ArenaKinds::exprs, b.lhs, md);
        }

        void visit(hir::ExprAssign& a, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, a.rhs, md);
            it_.defer(hir::ArenaKinds::exprs, a.lhs, md);
        }

        void visit(hir::ExprIndex& ix, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::exprs, ix.index, md);
            it_.defer(hir::ArenaKinds::exprs, ix.base, md);
        }

        void visit(hir::ExprField& f, TypeFormMetaData md) override { it_.defer(hir::ArenaKinds::exprs, f.base, md); }

        void visit(hir::ExprLitArray& a, TypeFormMetaData md) override
        {
            for (int32_t i = (int32_t)a.elements.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::exprs, a.elements[(size_t)i], md);
        }

        void visit(hir::ExprPath&, TypeFormMetaData) override
        {
        }

        void visit(hir::ExprLitInt&, TypeFormMetaData) override
        {
        }

        void visit(hir::ExprLitFloat&, TypeFormMetaData) override
        {
        }

        void visit(hir::ExprLitBool&, TypeFormMetaData) override
        {
        }

        void visit(hir::ExprLitChar&, TypeFormMetaData) override
        {
        }

        void visit(hir::ExprLitString&, TypeFormMetaData) override
        {
        }

        // ---- types: ensure children are visited before checking parent ----
        void visit(hir::TypeRef& tr, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::types, tr.inner, md);
        }

        void visit(hir::TypeArray& ta, TypeFormMetaData md) override
        {
            it_.defer(hir::ArenaKinds::types, ta.elem, md);
            it_.defer(hir::ArenaKinds::exprs, ta.size, md);
        }

        void visit(hir::TypePath& tp, TypeFormMetaData md) override
        {
            // CRITICAL: do not defer tp.path (ExprId) as Expr.
            for (int32_t i = (int32_t)tp.targs.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::types, tp.targs[(size_t)i], md);
        }

        void visit(hir::TypeBuiltin&, TypeFormMetaData) override
        {
        }

        void visit(hir::LoadFnDecl&, TypeFormMetaData) override
        {
            //TODO:
        }
    };

    // ============================================================
    // Applying visitor (does the checks)
    // ============================================================
    template <typename It>
    struct TypeFormApplyingVisitor final : hir::CoreApplyingVisitor<It, TypeFormMetaData>
    {
        using Base = hir::CoreApplyingVisitor<It, TypeFormMetaData>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        void visit(hir::TypePath& tp, TypeFormMetaData md) override
        {
            auto& ar = it_.a;

            // Sanity: ensure path expression is ExprPath if you want.
            if (!TypeFormBuilder::isExprPath(ar, tp.path))
            {
                md.b.out.errors.push_back({TypeFormErrKind::BadTypePathExpr, md.module, tp.loc});
                return;
            }

            switch (tp.res.kind)
            {
            case hir::TypeResKind::Error:
                {
                    md.b.out.errors.push_back({TypeFormErrKind::UnresolvedType, md.module, tp.loc});
                    return;
                }

            case hir::TypeResKind::TypeParam:
                {
                    if (!tp.targs.empty())
                        md.b.out.errors.push_back({TypeFormErrKind::TypeParamWithTypeArgs, md.module, tp.loc});
                    return;
                }

            case hir::TypeResKind::Def:
                {
                    const auto def = tp.res.id;

                    if (!md.b.defIsType(def))
                    {
                        md.b.out.errors.push_back({TypeFormErrKind::NonTypeDefInTypePos, md.module, tp.loc});
                        return;
                    }

                    auto exp = md.b.expectedArityForTypeDef(def);
                    if (!exp.has_value())
                    {
                        md.b.out.errors.push_back({TypeFormErrKind::NonTypeDefInTypePos, md.module, tp.loc});
                        return;
                    }

                    const auto got = (uint32_t)tp.targs.size();
                    if (got != *exp)
                        md.b.out.errors.push_back({TypeFormErrKind::WrongTypeArgCount, md.module, tp.loc});

                    return;
                }

            case hir::TypeResKind::Unresolved:
                {
                }
            }
        }

        void visit(hir::TypeArray& ta, TypeFormMetaData md) override
        {
            auto& ar = it_.a;

            // Minimal rule: array size must be integer literal at this stage.
            // (You can relax this later if you support const-exprs.)
            if (!TypeFormBuilder::isConstIntExpr(ar, ta.size))
                md.b.out.errors.push_back({TypeFormErrKind::ArraySizeNotConstInt, md.module, ta.loc});
        }

        void visit(hir::ExprLitStruct& s, TypeFormMetaData md) override
        {
            // Only if you added a separate type_res in ExprLitStruct:
            if constexpr (requires { s.type_res; })
            {
                if (s.type_res.kind == hir::TypeResKind::Error)
                    md.b.out.errors.push_back({TypeFormErrKind::UnresolvedType, md.module, s.loc});
            }
            else
            {
                // If you DID NOT add type_res, then Pass4 must ensure you never treat s.type as a value.
                // Pass5 will not validate struct literal type further here.
            }
        }

        void visit(hir::LoadFnDecl&, TypeFormMetaData) override
        {
            //TODO:
        }
    };

    using TypeFormIterator = hir::PartialIterator<
        TypeFormDeferringVisitor,
        TypeFormApplyingVisitor,
        TypeFormMetaData
    >;

    // ============================================================
    // Runner
    // ============================================================
    inline TypeFormPassDB runTypeFormationPass(hir::ArenaHolder& holder,
                                               ModulePassDB& pass1,
                                               ScopePassDB& pass2,
                                               DeclBindPassDB& pass3)
    {
        TypeFormPassDB out;
        TypeFormBuilder builder{holder, pass1, pass2, pass3, out};

        for (ModuleId mid = 0; mid < (ModuleId)pass1.modules.size(); ++mid)
        {
            const auto& mr = pass1.modules[(size_t)mid];
            const uint32_t arenaIndex = mr.arena_index;
            hir::Arena& ar = holder.arenas_[(size_t)arenaIndex];

            const uint32_t nodeCount =
                (uint32_t)ar.imports.size() +
                (uint32_t)ar.tparams.size() +
                (uint32_t)ar.params.size() +
                (uint32_t)ar.field_decls.size() +
                (uint32_t)ar.field_inits.size() +
                (uint32_t)ar.decls.size() +
                (uint32_t)ar.methods.size() +
                (uint32_t)ar.types.size() +
                (uint32_t)ar.exprs.size() +
                (uint32_t)ar.stmts.size() +
                (uint32_t)ar.blocks.size();

            TypeFormIterator it{ar, nodeCount};

            TypeFormApplyingVisitor<TypeFormIterator> av{it};
            it.setAVisitor(av);

            TypeFormMetaData md{builder};
            md.module = mid;
            md.block = ~0u;

            it.defer_first(ar.module, md);
            it.start_apply_inline();
        }

        return out;
    }
}

#endif //INZ_TYPE_FORMATION_PASS_HPP
