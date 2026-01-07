//
// Created by yhwach on 12/25/25.
//

#ifndef INZ_DFS_DEFERRING_VISIT_HPP
#define INZ_DFS_DEFERRING_VISIT_HPP

#include "visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "hir_types.hpp"
#include "decls.hpp"
#include "stmts.hpp"

namespace hir
{
    template <typename It, typename... MetaData>
    struct CoreDeferringVisitor : Visitor<It, MetaData...>
    {
        using Base = Visitor<It, MetaData...>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        using K = typename It::ContractedEnum;
        using I = typename It::Index;

        CoreDeferringVisitor(It& it)
            : Base(it)
        {
        }

    private:
        void defer_one(K kind, I idx, MetaData... md);

        template <class Vec>
        void defer_rev(K kind, Vec const& v, MetaData... md);

    public:
        virtual void visit(hir::Module& m, MetaData... md) override;

        // ---------------- arena-ish leaves ----------------
        virtual void visit(hir::Import& i, MetaData... md) override;
        virtual void visit(hir::TypeParam&, MetaData... /*md*/) override;
        virtual void visit(hir::ParamSelf&, MetaData... /*md*/) override;
        virtual void visit(hir::ParamNamed& p, MetaData... md) override;
        virtual void visit(hir::StructFieldDecl& f, MetaData... md) override;
        virtual void visit(hir::StructFieldInit& f, MetaData... md) override;
        virtual void visit(hir::Block& b, MetaData... md) override;
        virtual void visit(hir::FnDecl& fn, MetaData... md) override;
        virtual void visit(hir::StructDecl& st, MetaData... md) override;
        virtual void visit(hir::TypeAliasDecl& ta, MetaData... md) override;
        virtual void visit(hir::TraitDecl& t, MetaData... md) override;
        virtual void visit(hir::ImplDecl& i, MetaData... md) override;
        virtual void visit(hir::TypeBuiltin&, MetaData... /*md*/) override;
        virtual void visit(hir::TypePath& tp, MetaData... md) override;
        virtual void visit(hir::TypeRef& tr, MetaData... md) override;
        virtual void visit(hir::TypeArray& ta, MetaData... md) override;
        virtual void visit(hir::ExprPath&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitInt&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitFloat&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitBool&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitChar&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitString&, MetaData... /*md*/) override;
        virtual void visit(hir::ExprLitArray& ea, MetaData... md) override;
        virtual void visit(hir::ExprUnary& eu, MetaData... md) override;
        virtual void visit(hir::ExprBinary& eb, MetaData... md) override;
        virtual void visit(hir::ExprAssign& ea, MetaData... md) override;
        virtual void visit(hir::ExprCall& ec, MetaData... md) override;
        virtual void visit(hir::ExprIndex& ei, MetaData... md) override;
        virtual void visit(hir::ExprField& ef, MetaData... md) override;
        virtual void visit(hir::ExprLitStruct& es, MetaData... md) override;
        virtual void visit(hir::ExprCast& ec, MetaData... md) override;
        virtual void visit(hir::StmtBlock& sb, MetaData... md) override;
        virtual void visit(hir::StmtIf& si, MetaData... md) override;
        virtual void visit(hir::StmtElseIf& se, MetaData... md) override;
        virtual void visit(hir::StmtElse& se, MetaData... md) override;
        virtual void visit(hir::StmtWhile& sw, MetaData... md) override;
        virtual void visit(hir::StmtDoWhile& sd, MetaData... md) override;
        virtual void visit(hir::StmtBreak&, MetaData... /*md*/) override;
        virtual void visit(hir::StmtContinue&, MetaData... /*md*/) override;
        virtual void visit(hir::StmtReturn& sr, MetaData... md) override;
        virtual void visit(hir::StmtVar& sv, MetaData... md) override;
        virtual void visit(hir::StmtExpr& se, MetaData... md) override;
        virtual void visit(hir::TraitMethod& fn, MetaData... md) override;
        virtual void visit(hir::ImplMethod& fn, MetaData... md) override;
        virtual void visit(LoadFnDecl&, MetaData...) override;
    };

    // ---------------- private helpers ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::defer_one(K kind, I idx, MetaData... md)
    {
        it_.defer(kind, idx, md...);
    }

