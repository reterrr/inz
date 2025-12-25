//
// Created by yhwach on 12/23/25.
//

#ifndef INZ_TYPE_EXPR_KIND_HPP
#define INZ_TYPE_EXPR_KIND_HPP

namespace ast
{
    enum class TypeExprKind
    {
        Builtin, Array, Path, Ref, Callable
    };
}

#endif //INZ_TYPE_EXPR_KIND_HPP
