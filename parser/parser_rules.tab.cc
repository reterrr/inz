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





#include "parser_rules.tab.hh"


// Unqualified %code blocks.
#line 56 "parser_rules.y"

  #include "../ast/nodes/decl/param_decl.hpp"  // only if parser.cc needs it
  #include "../ast/nodes/type/type.hpp"
  #include "../types.hpp"

  using Str = lex::SymId;

  // statements
  ast::StatementPtr mk_block_stmt(std::vector<ast::StatementPtr>&&, const lex::Loc&);
  ast::StatementPtr mk_return_stmt(ast::ExprPtr, const lex::Loc&);
  ast::StatementPtr mk_if_stmt(ast::ExprPtr, ast::StatementPtr, ast::StatementPtr, const lex::Loc&);
  ast::StatementPtr mk_while_stmt(ast::ExprPtr, ast::StatementPtr, const lex::Loc&);
  ast::StatementPtr mk_do_while_stmt(ast::StatementPtr, ast::ExprPtr, const lex::Loc&);
  ast::StatementPtr mk_break_stmt(const lex::Loc&);
  ast::StatementPtr mk_continue_stmt(const lex::Loc&);

  // decls
  ast::StatementPtr mk_fn_decl(const Str& name,
                               std::vector<ast::ParamDecl*>&& params, // <-- pointer, see note below
                               ast::TypePtr ret_type,
                               ast::StatementPtr body,
                               const lex::Loc& loc);
  ast::StatementPtr mk_var_decl(ast::TypePtr, Str, ast::ExprPtr, const lex::Loc&);

  // expressions
  ast::ExprPtr mk_ref_expr(const Str&, const lex::Loc&);
  ast::ExprPtr mk_int_literal_expr(long long, const lex::Loc&);
  ast::ExprPtr mk_float_literal_expr(double, const lex::Loc&);
  ast::ExprPtr mk_str_literal_expr(const Str&, const lex::Loc&);
  ast::ExprPtr mk_bool_literal_expr(bool, const lex::Loc&);
  ast::ExprPtr mk_call_expr(ast::ExprPtr, std::vector<ast::ExprPtr>&&, const lex::Loc&);
  ast::ExprPtr mk_index_expr(ast::ExprPtr, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_field_expr(ast::ExprPtr, const Str&, const lex::Loc&);
  ast::ExprPtr mk_postfix_incdec_expr(ast::ExprPtr, bool, const lex::Loc&);
  ast::ExprPtr mk_prefix_incdec_expr(ast::ExprPtr, bool, const lex::Loc&);
  ast::ExprPtr mk_unary_expr_neg(ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_unary_expr_not(ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_binary_expr(ast::ExprPtr, int, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_assign_expr(ast::ExprPtr, int, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_cond_expr(ast::ExprPtr, ast::ExprPtr, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_struct_literal_expr(ast::PathType,
                                      std::vector<ast::FieldInitExpr *>&&, const lex::Loc&);
  ast::ExprPtr mk_field_init(const Str&, ast::ExprPtr, const lex::Loc&);

  // types
  ast::TypePtr mk_builtin_type(int, const lex::Loc&);
  ast::TypePtr mk_array_type(ast::TypePtr, const lex::Loc&);
  ast::TypePtr mk_type_from_path(const ast::PathType&, const lex::Loc&);

#line 96 "parser_rules.tab.cc"


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

#line 4 "parser_rules.y"
namespace yy {
#line 189 "parser_rules.tab.cc"

  /// Build a parser object.
  parser::parser (Scanner& scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.YY_MOVE_OR_COPY< Str > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< ast::ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.YY_MOVE_OR_COPY< ast::FieldInitExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ast::ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.YY_MOVE_OR_COPY< ast::PathType > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.YY_MOVE_OR_COPY< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.YY_MOVE_OR_COPY< kl_bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.YY_MOVE_OR_COPY< kl_double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.YY_MOVE_OR_COPY< kl_int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.YY_MOVE_OR_COPY< kl_string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldInitExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.YY_MOVE_OR_COPY< std::vector<ast::StatementPtr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (YY_MOVE (that.value));
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
        value.move< ast::ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathType > (YY_MOVE (that.value));
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
        value.move< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.move< kl_string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.move< std::vector<ast::StatementPtr> > (YY_MOVE (that.value));
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.copy< Str > (that.value);
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
        value.copy< ast::ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitExpr > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDecl > (that.value);
        break;

      case symbol_kind::S_type_path: // type_path
        value.copy< ast::PathType > (that.value);
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
        value.copy< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.copy< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.copy< kl_bool > (that.value);
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.copy< kl_double > (that.value);
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.copy< kl_int > (that.value);
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.copy< kl_string > (that.value);
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitExpr> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.copy< std::vector<ast::StatementPtr> > (that.value);
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (that.value);
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
        value.move< ast::ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl > (that.value);
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathType > (that.value);
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
        value.move< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (that.value);
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_double > (that.value);
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (that.value);
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        value.move< kl_string > (that.value);
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        value.move< std::vector<ast::StatementPtr> > (that.value);
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
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Str > ();
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
        yylhs.value.emplace< ast::ExprPtr > ();
        break;

      case symbol_kind::S_field_init: // field_init
        yylhs.value.emplace< ast::FieldInitExpr > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ast::ParamDecl > ();
        break;

      case symbol_kind::S_type_path: // type_path
        yylhs.value.emplace< ast::PathType > ();
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
        yylhs.value.emplace< ast::StatementPtr > ();
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        yylhs.value.emplace< ast::TypePtr > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        yylhs.value.emplace< kl_bool > ();
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        yylhs.value.emplace< kl_double > ();
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        yylhs.value.emplace< kl_int > ();
        break;

      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
        yylhs.value.emplace< kl_string > ();
        break;

      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        yylhs.value.emplace< std::vector<ast::ExprPtr> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        yylhs.value.emplace< std::vector<ast::FieldInitExpr> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<ast::ParamDecl> > ();
        break;

      case symbol_kind::S_import_list: // import_list
      case symbol_kind::S_decl_list: // decl_list
      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_init_declarator_list: // init_declarator_list
        yylhs.value.emplace< std::vector<ast::StatementPtr> > ();
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
  case 2: // translation_unit: opt_package import_list decl_list
#line 199 "parser_rules.y"
    {
      // If you have a Program node, build it here. For now, just wrap decls in a block.
      yylhs.value.as < ast::StatementPtr > () = mk_block_stmt(std::move(yystack_[0].value.as < std::vector<ast::StatementPtr> > ()), yystack_[2].location + yystack_[0].location);
    }
#line 1086 "parser_rules.tab.cc"
    break;

  case 3: // opt_package: %empty
#line 206 "parser_rules.y"
                                                { yylhs.value.as < ast::StatementPtr > () = nullptr; }
#line 1092 "parser_rules.tab.cc"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 208 "parser_rules.y"
    {
      // If you model packages, create a node. Otherwise ignore.
      yylhs.value.as < ast::StatementPtr > () = nullptr;
    }
#line 1101 "parser_rules.tab.cc"
    break;

  case 5: // import_list: %empty
#line 215 "parser_rules.y"
                                                { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1107 "parser_rules.tab.cc"
    break;

  case 6: // import_list: import_list import_decl
#line 217 "parser_rules.y"
    {
      yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ()));
      yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ());
    }
#line 1116 "parser_rules.tab.cc"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 225 "parser_rules.y"
    {
      // Build an import node if you have one; otherwise return nullptr placeholder.
      yylhs.value.as < ast::StatementPtr > () = nullptr;
    }
#line 1125 "parser_rules.tab.cc"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 230 "parser_rules.y"
    {
      yylhs.value.as < ast::StatementPtr > () = nullptr;
    }
#line 1133 "parser_rules.tab.cc"
    break;

  case 9: // names_separated_by_dots: name
#line 237 "parser_rules.y"
    { std::vector<Str> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1139 "parser_rules.tab.cc"
    break;

  case 10: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 239 "parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1145 "parser_rules.tab.cc"
    break;

  case 11: // name: TOK_IDENTIFIER
#line 244 "parser_rules.y"
    { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1151 "parser_rules.tab.cc"
    break;

  case 12: // decl_list: %empty
#line 250 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1157 "parser_rules.tab.cc"
    break;

  case 13: // decl_list: decl_list decl
#line 252 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1163 "parser_rules.tab.cc"
    break;

  case 14: // decl: maybe_export fn_decl
#line 256 "parser_rules.y"
                              { yylhs.value.as < ast::StatementPtr > () = std::move(yystack_[0].value.as < ast::StatementPtr > ()); }
#line 1169 "parser_rules.tab.cc"
    break;

  case 15: // decl: maybe_export type_alias
#line 257 "parser_rules.y"
                              { yylhs.value.as < ast::StatementPtr > () = std::move(yystack_[0].value.as < ast::StatementPtr > ()); }
#line 1175 "parser_rules.tab.cc"
    break;

  case 16: // decl: maybe_export var_decl
#line 258 "parser_rules.y"
                              { yylhs.value.as < ast::StatementPtr > () = std::move(yystack_[0].value.as < ast::StatementPtr > ()); }
#line 1181 "parser_rules.tab.cc"
    break;

  case 17: // decl: maybe_export
#line 259 "parser_rules.y"
                                                          { yylhs.value.as < ast::StatementPtr > () = nullptr; }
#line 1187 "parser_rules.tab.cc"
    break;

  case 18: // maybe_export: %empty
#line 263 "parser_rules.y"
                  { yylhs.value.as < ast::StatementPtr > () = nullptr; }
#line 1193 "parser_rules.tab.cc"
    break;

  case 19: // maybe_export: TOK_EXPORT
#line 264 "parser_rules.y"
                  { yylhs.value.as < ast::StatementPtr > () = nullptr; }
#line 1199 "parser_rules.tab.cc"
    break;

  case 20: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block
#line 271 "parser_rules.y"
    {
      yylhs.value.as < ast::StatementPtr > () = mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl> > ()), yystack_[1].value.as < ast::TypePtr > (), std::move(yystack_[0].value.as < ast::StatementPtr > ()), yystack_[6].location + yystack_[0].location);
    }
#line 1207 "parser_rules.tab.cc"
    break;

  case 21: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN
#line 275 "parser_rules.y"
    {
      yylhs.value.as < ast::StatementPtr > () = mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl> > ()), yystack_[1].value.as < ast::TypePtr > (), nullptr, yystack_[6].location + yystack_[1].location);
    }
#line 1215 "parser_rules.tab.cc"
    break;

  case 22: // param_list_opt: %empty
#line 282 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl> > () = std::vector<ast::ParamDecl>{}; }
#line 1221 "parser_rules.tab.cc"
    break;

  case 23: // param_list_opt: param_list
#line 283 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl> > () = yystack_[0].value.as < std::vector<ast::ParamDecl> > (); }
#line 1227 "parser_rules.tab.cc"
    break;

  case 24: // param_list: param
#line 288 "parser_rules.y"
    { std::vector<ast::ParamDecl> v; v.push_back(std::move(yystack_[0].value.as < ast::ParamDecl > ())); yylhs.value.as < std::vector<ast::ParamDecl> > () = std::move(v); }
#line 1233 "parser_rules.tab.cc"
    break;

  case 25: // param_list: param_list TOK_COMMA param
#line 290 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl> > ().push_back(std::move(yystack_[0].value.as < ast::ParamDecl > ())); yylhs.value.as < std::vector<ast::ParamDecl> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl> > ()); }
#line 1239 "parser_rules.tab.cc"
    break;

  case 26: // param_list: param_list TOK_COMMA
#line 292 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl> > ()); }
#line 1245 "parser_rules.tab.cc"
    break;

  case 27: // param: type_spec ident
#line 297 "parser_rules.y"
    {
      // Build your ParamDecl here; assuming ParamDecl{TypePtr, string, Loc}
      extern ast::ParamDecl mk_param(ast::TypePtr, const Str&, const lex::Loc&);
      yylhs.value.as < ast::ParamDecl > () = mk_param(yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < Str > (), yystack_[1].location + yystack_[0].location);
    }
#line 1255 "parser_rules.tab.cc"
    break;

  case 28: // ret_type: TOK_ARROW type_spec
#line 305 "parser_rules.y"
                          { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1261 "parser_rules.tab.cc"
    break;

  case 29: // type_alias: TOK_TYPE ident TOK_ASSIGN type_spec TOK_SMCLN
#line 310 "parser_rules.y"
    {
      // Build a type alias node if you have one; for now, stub:
      yylhs.value.as < ast::StatementPtr > () = nullptr;
    }
#line 1270 "parser_rules.tab.cc"
    break;

  case 30: // type_spec: builtin_type
#line 319 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1276 "parser_rules.tab.cc"
    break;

  case 31: // type_spec: type_path
#line 320 "parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = mk_type_from_path(yystack_[0].value.as < ast::PathType > (), yystack_[0].location); }
#line 1282 "parser_rules.tab.cc"
    break;

  case 32: // type_spec: TOK_LBRACK type_spec TOK_RBRACK
#line 322 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = mk_array_type(yystack_[1].value.as < ast::TypePtr > (), yystack_[2].location + yystack_[0].location); }
#line 1288 "parser_rules.tab.cc"
    break;

  case 33: // builtin_type: TOK_INT
#line 326 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_INT, yystack_[0].location); }
#line 1294 "parser_rules.tab.cc"
    break;

  case 34: // builtin_type: TOK_BIGINT
#line 327 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_BIGINT, yystack_[0].location); }
#line 1300 "parser_rules.tab.cc"
    break;

  case 35: // builtin_type: TOK_MAGICINT
#line 328 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_MAGICINT, yystack_[0].location); }
#line 1306 "parser_rules.tab.cc"
    break;

  case 36: // builtin_type: TOK_DOUBLE
#line 329 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_DOUBLE, yystack_[0].location); }
#line 1312 "parser_rules.tab.cc"
    break;

  case 37: // builtin_type: TOK_BOOL
#line 330 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_BOOL, yystack_[0].location); }
#line 1318 "parser_rules.tab.cc"
    break;

  case 38: // builtin_type: TOK_VOID
#line 331 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_VOID, yystack_[0].location); }
#line 1324 "parser_rules.tab.cc"
    break;

  case 39: // builtin_type: TOK_STRING
#line 332 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = mk_builtin_type(TOK_STRING, yystack_[0].location); }
#line 1330 "parser_rules.tab.cc"
    break;

  case 40: // type_path: type_atom
#line 337 "parser_rules.y"
    {
      // Build a single-segment path
      extern ast::PathType mk_type_path_single(const Str&, const lex::Loc&);
      yylhs.value.as < ast::PathType > () = mk_type_path_single(yystack_[0].value.as < Str > (), yystack_[0].location);
    }
#line 1340 "parser_rules.tab.cc"
    break;

  case 41: // type_path: type_path TOK_DOT type_atom
#line 343 "parser_rules.y"
    {
      // Append segment
      extern ast::PathType mk_type_path_append(ast::PathType, const Str&, const lex::Loc&);
      yylhs.value.as < ast::PathType > () = mk_type_path_append(yystack_[2].value.as < ast::PathType > (), yystack_[0].value.as < Str > (), yystack_[2].location + yystack_[0].location);
    }
#line 1350 "parser_rules.tab.cc"
    break;

  case 42: // type_atom: TOK_TYPE_NAME
#line 351 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1356 "parser_rules.tab.cc"
    break;

  case 43: // type_atom: TOK_IDENTIFIER
#line 352 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1362 "parser_rules.tab.cc"
    break;

  case 44: // ident: TOK_IDENTIFIER
#line 356 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1368 "parser_rules.tab.cc"
    break;

  case 45: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 363 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()), yystack_[2].location + yystack_[0].location); }
#line 1374 "parser_rules.tab.cc"
    break;

  case 46: // stmt_list: %empty
#line 368 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1380 "parser_rules.tab.cc"
    break;

  case 47: // stmt_list: stmt_list stmt
#line 370 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1386 "parser_rules.tab.cc"
    break;

  case 48: // stmt: var_decl
#line 374 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = yystack_[0].value.as < ast::StatementPtr > (); }
#line 1392 "parser_rules.tab.cc"
    break;

  case 49: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 376 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_return_stmt(std::move(yystack_[1].value.as < ast::ExprPtr > ()), yystack_[2].location); }
#line 1398 "parser_rules.tab.cc"
    break;

  case 50: // stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt else_opt
#line 378 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_if_stmt(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::StatementPtr > ()), std::move(yystack_[0].value.as < ast::StatementPtr > ()), yystack_[5].location + yystack_[1].location); }
#line 1404 "parser_rules.tab.cc"
    break;

  case 51: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR stmt
#line 380 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_while_stmt(std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::StatementPtr > ()), yystack_[4].location + yystack_[0].location); }
#line 1410 "parser_rules.tab.cc"
    break;

  case 52: // stmt: TOK_DO stmt TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 382 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_do_while_stmt(std::move(yystack_[5].value.as < ast::StatementPtr > ()), std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[6].location + yystack_[0].location); }
#line 1416 "parser_rules.tab.cc"
    break;

  case 53: // stmt: TOK_BREAK TOK_SMCLN
#line 384 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_break_stmt(yystack_[1].location + yystack_[0].location); }
#line 1422 "parser_rules.tab.cc"
    break;

  case 54: // stmt: TOK_CONTINUE TOK_SMCLN
#line 386 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_continue_stmt(yystack_[1].location + yystack_[0].location); }
#line 1428 "parser_rules.tab.cc"
    break;

  case 55: // stmt: block
#line 387 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = yystack_[0].value.as < ast::StatementPtr > (); }
#line 1434 "parser_rules.tab.cc"
    break;

  case 56: // stmt: expr TOK_SMCLN
#line 389 "parser_rules.y"
    {
      // Expression statement: wrap as statement if you model it, else drop
      extern ast::StatementPtr mk_expr_stmt(ast::ExprPtr, const lex::Loc&);
      yylhs.value.as < ast::StatementPtr > () = mk_expr_stmt(std::move(yystack_[1].value.as < ast::ExprPtr > ()), yystack_[1].location + yystack_[0].location);
    }
#line 1444 "parser_rules.tab.cc"
    break;

  case 57: // else_opt: %empty
#line 397 "parser_rules.y"
                  { yylhs.value.as < ast::StatementPtr > () = nullptr; }
#line 1450 "parser_rules.tab.cc"
    break;

  case 58: // else_opt: TOK_ELSE stmt
#line 398 "parser_rules.y"
                  { yylhs.value.as < ast::StatementPtr > () = std::move(yystack_[0].value.as < ast::StatementPtr > ()); }
#line 1456 "parser_rules.tab.cc"
    break;

  case 59: // expr_opt: %empty
#line 402 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = nullptr; }
#line 1462 "parser_rules.tab.cc"
    break;

  case 60: // expr_opt: expr
#line 403 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1468 "parser_rules.tab.cc"
    break;

  case 61: // var_decl: type_spec init_declarator_list TOK_SMCLN
#line 409 "parser_rules.y"
    {
      // Fold a list of decls into multiple var_decl statements wrapped in a block
      // If you prefer a single multi-decl node, change this.
      std::vector<ast::StatementPtr> decls = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ());
      yylhs.value.as < ast::StatementPtr > () = mk_block_stmt(std::move(decls), yystack_[2].location + yystack_[0].location);
    }
