//
// Created by yhwach on 8/21/25.
//

#ifndef UNARY_EXPRESSION_KIND_HPP
#define UNARY_EXPRESSION_KIND_HPP

namespace ast {
    enum class UnaryOp {
        preincrement,
        predecrement,
        postincrement,
        postdecrement,
        negation,
        logical_not,
        deref,
        addr_of,
        addr_of_mut
    };
}

#endif //UNARY_EXPRESSION_KIND_HPP
