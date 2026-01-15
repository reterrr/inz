//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_DEFAULT_DEFERING_VISIT_HPP
#define INZ_DEFAULT_DEFERING_VISIT_HPP
#include "core_deferring_visit.hpp"
#include "metadata.hpp"

namespace hir
{
    template <typename It>
    struct DefaultDeferingVisitor final : CoreDeferringVisitor<It, MetaData>
    {
        using Base = CoreDeferringVisitor<It, MetaData>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

    private:
        static MetaData bump(MetaData md) noexcept
        {
            ++md.depth;
            return md;
        }

    public:
        // --- module / decl / block ---
        void visit(hir::Module& m, MetaData md) override { Base::visit(m, bump(md)); }
        void visit(hir::Import& i, MetaData md) override { Base::visit(i, bump(md)); }

        void visit(hir::TypeParam& tp, MetaData md) override { Base::visit(tp, md); }
        void visit(hir::ParamSelf& ps, MetaData md) override { Base::visit(ps, md); }

        void visit(hir::ParamNamed& p, MetaData md) override { Base::visit(p, bump(md)); }
        void visit(hir::StructFieldDecl& f, MetaData md) override { Base::visit(f, bump(md)); }
        void visit(hir::StructFieldInit& f, MetaData md) override { Base::visit(f, bump(md)); }

        void visit(hir::Block& b, MetaData md) override { Base::visit(b, bump(md)); }

        void visit(hir::FnDecl& fn, MetaData md) override { Base::visit(fn, bump(md)); }
        void visit(hir::StructDecl& st, MetaData md) override { Base::visit(st, bump(md)); }
        void visit(hir::TypeAliasDecl& ta, MetaData md) override { Base::visit(ta, bump(md)); }
        void visit(hir::TraitDecl& t, MetaData md) override { Base::visit(t, bump(md)); }
        void visit(hir::ImplDecl& i, MetaData md) override { Base::visit(i, bump(md)); }

        // --- types ---
        void visit(hir::TypeBuiltin& tb, MetaData md) override { Base::visit(tb, md); }
        void visit(hir::TypePath& tp, MetaData md) override { Base::visit(tp, bump(md)); }
        void visit(hir::TypeRef& tr, MetaData md) override { Base::visit(tr, bump(md)); }
        void visit(hir::TypeArray& ta, MetaData md) override { Base::visit(ta, bump(md)); }

        // --- expr ---
        void visit(hir::ExprPath& e, MetaData md) override { Base::visit(e, md); }
        void visit(hir::ExprLitInt& e, MetaData md) override { Base::visit(e, md); }
        void visit(hir::ExprLitFloat& e, MetaData md) override { Base::visit(e, md); }
        void visit(hir::ExprLitBool& e, MetaData md) override { Base::visit(e, md); }
        void visit(hir::ExprLitChar& e, MetaData md) override { Base::visit(e, md); }
        void visit(hir::ExprLitString& e, MetaData md) override { Base::visit(e, md); }

        void visit(hir::ExprLitArray& ea, MetaData md) override { Base::visit(ea, bump(md)); }
        void visit(hir::ExprUnary& eu, MetaData md) override { Base::visit(eu, bump(md)); }
        void visit(hir::ExprBinary& eb, MetaData md) override { Base::visit(eb, bump(md)); }
        void visit(hir::ExprAssign& ea, MetaData md) override { Base::visit(ea, bump(md)); }
        void visit(hir::ExprCall& ec, MetaData md) override { Base::visit(ec, bump(md)); }
        void visit(hir::ExprIndex& ei, MetaData md) override { Base::visit(ei, bump(md)); }
        void visit(hir::ExprField& ef, MetaData md) override { Base::visit(ef, bump(md)); }
        void visit(hir::ExprLitStruct& es, MetaData md) override { Base::visit(es, bump(md)); }
        void visit(hir::ExprCast& ec, MetaData md) override { Base::visit(ec, bump(md)); }

        // --- stmt ---
        void visit(hir::StmtBlock& sb, MetaData md) override { Base::visit(sb, bump(md)); }
        void visit(hir::StmtIf& si, MetaData md) override { Base::visit(si, bump(md)); }
        void visit(hir::StmtElseIf& se, MetaData md) override { Base::visit(se, bump(md)); }
        void visit(hir::StmtElse& se, MetaData md) override { Base::visit(se, bump(md)); }
        void visit(hir::StmtWhile& sw, MetaData md) override { Base::visit(sw, bump(md)); }
        void visit(hir::StmtDoWhile& sd, MetaData md) override { Base::visit(sd, bump(md)); }

        void visit(hir::StmtBreak& sb, MetaData md) override { Base::visit(sb, md); }
        void visit(hir::StmtContinue& sc, MetaData md) override { Base::visit(sc, md); }

        void visit(hir::StmtReturn& sr, MetaData md) override { Base::visit(sr, bump(md)); }
        void visit(hir::StmtVar& sv, MetaData md) override { Base::visit(sv, bump(md)); }
        void visit(hir::StmtExpr& se, MetaData md) override { Base::visit(se, bump(md)); }

        // --- methods ---
        void visit(hir::TraitMethod& fn, MetaData md) override { Base::visit(fn, bump(md)); }
        void visit(hir::ImplMethod& fn, MetaData md) override { Base::visit(fn, bump(md)); }
        void visit(hir::LoadFnDecl& fn, MetaData md) override { Base::visit(fn, bump(md)); }

        ~DefaultDeferingVisitor() noexcept override = default;
    };
}

#endif //INZ_DEFAULT_DEFERING_VISIT_HPP