#line 1479 "parser_rules.tab.cc"
    break;

  case 62: // init_declarator_list: init_declarator
#line 420 "parser_rules.y"
    { std::vector<ast::StatementPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(v); }
#line 1485 "parser_rules.tab.cc"
    break;

  case 63: // init_declarator_list: init_declarator_list TOK_COMMA init_declarator
#line 422 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1491 "parser_rules.tab.cc"
    break;

  case 64: // init_declarator: ident
#line 427 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_var_decl($(-1) /* type_spec from left context — see note below */, yystack_[0].value.as < Str > (), nullptr, yystack_[0].location); }
#line 1497 "parser_rules.tab.cc"
    break;

  case 65: // init_declarator: ident TOK_ASSIGN assign
#line 429 "parser_rules.y"
    { yylhs.value.as < ast::StatementPtr > () = mk_var_decl($(-3) /* type_spec */, yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1503 "parser_rules.tab.cc"
    break;

  case 66: // expr: assign
#line 442 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1509 "parser_rules.tab.cc"
    break;

  case 67: // assign: cond
#line 446 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1515 "parser_rules.tab.cc"
    break;

  case 68: // assign: postfix TOK_ASSIGN assign
#line 447 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_assign_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Simple*/0, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1521 "parser_rules.tab.cc"
    break;

  case 69: // assign: postfix TOK_PLUS_ASSIGN assign
#line 448 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_assign_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Add*/1,    std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1527 "parser_rules.tab.cc"
    break;

  case 70: // assign: postfix TOK_MIN_ASSIGN assign
#line 449 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_assign_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Sub*/2,    std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1533 "parser_rules.tab.cc"
    break;

  case 71: // assign: postfix TOK_MUL_ASSIGN assign
#line 450 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_assign_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Mul*/3,    std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1539 "parser_rules.tab.cc"
    break;

  case 72: // assign: postfix TOK_DIV_ASSIGN assign
#line 451 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_assign_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Div*/4,    std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1545 "parser_rules.tab.cc"
    break;

  case 73: // cond: logic_or
#line 455 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1551 "parser_rules.tab.cc"
    break;

  case 74: // cond: logic_or TOK_QUESTION expr TOK_COLON cond
#line 457 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_cond_expr(std::move(yystack_[4].value.as < ast::ExprPtr > ()), std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[4].location + yystack_[0].location); }
#line 1557 "parser_rules.tab.cc"
    break;

  case 75: // logic_or: logic_and
#line 461 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1563 "parser_rules.tab.cc"
    break;

  case 76: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 463 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*LOr*/10, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1569 "parser_rules.tab.cc"
    break;

  case 77: // logic_and: equality
#line 467 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1575 "parser_rules.tab.cc"
    break;

  case 78: // logic_and: logic_and TOK_BOOL_AND equality
#line 469 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*LAnd*/11, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1581 "parser_rules.tab.cc"
    break;

  case 79: // equality: relational
#line 473 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1587 "parser_rules.tab.cc"
    break;

  case 80: // equality: equality TOK_EQUAL relational
#line 475 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Eq*/20, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1593 "parser_rules.tab.cc"
    break;

  case 81: // equality: equality TOK_NEQUAL relational
#line 477 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Ne*/21, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1599 "parser_rules.tab.cc"
    break;

  case 82: // relational: additive
#line 481 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1605 "parser_rules.tab.cc"
    break;

  case 83: // relational: relational TOK_LESS additive
#line 482 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Lt*/30, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1611 "parser_rules.tab.cc"
    break;

  case 84: // relational: relational TOK_LEQ additive
#line 483 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Le*/31, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1617 "parser_rules.tab.cc"
    break;

  case 85: // relational: relational TOK_GREATER additive
#line 484 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Gt*/32, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1623 "parser_rules.tab.cc"
    break;

  case 86: // relational: relational TOK_GEQ additive
#line 485 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Ge*/33, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1629 "parser_rules.tab.cc"
    break;

  case 87: // additive: multiplicative
#line 489 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1635 "parser_rules.tab.cc"
    break;

  case 88: // additive: additive TOK_PLUS multiplicative
#line 490 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Add*/40, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1641 "parser_rules.tab.cc"
    break;

  case 89: // additive: additive TOK_MINUS multiplicative
#line 491 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Sub*/41, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1647 "parser_rules.tab.cc"
    break;

  case 90: // multiplicative: unary
#line 495 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1653 "parser_rules.tab.cc"
    break;

  case 91: // multiplicative: multiplicative TOK_STAR unary
#line 496 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Mul*/50, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1659 "parser_rules.tab.cc"
    break;

  case 92: // multiplicative: multiplicative TOK_SLASH unary
#line 497 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Div*/51, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1665 "parser_rules.tab.cc"
    break;

  case 93: // multiplicative: multiplicative TOK_MODULO unary
#line 498 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = mk_binary_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), /*Mod*/52, std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1671 "parser_rules.tab.cc"
    break;

  case 94: // unary: TOK_NEG unary
#line 502 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_unary_expr_neg(std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[1].location + yystack_[0].location); }
#line 1677 "parser_rules.tab.cc"
    break;

  case 95: // unary: TOK_NEGATION unary
#line 503 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_unary_expr_not(std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[1].location + yystack_[0].location); }
#line 1683 "parser_rules.tab.cc"
    break;

  case 96: // unary: TOK_INC unary
#line 504 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_prefix_incdec_expr(std::move(yystack_[0].value.as < ast::ExprPtr > ()), true,  yystack_[1].location + yystack_[0].location); }
#line 1689 "parser_rules.tab.cc"
    break;

  case 97: // unary: TOK_DEC unary
#line 505 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = mk_prefix_incdec_expr(std::move(yystack_[0].value.as < ast::ExprPtr > ()), false, yystack_[1].location + yystack_[0].location); }
#line 1695 "parser_rules.tab.cc"
    break;

  case 98: // unary: postfix
#line 506 "parser_rules.y"
                                        { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1701 "parser_rules.tab.cc"
    break;

  case 99: // postfix: primary
#line 510 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1707 "parser_rules.tab.cc"
    break;

  case 100: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 512 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_call_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()), yystack_[3].location + yystack_[0].location); }
