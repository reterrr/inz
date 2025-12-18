//
// Created by yhwach on 8/20/25.
//

#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#include <cstdint>

enum class RefType
{
    Mut, NotMut
};

enum class PostOp
{
    Increment, Decrement
};

enum class AssignOp
{
    Assign, Add, Subtract, Multiply, Divide, Modulo
};

enum class NodeKind : uint16_t
{
    Project,
    // ---- Expressions: literals
    // ---- Expressions: variables & references
    Expr_Var, // identifier use
    Expr_Ref, // &x / &mut x
    Expr_Deref, // *p

    // ---- Expressions: operators
    Expr_Unary, // -x, !x, ++x, --x (prefix)
    Expr_Binary, // + - * / % < <= > >= == != && ||
    Expr_Assign, // =, +=, -=, *=, /=
    Expr_Postfix, // x++, x--

    // ---- Expressions: access / call
    Expr_Field, // e.name
    Expr_FieldInit,
    Expr_Index, // e[i]
    Expr_Call, // f(a, b, ...)
    Expr_Literal,

    // ---- Expressions: other
    Expr_Cond, // a ? b : c
    Expr_StructInit, // Type { field: expr, ... }
    Expr_DeclInit,

    // ---- Statements
    Stmt_VarDecl,
    Stmt_VarsDecl_Sugar, // (qualifiers + type) name [= init], ...
    Stmt_Return,
    Stmt_If,
    Stmt_While,
    Stmt_DoWhile,
    Stmt_Break,
    Stmt_Continue,
    Stmt_Block,
    Stmt_Expr, // expression statement

    // ---- Declarations
    Decl_Struct,
    Decl_Enum,
    Decl_Fn,
    Decl_TypeAlias,
    Decl_Import,
    Decl_Export,
    Decl_Module,
    Decl_Package,
    Decl_Param,
    Decl_Var,
    Decl_Vars_Sugar,
    Decl_Field,

    // ---- Sentinels
    Expr_Type,
    Expr_Path,
    Expr_Cast,
    Stmt_ElseIf,
    Stmt_Else,
};

#endif //NODE_TYPE_HPP
