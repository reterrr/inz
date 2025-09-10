// Auto-generated token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <cstdint>

namespace lex {
    enum Type {
        TOK_UNKNOWN = 0,
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
        TOK_INT = 13, // int
        TOK_BIGINT = 14, // bigint
        TOK_MAGICINT = 15, // magicint
        TOK_DOUBLE = 16, // double
        TOK_BOOL = 17, // bool
        TOK_VOID = 18, // void
        TOK_STRING = 19, // string
        TOK_BREAK = 20, // break
        TOK_CONTINUE = 21, // continue
        TOK_IMPORT = 22, // import
        TOK_EXPORT = 23, // export
        TOK_PACKAGE = 24, // package
        TOK_AS = 25, // as
        TOK_INC = 26, // ++
        TOK_DEC = 27, // --
        TOK_NEGATION = 28, // !
        TOK_NEG = 29, // -
        TOK_STAR = 30, // *
        TOK_SLASH = 31, // /
        TOK_MODULO = 32, // %
        TOK_PLUS = 33, // +
        TOK_MINUS = 34, // -
        TOK_LESS = 35, // <
        TOK_LEQ = 36, // <=
        TOK_GREATER = 37, // >
        TOK_GEQ = 38, // >=
        TOK_EQUAL = 39, // ==
        TOK_NEQUAL = 40, // !=
        TOK_BOOL_AND = 41, // &&
        TOK_BOOL_OR = 42, // ||
        TOK_ASSIGN = 43, // =
        TOK_PLUS_ASSIGN = 44, // +=
        TOK_MIN_ASSIGN = 45, // -=
        TOK_MUL_ASSIGN = 46, // *=
        TOK_DIV_ASSIGN = 47, // /=
        TOK_LPAR = 48, // (
        TOK_RPAR = 49, // )
        TOK_LBRACK = 50, // [
        TOK_RBRACK = 51, // ]
        TOK_LCBRA = 52, // {
        TOK_RCBRA = 53, // }
        TOK_COMMA = 54, // ,
        TOK_SMCLN = 55, // ;
        TOK_COLON = 56, // :
        TOK_DOT = 57, // .
        TOK_QUESTION = 58, // ?
        TOK_ARROW = 59, // ->
        TOK_IDENTIFIER = 60,
        TOK_INT_LITERAL = 61,
        TOK_FLOAT_LITERAL = 62,
        TOK_STRING_LITERAL = 63,
        TOK_END = 64
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