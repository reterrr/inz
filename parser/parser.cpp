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
#line 64 "parser/parser_rules.y"

  #include "../lexer/lexer.hpp"   // Scanner definition
  #include "../ast/ast.hpp"       // AST factory class declarations (mk_*)
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.end.line << ':' << loc.end.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    int rc = scanner.yylex(); // advance; fills current_token_

    const lex::Token& t = scanner.getCurrentToken();
    const lex::Loc   L  = t.loc_;

    using T = lex::Type;
    switch (t.type_) {
      /* Identifiers / literals (payloads) */
      case T::TOK_IDENTIFIER:     return yy::parser::make_TOK_IDENTIFIER(t.u_.sym, L);
      case T::TOK_INT_LITERAL:    return yy::parser::make_TOK_INT_LITERAL((kl_int)t.u_.i64, L);
      case T::TOK_FLOAT_LITERAL:  return yy::parser::make_TOK_FLOAT_LITERAL((kl_float)t.u_.f64, L);
      case T::TOK_STRING_LITERAL: return yy::parser::make_TOK_STRING_LITERAL(t.u_.sym, L);

      /* Keywords */
      case T::TOK_IF:       return yy::parser::make_TOK_IF(L);
      case T::TOK_ELSE:     return yy::parser::make_TOK_ELSE(L);
      case T::TOK_WHILE:    return yy::parser::make_TOK_WHILE(L);
      case T::TOK_DO:       return yy::parser::make_TOK_DO(L);
      case T::TOK_FN:       return yy::parser::make_TOK_FN(L);
      case T::TOK_RETURN:   return yy::parser::make_TOK_RETURN(L);
      case T::TOK_LET:      return yy::parser::make_TOK_LET(L);
      case T::TOK_STRUCT:   return yy::parser::make_TOK_STRUCT(L);
      case T::TOK_TRAIT:    return yy::parser::make_TOK_TRAIT(L);
      case T::TOK_ENUM:     return yy::parser::make_TOK_ENUM(L);
      case T::TOK_TYPE:     return yy::parser::make_TOK_TYPE(L);
      case T::TOK_IMPORT:   return yy::parser::make_TOK_IMPORT(L);
      case T::TOK_EXPORT:   return yy::parser::make_TOK_EXPORT(L);
      case T::TOK_PACKAGE:  return yy::parser::make_TOK_PACKAGE(L);
      case T::TOK_AS:       return yy::parser::make_TOK_AS(L);
      case T::TOK_PUB:      return yy::parser::make_TOK_PUB(L);
      case T::TOK_MUT:      return yy::parser::make_TOK_MUT(L);

      /* Builtin type keywords */
      case T::TOK_INT:      return yy::parser::make_TOK_INT(L);
      case T::TOK_BIGINT:   return yy::parser::make_TOK_BIGINT(L);
      case T::TOK_MAGICINT: return yy::parser::make_TOK_MAGICINT(L);
      case T::TOK_DOUBLE:   return yy::parser::make_TOK_DOUBLE(L);
      case T::TOK_BOOL:     return yy::parser::make_TOK_BOOL(L);
      case T::TOK_VOID:     return yy::parser::make_TOK_VOID(L);
      case T::TOK_STRING:   return yy::parser::make_TOK_STRING(L);

      /* Delimiters / punct */
      case T::TOK_LPAR:     return yy::parser::make_TOK_LPAR(L);
      case T::TOK_RPAR:     return yy::parser::make_TOK_RPAR(L);
      case T::TOK_LBRACK:   return yy::parser::make_TOK_LBRACK(L);
      case T::TOK_RBRACK:   return yy::parser::make_TOK_RBRACK(L);
      case T::TOK_LCBRA:    return yy::parser::make_TOK_LCBRA(L);
      case T::TOK_RCBRA:    return yy::parser::make_TOK_RCBRA(L);
      case T::TOK_COMMA:    return yy::parser::make_TOK_COMMA(L);
      case T::TOK_SMCLN:    return yy::parser::make_TOK_SMCLN(L);
      case T::TOK_COLON:    return yy::parser::make_TOK_COLON(L);
      case T::TOK_DOT:      return yy::parser::make_TOK_DOT(L);
      case T::TOK_QUESTION: return yy::parser::make_TOK_QUESTION(L);
      case T::TOK_ARROW:    return yy::parser::make_TOK_ARROW(L);

      /* Operators */
      case T::TOK_NEGATION:    return yy::parser::make_TOK_NEGATION(L);
      case T::TOK_NEG:         return yy::parser::make_TOK_NEG(L);
      case T::TOK_INC:         return yy::parser::make_TOK_INC(L);
      case T::TOK_DEC:         return yy::parser::make_TOK_DEC(L);
      case T::TOK_STAR:        return yy::parser::make_TOK_STAR(L);
      case T::TOK_SLASH:       return yy::parser::make_TOK_SLASH(L);
      case T::TOK_MODULO:      return yy::parser::make_TOK_MODULO(L);
      case T::TOK_PLUS:        return yy::parser::make_TOK_PLUS(L);
      case T::TOK_MINUS:       return yy::parser::make_TOK_MINUS(L);
      case T::TOK_LESS:        return yy::parser::make_TOK_LESS(L);
      case T::TOK_LEQ:         return yy::parser::make_TOK_LEQ(L);
      case T::TOK_GREATER:     return yy::parser::make_TOK_GREATER(L);
      case T::TOK_GEQ:         return yy::parser::make_TOK_GEQ(L);
      case T::TOK_EQUAL:       return yy::parser::make_TOK_EQUAL(L);
      case T::TOK_NEQUAL:      return yy::parser::make_TOK_NEQUAL(L);
      case T::TOK_BOOL_AND:    return yy::parser::make_TOK_BOOL_AND(L);
      case T::TOK_BOOL_OR:     return yy::parser::make_TOK_BOOL_OR(L);
      case T::TOK_ASSIGN:      return yy::parser::make_TOK_ASSIGN(L);
      case T::TOK_PLUS_ASSIGN: return yy::parser::make_TOK_PLUS_ASSIGN(L);
      case T::TOK_MIN_ASSIGN:  return yy::parser::make_TOK_MIN_ASSIGN(L);
      case T::TOK_MUL_ASSIGN:  return yy::parser::make_TOK_MUL_ASSIGN(L);
      case T::TOK_DIV_ASSIGN:  return yy::parser::make_TOK_DIV_ASSIGN(L);

      /* EOF / unknown */
      case T::TOK_END:         return yy::parser::make_YYEOF(L);
      default:                 return yy::parser::make_YYUNDEF(L);
    }
  }

  static inline lex::Loc combine(const lex::Loc& a, const lex::Loc& b) {
    lex::Loc L;
    L.begin = a.begin;
    L.end   = b.end;

    return L;
   }

