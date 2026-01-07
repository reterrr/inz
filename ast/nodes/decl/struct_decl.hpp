//
// Created by yhwach on 9/14/25.
//

#ifndef STRUCT_DECL_HPP
#define STRUCT_DECL_HPP

#include <utility>
#include <vector>
#include <algorithm>

#include "decl.hpp"
#include "field_decl.hpp"
#include "type_param_decl.hpp"
#include "visit/decl_visitor.hpp"
#include "type/type_parametrized_decl.hpp"


namespace ast
{
    struct StructDecl final : Decl, TypeParametrizedDecl
    {
        lex::SymId name_;
        std::vector<FieldDecl*> fields_;
        bool isExported_;

        StructDecl(const lex::SymId name,
                   std::vector<TypeParamDecl*>&& typeParamsDecls,
                   std::vector<FieldDecl*>&& fields,
                   const bool isExported,
                   const lex::Loc& loc)
            : Decl(NodeKind::Decl_Struct, loc),
              TypeParametrizedDecl(TypeParametrizedKind::Struct, std::move(typeParamsDecls), this),
              name_(name), fields_(std::move(fields)), isExported_(isExported)
        {
            std::ranges::for_each(fields_, [this](FieldDecl* field)
            {
                field->parent = this;
            });
        }

        void accept(visitor::DeclVisitor&) override;
    };

    inline void StructDecl::accept(visitor::DeclVisitor& v)
    {
        v.visit(*this);
    }
}

#endif //STRUCT_DECL_HPP
