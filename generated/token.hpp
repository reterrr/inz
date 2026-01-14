// Auto-generated token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <ostream>

#include "types.hpp"

namespace lex {

    using SymId = std::uint32_t;

    enum Type : std::uint32_t {
        TOK_END = 0,


        TOK_IF = 1, // if
        TOK_WHILE = 2, // while
        TOK_DO = 3, // do
        TOK_ELSE = 4, // else
        TOK_STRUCT = 5, // struct
        TOK_FN = 6, // fn
        TOK_RETURN = 7, // return
        TOK_MUT = 8, // mut
        TOK_IMM = 9, // imm
        TOK_PUB = 10, // pub
        TOK_I8 = 11, // i8
        TOK_U8 = 12, // u8
        TOK_I16 = 13, // i16
        TOK_U16 = 14, // u16
        TOK_I32 = 15, // i32
        TOK_U32 = 16, // u32
        TOK_I64 = 17, // i64
        TOK_U64 = 18, // u64
        TOK_I128 = 19, // i128
        TOK_U128 = 20, // u128
        TOK_F32 = 21, // f32
        TOK_F64 = 22, // f64
        TOK_BOOL = 23, // bool
        TOK_CHAR = 24, // char
        TOK_VOID = 25, // void
        TOK_BREAK = 26, // break
        TOK_CONTINUE = 27, // continue
        TOK_IMPORT = 28, // import
        TOK_PACKAGE = 29, // package
        TOK_AS = 30, // as
        TOK_LOAD = 31, // load

        TOK_AMP = 32, // &
        TOK_INC = 33, // ++
        TOK_DEC = 34, // --
        TOK_NEGATION = 35, // !
        TOK_STAR = 36, // *
        TOK_SLASH = 37, // /
        TOK_MODULO = 38, // %
        TOK_PLUS = 39, // +
        TOK_MINUS = 40, // -
        TOK_LESS = 41, // <
        TOK_LEQ = 42, // <=
        TOK_GREATER = 43, // >
        TOK_GEQ = 44, // >=
        TOK_EQUAL = 45, // ==
        TOK_NEQUAL = 46, // !=
        TOK_BOOL_AND = 47, // &&
        TOK_BOOL_OR = 48, // ||
        TOK_ASSIGN = 49, // =

        TOK_LPAR = 50, // (
        TOK_RPAR = 51, // )
        TOK_LBRACK = 52, // [
        TOK_RBRACK = 53, // ]
        TOK_LCBRA = 54, // {
        TOK_RCBRA = 55, // }
        TOK_COMMA = 56, // ,
        TOK_SMCLN = 57, // ;
        TOK_COLON = 58, // :
        TOK_COLONCOLON = 59, // ::
        TOK_TURBOFISH_S = 60, // ::<
        TOK_DOT = 61, // .
        TOK_ARROW = 62, // ->

        TOK_IDENTIFIER = 63,

        TOK_INT_LITERAL = 64,
        TOK_FLOAT_LITERAL = 65,
        TOK_STRING_LITERAL = 66,
        TOK_BOOL_LITERAL = 67,
        TOK_CHAR_LITERAL = 68,

        TOK_UNDEF = 69
    };

    struct Pos final {
        std::uint32_t line   = 1;
        std::uint32_t column = 1;
        std::uint64_t offset = 0;
    };

    struct Loc final {
        Pos begin;
        Pos end;
    };

    inline Loc& operator+=(Loc& a, const Loc& b) { a.end = b.end; return a; }
    inline Loc  operator+(Loc a, const Loc& b)   { a += b; return a; }

    inline std::ostream& operator<<(std::ostream& os, const Pos& pos) {
        return os << "(line: " << pos.line << ", column: " << pos.column << ", offset: " << pos.offset << ")";
    }

    inline std::ostream& operator<<(std::ostream& os, const Loc& loc) {
        return os << "(begin: " << loc.begin << ", end: " << loc.end << ")";
    }

    struct Token final {
        Type type_;
        Loc  loc_;

        union {
            SymId    sym;      // IDENTIFIER, INT_LITERAL, FLOAT_LITERAL, STRING_LITERAL
            kl::rt::boolean     boolean;  // BOOL_LITERAL
            kl::rt::character ch;       // CHAR_LITERAL
        } u_{};
    };

} // namespace lex

#endif // TOKEN_HPP