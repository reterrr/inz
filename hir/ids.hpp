//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_IDS_HPP
#define INZ_IDS_HPP
#include <cstdint>
#include <vector>
#include "token.hpp"


namespace hir
{
    using ModuleId = uint32_t;
    using DeclId = uint32_t;
    using StmtId = uint32_t;
    using ExprId = uint32_t;
    using TypeId = uint32_t;
    using ImportId = uint32_t;
    using ParamId = uint32_t;
    using FieldDeclId = uint32_t;
    using FieldInitId = uint32_t;
    using BlockId = uint32_t;
    using PathId = uint32_t;
    using TypeParamId = uint32_t;
    using UnitId = uint32_t;
    using DiagId = uint32_t;
    using GenericsId = uint32_t;
    using MethodId = uint32_t;

    struct PathEntry
    {
        std::vector<lex::SymId> path;
    };
}
#endif //INZ_IDS_HPP
