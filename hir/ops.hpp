#ifndef INZ_OPS_HPP
#define INZ_OPS_HPP

#include <cstdint>

namespace hir
{
    enum class UnaryOp : uint8_t
    {
        Negation,
        LogicalNot,
        PreIncrement,
        PreDecrement,
        PostIncrement,
        PostDecrement
    };

    enum class BinaryOp : uint8_t
    {
        Add,
        Subtract,
        Multiply,
        Divide,
        Modulo,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,
        LogicalAnd,
        LogicalOr
    };

    enum class AssignOp : uint8_t
    {
        Assign,
        AddAssign,
        SubAssign,
        MulAssign,
        DivAssign
    };
}

#endif
