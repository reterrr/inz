//
// Created by yhwach on 12/25/25.
//

#ifndef INZ_DFS_DEFERRING_VISIT_HPP
#define INZ_DFS_DEFERRING_VISIT_HPP
#include <cstdint>

#include "visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"
#include "decls.hpp"

namespace hir
{
    template <typename It>
    struct DFSDeferringChildVisitor final : Visitor<It>
    {
        using Visitor<It>::Visitor;
        using Visitor<It>::visit;
        using Visitor<It>::it_;

        using K = typename It::ContractedEnum;

        // small helpers to reduce boilerplate
        template <class Vec>
        void defer_rev(K kind, const Vec& v)
        {
            for (auto it = v.rbegin(); it != v.rend(); ++it)
                it_.defer(kind, static_cast<uint32_t>(*it));
        }

        void defer_one(K kind, uint32_t idx)
        {
            it_.defer(kind, idx);
        }

        // arena leaves
        void visit(Module& m) override;
        void visit(Import& i) override;

        void visit(TypeParam&) override
        {
        }

        void visit(Param& p) override;
        void visit(StructFieldDecl& f) override;
        void visit(StructFieldInit& f) override;
        void visit(Block& b) override;

        // decl alternatives
        void visit(FnDecl& fn) override;
        void visit(StructDecl& st) override;
        void visit(TypeAliasDecl& ta) override;

        // type alternatives
        void visit(TypeBuiltin&) override
        {
        }

        void visit(TypePath& tp) override;
        void visit(TypeRef& tr) override;
        void visit(TypeArray& ta) override;

        // expr alternatives
        void visit(ExprPath& ep) override;

        void visit(ExprLitInt&) override
        {
        }

        void visit(ExprLitArray& ea) override;

        void visit(ExprLitFloat&) override
        {
        }

        void visit(ExprLitBool&) override
        {
        }

        void visit(ExprLitChar&) override
        {
        }

        void visit(ExprLitString&) override
        {
        }

        void visit(ExprUnary& eu) override;
        void visit(ExprBinary& eb) override;
        void visit(ExprAssign& ea) override;
        void visit(ExprCall& ec) override;
        void visit(ExprIndex& ei) override;
        void visit(ExprField& ef) override;
        void visit(ExprLitStruct& es) override;
        void visit(ExprCast& ec) override;

        // stmt alternatives
        void visit(StmtBlock& sb) override;
        void visit(StmtIf& si) override;
        void visit(StmtElseIf& se) override;
        void visit(StmtElse& se) override;
        void visit(StmtWhile& sw) override;
        void visit(StmtDoWhile& sd) override;

        void visit(StmtBreak&) override
        {
        }

        void visit(StmtContinue&) override
        {
        }

        void visit(StmtReturn& sr) override;
        void visit(StmtVar& sv) override;
        void visit(StmtExpr& se) override;
    };

