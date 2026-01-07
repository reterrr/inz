//
// Created by yhwach on 12/29/25.
//

#ifndef INZ_BODY_TYPE_CHECK_PASS_HPP
#define INZ_BODY_TYPE_CHECK_PASS_HPP

#include "module_import_pass.hpp"
#include "scope_pass.hpp"
#include "decl_bind_pass.hpp"      // Pass 3
#include "name_resolution_pass.hpp"// Pass 4 (res fields already on HIR nodes)

#include "hir/arena_holder.hpp"
#include "hir/arena.hpp"

#include <optional>
#include <llvm/ADT/SmallVector.h>

namespace sema
{
    // ----------------------------
    // Errors
    // ----------------------------
    enum class BodyTcErrKind : uint8_t
    {
        VarHasVoidType,
        ParamHasVoidType,
        FieldHasVoidType,

        IfCondNotBool,
        WhileCondNotBool,

        ReturnTypeMismatch,
        ReturnValueInVoidFn,
        MissingReturnValue,

        // Placeholder for future:
        UnresolvedValueInExpr,
        CallOnNonCallable,
        ArgCountMismatch,
        ArgTypeMismatch,
    };

    struct BodyTcError
    {
        BodyTcErrKind kind{};
        ModuleId module{};
        lex::Loc loc{};
    };

    struct BodyTypeCheckDB
    {
        llvm::SmallVector<BodyTcError, 128> errors;
        // Optional: ExprId -> TypeId or semantic type id
        // std::vector<...> expr_types;
    };

    // ----------------------------
    // Helpers
    // ----------------------------
    static inline bool isVoidType(hir::Arena& ar, hir::TypeId tid)
    {
        auto& t = ar.types[(size_t)tid];
        if (auto* tb = std::get_if<hir::TypeBuiltin>(&t.kind))
            return tb->kind == kl::rt::BuiltinTypeExprKind::Void;
        return false;
    }

    static inline bool isBoolType(hir::Arena& ar, hir::TypeId tid)
    {
        auto& t = ar.types[(size_t)tid];
        if (auto* tb = std::get_if<hir::TypeBuiltin>(&t.kind))
            return tb->kind == kl::rt::BuiltinTypeExprKind::Bool;
        return false;
    }

    // ----------------------------
    // Builder
    // ----------------------------
    struct BodyTcBuilder
    {
        hir::ArenaHolder& holder;
        ModulePassDB& pass1;
        ScopePassDB& pass2;
        DeclBindPassDB& pass3;
        BodyTypeCheckDB& out;

        void error(BodyTcErrKind k, ModuleId m, const lex::Loc& loc)
        {
            out.errors.push_back(BodyTcError{k, m, loc});
        }

        // ---- ADAPT: you will implement expression typing here later. ----
        // For now we only demonstrate the *void* checks and control-flow checks.
        //
        // Later you will return something like: TypeId or SemTyId for ExprId.
        //
        hir::TypeId typeOfExpr(ModuleId /*mid*/, hir::Arena& /*ar*/, hir::ExprId /*eid*/)
        {
            // TODO: Pass 6 main work
            return hir::TypeId{}; // placeholder
        }
    };

    // ----------------------------
    // Metadata
    // ----------------------------
    struct BodyTcMeta
    {
        BodyTcBuilder& b;
        ModuleId module{};

        // current function/method return type (syntactic TypeId)
        hir::TypeId returnType{};

        // current block id (only if needed by your iterator; optional)
        hir::BlockId block{~0u};
    };

    // ============================================================
    // Deferring visitor (no Base::visit)
    // ============================================================
    template <typename It>
    struct BodyTcDeferringVisitor final : hir::CoreDeferringVisitor<It, BodyTcMeta>
    {
        using Base = hir::CoreDeferringVisitor<It, BodyTcMeta>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        void visit(hir::Module& m, BodyTcMeta md) override
        {
            for (int32_t i = (int32_t)m.decls.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::decls, m.decls[(size_t)i], md);
        }

        void visit(hir::FnDecl& f, BodyTcMeta md) override
        {
            md.returnType = f.header.return_type;
            md.block = f.body;

            it_.defer(hir::ArenaKinds::blocks, f.body, md);

            // Optional: also defer params if your iterator includes them
            // for (auto pid : f.header.params) it_.defer(hir::ArenaKinds::params, pid, md);
        }

        void visit(hir::StructDecl& s, BodyTcMeta md) override
        {
            for (int32_t i = (int32_t)s.fields.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::field_decls, s.fields[(size_t)i], md);
        }

