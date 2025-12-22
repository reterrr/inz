#ifndef INZ_EXPRS_HPP
#define INZ_EXPRS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "ops.hpp"
#include "token.hpp"
#include "types.hpp"

namespace hir
{
    struct ExprPath
    {
        PathId path;
        std::vector<TypeParamId> targs;
    };

    struct ExprLitInt
    {
        lex::SymId sym;
        std::optional<kl::rt::IntKind> kind;
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
        UnaryOp op;
        ExprId rhs;
    };

    struct ExprBinary
    {
        BinaryOp op;
        ExprId lhs;
        ExprId rhs;
    };

    struct ExprAssign
    {
        AssignOp op;
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
        TypeId type;
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
