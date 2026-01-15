//
// Created by yhwach on 8/20/25.
//

#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#include <cstdint>

enum class NodeKind : uint32_t {
  // ---- Expressions: literals
  // ---- Expressions: variables & references
  Expr_Var, // identifier use
  Expr_Ref, // &x / &mut x
            // `self` value in method bodies

  // ---- Expressions: operators
  Expr_Unary,
  Expr_Binary,
  Expr_Assign,
  Expr_Postfix,

  // ---- Expressions: access / call
  Expr_Field,
  Expr_FieldInit,
  Expr_Index,
  Expr_Call,
  Expr_Literal,

  // ---- Expressions: other
  Expr_Cond,
  Expr_StructInit,
  Expr_DeclInit,
  Expr_Type,
  Expr_Path,
  Expr_Cast,

  // ---- Statements
  Stmt_Var,
  Stmt_Return,
  Stmt_If,
  Stmt_While,
  Stmt_DoWhile,
  Stmt_Break,
  Stmt_Continue,
  Stmt_Block,
  Stmt_ElseIf,
  Stmt_Else,
  Stmt_Expr,

  // ---- Declarations
  Decl_Struct,
  Decl_Fn,
  Decl_LoadFn,
  Decl_Import,
  Decl_Module,
  Decl_Param,
  Decl_Field,
  Decl_TypeParam,

  Count,

};

#endif // NODE_TYPE_HPP
