// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 55 "parser_rules.y"

  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"
  #include <iostream>

  void yy::reserved::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << filePath << ':' << loc.begin.line << ':' << loc.begin.column
              << ": " << msg << '\n';
  }

  yy::reserved::parser::symbol_type yy::reserved::yylex(Scanner& scanner) {
    scanner.yylex();

    const lex::Token& t = scanner.getCurrentToken();
    const lex::Loc    L = t.loc_;

    using T = lex::Type;
    switch (t.type_) {
      /* payload-bearing */
      case T::TOK_IDENTIFIER:     return yy::reserved::parser::make_TOK_IDENTIFIER(t.u_.sym, L);
      case T::TOK_INT_LITERAL:    return yy::reserved::parser::make_TOK_INT_LITERAL(t.u_.sym, L);
      case T::TOK_FLOAT_LITERAL:  return yy::reserved::parser::make_TOK_FLOAT_LITERAL(t.u_.sym, L);
      case T::TOK_STRING_LITERAL: return yy::reserved::parser::make_TOK_STRING_LITERAL(t.u_.sym, L);
      case T::TOK_BOOL_LITERAL:   return yy::reserved::parser::make_TOK_BOOL_LITERAL(t.u_.boolean, L);
      case T::TOK_CHAR_LITERAL:   return yy::reserved::parser::make_TOK_CHAR_LITERAL(t.u_.ch, L);

      /* keywords */
      case T::TOK_FN:       return yy::reserved::parser::make_TOK_FN(L);
      case T::TOK_STRUCT:   return yy::reserved::parser::make_TOK_STRUCT(L);
      case T::TOK_IMPORT:   return yy::reserved::parser::make_TOK_IMPORT(L);
      case T::TOK_PACKAGE:  return yy::reserved::parser::make_TOK_PACKAGE(L);
      case T::TOK_AS:       return yy::reserved::parser::make_TOK_AS(L);
      case T::TOK_PUB:      return yy::reserved::parser::make_TOK_PUB(L);
      case T::TOK_MUT:      return yy::reserved::parser::make_TOK_MUT(L);
      case T::TOK_IMM:      return yy::reserved::parser::make_TOK_IMM(L);
      case T::TOK_LOAD:     return yy::reserved::parser::make_TOK_LOAD(L);

      /* builtin type keywords */
      case T::TOK_I8:   return yy::reserved::parser::make_TOK_I8(L);
      case T::TOK_U8:   return yy::reserved::parser::make_TOK_U8(L);
      case T::TOK_I16:  return yy::reserved::parser::make_TOK_I16(L);
      case T::TOK_U16:  return yy::reserved::parser::make_TOK_U16(L);
      case T::TOK_I32:  return yy::reserved::parser::make_TOK_I32(L);
      case T::TOK_U32:  return yy::reserved::parser::make_TOK_U32(L);
      case T::TOK_I64:  return yy::reserved::parser::make_TOK_I64(L);
      case T::TOK_U64:  return yy::reserved::parser::make_TOK_U64(L);
      case T::TOK_I128: return yy::reserved::parser::make_TOK_I128(L);
      case T::TOK_U128: return yy::reserved::parser::make_TOK_U128(L);
      case T::TOK_F32:  return yy::reserved::parser::make_TOK_F32(L);
      case T::TOK_F64:  return yy::reserved::parser::make_TOK_F64(L);
      case T::TOK_BOOL: return yy::reserved::parser::make_TOK_BOOL(L);
      case T::TOK_CHAR: return yy::reserved::parser::make_TOK_CHAR(L);
      case T::TOK_VOID: return yy::reserved::parser::make_TOK_VOID(L);

      /* punctuation */
      case T::TOK_LPAR:        return yy::reserved::parser::make_TOK_LPAR(L);
      case T::TOK_RPAR:        return yy::reserved::parser::make_TOK_RPAR(L);
      case T::TOK_LBRACK:      return yy::reserved::parser::make_TOK_LBRACK(L);
      case T::TOK_RBRACK:      return yy::reserved::parser::make_TOK_RBRACK(L);
      case T::TOK_LCBRA:       return yy::reserved::parser::make_TOK_LCBRA(L);
      case T::TOK_RCBRA:       return yy::reserved::parser::make_TOK_RCBRA(L);
      case T::TOK_COMMA:       return yy::reserved::parser::make_TOK_COMMA(L);
      case T::TOK_SMCLN:       return yy::reserved::parser::make_TOK_SMCLN(L);
      case T::TOK_COLON:       return yy::reserved::parser::make_TOK_COLON(L);
      case T::TOK_COLONCOLON:  return yy::reserved::parser::make_TOK_COLONCOLON(L);
      case T::TOK_ARROW:       return yy::reserved::parser::make_TOK_ARROW(L);
      case T::TOK_TURBOFISH_S: return yy::reserved::parser::make_TOK_TURBOFISH_S(L);
      case T::TOK_LESS:        return yy::reserved::parser::make_TOK_LESS(L);
      case T::TOK_GREATER:     return yy::reserved::parser::make_TOK_GREATER(L);

      /* operators used in type refs */
      case T::TOK_AMP:         return yy::reserved::parser::make_TOK_AMP(L);

      /* EOF / unknown */
      case T::TOK_END: return yy::reserved::parser::make_YYEOF(L);
      default:         return yy::reserved::parser::make_YYUNDEF(L);
    }
  }

  static inline lex::Loc combine(const lex::Loc& a, const lex::Loc& b) {
    lex::Loc L{};
    L.begin = a.begin;
    L.end   = b.end;
    return L;
  }

