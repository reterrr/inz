//
// Created by yhwach on 9/30/25.
//

#ifndef SCOPE_STACK_HPP
#define SCOPE_STACK_HPP
#include <algorithm>

#include <ranges>
#include "symbol_table.hpp"

namespace sema {
    class ScopeStack {
        std::vector<SymbolTable> stack_;

    public:
        void enterScope(lex::SymId scope) { stack_.emplace_back({scope}); }
        void exitScope() { stack_.pop_back(); }

        bool declare(Symbol sym) {
            // ensure top exists
            if (stack_.empty()) enterScope();
            return stack_.back().declare(std::move(sym));
        }

        // Find first scope that has the name
        const SymbolBucket *lookup(lex::SymId id) const {
            for (const auto & it : std::ranges::reverse_view(stack_))
                if (auto b = it.lookup_local(id)) return b;
            return nullptr;
        }

        const SymbolBucket *lookup_local(lex::SymId id) const {
            return stack_.empty() ? nullptr : stack_.back().lookup_local(id);
        }
    };
}

#endif //SCOPE_STACK_HPP
