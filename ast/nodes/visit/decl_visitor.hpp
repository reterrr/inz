//
// Created by yhwach on 8/29/25.
//

#ifndef DECL_VISITOR_HPP
#define DECL_VISITOR_HPP

#include "visitor.hpp"

namespace ast {
struct LoadFnDecl;
struct ParamDecl;
struct FnDecl;
struct ImportDecl;
struct StructDecl;
struct FieldDecl;
struct TypeParamDecl;
} // namespace ast

namespace ast::visitor {
struct DeclVisitor : Visitor<ParamDecl, FnDecl, LoadFnDecl, ImportDecl,
                             StructDecl, FieldDecl, TypeParamDecl> {};
} // namespace ast::visitor

#endif // DECL_VISITOR_HPP
