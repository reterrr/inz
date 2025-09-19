// Auto-generated token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <cstdint>

namespace lex {
    enum Type {
        TOK_END = 0,
        TOK_IF = 1, // if
        TOK_WHILE = 2, // while
        TOK_DO = 3, // do
        TOK_ELSE = 4, // else
        TOK_STRUCT = 5, // struct
        TOK_TRAIT = 6, // trait
        TOK_ENUM = 7, // enum
        TOK_FN = 8, // fn
        TOK_TYPE = 9, // type
        TOK_LET = 10, // let
        TOK_RETURN = 11, // return
        TOK_MUT = 12, // mut
        TOK_PUB = 13, // pub
        TOK_INT = 14, // int
        TOK_BIGINT = 15, // bigint
        TOK_MAGICINT = 16, // magicint
        TOK_DOUBLE = 17, // double
        TOK_BOOL = 18, // bool
        TOK_VOID = 19, // void
        TOK_STRING = 20, // string
        TOK_BREAK = 21, // break
        TOK_CONTINUE = 22, // continue
        TOK_IMPORT = 23, // import
        TOK_EXPORT = 24, // export
        TOK_PACKAGE = 25, // package
        TOK_AS = 26, // as
        TOK_INC = 27, // ++
        TOK_DEC = 28, // --
        TOK_NEGATION = 29, // !
        TOK_NEG = 30, // -
        TOK_STAR = 31, // *
        TOK_SLASH = 32, // /
        TOK_MODULO = 33, // %
        TOK_PLUS = 34, // +
        TOK_MINUS = 35, // -
        TOK_LESS = 36, // <
        TOK_LEQ = 37, // <=
        TOK_GREATER = 38, // >
        TOK_GEQ = 39, // >=
        TOK_EQUAL = 40, // ==
        TOK_NEQUAL = 41, // !=
        TOK_BOOL_AND = 42, // &&
        TOK_BOOL_OR = 43, // ||
        TOK_ASSIGN = 44, // =
        TOK_PLUS_ASSIGN = 45, // +=
        TOK_MIN_ASSIGN = 46, // -=
        TOK_MUL_ASSIGN = 47, // *=
        TOK_DIV_ASSIGN = 48, // /=
        TOK_LPAR = 49, // (
        TOK_RPAR = 50, // )
        TOK_LBRACK = 51, // [
        TOK_RBRACK = 52, // ]
        TOK_LCBRA = 53, // {
        TOK_RCBRA = 54, // }
        TOK_COMMA = 55, // ,
        TOK_SMCLN = 56, // ;
        TOK_COLON = 57, // :
        TOK_DOT = 58, // .
        TOK_QUESTION = 59, // ?
        TOK_ARROW = 60, // ->
        TOK_IDENTIFIER = 61,
        TOK_INT_LITERAL = 62,
        TOK_FLOAT_LITERAL = 63,
        TOK_STRING_LITERAL = 64,
        TOK_UNKNOWN = 65
    };

   struct Pos final {
       uint32_t line = 1;
       uint32_t column = 1;
       uint64_t offset = 0;
   };

   struct Loc final {
       Pos begin;
       Pos end;
   };

   inline Loc &operator+=(Loc &a, const Loc &b) {
       a.end = b.end;
       return a;
   }

   inline Loc operator+(Loc a, const Loc &b) {
       a += b;
       return a;
   }

   using SymId = uint32_t;

   struct Token final {
           Type type_;
           Loc loc_;

           union {
               int64_t i64;
               double f64;
               SymId sym;
           } u_{};
   };
}


#endif // TOKEN_HPP