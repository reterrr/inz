//
// Created by yhwach on 12/22/25.
//

#ifndef INZ_BLOCK_STMT_KIND_HPP
#define INZ_BLOCK_STMT_KIND_HPP


namespace ast
{
    enum class BlockKind
    {
        Anon, Fn, If, ElseIf, Else, While, DoWhile
    };
}

#endif //INZ_BLOCK_STMT_KIND_HPP
