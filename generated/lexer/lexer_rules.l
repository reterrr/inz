%{
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "parser/parser.hpp"

#include "generated/token.hpp"
#include "lexer.hpp"

using lex::Type;
using lex::Token;
using lex::Loc;
using lex::Pos;

#define YY_DECL int Scanner::yylex()


static Pos cur;  // { line=1, column=1, offset=0 } by default


inline void advance(Pos& p, const char* text, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    unsigned char c = static_cast<unsigned char>(text[i]);
    ++p.offset;
    if (c == '\n') { ++p.line; p.column = 1; }
    else           { ++p.column; }
  }
}

static inline Loc token_loc_and_advance(const char* text, size_t n) {
  Loc L{};
  L.begin = cur;
  if (n) {
    L.end        = cur;
    L.end.column += static_cast<uint32_t>(n - 1);
    L.end.offset += static_cast<uint64_t>(n - 1);
  } else {
    L.end = cur;
  }
  advance(cur, text, n);   // finally move the global cursor
  return L;
}

#define EMIT_KIND(KIND) do { \
  auto* self = static_cast<Scanner*>(this); \
  Loc loc = token_loc_and_advance(yytext, (size_t)yyleng); \
  Token t{}; t.type_ = (KIND); t.loc_ = loc; \
  self->setCurrentToken(t); \
  return static_cast<int>(KIND); \
} while(0)

#define EMIT_INT() do { \
  auto* self = static_cast<Scanner*>(this); \
  Loc loc = token_loc_and_advance(yytext, (size_t)yyleng); \
  Token t{}; t.type_ = Type::TOK_INT_LITERAL; t.loc_ = loc; \
  t.u_.i64 = strtoll(yytext, nullptr, 10); \
  self->setCurrentToken(t); \
  return static_cast<int>(Type::TOK_INT_LITERAL); \
} while(0)

#define EMIT_FLOAT() do { \
  auto* self = static_cast<Scanner*>(this); \
  Loc loc = token_loc_and_advance(yytext, (size_t)yyleng); \
  Token t{}; t.type_ = Type::TOK_FLOAT_LITERAL; t.loc_ = loc; \
  t.u_.f64 = strtod(yytext, nullptr); \
  self->setCurrentToken(t); \
  return static_cast<int>(Type::TOK_FLOAT_LITERAL); \
} while(0)

#define EMIT_STRING() do { \
  auto* self = static_cast<Scanner*>(this); \
  const char* payload = yytext + 1; size_t n = (size_t)yyleng >= 2 ? (size_t)yyleng - 2 : 0; \
  lex::SymId sym = self->internString(payload, n); \
  Loc loc = token_loc_and_advance(yytext, (size_t)yyleng); \
  Token t{}; t.type_ = Type::TOK_STRING_LITERAL; t.loc_ = loc; \
  t.u_.sym = sym; \
  self->setCurrentToken(t); \
  return static_cast<int>(Type::TOK_STRING_LITERAL); \
} while(0)

#define EMIT_IDENT() do { \
  auto* self = static_cast<Scanner*>(this); \
  Loc loc = token_loc_and_advance(yytext, (size_t)yyleng); \
  lex::SymId sym = self->internIdent(yytext, (size_t)yyleng); \
  Token t{}; t.type_ = Type::TOK_IDENTIFIER; t.loc_ = loc; \
  t.u_.sym = sym; \
  self->setCurrentToken(t); \
  return static_cast<int>(Type::TOK_IDENTIFIER); \
} while(0)

%}

%option c++
%option yyclass="Scanner"
%option noyywrap
%option nounput noinput

%%

