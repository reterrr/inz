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
        TOK_IMM = 13, // imm
        TOK_STATIC = 14, // static
        TOK_PUB = 15, // pub
        TOK_INT = 16, // int
        TOK_BIGINT = 17, // bigint
        TOK_MAGICINT = 18, // magicint
        TOK_DOUBLE = 19, // double
        TOK_BOOL = 20, // bool
        TOK_VOID = 21, // void
        TOK_STRING = 22, // string
        TOK_I8 = 23, // type
        TOK_U8 = 24, // type
        TOK_I16 = 25, // type
        TOK_U16 = 26, // type
        TOK_I32 = 27, // type
        TOK_U32 = 28, // type
        TOK_I64 = 29, // type
        TOK_U64 = 30, // type
        TOK_I128 = 31, // type
        TOK_U128 = 32, // type
        TOK_F32 = 33, // type
        TOK_F64 = 34, // type
        TOK_Bool = 35, // type
        TOK_Char = 36, // type
        TOK_BREAK = 37, // break
        TOK_CONTINUE = 38, // continue
        TOK_IMPORT = 39, // import
        TOK_EXPORT = 40, // export
        TOK_PACKAGE = 41, // package
        TOK_AS = 42, // as
        TOK_AMP = 43, // &
        TOK_INC = 44, // ++
        TOK_DEC = 45, // --
        TOK_NEGATION = 46, // !
        TOK_NEG = 47, // -
        TOK_STAR = 48, // *
        TOK_SLASH = 49, // /
        TOK_MODULO = 50, // %
        TOK_PLUS = 51, // +
        TOK_MINUS = 52, // -
        TOK_LESS = 53, // <
        TOK_LEQ = 54, // <=
        TOK_GREATER = 55, // >
        TOK_GEQ = 56, // >=
        TOK_EQUAL = 57, // ==
        TOK_NEQUAL = 58, // !=
        TOK_BOOL_AND = 59, // &&
        TOK_BOOL_OR = 60, // ||
        TOK_ASSIGN = 61, // =
        TOK_PLUS_ASSIGN = 62, // +=
        TOK_MIN_ASSIGN = 63, // -=
        TOK_MUL_ASSIGN = 64, // *=
        TOK_DIV_ASSIGN = 65, // /=
        TOK_LPAR = 66, // (
        TOK_RPAR = 67, // )
        TOK_LBRACK = 68, // [
        TOK_RBRACK = 69, // ]
        TOK_LCBRA = 70, // {
        TOK_RCBRA = 71, // }
        TOK_COMMA = 72, // ,
        TOK_SMCLN = 73, // ;
        TOK_COLON = 74, // :
        TOK_DOT = 75, // .
        TOK_QUESTION = 76, // ?
        TOK_ARROW = 77, // ->
        TOK_IDENTIFIER = 78,
        TOK_INT_LITERAL = 79,
        TOK_FLOAT_LITERAL = 80,
        TOK_STRING_LITERAL = 81,
        TOK_UNKNOWN = 82
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