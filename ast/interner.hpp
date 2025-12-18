//
// Created by yhwach on 12/18/25.
//

#ifndef INZ_INTERNER_HPP
#define INZ_INTERNER_HPP

#include <deque>
#include <string>
#include <unordered_map>

#include "token.hpp"

namespace ast
{
    template <typename Pool = std::deque<std::string>, typename Table = std::unordered_map<
                  std::string_view, lex::SymId>>
        requires requires(Pool& pool, const Pool& cpool, Table& table, std::string_view sv)
        {
            pool.emplace_back(sv);
            pool.back();
            cpool.size();
            cpool[std::size_t{}];

            table.find(sv);
            table.end();
            table.emplace(sv, lex::SymId{});
        }
    struct Interner
    {
        Pool pool_;
        Table table_;

        lex::SymId intern(std::string_view s)
        {
            if (auto it = table_.find(s); it != table_.end())
                return it->second;

            pool_.emplace_back(s);
            const std::string& stored = pool_.back();

            const auto idx = static_cast<size_t>(pool_.size() - 1);
            const auto id = static_cast<lex::SymId>(idx);

            std::string_view key{stored.data(), stored.size()};
            table_.emplace(key, id);

            return id;
        }

        [[nodiscard]]
        std::string_view view(lex::SymId id) const
        {
            const auto idx = static_cast<size_t>(id);

            const std::string& stored = pool_[idx];

            return std::string_view{stored.data(), stored.size()};
        }
    };
}

#endif //INZ_INTERNER_HPP
