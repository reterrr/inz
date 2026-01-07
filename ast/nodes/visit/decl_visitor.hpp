//
// Created by yhwach on 8/29/25.
//

#ifndef DECL_VISITOR_HPP
#define DECL_VISITOR_HPP


#include "visitor.hpp"

namespace ast
{
    struct LoadFnDecl;
    struct ImplFnDecl;
    struct TraitFnDecl;
    struct ParamDecl;
    struct FnDecl;
    struct TypeAliasDecl;
    struct ImportDecl;
    struct StructDecl;
    struct FieldDecl;
    struct TypeParamDecl;
    struct TraitDecl;
    struct ImplDecl;
    struct SelfParamDecl;
}

namespace ast::visitor
{
    struct DeclVisitor
        : Visitor<ParamDecl,
                  SelfParamDecl,
                  FnDecl,
                  LoadFnDecl,
                  TraitFnDecl,
                  ImplFnDecl,
                  TypeAliasDecl,
                  ImportDecl,
                  StructDecl,
                  TraitDecl,
                  ImplDecl,
                  FieldDecl,
                  TypeParamDecl>
    {
    };
}

#endif //DECL_VISITOR_HPP
