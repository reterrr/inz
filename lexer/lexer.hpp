#ifndef LEXER_H
#define LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <cstddef>
#include <string_view>

#include "compiler_context.hpp"
#include "interner.hpp"
#include "generated/token.hpp"

class Scanner final : public yyFlexLexer
{
    lex::Token current_token_{};
    lex::Pos cur_{};

    ast::Interner<>& stringInterner_;
    ast::Interner<>& identInterner_;
    ast::Interner<>& numericInterner_;

public:
    explicit Scanner(
        CompilerContext& compilerContext,
        std::istream* in = &std::cin,
        std::ostream* out = &std::cout)
        : yyFlexLexer(in, out),
          stringInterner_(compilerContext.stringInterner),
          identInterner_(compilerContext.identInterner),
          numericInterner_(compilerContext.numericInterner)
    {
    }

    int yylex() override;

    void setCurrentToken(const lex::Token& t) { current_token_ = t; }
    const lex::Token& getCurrentToken() const { return current_token_; }


    lex::Pos& cur() { return cur_; }
    const lex::Pos& cur() const { return cur_; }
    void reset_location() { cur_ = {}; }

    lex::SymId internIdent(const char* s, std::size_t n) const
    {
        return identInterner_.intern(std::string_view{s, n});
    }

    lex::SymId internString(const char* s, std::size_t n) const
    {
        return stringInterner_.intern(std::string_view{s, n});
    }

    lex::SymId internNumeric(const char* s, std::size_t n) const
    {
        return numericInterner_.intern(std::string_view{s, n});
    }
};

#endif
