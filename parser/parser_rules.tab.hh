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
 ** \file parser_rules.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_RULES_TAB_HH_INCLUDED
# define YY_YY_PARSER_RULES_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 15 "parser_rules.y"

  #include "../generated/token.hpp"   // lex::Loc, lex::SymId
  #include <string>
  #include <vector>
  #include <memory>

  using namespace lex;

  // If you use these in %token/%type, they must be visible here:
  using Str = lex::SymId;

  class Scanner;
  namespace yy { class parser; }   // forward-declare the parser class
  yy::parser::symbol_type yylex(Scanner& scanner);  // ⬅️ declaration

  #include <location.hh>

  // If you referenced kl_* in your %token types, define them (or stop using them):
  //using kl_bool   = bool;
  //using kl_double = double;
  //using kl_int    = long long;   // or int64_t
  //using kl_string = Str;

  namespace ast {
    struct Expr;        using ExprPtr      = Expr*;
    struct Statement;   using StatementPtr = Statement*;
    struct Type;        using TypePtr      = Type*;
    struct PathType;
    struct ParamDecl;   // forward decl is OK if you only pass pointers

    // If FieldInitExpr is a semantic value **by value**, give a full def here.
    struct FieldInitExpr { std::string name; ExprPtr value; lex::Loc loc; };
  }

  // If you insist on semantic values like std::vector<ast::ParamDecl> (by value),
  // you MUST also include its full definition here:
  #include "../ast/nodes/decl/param_decl.hpp"
  #include "../types.hpp"

#line 89 "parser_rules.tab.hh"


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
# define YYDEBUG 0
#endif

#line 4 "parser_rules.y"
namespace yy {
#line 225 "parser_rules.tab.hh"




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
      // TOK_TYPE_NAME
      // name
      // type_atom
      // ident
      char dummy1[sizeof (Str)];

      // expr_opt
      // expr
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
      // struct_lit
      char dummy2[sizeof (ast::ExprPtr)];

      // field_init
      char dummy3[sizeof (ast::FieldInitExpr)];

      // param
      char dummy4[sizeof (ast::ParamDecl)];

      // type_path
      char dummy5[sizeof (ast::PathType)];

      // translation_unit
      // opt_package
      // import_decl
      // decl
      // maybe_export
      // fn_decl
      // type_alias
      // block
      // stmt
      // else_opt
      // var_decl
      // init_declarator
      char dummy6[sizeof (ast::StatementPtr)];

      // ret_type
      // type_spec
      // builtin_type
      char dummy7[sizeof (ast::TypePtr)];

      // TOK_BOOL_LITERAL
      char dummy8[sizeof (kl_bool)];

      // TOK_FLOAT_LITERAL
      char dummy9[sizeof (kl_double)];

      // TOK_INT_LITERAL
      char dummy10[sizeof (kl_int)];

      // TOK_STRING_LITERAL
      char dummy11[sizeof (kl_string)];

      // names_separated_by_dots
      char dummy12[sizeof (std::vector<Str>)];

      // arg_list_opt
      // arg_list
      char dummy13[sizeof (std::vector<ast::ExprPtr>)];

      // field_inits_opt
      // field_inits
      char dummy14[sizeof (std::vector<ast::FieldInitExpr>)];

      // param_list_opt
      // param_list
      char dummy15[sizeof (std::vector<ast::ParamDecl>)];