#line 134 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 17 "parser_rules.y"
namespace yy { namespace reserved {
#line 227 "parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner& scanner_yyarg, ast::Ast& ast_yyarg, Translation& unit_yyarg, std::string_view filePath_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      scanner (scanner_yyarg),
      ast (ast_yyarg),
      unit (unit_yyarg),
      filePath (filePath_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.YY_MOVE_OR_COPY< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.YY_MOVE_OR_COPY< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_decl: // sig_decl
        value.YY_MOVE_OR_COPY< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_int_expr: // const_int_expr
        value.YY_MOVE_OR_COPY< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_fn_decl: // sig_fn_decl
        value.YY_MOVE_OR_COPY< ast::FnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_load_fn_decl: // sig_load_fn_decl
        value.YY_MOVE_OR_COPY< ast::LoadFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.YY_MOVE_OR_COPY< ast::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ast::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
        value.YY_MOVE_OR_COPY< ast::PathExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.YY_MOVE_OR_COPY< ast::PathTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.YY_MOVE_OR_COPY< ast::RefTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_struct_decl: // sig_struct_decl
        value.YY_MOVE_OR_COPY< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.YY_MOVE_OR_COPY< ast::TypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_param: // type_param
        value.YY_MOVE_OR_COPY< ast::TypeParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.YY_MOVE_OR_COPY< kl::rt::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.YY_MOVE_OR_COPY< kl::rt::character > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path: // path
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_decl_list_opt: // sig_decl_list_opt
      case symbol_kind::S_sig_decl_list: // sig_decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_array_dims: // type_array_dims
        value.YY_MOVE_OR_COPY< std::vector<ast::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.YY_MOVE_OR_COPY< std::vector<ast::TypeExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::TypeParamDecl*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.move< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_decl: // sig_decl
        value.move< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_int_expr: // const_int_expr
        value.move< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_fn_decl: // sig_fn_decl
        value.move< ast::FnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_load_fn_decl: // sig_load_fn_decl
        value.move< ast::LoadFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
        value.move< ast::PathExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_struct_decl: // sig_struct_decl
        value.move< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.move< ast::TypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_param: // type_param
        value.move< ast::TypeParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.move< kl::rt::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path: // path
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sig_decl_list_opt: // sig_decl_list_opt
      case symbol_kind::S_sig_decl_list: // sig_decl_list
        value.move< std::vector<ast::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_array_dims: // type_array_dims
        value.move< std::vector<ast::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.move< std::vector<ast::TypeExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.move< std::vector<ast::TypeParamDecl*> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.copy< Str > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.copy< ast::BuiltinTypeExpr* > (that.value);
        break;

      case symbol_kind::S_sig_decl: // sig_decl
        value.copy< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_const_int_expr: // const_int_expr
        value.copy< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_sig_fn_decl: // sig_fn_decl
        value.copy< ast::FnDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_sig_load_fn_decl: // sig_load_fn_decl
        value.copy< ast::LoadFnDecl* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.copy< ast::Mutability > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_path_expr: // path_expr
        value.copy< ast::PathExpr* > (that.value);
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.copy< ast::PathTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.copy< ast::RefTypeExpr* > (that.value);
        break;

      case symbol_kind::S_sig_struct_decl: // sig_struct_decl
        value.copy< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.copy< ast::TypeExpr* > (that.value);
        break;

      case symbol_kind::S_type_param: // type_param
        value.copy< ast::TypeParamDecl* > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.copy< kl::rt::boolean > (that.value);
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.copy< kl::rt::character > (that.value);
        break;

      case symbol_kind::S_path: // path
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_sig_decl_list_opt: // sig_decl_list_opt
      case symbol_kind::S_sig_decl_list: // sig_decl_list
        value.copy< std::vector<ast::Decl*> > (that.value);
        break;

      case symbol_kind::S_type_array_dims: // type_array_dims
        value.copy< std::vector<ast::Expr*> > (that.value);
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.copy< std::vector<ast::TypeExpr*> > (that.value);
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.copy< std::vector<ast::TypeParamDecl*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        value.move< Str > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (that.value);
        break;

      case symbol_kind::S_sig_decl: // sig_decl
        value.move< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_const_int_expr: // const_int_expr
        value.move< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_sig_fn_decl: // sig_fn_decl
        value.move< ast::FnDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_sig_load_fn_decl: // sig_load_fn_decl
        value.move< ast::LoadFnDecl* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_path_expr: // path_expr
        value.move< ast::PathExpr* > (that.value);
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (that.value);
        break;

      case symbol_kind::S_sig_struct_decl: // sig_struct_decl
        value.move< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        value.move< ast::TypeExpr* > (that.value);
        break;

      case symbol_kind::S_type_param: // type_param
        value.move< ast::TypeParamDecl* > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        value.move< kl::rt::boolean > (that.value);
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (that.value);
        break;

      case symbol_kind::S_path: // path
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_sig_decl_list_opt: // sig_decl_list_opt
      case symbol_kind::S_sig_decl_list: // sig_decl_list
        value.move< std::vector<ast::Decl*> > (that.value);
        break;

      case symbol_kind::S_type_array_dims: // type_array_dims
        value.move< std::vector<ast::Expr*> > (that.value);
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        value.move< std::vector<ast::TypeExpr*> > (that.value);
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        value.move< std::vector<ast::TypeParamDecl*> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_TOK_IDENTIFIER: // TOK_IDENTIFIER
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
        yylhs.value.emplace< Str > ();
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        yylhs.value.emplace< ast::BuiltinTypeExpr* > ();
        break;

      case symbol_kind::S_sig_decl: // sig_decl
        yylhs.value.emplace< ast::Decl* > ();
        break;

      case symbol_kind::S_const_int_expr: // const_int_expr
        yylhs.value.emplace< ast::Expr* > ();
        break;

      case symbol_kind::S_sig_fn_decl: // sig_fn_decl
        yylhs.value.emplace< ast::FnDecl* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_sig_load_fn_decl: // sig_load_fn_decl
        yylhs.value.emplace< ast::LoadFnDecl* > ();
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        yylhs.value.emplace< ast::Mutability > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ast::ParamDecl* > ();
        break;

      case symbol_kind::S_path_expr: // path_expr
        yylhs.value.emplace< ast::PathExpr* > ();
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        yylhs.value.emplace< ast::PathTypeExpr* > ();
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        yylhs.value.emplace< ast::RefTypeExpr* > ();
        break;

      case symbol_kind::S_sig_struct_decl: // sig_struct_decl
        yylhs.value.emplace< ast::StructDecl* > ();
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
      case symbol_kind::S_type_postfix: // type_postfix
      case symbol_kind::S_type_primary: // type_primary
        yylhs.value.emplace< ast::TypeExpr* > ();
        break;

      case symbol_kind::S_type_param: // type_param
        yylhs.value.emplace< ast::TypeParamDecl* > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
        yylhs.value.emplace< kl::rt::boolean > ();
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        yylhs.value.emplace< kl::rt::character > ();
        break;

      case symbol_kind::S_path: // path
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_sig_decl_list_opt: // sig_decl_list_opt
      case symbol_kind::S_sig_decl_list: // sig_decl_list
        yylhs.value.emplace< std::vector<ast::Decl*> > ();
        break;

      case symbol_kind::S_type_array_dims: // type_array_dims
        yylhs.value.emplace< std::vector<ast::Expr*> > ();
        break;

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        yylhs.value.emplace< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<ast::ParamDecl*> > ();
        break;

      case symbol_kind::S_type_args: // type_args
      case symbol_kind::S_type_arg_list: // type_arg_list
        yylhs.value.emplace< std::vector<ast::TypeExpr*> > ();
        break;

      case symbol_kind::S_type_params_opt: // type_params_opt
      case symbol_kind::S_type_param_list: // type_param_list
        yylhs.value.emplace< std::vector<ast::TypeParamDecl*> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: sig_module
#line 223 "parser_rules.y"
    { }
#line 1185 "parser.cpp"
    break;

  case 3: // sig_module: TOK_PACKAGE path_expr TOK_SMCLN import_list_opt sig_decl_list_opt
#line 228 "parser_rules.y"
    {
      ast.mk_module(yystack_[3].value.as < ast::PathExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[4].location, yystack_[0].location));
      unit.addModule(std::move(ast));
    }
#line 1194 "parser.cpp"
    break;

