//
// Created by yhwach on 9/14/25.
//

#ifndef FIELD_DECL_HPP
#define FIELD_DECL_HPP

#include "decl.hpp"
#include "visit/decl_visitor.hpp"
#include "field_visibility.hpp"

namespace ast
{
    struct FieldDecl final : Decl
    {
        lex::SymId name_;
        TypeExpr* type_;
        Visibility visibility_;

        FieldDecl(const lex::SymId name, TypeExpr* type,
                  Visibility visibility, const lex::Loc& loc)
            : Decl(NodeKind::Decl_Field, loc), name_(name),
              type_(type), visibility_(visibility)
        {
            type_->parent = this;
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void FieldDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //FIELD_DECL_HPP
