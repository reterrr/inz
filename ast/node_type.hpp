//
// Created by yhwach on 8/20/25.
//

#ifndef NODE_TYPE_HPP
#define NODE_TYPE_HPP

#include <cstdint>

enum class NodeType {
    expression,
    int_,
    float_,
    bool_,
    string,

    function, //as well as either simple function or lambda
    call, // invokable things like function, lambda, maybe some functor

    sys_call, // ????? do i even need this?

    if_block,
    while_block,
    for_block,
    do_while_block,
    match_block,

    struct_block, // ?
    enum_block, // ?

    comment_block // do i even need this?
};

enum class RefType {
    Mut, NotMut
};

enum class PostOp {
    Increment, Decrement
};

enum class AssignOp {
    Assign, Add, Subtract, Multiply, Divide, Modulo
};

enum class NodeKind : uint16_t {
    Project,
    // ---- Expressions: literals
    Expr_IntLiteral,
    Expr_FloatLiteral,
    Expr_BoolLiteral,
    Expr_StringLiteral,
    Expr_ObjLiteral,

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

    // ---- Expressions: other
    Expr_Cond, // a ? b : c
    Expr_StructInit, // Type { field: expr, ... }
    Expr_DeclInit,

    // ---- Statements
    Stmt_VarDecl,
    Stmt_VarsDecl_Sugar,// (qualifiers + type) name [= init], ...
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

    // ---- Type syntax
    Type_Builtin, // int, double, bool, string, void, etc.
    Type_Path, // pkg.sub.Type
    Type_Array, // [T]

    // ---- Sentinels
};

#endif //NODE_TYPE_HPP
