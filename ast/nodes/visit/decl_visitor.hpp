//
// Created by yhwach on 8/29/25.
//

#ifndef DECL_VISITOR_HPP
#define DECL_VISITOR_HPP


#include "visitor.hpp"

namespace ast {
    struct ParamDecl;
    struct FunctionDecl;
    struct TypeAliasDecl;
    struct ImportDecl;
    struct VarDecl;
}

namespace ast::visitor {
    struct DeclVisitor
            : Visitor<ParamDecl,
                FunctionDecl,
                TypeAliasDecl,
                ImportDecl,
                VarDecl> {
    };
}

#endif //DECL_VISITOR_HPP