#line 1713 "parser_rules.tab.cc"
    break;

  case 101: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 514 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_index_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::ExprPtr > ()), yystack_[3].location + yystack_[0].location); }
#line 1719 "parser_rules.tab.cc"
    break;

  case 102: // postfix: postfix TOK_DOT ident
#line 516 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_field_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[0].value.as < Str > (), yystack_[2].location + yystack_[0].location); }
#line 1725 "parser_rules.tab.cc"
    break;

  case 103: // postfix: postfix TOK_INC
#line 518 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_postfix_incdec_expr(std::move(yystack_[1].value.as < ast::ExprPtr > ()), true,  yystack_[1].location + yystack_[0].location); }
#line 1731 "parser_rules.tab.cc"
    break;

  case 104: // postfix: postfix TOK_DEC
#line 520 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_postfix_incdec_expr(std::move(yystack_[1].value.as < ast::ExprPtr > ()), false, yystack_[1].location + yystack_[0].location); }
#line 1737 "parser_rules.tab.cc"
    break;

  case 105: // arg_list_opt: %empty
#line 524 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::vector<ast::ExprPtr>{}; }
#line 1743 "parser_rules.tab.cc"
    break;

  case 106: // arg_list_opt: arg_list
#line 525 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ExprPtr> > () = yystack_[0].value.as < std::vector<ast::ExprPtr> > (); }
#line 1749 "parser_rules.tab.cc"
    break;

  case 107: // arg_list: expr
