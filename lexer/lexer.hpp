//
// Created by yhwach on 7/26/25.
//

#ifndef LEXER_H
#define LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "generated/token.hpp"


class Scanner final : public yyFlexLexer {
    Token::Value current_token_;

public:
    using yyFlexLexer::yyFlexLexer;

    // declare the override that Flex will generate
    int yylex() override;

    void setCurrentToken(const Token::Value &token) {
        current_token_ = token;
    }

    const Token::Value &getCurrentToken() const {
        return current_token_;
    }
};


#endif
