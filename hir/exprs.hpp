#ifndef INZ_EXPRS_HPP
#define INZ_EXPRS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "expr/assign_op.hpp"
#include "expr/binary_op_exression_kind.hpp"
#include "expr/unary_op_expression_kind.hpp"

namespace hir
{
    struct ExprPath
    {
        PathId path;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitInt
    {
        lex::SymId sym;
        std::optional<kl::rt::IntKind> kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitArray
    {
        std::vector<ExprId> elements;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitFloat
    {
        lex::SymId sym;
        std::optional<kl::rt::FloatKind> kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitBool
    {
        kl::rt::boolean value;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitChar
    {
        kl::rt::character value;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitString
    {
        lex::SymId sym;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprUnary
    {
        ast::UnaryOp op;
        ExprId rhs;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprBinary
    {
        ast::BinaryOp op;
        ExprId lhs;
        ExprId rhs;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprAssign
    {
        ast::AssignOp op;
        ExprId lhs;
        ExprId rhs;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprCall
    {
        ExprId callee;
        std::vector<TypeParamId> targs;
        std::vector<ExprId> args;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprIndex
    {
        ExprId base;
        ExprId index;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprField
    {
        ExprId base;
        lex::SymId field;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprLitStruct
    {
        ExprId type;
        std::vector<FieldInitId> fields;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ExprCast
    {
        ExprId expr;
        TypeId type;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
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

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
