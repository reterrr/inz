//
// Created by yhwach on 7/26/25.
//

#include "lexer.hpp"

#include <map>


lex::SymId Scanner::internCommon(const char *s, std::size_t n,
                                 std::vector<std::string> &storage,
                                 std::map<std::string_view, lex::SymId> &table) {
    // Probe by string_view into existing storage (stable addresses)
    const std::string_view key{s, n};
    auto it = table.find(key);
    if (it != table.end()) return it->second;

    // Store a new owned copy to keep the bytes alive
    storage.emplace_back(s, n);
    std::string &owned = storage.back();
    std::string_view view{owned.data(), owned.size()};

    const auto id = static_cast<lex::SymId>(table.size() + 1); // 0 reserved if you like
    table.emplace(view, id);

    return id;
}