  case 4: // import_list_opt: %empty
#line 240 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1200 "parser.cpp"
    break;

  case 5: // import_list_opt: import_list
#line 242 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1206 "parser.cpp"
    break;

  case 6: // import_list: import_decl
#line 247 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{ yystack_[0].value.as < ast::ImportDecl* > () }; }
#line 1212 "parser.cpp"
    break;

  case 7: // import_list: import_list import_decl
#line 249 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1218 "parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT path_expr TOK_SMCLN
#line 254 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < ast::PathExpr* > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1224 "parser.cpp"
    break;

  case 9: // import_decl: TOK_IMPORT path_expr TOK_AS ident_no_self TOK_SMCLN
#line 256 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < ast::PathExpr* > ()), std::optional<Str>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1230 "parser.cpp"
    break;

  case 10: // path: ident_any
#line 265 "parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[0].value.as < Str > () }; }
#line 1236 "parser.cpp"
    break;

  case 11: // path: path TOK_COLONCOLON ident_any
#line 267 "parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1242 "parser.cpp"
    break;

  case 12: // path_expr: path
#line 272 "parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1248 "parser.cpp"
    break;

  case 13: // ident_no_self: TOK_IDENTIFIER
#line 277 "parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1254 "parser.cpp"
    break;

  case 14: // ident_any: TOK_IDENTIFIER
#line 282 "parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1260 "parser.cpp"
    break;

