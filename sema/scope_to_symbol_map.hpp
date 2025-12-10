//
// Created by yhwach on 11/28/25.
//

#ifndef INZ_SCOPE_TO_SYMBOL_MAP_HPP
#define INZ_SCOPE_TO_SYMBOL_MAP_HPP

#include <map>

#include "token.hpp"

namespace sema::scope
{
    using ScopeId = uint32_t;

    class Scope2SymbolMap final
    {
        std::map<ScopeId, lex::SymId> map;

    public:
        void add(ScopeId scopeId, lex::SymId symId)
        {
            map.emplace(scopeId, symId);
        }

        Scope2SymbolMap() = default;
    };
}

#endif //INZ_SCOPE_TO_SYMBOL_MAP_HPP