#line 529 "parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(v); }
#line 1755 "parser_rules.tab.cc"
    break;

  case 108: // arg_list: arg_list TOK_COMMA expr
#line 530 "parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ExprPtr> > ()); }
#line 1761 "parser_rules.tab.cc"
    break;

  case 109: // arg_list: arg_list TOK_COMMA
#line 531 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()); }
#line 1767 "parser_rules.tab.cc"
    break;

  case 110: // primary: ident
#line 536 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1773 "parser_rules.tab.cc"
    break;

  case 111: // primary: TOK_INT_LITERAL
#line 538 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_int_literal_expr(yystack_[0].value.as < kl_int > (), yystack_[0].location); }
#line 1779 "parser_rules.tab.cc"
    break;

  case 112: // primary: TOK_FLOAT_LITERAL
#line 540 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_float_literal_expr(yystack_[0].value.as < kl_double > (), yystack_[0].location); }
#line 1785 "parser_rules.tab.cc"
    break;

  case 113: // primary: TOK_STRING_LITERAL
#line 542 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_str_literal_expr(yystack_[0].value.as < kl_string > (), yystack_[0].location); }
#line 1791 "parser_rules.tab.cc"
    break;

  case 114: // primary: TOK_BOOL_LITERAL
#line 544 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_bool_literal_expr(yystack_[0].value.as < kl_bool > (), yystack_[0].location); }
#line 1797 "parser_rules.tab.cc"
    break;

  case 115: // primary: TOK_LPAR expr TOK_RPAR