    template <typename It, typename... MetaData>
    template <class Vec>
    void CoreDeferringVisitor<It, MetaData...>::defer_rev(K kind, Vec const& v, MetaData... md)
    {
        for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
            it_.defer(kind, static_cast<I>(*rit), md...);
    }

    // ---------------- module ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::Module& m, MetaData... md)
    {
        // desired: package_path, imports (source), decls (source)
        // LIFO reverse:
        defer_rev(K::decls, m.decls, md...);
        defer_rev(K::imports, m.imports, md...);
        defer_one(K::exprs, static_cast<I>(m.package_path), md...);
    }

    // ---------------- arena-ish leaves ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::Import& i, MetaData... md)
    {
        // desired: path
        defer_one(K::exprs, static_cast<I>(i.path), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypeParam&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ParamSelf&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ParamNamed& p, MetaData... md)
    {
        // desired: type
        defer_one(K::types, static_cast<I>(p.type), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StructFieldDecl& f, MetaData... md)
    {
        // desired: type
        defer_one(K::types, static_cast<I>(f.type), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StructFieldInit& f, MetaData... md)
    {
        // desired: value
        defer_one(K::exprs, static_cast<I>(f.value), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::Block& b, MetaData... md)
    {
        // desired: stmts in source order
        // reverse:
        defer_rev(K::stmts, b.stmts, md...);
    }

    // ---------------- decl alternatives ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::FnDecl& fn, MetaData... md)
    {
        // desired: tparams (source), params (source), return_type, body(if any)
        // reverse:
        defer_one(K::blocks, static_cast<I>(fn.body), md...);

        if (fn.header.return_type)
            defer_one(K::types, static_cast<I>(fn.header.return_type.value()), md...);
        defer_rev(K::params, fn.header.params, md...);
        defer_rev(K::tparams, fn.tparams, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StructDecl& st, MetaData... md)
    {
        // desired: tparams (source), fields (source)
        // reverse:
        defer_rev(K::field_decls, st.fields, md...);
        defer_rev(K::tparams, st.tparams, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypeAliasDecl& ta, MetaData... md)
    {
        // desired: aliased
        defer_one(K::types, static_cast<I>(ta.aliased), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TraitDecl& t, MetaData... md)
    {
        // desired: tparams (source), methods (source)
        // reverse:
        defer_rev(K::methods, t.methods, md...);
        defer_rev(K::tparams, t.tparams, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ImplDecl& i, MetaData... md)
    {
        // desired: tparams (source), trait_path?, for_type, methods (source)
        // reverse:
        defer_rev(K::methods, i.methods, md...);
        defer_one(K::types, static_cast<I>(i.for_type), md...);

        if (i.trait_path.has_value())
            defer_one(K::exprs, static_cast<I>(*i.trait_path), md...);

        defer_rev(K::tparams, i.tparams, md...);
    }

    // ---------------- type alternatives ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypeBuiltin&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypePath& tp, MetaData... md)
    {
        // desired: path, then targs (source)
        // reverse:
        defer_rev(K::types, tp.targs, md...);
        defer_one(K::exprs, static_cast<I>(tp.path), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypeRef& tr, MetaData... md)
    {
        // desired: inner
        defer_one(K::types, static_cast<I>(tr.inner), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TypeArray& ta, MetaData... md)
    {
        // desired: elem, then size
        // reverse:
        defer_one(K::exprs, static_cast<I>(ta.size), md...);
        defer_one(K::types, static_cast<I>(ta.elem), md...);
    }

    // ---------------- expr alternatives ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprPath&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitInt&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitFloat&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitBool&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitChar&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitString&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitArray& ea, MetaData... md)
    {
        // desired: elements in source order
        // reverse:
        defer_rev(K::exprs, ea.elements, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprUnary& eu, MetaData... md)
    {
        // desired: rhs
        defer_one(K::exprs, static_cast<I>(eu.rhs), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprBinary& eb, MetaData... md)
    {
        // desired: lhs then rhs
        // reverse:
        defer_one(K::exprs, static_cast<I>(eb.rhs), md...);
        defer_one(K::exprs, static_cast<I>(eb.lhs), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprAssign& ea, MetaData... md)
    {
        // desired: lhs then rhs
        // reverse:
        defer_one(K::exprs, static_cast<I>(ea.rhs), md...);
        defer_one(K::exprs, static_cast<I>(ea.lhs), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprCall& ec, MetaData... md)
    {
        // desired: callee, targs (source), args (source)
        // reverse:
        defer_rev(K::exprs, ec.args, md...);
        defer_rev(K::types, ec.targs, md...);
        defer_one(K::exprs, static_cast<I>(ec.callee), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprIndex& ei, MetaData... md)
    {
        // desired: base then index
        // reverse:
        defer_one(K::exprs, static_cast<I>(ei.index), md...);
        defer_one(K::exprs, static_cast<I>(ei.base), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprField& ef, MetaData... md)
    {
        // desired: base
        defer_one(K::exprs, static_cast<I>(ef.base), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprLitStruct& es, MetaData... md)
    {
        // desired: type, then fields (source)
        // reverse:
        defer_rev(K::field_inits, es.fields, md...);
        defer_one(K::exprs, static_cast<I>(es.type), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ExprCast& ec, MetaData... md)
    {
        // desired: expr then type
        // reverse:
        defer_one(K::types, static_cast<I>(ec.type), md...);
        defer_one(K::exprs, static_cast<I>(ec.expr), md...);
    }

    // ---------------- stmt alternatives ----------------

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtBlock& sb, MetaData... md)
    {
        // desired: block
        defer_one(K::blocks, static_cast<I>(sb.block), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtIf& si, MetaData... md)
    {
        // desired: cond, then_blk, elseifs (source), else (optional)
        // reverse:
        if (si.else_)
            defer_one(K::stmts, static_cast<I>(*si.else_), md...);

        defer_rev(K::stmts, si.elseifs, md...);
        defer_one(K::blocks, static_cast<I>(si.then_blk), md...);
        defer_one(K::exprs, static_cast<I>(si.cond), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtElseIf& se, MetaData... md)
    {
        // desired: cond, then blk
        // reverse:
        defer_one(K::blocks, static_cast<I>(se.blk), md...);
        defer_one(K::exprs, static_cast<I>(se.cond), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtElse& se, MetaData... md)
    {
        // desired: blk
        defer_one(K::blocks, static_cast<I>(se.blk), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtWhile& sw, MetaData... md)
    {
        // desired: cond then body
        // reverse:
        defer_one(K::blocks, static_cast<I>(sw.body), md...);
        defer_one(K::exprs, static_cast<I>(sw.cond), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtDoWhile& sd, MetaData... md)
    {
        // desired: body then cond
        // reverse:
        defer_one(K::exprs, static_cast<I>(sd.cond), md...);
        defer_one(K::blocks, static_cast<I>(sd.body), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtBreak&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtContinue&, MetaData... /*md*/)
    {
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtReturn& sr, MetaData... md)
    {
        // desired: value if present
        if (sr.value)
            defer_one(K::exprs, static_cast<I>(*sr.value), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtVar& sv, MetaData... md)
    {
        // desired: type then init(if any)
        // reverse:
        if (sv.init)
            defer_one(K::exprs, static_cast<I>(*sv.init), md...);

        defer_one(K::types, static_cast<I>(sv.type), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::StmtExpr& se, MetaData... md)
    {
        // desired: expr
        defer_one(K::exprs, static_cast<I>(se.expr), md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::TraitMethod& fn, MetaData... md)
    {
        if (fn.body)
            defer_one(K::blocks, static_cast<I>(*fn.body), md...);

        if (fn.header.return_type)
            defer_one(K::types, static_cast<I>(fn.header.return_type.value()), md...);
        defer_rev(K::params, fn.header.params, md...);
        defer_rev(K::tparams, fn.tparams, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(hir::ImplMethod& fn, MetaData... md)
    {
        defer_one(K::blocks, static_cast<I>(fn.body), md...);

        if (fn.header.return_type)
            defer_one(K::types, static_cast<I>(fn.header.return_type.value()), md...);
        defer_rev(K::params, fn.header.params, md...);
        defer_rev(K::tparams, fn.tparams, md...);
    }

    template <typename It, typename... MetaData>
    void CoreDeferringVisitor<It, MetaData...>::visit(LoadFnDecl& fn, MetaData... md)
    {
        if (fn.header.return_type)
            defer_one(K::types, static_cast<I>(fn.header.return_type.value()), md...);
        defer_rev(K::params, fn.header.params, md...);
    }
}
#endif //INZ_DFS_DEFERRING_VISIT_HPP