#line 150 "parser/parser.cpp"


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

#line 4 "parser/parser_rules.y"
namespace yy {
#line 243 "parser/parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner& scanner_yyarg, ast::AST& ast_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      scanner (scanner_yyarg),
      ast (ast_yyarg)
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
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.YY_MOVE_OR_COPY< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type: // builtin_type
        value.YY_MOVE_OR_COPY< ast::BuiltinType * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_top_decl: // top_decl
        value.YY_MOVE_OR_COPY< ast::DeclPtr > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< ast::ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.YY_MOVE_OR_COPY< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.YY_MOVE_OR_COPY< ast::FieldInitPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fixed_array_type: // fixed_array_type
        value.YY_MOVE_OR_COPY< ast::FixedArrayType* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.YY_MOVE_OR_COPY< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.YY_MOVE_OR_COPY< ast::ModulePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.YY_MOVE_OR_COPY< ast::ObjLiteralExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ast::ParamDeclPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.YY_MOVE_OR_COPY< ast::PathTypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.YY_MOVE_OR_COPY< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_with_spec: // type_with_spec
      case symbol_kind::S_type_spec: // type_spec
        value.YY_MOVE_OR_COPY< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.YY_MOVE_OR_COPY< ast::TypeRegion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.YY_MOVE_OR_COPY< ast::TypeSpecifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.YY_MOVE_OR_COPY< ast::VarDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars_decl: // vars_decl
        value.YY_MOVE_OR_COPY< ast::VarsDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars_decl_stmt: // vars_decl_stmt
        value.YY_MOVE_OR_COPY< ast::VarsDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_maybe_export: // maybe_export
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.YY_MOVE_OR_COPY< kl_bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.YY_MOVE_OR_COPY< kl_float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.YY_MOVE_OR_COPY< kl_int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_vars_group: // vars_group
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::DeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldInitPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ParamDeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
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
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::BuiltinType * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_top_decl: // top_decl
        value.move< ast::DeclPtr > (YY_MOVE (that.value));
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
        value.move< ast::ExprPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fixed_array_type: // fixed_array_type
        value.move< ast::FixedArrayType* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::ModulePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::ObjLiteralExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDeclPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathTypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_with_spec: // type_with_spec
      case symbol_kind::S_type_spec: // type_spec
        value.move< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.move< ast::TypeRegion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.move< ast::TypeSpecifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars_decl: // vars_decl
        value.move< ast::VarsDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars_decl_stmt: // vars_decl_stmt
        value.move< ast::VarsDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_maybe_export: // maybe_export
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_vars_group: // vars_group
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::DeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
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
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.copy< Str > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type: // builtin_type
        value.copy< ast::BuiltinType * > (that.value);
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_top_decl: // top_decl
        value.copy< ast::DeclPtr > (that.value);
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
        value.copy< ast::ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitPtr > (that.value);
        break;

      case symbol_kind::S_fixed_array_type: // fixed_array_type
        value.copy< ast::FixedArrayType* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.copy< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.copy< ast::ModulePtr > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.copy< ast::ObjLiteralExpr* > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDeclPtr > (that.value);
        break;

      case symbol_kind::S_type_path: // type_path
        value.copy< ast::PathTypePtr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.copy< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_with_spec: // type_with_spec
      case symbol_kind::S_type_spec: // type_spec
        value.copy< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.copy< ast::TypeRegion > (that.value);
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.copy< ast::TypeSpecifier > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.copy< ast::VarDeclStatement* > (that.value);
        break;

      case symbol_kind::S_vars_decl: // vars_decl
        value.copy< ast::VarsDecl* > (that.value);
        break;

      case symbol_kind::S_vars_decl_stmt: // vars_decl_stmt
        value.copy< ast::VarsDeclStatement* > (that.value);
        break;

      case symbol_kind::S_maybe_export: // maybe_export
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.copy< kl_bool > (that.value);
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.copy< kl_float > (that.value);
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.copy< kl_int > (that.value);
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_vars_group: // vars_group
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< std::vector<ast::DeclPtr> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.copy< std::vector<ast::FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitPtr> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDeclPtr> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
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
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        value.move< Str > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::BuiltinType * > (that.value);
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_top_decl: // top_decl
        value.move< ast::DeclPtr > (that.value);
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
        value.move< ast::ExprPtr > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitPtr > (that.value);
        break;

      case symbol_kind::S_fixed_array_type: // fixed_array_type
        value.move< ast::FixedArrayType* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::ModulePtr > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::ObjLiteralExpr* > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDeclPtr > (that.value);
        break;

      case symbol_kind::S_type_path: // type_path
        value.move< ast::PathTypePtr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_with_spec: // type_with_spec
      case symbol_kind::S_type_spec: // type_spec
        value.move< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.move< ast::TypeRegion > (that.value);
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.move< ast::TypeSpecifier > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (that.value);
        break;

      case symbol_kind::S_vars_decl: // vars_decl
        value.move< ast::VarsDecl* > (that.value);
        break;

      case symbol_kind::S_vars_decl_stmt: // vars_decl_stmt
        value.move< ast::VarsDeclStatement* > (that.value);
        break;

      case symbol_kind::S_maybe_export: // maybe_export
        value.move< int > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        value.move< kl_bool > (that.value);
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        value.move< kl_float > (that.value);
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        value.move< kl_int > (that.value);
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_vars_group: // vars_group
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::DeclPtr> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitPtr> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDeclPtr> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
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
      case symbol_kind::S_TOK_TYPE_NAME: // TOK_TYPE_NAME
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Str > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< ast::BlockStatement* > ();
        break;

      case symbol_kind::S_builtin_type: // builtin_type
        yylhs.value.emplace< ast::BuiltinType * > ();
        break;

      case symbol_kind::S_decl: // decl
      case symbol_kind::S_top_decl: // top_decl
        yylhs.value.emplace< ast::DeclPtr > ();
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
        yylhs.value.emplace< ast::ExprPtr > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        yylhs.value.emplace< ast::FieldDecl* > ();
        break;

      case symbol_kind::S_field_init: // field_init
        yylhs.value.emplace< ast::FieldInitPtr > ();
        break;

      case symbol_kind::S_fixed_array_type: // fixed_array_type
        yylhs.value.emplace< ast::FixedArrayType* > ();
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        yylhs.value.emplace< ast::FunctionDecl* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        yylhs.value.emplace< ast::ModulePtr > ();
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        yylhs.value.emplace< ast::ObjLiteralExpr* > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ast::ParamDeclPtr > ();
        break;