#line 546 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[1].value.as < ast::ExprPtr > ()); yylhs.value.as < ast::ExprPtr > ()->loc = yystack_[2].location + yystack_[0].location; }
#line 1803 "parser_rules.tab.cc"
    break;

  case 116: // primary: struct_lit
#line 547 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1809 "parser_rules.tab.cc"
    break;

  case 117: // struct_lit: type_path TOK_LCBRA field_inits_opt TOK_RCBRA
#line 552 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = mk_struct_literal_expr(std::move(yystack_[3].value.as < ast::PathType > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr> > ()), yystack_[3].location + yystack_[0].location); }
#line 1815 "parser_rules.tab.cc"
    break;

  case 118: // field_inits_opt: %empty
#line 557 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr> > () = std::vector<ast::FieldInitExpr>{}; }
#line 1821 "parser_rules.tab.cc"
    break;

  case 119: // field_inits_opt: field_inits
#line 558 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr> > () = yystack_[0].value.as < std::vector<ast::FieldInitExpr> > (); }
#line 1827 "parser_rules.tab.cc"
    break;

  case 120: // field_inits: field_init
#line 563 "parser_rules.y"
    { std::vector<ast::FieldInitExpr> v; v.push_back(std::move(yystack_[0].value.as < ast::FieldInitExpr > ())); yylhs.value.as < std::vector<ast::FieldInitExpr> > () = std::move(v); }