      // import_list
      // decl_list
      // stmt_list
      // init_declarator_list
      char dummy16[sizeof (std::vector<ast::StatementPtr>)];
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
    typedef yy::location location_type;

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
    TOK_TRAIT = 263,               // TOK_TRAIT
    TOK_ENUM = 264,                // TOK_ENUM
    TOK_FN = 265,                  // TOK_FN
    TOK_TYPE = 266,                // TOK_TYPE
    TOK_LET = 267,                 // TOK_LET
    TOK_RETURN = 268,              // TOK_RETURN
    TOK_INT = 269,                 // TOK_INT
    TOK_BIGINT = 270,              // TOK_BIGINT
    TOK_MAGICINT = 271,            // TOK_MAGICINT
    TOK_DOUBLE = 272,              // TOK_DOUBLE
    TOK_BOOL = 273,                // TOK_BOOL
    TOK_VOID = 274,                // TOK_VOID
    TOK_STRING = 275,              // TOK_STRING
    TOK_BREAK = 276,               // TOK_BREAK
    TOK_CONTINUE = 277,            // TOK_CONTINUE
    TOK_IMPORT = 278,              // TOK_IMPORT
    TOK_EXPORT = 279,              // TOK_EXPORT
    TOK_PACKAGE = 280,             // TOK_PACKAGE
    TOK_AS = 281,                  // TOK_AS
    TOK_IDENTIFIER = 282,          // TOK_IDENTIFIER
    TOK_TYPE_NAME = 283,           // TOK_TYPE_NAME
    TOK_INT_LITERAL = 284,         // TOK_INT_LITERAL
    TOK_FLOAT_LITERAL = 285,       // TOK_FLOAT_LITERAL
    TOK_STRING_LITERAL = 286,      // TOK_STRING_LITERAL
    TOK_BOOL_LITERAL = 287,        // TOK_BOOL_LITERAL
    TOK_LPAR = 288,                // TOK_LPAR
    TOK_RPAR = 289,                // TOK_RPAR
    TOK_LBRACK = 290,              // TOK_LBRACK
    TOK_RBRACK = 291,              // TOK_RBRACK
    TOK_LCBRA = 292,               // TOK_LCBRA
    TOK_RCBRA = 293,               // TOK_RCBRA
    TOK_COMMA = 294,               // TOK_COMMA
    TOK_SMCLN = 295,               // TOK_SMCLN
    TOK_COLON = 296,               // TOK_COLON
    TOK_DOT = 297,                 // TOK_DOT
    TOK_QUESTION = 298,            // TOK_QUESTION
    TOK_ARROW = 299,               // TOK_ARROW
    TOK_NEGATION = 300,            // TOK_NEGATION
    TOK_NEG = 301,                 // TOK_NEG
    TOK_INC = 302,                 // TOK_INC
    TOK_DEC = 303,                 // TOK_DEC
    TOK_STAR = 304,                // TOK_STAR
    TOK_SLASH = 305,               // TOK_SLASH
    TOK_MODULO = 306,              // TOK_MODULO
    TOK_PLUS = 307,                // TOK_PLUS
    TOK_MINUS = 308,               // TOK_MINUS
    TOK_LESS = 309,                // TOK_LESS
    TOK_LEQ = 310,                 // TOK_LEQ
    TOK_GREATER = 311,             // TOK_GREATER
    TOK_GEQ = 312,                 // TOK_GEQ
    TOK_EQUAL = 313,               // TOK_EQUAL
    TOK_NEQUAL = 314,              // TOK_NEQUAL
    TOK_BOOL_AND = 315,            // TOK_BOOL_AND
    TOK_BOOL_OR = 316,             // TOK_BOOL_OR
    TOK_ASSIGN = 317,              // TOK_ASSIGN
    TOK_PLUS_ASSIGN = 318,         // TOK_PLUS_ASSIGN
    TOK_MIN_ASSIGN = 319,          // TOK_MIN_ASSIGN
    TOK_MUL_ASSIGN = 320,          // TOK_MUL_ASSIGN
    TOK_DIV_ASSIGN = 321,          // TOK_DIV_ASSIGN
    TERNARY = 322,                 // TERNARY
    UMINUS = 323,                  // UMINUS
    UPRE = 324                     // UPRE
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
        YYNTOKENS = 70, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TOK_IF = 3,                            // TOK_IF
        S_TOK_WHILE = 4,                         // TOK_WHILE
        S_TOK_DO = 5,                            // TOK_DO
        S_TOK_ELSE = 6,                          // TOK_ELSE
        S_TOK_STRUCT = 7,                        // TOK_STRUCT
        S_TOK_TRAIT = 8,                         // TOK_TRAIT
        S_TOK_ENUM = 9,                          // TOK_ENUM
        S_TOK_FN = 10,                           // TOK_FN
        S_TOK_TYPE = 11,                         // TOK_TYPE
        S_TOK_LET = 12,                          // TOK_LET
        S_TOK_RETURN = 13,                       // TOK_RETURN
        S_TOK_INT = 14,                          // TOK_INT
        S_TOK_BIGINT = 15,                       // TOK_BIGINT
        S_TOK_MAGICINT = 16,                     // TOK_MAGICINT
        S_TOK_DOUBLE = 17,                       // TOK_DOUBLE
        S_TOK_BOOL = 18,                         // TOK_BOOL
        S_TOK_VOID = 19,                         // TOK_VOID
        S_TOK_STRING = 20,                       // TOK_STRING
        S_TOK_BREAK = 21,                        // TOK_BREAK
        S_TOK_CONTINUE = 22,                     // TOK_CONTINUE
        S_TOK_IMPORT = 23,                       // TOK_IMPORT
        S_TOK_EXPORT = 24,                       // TOK_EXPORT
        S_TOK_PACKAGE = 25,                      // TOK_PACKAGE
        S_TOK_AS = 26,                           // TOK_AS
        S_TOK_IDENTIFIER = 27,                   // TOK_IDENTIFIER
        S_TOK_TYPE_NAME = 28,                    // TOK_TYPE_NAME
        S_TOK_INT_LITERAL = 29,                  // TOK_INT_LITERAL
        S_TOK_FLOAT_LITERAL = 30,                // TOK_FLOAT_LITERAL
        S_TOK_STRING_LITERAL = 31,               // TOK_STRING_LITERAL
        S_TOK_BOOL_LITERAL = 32,                 // TOK_BOOL_LITERAL
        S_TOK_LPAR = 33,                         // TOK_LPAR
        S_TOK_RPAR = 34,                         // TOK_RPAR
        S_TOK_LBRACK = 35,                       // TOK_LBRACK
        S_TOK_RBRACK = 36,                       // TOK_RBRACK
        S_TOK_LCBRA = 37,                        // TOK_LCBRA
        S_TOK_RCBRA = 38,                        // TOK_RCBRA
        S_TOK_COMMA = 39,                        // TOK_COMMA
        S_TOK_SMCLN = 40,                        // TOK_SMCLN
        S_TOK_COLON = 41,                        // TOK_COLON
        S_TOK_DOT = 42,                          // TOK_DOT
        S_TOK_QUESTION = 43,                     // TOK_QUESTION
        S_TOK_ARROW = 44,                        // TOK_ARROW
        S_TOK_NEGATION = 45,                     // TOK_NEGATION
        S_TOK_NEG = 46,                          // TOK_NEG
        S_TOK_INC = 47,                          // TOK_INC
        S_TOK_DEC = 48,                          // TOK_DEC
        S_TOK_STAR = 49,                         // TOK_STAR
        S_TOK_SLASH = 50,                        // TOK_SLASH
        S_TOK_MODULO = 51,                       // TOK_MODULO
        S_TOK_PLUS = 52,                         // TOK_PLUS
        S_TOK_MINUS = 53,                        // TOK_MINUS
        S_TOK_LESS = 54,                         // TOK_LESS
        S_TOK_LEQ = 55,                          // TOK_LEQ
        S_TOK_GREATER = 56,                      // TOK_GREATER
        S_TOK_GEQ = 57,                          // TOK_GEQ
        S_TOK_EQUAL = 58,                        // TOK_EQUAL
        S_TOK_NEQUAL = 59,                       // TOK_NEQUAL
        S_TOK_BOOL_AND = 60,                     // TOK_BOOL_AND
        S_TOK_BOOL_OR = 61,                      // TOK_BOOL_OR
        S_TOK_ASSIGN = 62,                       // TOK_ASSIGN
        S_TOK_PLUS_ASSIGN = 63,                  // TOK_PLUS_ASSIGN
        S_TOK_MIN_ASSIGN = 64,                   // TOK_MIN_ASSIGN
        S_TOK_MUL_ASSIGN = 65,                   // TOK_MUL_ASSIGN
        S_TOK_DIV_ASSIGN = 66,                   // TOK_DIV_ASSIGN
        S_TERNARY = 67,                          // TERNARY
        S_UMINUS = 68,                           // UMINUS
        S_UPRE = 69,                             // UPRE
        S_YYACCEPT = 70,                         // $accept
        S_translation_unit = 71,                 // translation_unit
        S_opt_package = 72,                      // opt_package
        S_import_list = 73,                      // import_list
        S_import_decl = 74,                      // import_decl
        S_names_separated_by_dots = 75,          // names_separated_by_dots
        S_name = 76,                             // name
        S_decl_list = 77,                        // decl_list
        S_decl = 78,                             // decl
        S_maybe_export = 79,                     // maybe_export
        S_fn_decl = 80,                          // fn_decl
        S_param_list_opt = 81,                   // param_list_opt
        S_param_list = 82,                       // param_list
        S_param = 83,                            // param
        S_ret_type = 84,                         // ret_type
        S_type_alias = 85,                       // type_alias
        S_type_spec = 86,                        // type_spec
        S_builtin_type = 87,                     // builtin_type
        S_type_path = 88,                        // type_path
        S_type_atom = 89,                        // type_atom
        S_ident = 90,                            // ident
        S_block = 91,                            // block
        S_stmt_list = 92,                        // stmt_list
        S_stmt = 93,                             // stmt
        S_else_opt = 94,                         // else_opt
        S_expr_opt = 95,                         // expr_opt
        S_var_decl = 96,                         // var_decl
        S_init_declarator_list = 97,             // init_declarator_list
        S_init_declarator = 98,                  // init_declarator
        S_expr = 99,                             // expr
        S_assign = 100,                          // assign
        S_cond = 101,                            // cond
        S_logic_or = 102,                        // logic_or
        S_logic_and = 103,                       // logic_and
        S_equality = 104,                        // equality
        S_relational = 105,                      // relational
        S_additive = 106,                        // additive
        S_multiplicative = 107,                  // multiplicative
        S_unary = 108,                           // unary
        S_postfix = 109,                         // postfix
        S_arg_list_opt = 110,                    // arg_list_opt
        S_arg_list = 111,                        // arg_list
        S_primary = 112,                         // primary
        S_struct_lit = 113,                      // struct_lit
        S_field_inits_opt = 114,                 // field_inits_opt
        S_field_inits = 115,                     // field_inits
        S_field_init = 116                       // field_init
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (std::move (that.value));
        break;

      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_expr: // expr
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
      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::ExprPtr > (std::move (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr > (std::move (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl > (std::move (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathType > (std::move (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_import_decl: // import_decl
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_maybe_export: // maybe_export
      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_type_alias: // type_alias
      case symbol_kind::S_block: // block
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_else_opt: // else_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_init_declarator: // init_declarator
        value.move< ast::StatementPtr > (std::move (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_double > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (std::move (that.value));
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.move< kl_string > (std::move (that.value));
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (std::move (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (std::move (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.move< std::vector<ast::StatementPtr> > (std::move (that.value));
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
      basic_symbol (typename Base::kind_type t, ast::ExprPtr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ExprPtr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::FieldInitExpr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::FieldInitExpr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::ParamDecl&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ParamDecl& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::PathType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::PathType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::StatementPtr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::StatementPtr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast::TypePtr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::TypePtr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl_bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl_bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl_double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl_double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl_int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl_int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, kl_string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const kl_string& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<ast::ExprPtr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ExprPtr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::FieldInitExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::FieldInitExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ParamDecl>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ParamDecl>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::StatementPtr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::StatementPtr>& v, const location_type& l)
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.template destroy< Str > ();
        break;

      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_expr: // expr
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
      case symbol_kind::S_struct_lit: // struct_lit
        value.template destroy< ast::ExprPtr > ();
        break;

      case symbol_kind::S_field_init: // field_init
        value.template destroy< ast::FieldInitExpr > ();
        break;

      case symbol_kind::S_param: // param
        value.template destroy< ast::ParamDecl > ();
        break;

      case symbol_kind::S_type_path: // type_path
        value.template destroy< ast::PathType > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_import_decl: // import_decl
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_maybe_export: // maybe_export
      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_type_alias: // type_alias
      case symbol_kind::S_block: // block
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_else_opt: // else_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_init_declarator: // init_declarator
        value.template destroy< ast::StatementPtr > ();
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.template destroy< ast::TypePtr > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.template destroy< kl_bool > ();
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.template destroy< kl_double > ();
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.template destroy< kl_int > ();
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.template destroy< kl_string > ();
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.template destroy< std::vector<Str> > ();
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.template destroy< std::vector<ast::ExprPtr> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.template destroy< std::vector<ast::FieldInitExpr> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.template destroy< std::vector<ast::ParamDecl> > ();
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.template destroy< std::vector<ast::StatementPtr> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


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
      symbol_type (int tok, kl_bool v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl_bool& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kl_double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl_double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kl_int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl_int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, kl_string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const kl_string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    parser (Scanner& scanner_yyarg);
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

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


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
      make_TOK_LET (location_type l)
      {
        return symbol_type (token::TOK_LET, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_LET (const location_type& l)
      {
        return symbol_type (token::TOK_LET, l);
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
      make_TOK_INT (location_type l)
      {
        return symbol_type (token::TOK_INT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_INT (const location_type& l)
      {
        return symbol_type (token::TOK_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BIGINT (location_type l)
      {
        return symbol_type (token::TOK_BIGINT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BIGINT (const location_type& l)
      {
        return symbol_type (token::TOK_BIGINT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_MAGICINT (location_type l)
      {
        return symbol_type (token::TOK_MAGICINT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_MAGICINT (const location_type& l)
      {
        return symbol_type (token::TOK_MAGICINT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_DOUBLE (location_type l)
      {
        return symbol_type (token::TOK_DOUBLE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_DOUBLE (const location_type& l)
      {
        return symbol_type (token::TOK_DOUBLE, l);
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
      make_TOK_STRING (location_type l)
      {
        return symbol_type (token::TOK_STRING, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STRING (const location_type& l)
      {
        return symbol_type (token::TOK_STRING, l);
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
      make_TOK_TYPE_NAME (Str v, location_type l)
      {
        return symbol_type (token::TOK_TYPE_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_TYPE_NAME (const Str& v, const location_type& l)
      {
        return symbol_type (token::TOK_TYPE_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_INT_LITERAL (kl_int v, location_type l)
      {
        return symbol_type (token::TOK_INT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_INT_LITERAL (const kl_int& v, const location_type& l)
      {
        return symbol_type (token::TOK_INT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_FLOAT_LITERAL (kl_double v, location_type l)
      {
        return symbol_type (token::TOK_FLOAT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_FLOAT_LITERAL (const kl_double& v, const location_type& l)
      {
        return symbol_type (token::TOK_FLOAT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_STRING_LITERAL (kl_string v, location_type l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_STRING_LITERAL (const kl_string& v, const location_type& l)
      {
        return symbol_type (token::TOK_STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOK_BOOL_LITERAL (kl_bool v, location_type l)
      {
        return symbol_type (token::TOK_BOOL_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_BOOL_LITERAL (const kl_bool& v, const location_type& l)
      {
        return symbol_type (token::TOK_BOOL_LITERAL, v, l);
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
      make_TOK_NEG (location_type l)
      {
        return symbol_type (token::TOK_NEG, std::move (l));
      }
#else
      static
      symbol_type
      make_TOK_NEG (const location_type& l)
      {
        return symbol_type (token::TOK_NEG, l);
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


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

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

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

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
      yylast_ = 266,     ///< Last index in yytable_.
      yynnts_ = 47,  ///< Number of nonterminal symbols.
      yyfinal_ = 7 ///< Termination state number.
    };


    // User arguments.
    Scanner& scanner;

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
      65,    66,    67,    68,    69
    };
    // Last valid token kind.
    const int code_max = 324;

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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.copy< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_expr: // expr
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
      case symbol_kind::S_struct_lit: // struct_lit
        value.copy< ast::ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.copy< ast::PathType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_import_decl: // import_decl
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_maybe_export: // maybe_export
      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_type_alias: // type_alias
      case symbol_kind::S_block: // block
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_else_opt: // else_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_init_declarator: // init_declarator
        value.copy< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.copy< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.copy< kl_bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.copy< kl_double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.copy< kl_int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.copy< kl_string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.copy< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.copy< std::vector<ast::StatementPtr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_opt: // expr_opt
      case symbol_kind::S_expr: // expr
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
      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::ExprPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_import_decl: // import_decl
      case symbol_kind::S_decl: // decl
      case symbol_kind::S_maybe_export: // maybe_export
      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_type_alias: // type_alias
      case symbol_kind::S_block: // block
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_else_opt: // else_opt
      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_init_declarator: // init_declarator
        value.move< ast::StatementPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.move< kl_string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.move< std::vector<ast::StatementPtr> > (YY_MOVE (s.value));
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


#line 4 "parser_rules.y"
} // yy
#line 3179 "parser_rules.tab.hh"




#endif // !YY_YY_PARSER_RULES_TAB_HH_INCLUDED