      case symbol_kind::S_type_path: // type_path
        yylhs.value.emplace< ast::PathTypePtr > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< ast::StatementPtr > ();
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        yylhs.value.emplace< ast::StructDecl* > ();
        break;

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_with_spec: // type_with_spec
      case symbol_kind::S_type_spec: // type_spec
        yylhs.value.emplace< ast::TypePtr > ();
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        yylhs.value.emplace< ast::TypeRegion > ();
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        yylhs.value.emplace< ast::TypeSpecifier > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< ast::VarDecl* > ();
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        yylhs.value.emplace< ast::VarDeclStatement* > ();
        break;

      case symbol_kind::S_vars_decl: // vars_decl
        yylhs.value.emplace< ast::VarsDecl* > ();
        break;

      case symbol_kind::S_vars_decl_stmt: // vars_decl_stmt
        yylhs.value.emplace< ast::VarsDeclStatement* > ();
        break;

      case symbol_kind::S_maybe_export: // maybe_export
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
        yylhs.value.emplace< kl_bool > ();
        break;

      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
        yylhs.value.emplace< kl_float > ();
        break;

      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
        yylhs.value.emplace< kl_int > ();
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_vars_group: // vars_group
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< std::vector<ast::DeclPtr> > ();
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        yylhs.value.emplace< std::vector<ast::ExprPtr> > ();
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        yylhs.value.emplace< std::vector<ast::FieldDecl*> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        yylhs.value.emplace< std::vector<ast::FieldInitPtr> > ();
        break;

      case symbol_kind::S_import_list: // import_list
        yylhs.value.emplace< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<ast::ParamDeclPtr> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
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
#line 275 "parser/parser_rules.y"
    {
        auto* m = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::DeclPtr> > ()), combine(yystack_[2].location, yystack_[0].location));
        ast.project_add_module(m);
        yylhs.value.as < ast::ModulePtr > () = m;
    }
#line 1488 "parser/parser.cpp"
    break;

  case 3: // opt_package: %empty
#line 285 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1494 "parser/parser.cpp"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 287 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1500 "parser/parser.cpp"
    break;

  case 5: // import_list: %empty
#line 293 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1506 "parser/parser.cpp"
    break;

  case 6: // import_list: import_list import_decl
#line 295 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1512 "parser/parser.cpp"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 304 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1518 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 306 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1524 "parser/parser.cpp"
    break;

  case 9: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 308 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/true,  combine(yystack_[3].location, yystack_[0].location)); }
#line 1530 "parser/parser.cpp"
    break;

  case 10: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 310 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/true,  combine(yystack_[5].location, yystack_[0].location)); }
#line 1536 "parser/parser.cpp"
    break;

  case 11: // names_separated_by_dots: name
#line 316 "parser/parser_rules.y"
    { std::vector<lex::SymId> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1542 "parser/parser.cpp"
    break;

  case 12: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 318 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1548 "parser/parser.cpp"
    break;

  case 13: // name: TOK_IDENTIFIER
#line 323 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1554 "parser/parser.cpp"
    break;

  case 14: // decl_list: %empty
#line 328 "parser/parser_rules.y"
                                   { yylhs.value.as < std::vector<ast::DeclPtr> > () = std::vector<ast::DeclPtr>{}; }
#line 1560 "parser/parser.cpp"
    break;

  case 15: // decl_list: decl_list decl
#line 329 "parser/parser_rules.y"
                                   { yystack_[1].value.as < std::vector<ast::DeclPtr> > ().push_back(std::move(yystack_[0].value.as < ast::DeclPtr > ())); yylhs.value.as < std::vector<ast::DeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::DeclPtr> > ()); }
#line 1566 "parser/parser.cpp"
    break;

  case 16: // decl: maybe_export fn_decl
#line 333 "parser/parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1572 "parser/parser.cpp"
    break;

  case 17: // decl: maybe_export top_decl
#line 334 "parser/parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::DeclPtr > ()); }
#line 1578 "parser/parser.cpp"
    break;

  case 18: // decl: maybe_export struct_decl
#line 335 "parser/parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1584 "parser/parser.cpp"
    break;

  case 19: // maybe_export: %empty
#line 339 "parser/parser_rules.y"
                  { yylhs.value.as < int > () = 0; }
#line 1590 "parser/parser.cpp"
    break;

  case 20: // maybe_export: TOK_EXPORT
#line 340 "parser/parser_rules.y"
                  { yylhs.value.as < int > () = 1; }
#line 1596 "parser/parser.cpp"
    break;

  case 21: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block
#line 345 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (),/*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1604 "parser/parser.cpp"
    break;

  case 22: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN
#line 349 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), /*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), nullptr, combine(yystack_[6].location, yystack_[1].location)); /* prototype */
    }
#line 1612 "parser/parser.cpp"
    break;

  case 23: // struct_decl: TOK_STRUCT ident TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 356 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[3].value.as < Str > (), std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 1618 "parser/parser.cpp"
    break;

  case 24: // struct_decl: TOK_STRUCT ident TOK_SMCLN
#line 358 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[1].value.as < Str > (), std::vector<ast::FieldDecl*>{}, combine(yystack_[2].location, yystack_[0].location)); }
#line 1624 "parser/parser.cpp"
    break;

  case 25: // field_decl_list_opt: %empty
#line 362 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 1630 "parser/parser.cpp"
    break;

  case 26: // field_decl_list_opt: field_decl_list
#line 363 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1636 "parser/parser.cpp"
    break;

  case 27: // field_decl_list: field_decl
#line 367 "parser/parser_rules.y"
                                        { std::vector<ast::FieldDecl*> v; v.push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(v); }
#line 1642 "parser/parser.cpp"
    break;

  case 28: // field_decl_list: field_decl_list field_decl