#line 1833 "parser_rules.tab.cc"
    break;

  case 121: // field_inits: field_inits TOK_COMMA field_init
#line 565 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::FieldInitExpr> > ().push_back(std::move(yystack_[0].value.as < ast::FieldInitExpr > ())); yylhs.value.as < std::vector<ast::FieldInitExpr> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr> > ()); }
#line 1839 "parser_rules.tab.cc"
    break;

  case 122: // field_inits: field_inits TOK_COMMA
#line 567 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr> > ()); }
#line 1845 "parser_rules.tab.cc"
    break;

  case 123: // field_init: ident TOK_COLON expr
#line 572 "parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr > () = mk_field_init(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), yystack_[2].location + yystack_[0].location); }
#line 1851 "parser_rules.tab.cc"
    break;


#line 1855 "parser_rules.tab.cc"

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
        std::string msg = YY_("syntax error");
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

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -108;

  const signed char parser::yytable_ninf_ = -44;

  const short
  parser::yypact_[] =
  {
      -8,    -3,    19,  -108,  -108,   -29,  -108,  -108,    12,  -108,
      -3,    -3,  -108,     5,  -108,    50,  -108,  -108,   108,    -3,
    -108,    60,    60,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,   231,  -108,  -108,    60,  -108,    49,  -108,  -108,
      53,  -108,    66,    48,    81,    67,    29,  -108,    70,  -108,
     231,   231,  -108,   134,    60,  -108,  -108,    68,    92,  -108,
      60,    93,    40,  -108,  -108,  -108,  -108,   134,   134,   134,
     134,   134,    44,  -108,  -108,  -108,   -35,    77,    21,    52,
      51,   -12,  -108,   -17,  -108,  -108,  -108,    94,   231,  -108,
    -108,   106,  -108,  -108,    97,  -108,  -108,  -108,    60,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,    60,  -108,  -108,   134,   134,
     134,   134,   134,   231,   -30,  -108,  -108,   101,   109,   107,
    -108,   112,    77,    21,    52,    52,    51,    51,    51,    51,
     -12,   -12,  -108,  -108,  -108,  -108,   120,   117,   121,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,   134,
    -108,    60,   134,  -108,   134,  -108,   171,  -108,  -108,  -108,
    -108,   125,   126,   207,   134,   128,   129,  -108,    44,  -108,
    -108,  -108,   130,   134,   134,   156,   131,  -108,  -108,  -108,
    -108,   138,   139,   161,  -108,   207,   207,   134,   189,  -108,
     162,   207,  -108,   157,  -108,  -108
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    11,     0,     9,     1,    12,     4,
       0,     0,     6,    18,    10,     0,    19,    13,    17,     0,
       7,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      43,    42,     0,    14,    15,     0,    30,    31,    40,    16,
       0,    44,     0,     0,     0,    64,     0,    62,     0,     8,
      22,     0,    32,     0,     0,    61,    41,     0,    23,    24,
       0,     0,    44,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,   110,    65,    67,    73,    75,    77,    79,
      82,    87,    90,    98,    99,   116,    63,     0,    26,    27,
      29,     0,    66,    95,    98,    94,    96,    97,   118,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   103,   104,     0,     0,
       0,     0,     0,     0,     0,    25,   115,     0,     0,   119,
     120,     0,    76,    78,    80,    81,    83,    84,    85,    86,
      88,    89,    91,    92,    93,   107,     0,   106,     0,   102,
      68,    69,    70,    71,    72,    28,    46,    21,    20,     0,
     117,   122,     0,   100,   109,   101,     0,   123,   121,    74,
     108,     0,     0,     0,    59,     0,     0,    45,    31,    55,
      47,    48,     0,     0,     0,     0,     0,    60,    53,    54,
      56,     0,     0,     0,    49,     0,     0,     0,    57,    51,
       0,     0,    50,     0,    58,    52
  };

  const short
  parser::yypgoto_[] =
  {
    -108,  -108,  -108,  -108,  -108,   194,    -7,  -108,  -108,  -108,
    -108,  -108,  -108,   119,  -108,  -108,   -23,  -108,   -18,   165,
     -20,    90,  -108,  -107,  -108,  -108,   197,  -108,   176,   -63,
     -47,    69,  -108,   132,   140,    10,    45,     7,   -27,   -48,
    -108,  -108,  -108,  -108,  -108,  -108,    72
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    12,     5,     6,    13,    17,    18,
      33,    57,    58,    59,   124,    34,    35,    36,    72,    38,
      73,   179,   166,   180,   202,   186,   181,    46,    47,   182,
      92,    75,    76,    77,    78,    79,    80,    81,    82,    83,
     146,   147,    84,    85,   128,   129,   130
  };

  const short
  parser::yytable_[] =
  {
      37,    42,    43,    14,    91,    -2,    74,   156,    99,    44,
     157,     9,    40,    10,    37,    45,   113,     1,   114,     7,
      94,    94,    94,    94,     4,   115,   100,    60,    61,    16,
     116,   117,    37,    37,    45,    11,   131,   110,   111,   112,
      89,    93,    95,    96,    97,   118,   119,   120,   121,   122,
     145,   148,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    60,   185,   -43,    54,    55,
      37,   150,   151,   152,   153,   154,    19,   -43,   127,   102,
     103,    98,   -43,   142,   143,   144,    48,    41,   198,   199,
      20,    48,    10,    49,   204,   149,   167,    30,    31,    50,
     155,   170,    87,   108,   109,    37,   104,   105,   106,   107,
      51,   187,   134,   135,    94,   140,   141,    52,    21,    22,
     191,   192,    23,    24,    25,    26,    27,    28,    29,    53,
     113,    88,   114,    90,   200,    30,    31,   101,   123,   115,
     126,   127,   159,    32,   116,   117,   161,   160,   178,   136,
     137,   138,   139,   162,   163,   178,   164,   165,   183,   184,
     193,    62,    31,    63,    64,    65,    66,    67,   188,   189,
     190,   194,   195,   196,   171,   172,   173,   178,   178,    68,
      69,    70,    71,   178,   174,    23,    24,    25,    26,    27,
      28,    29,   175,   176,   197,   201,   203,   205,    62,    31,
      63,    64,    65,    66,    67,    15,    32,   125,   156,   177,
     171,   172,   173,    56,   158,    39,    68,    69,    70,    71,
     174,    23,    24,    25,    26,    27,    28,    29,   175,   176,
      86,   169,   132,   168,    62,    31,    63,    64,    65,    66,
      67,   133,    32,     0,   156,    23,    24,    25,    26,    27,
      28,    29,    68,    69,    70,    71,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,    32
  };

  const short
  parser::yycheck_[] =
  {
      18,    21,    22,    10,    67,     0,    53,    37,    43,    32,
      40,    40,    19,    42,    32,    35,    33,    25,    35,     0,
      68,    69,    70,    71,    27,    42,    61,    50,    51,    24,
      47,    48,    50,    51,    54,    23,    99,    49,    50,    51,
      60,    68,    69,    70,    71,    62,    63,    64,    65,    66,
     113,   114,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    88,   173,    27,    39,    40,
      88,   118,   119,   120,   121,   122,    26,    37,    98,    58,
      59,    37,    42,   110,   111,   112,    42,    27,   195,   196,
      40,    42,    42,    40,   201,   115,   159,    27,    28,    33,
     123,   164,    34,    52,    53,   123,    54,    55,    56,    57,
      62,   174,   102,   103,   162,   108,   109,    36,    10,    11,
     183,   184,    14,    15,    16,    17,    18,    19,    20,    62,
      33,    39,    35,    40,   197,    27,    28,    60,    44,    42,
      34,   161,    41,    35,    47,    48,    39,    38,   166,   104,
     105,   106,   107,    41,    34,   173,    39,    36,    33,    33,
       4,    27,    28,    29,    30,    31,    32,    33,    40,    40,
      40,    40,    34,    34,     3,     4,     5,   195,   196,    45,
      46,    47,    48,   201,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    33,     6,    34,    40,    27,    28,
      29,    30,    31,    32,    33,    11,    35,    88,    37,    38,
       3,     4,     5,    48,   124,    18,    45,    46,    47,    48,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      54,   162,   100,   161,    27,    28,    29,    30,    31,    32,
      33,   101,    35,    -1,    37,    14,    15,    16,    17,    18,
      19,    20,    45,    46,    47,    48,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35
  };

  const signed char
  parser::yystos_[] =
  {
       0,    25,    71,    72,    27,    75,    76,     0,    73,    40,
      42,    23,    74,    77,    76,    75,    24,    78,    79,    26,
      40,    10,    11,    14,    15,    16,    17,    18,    19,    20,
      27,    28,    35,    80,    85,    86,    87,    88,    89,    96,
      76,    27,    90,    90,    86,    90,    97,    98,    42,    40,
      33,    62,    36,    62,    39,    40,    89,    81,    82,    83,
      86,    86,    27,    29,    30,    31,    32,    33,    45,    46,
      47,    48,    88,    90,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   112,   113,    98,    34,    39,    90,
      40,    99,   100,   108,   109,   108,   108,   108,    37,    43,
      61,    60,    58,    59,    54,    55,    56,    57,    52,    53,
      49,    50,    51,    33,    35,    42,    47,    48,    62,    63,
      64,    65,    66,    44,    84,    83,    34,    90,   114,   115,
     116,    99,   103,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   108,    99,   110,   111,    99,    90,
     100,   100,   100,   100,   100,    86,    37,    40,    91,    41,
      38,    39,    41,    34,    39,    36,    92,    99,   116,   101,
      99,     3,     4,     5,    13,    21,    22,    38,    88,    91,
      93,    96,    99,    33,    33,    93,    95,    99,    40,    40,
      40,    99,    99,     4,    40,    34,    34,    33,    93,    93,
      99,     6,    94,    34,    93,    40
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    83,    84,    85,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    90,    91,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    95,
      95,    96,    97,    97,    98,    98,    99,   100,   100,   100,
     100,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   105,   105,   105,   105,   105,   106,   106,   106,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   109,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   113,   114,   114,
     115,   115,   115,   116
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     1,
       3,     1,     0,     2,     2,     2,     2,     1,     0,     1,
       7,     7,     0,     1,     1,     3,     2,     2,     2,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     0,     2,     1,     3,
       6,     5,     7,     2,     2,     1,     2,     0,     2,     0,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     1,     5,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     2,     2,     2,     2,     1,     1,
       4,     4,     3,     2,     2,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     3,     1,     4,     0,     1,
       1,     3,     2,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_TRAIT", "TOK_ENUM", "TOK_FN",
  "TOK_TYPE", "TOK_LET", "TOK_RETURN", "TOK_INT", "TOK_BIGINT",
  "TOK_MAGICINT", "TOK_DOUBLE", "TOK_BOOL", "TOK_VOID", "TOK_STRING",
  "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT", "TOK_EXPORT", "TOK_PACKAGE",
  "TOK_AS", "TOK_IDENTIFIER", "TOK_TYPE_NAME", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA",
  "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON", "TOK_DOT",
  "TOK_QUESTION", "TOK_ARROW", "TOK_NEGATION", "TOK_NEG", "TOK_INC",
  "TOK_DEC", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit",
  "opt_package", "import_list", "import_decl", "names_separated_by_dots",
  "name", "decl_list", "decl", "maybe_export", "fn_decl", "param_list_opt",
  "param_list", "param", "ret_type", "type_alias", "type_spec",
  "builtin_type", "type_path", "type_atom", "ident", "block", "stmt_list",
  "stmt", "else_opt", "expr_opt", "var_decl", "init_declarator_list",
  "init_declarator", "expr", "assign", "cond", "logic_or", "logic_and",
  "equality", "relational", "additive", "multiplicative", "unary",
  "postfix", "arg_list_opt", "arg_list", "primary", "struct_lit",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   198,   198,   206,   207,   215,   216,   224,   229,   236,
     238,   243,   250,   251,   256,   257,   258,   259,   263,   264,
     270,   274,   282,   283,   287,   289,   291,   296,   305,   309,
     319,   320,   321,   326,   327,   328,   329,   330,   331,   332,
     336,   342,   351,   352,   356,   362,   368,   369,   374,   375,
     377,   379,   381,   383,   385,   387,   388,   397,   398,   402,
     403,   408,   419,   421,   426,   428,   442,   446,   447,   448,
     449,   450,   451,   455,   456,   461,   462,   467,   468,   473,
     474,   476,   481,   482,   483,   484,   485,   489,   490,   491,
     495,   496,   497,   498,   502,   503,   504,   505,   506,   510,
     511,   513,   515,   517,   519,   524,   525,   529,   530,   531,
     535,   537,   539,   541,   543,   545,   547,   551,   557,   558,
     562,   564,   566,   571
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


#line 4 "parser_rules.y"
} // yy
#line 2334 "parser_rules.tab.cc"

#line 575 "parser_rules.y"


/* Optionally: yyerror, yylex wrappers, etc. */
