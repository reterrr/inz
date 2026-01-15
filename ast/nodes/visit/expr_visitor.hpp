//
// Created by yhwach on 8/21/25.
//

#ifndef EXPR_VISITOR_HPP
#define EXPR_VISITOR_HPP

#include "visitor.hpp"

namespace ast {
struct UnaryExpr;
struct BinaryExpr;
struct IntLiteralExpr;
struct FloatLiteralExpr;
struct ArrayLiteralExpr;
struct CharLiteralExpr;
struct StructLiteralExpr;
struct AssignExpr;
struct FieldExpr;
struct PathExpr;
struct CallExpr;
struct CastExpr;
struct RefExpr;
struct IndexExpr;
struct BoolLiteralExpr;
struct FieldInitExpr;
struct StringLiteralExpr;

struct ArrayTypeExpr;
struct PathTypeExpr;
struct RefTypeExpr;
struct BuiltinTypeExpr;
} // namespace ast

namespace ast::visitor {
struct ExprVisitor
    : Visitor<IntLiteralExpr, FloatLiteralExpr, UnaryExpr, BinaryExpr,
              StructLiteralExpr, AssignExpr, FieldExpr, CallExpr, CastExpr,
              RefExpr, IndexExpr, BoolLiteralExpr, FieldInitExpr, ArrayTypeExpr,
              PathTypeExpr, RefTypeExpr, PathExpr, BuiltinTypeExpr,
              CharLiteralExpr, ArrayLiteralExpr, StringLiteralExpr> {};
} // namespace ast::visitor

#endif // EXPR_VISITOR_HPP