#line 368 "parser/parser_rules.y"
                                        { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1648 "parser/parser.cpp"
    break;

  case 29: // field_decl: type_with_spec ident TOK_SMCLN
#line 373 "parser/parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypePtr > (), false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1654 "parser/parser.cpp"
    break;

  case 30: // field_decl: TOK_PUB type_with_spec ident TOK_SMCLN
#line 375 "parser/parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypePtr > (), true, combine(yystack_[3].location, yystack_[0].location)); }
#line 1660 "parser/parser.cpp"
    break;

  case 31: // ret_type: TOK_ARROW type_with_spec
#line 379 "parser/parser_rules.y"
                                              { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1666 "parser/parser.cpp"
    break;

  case 32: // param_list_opt: %empty
#line 383 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::vector<ast::ParamDeclPtr>{}; }
#line 1672 "parser/parser.cpp"
    break;

  case 33: // param_list_opt: param_list
#line 384 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1678 "parser/parser.cpp"
    break;

  case 34: // param_list: param
#line 388 "parser/parser_rules.y"
                                         { std::vector<ast::ParamDeclPtr> v; v.push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(v); }
#line 1684 "parser/parser.cpp"
    break;

  case 35: // param_list: param_list TOK_COMMA param
#line 389 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ().push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1690 "parser/parser.cpp"
    break;

  case 36: // param_list: param_list TOK_COMMA
#line 390 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1696 "parser/parser.cpp"
    break;

  case 37: // param: type_with_spec ident
#line 394 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::ParamDeclPtr > () = ast.mk_param_decl(yystack_[0].value.as < Str > (), yystack_[1].value.as < ast::TypePtr > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1702 "parser/parser.cpp"
    break;

  case 38: // type_specifier_opt: %empty
#line 402 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Imm; }
#line 1708 "parser/parser.cpp"
    break;

  case 39: // type_specifier_opt: TOK_MUT
#line 404 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Mut; }
#line 1714 "parser/parser.cpp"
    break;

  case 40: // type_region_opt: %empty
#line 409 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Auto; }
#line 1720 "parser/parser.cpp"
    break;

  case 41: // type_region_opt: TOK_STATIC
#line 411 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Static; }
#line 1726 "parser/parser.cpp"
    break;

  case 42: // type_with_spec: type_specifier_opt type_spec
#line 416 "parser/parser_rules.y"
    { yystack_[0].value.as < ast::TypePtr > ()->specifier = yystack_[1].value.as < ast::TypeSpecifier > (); yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1732 "parser/parser.cpp"
    break;

  case 43: // type_spec: builtin_type
#line 420 "parser/parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = static_cast<ast::TypePtr>(yystack_[0].value.as < ast::BuiltinType * > ()); }
#line 1738 "parser/parser.cpp"
    break;

  case 44: // type_spec: type_path
#line 421 "parser/parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = static_cast<ast::TypePtr>(ast.mk_type_from_path(yystack_[0].value.as < ast::PathTypePtr > (), yystack_[0].location)); }
#line 1744 "parser/parser.cpp"
    break;

  case 45: // type_spec: fixed_array_type
#line 422 "parser/parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = static_cast<ast::TypePtr>(yystack_[0].value.as < ast::FixedArrayType* > ()); }
#line 1750 "parser/parser.cpp"
    break;

  case 46: // builtin_type: TOK_INT
#line 426 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::Int, yystack_[0].location); }
#line 1756 "parser/parser.cpp"
    break;

  case 47: // builtin_type: TOK_BIGINT
#line 427 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::BigInt, yystack_[0].location); }
#line 1762 "parser/parser.cpp"
    break;

  case 48: // builtin_type: TOK_MAGICINT
#line 428 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::MagicInt, yystack_[0].location); }
#line 1768 "parser/parser.cpp"
    break;

  case 49: // builtin_type: TOK_DOUBLE
#line 429 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::Double, yystack_[0].location); }
#line 1774 "parser/parser.cpp"
    break;

  case 50: // builtin_type: TOK_BOOL
#line 430 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::Bool, yystack_[0].location); }
#line 1780 "parser/parser.cpp"
    break;

  case 51: // builtin_type: TOK_VOID
#line 431 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::Void, yystack_[0].location); }
#line 1786 "parser/parser.cpp"
    break;

  case 52: // builtin_type: TOK_STRING
#line 432 "parser/parser_rules.y"
                  { yylhs.value.as < ast::BuiltinType * > () = ast.mk_builtin_type(ast::BuiltinTy::String, yystack_[0].location); }
#line 1792 "parser/parser.cpp"
    break;

  case 53: // type_path: type_atom
#line 437 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_single(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1798 "parser/parser.cpp"
    break;

  case 54: // type_path: type_path TOK_DOT type_atom
#line 439 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_append(yystack_[2].value.as < ast::PathTypePtr > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1804 "parser/parser.cpp"
    break;

  case 55: // type_atom: TOK_IDENTIFIER
#line 443 "parser/parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1810 "parser/parser.cpp"
    break;

  case 56: // fixed_array_type: type_spec TOK_LBRACK TOK_INT_LITERAL TOK_RBRACK
#line 448 "parser/parser_rules.y"
    { yylhs.value.as < ast::FixedArrayType* > () = ast.mk_fixed_array_type(yystack_[3].value.as < ast::TypePtr > (), yystack_[1].value.as < kl_int > (), combine(yystack_[3].location, yystack_[1].location)); }
#line 1816 "parser/parser.cpp"
    break;

  case 57: // ident: TOK_IDENTIFIER
#line 452 "parser/parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1822 "parser/parser.cpp"
    break;

  case 58: // ident_list: ident
#line 456 "parser/parser_rules.y"
                                   { yylhs.value.as < std::vector<Str> > () = std::vector<Str>(std::move(yystack_[0].value.as < Str > ())); }
#line 1828 "parser/parser.cpp"
    break;

  case 59: // ident_list: ident_list TOK_COMMA ident
#line 457 "parser/parser_rules.y"
                                   { yystack_[2].value.as < std::vector<Str> > ().push_back(std::move(yystack_[0].value.as < Str > ())); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1834 "parser/parser.cpp"
    break;

  case 60: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 464 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()), combine(yystack_[2].location, yystack_[1].location)); }
#line 1840 "parser/parser.cpp"
    break;

  case 61: // stmt_list: %empty
#line 468 "parser/parser_rules.y"
                              { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1846 "parser/parser.cpp"
    break;

  case 62: // stmt_list: stmt_list stmt
#line 469 "parser/parser_rules.y"
                              { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1852 "parser/parser.cpp"
    break;

  case 63: // stmt: var_decl_stmt
#line 473 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 1858 "parser/parser.cpp"
    break;

  case 64: // stmt: vars_decl_stmt
#line 474 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::VarsDeclStatement* > ()); }
#line 1864 "parser/parser.cpp"
    break;

  case 65: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 475 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_return_stmt(yystack_[1].value.as < ast::ExprPtr > (), yystack_[2].location); }
#line 1870 "parser/parser.cpp"
    break;

  case 66: // stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt
#line 477 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_if_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::StatementPtr > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1876 "parser/parser.cpp"
    break;

  case 67: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 479 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1882 "parser/parser.cpp"
    break;

  case 68: // stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 481 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 1888 "parser/parser.cpp"
    break;

  case 69: // stmt: TOK_BREAK TOK_SMCLN
#line 482 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1894 "parser/parser.cpp"
    break;

  case 70: // stmt: TOK_CONTINUE TOK_SMCLN
#line 483 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1900 "parser/parser.cpp"
    break;

  case 71: // stmt: block
#line 484 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 1906 "parser/parser.cpp"
    break;

  case 72: // stmt: expr TOK_SMCLN
#line 485 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::ExprPtr > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1912 "parser/parser.cpp"
    break;

  case 73: // expr_opt: %empty
#line 494 "parser/parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = nullptr; }
#line 1918 "parser/parser.cpp"
    break;

  case 74: // expr_opt: expr
#line 495 "parser/parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1924 "parser/parser.cpp"
    break;

  case 75: // var_decl_stmt: TOK_LET var_decl
#line 503 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(yystack_[0].value.as < ast::VarDecl* > (), yystack_[0].location); }
#line 1930 "parser/parser.cpp"
    break;

  case 76: // vars_decl_stmt: TOK_LET vars_decl
#line 508 "parser/parser_rules.y"
  { yylhs.value.as < ast::VarsDeclStatement* > () = ast.mk_vars_decl_stmt(yystack_[0].value.as < ast::VarsDecl* > (), yystack_[0].location); }
#line 1936 "parser/parser.cpp"
    break;

  case 77: // vars_group: TOK_LPAR ident_list TOK_RPAR
#line 515 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1942 "parser/parser.cpp"
    break;

  case 78: // top_decl: TOK_LET var_decl
#line 519 "parser/parser_rules.y"
                          { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::VarDecl* > ()); }
#line 1948 "parser/parser.cpp"
    break;

  case 79: // top_decl: TOK_LET vars_decl
#line 520 "parser/parser_rules.y"
                          { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::VarsDecl* > ()); }
