//
// Created by yhwach on 8/21/25.
//

#ifndef BINARY_OP_EXPRESSION_KIND_HPP
#define BINARY_OP_EXPRESSION_KIND_HPP

namespace ast {
    enum class BinaryOp {
        add,
        subtract,
        multiply,
        divide,
        modulo,
        logical_and,
        logical_or,

        equal,
        not_equal,

        less,
        greater,
        less_equal,
        greater_equal
    };
}

#endif //BINARY_OP_EXPRESSION_KIND_HPP
