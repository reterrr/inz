#ifndef LEXER_H
#define LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "../generated/token.hpp"


class Scanner final : public yyFlexLexer {
    lex::Token current_token_{};

    std::vector<std::string> string_pool_;
    std::map<std::string_view, lex::SymId> string_ids_;

    std::vector<std::string> ident_pool_;
    std::map<std::string_view, lex::SymId> ident_ids_;

public:
    explicit Scanner(std::istream *in = &std::cin, std::ostream *out = &std::cout)
        : yyFlexLexer(in, out) {
    }

    int yylex() override;

    void setCurrentToken(const lex::Token &t) { current_token_ = t; }
    const lex::Token &getCurrentToken() const { return current_token_; }

    lex::SymId internIdent(const char *s, const std::size_t n) {
        return internCommon(s, n, ident_pool_, ident_ids_);
    }

    lex::SymId internString(const char *s, const std::size_t n) {
        return internCommon(s, n, string_pool_, string_ids_);
    }

private:
    lex::SymId internCommon(const char *s, std::size_t n,
                            std::vector<std::string> &storage,
                            std::map<std::string_view, lex::SymId> &table);
};

#endif
