
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
    Loc L;
    L.line = line; L.end_line = line;
    L.column = start_col;
    L.end_column = start_col + (len ? (len - 1) : 0);
    L.begin_off = start_off;
    L.end_off = start_off + (len ? (len - 1) : 0);
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

%}

%option c++
%option yyclass="Scanner"
%option noyywrap
%option yylineno
%option nounput noinput

%%

/* ---------- Operators (maximal munch will pick longest) ---------- */
"+"    { EMIT_SIMPLE(Type::TOK_PLUS); }
"-"    { EMIT_SIMPLE(Type::TOK_MINUS); }
"/"    { EMIT_SIMPLE(Type::TOK_SLASH); }
"*"    { EMIT_SIMPLE(Type::TOK_STAR); }
"=="    { EMIT_SIMPLE(Type::TOK_EQUAL); }
"!="    { EMIT_SIMPLE(Type::TOK_NOT_EQUAL); }
"<"    { EMIT_SIMPLE(Type::TOK_LESS); }
">"    { EMIT_SIMPLE(Type::TOK_GREATER); }
"<="    { EMIT_SIMPLE(Type::TOK_LESS_EQUAL); }
">="    { EMIT_SIMPLE(Type::TOK_GREATER_EQUAL); }
"!"    { EMIT_SIMPLE(Type::TOK_NEGATION); }
"="    { EMIT_SIMPLE(Type::TOK_ASSIGN); }
"+="    { EMIT_SIMPLE(Type::TOK_PLUS_ASSIGN); }
"-="    { EMIT_SIMPLE(Type::TOK_MIN_ASSIGN); }
"/="    { EMIT_SIMPLE(Type::TOK_DIV_ASSIGN); }
"*="    { EMIT_SIMPLE(Type::TOK_MUL_ASSIGN); }

/* ---------- Delimiters / punct ---------- */
"("    { EMIT_SIMPLE(Type::TOK_LPAR); }
")"    { EMIT_SIMPLE(Type::TOK_RPAR); }
"{"    { EMIT_SIMPLE(Type::TOK_LCBRA); }
"}"    { EMIT_SIMPLE(Type::TOK_RCBRA); }
";"    { EMIT_SIMPLE(Type::TOK_SMCLN); }
"."    { EMIT_SIMPLE(Type::TOK_DOT); }

/* ---------- String literals (no newline) ---------- */
\"([^\\\n"]|\\.)*\"                                       { EMIT_STRING(); }

/* ---------- Numeric literals ---------- */
/* floats: 1.23, 1., .23, 1e10, 1.2e-3 */
[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?                         { EMIT_FLOAT(); }
\.[0-9]+([eE][+-]?[0-9]+)?                               { EMIT_FLOAT(); }
[0-9]+([eE][+-]?[0-9]+)                                  { EMIT_FLOAT(); }

/* ints: 0, 123 (keep after float rules) */
[0-9]+                                                   { EMIT_INT(); }

/* ---------- Identifiers & keywords ---------- */
[a-zA-Z_][a-zA-Z0-9_]*  {
    auto* self = static_cast<Scanner*>(this);
    Loc loc = make_loc(yylineno, g_column, yyleng, g_offset);
    Token t{}; t.loc_ = loc;

    /* generated keyword check (exact match) */
    /* fast path by length */
    switch (yyleng) {
      case 2:
        if (memcmp(yytext, "do", 2) == 0) {
            t.type_ = Type::TOK_DO;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_DO);
        }
        if (memcmp(yytext, "if", 2) == 0) {
            t.type_ = Type::TOK_IF;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_IF);
        }
        break;
      case 3:
        if (memcmp(yytext, "int", 3) == 0) {
            t.type_ = Type::TOK_INT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_INT);
        }
        if (memcmp(yytext, "mut", 3) == 0) {
            t.type_ = Type::TOK_MUT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_MUT);
        }
        break;
      case 4:
        if (memcmp(yytext, "bool", 4) == 0) {
            t.type_ = Type::TOK_BOOL;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_BOOL);
        }
        if (memcmp(yytext, "void", 4) == 0) {
            t.type_ = Type::TOK_VOID;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_VOID);
        }
        break;
      case 5:
        if (memcmp(yytext, "trait", 5) == 0) {
            t.type_ = Type::TOK_TRAIT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_TRAIT);
        }
        if (memcmp(yytext, "while", 5) == 0) {
            t.type_ = Type::TOK_WHILE;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_WHILE);
        }
        break;
      case 6:
        if (memcmp(yytext, "bigint", 6) == 0) {
            t.type_ = Type::TOK_BIGINT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_BIGINT);
        }
        if (memcmp(yytext, "double", 6) == 0) {
            t.type_ = Type::TOK_DOUBLE;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_DOUBLE);
        }
        if (memcmp(yytext, "struct", 6) == 0) {
            t.type_ = Type::TOK_STRUCT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_STRUCT);
        }
        if (memcmp(yytext, "string", 6) == 0) {
            t.type_ = Type::TOK_STRING;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_STRING);
        }
        break;
      case 8:
        if (memcmp(yytext, "magicint", 8) == 0) {
            t.type_ = Type::TOK_MAGICINT;
            self->setCurrentToken(t);
            g_column += yyleng; g_offset += yyleng;
            return static_cast<int>(Type::TOK_MAGICINT);
        }
        break;
    default: break;
    }

    /* not a keyword → identifier */
    t.type_ = Type::TOK_IDENTIFIER;
    t.u_.sym = self->internIdent(yytext, (size_t)yyleng);
    self->setCurrentToken(t);
    g_column += yyleng; g_offset += yyleng;
    return static_cast<int>(Type::TOK_IDENTIFIER);
}

/* ---------- Whitespace & comments ---------- */
/* spaces/tabs */
[ \t]+            { g_offset += yyleng; g_column += yyleng; }

/* newlines (count all) */
(\r\n|\r|\n)+     { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

/* // line comment */
"//".*            { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

/* /* block comment *\/  (may span lines) */
"/*"([^*]|\*+[^*/])*"\*/"  { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

/* ---------- Unknown single char: skip but advance (you may want to error) ---------- */
.                 { bump_pos_for_text(yytext, (size_t)yyleng, yylineno); }

/* ---------- EOF ---------- */
<<EOF>>           {
    auto* self = static_cast<Scanner*>(this);
    Loc loc = make_loc(yylineno, g_column, 0, g_offset);
    Token t{}; t.type_ = Type::TOK_END; t.loc_ = loc;
    self->setCurrentToken(t);
    return 0;
}

%%


%%PARSER_RULES%%