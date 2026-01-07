// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file parser/parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 23 "parser/parser_rules.y"

  #include "generated/token.hpp"
  #include "types.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"

  #include <string>
  #include <vector>
  #include <optional>

  class Scanner;

  using Str = lex::SymId;

#line 64 "parser/parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 8 "parser/parser_rules.y"
namespace yy {
#line 200 "parser/parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // TOK_IDENTIFIER
      // TOK_SELF
      // TOK_INT_LITERAL
      // TOK_FLOAT_LITERAL
      // TOK_STRING_LITERAL
      // ident_no_self
      // ident_any
      char dummy1[sizeof (Str)];

      // anon_block
      // fn_block
      // if_block
      // else_if_block
      // else_block
      // while_block
      // do_while_block
      char dummy2[sizeof (ast::BlockStatement*)];

      // break_stmt
      char dummy3[sizeof (ast::BreakStatement*)];

      // builtin_type_expr
      char dummy4[sizeof (ast::BuiltinTypeExpr*)];

      // continue_stmt
      char dummy5[sizeof (ast::ContinueStatement*)];

      // decl
      // trait_decl
      // impl_decl
      char dummy6[sizeof (ast::Decl*)];

      // do_while_stmt
      char dummy7[sizeof (ast::DoWhileStatement*)];

      // elseif
      char dummy8[sizeof (ast::ElseIfStatement*)];

      // else_part
      char dummy9[sizeof (ast::ElseStatement*)];

      // expr
      // expr_opt
      // assign
      // cond
      // logic_or
      // logic_and
      // equality
      // relational
      // additive
      // multiplicative
      // unary
      // postfix
      // primary
      char dummy10[sizeof (ast::Expr*)];

      // expr_stmt
      char dummy11[sizeof (ast::ExprStatement*)];

      // field_decl
      char dummy12[sizeof (ast::FieldDecl*)];

      // field_init
      char dummy13[sizeof (ast::FieldInitExpr*)];

      // fn_decl
      char dummy14[sizeof (ast::FnDecl*)];

      // if_stmt
      char dummy15[sizeof (ast::IfStatement*)];

      // impl_fn_decl
      // impl_item
      char dummy16[sizeof (ast::ImplFnDecl*)];

      // import_decl
      char dummy17[sizeof (ast::ImportDecl*)];

      // load_fn_decl
      char dummy18[sizeof (ast::LoadFnDecl*)];

      // ref_mutability
      char dummy19[sizeof (ast::Mutability)];

      // param
      // self_param
      char dummy20[sizeof (ast::ParamDecl*)];

      // path_expr
      // qpath_expr
      char dummy21[sizeof (ast::PathExpr*)];

      // path_type_expr
      char dummy22[sizeof (ast::PathTypeExpr*)];

      // ref_type_expr
      char dummy23[sizeof (ast::RefTypeExpr*)];

      // return_stmt
      char dummy24[sizeof (ast::ReturnStatement*)];

      // stmt
      // simple_stmt
      // compound_stmt
      char dummy25[sizeof (ast::Statement*)];

      // struct_decl
      // struct_decl_def
      // struct_decl_fwd
      char dummy26[sizeof (ast::StructDecl*)];

      // trait_fn_decl
      // trait_item
      char dummy27[sizeof (ast::TraitFnDecl*)];

      // ret_type_expr
      // type_expr
      // type_postfix
      // type_primary
      char dummy28[sizeof (ast::TypeExpr*)];

      // type_param
      char dummy29[sizeof (ast::TypeParamDecl*)];

      // var_stmt
      // var_stmt_default
      // var_stmt_imm
      // var_stmt_mut
      // var_stmt_static_default
      // var_stmt_static_imm
      // var_stmt_static_mut
      char dummy30[sizeof (ast::VarStmt*)];

      // while_stmt
      char dummy31[sizeof (ast::WhileStatement*)];

      // TOK_BOOL_LITERAL
      // pub_opt
      char dummy32[sizeof (kl::rt::boolean)];

      // TOK_CHAR_LITERAL
      char dummy33[sizeof (kl::rt::character)];

      // float_literal_type_opt
      char dummy34[sizeof (std::optional<kl::rt::FloatKind>)];

      // int_literal_type_opt
      char dummy35[sizeof (std::optional<kl::rt::IntKind>)];

      // path
      // qpath
      char dummy36[sizeof (std::vector<Str>)];

      // decl_list_opt
      // decl_list
      char dummy37[sizeof (std::vector<ast::Decl*>)];

      // elseif_list
      char dummy38[sizeof (std::vector<ast::ElseIfStatement*>)];

      // array_elems_opt
      // array_elems
      // arg_list_opt
      // arg_list
      char dummy39[sizeof (std::vector<ast::Expr*>)];

      // field_decl_list_opt
      // field_decl_list
      char dummy40[sizeof (std::vector<ast::FieldDecl*>)];

      // field_inits_opt
      // field_inits
      char dummy41[sizeof (std::vector<ast::FieldInitExpr*>)];

      // impl_item_list_opt
      // impl_item_list
      char dummy42[sizeof (std::vector<ast::ImplFnDecl*>)];

      // import_list_opt
      // import_list
      char dummy43[sizeof (std::vector<ast::ImportDecl*>)];

      // param_list_opt
      // param_list
      char dummy44[sizeof (std::vector<ast::ParamDecl*>)];

      // stmt_list_opt
      // stmt_list
      char dummy45[sizeof (std::vector<ast::Statement*>)];

      // trait_item_list_opt
      // trait_item_list
      char dummy46[sizeof (std::vector<ast::TraitFnDecl*>)];

      // type_args
      // type_arg_list
      char dummy47[sizeof (std::vector<ast::TypeExpr*>)];

