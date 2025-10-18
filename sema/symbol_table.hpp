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

namespace sema {
    using SymbolBucket = std::vector<Symbol>;

    class SymbolTable final {
        std::unordered_map<lex::SymId, SymbolBucket> table_;
        const std::vector<lex::SymId> scope_;

    public:
        explicit SymbolTable(std::vector<lex::SymId> scope)
            : scope_(std::move(scope)) {
        }

        std::vector<lex::SymId> current() const {
            return scope_;
        }

        bool declare(Symbol &sym) {
            auto &bucket = table_[sym.id];

            if (sym.kind != SymbolKind::Func) {
                for (auto &s: bucket) {
                    if (s.id == sym.id) {
                        return false;
                    }
                }
            }
            sym.overload_index = static_cast<uint32_t>(bucket.size());
            bucket.push_back(std::move(sym));

            return true;
        }

        const SymbolBucket *lookup_local(lex::SymId name) const {
            if (auto it = table_.find(name); it != table_.end())
                return &it->second;

            return nullptr;
        }

        bool contains_local(lex::SymId name) const {
            return lookup_local(name) != nullptr;
        }
    };
}

#endif //SYMBOL_TABLE_HPP
