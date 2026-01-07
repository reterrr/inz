#ifndef INZ_EXPRS_HPP
#define INZ_EXPRS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "hir_types.hpp"
#include "ids.hpp"
#include "value_res_kind.hpp"
#include "expr/assign_op.hpp"
#include "expr/binary_op_exression_kind.hpp"
#include "expr/unary_op_expression_kind.hpp"

namespace hir
{
    struct ValueRes
    {
        ValueResKind kind;
        ValueResId id;
        ModuleId module;
    };

    struct ExprPath
    {
        PathId path;
        lex::Loc loc;
        ValueRes res{};
    };

    struct ExprLitInt
    {
        lex::SymId sym;
        std::optional<kl::rt::IntKind> kind;
        lex::Loc loc;
    };

    struct ExprLitArray
    {
        std::vector<ExprId> elements;
        lex::Loc loc;
    };

    struct ExprLitFloat
    {
        lex::SymId sym;
        std::optional<kl::rt::FloatKind> kind;
        lex::Loc loc;
    };

    struct ExprLitBool
    {
        kl::rt::boolean value;
        lex::Loc loc;
    };

    struct ExprLitChar
    {
        kl::rt::character value;
        lex::Loc loc;
    };

    struct ExprLitString
    {
        lex::SymId sym;
        lex::Loc loc;
    };

    struct ExprUnary
    {
        ast::UnaryOp op;
        ExprId rhs;
        lex::Loc loc;
    };

    struct ExprBinary
    {
        ast::BinaryOp op;
        ExprId lhs;
        ExprId rhs;
        lex::Loc loc;
    };

    struct ExprAssign
    {
        ast::AssignOp op;
        ExprId lhs;
        ExprId rhs;
        lex::Loc loc;
    };

    struct ExprCall
    {
        ExprId callee;
        std::vector<TypeParamId> targs;
        std::vector<ExprId> args;
        lex::Loc loc;
    };

    struct ExprIndex
    {
        ExprId base;
        ExprId index;
        lex::Loc loc;
    };

    struct ExprField
    {
        ExprId base;
        lex::SymId field;
        lex::Loc loc;
    };

    struct ExprLitStruct
    {
        ExprId type;
        std::vector<FieldInitId> fields;
        lex::Loc loc;

        TypeRes type_res{};
    };

    struct ExprCast
    {
        ExprId expr;
        TypeId type;
        lex::Loc loc;
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
        ExprKind kind;
    };
}

#endif
