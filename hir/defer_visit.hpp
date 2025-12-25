//
// Created by yhwach on 12/24/25.
//

#ifndef INZ_DEFER_VISIT_HPP
#define INZ_DEFER_VISIT_HPP
#include "visitor.hpp"

#include "stmts.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "decls.hpp"
#include "hir_types.hpp"

namespace hir
{
    template <typename It>
    struct DeferringChildVisitor final : Visitor<It>
    {
        using Visitor<It>::Visitor;
        using Visitor<It>::visit;
        using Visitor<It>::it_;

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

    // -------- arena nodes --------

    template <typename It>
    void DeferringChildVisitor<It>::visit(Module& m)
    {

        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(m.package_path));

        // then imports in source order
        for (auto id : m.imports)
            it_.defer(It::ContractedEnum::imports, static_cast<uint32_t>(id));

        // then decls in source order
        for (auto id : m.decls)
            it_.defer(It::ContractedEnum::decls, static_cast<uint32_t>(id));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(Import& i)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(i.path));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(Param& p)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(p.type));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StructFieldDecl& f)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(f.type));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StructFieldInit& f)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(f.value));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(Block& b)
    {
        for (auto it = b.stmts.begin(); it != b.stmts.end(); ++it)
            it_.defer(It::ContractedEnum::stmts, static_cast<uint32_t>(*it));
    }

    // -------- decl alternatives --------

    template <typename It>
    void DeferringChildVisitor<It>::visit(FnDecl& fn)
    {
        for (auto id : fn.tparams)
            it_.defer(It::ContractedEnum::tparams, static_cast<uint32_t>(id));

        for (auto id : fn.params)
            it_.defer(It::ContractedEnum::params, static_cast<uint32_t>(id));

        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(fn.return_type));

        if (fn.body)
            it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(*fn.body));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StructDecl& st)
    {
        for (auto id : st.tparams)
            it_.defer(It::ContractedEnum::tparams, static_cast<uint32_t>(id));

        for (auto id : st.fields)
            it_.defer(It::ContractedEnum::field_decls, static_cast<uint32_t>(id));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(TypeAliasDecl& ta)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(ta.aliased));
    }

    // -------- type alternatives --------

    template <typename It>
    void DeferringChildVisitor<It>::visit(TypePath& tp)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(tp.path));
        // If tp.path is PathId instead, use:
        // it_.defer(It::ContractedEnum::paths, static_cast<uint32_t>(tp.path));

        for (auto id : tp.targs)
            it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(id));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(TypeRef& tr)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(tr.inner));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(TypeArray& ta)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(ta.elem));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ta.size));
    }

    // -------- expr alternatives --------

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprPath& /*ep*/)
    {
        // ExprPath holds PathId (paths arena). If you want to traverse it:
        // it_.defer(It::ContractedEnum::paths, static_cast<uint32_t>(ep.path));
        // If you don't care about paths here, leave empty.
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprLitArray& ea)
    {
        for (auto it = ea.elements.begin(); it != ea.elements.end(); ++it)
            it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(*it));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprUnary& eu)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(eu.rhs));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprBinary& eb)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(eb.lhs));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(eb.rhs));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprAssign& ea)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ea.lhs));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ea.rhs));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprCall& ec)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ec.callee));

        for (auto id : ec.targs)
            it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(id));

        for (auto id : ec.args)
            it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(id));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprIndex& ei)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ei.base));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ei.index));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprField& ef)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ef.base));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprLitStruct& es)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(es.type));

        for (auto id : es.fields)
            it_.defer(It::ContractedEnum::field_inits, static_cast<uint32_t>(id));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(ExprCast& ec)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(ec.type));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(ec.expr));
    }

    // -------- stmt alternatives --------

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtBlock& sb)
    {
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(sb.block));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtIf& si)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(si.cond));
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(si.then_blk));

        for (auto id : si.elseifs)
            it_.defer(It::ContractedEnum::stmts, static_cast<uint32_t>(id));

        if (si.else_)
            it_.defer(It::ContractedEnum::stmts, static_cast<uint32_t>(*si.else_));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtElseIf& se)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(se.cond));
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(se.blk));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtElse& se)
    {
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(se.blk));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtWhile& sw)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(sw.cond));
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(sw.body));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtDoWhile& sd)
    {
        it_.defer(It::ContractedEnum::blocks, static_cast<uint32_t>(sd.body));
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(sd.cond));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtReturn& sr)
    {
        if (sr.value) it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(*sr.value));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtVar& sv)
    {
        it_.defer(It::ContractedEnum::types, static_cast<uint32_t>(sv.type));
        if (sv.init)
            it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(*sv.init));
    }

    template <typename It>
    void DeferringChildVisitor<It>::visit(StmtExpr& se)
    {
        it_.defer(It::ContractedEnum::exprs, static_cast<uint32_t>(se.expr));
    }
}

#endif //INZ_DEFER_VISIT_HPP
