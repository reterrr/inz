%{


#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "generated/token.hpp"
#include "lexer.hpp"

using lex::Type;
using lex::Token;
using lex::Loc;

// Running position
static uint32_t g_column = 1;
static uint64_t g_offset = 0;

// Build a Loc for a token that does not span newlines
static inline Loc make_loc(uint32_t line, uint32_t start_col, uint32_t len, uint64_t start_off) {
    Loc L{};
    L.begin.line   = line;
    L.begin.column = start_col;
    L.begin.offset = start_off;

    L.end.line   = line;
    if (len) {
        L.end.column = start_col + (len - 1);
        L.end.offset = start_off + (len - 1);
    } else {
        L.end.column = start_col;
        L.end.offset = start_off;
    }
    return L;
}

// Advance counters for arbitrary text (used in comments/newlines)
static inline void bump_pos_for_text(const char* s, size_t n, int& yylineno_ref) {
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '\n') { ++yylineno_ref; g_column = 1; }
        else { ++g_column; }
        ++g_offset;
    }
}

#define EMIT_SIMPLE(KIND) do { \
    auto* self = static_cast<Scanner*>(this); \
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset); \
    Token t{}; t.type_ = KIND; t.loc_ = loc; \
    self->setCurrentToken(t); \
    g_column += yyleng; g_offset += yyleng; \
    return static_cast<int>(KIND); \
} while(0)

#define EMIT_INT() do { \
    auto* self = static_cast<Scanner*>(this); \
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset); \
    Token t{}; t.type_ = Type::TOK_INT_LITERAL; t.loc_ = loc; \
    /* simple strtoll; you can add base/underscores later */ \
    t.u_.i64 = strtoll(yytext, nullptr, 10); \
    self->setCurrentToken(t); \
    g_column += yyleng; g_offset += yyleng; \
    return static_cast<int>(Type::TOK_INT_LITERAL); \
} while(0)

#define EMIT_FLOAT() do { \
    auto* self = static_cast<Scanner*>(this); \
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset); \
    Token t{}; t.type_ = Type::TOK_FLOAT_LITERAL; t.loc_ = loc; \
    t.u_.f64 = strtod(yytext, nullptr); \
    self->setCurrentToken(t); \
    g_column += yyleng; g_offset += yyleng; \
    return static_cast<int>(Type::TOK_FLOAT_LITERAL); \
} while(0)

#define EMIT_STRING() do { \
    auto* self = static_cast<Scanner*>(this); \
    /* strip surrounding quotes; assume no newlines in rule */ \
    const char* payload = yytext + 1; size_t n = (size_t)yyleng >= 2 ? (size_t)yyleng - 2 : 0; \
    /* NOTE: implement unescape inside internString if you support escapes */ \
    lex::SymId sym = self->internString(payload, n); \
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset); \
    Token t{}; t.type_ = Type::TOK_STRING_LITERAL; t.loc_ = loc; \
    t.u_.sym = sym; \
    self->setCurrentToken(t); \
    g_column += yyleng; g_offset += yyleng; \
    return static_cast<int>(Type::TOK_STRING_LITERAL); \
} while(0)

#define EMIT_IDENT() do { \
    auto* self = static_cast<Scanner*>(this); \
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset); \
    lex::SymId sym = self->internIdent(yytext, (size_t)yyleng); \
    Token t{}; t.type_ = Type::TOK_IDENTIFIER; t.loc_ = loc; \
    t.u_.sym = sym; \
    self->setCurrentToken(t); \
    g_column += yyleng; g_offset += yyleng; \
    return static_cast<int>(Type::TOK_IDENTIFIER); \
} while(0)

%}

%option c++
%option yyclass="Scanner"
%option noyywrap
%option yylineno
%option nounput noinput


%%

"if"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_IF;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_IF);
             }
"while"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_WHILE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_WHILE);
             }
"do"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_DO;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_DO);
             }
"else"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_ELSE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_ELSE);
             }
"struct"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_STRUCT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_STRUCT);
             }
"trait"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_TRAIT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_TRAIT);
             }
"enum"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_ENUM;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_ENUM);
             }
"fn"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_FN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_FN);
             }
"type"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_TYPE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_TYPE);
             }