    // ---------------- DFS (preorder) deferrals ----------------
    // NOTE: These assume iterator uses LIFO pop_back DFS.
    // Therefore: defer children in REVERSE of desired visitation order.

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(Module& m)
    {
        // desired visitation:
        //   package_path, imports (source order), decls (source order)
        // LIFO defer in reverse:
        defer_rev(K::decls, m.decls);
        defer_rev(K::imports, m.imports);
        defer_one(K::exprs, static_cast<uint32_t>(m.package_path));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(Import& i)
    {
        // desired: path
        defer_one(K::exprs, static_cast<uint32_t>(i.path));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(Param& p)
    {
        // desired: type
        defer_one(K::types, static_cast<uint32_t>(p.type));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StructFieldDecl& f)
    {
        // desired: type
        defer_one(K::types, static_cast<uint32_t>(f.type));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StructFieldInit& f)
    {
        // desired: value
        defer_one(K::exprs, static_cast<uint32_t>(f.value));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(Block& b)
    {
        // desired: stmts in source order
        defer_rev(K::stmts, b.stmts);
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(FnDecl& fn)
    {
        // desired visitation:
        //   tparams (source order), params (source order), return_type, body (if any)
        // reverse for LIFO:
        if (fn.body)
            defer_one(K::blocks, static_cast<uint32_t>(*fn.body));
        defer_one(K::types, static_cast<uint32_t>(fn.return_type));
        defer_rev(K::params, fn.params);
        defer_rev(K::tparams, fn.tparams);
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StructDecl& st)
    {
        // desired: tparams (source order), fields (source order)
        // reverse:
        defer_rev(K::field_decls, st.fields);
        defer_rev(K::tparams, st.tparams);
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(TypeAliasDecl& ta)
    {
        // desired: aliased
        defer_one(K::types, static_cast<uint32_t>(ta.aliased));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(TypePath& tp)
    {
        // desired: path, then targs (source order)
        // reverse:
        defer_rev(K::types, tp.targs);
        defer_one(K::exprs, static_cast<uint32_t>(tp.path));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(TypeRef& tr)
    {
        // desired: inner
        defer_one(K::types, static_cast<uint32_t>(tr.inner));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(TypeArray& ta)
    {
        // desired: elem, then size
        // reverse:
        defer_one(K::exprs, static_cast<uint32_t>(ta.size));
        defer_one(K::types, static_cast<uint32_t>(ta.elem));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprPath& /*ep*/)
    {
        // If you want to traverse paths arena, do it here (if your enum has paths):
        // it_.defer(K::paths, static_cast<uint32_t>(ep.path));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprLitArray& ea)
    {
        // desired: elements in source order
        defer_rev(K::exprs, ea.elements);
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprUnary& eu)
    {
        // desired: rhs
        defer_one(K::exprs, static_cast<uint32_t>(eu.rhs));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprBinary& eb)
    {
        // desired: lhs then rhs
        // reverse:
        defer_one(K::exprs, static_cast<uint32_t>(eb.rhs));
        defer_one(K::exprs, static_cast<uint32_t>(eb.lhs));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprAssign& ea)
    {
        // desired: lhs then rhs
        // reverse:
        defer_one(K::exprs, static_cast<uint32_t>(ea.rhs));
        defer_one(K::exprs, static_cast<uint32_t>(ea.lhs));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprCall& ec)
    {
        // desired: callee, then targs (source order), then args (source order)
        // reverse:
        defer_rev(K::exprs, ec.args);
        defer_rev(K::types, ec.targs);
        defer_one(K::exprs, static_cast<uint32_t>(ec.callee));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprIndex& ei)
    {
        // desired: base then index
        // reverse:
        defer_one(K::exprs, static_cast<uint32_t>(ei.index));
        defer_one(K::exprs, static_cast<uint32_t>(ei.base));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprField& ef)
    {
        // desired: base
        defer_one(K::exprs, static_cast<uint32_t>(ef.base));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprLitStruct& es)
    {
        // desired: type, then fields (source order)
        // reverse:
        defer_rev(K::field_inits, es.fields);
        defer_one(K::exprs, static_cast<uint32_t>(es.type));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(ExprCast& ec)
    {
        // desired: expr then type
        // reverse:
        defer_one(K::types, static_cast<uint32_t>(ec.type));
        defer_one(K::exprs, static_cast<uint32_t>(ec.expr));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtBlock& sb)
    {
        // desired: block
        defer_one(K::blocks, static_cast<uint32_t>(sb.block));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtIf& si)
    {
        // desired:
        //   cond, then then_blk, then elseifs (source order), then else (if any)
        // reverse:
        if (si.else_)
            defer_one(K::stmts, static_cast<uint32_t>(*si.else_));
        defer_rev(K::stmts, si.elseifs);
        defer_one(K::blocks, static_cast<uint32_t>(si.then_blk));
        defer_one(K::exprs, static_cast<uint32_t>(si.cond));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtElseIf& se)
    {
        // desired: cond, then blk
        // reverse:
        defer_one(K::blocks, static_cast<uint32_t>(se.blk));
        defer_one(K::exprs, static_cast<uint32_t>(se.cond));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtElse& se)
    {
        // desired: blk
        defer_one(K::blocks, static_cast<uint32_t>(se.blk));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtWhile& sw)
    {
        // desired: cond then body
        // reverse:
        defer_one(K::blocks, static_cast<uint32_t>(sw.body));
        defer_one(K::exprs, static_cast<uint32_t>(sw.cond));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtDoWhile& sd)
    {
        // desired (syntax): body then cond
        // reverse:
        defer_one(K::exprs, static_cast<uint32_t>(sd.cond));
        defer_one(K::blocks, static_cast<uint32_t>(sd.body));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtReturn& sr)
    {
        // desired: value if present
        if (sr.value)
            defer_one(K::exprs, static_cast<uint32_t>(*sr.value));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtVar& sv)
    {
        // desired: type then init (if any)
        // reverse:
        if (sv.init)
            defer_one(K::exprs, static_cast<uint32_t>(*sv.init));
        defer_one(K::types, static_cast<uint32_t>(sv.type));
    }

    template <typename It>
    void DFSDeferringChildVisitor<It>::visit(StmtExpr& se)
    {
        // desired: expr
        defer_one(K::exprs, static_cast<uint32_t>(se.expr));
    }
}

#endif //INZ_DFS_DEFERRING_VISIT_HPP