  case 15: // type_params_opt: %empty
#line 291 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{}; }
#line 1266 "parser.cpp"
    break;

  case 16: // type_params_opt: TOK_LESS type_param_list TOK_GREATER
#line 293 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1272 "parser.cpp"
    break;

  case 17: // type_param_list: type_param
#line 298 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{ yystack_[0].value.as < ast::TypeParamDecl* > () }; }
#line 1278 "parser.cpp"
    break;

  case 18: // type_param_list: type_param_list TOK_COMMA type_param
#line 300 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ().push_back(yystack_[0].value.as < ast::TypeParamDecl* > ()); yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1284 "parser.cpp"
    break;

  case 19: // type_param_list: type_param_list TOK_COMMA
#line 302 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1290 "parser.cpp"
    break;

  case 20: // type_param: ident_no_self
#line 307 "parser_rules.y"
    { yylhs.value.as < ast::TypeParamDecl* > () = ast.mk_type_param_decl(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1296 "parser.cpp"
    break;

  case 21: // type_args: %empty
#line 312 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{}; }
#line 1302 "parser.cpp"
    break;

  case 22: // type_args: TOK_TURBOFISH_S type_arg_list TOK_GREATER
#line 314 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1308 "parser.cpp"
    break;

  case 23: // type_arg_list: type_expr
#line 319 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{ yystack_[0].value.as < ast::TypeExpr* > () }; }
#line 1314 "parser.cpp"
    break;

  case 24: // type_arg_list: type_arg_list TOK_COMMA type_expr
#line 321 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeExpr*> > ().push_back(yystack_[0].value.as < ast::TypeExpr* > ()); yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1320 "parser.cpp"
    break;

  case 25: // type_arg_list: type_arg_list TOK_COMMA
#line 323 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1326 "parser.cpp"
    break;

  case 26: // pub_opt: %empty
#line 331 "parser_rules.y"
             { yylhs.value.as < kl::rt::boolean > () = false; }
#line 1332 "parser.cpp"
    break;

  case 27: // pub_opt: TOK_PUB
#line 332 "parser_rules.y"
             { yylhs.value.as < kl::rt::boolean > () = true;  }
#line 1338 "parser.cpp"
    break;

  case 28: // sig_decl_list_opt: %empty
#line 337 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 1344 "parser.cpp"
    break;

  case 29: // sig_decl_list_opt: sig_decl_list
#line 339 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()); }
#line 1350 "parser.cpp"
    break;

  case 30: // sig_decl_list: sig_decl
#line 344 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{ yystack_[0].value.as < ast::Decl* > () }; }
#line 1356 "parser.cpp"
    break;

  case 31: // sig_decl_list: sig_decl_list sig_decl
#line 346 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(yystack_[0].value.as < ast::Decl* > ()); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 1362 "parser.cpp"
    break;

  case 32: // sig_decl: sig_fn_decl
#line 351 "parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FnDecl* > ()); }
#line 1368 "parser.cpp"
    break;

  case 33: // sig_decl: sig_load_fn_decl
#line 353 "parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::LoadFnDecl* > ()); }
#line 1374 "parser.cpp"
    break;

  case 34: // sig_decl: sig_struct_decl
#line 355 "parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1380 "parser.cpp"
    break;

  case 35: // sig_fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 362 "parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_FN */
      auto sigLoc = combine(start, yystack_[0].location);

      auto emptyBody = ast.mk_block_stmt(
        std::vector<ast::Statement*>{},
        ast::BlockKind::Fn,
        sigLoc
      );

      yylhs.value.as < ast::FnDecl* > () = ast.mk_fn_decl(
            yystack_[6].value.as < Str > (),                 /* name */
            std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()),      /* type params */
            std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()),      /* params */
            yystack_[1].value.as < ast::TypeExpr* > (),                 /* ret */
            emptyBody,          /* synthesized empty body */
            yystack_[8].value.as < kl::rt::boolean > (),                 /* isExported */
            sigLoc
          );
    }
#line 1405 "parser.cpp"
    break;