      // type_params_opt
      // type_param_list
      char dummy48[sizeof (std::vector<ast::TypeParamDecl*>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef lex::Loc location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TOK_IF = 258,                  // TOK_IF
    TOK_WHILE = 259,               // TOK_WHILE
    TOK_DO = 260,                  // TOK_DO
    TOK_ELSE = 261,                // TOK_ELSE
    TOK_STRUCT = 262,              // TOK_STRUCT
    TOK_ENUM = 263,                // TOK_ENUM
    TOK_TRAIT = 264,               // TOK_TRAIT
    TOK_FN = 265,                  // TOK_FN
    TOK_TYPE = 266,                // TOK_TYPE
    TOK_RETURN = 267,              // TOK_RETURN
    TOK_IMPL = 268,                // TOK_IMPL
    TOK_FOR = 269,                 // TOK_FOR
    TOK_MUT = 270,                 // TOK_MUT
    TOK_IMM = 271,                 // TOK_IMM
    TOK_STATIC = 272,              // TOK_STATIC
    TOK_PUB = 273,                 // TOK_PUB
    TOK_BREAK = 274,               // TOK_BREAK
    TOK_CONTINUE = 275,            // TOK_CONTINUE
    TOK_IMPORT = 276,              // TOK_IMPORT
    TOK_EXPORT = 277,              // TOK_EXPORT
    TOK_PACKAGE = 278,             // TOK_PACKAGE
    TOK_AS = 279,                  // TOK_AS
    TOK_LOAD = 280,                // TOK_LOAD
    TOK_I8 = 281,                  // TOK_I8
    TOK_U8 = 282,                  // TOK_U8
    TOK_I16 = 283,                 // TOK_I16
    TOK_U16 = 284,                 // TOK_U16
    TOK_I32 = 285,                 // TOK_I32
    TOK_U32 = 286,                 // TOK_U32
    TOK_I64 = 287,                 // TOK_I64
    TOK_U64 = 288,                 // TOK_U64
    TOK_I128 = 289,                // TOK_I128
    TOK_U128 = 290,                // TOK_U128
    TOK_F32 = 291,                 // TOK_F32
    TOK_F64 = 292,                 // TOK_F64
    TOK_BOOL = 293,                // TOK_BOOL
    TOK_CHAR = 294,                // TOK_CHAR
    TOK_VOID = 295,                // TOK_VOID
    TOK_IDENTIFIER = 296,          // TOK_IDENTIFIER
    TOK_SELF = 297,                // TOK_SELF
    TOK_INT_LITERAL = 298,         // TOK_INT_LITERAL
    TOK_FLOAT_LITERAL = 299,       // TOK_FLOAT_LITERAL
    TOK_STRING_LITERAL = 300,      // TOK_STRING_LITERAL
    TOK_BOOL_LITERAL = 301,        // TOK_BOOL_LITERAL
    TOK_CHAR_LITERAL = 302,        // TOK_CHAR_LITERAL
    TOK_LPAR = 303,                // TOK_LPAR
    TOK_RPAR = 304,                // TOK_RPAR
    TOK_LBRACK = 305,              // TOK_LBRACK
    TOK_RBRACK = 306,              // TOK_RBRACK
    TOK_LCBRA = 307,               // TOK_LCBRA
    TOK_RCBRA = 308,               // TOK_RCBRA
    TOK_COMMA = 309,               // TOK_COMMA
    TOK_SMCLN = 310,               // TOK_SMCLN
    TOK_COLON = 311,               // TOK_COLON
    TOK_DOT = 312,                 // TOK_DOT
    TOK_QUESTION = 313,            // TOK_QUESTION
    TOK_ARROW = 314,               // TOK_ARROW
    TOK_COLONCOLON = 315,          // TOK_COLONCOLON
    TOK_TURBOFISH_S = 316,         // TOK_TURBOFISH_S
    TOK_NEGATION = 317,            // TOK_NEGATION
    TOK_INC = 318,                 // TOK_INC
    TOK_DEC = 319,                 // TOK_DEC
    TOK_AMP = 320,                 // TOK_AMP
    TOK_STAR = 321,                // TOK_STAR
    TOK_SLASH = 322,               // TOK_SLASH
    TOK_MODULO = 323,              // TOK_MODULO
    TOK_PLUS = 324,                // TOK_PLUS
    TOK_MINUS = 325,               // TOK_MINUS
    TOK_LESS = 326,                // TOK_LESS
    TOK_LEQ = 327,                 // TOK_LEQ
    TOK_GREATER = 328,             // TOK_GREATER
    TOK_GEQ = 329,                 // TOK_GEQ
    TOK_EQUAL = 330,               // TOK_EQUAL
    TOK_NEQUAL = 331,              // TOK_NEQUAL
    TOK_BOOL_AND = 332,            // TOK_BOOL_AND
    TOK_BOOL_OR = 333,             // TOK_BOOL_OR
    TOK_ASSIGN = 334,              // TOK_ASSIGN
    TOK_PLUS_ASSIGN = 335,         // TOK_PLUS_ASSIGN
    TOK_MIN_ASSIGN = 336,          // TOK_MIN_ASSIGN
    TOK_MUL_ASSIGN = 337,          // TOK_MUL_ASSIGN
    TOK_DIV_ASSIGN = 338,          // TOK_DIV_ASSIGN
    TERNARY = 339,                 // TERNARY
    UMINUS = 340,                  // UMINUS
    UPRE = 341,                    // UPRE
    LOWER_THAN_ASSIGN = 342        // LOWER_THAN_ASSIGN
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 88, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TOK_IF = 3,                            // TOK_IF
        S_TOK_WHILE = 4,                         // TOK_WHILE
        S_TOK_DO = 5,                            // TOK_DO
        S_TOK_ELSE = 6,                          // TOK_ELSE
        S_TOK_STRUCT = 7,                        // TOK_STRUCT
        S_TOK_ENUM = 8,                          // TOK_ENUM
        S_TOK_TRAIT = 9,                         // TOK_TRAIT
        S_TOK_FN = 10,                           // TOK_FN
        S_TOK_TYPE = 11,                         // TOK_TYPE
        S_TOK_RETURN = 12,                       // TOK_RETURN
        S_TOK_IMPL = 13,                         // TOK_IMPL
        S_TOK_FOR = 14,                          // TOK_FOR
        S_TOK_MUT = 15,                          // TOK_MUT
        S_TOK_IMM = 16,                          // TOK_IMM
        S_TOK_STATIC = 17,                       // TOK_STATIC
        S_TOK_PUB = 18,                          // TOK_PUB
        S_TOK_BREAK = 19,                        // TOK_BREAK
        S_TOK_CONTINUE = 20,                     // TOK_CONTINUE
        S_TOK_IMPORT = 21,                       // TOK_IMPORT
        S_TOK_EXPORT = 22,                       // TOK_EXPORT
        S_TOK_PACKAGE = 23,                      // TOK_PACKAGE
        S_TOK_AS = 24,                           // TOK_AS
        S_TOK_LOAD = 25,                         // TOK_LOAD
        S_TOK_I8 = 26,                           // TOK_I8
        S_TOK_U8 = 27,                           // TOK_U8
        S_TOK_I16 = 28,                          // TOK_I16
        S_TOK_U16 = 29,                          // TOK_U16
        S_TOK_I32 = 30,                          // TOK_I32
        S_TOK_U32 = 31,                          // TOK_U32
        S_TOK_I64 = 32,                          // TOK_I64
        S_TOK_U64 = 33,                          // TOK_U64
        S_TOK_I128 = 34,                         // TOK_I128
        S_TOK_U128 = 35,                         // TOK_U128
        S_TOK_F32 = 36,                          // TOK_F32
        S_TOK_F64 = 37,                          // TOK_F64
        S_TOK_BOOL = 38,                         // TOK_BOOL
        S_TOK_CHAR = 39,                         // TOK_CHAR
        S_TOK_VOID = 40,                         // TOK_VOID
        S_TOK_IDENTIFIER = 41,                   // TOK_IDENTIFIER
        S_TOK_SELF = 42,                         // TOK_SELF
        S_TOK_INT_LITERAL = 43,                  // TOK_INT_LITERAL
        S_TOK_FLOAT_LITERAL = 44,                // TOK_FLOAT_LITERAL
        S_TOK_STRING_LITERAL = 45,               // TOK_STRING_LITERAL
        S_TOK_BOOL_LITERAL = 46,                 // TOK_BOOL_LITERAL
        S_TOK_CHAR_LITERAL = 47,                 // TOK_CHAR_LITERAL
        S_TOK_LPAR = 48,                         // TOK_LPAR
        S_TOK_RPAR = 49,                         // TOK_RPAR
        S_TOK_LBRACK = 50,                       // TOK_LBRACK
        S_TOK_RBRACK = 51,                       // TOK_RBRACK
        S_TOK_LCBRA = 52,                        // TOK_LCBRA
        S_TOK_RCBRA = 53,                        // TOK_RCBRA
        S_TOK_COMMA = 54,                        // TOK_COMMA
        S_TOK_SMCLN = 55,                        // TOK_SMCLN
        S_TOK_COLON = 56,                        // TOK_COLON
        S_TOK_DOT = 57,                          // TOK_DOT
        S_TOK_QUESTION = 58,                     // TOK_QUESTION
        S_TOK_ARROW = 59,                        // TOK_ARROW
        S_TOK_COLONCOLON = 60,                   // TOK_COLONCOLON
        S_TOK_TURBOFISH_S = 61,                  // TOK_TURBOFISH_S
        S_TOK_NEGATION = 62,                     // TOK_NEGATION
        S_TOK_INC = 63,                          // TOK_INC
        S_TOK_DEC = 64,                          // TOK_DEC
        S_TOK_AMP = 65,                          // TOK_AMP
        S_TOK_STAR = 66,                         // TOK_STAR
        S_TOK_SLASH = 67,                        // TOK_SLASH
        S_TOK_MODULO = 68,                       // TOK_MODULO
        S_TOK_PLUS = 69,                         // TOK_PLUS
        S_TOK_MINUS = 70,                        // TOK_MINUS
        S_TOK_LESS = 71,                         // TOK_LESS
        S_TOK_LEQ = 72,                          // TOK_LEQ
        S_TOK_GREATER = 73,                      // TOK_GREATER
        S_TOK_GEQ = 74,                          // TOK_GEQ
        S_TOK_EQUAL = 75,                        // TOK_EQUAL
        S_TOK_NEQUAL = 76,                       // TOK_NEQUAL
        S_TOK_BOOL_AND = 77,                     // TOK_BOOL_AND
        S_TOK_BOOL_OR = 78,                      // TOK_BOOL_OR
        S_TOK_ASSIGN = 79,                       // TOK_ASSIGN
        S_TOK_PLUS_ASSIGN = 80,                  // TOK_PLUS_ASSIGN
        S_TOK_MIN_ASSIGN = 81,                   // TOK_MIN_ASSIGN
        S_TOK_MUL_ASSIGN = 82,                   // TOK_MUL_ASSIGN
        S_TOK_DIV_ASSIGN = 83,                   // TOK_DIV_ASSIGN
        S_TERNARY = 84,                          // TERNARY
        S_UMINUS = 85,                           // UMINUS
        S_UPRE = 86,                             // UPRE
        S_LOWER_THAN_ASSIGN = 87,                // LOWER_THAN_ASSIGN
        S_YYACCEPT = 88,                         // $accept
        S_translation_unit = 89,                 // translation_unit
        S_module = 90,                           // module
        S_import_list_opt = 91,                  // import_list_opt
        S_import_list = 92,                      // import_list
        S_import_decl = 93,                      // import_decl
        S_path = 94,                             // path
        S_path_expr = 95,                        // path_expr
        S_qpath = 96,                            // qpath
        S_qpath_expr = 97,                       // qpath_expr
        S_ident_no_self = 98,                    // ident_no_self
        S_ident_any = 99,                        // ident_any
        S_type_params_opt = 100,                 // type_params_opt
        S_type_param_list = 101,                 // type_param_list
        S_type_param = 102,                      // type_param
        S_type_args = 103,                       // type_args
        S_type_arg_list = 104,                   // type_arg_list
        S_pub_opt = 105,                         // pub_opt
        S_decl_list_opt = 106,                   // decl_list_opt
        S_decl_list = 107,                       // decl_list
        S_decl = 108,                            // decl
        S_fn_decl = 109,                         // fn_decl
        S_load_fn_decl = 110,                    // load_fn_decl
        S_impl_fn_decl = 111,                    // impl_fn_decl
        S_trait_fn_decl = 112,                   // trait_fn_decl
        S_struct_decl = 113,                     // struct_decl
        S_struct_decl_def = 114,                 // struct_decl_def
        S_array_elems_opt = 115,                 // array_elems_opt
        S_array_elems = 116,                     // array_elems
        S_struct_decl_fwd = 117,                 // struct_decl_fwd
        S_field_decl_list_opt = 118,             // field_decl_list_opt
        S_field_decl_list = 119,                 // field_decl_list
        S_field_decl = 120,                      // field_decl
        S_trait_decl = 121,                      // trait_decl
        S_trait_item_list_opt = 122,             // trait_item_list_opt
        S_trait_item_list = 123,                 // trait_item_list
        S_trait_item = 124,                      // trait_item
        S_impl_decl = 125,                       // impl_decl
        S_impl_item_list_opt = 126,              // impl_item_list_opt
        S_impl_item_list = 127,                  // impl_item_list
        S_impl_item = 128,                       // impl_item
        S_ret_type_expr = 129,                   // ret_type_expr
        S_param_list_opt = 130,                  // param_list_opt
        S_param_list = 131,                      // param_list
        S_param = 132,                           // param
        S_self_param = 133,                      // self_param
        S_type_expr = 134,                       // type_expr
        S_ref_type_expr = 135,                   // ref_type_expr
        S_ref_mutability = 136,                  // ref_mutability
        S_type_postfix = 137,                    // type_postfix
        S_type_primary = 138,                    // type_primary
        S_builtin_type_expr = 139,               // builtin_type_expr
        S_path_type_expr = 140,                  // path_type_expr
        S_anon_block = 141,                      // anon_block
        S_fn_block = 142,                        // fn_block
        S_if_block = 143,                        // if_block
        S_else_if_block = 144,                   // else_if_block
        S_else_block = 145,                      // else_block
        S_while_block = 146,                     // while_block
        S_do_while_block = 147,                  // do_while_block
        S_stmt_list_opt = 148,                   // stmt_list_opt
        S_stmt_list = 149,                       // stmt_list
        S_stmt = 150,                            // stmt
        S_simple_stmt = 151,                     // simple_stmt
        S_compound_stmt = 152,                   // compound_stmt
        S_return_stmt = 153,                     // return_stmt
        S_if_stmt = 154,                         // if_stmt
        S_elseif_list = 155,                     // elseif_list
        S_elseif = 156,                          // elseif
        S_else_part = 157,                       // else_part
        S_while_stmt = 158,                      // while_stmt
        S_do_while_stmt = 159,                   // do_while_stmt
        S_break_stmt = 160,                      // break_stmt
        S_continue_stmt = 161,                   // continue_stmt
        S_expr_stmt = 162,                       // expr_stmt
        S_var_stmt = 163,                        // var_stmt
        S_var_stmt_default = 164,                // var_stmt_default
        S_var_stmt_imm = 165,                    // var_stmt_imm
        S_var_stmt_mut = 166,                    // var_stmt_mut
        S_var_stmt_static_default = 167,         // var_stmt_static_default
        S_var_stmt_static_imm = 168,             // var_stmt_static_imm
        S_var_stmt_static_mut = 169,             // var_stmt_static_mut
        S_expr = 170,                            // expr
        S_expr_opt = 171,                        // expr_opt
        S_assign = 172,                          // assign
        S_cond = 173,                            // cond
        S_logic_or = 174,                        // logic_or
        S_logic_and = 175,                       // logic_and
        S_equality = 176,                        // equality
        S_relational = 177,                      // relational
        S_additive = 178,                        // additive
        S_multiplicative = 179,                  // multiplicative
        S_unary = 180,                           // unary
        S_postfix = 181,                         // postfix
        S_arg_list_opt = 182,                    // arg_list_opt
        S_arg_list = 183,                        // arg_list
        S_int_literal_type_opt = 184,            // int_literal_type_opt
        S_float_literal_type_opt = 185,          // float_literal_type_opt
        S_primary = 186,                         // primary
        S_field_inits_opt = 187,                 // field_inits_opt
        S_field_inits = 188,                     // field_inits
        S_field_init = 189                       // field_init
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.move< Str > (std::move (that.value));
        break;

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
        value.move< ast::BlockStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.move< ast::BreakStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.move< ast::ContinueStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
        value.move< ast::Decl* > (std::move (that.value));
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.move< ast::DoWhileStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_cond: // cond
      case symbol_kind::S_logic_or: // logic_or
      case symbol_kind::S_logic_and: // logic_and
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_relational: // relational
      case symbol_kind::S_additive: // additive
      case symbol_kind::S_multiplicative: // multiplicative
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< ast::Expr* > (std::move (that.value));
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.move< ast::ExprStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FnDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.move< ast::ImplFnDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.move< ast::LoadFnDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (std::move (that.value));
        break;

      case symbol_kind::S_param: // param
      case symbol_kind::S_self_param: // self_param
        value.move< ast::ParamDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
        value.move< ast::PathExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_return_stmt: // return_stmt
        value.move< ast::ReturnStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.move< ast::Statement* > (std::move (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
        value.move< ast::StructDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.move< ast::TraitFnDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.move< ast::TypeExpr* > (std::move (that.value));
        break;

      case symbol_kind::S_type_param: // type_param
        value.move< ast::TypeParamDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.move< ast::VarStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.move< kl::rt::boolean > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (std::move (that.value));
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.move< std::optional<kl::rt::FloatKind> > (std::move (that.value));
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.move< std::optional<kl::rt::IntKind> > (std::move (that.value));
        break;

      case symbol_kind::S_path: // path
      case symbol_kind::S_qpath: // qpath
        value.move< std::vector<Str> > (std::move (that.value));
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::Decl*> > (std::move (that.value));
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.move< std::vector<ast::ElseIfStatement*> > (std::move (that.value));
        break;

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::Expr*> > (std::move (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr*> > (std::move (that.value));
        break;

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.move< std::vector<ast::ImplFnDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (std::move (that.value));
        break;

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.move< std::vector<ast::TraitFnDecl*> > (std::move (that.value));
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.move< std::vector<ast::TypeExpr*> > (std::move (that.value));
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.move< std::vector<ast::TypeParamDecl*> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Str&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Str& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::BlockStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::BlockStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::BreakStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::BreakStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::BuiltinTypeExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::BuiltinTypeExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ContinueStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ContinueStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::Decl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::Decl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::DoWhileStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::DoWhileStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ElseIfStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ElseIfStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ElseStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ElseStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::Expr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::Expr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ExprStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ExprStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::FieldDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::FieldDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::FieldInitExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::FieldInitExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::FnDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::FnDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::IfStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::IfStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ImplFnDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ImplFnDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ImportDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ImportDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::LoadFnDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::LoadFnDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::Mutability&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::Mutability& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ParamDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ParamDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::PathExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::PathExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::PathTypeExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::PathTypeExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::RefTypeExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::RefTypeExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ReturnStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ReturnStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::Statement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::Statement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::StructDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::StructDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::TraitFnDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::TraitFnDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::TypeExpr*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::TypeExpr*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::TypeParamDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::TypeParamDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::VarStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::VarStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::WhileStatement*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::WhileStatement*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl::rt::boolean&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl::rt::boolean& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl::rt::character&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl::rt::character& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::optional<kl::rt::FloatKind>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::optional<kl::rt::FloatKind>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::optional<kl::rt::IntKind>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::optional<kl::rt::IntKind>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Str>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Str>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::Decl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::Decl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ElseIfStatement*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ElseIfStatement*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::Expr*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::Expr*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::FieldDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::FieldDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::FieldInitExpr*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::FieldInitExpr*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ImplFnDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ImplFnDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ImportDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ImportDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ParamDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ParamDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::Statement*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::Statement*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::TraitFnDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::TraitFnDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::TypeExpr*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::TypeExpr*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::TypeParamDecl*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::TypeParamDecl*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.template destroy< Str > ();
        break;

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
        value.template destroy< ast::BlockStatement* > ();
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.template destroy< ast::BreakStatement* > ();
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.template destroy< ast::BuiltinTypeExpr* > ();
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.template destroy< ast::ContinueStatement* > ();
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
        value.template destroy< ast::Decl* > ();
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.template destroy< ast::DoWhileStatement* > ();
        break;

      case symbol_kind::S_elseif: // elseif
        value.template destroy< ast::ElseIfStatement* > ();
        break;

      case symbol_kind::S_else_part: // else_part
        value.template destroy< ast::ElseStatement* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_cond: // cond
      case symbol_kind::S_logic_or: // logic_or
      case symbol_kind::S_logic_and: // logic_and
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_relational: // relational
      case symbol_kind::S_additive: // additive
      case symbol_kind::S_multiplicative: // multiplicative
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.template destroy< ast::Expr* > ();
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.template destroy< ast::ExprStatement* > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.template destroy< ast::FieldDecl* > ();
        break;

      case symbol_kind::S_field_init: // field_init
        value.template destroy< ast::FieldInitExpr* > ();
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.template destroy< ast::FnDecl* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.template destroy< ast::IfStatement* > ();
        break;

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.template destroy< ast::ImplFnDecl* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.template destroy< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.template destroy< ast::LoadFnDecl* > ();
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.template destroy< ast::Mutability > ();
        break;

      case symbol_kind::S_param: // param
      case symbol_kind::S_self_param: // self_param
        value.template destroy< ast::ParamDecl* > ();
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
        value.template destroy< ast::PathExpr* > ();
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.template destroy< ast::PathTypeExpr* > ();
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.template destroy< ast::RefTypeExpr* > ();
        break;

      case symbol_kind::S_return_stmt: // return_stmt
        value.template destroy< ast::ReturnStatement* > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.template destroy< ast::Statement* > ();
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
        value.template destroy< ast::StructDecl* > ();
        break;

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.template destroy< ast::TraitFnDecl* > ();
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.template destroy< ast::TypeExpr* > ();
        break;

      case symbol_kind::S_type_param: // type_param
        value.template destroy< ast::TypeParamDecl* > ();
        break;

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.template destroy< ast::VarStmt* > ();
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.template destroy< ast::WhileStatement* > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.template destroy< kl::rt::boolean > ();
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.template destroy< kl::rt::character > ();
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.template destroy< std::optional<kl::rt::FloatKind> > ();
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.template destroy< std::optional<kl::rt::IntKind> > ();
        break;

      case symbol_kind::S_path: // path
      case symbol_kind::S_qpath: // qpath
        value.template destroy< std::vector<Str> > ();
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
      case symbol_kind::S_decl_list: // decl_list
        value.template destroy< std::vector<ast::Decl*> > ();
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.template destroy< std::vector<ast::ElseIfStatement*> > ();
        break;

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.template destroy< std::vector<ast::Expr*> > ();
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.template destroy< std::vector<ast::FieldDecl*> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.template destroy< std::vector<ast::FieldInitExpr*> > ();
        break;

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.template destroy< std::vector<ast::ImplFnDecl*> > ();
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.template destroy< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.template destroy< std::vector<ast::ParamDecl*> > ();
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.template destroy< std::vector<ast::Statement*> > ();
        break;

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.template destroy< std::vector<ast::TraitFnDecl*> > ();
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.template destroy< std::vector<ast::TypeExpr*> > ();
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.template destroy< std::vector<ast::TypeParamDecl*> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Str v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Str& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kl::rt::boolean v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl::rt::boolean& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kl::rt::character v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl::rt::character& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    parser (Scanner& scanner_yyarg, ast::Ast& ast_yyarg, Translation& unit_yyarg, std::string_view filePath_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IF (location_type l)
      {
        return symbol_type (token::TOK_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IF (const location_type& l)
      {
        return symbol_type (token::TOK_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_WHILE (location_type l)
      {
        return symbol_type (token::TOK_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_WHILE (const location_type& l)
      {
        return symbol_type (token::TOK_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DO (location_type l)
      {
        return symbol_type (token::TOK_DO, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DO (const location_type& l)
      {
        return symbol_type (token::TOK_DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_ELSE (location_type l)
      {
        return symbol_type (token::TOK_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_ELSE (const location_type& l)
      {
        return symbol_type (token::TOK_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_STRUCT (location_type l)
      {
        return symbol_type (token::TOK_STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STRUCT (const location_type& l)
      {
        return symbol_type (token::TOK_STRUCT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_ENUM (location_type l)
      {
        return symbol_type (token::TOK_ENUM, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_ENUM (const location_type& l)
      {
        return symbol_type (token::TOK_ENUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_TRAIT (location_type l)
      {
        return symbol_type (token::TOK_TRAIT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TRAIT (const location_type& l)
      {
        return symbol_type (token::TOK_TRAIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_FN (location_type l)
      {
        return symbol_type (token::TOK_FN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_FN (const location_type& l)
      {
        return symbol_type (token::TOK_FN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_TYPE (location_type l)
      {
        return symbol_type (token::TOK_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TYPE (const location_type& l)
      {
        return symbol_type (token::TOK_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_RETURN (location_type l)
      {
        return symbol_type (token::TOK_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_RETURN (const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IMPL (location_type l)
      {
        return symbol_type (token::TOK_IMPL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IMPL (const location_type& l)
      {
        return symbol_type (token::TOK_IMPL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_FOR (location_type l)
      {
        return symbol_type (token::TOK_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_FOR (const location_type& l)
      {
        return symbol_type (token::TOK_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MUT (location_type l)
      {
        return symbol_type (token::TOK_MUT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MUT (const location_type& l)
      {
        return symbol_type (token::TOK_MUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IMM (location_type l)
      {
        return symbol_type (token::TOK_IMM, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IMM (const location_type& l)
      {
        return symbol_type (token::TOK_IMM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_STATIC (location_type l)
      {
        return symbol_type (token::TOK_STATIC, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STATIC (const location_type& l)
      {
        return symbol_type (token::TOK_STATIC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_PUB (location_type l)
      {
        return symbol_type (token::TOK_PUB, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_PUB (const location_type& l)
      {
        return symbol_type (token::TOK_PUB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BREAK (location_type l)
      {
        return symbol_type (token::TOK_BREAK, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BREAK (const location_type& l)
      {
        return symbol_type (token::TOK_BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_CONTINUE (location_type l)
      {
        return symbol_type (token::TOK_CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_CONTINUE (const location_type& l)
      {
        return symbol_type (token::TOK_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IMPORT (location_type l)
      {
        return symbol_type (token::TOK_IMPORT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IMPORT (const location_type& l)
      {
        return symbol_type (token::TOK_IMPORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_EXPORT (location_type l)
      {
        return symbol_type (token::TOK_EXPORT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_EXPORT (const location_type& l)
      {
        return symbol_type (token::TOK_EXPORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_PACKAGE (location_type l)
      {
        return symbol_type (token::TOK_PACKAGE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_PACKAGE (const location_type& l)
      {
        return symbol_type (token::TOK_PACKAGE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_AS (location_type l)
      {
        return symbol_type (token::TOK_AS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_AS (const location_type& l)
      {
        return symbol_type (token::TOK_AS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LOAD (location_type l)
      {
        return symbol_type (token::TOK_LOAD, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LOAD (const location_type& l)
      {
        return symbol_type (token::TOK_LOAD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_I8 (location_type l)
      {
        return symbol_type (token::TOK_I8, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_I8 (const location_type& l)
      {
        return symbol_type (token::TOK_I8, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_U8 (location_type l)
      {
        return symbol_type (token::TOK_U8, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_U8 (const location_type& l)
      {
        return symbol_type (token::TOK_U8, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_I16 (location_type l)
      {
        return symbol_type (token::TOK_I16, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_I16 (const location_type& l)
      {
        return symbol_type (token::TOK_I16, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_U16 (location_type l)
      {
        return symbol_type (token::TOK_U16, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_U16 (const location_type& l)
      {
        return symbol_type (token::TOK_U16, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_I32 (location_type l)
      {
        return symbol_type (token::TOK_I32, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_I32 (const location_type& l)
      {
        return symbol_type (token::TOK_I32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_U32 (location_type l)
      {
        return symbol_type (token::TOK_U32, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_U32 (const location_type& l)
      {
        return symbol_type (token::TOK_U32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_I64 (location_type l)
      {
        return symbol_type (token::TOK_I64, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_I64 (const location_type& l)
      {
        return symbol_type (token::TOK_I64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_U64 (location_type l)
      {
        return symbol_type (token::TOK_U64, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_U64 (const location_type& l)
      {
        return symbol_type (token::TOK_U64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_I128 (location_type l)
      {
        return symbol_type (token::TOK_I128, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_I128 (const location_type& l)
      {
        return symbol_type (token::TOK_I128, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_U128 (location_type l)
      {
        return symbol_type (token::TOK_U128, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_U128 (const location_type& l)
      {
        return symbol_type (token::TOK_U128, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_F32 (location_type l)
      {
        return symbol_type (token::TOK_F32, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_F32 (const location_type& l)
      {
        return symbol_type (token::TOK_F32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_F64 (location_type l)
      {
        return symbol_type (token::TOK_F64, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_F64 (const location_type& l)
      {
        return symbol_type (token::TOK_F64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BOOL (location_type l)
      {
        return symbol_type (token::TOK_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BOOL (const location_type& l)
      {
        return symbol_type (token::TOK_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_CHAR (location_type l)
      {
        return symbol_type (token::TOK_CHAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_CHAR (const location_type& l)
      {
        return symbol_type (token::TOK_CHAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_VOID (location_type l)
      {
        return symbol_type (token::TOK_VOID, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_VOID (const location_type& l)
      {
        return symbol_type (token::TOK_VOID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_IDENTIFIER (Str v, location_type l)
      {
        return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_IDENTIFIER (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_SELF (Str v, location_type l)
      {
        return symbol_type (token::TOK_SELF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_SELF (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_SELF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_INT_LITERAL (Str v, location_type l)
      {
        return symbol_type (token::TOK_INT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_INT_LITERAL (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_INT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_FLOAT_LITERAL (Str v, location_type l)
      {
        return symbol_type (token::TOK_FLOAT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_FLOAT_LITERAL (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_FLOAT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_STRING_LITERAL (Str v, location_type l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STRING_LITERAL (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BOOL_LITERAL (kl::rt::boolean v, location_type l)
      {
        return symbol_type (token::TOK_BOOL_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BOOL_LITERAL (const kl::rt::boolean& v, const location_type& l)
      {
        return symbol_type (token::TOK_BOOL_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_CHAR_LITERAL (kl::rt::character v, location_type l)
      {
        return symbol_type (token::TOK_CHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_CHAR_LITERAL (const kl::rt::character& v, const location_type& l)
      {
        return symbol_type (token::TOK_CHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LPAR (location_type l)
      {
        return symbol_type (token::TOK_LPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LPAR (const location_type& l)
      {
        return symbol_type (token::TOK_LPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_RPAR (location_type l)
      {
        return symbol_type (token::TOK_RPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_RPAR (const location_type& l)
      {
        return symbol_type (token::TOK_RPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LBRACK (location_type l)
      {
        return symbol_type (token::TOK_LBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_LBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_RBRACK (location_type l)
      {
        return symbol_type (token::TOK_RBRACK, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_RBRACK (const location_type& l)
      {
        return symbol_type (token::TOK_RBRACK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LCBRA (location_type l)
      {
        return symbol_type (token::TOK_LCBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LCBRA (const location_type& l)
      {
        return symbol_type (token::TOK_LCBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_RCBRA (location_type l)
      {
        return symbol_type (token::TOK_RCBRA, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_RCBRA (const location_type& l)
      {
        return symbol_type (token::TOK_RCBRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_COMMA (location_type l)
      {
        return symbol_type (token::TOK_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_COMMA (const location_type& l)
      {
        return symbol_type (token::TOK_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_SMCLN (location_type l)
      {
        return symbol_type (token::TOK_SMCLN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_SMCLN (const location_type& l)
      {
        return symbol_type (token::TOK_SMCLN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_COLON (location_type l)
      {
        return symbol_type (token::TOK_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_COLON (const location_type& l)
      {
        return symbol_type (token::TOK_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DOT (location_type l)
      {
        return symbol_type (token::TOK_DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DOT (const location_type& l)
      {
        return symbol_type (token::TOK_DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_QUESTION (location_type l)
      {
        return symbol_type (token::TOK_QUESTION, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_QUESTION (const location_type& l)
      {
        return symbol_type (token::TOK_QUESTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_ARROW (location_type l)
      {
        return symbol_type (token::TOK_ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_ARROW (const location_type& l)
      {
        return symbol_type (token::TOK_ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_COLONCOLON (location_type l)
      {
        return symbol_type (token::TOK_COLONCOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_COLONCOLON (const location_type& l)
      {
        return symbol_type (token::TOK_COLONCOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_TURBOFISH_S (location_type l)
      {
        return symbol_type (token::TOK_TURBOFISH_S, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TURBOFISH_S (const location_type& l)
      {
        return symbol_type (token::TOK_TURBOFISH_S, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_NEGATION (location_type l)
      {
        return symbol_type (token::TOK_NEGATION, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_NEGATION (const location_type& l)
      {
        return symbol_type (token::TOK_NEGATION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_INC (location_type l)
      {
        return symbol_type (token::TOK_INC, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_INC (const location_type& l)
      {
        return symbol_type (token::TOK_INC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DEC (location_type l)
      {
        return symbol_type (token::TOK_DEC, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DEC (const location_type& l)
      {
        return symbol_type (token::TOK_DEC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_AMP (location_type l)
      {
        return symbol_type (token::TOK_AMP, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_AMP (const location_type& l)
      {
        return symbol_type (token::TOK_AMP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_STAR (location_type l)
      {
        return symbol_type (token::TOK_STAR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STAR (const location_type& l)
      {
        return symbol_type (token::TOK_STAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_SLASH (location_type l)
      {
        return symbol_type (token::TOK_SLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_SLASH (const location_type& l)
      {
        return symbol_type (token::TOK_SLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MODULO (location_type l)
      {
        return symbol_type (token::TOK_MODULO, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MODULO (const location_type& l)
      {
        return symbol_type (token::TOK_MODULO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_PLUS (location_type l)
      {
        return symbol_type (token::TOK_PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_PLUS (const location_type& l)
      {
        return symbol_type (token::TOK_PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MINUS (location_type l)
      {
        return symbol_type (token::TOK_MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MINUS (const location_type& l)
      {
        return symbol_type (token::TOK_MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LESS (location_type l)
      {
        return symbol_type (token::TOK_LESS, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LESS (const location_type& l)
      {
        return symbol_type (token::TOK_LESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_LEQ (location_type l)
      {
        return symbol_type (token::TOK_LEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LEQ (const location_type& l)
      {
        return symbol_type (token::TOK_LEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_GREATER (location_type l)
      {
        return symbol_type (token::TOK_GREATER, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_GREATER (const location_type& l)
      {
        return symbol_type (token::TOK_GREATER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_GEQ (location_type l)
      {
        return symbol_type (token::TOK_GEQ, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_GEQ (const location_type& l)
      {
        return symbol_type (token::TOK_GEQ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_EQUAL (location_type l)
      {
        return symbol_type (token::TOK_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_EQUAL (const location_type& l)
      {
        return symbol_type (token::TOK_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_NEQUAL (location_type l)
      {
        return symbol_type (token::TOK_NEQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_NEQUAL (const location_type& l)
      {
        return symbol_type (token::TOK_NEQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BOOL_AND (location_type l)
      {
        return symbol_type (token::TOK_BOOL_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BOOL_AND (const location_type& l)
      {
        return symbol_type (token::TOK_BOOL_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BOOL_OR (location_type l)
      {
        return symbol_type (token::TOK_BOOL_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BOOL_OR (const location_type& l)
      {
        return symbol_type (token::TOK_BOOL_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_PLUS_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_PLUS_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_PLUS_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_PLUS_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MIN_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_MIN_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MIN_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_MIN_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MUL_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_MUL_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MUL_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_MUL_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DIV_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_DIV_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DIV_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_DIV_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TERNARY (location_type l)
      {
        return symbol_type (token::TERNARY, std::move (l));
      }
#else
      static
      symbol_type
      make_TERNARY (const location_type& l)
      {
        return symbol_type (token::TERNARY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UMINUS (location_type l)
      {
        return symbol_type (token::UMINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UMINUS (const location_type& l)
      {
        return symbol_type (token::UMINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UPRE (location_type l)
      {
        return symbol_type (token::UPRE, std::move (l));
      }
#else
      static
      symbol_type
      make_UPRE (const location_type& l)
      {
        return symbol_type (token::UPRE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOWER_THAN_ASSIGN (location_type l)
      {
        return symbol_type (token::LOWER_THAN_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_LOWER_THAN_ASSIGN (const location_type& l)
      {
        return symbol_type (token::LOWER_THAN_ASSIGN, l);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const unsigned char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 469,     ///< Last index in yytable_.
      yynnts_ = 102,  ///< Number of nonterminal symbols.
      yyfinal_ = 9 ///< Termination state number.
    };


    // User arguments.
    Scanner& scanner;
    ast::Ast& ast;
    Translation& unit;
    std::string_view filePath;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
    };
    // Last valid token kind.
    const int code_max = 342;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.copy< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
        value.copy< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.copy< ast::BreakStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.copy< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.copy< ast::ContinueStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
        value.copy< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.copy< ast::DoWhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.copy< ast::ElseIfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.copy< ast::ElseStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_cond: // cond
      case symbol_kind::S_logic_or: // logic_or
      case symbol_kind::S_logic_and: // logic_and
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_relational: // relational
      case symbol_kind::S_additive: // additive
      case symbol_kind::S_multiplicative: // multiplicative
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.copy< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.copy< ast::ExprStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.copy< ast::FnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.copy< ast::ImplFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.copy< ast::LoadFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.copy< ast::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
      case symbol_kind::S_self_param: // self_param
        value.copy< ast::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
        value.copy< ast::PathExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.copy< ast::PathTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.copy< ast::RefTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return_stmt: // return_stmt
        value.copy< ast::ReturnStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.copy< ast::Statement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
        value.copy< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.copy< ast::TraitFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.copy< ast::TypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_param: // type_param
        value.copy< ast::TypeParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.copy< ast::VarStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.copy< ast::WhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.copy< kl::rt::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.copy< kl::rt::character > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.copy< std::optional<kl::rt::FloatKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.copy< std::optional<kl::rt::IntKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path: // path
      case symbol_kind::S_qpath: // qpath
        value.copy< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
      case symbol_kind::S_decl_list: // decl_list
        value.copy< std::vector<ast::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.copy< std::vector<ast::ElseIfStatement*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.copy< std::vector<ast::FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.copy< std::vector<ast::ImplFnDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<ast::Statement*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.copy< std::vector<ast::TraitFnDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.copy< std::vector<ast::TypeExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.copy< std::vector<ast::TypeParamDecl*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.move< Str > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
        value.move< ast::BlockStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.move< ast::BreakStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.move< ast::ContinueStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
        value.move< ast::Decl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.move< ast::DoWhileStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_cond: // cond
      case symbol_kind::S_logic_or: // logic_or
      case symbol_kind::S_logic_and: // logic_and
      case symbol_kind::S_equality: // equality
      case symbol_kind::S_relational: // relational
      case symbol_kind::S_additive: // additive
      case symbol_kind::S_multiplicative: // multiplicative
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< ast::Expr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.move< ast::ExprStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FnDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.move< ast::ImplFnDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.move< ast::LoadFnDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param: // param
      case symbol_kind::S_self_param: // self_param
        value.move< ast::ParamDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
        value.move< ast::PathExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_return_stmt: // return_stmt
        value.move< ast::ReturnStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.move< ast::Statement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
        value.move< ast::StructDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.move< ast::TraitFnDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.move< ast::TypeExpr* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_param: // type_param
        value.move< ast::TypeParamDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.move< ast::VarStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.move< kl::rt::boolean > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.move< std::optional<kl::rt::FloatKind> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.move< std::optional<kl::rt::IntKind> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_path: // path
      case symbol_kind::S_qpath: // qpath
        value.move< std::vector<Str> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::Decl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.move< std::vector<ast::ElseIfStatement*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::Expr*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.move< std::vector<ast::ImplFnDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.move< std::vector<ast::TraitFnDecl*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.move< std::vector<ast::TypeExpr*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.move< std::vector<ast::TypeParamDecl*> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 8 "parser/parser_rules.y"
} // yy
#line 4709 "parser/parser.hpp"


// "%code provides" blocks.
#line 39 "parser/parser_rules.y"

  namespace yy {
    parser::symbol_type yylex(Scanner& scanner);
  }

#line 4719 "parser/parser.hpp"


#endif // !YY_YY_PARSER_PARSER_HPP_INCLUDED
