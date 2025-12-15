//
// Created by yhwach on 8/21/25.
//

#ifndef EXPR_VISITOR_HPP
#define EXPR_VISITOR_HPP


#include "visitor.hpp"

namespace ast
{
    struct UnaryExpr;
    struct BinaryExpr;
    struct IntLiteralExpr;
    struct FloatLiteralExpr;
    struct StringLiteralExpr;
    struct PathLiteralExpr;
    struct AssignExpr;
    struct InitDeclarator;
    struct FieldExpr;
    struct CallExpr;
    struct RefExpr;
    struct IndexExpr;
    struct BoolLiteralExpr;
    struct FieldInitExpr;

    struct ArrayTypeExpr;
    struct PathTypeExpr;
    struct RefTypeExpr;
    struct BuiltinTypeExpr;
}

namespace ast::visitor
{
    struct ExprVisitor
        : Visitor<IntLiteralExpr, FloatLiteralExpr, UnaryExpr,
                  BinaryExpr, StringLiteralExpr, PathLiteralExpr,
                  AssignExpr, InitDeclarator, FieldExpr, CallExpr,
                  RefExpr, IndexExpr, BoolLiteralExpr, FieldInitExpr,
                  ArrayTypeExpr, PathTypeExpr, RefTypeExpr, BuiltinTypeExpr>
    {
    };
}

#endif //EXPR_VISITOR_HPP
