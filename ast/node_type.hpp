//
// Created by yhwach on 8/20/25.
//

#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#include <cstdint>

enum class NodeKind : uint32_t
{
    Project,
    // ---- Expressions: literals
    // ---- Expressions: variables & references
    Expr_Var, // identifier use
    Expr_Ref, // &x / &mut x

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
    Expr_Type,
    Expr_Path,
    Expr_Cast,

    // ---- Statements
    Stmt_Var, // (qualifiers + type) name [= init], ...
    Stmt_Return,
    Stmt_If,
    Stmt_While,
    Stmt_DoWhile,
    Stmt_Break,
    Stmt_Continue,
    Stmt_Block,
    Stmt_ElseIf,
    Stmt_Else,
    Stmt_Expr, // expression statement

    // ---- Declarations
    Decl_Struct,
    Decl_Fn,
    Decl_TypeAlias,
    Decl_Import,
    Decl_Module,
    Decl_Param,
    Decl_Field,
    Decl_TypeParam,

    // ---- Sentinels
    Count, //FATAL: must be last!!!!! do not move and do nor insert after
};

#endif //NODE_TYPE_HPP
