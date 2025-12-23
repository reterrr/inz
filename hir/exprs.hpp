#ifndef INZ_EXPRS_HPP
#define INZ_EXPRS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "token.hpp"
#include "types.hpp"
#include "expr/assign_op.hpp"
#include "expr/binary_op_exression_kind.hpp"
#include "expr/unary_op_expression_kind.hpp"

namespace hir
{
    struct ExprPath
    {
        PathId path;
    };

    struct ExprLitInt
    {
        lex::SymId sym;
        std::optional<kl::rt::IntKind> kind;
    };

    struct ExprLitArray
    {
        std::vector<ExprId> elements;
    };

    struct ExprLitFloat
    {
        lex::SymId sym;
        std::optional<kl::rt::FloatKind> kind;
    };

    struct ExprLitBool
    {
        kl::rt::boolean value;
    };

    struct ExprLitChar
    {
        kl::rt::character value;
    };

    struct ExprLitString
    {
        lex::SymId sym;
    };

    struct ExprUnary
    {
        ast::UnaryOp op;
        ExprId rhs;
    };

    struct ExprBinary
    {
        ast::BinaryOp op;
        ExprId lhs;
        ExprId rhs;
    };

    struct ExprAssign
    {
        ast::AssignOp op;
        ExprId lhs;
        ExprId rhs;
    };

    struct ExprCall
    {
        ExprId callee;
        std::vector<TypeParamId> targs;
        std::vector<ExprId> args;
    };

    struct ExprIndex
    {
        ExprId base;
        ExprId index;
    };

    struct ExprField
    {
        ExprId base;
        lex::SymId field;
    };

    struct ExprLitStruct
    {
        ExprId type;
        std::vector<FieldInitId> fields;
    };

    struct ExprCast
    {
        ExprId expr;
        TypeId type;
    };

    using ExprKind = std::variant<
        ExprPath,
        ExprLitInt,
        ExprLitArray,
        ExprLitFloat,
        ExprLitBool,
        ExprLitChar,
        ExprLitString,
        ExprUnary,
        ExprBinary,
        ExprAssign,
        ExprCall,
        ExprIndex,
        ExprField,
        ExprLitStruct,
        ExprCast
    >;

    struct Expr
    {
        lex::Loc loc;
        ExprKind kind;
    };
}

#endif
