// Auto-generated token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <cstdint>
#include <ostream>

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
        TOK_STATIC = 13, // static
        TOK_PUB = 14, // pub
        TOK_INT = 15, // int
        TOK_BIGINT = 16, // bigint
        TOK_MAGICINT = 17, // magicint
        TOK_DOUBLE = 18, // double
        TOK_BOOL = 19, // bool
        TOK_VOID = 20, // void
        TOK_STRING = 21, // string
        TOK_BREAK = 22, // break
        TOK_CONTINUE = 23, // continue
        TOK_IMPORT = 24, // import
        TOK_EXPORT = 25, // export
        TOK_PACKAGE = 26, // package
        TOK_AS = 27, // as
        TOK_INC = 28, // ++
        TOK_DEC = 29, // --
        TOK_NEGATION = 30, // !
        TOK_NEG = 31, // -
        TOK_STAR = 32, // *
        TOK_SLASH = 33, // /
        TOK_MODULO = 34, // %
        TOK_PLUS = 35, // +
        TOK_MINUS = 36, // -
        TOK_LESS = 37, // <
        TOK_LEQ = 38, // <=
        TOK_GREATER = 39, // >
        TOK_GEQ = 40, // >=
        TOK_EQUAL = 41, // ==
        TOK_NEQUAL = 42, // !=
        TOK_BOOL_AND = 43, // &&
        TOK_BOOL_OR = 44, // ||
        TOK_ASSIGN = 45, // =
        TOK_PLUS_ASSIGN = 46, // +=
        TOK_MIN_ASSIGN = 47, // -=
        TOK_MUL_ASSIGN = 48, // *=
        TOK_DIV_ASSIGN = 49, // /=
        TOK_LPAR = 50, // (
        TOK_RPAR = 51, // )
        TOK_LBRACK = 52, // [
        TOK_RBRACK = 53, // ]
        TOK_LCBRA = 54, // {
        TOK_RCBRA = 55, // }
        TOK_COMMA = 56, // ,
        TOK_SMCLN = 57, // ;
        TOK_COLON = 58, // :
        TOK_DOT = 59, // .
        TOK_QUESTION = 60, // ?
        TOK_ARROW = 61, // ->
        TOK_IDENTIFIER = 62,
        TOK_INT_LITERAL = 63,
        TOK_FLOAT_LITERAL = 64,
        TOK_STRING_LITERAL = 65,
        TOK_UNKNOWN = 66
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

   inline std::ostream& operator<<(std::ostream &os, const Pos &pos) {
        return os << "\n(line: " << pos.line << ", column: " << pos.column << ", offset: " << pos.offset << ")\n";
   }

   inline std::ostream& operator<<(std::ostream &os, const Loc &loc) {
        return os << "\n(begin: " << loc.begin << ", end: " << loc.end << ")\n";
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