#line 1954 "parser/parser.cpp"
    break;

  case 80: // vars_decl: type_region_opt type_with_spec vars_group TOK_SMCLN
#line 525 "parser/parser_rules.y"
    {
      // No initializers
      yylhs.value.as < ast::VarsDecl* > () = ast.mk_vars_decl(/*names*/std::move(yystack_[1].value.as < std::vector<Str> > ()),
                            /*assignments*/std::vector<ast::ExprPtr>{},
                            /*type*/yystack_[2].value.as < ast::TypePtr > (),
                            /*region*/yystack_[3].value.as < ast::TypeRegion > (),
                            /*range*/combine(yystack_[3].location, yystack_[1].location));
    }
#line 1967 "parser/parser.cpp"
    break;

  case 81: // vars_decl: type_region_opt type_with_spec vars_group TOK_ASSIGN arg_list_opt TOK_SMCLN
#line 534 "parser/parser_rules.y"
    {
      // Initializers: either empty, one expr, or N exprs
      yylhs.value.as < ast::VarsDecl* > () = ast.mk_vars_decl(/*names*/std::move(yystack_[3].value.as < std::vector<Str> > ()),
                            /*assignments*/std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()),
                            /*type*/yystack_[4].value.as < ast::TypePtr > (),
                            /*region*/yystack_[5].value.as < ast::TypeRegion > (),
                            /*range*/combine(yystack_[5].location, yystack_[3].location));
    }
#line 1980 "parser/parser.cpp"
    break;

  case 82: // var_decl: type_region_opt type_with_spec ident TOK_SMCLN
#line 546 "parser/parser_rules.y"
    {
      auto decl = ast.mk_var_declarator_expr(yystack_[1].value.as < Str > (), nullptr, yystack_[1].location);
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(std::move(decl), yystack_[2].value.as < ast::TypePtr > (), yystack_[3].value.as < ast::TypeRegion > (), combine(yystack_[3].location, yystack_[1].location));
    }
#line 1989 "parser/parser.cpp"
    break;

  case 83: // var_decl: type_region_opt type_with_spec ident TOK_ASSIGN assign TOK_SMCLN
#line 551 "parser/parser_rules.y"
    {
      auto decl = ast.mk_var_declarator_expr(yystack_[3].value.as < Str > (), std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[3].location, yystack_[1].location));
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(std::move(decl), yystack_[4].value.as < ast::TypePtr > (), yystack_[5].value.as < ast::TypeRegion > (), combine(yystack_[5].location, yystack_[1].location));
    }
#line 1998 "parser/parser.cpp"
    break;

  case 84: // expr: assign
#line 561 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2004 "parser/parser.cpp"
    break;

  case 85: // assign: cond
#line 565 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2010 "parser/parser.cpp"
    break;

  case 86: // assign: postfix TOK_ASSIGN assign
#line 566 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*Assign*/AssignOp::Assign, combine(yystack_[2].location, yystack_[0].location)); }
#line 2016 "parser/parser.cpp"
    break;

  case 87: // assign: postfix TOK_PLUS_ASSIGN assign
#line 567 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*AddEq*/AssignOp::Add, combine(yystack_[2].location, yystack_[0].location)); }
#line 2022 "parser/parser.cpp"
    break;

  case 88: // assign: postfix TOK_MIN_ASSIGN assign
#line 568 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*SubEq*/AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 2028 "parser/parser.cpp"
    break;

  case 89: // assign: postfix TOK_MUL_ASSIGN assign
#line 569 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*MulEq*/AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 2034 "parser/parser.cpp"
    break;

  case 90: // assign: postfix TOK_DIV_ASSIGN assign
#line 570 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*DivEq*/AssignOp::Divide, combine(yystack_[2].location, yystack_[0].location)); }
#line 2040 "parser/parser.cpp"
    break;

  case 91: // cond: logic_or
#line 574 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2046 "parser/parser.cpp"
    break;

  case 92: // logic_or: logic_and
#line 578 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2052 "parser/parser.cpp"
    break;

  case 93: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 580 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2058 "parser/parser.cpp"
    break;

  case 94: // logic_and: equality
#line 584 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2064 "parser/parser.cpp"
    break;

  case 95: // logic_and: logic_and TOK_BOOL_AND equality
#line 586 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2070 "parser/parser.cpp"
    break;

  case 96: // equality: relational
#line 590 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2076 "parser/parser.cpp"
    break;

  case 97: // equality: equality TOK_EQUAL relational
#line 592 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2082 "parser/parser.cpp"
    break;

  case 98: // equality: equality TOK_NEQUAL relational
#line 594 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2088 "parser/parser.cpp"
    break;

  case 99: // relational: additive
#line 598 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2094 "parser/parser.cpp"
    break;

  case 100: // relational: relational TOK_LESS additive
#line 599 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2100 "parser/parser.cpp"
    break;

  case 101: // relational: relational TOK_LEQ additive
#line 600 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2106 "parser/parser.cpp"
    break;

  case 102: // relational: relational TOK_GREATER additive
#line 601 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2112 "parser/parser.cpp"
    break;

  case 103: // relational: relational TOK_GEQ additive
#line 602 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2118 "parser/parser.cpp"
    break;

  case 104: // additive: multiplicative
#line 606 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2124 "parser/parser.cpp"
    break;

  case 105: // additive: additive TOK_PLUS multiplicative