        void visit(hir::TraitDecl& tr, BodyTcMeta md) override
        {
            for (int32_t i = (int32_t)tr.methods.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::methods, tr.methods[(size_t)i], md);
        }

        void visit(hir::ImplDecl& im, BodyTcMeta md) override
        {
            for (int32_t i = (int32_t)im.methods.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::methods, im.methods[(size_t)i], md);
        }

        void visit(hir::TraitMethod& m, BodyTcMeta md) override
        {
            md.returnType = m.header.return_type;

            if (m.body)
            {
                md.block = *m.body;
                it_.defer(hir::ArenaKinds::blocks, *m.body, md);
            }
        }

        void visit(hir::ImplMethod& m, BodyTcMeta md) override
        {
            md.returnType = m.header.return_type;
            md.block = m.body;
            it_.defer(hir::ArenaKinds::blocks, m.body, md);
        }

        void visit(hir::Block&, BodyTcMeta md) override
        {
            auto& ar = it_.a;
            const hir::BlockId bid = md.block;

            auto& blk = ar.blocks[(size_t)bid];
            for (int32_t i = (int32_t)blk.stmts.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::stmts, blk.stmts[(size_t)i], md);
        }

        void visit(hir::StmtVar& sv, BodyTcMeta md) override
        {
            if (sv.init) it_.defer(hir::ArenaKinds::exprs, *sv.init, md);
        }

        void visit(hir::StmtExpr& se, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, se.expr, md);
        }

        void visit(hir::StmtReturn& sr, BodyTcMeta md) override
        {
            if (sr.value) it_.defer(hir::ArenaKinds::exprs, *sr.value, md);
        }

        void visit(hir::StmtIf& si, BodyTcMeta md) override
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

