#ifndef LEXER_H
#define LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <cstddef>
#include <string_view>

#include "interner.hpp"
#include "generated/token.hpp"

class Scanner final : public yyFlexLexer
{
    lex::Token current_token_{};

    ast::Interner<>& stringInterner_;
    ast::Interner<>& identInterner_;
    ast::Interner<>& numericInterner_;

public:
    explicit Scanner(
        ast::Interner<>& stringInterner,
        ast::Interner<>& identInterner,
        ast::Interner<>& numericInterner,
        std::istream* in = &std::cin,
        std::ostream* out = &std::cout)
        : yyFlexLexer(in, out),
          stringInterner_(stringInterner),
          identInterner_(identInterner),
          numericInterner_(numericInterner)
    {
    }

    int yylex() override;

    void setCurrentToken(const lex::Token& t) { current_token_ = t; }
    const lex::Token& getCurrentToken() const { return current_token_; }

    lex::SymId internIdent(const char* s, const std::size_t n) const
    {
        return identInterner_.intern(std::string_view{s, n});
    }

    lex::SymId internString(const char* s, const std::size_t n) const
    {
        return stringInterner_.intern(std::string_view{s, n});
    }

    lex::SymId internNumeric(const char* s, const std::size_t n) const
    {
        return numericInterner_.intern(std::string_view{s, n});
    }
};

#endif