"if" { EMIT_KIND(Type::TOK_IF); }
"while" { EMIT_KIND(Type::TOK_WHILE); }
"do" { EMIT_KIND(Type::TOK_DO); }
"else" { EMIT_KIND(Type::TOK_ELSE); }
"struct" { EMIT_KIND(Type::TOK_STRUCT); }
"trait" { EMIT_KIND(Type::TOK_TRAIT); }
"enum" { EMIT_KIND(Type::TOK_ENUM); }
"fn" { EMIT_KIND(Type::TOK_FN); }
"type" { EMIT_KIND(Type::TOK_TYPE); }
"let" { EMIT_KIND(Type::TOK_LET); }
"return" { EMIT_KIND(Type::TOK_RETURN); }
"mut" { EMIT_KIND(Type::TOK_MUT); }
"pub" { EMIT_KIND(Type::TOK_PUB); }
"int" { EMIT_KIND(Type::TOK_INT); }
"bigint" { EMIT_KIND(Type::TOK_BIGINT); }
"magicint" { EMIT_KIND(Type::TOK_MAGICINT); }
"double" { EMIT_KIND(Type::TOK_DOUBLE); }
"bool" { EMIT_KIND(Type::TOK_BOOL); }
"void" { EMIT_KIND(Type::TOK_VOID); }
"string" { EMIT_KIND(Type::TOK_STRING); }
"break" { EMIT_KIND(Type::TOK_BREAK); }
"continue" { EMIT_KIND(Type::TOK_CONTINUE); }
"import" { EMIT_KIND(Type::TOK_IMPORT); }
"export" { EMIT_KIND(Type::TOK_EXPORT); }
"package" { EMIT_KIND(Type::TOK_PACKAGE); }
"as" { EMIT_KIND(Type::TOK_AS); }
"(" { EMIT_KIND(Type::TOK_LPAR); }
")" { EMIT_KIND(Type::TOK_RPAR); }
"[" { EMIT_KIND(Type::TOK_LBRACK); }
"]" { EMIT_KIND(Type::TOK_RBRACK); }
"{" { EMIT_KIND(Type::TOK_LCBRA); }
"}" { EMIT_KIND(Type::TOK_RCBRA); }
"," { EMIT_KIND(Type::TOK_COMMA); }
";" { EMIT_KIND(Type::TOK_SMCLN); }
":" { EMIT_KIND(Type::TOK_COLON); }
"." { EMIT_KIND(Type::TOK_DOT); }
"?" { EMIT_KIND(Type::TOK_QUESTION); }
"->" { EMIT_KIND(Type::TOK_ARROW); }
"++" { EMIT_KIND(Type::TOK_INC); }
"--" { EMIT_KIND(Type::TOK_DEC); }
"!" { EMIT_KIND(Type::TOK_NEGATION); }
"-" { EMIT_KIND(Type::TOK_NEG); }
"*" { EMIT_KIND(Type::TOK_STAR); }
"/" { EMIT_KIND(Type::TOK_SLASH); }
"%" { EMIT_KIND(Type::TOK_MODULO); }
"+" { EMIT_KIND(Type::TOK_PLUS); }
"-" { EMIT_KIND(Type::TOK_MINUS); }
"<" { EMIT_KIND(Type::TOK_LESS); }
"<=" { EMIT_KIND(Type::TOK_LEQ); }
">" { EMIT_KIND(Type::TOK_GREATER); }
">=" { EMIT_KIND(Type::TOK_GEQ); }
"==" { EMIT_KIND(Type::TOK_EQUAL); }
"!=" { EMIT_KIND(Type::TOK_NEQUAL); }
"&&" { EMIT_KIND(Type::TOK_BOOL_AND); }
"||" { EMIT_KIND(Type::TOK_BOOL_OR); }
"=" { EMIT_KIND(Type::TOK_ASSIGN); }
"+=" { EMIT_KIND(Type::TOK_PLUS_ASSIGN); }
"-=" { EMIT_KIND(Type::TOK_MIN_ASSIGN); }
"*=" { EMIT_KIND(Type::TOK_MUL_ASSIGN); }
"/=" { EMIT_KIND(Type::TOK_DIV_ASSIGN); }
\"([^\\\n"]|\\.)*\"             { EMIT_STRING(); }

[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?  { EMIT_FLOAT(); }
\.[0-9]+([eE][+-]?[0-9]+)?        { EMIT_FLOAT(); }
[0-9]+([eE][+-]?[0-9]+)           { EMIT_FLOAT(); }

[0-9]+                             { EMIT_INT(); }

[a-zA-Z_][a-zA-Z0-9_]*             { EMIT_IDENT(); }

[ \t]+                              { advance(cur, yytext, (size_t)yyleng); }
(\r\n|\r|\n)+                       { advance(cur, yytext, (size_t)yyleng); }
"//"[^\r\n]*                        { advance(cur, yytext, (size_t)yyleng); }
"/*"([^*]|\*+[^*/])*"*/"            { advance(cur, yytext, (size_t)yyleng); }

.                                   { advance(cur, yytext, (size_t)yyleng); }

<<EOF>> {
  auto* self = static_cast<Scanner*>(this);
  Loc loc{}; loc.begin = cur; loc.end = cur;  /* zero-length at end */
  Token t{}; t.type_ = Type::TOK_END; t.loc_ = loc;
  self->setCurrentToken(t);
  return 0;   /* Bison EOF */
}

%%