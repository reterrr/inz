//
// Created by yhwach on 9/25/25.
//

#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <token.hpp>
#include <unordered_map>
#include <utility>
#include <vector>

#include "symbol.hpp"

namespace sema
{
    using ScopeId = uint32_t;

    class SymbolTable final
    {
        std::unordered_map<lex::SymId, Symbol> table_;

    public:
        explicit SymbolTable()
            : table_()
        {
        }

        bool declare(Symbol& sym)
        {
            auto& s = table_[sym.id];

            if (s.id == sym.id)
            {
                return false;
            }

            table_.emplace(sym.id, sym);

            return true;
        }

        const SymbolBucket* lookup_local(lex::SymId name) const
        {
            if (const auto it = table_.find(name); it != table_.end())
                return &it->second;

            return nullptr;
        }

        bool contains_local(lex::SymId name) const
        {
            return lookup_local(name) != nullptr;
        }
    };
}

#endif //SYMBOL_TABLE_HPP