        void visit(hir::StmtElseIf& s, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, s.cond, md);
            {
                auto child = md;
                child.block = s.blk;
                it_.defer(hir::ArenaKinds::blocks, s.blk, child);
            }
        }

        void visit(hir::StmtElse& s, BodyTcMeta md) override
        {
            {
                auto child = md;
                child.block = s.blk;
                it_.defer(hir::ArenaKinds::blocks, s.blk, child);
            }
        }

        void visit(hir::StmtWhile& sw, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, sw.cond, md);
            {
                auto child = md;
                child.block = sw.body;
                it_.defer(hir::ArenaKinds::blocks, sw.body, child);
            }
        }

        void visit(hir::StmtDoWhile& sd, BodyTcMeta md) override
        {
            {
                auto child = md;
                child.block = sd.body;
                it_.defer(hir::ArenaKinds::blocks, sd.body, child);
            }
            it_.defer(hir::ArenaKinds::exprs, sd.cond, md);
        }

        void visit(hir::StmtBlock& sb, BodyTcMeta md) override
        {
            {
                auto child = md;
                child.block = sb.block;
                it_.defer(hir::ArenaKinds::blocks, sb.block, child);
            }
        }

        void visit(hir::StmtBreak&, BodyTcMeta) override
        {
        }

        void visit(hir::StmtContinue&, BodyTcMeta) override
        {
        }

        // Defer expression children (minimal subset; expand later)
        void visit(hir::ExprUnary& u, BodyTcMeta md) override { it_.defer(hir::ArenaKinds::exprs, u.rhs, md); }

        void visit(hir::ExprBinary& b, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, b.rhs, md);
            it_.defer(hir::ArenaKinds::exprs, b.lhs, md);
        }

        void visit(hir::ExprAssign& a, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, a.rhs, md);
            it_.defer(hir::ArenaKinds::exprs, a.lhs, md);
        }

        void visit(hir::ExprCall& c, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, c.callee, md);
            for (int32_t i = (int32_t)c.args.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::exprs, c.args[(size_t)i], md);
        }

        void visit(hir::ExprIndex& ix, BodyTcMeta md) override
        {
            it_.defer(hir::ArenaKinds::exprs, ix.index, md);
            it_.defer(hir::ArenaKinds::exprs, ix.base, md);
        }

        void visit(hir::ExprField& f, BodyTcMeta md) override { it_.defer(hir::ArenaKinds::exprs, f.base, md); }
        void visit(hir::ExprCast& c, BodyTcMeta md) override { it_.defer(hir::ArenaKinds::exprs, c.expr, md); }

        void visit(hir::ExprPath&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitInt&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitFloat&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitBool&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitChar&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitString&, BodyTcMeta) override
        {
        }

        void visit(hir::ExprLitArray& a, BodyTcMeta md) override
        {
            for (int32_t i = (int32_t)a.elements.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::exprs, a.elements[(size_t)i], md);
        }

        void visit(hir::ExprLitStruct& s, BodyTcMeta md) override
        {
            // type is semantic-type, not value-expr; do not defer s.type as expr.
            for (int32_t i = (int32_t)s.fields.size() - 1; i >= 0; --i)
                it_.defer(hir::ArenaKinds::field_inits, s.fields[(size_t)i], md);
        }

        // field decls: no children deferred here (types are checked via direct access in applying)
        void visit(hir::StructFieldDecl&, BodyTcMeta) override
        {
        }

        void visit(hir::LoadFnDecl&, BodyTcMeta) override
        {
            //TODO:
        }
    };

    // ============================================================
    // Applying visitor (where the void checks live)
    // ============================================================
    template <typename It>
    struct BodyTcApplyingVisitor final : hir::CoreApplyingVisitor<It, BodyTcMeta>
    {
        using Base = hir::CoreApplyingVisitor<It, BodyTcMeta>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        void visit(hir::StmtVar& sv, BodyTcMeta md) override
        {
            auto& ar = it_.a;

            if (isVoidType(ar, sv.type))
                md.b.error(BodyTcErrKind::VarHasVoidType, md.module, sv.loc);

            // Later: if init exists -> compute type and check assignable
            // if (sv.init) { auto it = md.b.typeOfExpr(...); ... }
        }

        void visit(hir::StructFieldDecl& fd, BodyTcMeta md) override
        {
            auto& ar = it_.a;

            // ADAPT: field type member name; I assume fd.type
            if (isVoidType(ar, fd.type))
                md.b.error(BodyTcErrKind::FieldHasVoidType, md.module, fd.loc);
        }

        void visit(hir::StmtIf& si, BodyTcMeta md) override
        {
            // Later you will call md.b.typeOfExpr on si.cond, but for now demonstrate structure.
            // auto t = md.b.typeOfExpr(md.module, it_.a, si.cond);
            // if (!isBool(t)) error(...)
            (void)si;
        }

        void visit(hir::StmtWhile& sw, BodyTcMeta md) override
        {
            (void)sw;
        }

        void visit(hir::StmtReturn& sr, BodyTcMeta md) override
        {
            auto& ar = it_.a;

            const bool retVoid = isVoidType(ar, md.returnType);

            if (!sr.value)
            {
                if (!retVoid)
                    md.b.error(BodyTcErrKind::MissingReturnValue, md.module, sr.loc);
                return;
            }

            if (retVoid)
            {
                md.b.error(BodyTcErrKind::ReturnValueInVoidFn, md.module, sr.loc);
                return;
            }

            // Later:
            // auto vt = md.b.typeOfExpr(md.module, ar, *sr.value);
            // auto rt = md.b.formType(md.module, ar, md.returnType);
            // if (!assignable(vt, rt)) error(ReturnTypeMismatch)
        }

        void visit(hir::LoadFnDecl&, BodyTcMeta) override
        {
            //TODO:
        }
    };

    using BodyTcIterator = hir::PartialIterator<
        BodyTcDeferringVisitor,
        BodyTcApplyingVisitor,
        BodyTcMeta
    >;

    inline BodyTypeCheckDB runBodyTypeCheckPass(hir::ArenaHolder& holder,
                                                ModulePassDB& pass1,
                                                ScopePassDB& pass2,
                                                DeclBindPassDB& pass3)
    {
        BodyTypeCheckDB out;
        BodyTcBuilder builder{holder, pass1, pass2, pass3, out};

        for (ModuleId mid = 0; mid < (ModuleId)pass1.modules.size(); ++mid)
        {
            const auto& mr = pass1.modules[(size_t)mid];
            hir::Arena& ar = holder.arenas_[(size_t)mr.arena_index];

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

            BodyTcIterator it{ar, nodeCount};

            BodyTcApplyingVisitor<BodyTcIterator> av{it};
            it.setAVisitor(av);

            BodyTcMeta md{builder};
            md.module = mid;
            md.returnType = hir::TypeId{}; // will be set when entering fn/method
            md.block = ~0u;

            it.defer_first(ar.module, md);
            it.start_apply_inline();
        }

        return out;
    }
} // namespace sema

#endif // INZ_BODY_TYPE_CHECK_PASS_HPP
