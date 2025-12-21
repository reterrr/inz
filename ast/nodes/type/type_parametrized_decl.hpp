//
// Created by yhwach on 12/14/25.
//

#ifndef INZ_TYPE_PARAMETRIZED_HPP
#define INZ_TYPE_PARAMETRIZED_HPP
#include <vector>

#include "sema/type/type.hpp"
#include "type_param_decl.hpp"

namespace ast
{
    struct TypeParametrizedDecl
    {
        enum class TypeParametrizedKind { Struct, Function };

        TypeParametrizedKind kind_;
        std::vector<TypeParamDecl*> typeParamsDecls_;

        explicit TypeParametrizedDecl(TypeParametrizedKind kind,
                                      std::vector<TypeParamDecl*>&& typeParamsDecls,
                                      Decl* parent)
            : kind_(kind), typeParamsDecls_(std::move(typeParamsDecls))
        {
            std::ranges::for_each(typeParamsDecls_, [parent](auto& typeParamDecl)
            {
                typeParamDecl->parent = parent;
            });
        }
    };
}

#endif //INZ_TYPE_PARAMETRIZED_HPP
