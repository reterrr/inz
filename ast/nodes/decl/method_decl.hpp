//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_METHOD_DECL_HPP
#define INZ_METHOD_DECL_HPP
#include "decl.hpp"

namespace ast
{
    struct MethodDecl : Decl
    {
        MethodDecl(NodeKind nodeType, const lex::Loc& loc)
            : Decl(nodeType, loc)
        {
        }
    };
}

#endif //INZ_METHOD_DECL_HPP