  case 36: // sig_load_fn_decl: pub_opt TOK_LOAD TOK_FN ident_no_self TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 387 "parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_LOAD */
      yylhs.value.as < ast::LoadFnDecl* > () = ast.mk_load_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 1414 "parser.cpp"
    break;

  case 37: // sig_struct_decl: pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_SMCLN
#line 396 "parser_rules.y"
    {
      auto start = yystack_[4].value.as < kl::rt::boolean > () ? yystack_[4].location : yystack_[3].location; /* TOK_PUB if present else TOK_STRUCT */
      yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(
            yystack_[2].value.as < Str > (),
            std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::vector<ast::FieldDecl*>{},
            yystack_[4].value.as < kl::rt::boolean > (),
            combine(start, yystack_[0].location)
          );
    }
#line 1429 "parser.cpp"
    break;

  case 38: // param_list_opt: %empty
#line 414 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 1435 "parser.cpp"
    break;

  case 39: // param_list_opt: param_list
#line 416 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1441 "parser.cpp"
    break;

  case 40: // param_list: param
#line 421 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{ yystack_[0].value.as < ast::ParamDecl* > () }; }
#line 1447 "parser.cpp"
    break;

  case 41: // param_list: param_list TOK_COMMA param
#line 423 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1453 "parser.cpp"
    break;