"let"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LET;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LET);
             }
"return"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_RETURN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_RETURN);
             }
"mut"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MUT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MUT);
             }
"int"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_INT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_INT);
             }
"bigint"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_BIGINT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_BIGINT);
             }
"magicint"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MAGICINT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MAGICINT);
             }
"double"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_DOUBLE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_DOUBLE);
             }
"bool"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_BOOL;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_BOOL);
             }
"void"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_VOID;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_VOID);
             }
"string"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_STRING;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_STRING);
             }
"break"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_BREAK;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_BREAK);
             }
"continue"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_CONTINUE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_CONTINUE);
             }
"import"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_IMPORT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_IMPORT);
             }
"export"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_EXPORT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_EXPORT);
             }
"package"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_PACKAGE;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_PACKAGE);
             }
"as"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_AS;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_AS);
             }

"("  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LPAR;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LPAR);
             }
")"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_RPAR;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_RPAR);
             }
"["  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LBRACK;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LBRACK);
             }
"]"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_RBRACK;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_RBRACK);
             }
"{"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LCBRA;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LCBRA);
             }
"}"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_RCBRA;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_RCBRA);
             }
","  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_COMMA;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_COMMA);
             }
";"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_SMCLN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_SMCLN);
             }
":"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_COLON;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_COLON);
             }
"."  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_DOT;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_DOT);
             }
"?"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_QUESTION;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_QUESTION);
             }
"->"  {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_ARROW;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_ARROW);
             }

"++" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_INC;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_INC);
                 }
"--" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_DEC;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_DEC);
                 }
"!" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_NEGATION;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_NEGATION);
                 }
"-" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_NEG;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_NEG);
                 }
"*" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_STAR;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_STAR);
                 }
"/" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_SLASH;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_SLASH);
                 }
"%" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MODULO;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MODULO);
                 }
"+" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_PLUS;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_PLUS);
                 }
"-" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MINUS;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MINUS);
                 }
"<" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LESS;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LESS);
                 }
"<=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_LEQ;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_LEQ);
                 }
">" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_GREATER;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_GREATER);
                 }
">=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_GEQ;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_GEQ);
                 }
"==" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_EQUAL;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_EQUAL);
                 }
"!=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_NEQUAL;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_NEQUAL);
                 }
"&&" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_BOOL_AND;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_BOOL_AND);
                 }
"||" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_BOOL_OR;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_BOOL_OR);
                 }
"=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_ASSIGN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_ASSIGN);
                 }
"+=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_PLUS_ASSIGN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_PLUS_ASSIGN);
                 }
"-=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MIN_ASSIGN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MIN_ASSIGN);
                 }
"*=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_MUL_ASSIGN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_MUL_ASSIGN);
                 }
"/=" {
                  auto* self = static_cast<Scanner*>(this);
                  Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
                  Token t{}; t.loc_ = loc;

                  t.type_ = Type::TOK_DIV_ASSIGN;
                  self->setCurrentToken(t);
                  g_column += yyleng; g_offset += yyleng;

                  return static_cast<int>(Type::TOK_DIV_ASSIGN);
                 }

\"([^\\\n"]|\\.)*\"                                       { EMIT_STRING(); }

[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?                         { EMIT_FLOAT(); }
\.[0-9]+([eE][+-]?[0-9]+)?                               { EMIT_FLOAT(); }
[0-9]+([eE][+-]?[0-9]+)                                  { EMIT_FLOAT(); }

[0-9]+                                                   { EMIT_INT(); }

[a-zA-Z_][a-zA-Z0-9_]*                                    { EMIT_IDENT(); }

[ \t]+            { g_offset += yyleng; g_column += yyleng; }

(\r\n|\r|\n)+     { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

"//".*            { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

"/*"([^*]|\*+[^*/])*"\*/"  { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

.                 { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] {  }
"//".* {  }
[/][*] {  } //TODO: fatal error

<<EOF>>           {
    auto* self = static_cast<Scanner*>(this);
    Loc loc = make_loc(yylineno, g_column, 0, g_offset);
    Token t{}; t.type_ = Type::TOK_END; t.loc_ = loc;
    self->setCurrentToken(t);
    return static_cast<int>(Type::TOK_END);
}

%%