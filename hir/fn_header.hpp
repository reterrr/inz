//
// Created by yhwach on 12/27/25.
//

#ifndef INZ_FN_HEADER_HPP
#define INZ_FN_HEADER_HPP
#include <vector>

#include "ids.hpp"
#include "token.hpp"


namespace hir
{
    struct FnHeader
    {
        lex::SymId name;

        std::vector<ParamId> params;
        std::optional<TypeId> return_type;
    };
}
#endif //INZ_FN_HEADER_HPP