  case 42: // param_list: param_list TOK_COMMA
#line 425 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1459 "parser.cpp"
    break;

  case 43: // param: ident_no_self TOK_COLON type_expr
#line 430 "parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1465 "parser.cpp"
    break;

  case 44: // ret_type_expr: TOK_ARROW type_expr
#line 436 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 1471 "parser.cpp"
    break;

  case 45: // type_expr: ref_type_expr
#line 441 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 1477 "parser.cpp"
    break;

  case 46: // type_expr: type_postfix
#line 443 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 1483 "parser.cpp"
    break;

  case 47: // ref_type_expr: TOK_AMP ref_mutability type_postfix
#line 448 "parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1489 "parser.cpp"
    break;

  case 48: // ref_mutability: %empty
#line 452 "parser_rules.y"
             { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 1495 "parser.cpp"
    break;

  case 49: // ref_mutability: TOK_IMM
#line 453 "parser_rules.y"
             { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 1501 "parser.cpp"
    break;

  case 50: // ref_mutability: TOK_MUT
#line 454 "parser_rules.y"
             { yylhs.value.as < ast::Mutability > () = ast::Mutability::Mut; }
#line 1507 "parser.cpp"
    break;

  case 51: // type_postfix: type_primary type_array_dims
#line 459 "parser_rules.y"
        {
          ast::TypeExpr* t = yystack_[1].value.as < ast::TypeExpr* > ();

          if (!yystack_[0].value.as < std::vector<ast::Expr*> > ().empty())
          {
            const lex::Loc whole = combine(yystack_[1].location, yystack_[0].location);

            // IMPORTANT: apply dims right-to-left
            for (auto it = yystack_[0].value.as < std::vector<ast::Expr*> > ().rbegin(); it != yystack_[0].value.as < std::vector<ast::Expr*> > ().rend(); ++it)
            {
              t = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr(t, *it, whole));
            }
          }

          yylhs.value.as < ast::TypeExpr* > () = t;
        }
#line 1528 "parser.cpp"
    break;

  case 52: // type_array_dims: %empty
#line 479 "parser_rules.y"
        { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 1534 "parser.cpp"
    break;

  case 53: // type_array_dims: type_array_dims TOK_LBRACK const_int_expr TOK_RBRACK
#line 481 "parser_rules.y"
        { yystack_[3].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[1].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[3].value.as < std::vector<ast::Expr*> > ()); }
#line 1540 "parser.cpp"
    break;

  case 54: // type_primary: builtin_type_expr
#line 486 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 1546 "parser.cpp"
    break;

  case 55: // type_primary: path_type_expr
#line 488 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 1552 "parser.cpp"
    break;

  case 56: // type_primary: TOK_LPAR type_expr TOK_RPAR
#line 490 "parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[1].value.as < ast::TypeExpr* > (); }
#line 1558 "parser.cpp"
    break;

  case 57: // builtin_type_expr: TOK_I8
#line 494 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 1564 "parser.cpp"
    break;

  case 58: // builtin_type_expr: TOK_U8
#line 495 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 1570 "parser.cpp"
    break;

  case 59: // builtin_type_expr: TOK_I16
#line 496 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 1576 "parser.cpp"
    break;

  case 60: // builtin_type_expr: TOK_U16
#line 497 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 1582 "parser.cpp"
    break;

  case 61: // builtin_type_expr: TOK_I32
#line 498 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 1588 "parser.cpp"
    break;

  case 62: // builtin_type_expr: TOK_U32
#line 499 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 1594 "parser.cpp"
    break;

  case 63: // builtin_type_expr: TOK_I64
#line 500 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 1600 "parser.cpp"
    break;

  case 64: // builtin_type_expr: TOK_U64
#line 501 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 1606 "parser.cpp"
    break;

  case 65: // builtin_type_expr: TOK_I128
#line 502 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 1612 "parser.cpp"
    break;

  case 66: // builtin_type_expr: TOK_U128
#line 503 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 1618 "parser.cpp"
    break;

  case 67: // builtin_type_expr: TOK_F32
#line 504 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 1624 "parser.cpp"
    break;

  case 68: // builtin_type_expr: TOK_F64
#line 505 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 1630 "parser.cpp"
    break;

  case 69: // builtin_type_expr: TOK_BOOL
#line 506 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 1636 "parser.cpp"
    break;

  case 70: // builtin_type_expr: TOK_CHAR
#line 507 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 1642 "parser.cpp"
    break;

  case 71: // builtin_type_expr: TOK_VOID
#line 508 "parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Void, yystack_[0].location); }
#line 1648 "parser.cpp"
    break;

  case 72: // path_type_expr: path_expr type_args
#line 513 "parser_rules.y"
    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[1].value.as < ast::PathExpr* > (), std::move(yystack_[0].value.as < std::vector<ast::TypeExpr*> > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 1654 "parser.cpp"
    break;

  case 73: // const_int_expr: TOK_INT_LITERAL
#line 522 "parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[0].value.as < Str > (), std::nullopt, yystack_[0].location); }
#line 1660 "parser.cpp"
    break;


#line 1664 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -59;

  const signed char parser::yytable_ninf_ = -30;

  const signed char
  parser::yypact_[] =
  {
      13,    -3,    31,   -59,   -59,   -16,    -9,   -59,   -59,    -3,
      32,   -59,    -3,    18,    32,   -59,     9,   -59,    36,   -59,
      25,   -59,   -59,   -59,   -59,   -59,    22,   -59,    22,    22,
      41,   -59,   -59,     8,    33,    33,    22,   -59,    22,    29,
      37,    42,   -59,     1,   -59,   -59,    22,    22,   -59,    22,
      34,    44,    35,   -59,    45,   -59,   -12,    39,    22,    39,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,   -12,    38,    43,   -59,   -59,
     -59,   -59,   -59,   -59,   -12,    46,   -59,    48,    47,   -59,
     -59,    40,   -12,   -59,    50,   -59,   -59,   -59,   -59,   -59,
      28,   -59,    52,   -59,   -12,   -59,    51,   -59,   -59
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,    14,    12,     0,    10,     1,     0,
       4,    11,     0,    26,     5,     6,     0,    27,     0,     3,
      26,    30,    32,    33,    34,     7,     0,     8,     0,     0,
       0,    31,    13,     0,    15,    15,     0,     9,     0,     0,
       0,     0,    20,     0,    17,    37,    38,    38,    16,    19,
       0,     0,    39,    40,     0,    18,     0,     0,    42,     0,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    48,    21,    43,    45,
      46,    52,    54,    55,     0,     0,    41,     0,     0,    50,
      49,     0,     0,    72,    51,    44,    35,    36,    56,    47,
       0,    23,     0,    22,    25,    73,     0,    24,    53
  };

  const signed char
  parser::yypgoto_[] =
  {
     -59,   -59,   -59,   -59,   -59,    60,   -59,    26,    -6,    73,
      56,   -59,    49,   -59,   -59,   -59,   -59,   -59,    63,   -59,
     -59,   -59,    53,   -59,    54,    27,   -58,   -59,   -59,     2,
     -59,   -59,   -59,   -59,   -59
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,     3,    13,    14,    15,     5,    77,    50,     7,
      39,    43,    44,    93,   100,    18,    19,    20,    21,    22,
      23,    24,    51,    52,    53,    85,    78,    79,    91,    80,
      94,    81,    82,    83,   106
  };

  const signed char
  parser::yytable_[] =
  {
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     4,    26,    88,   -28,     1,
      33,    75,    34,    35,     4,   -29,    95,     6,     9,    17,
      41,     8,    42,    10,   101,    76,    17,    12,    16,    28,
      29,    48,    49,    42,    30,    36,   107,    89,    90,    32,
      37,    27,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     4,   103,   104,
      46,    45,    38,    75,    25,    47,    58,    56,    57,    59,
     105,    98,    11,    31,    84,   102,    87,   108,    96,    92,
      97,    40,     0,    99,     0,     0,     0,     0,    55,     0,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86
  };

  const signed char
  parser::yycheck_[] =
  {
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,     7,    75,     0,     6,
      26,    33,    28,    29,    27,     0,    84,     1,    44,    11,
      36,     0,    38,    42,    92,    47,    11,     5,    12,     3,
       4,    40,    41,    49,     8,     4,   104,     9,    10,    27,
      42,    42,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    40,    41,
      33,    42,    39,    33,    14,    33,    41,    43,    34,    34,
      28,    34,     9,    20,    45,    35,    59,    36,    42,    46,
      42,    35,    -1,    91,    -1,    -1,    -1,    -1,    49,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58
  };

  const signed char
  parser::yystos_[] =
  {
       0,     6,    49,    50,    27,    54,    55,    57,     0,    44,
      42,    57,     5,    51,    52,    53,    55,    11,    63,    64,
      65,    66,    67,    68,    69,    53,     7,    42,     3,     4,
       8,    66,    27,    56,    56,    56,     4,    42,    39,    58,
      58,    56,    56,    59,    60,    42,    33,    33,    40,    41,
      56,    70,    71,    72,    70,    60,    43,    34,    41,    34,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    33,    47,    55,    74,    75,
      77,    79,    80,    81,    45,    73,    72,    73,    74,     9,
      10,    76,    46,    61,    78,    74,    42,    42,    34,    77,
      62,    74,    35,    40,    41,    28,    82,    74,    36
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    48,    49,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    55,    56,    57,    58,    58,    59,    59,    59,
      60,    61,    61,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    67,    68,    69,    70,    70,
      71,    71,    71,    72,    73,    74,    74,    75,    76,    76,
      76,    77,    78,    78,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    82
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     5,     0,     1,     1,     2,     3,     5,
       1,     3,     1,     1,     1,     0,     3,     1,     3,     2,
       1,     0,     3,     1,     3,     2,     0,     1,     0,     1,
       1,     2,     1,     1,     1,     9,     9,     5,     0,     1,
       1,     3,     2,     3,     2,     1,     1,     3,     0,     1,
       1,     2,     0,     4,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_STRUCT", "TOK_FN",
  "TOK_IMPORT", "TOK_PACKAGE", "TOK_AS", "TOK_LOAD", "TOK_MUT", "TOK_IMM",
  "TOK_PUB", "TOK_I8", "TOK_U8", "TOK_I16", "TOK_U16", "TOK_I32",
  "TOK_U32", "TOK_I64", "TOK_U64", "TOK_I128", "TOK_U128", "TOK_F32",
  "TOK_F64", "TOK_BOOL", "TOK_CHAR", "TOK_VOID", "TOK_IDENTIFIER",
  "TOK_INT_LITERAL", "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL",
  "TOK_BOOL_LITERAL", "TOK_CHAR_LITERAL", "TOK_LPAR", "TOK_RPAR",
  "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA", "TOK_RCBRA", "TOK_LESS",
  "TOK_GREATER", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON", "TOK_COLONCOLON",
  "TOK_ARROW", "TOK_TURBOFISH_S", "TOK_AMP", "$accept", "translation_unit",
  "sig_module", "import_list_opt", "import_list", "import_decl", "path",
  "path_expr", "ident_no_self", "ident_any", "type_params_opt",
  "type_param_list", "type_param", "type_args", "type_arg_list", "pub_opt",
  "sig_decl_list_opt", "sig_decl_list", "sig_decl", "sig_fn_decl",
  "sig_load_fn_decl", "sig_struct_decl", "param_list_opt", "param_list",
  "param", "ret_type_expr", "type_expr", "ref_type_expr", "ref_mutability",
  "type_postfix", "type_array_dims", "type_primary", "builtin_type_expr",
  "path_type_expr", "const_int_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   222,   222,   227,   239,   241,   246,   248,   253,   255,
     264,   266,   271,   276,   281,   290,   292,   297,   299,   301,
     306,   311,   313,   318,   320,   322,   331,   332,   336,   338,
     343,   345,   350,   352,   354,   361,   386,   395,   413,   415,
     420,   422,   424,   429,   435,   440,   442,   447,   452,   453,
     454,   458,   478,   480,   485,   487,   489,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   512,   521
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 17 "parser_rules.y"
} } // yy::reserved
#line 2356 "parser.cpp"

#line 525 "parser_rules.y"

