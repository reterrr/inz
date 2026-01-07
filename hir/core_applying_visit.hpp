//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_CORE_APPLYING_VISIT_HPP
#define INZ_CORE_APPLYING_VISIT_HPP
#include "visitor.hpp"

namespace hir
{
    template <typename It, typename... MetaData>
    struct CoreApplyingVisitor : Visitor<It, MetaData...>
    {
        using Base = hir::Visitor<It, MetaData...>;
        using Base::Base;
        using Base::visit;

        virtual void visit(hir::Module&, MetaData...) override
        {
        }

        virtual void visit(hir::Import&, MetaData...) override
        {
        }

        virtual void visit(hir::TypeParam&, MetaData...) override
        {
        }

        virtual void visit(hir::ParamSelf&, MetaData...) override
        {
        }

        virtual void visit(hir::ParamNamed&, MetaData...) override
        {
        }

        virtual void visit(hir::StructFieldDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::StructFieldInit&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtBlock&, MetaData...) override
        {
        }

        virtual void visit(hir::FnDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::StructDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::TypeAliasDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::TraitDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::ImplDecl&, MetaData...) override
        {
        }

        virtual void visit(hir::TypeBuiltin&, MetaData...) override
        {
        }

        virtual void visit(hir::TypePath&, MetaData...) override
        {
        }

        virtual void visit(hir::TypeRef&, MetaData...) override
        {
        }

        virtual void visit(hir::TypeArray&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprPath&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitInt&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitArray&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitFloat&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitBool&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitChar&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitString&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprUnary&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprBinary&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprAssign&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprCall&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprIndex&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprField&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprLitStruct&, MetaData...) override
        {
        }

        virtual void visit(hir::ExprCast&, MetaData...) override
        {
        }

        virtual void visit(hir::Block&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtIf&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtElseIf&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtElse&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtWhile&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtDoWhile&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtBreak&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtContinue&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtReturn&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtVar&, MetaData...) override
        {
        }

        virtual void visit(hir::StmtExpr&, MetaData...) override
        {
        }

        virtual void visit(hir::TraitMethod&, MetaData...) override
        {
        }

        virtual void visit(hir::ImplMethod&, MetaData...) override
        {
        }

        virtual void visit(LoadFnDecl&, MetaData...) override
        {
        }
    };
}
#endif //INZ_CORE_APPLYING_VISIT_HPP
