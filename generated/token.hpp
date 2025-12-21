// Auto-generated token.hpp
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <ostream>

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
        TOK_ENUM = 7, // enum
        TOK_FN = 8, // fn
        TOK_TYPE = 9, // type
        TOK_RETURN = 10, // return
        TOK_MUT = 11, // mut
        TOK_IMM = 12, // imm
        TOK_STATIC = 13, // static
        TOK_PUB = 14, // pub
        TOK_I8 = 15, // i8
        TOK_U8 = 16, // u8
        TOK_I16 = 17, // i16
        TOK_U16 = 18, // u16
        TOK_I32 = 19, // i32
        TOK_U32 = 20, // u32
        TOK_I64 = 21, // i64
        TOK_U64 = 22, // u64
        TOK_I128 = 23, // i128
        TOK_U128 = 24, // u128
        TOK_F32 = 25, // f32
        TOK_F64 = 26, // f64
        TOK_BOOL = 27, // bool
        TOK_CHAR = 28, // char
        TOK_BREAK = 29, // break
        TOK_CONTINUE = 30, // continue
        TOK_IMPORT = 31, // import
        TOK_EXPORT = 32, // export
        TOK_PACKAGE = 33, // package
        TOK_AS = 34, // as

        TOK_AMP = 35, // &
        TOK_INC = 36, // ++
        TOK_DEC = 37, // --
        TOK_NEGATION = 38, // !
        TOK_STAR = 39, // *
        TOK_SLASH = 40, // /
        TOK_MODULO = 41, // %
        TOK_PLUS = 42, // +
        TOK_MINUS = 43, // -
        TOK_LESS = 44, // <
        TOK_LEQ = 45, // <=
        TOK_GREATER = 46, // >
        TOK_GEQ = 47, // >=
        TOK_EQUAL = 48, // ==
        TOK_NEQUAL = 49, // !=
        TOK_BOOL_AND = 50, // &&
        TOK_BOOL_OR = 51, // ||
        TOK_ASSIGN = 52, // =
        TOK_PLUS_ASSIGN = 53, // +=
        TOK_MIN_ASSIGN = 54, // -=
        TOK_MUL_ASSIGN = 55, // *=
        TOK_DIV_ASSIGN = 56, // /=

        TOK_LPAR = 57, // (
        TOK_RPAR = 58, // )
        TOK_LBRACK = 59, // [
        TOK_RBRACK = 60, // ]
        TOK_LCBRA = 61, // {
        TOK_RCBRA = 62, // }
        TOK_COMMA = 63, // ,
        TOK_SMCLN = 64, // ;
        TOK_COLON = 65, // :
        TOK_COLONCOLON = 66, // ::
        TOK_TURBOFISH_S = 67, // ::<
        TOK_DOT = 68, // .
        TOK_QUESTION = 69, // ?
        TOK_ARROW = 70, // ->

        TOK_IDENTIFIER = 71,

        TOK_INT_LITERAL = 72,
        TOK_FLOAT_LITERAL = 73,
        TOK_STRING_LITERAL = 74,
        TOK_BOOL_LITERAL = 75,
        TOK_CHAR_LITERAL = 76,

        TOK_UNDEF = 77
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
            bool     boolean;  // BOOL_LITERAL
            char32_t ch;       // CHAR_LITERAL
        } u_{};
    };

} // namespace lex

#endif // TOKEN_HPP