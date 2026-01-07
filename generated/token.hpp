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
        TOK_TRAIT = 6, // trait
        TOK_IMPL = 7, // impl
        TOK_ENUM = 8, // enum
        TOK_FN = 9, // fn
        TOK_TYPE = 10, // type
        TOK_RETURN = 11, // return
        TOK_MUT = 12, // mut
        TOK_IMM = 13, // imm
        TOK_STATIC = 14, // static
        TOK_PUB = 15, // pub
        TOK_SELF = 16, // self
        TOK_FOR = 17, // for
        TOK_I8 = 18, // i8
        TOK_U8 = 19, // u8
        TOK_I16 = 20, // i16
        TOK_U16 = 21, // u16
        TOK_I32 = 22, // i32
        TOK_U32 = 23, // u32
        TOK_I64 = 24, // i64
        TOK_U64 = 25, // u64
        TOK_I128 = 26, // i128
        TOK_U128 = 27, // u128
        TOK_F32 = 28, // f32
        TOK_F64 = 29, // f64
        TOK_BOOL = 30, // bool
        TOK_CHAR = 31, // char
        TOK_VOID = 32, // void
        TOK_BREAK = 33, // break
        TOK_CONTINUE = 34, // continue
        TOK_IMPORT = 35, // import
        TOK_EXPORT = 36, // export
        TOK_PACKAGE = 37, // package
        TOK_AS = 38, // as
        TOK_LOAD = 39, // load

        TOK_AMP = 40, // &
        TOK_INC = 41, // ++
        TOK_DEC = 42, // --
        TOK_NEGATION = 43, // !
        TOK_STAR = 44, // *
        TOK_SLASH = 45, // /
        TOK_MODULO = 46, // %
        TOK_PLUS = 47, // +
        TOK_MINUS = 48, // -
        TOK_LESS = 49, // <
        TOK_LEQ = 50, // <=
        TOK_GREATER = 51, // >
        TOK_GEQ = 52, // >=
        TOK_EQUAL = 53, // ==
        TOK_NEQUAL = 54, // !=
        TOK_BOOL_AND = 55, // &&
        TOK_BOOL_OR = 56, // ||
        TOK_ASSIGN = 57, // =
        TOK_PLUS_ASSIGN = 58, // +=
        TOK_MIN_ASSIGN = 59, // -=
        TOK_MUL_ASSIGN = 60, // *=
        TOK_DIV_ASSIGN = 61, // /=

        TOK_LPAR = 62, // (
        TOK_RPAR = 63, // )
        TOK_LBRACK = 64, // [
        TOK_RBRACK = 65, // ]
        TOK_LCBRA = 66, // {
        TOK_RCBRA = 67, // }
        TOK_COMMA = 68, // ,
        TOK_SMCLN = 69, // ;
        TOK_COLON = 70, // :
        TOK_COLONCOLON = 71, // ::
        TOK_TURBOFISH_S = 72, // ::<
        TOK_DOT = 73, // .
        TOK_QUESTION = 74, // ?
        TOK_ARROW = 75, // ->

        TOK_IDENTIFIER = 76,

        TOK_INT_LITERAL = 77,
        TOK_FLOAT_LITERAL = 78,
        TOK_STRING_LITERAL = 79,
        TOK_BOOL_LITERAL = 80,
        TOK_CHAR_LITERAL = 81,

        TOK_UNDEF = 82
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