//
// Created by yhwach on 10/19/25.
//

#ifndef VARS_DECL_HPP
#define VARS_DECL_HPP

#include <vector>

#include "decl.hpp"
#include "visit/decl_visitor.hpp"

namespace ast
{
    struct VarDecl;
    struct Expr;

    struct VarsDecl final : Decl
    {
        std::vector<lex::SymId> varDecls;
        std::vector<Expr*> assignments_;
        Type* type{nullptr};
        TypeRegion region;

        VarsDecl(std::vector<lex::SymId>&& varDecls,
                 std::vector<Expr*>&& assignments,
                 Type* type,
                 TypeRegion region,
                 const lex::Loc& loc)
            : Decl(NodeKind::Decl_Vars_Sugar, loc),
              varDecls(std::move(varDecls)),
              assignments_(std::move(assignments)),
              type(type),
              region(region)
        {
            std::ranges::for_each(assignments_, [this](Expr* e)
            {
                e->parent = this;
            });
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void VarsDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //VARS_DECL_HPP