#line 607 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2130 "parser/parser.cpp"
    break;

  case 106: // additive: additive TOK_MINUS multiplicative
#line 608 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2136 "parser/parser.cpp"
    break;

  case 107: // multiplicative: unary
#line 612 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2142 "parser/parser.cpp"
    break;

  case 108: // multiplicative: multiplicative TOK_STAR unary
#line 613 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2148 "parser/parser.cpp"
    break;

  case 109: // multiplicative: multiplicative TOK_SLASH unary
#line 614 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2154 "parser/parser.cpp"
    break;

  case 110: // multiplicative: multiplicative TOK_MODULO unary
#line 615 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2160 "parser/parser.cpp"
    break;

  case 111: // unary: TOK_NEG unary
#line 619 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::negation, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2166 "parser/parser.cpp"
    break;

  case 112: // unary: TOK_NEGATION unary
#line 620 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2172 "parser/parser.cpp"
    break;

  case 113: // unary: TOK_INC unary
#line 621 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2178 "parser/parser.cpp"
    break;

  case 114: // unary: TOK_DEC unary
#line 622 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2184 "parser/parser.cpp"
    break;

  case 115: // unary: postfix
#line 623 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 2190 "parser/parser.cpp"
    break;

  case 116: // postfix: primary
#line 627 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2196 "parser/parser.cpp"
    break;

  case 117: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 629 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_call_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2202 "parser/parser.cpp"
    break;

  case 118: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 631 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_index(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2208 "parser/parser.cpp"
    break;

  case 119: // postfix: postfix TOK_DOT ident
#line 633 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_field_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2214 "parser/parser.cpp"
    break;

  case 120: // postfix: postfix TOK_INC
#line 635 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2220 "parser/parser.cpp"
    break;

  case 121: // postfix: postfix TOK_DEC
#line 637 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2226 "parser/parser.cpp"
    break;

  case 122: // arg_list_opt: %empty
#line 641 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::vector<ast::ExprPtr>{}; }
#line 2232 "parser/parser.cpp"
    break;

  case 123: // arg_list_opt: arg_list
#line 642 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::ExprPtr> > ());  }
#line 2238 "parser/parser.cpp"
    break;

  case 124: // arg_list: expr
#line 646 "parser/parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(v); }
#line 2244 "parser/parser.cpp"
    break;

  case 125: // arg_list: arg_list TOK_COMMA expr
#line 647 "parser/parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2250 "parser/parser.cpp"
    break;

  case 126: // arg_list: arg_list TOK_COMMA
#line 648 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2256 "parser/parser.cpp"
    break;

  case 127: // primary: ident
#line 652 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2262 "parser/parser.cpp"
    break;

  case 128: // primary: TOK_INT_LITERAL
#line 653 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_int_literal_expr(yystack_[0].value.as < kl_int > (), yystack_[0].location); }
#line 2268 "parser/parser.cpp"
    break;

  case 129: // primary: TOK_FLOAT_LITERAL
#line 654 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_float_literal_expr(yystack_[0].value.as < kl_float > (), yystack_[0].location); }
#line 2274 "parser/parser.cpp"
    break;

  case 130: // primary: TOK_STRING_LITERAL
#line 655 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2280 "parser/parser.cpp"
    break;

  case 131: // primary: TOK_BOOL_LITERAL
#line 656 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl_bool > (), yystack_[0].location); }
#line 2286 "parser/parser.cpp"
    break;

  case 132: // primary: TOK_LPAR expr TOK_RPAR
#line 657 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[1].value.as < ast::ExprPtr > ()); }
#line 2292 "parser/parser.cpp"
    break;

  case 133: // primary: struct_lit
#line 658 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = static_cast<ast::ExprPtr>(yystack_[0].value.as < ast::ObjLiteralExpr* > ()); }
#line 2298 "parser/parser.cpp"
    break;

  case 134: // struct_lit: type_path TOK_LCBRA field_inits_opt TOK_RCBRA
#line 663 "parser/parser_rules.y"
    { yylhs.value.as < ast::ObjLiteralExpr* > () = ast.mk_obj_literal_expr(yystack_[3].value.as < ast::PathTypePtr > (), std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2304 "parser/parser.cpp"
    break;

  case 135: // field_inits_opt: %empty
#line 667 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::vector<ast::FieldInitPtr>{}; }
#line 2310 "parser/parser.cpp"
    break;

  case 136: // field_inits_opt: field_inits
#line 668 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2316 "parser/parser.cpp"
    break;

  case 137: // field_inits: field_init
#line 672 "parser/parser_rules.y"
                                         { std::vector<ast::FieldInitPtr> v; v.push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(v); }
#line 2322 "parser/parser.cpp"
    break;

  case 138: // field_inits: field_inits TOK_COMMA field_init
#line 673 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ().push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2328 "parser/parser.cpp"
    break;

  case 139: // field_inits: field_inits TOK_COMMA
#line 674 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2334 "parser/parser.cpp"
    break;

  case 140: // field_init: ident TOK_COLON expr
#line 679 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitPtr > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2340 "parser/parser.cpp"
    break;


#line 2344 "parser/parser.cpp"

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


  const signed char parser::yypact_ninf_ = -101;

  const signed char parser::yytable_ninf_ = -56;

  const short
  parser::yypact_[] =
  {
     -21,   -14,    20,  -101,  -101,    52,  -101,  -101,    19,  -101,
     -14,   -14,     8,  -101,     5,  -101,    24,   -14,  -101,  -101,
     111,   -14,  -101,    71,    34,    34,    49,  -101,  -101,  -101,
      39,   -14,  -101,  -101,    61,    38,  -101,    82,  -101,  -101,
    -101,    62,    -6,  -101,    31,  -101,    69,     1,  -101,    82,
     103,    -2,  -101,    34,    80,   116,  -101,    34,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,    87,  -101,   117,  -101,
    -101,    34,   -35,   -29,    34,  -101,  -101,   124,   126,    17,
    -101,    95,   152,  -101,     7,  -101,    -8,  -101,    -8,   140,
    -101,    82,    93,  -101,   145,  -101,  -101,    34,    79,  -101,
    -101,  -101,  -101,    -8,    -8,    -8,    -8,    -8,    86,  -101,
     144,  -101,   134,   136,    76,    83,   119,   118,  -101,    25,
    -101,  -101,  -101,  -101,   157,   159,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,   171,  -101,    84,  -101,  -101,  -101,    34,
    -101,    -8,    -8,    -8,    -8,    -8,    -8,    -8,    -8,    -8,
      -8,    -8,    -8,    -8,    -8,    -8,    34,  -101,  -101,    -8,
      -8,    -8,    -8,    -8,  -101,    -8,   156,  -101,   165,   169,
     170,  -101,   136,    76,    83,    83,   119,   119,   119,   119,
     118,   118,  -101,  -101,  -101,   174,   177,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,   181,   182,   173,    49,    -8,   176,
     178,  -101,  -101,  -101,  -101,  -101,   184,    -8,  -101,    34,
    -101,  -101,    -8,    -8,   224,  -101,  -101,   186,  -101,  -101,
    -101,  -101,  -101,  -101,   194,   195,   197,  -101,   190,   173,
      -8,  -101,  -101,   198,   191,  -101
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    13,     0,    11,     1,    14,     4,
       0,     0,     0,     6,    19,    12,     0,     0,    20,    15,
       0,     0,     7,     0,     0,     0,    40,    16,    18,    17,
       0,     0,     9,    57,     0,     0,    41,    38,    79,    78,
       8,     0,    38,    24,    38,    39,     0,     0,    10,    38,
       0,    38,    27,     0,     0,    33,    34,     0,    46,    47,
      48,    49,    50,    51,    52,    55,    42,    43,    44,    53,
      45,     0,     0,     0,     0,    23,    28,     0,     0,    38,
      37,     0,     0,    58,     0,    82,     0,    80,   122,     0,
      29,    38,     0,    35,     0,    54,    77,     0,    57,   128,
     129,   130,   131,     0,     0,     0,     0,     0,     0,   127,
       0,    85,    91,    92,    94,    96,    99,   104,   107,   115,
     116,   133,   124,    84,     0,   123,    30,    31,    61,    22,
      21,    56,    59,     0,   112,   115,   111,   113,   114,   135,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,     0,     0,   120,   121,     0,
       0,     0,     0,     0,    81,   126,     0,   132,     0,     0,
     136,   137,    93,    95,    97,    98,   100,   101,   102,   103,
     105,   106,   108,   109,   110,     0,     0,   119,    86,    87,
      88,    89,    90,   125,     0,     0,     0,    40,    73,     0,
       0,    60,    71,    62,    63,    64,     0,     0,   134,   139,
     117,   118,     0,     0,     0,    76,    75,     0,    74,    69,
      70,    72,   140,   138,     0,     0,     0,    65,     0,     0,
       0,    66,    67,     0,     0,    68
  };

  const short
  parser::yypgoto_[] =
  {
    -101,  -101,  -101,  -101,  -101,    85,    41,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,   185,  -101,  -101,  -101,   158,  -101,
    -101,   -31,  -101,  -101,   196,   161,  -101,   -24,  -101,   -90,
    -101,    16,  -101,  -101,  -101,  -101,  -101,    48,    50,  -100,
     -82,  -101,  -101,   105,   106,    33,    18,    29,   -95,     4,
      96,  -101,  -101,  -101,  -101,  -101,    40
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    13,     5,     6,    14,    19,    20,
      27,    28,    50,    51,    52,    92,    54,    55,    56,    46,
      37,    53,    66,    67,   108,    69,    70,   109,    84,   202,
     166,   203,   217,   204,   205,    73,    29,    38,    39,   122,
     123,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     124,   125,   120,   121,   169,   170,   171
  };

  const short
  parser::yytable_[] =
  {
      34,    35,   130,   133,   110,    -2,    47,     1,    85,   134,
     136,   137,   138,    57,    87,    45,     4,    49,    74,    45,
       7,    49,    98,    72,    99,   100,   101,   102,   103,    77,
      86,    33,    18,    80,    17,   -25,    88,    71,    45,   -26,
     104,   105,   106,   107,    96,    11,    12,    83,    57,    97,
      89,    15,    45,    21,   -36,   186,   182,   183,   184,   -36,
     127,   154,    30,   155,    33,   193,   206,    22,   -32,    10,
     156,    36,    41,   132,    44,   157,   158,   188,   189,   190,
     191,   192,    40,    58,    59,    60,    61,    62,    63,    64,
     159,   160,   161,   162,   163,     9,    16,    10,   218,    65,
      31,    42,    23,    45,    43,    48,   214,   222,   135,   135,
     135,   135,   224,   225,    32,   168,    10,    78,    24,   -55,
     154,    25,   155,    26,   -55,    81,   139,    94,   206,   156,
     233,    82,   187,   128,   157,   158,   129,   143,   144,   232,
     145,   146,   147,   148,    75,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,    79,   194,
     195,   196,    82,   176,   177,   178,   179,    90,   197,   198,
     151,   152,   153,    91,   149,   150,   174,   175,   180,   181,
     199,   200,    65,   126,   131,   168,    98,   140,    99,   100,
     101,   102,   103,   194,   195,   196,   128,   201,   141,   142,
     164,   165,   197,   198,   104,   105,   106,   107,   167,   207,
     208,   210,   209,   128,   199,   200,   211,   212,   213,   219,
      98,   220,    99,   100,   101,   102,   103,   221,   226,   227,
     128,   228,   229,   230,   235,   234,    76,    93,   104,   105,
     106,   107,    68,    95,   231,   215,   172,   216,   173,   223,
     185
  };

  const unsigned char
  parser::yycheck_[] =
  {
      24,    25,    92,   103,    86,     0,    37,    28,    43,   104,
     105,   106,   107,    44,    43,    21,    30,    23,    49,    21,
       0,    23,    30,    47,    32,    33,    34,    35,    36,    53,
      65,    30,    27,    57,    26,    41,    65,    36,    21,    41,
      48,    49,    50,    51,    37,    26,    27,    71,    79,    42,
      74,    10,    21,    29,    37,   155,   151,   152,   153,    42,
      91,    36,    21,    38,    30,   165,   166,    43,    37,    45,
      45,    22,    31,    97,    36,    50,    51,   159,   160,   161,
     162,   163,    43,    14,    15,    16,    17,    18,    19,    20,
      65,    66,    67,    68,    69,    43,    11,    45,   198,    30,
      29,    40,    17,    21,    43,    43,   196,   207,   104,   105,
     106,   107,   212,   213,    43,   139,    45,    37,     7,    40,
      36,    10,    38,    12,    45,    38,    40,    32,   228,    45,
     230,    45,   156,    40,    50,    51,    43,    61,    62,   229,
      57,    58,    59,    60,    41,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,    42,     3,
       4,     5,    45,   145,   146,   147,   148,    43,    12,    13,
      52,    53,    54,    47,    55,    56,   143,   144,   149,   150,
      24,    25,    30,    43,    39,   209,    30,    43,    32,    33,
      34,    35,    36,     3,     4,     5,    40,    41,    64,    63,
      43,    42,    12,    13,    48,    49,    50,    51,    37,    44,
      41,    37,    42,    40,    24,    25,    39,    36,    36,    43,
      30,    43,    32,    33,    34,    35,    36,    43,     4,    43,
      40,    37,    37,    36,    43,    37,    51,    79,    48,    49,
      50,    51,    46,    82,   228,   197,   141,   197,   142,   209,
     154
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    28,    74,    75,    30,    78,    79,     0,    76,    43,
      45,    26,    27,    77,    80,    79,    78,    26,    27,    81,
      82,    29,    43,    78,     7,    10,    12,    83,    84,   109,
      79,    29,    43,    30,   100,   100,    22,    93,   110,   111,
      43,    79,    40,    43,    36,    21,    92,    94,    43,    23,
      85,    86,    87,    94,    89,    90,    91,    94,    14,    15,
      16,    17,    18,    19,    20,    30,    95,    96,    97,    98,
      99,    36,   100,   108,    94,    41,    87,   100,    37,    42,
     100,    38,    45,   100,   101,    43,    65,    43,    65,   100,
      43,    47,    88,    91,    32,    98,    37,    42,    30,    32,
      33,    34,    35,    36,    48,    49,    50,    51,    97,   100,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     125,   126,   112,   113,   123,   124,    43,    94,    40,    43,
     102,    39,   100,   112,   121,   122,   121,   121,   121,    40,
      43,    64,    63,    61,    62,    57,    58,    59,    60,    55,
      56,    52,    53,    54,    36,    38,    45,    50,    51,    65,
      66,    67,    68,    69,    43,    42,   103,    37,   100,   127,
     128,   129,   116,   117,   118,   118,   119,   119,   119,   119,
     120,   120,   121,   121,   121,   123,   112,   100,   113,   113,
     113,   113,   113,   112,     3,     4,     5,    12,    13,    24,
      25,    41,   102,   104,   106,   107,   112,    44,    41,    42,
      37,    39,    36,    36,   102,   110,   111,   105,   112,    43,
      43,    43,   112,   129,   112,   112,     4,    43,    37,    37,
      36,   104,   102,   112,    37,    43
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    78,    78,    79,    80,    80,    81,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    89,    89,    90,    90,    90,    91,    92,    92,
      93,    93,    94,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    97,    97,    98,    99,   100,   101,   101,
     102,   103,   103,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   105,   105,   106,   107,   108,   109,   109,
     110,   110,   111,   111,   112,   113,   113,   113,   113,   113,
     113,   114,   115,   115,   116,   116,   117,   117,   117,   118,
     118,   118,   118,   118,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   123,   123,   124,   124,   124,   125,   125,   125,
     125,   125,   125,   125,   126,   127,   127,   128,   128,   128,
     129
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     4,
       6,     1,     3,     1,     0,     2,     2,     2,     2,     0,
       1,     7,     7,     5,     3,     0,     1,     1,     2,     3,
       4,     2,     0,     1,     1,     3,     2,     2,     0,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     4,     1,     1,     3,
       3,     0,     2,     1,     1,     3,     5,     5,     7,     2,
       2,     1,     2,     0,     1,     2,     2,     3,     2,     2,
       4,     6,     4,     6,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     2,     2,     2,     2,     1,     1,     4,     4,     3,
       2,     2,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     3,     1,     4,     0,     1,     1,     3,     2,
       3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_ENUM", "TOK_TRAIT", "TOK_FN",
  "TOK_TYPE", "TOK_LET", "TOK_RETURN", "TOK_INT", "TOK_BIGINT",
  "TOK_MAGICINT", "TOK_DOUBLE", "TOK_BOOL", "TOK_VOID", "TOK_STRING",
  "TOK_MUT", "TOK_STATIC", "TOK_PUB", "TOK_BREAK", "TOK_CONTINUE",
  "TOK_IMPORT", "TOK_EXPORT", "TOK_PACKAGE", "TOK_AS", "TOK_IDENTIFIER",
  "TOK_TYPE_NAME", "TOK_INT_LITERAL", "TOK_FLOAT_LITERAL",
  "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL", "TOK_LPAR", "TOK_RPAR",
  "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA", "TOK_RCBRA", "TOK_COMMA",
  "TOK_SMCLN", "TOK_COLON", "TOK_DOT", "TOK_QUESTION", "TOK_ARROW",
  "TOK_NEGATION", "TOK_NEG", "TOK_INC", "TOK_DEC", "TOK_STAR", "TOK_SLASH",
  "TOK_MODULO", "TOK_PLUS", "TOK_MINUS", "TOK_LESS", "TOK_LEQ",
  "TOK_GREATER", "TOK_GEQ", "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND",
  "TOK_BOOL_OR", "TOK_ASSIGN", "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN",
  "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN", "TERNARY", "UMINUS", "UPRE",
  "$accept", "translation_unit", "opt_package", "import_list",
  "import_decl", "names_separated_by_dots", "name", "decl_list", "decl",
  "maybe_export", "fn_decl", "struct_decl", "field_decl_list_opt",
  "field_decl_list", "field_decl", "ret_type", "param_list_opt",
  "param_list", "param", "type_specifier_opt", "type_region_opt",
  "type_with_spec", "type_spec", "builtin_type", "type_path", "type_atom",
  "fixed_array_type", "ident", "ident_list", "block", "stmt_list", "stmt",
  "expr_opt", "var_decl_stmt", "vars_decl_stmt", "vars_group", "top_decl",
  "vars_decl", "var_decl", "expr", "assign", "cond", "logic_or",
  "logic_and", "equality", "relational", "additive", "multiplicative",
  "unary", "postfix", "arg_list_opt", "arg_list", "primary", "struct_lit",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   274,   274,   285,   286,   293,   294,   303,   305,   307,
     309,   315,   317,   322,   328,   329,   333,   334,   335,   339,
     340,   344,   348,   355,   357,   362,   363,   367,   368,   372,
     374,   379,   383,   384,   388,   389,   390,   394,   402,   403,
     409,   410,   415,   420,   421,   422,   426,   427,   428,   429,
     430,   431,   432,   436,   438,   443,   447,   452,   456,   457,
     463,   468,   469,   473,   474,   475,   476,   478,   480,   482,
     483,   484,   485,   494,   495,   502,   507,   514,   519,   520,
     524,   533,   545,   550,   561,   565,   566,   567,   568,   569,
     570,   574,   578,   579,   584,   585,   590,   591,   593,   598,
     599,   600,   601,   602,   606,   607,   608,   612,   613,   614,
     615,   619,   620,   621,   622,   623,   627,   628,   630,   632,
     634,   636,   641,   642,   646,   647,   648,   652,   653,   654,
     655,   656,   657,   658,   662,   667,   668,   672,   673,   674,
     678
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


#line 4 "parser/parser_rules.y"
} // yy
#line 3137 "parser/parser.cpp"

#line 682 "parser/parser_rules.y"


/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
