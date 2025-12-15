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
      case symbol_kind::S_ident: // ident
        value.YY_MOVE_OR_COPY< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type_expr: // array_type_expr
        value.YY_MOVE_OR_COPY< ast::ArrayTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.YY_MOVE_OR_COPY< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
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

      case symbol_kind::S_fn_decl: // fn_decl
        value.YY_MOVE_OR_COPY< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.YY_MOVE_OR_COPY< ast::ModulePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ast::ParamDeclPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.YY_MOVE_OR_COPY< ast::PathLiteralExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.YY_MOVE_OR_COPY< ast::PathTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.YY_MOVE_OR_COPY< ast::RefTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.YY_MOVE_OR_COPY< ast::RefTypeExpr::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.YY_MOVE_OR_COPY< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
        value.YY_MOVE_OR_COPY< ast::TypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_mutability: // var_mutability
        value.YY_MOVE_OR_COPY< ast::VarDecl::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.YY_MOVE_OR_COPY< ast::VarDeclStatement* > (YY_MOVE (that.value));
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
      case symbol_kind::S_ident: // ident
        value.move< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type_expr: // array_type_expr
        value.move< ast::ArrayTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
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

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::ModulePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDeclPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::PathLiteralExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::RefTypeExpr::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::StatementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
        value.move< ast::TypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_mutability: // var_mutability
        value.move< ast::VarDecl::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (YY_MOVE (that.value));
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
      case symbol_kind::S_ident: // ident
        value.copy< Str > (that.value);
        break;

      case symbol_kind::S_array_type_expr: // array_type_expr
        value.copy< ast::ArrayTypeExpr* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.copy< ast::BuiltinTypeExpr* > (that.value);
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

      case symbol_kind::S_fn_decl: // fn_decl
        value.copy< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.copy< ast::ModulePtr > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDeclPtr > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.copy< ast::PathLiteralExpr* > (that.value);
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.copy< ast::PathTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.copy< ast::RefTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.copy< ast::RefTypeExpr::Mutability > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.copy< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
        value.copy< ast::TypeExpr* > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_mutability: // var_mutability
        value.copy< ast::VarDecl::Mutability > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.copy< ast::VarDeclStatement* > (that.value);
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
      case symbol_kind::S_ident: // ident
        value.move< Str > (that.value);
        break;

      case symbol_kind::S_array_type_expr: // array_type_expr
        value.move< ast::ArrayTypeExpr* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (that.value);
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

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::ModulePtr > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDeclPtr > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::PathLiteralExpr* > (that.value);
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        value.move< ast::PathTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        value.move< ast::RefTypeExpr* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::RefTypeExpr::Mutability > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::StatementPtr > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
        value.move< ast::TypeExpr* > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_mutability: // var_mutability
        value.move< ast::VarDecl::Mutability > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (that.value);
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
      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Str > ();
        break;

      case symbol_kind::S_array_type_expr: // array_type_expr
        yylhs.value.emplace< ast::ArrayTypeExpr* > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< ast::BlockStatement* > ();
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        yylhs.value.emplace< ast::BuiltinTypeExpr* > ();
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

      case symbol_kind::S_fn_decl: // fn_decl
        yylhs.value.emplace< ast::FunctionDecl* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        yylhs.value.emplace< ast::ModulePtr > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ast::ParamDeclPtr > ();
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        yylhs.value.emplace< ast::PathLiteralExpr* > ();
        break;

      case symbol_kind::S_path_type_expr: // path_type_expr
        yylhs.value.emplace< ast::PathTypeExpr* > ();
        break;

      case symbol_kind::S_ref_type_expr: // ref_type_expr
        yylhs.value.emplace< ast::RefTypeExpr* > ();
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        yylhs.value.emplace< ast::RefTypeExpr::Mutability > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< ast::StatementPtr > ();
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        yylhs.value.emplace< ast::StructDecl* > ();
        break;

      case symbol_kind::S_ret_type_expr: // ret_type_expr
      case symbol_kind::S_type_expr: // type_expr
        yylhs.value.emplace< ast::TypeExpr* > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< ast::VarDecl* > ();
        break;

      case symbol_kind::S_var_mutability: // var_mutability
        yylhs.value.emplace< ast::VarDecl::Mutability > ();
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        yylhs.value.emplace< ast::VarDeclStatement* > ();
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
#line 272 "parser/parser_rules.y"
    {
        auto* m = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::DeclPtr> > ()), combine(yystack_[2].location, yystack_[0].location));
        ast.project_add_module(m);
        yylhs.value.as < ast::ModulePtr > () = m;
    }
#line 1433 "parser/parser.cpp"
    break;

  case 3: // opt_package: %empty
#line 282 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1439 "parser/parser.cpp"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 284 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1445 "parser/parser.cpp"
    break;

  case 5: // import_list: %empty
#line 290 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1451 "parser/parser.cpp"
    break;

  case 6: // import_list: import_list import_decl
#line 292 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1457 "parser/parser.cpp"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 299 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1463 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 301 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1469 "parser/parser.cpp"
    break;

  case 9: // names_separated_by_dots: name
#line 307 "parser/parser_rules.y"
    { std::vector<lex::SymId> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1475 "parser/parser.cpp"
    break;

  case 10: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 309 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1481 "parser/parser.cpp"
    break;

  case 11: // name: TOK_IDENTIFIER
#line 314 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1487 "parser/parser.cpp"
    break;

  case 12: // decl_list: %empty
#line 319 "parser/parser_rules.y"
                                   { yylhs.value.as < std::vector<ast::DeclPtr> > () = std::vector<ast::DeclPtr>{}; }
#line 1493 "parser/parser.cpp"
    break;

  case 13: // decl_list: decl_list decl
#line 320 "parser/parser_rules.y"
                                   { yystack_[1].value.as < std::vector<ast::DeclPtr> > ().push_back(std::move(yystack_[0].value.as < ast::DeclPtr > ())); yylhs.value.as < std::vector<ast::DeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::DeclPtr> > ()); }
#line 1499 "parser/parser.cpp"
    break;

  case 14: // decl: fn_decl
#line 324 "parser/parser_rules.y"
                 { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1505 "parser/parser.cpp"
    break;

  case 15: // decl: top_decl
#line 325 "parser/parser_rules.y"
                 { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::DeclPtr > ()); }
#line 1511 "parser/parser.cpp"
    break;

  case 16: // decl: struct_decl
#line 326 "parser/parser_rules.y"
                 { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1517 "parser/parser.cpp"
    break;

  case 17: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr block
#line 331 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1525 "parser/parser.cpp"
    break;

  case 18: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 335 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypeExpr* > (), nullptr, combine(yystack_[6].location, yystack_[1].location)); /* prototype */
    }
#line 1533 "parser/parser.cpp"
    break;

  case 19: // struct_decl: TOK_STRUCT ident TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 342 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[3].value.as < Str > (), std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 1539 "parser/parser.cpp"
    break;

  case 20: // struct_decl: TOK_STRUCT ident TOK_SMCLN
#line 344 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[1].value.as < Str > (), std::vector<ast::FieldDecl*>{}, combine(yystack_[2].location, yystack_[0].location)); }
#line 1545 "parser/parser.cpp"
    break;

  case 21: // field_decl_list_opt: %empty
#line 348 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 1551 "parser/parser.cpp"
    break;

  case 22: // field_decl_list_opt: field_decl_list
#line 349 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1557 "parser/parser.cpp"
    break;

  case 23: // field_decl_list: field_decl
#line 353 "parser/parser_rules.y"
                                        { std::vector<ast::FieldDecl*> v; v.push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(v); }
#line 1563 "parser/parser.cpp"
    break;

  case 24: // field_decl_list: field_decl_list field_decl
#line 354 "parser/parser_rules.y"
                                        { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1569 "parser/parser.cpp"
    break;

  case 25: // field_decl: type_expr ident TOK_SMCLN
#line 359 "parser/parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Priv, combine(yystack_[2].location, yystack_[0].location)); }
#line 1575 "parser/parser.cpp"
    break;

  case 26: // field_decl: TOK_PUB type_expr ident TOK_SMCLN
#line 361 "parser/parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Publ, combine(yystack_[3].location, yystack_[0].location)); }
#line 1581 "parser/parser.cpp"
    break;

  case 27: // ret_type_expr: TOK_ARROW type_expr
#line 365 "parser/parser_rules.y"
                                         { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 1587 "parser/parser.cpp"
    break;

  case 28: // param_list_opt: %empty
#line 369 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::vector<ast::ParamDeclPtr>{}; }
#line 1593 "parser/parser.cpp"
    break;

  case 29: // param_list_opt: param_list
#line 370 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1599 "parser/parser.cpp"
    break;

  case 30: // param_list: param
#line 374 "parser/parser_rules.y"
                                         { std::vector<ast::ParamDeclPtr> v; v.push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(v); }
#line 1605 "parser/parser.cpp"
    break;

  case 31: // param_list: param_list TOK_COMMA param
#line 375 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ().push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1611 "parser/parser.cpp"
    break;

  case 32: // param_list: param_list TOK_COMMA
#line 376 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1617 "parser/parser.cpp"
    break;

  case 33: // param: type_expr ident
#line 380 "parser/parser_rules.y"
                                     { yylhs.value.as < ast::ParamDeclPtr > () = ast.mk_param_decl(yystack_[0].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1623 "parser/parser.cpp"
    break;

  case 34: // type_expr: builtin_type_expr
#line 386 "parser/parser_rules.y"
                           { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 1629 "parser/parser.cpp"
    break;

  case 35: // type_expr: path_type_expr
#line 387 "parser/parser_rules.y"
                          { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 1635 "parser/parser.cpp"
    break;

  case 36: // type_expr: array_type_expr
#line 388 "parser/parser_rules.y"
                     { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::ArrayTypeExpr* > ()); }
#line 1641 "parser/parser.cpp"
    break;

  case 37: // type_expr: ref_type_expr
#line 389 "parser/parser_rules.y"
                      { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 1647 "parser/parser.cpp"
    break;

  case 38: // builtin_type_expr: TOK_I8
#line 393 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::I8,   yystack_[0].location); }
#line 1653 "parser/parser.cpp"
    break;

  case 39: // builtin_type_expr: TOK_U8
#line 394 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::U8,   yystack_[0].location); }
#line 1659 "parser/parser.cpp"
    break;

  case 40: // builtin_type_expr: TOK_I16
#line 395 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::I16,  yystack_[0].location); }
#line 1665 "parser/parser.cpp"
    break;

  case 41: // builtin_type_expr: TOK_U16
#line 396 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::U16,  yystack_[0].location); }
#line 1671 "parser/parser.cpp"
    break;

  case 42: // builtin_type_expr: TOK_I32
#line 397 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::I32,  yystack_[0].location); }
#line 1677 "parser/parser.cpp"
    break;

  case 43: // builtin_type_expr: TOK_U32
#line 398 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::U32,  yystack_[0].location); }
#line 1683 "parser/parser.cpp"
    break;

  case 44: // builtin_type_expr: TOK_I64
#line 399 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::I64,  yystack_[0].location); }
#line 1689 "parser/parser.cpp"
    break;

  case 45: // builtin_type_expr: TOK_U64
#line 400 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::U64,  yystack_[0].location); }
#line 1695 "parser/parser.cpp"
    break;

  case 46: // builtin_type_expr: TOK_I128
#line 401 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::I128, yystack_[0].location); }
#line 1701 "parser/parser.cpp"
    break;

  case 47: // builtin_type_expr: TOK_U128
#line 402 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::U128, yystack_[0].location); }
#line 1707 "parser/parser.cpp"
    break;

  case 48: // builtin_type_expr: TOK_F32
#line 403 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::F32,  yystack_[0].location); }
#line 1713 "parser/parser.cpp"
    break;

  case 49: // builtin_type_expr: TOK_F64
#line 404 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::F64,  yystack_[0].location); }
#line 1719 "parser/parser.cpp"
    break;

  case 50: // builtin_type_expr: TOK_BOOL
#line 405 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::Bool, yystack_[0].location); }
#line 1725 "parser/parser.cpp"
    break;

  case 51: // builtin_type_expr: TOK_CHAR
#line 406 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(ast::BuiltinTypeExpr::Kind::Char, yystack_[0].location); }
#line 1731 "parser/parser.cpp"
    break;

  case 52: // path_type_expr: ident_list
#line 410 "parser/parser_rules.y"
                    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1737 "parser/parser.cpp"
    break;

  case 53: // array_type_expr: type_expr TOK_LBRACK expr TOK_RBRACK
#line 415 "parser/parser_rules.y"
    { yylhs.value.as < ast::ArrayTypeExpr* > () = ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::ExprPtr > (), combine(yystack_[3].location, yystack_[1].location)); }
#line 1743 "parser/parser.cpp"
    break;

  case 54: // ref_mutability: %empty
#line 419 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 1749 "parser/parser.cpp"
    break;

  case 55: // ref_mutability: TOK_IMM
#line 420 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 1755 "parser/parser.cpp"
    break;

  case 56: // ref_mutability: TOK_MUT
#line 421 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Mut; }
#line 1761 "parser/parser.cpp"
    break;

  case 57: // ref_type_expr: TOK_AMP ref_mutability type_expr
#line 426 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::RefTypeExpr::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1767 "parser/parser.cpp"
    break;

  case 58: // ident: TOK_IDENTIFIER
#line 430 "parser/parser_rules.y"
                        { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1773 "parser/parser.cpp"
    break;

  case 59: // ident_list: ident
#line 434 "parser/parser_rules.y"
                                   { yylhs.value.as < std::vector<Str> > () = std::vector<Str>(std::move(yystack_[0].value.as < Str > ())); }
#line 1779 "parser/parser.cpp"
    break;

  case 60: // ident_list: ident_list TOK_COMMA ident
#line 435 "parser/parser_rules.y"
                                   { yystack_[2].value.as < std::vector<Str> > ().push_back(std::move(yystack_[0].value.as < Str > ())); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1785 "parser/parser.cpp"
    break;

  case 61: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 442 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()), combine(yystack_[2].location, yystack_[1].location)); }
#line 1791 "parser/parser.cpp"
    break;

  case 62: // stmt_list: %empty
#line 446 "parser/parser_rules.y"
                              { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1797 "parser/parser.cpp"
    break;

  case 63: // stmt_list: stmt_list stmt
#line 447 "parser/parser_rules.y"
                              { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1803 "parser/parser.cpp"
    break;

  case 64: // stmt: var_decl_stmt
#line 451 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 1809 "parser/parser.cpp"
    break;

  case 65: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 452 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_return_stmt(yystack_[1].value.as < ast::ExprPtr > (), yystack_[2].location); }
#line 1815 "parser/parser.cpp"
    break;

  case 66: // stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt
#line 454 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_if_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::StatementPtr > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1821 "parser/parser.cpp"
    break;

  case 67: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 456 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1827 "parser/parser.cpp"
    break;

  case 68: // stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 458 "parser/parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 1833 "parser/parser.cpp"
    break;

  case 69: // stmt: TOK_BREAK TOK_SMCLN
#line 459 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1839 "parser/parser.cpp"
    break;

  case 70: // stmt: TOK_CONTINUE TOK_SMCLN
#line 460 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1845 "parser/parser.cpp"
    break;

  case 71: // stmt: block
#line 461 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 1851 "parser/parser.cpp"
    break;

  case 72: // stmt: expr TOK_SMCLN
#line 462 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::ExprPtr > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1857 "parser/parser.cpp"
    break;

  case 73: // expr_opt: %empty
#line 471 "parser/parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = nullptr; }
#line 1863 "parser/parser.cpp"
    break;

  case 74: // expr_opt: expr
#line 472 "parser/parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1869 "parser/parser.cpp"
    break;

  case 75: // var_decl_stmt: TOK_LET var_decl
#line 480 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(yystack_[0].value.as < ast::VarDecl* > (), yystack_[0].location); }
#line 1875 "parser/parser.cpp"
    break;

  case 76: // top_decl: TOK_LET var_decl
#line 485 "parser/parser_rules.y"
                          { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::VarDecl* > ()); }
#line 1881 "parser/parser.cpp"
    break;

  case 77: // var_mutability: %empty
#line 489 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Imm; }
#line 1887 "parser/parser.cpp"
    break;

  case 78: // var_mutability: TOK_IMM
#line 490 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Imm; }
#line 1893 "parser/parser.cpp"
    break;

  case 79: // var_mutability: TOK_MUT
#line 491 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Mut; }
#line 1899 "parser/parser.cpp"
    break;

  case 80: // var_decl: type_expr var_mutability ident TOK_SMCLN
#line 496 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[1].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (), yystack_[2].value.as < ast::VarDecl::Mutability > (), combine(yystack_[3].location, yystack_[1].location));
    }
#line 1907 "parser/parser.cpp"
    break;

  case 81: // var_decl: type_expr var_mutability ident TOK_ASSIGN assign TOK_SMCLN
#line 500 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[3].value.as < Str > (), yystack_[5].value.as < ast::TypeExpr* > (), yystack_[4].value.as < ast::VarDecl::Mutability > (), combine(yystack_[5].location, yystack_[1].location));
    }
#line 1915 "parser/parser.cpp"
    break;

  case 82: // expr: assign
#line 509 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1921 "parser/parser.cpp"
    break;

  case 83: // assign: cond
#line 513 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1927 "parser/parser.cpp"
    break;

  case 84: // assign: postfix TOK_ASSIGN assign
#line 514 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*Assign*/AssignOp::Assign, combine(yystack_[2].location, yystack_[0].location)); }
#line 1933 "parser/parser.cpp"
    break;

  case 85: // assign: postfix TOK_PLUS_ASSIGN assign
#line 515 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*AddEq*/AssignOp::Add, combine(yystack_[2].location, yystack_[0].location)); }
#line 1939 "parser/parser.cpp"
    break;

  case 86: // assign: postfix TOK_MIN_ASSIGN assign
#line 516 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*SubEq*/AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 1945 "parser/parser.cpp"
    break;

  case 87: // assign: postfix TOK_MUL_ASSIGN assign
#line 517 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*MulEq*/AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 1951 "parser/parser.cpp"
    break;

  case 88: // assign: postfix TOK_DIV_ASSIGN assign
#line 518 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*DivEq*/AssignOp::Divide, combine(yystack_[2].location, yystack_[0].location)); }
#line 1957 "parser/parser.cpp"
    break;

  case 89: // cond: logic_or
#line 522 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1963 "parser/parser.cpp"
    break;

  case 90: // logic_or: logic_and
#line 526 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1969 "parser/parser.cpp"
    break;

  case 91: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 528 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1975 "parser/parser.cpp"
    break;

  case 92: // logic_and: equality
#line 532 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1981 "parser/parser.cpp"
    break;

  case 93: // logic_and: logic_and TOK_BOOL_AND equality
#line 534 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1987 "parser/parser.cpp"
    break;

  case 94: // equality: relational
#line 538 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1993 "parser/parser.cpp"
    break;

  case 95: // equality: equality TOK_EQUAL relational
#line 540 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1999 "parser/parser.cpp"
    break;

  case 96: // equality: equality TOK_NEQUAL relational
#line 542 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2005 "parser/parser.cpp"
    break;

  case 97: // relational: additive
#line 546 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2011 "parser/parser.cpp"
    break;

  case 98: // relational: relational TOK_LESS additive
#line 547 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2017 "parser/parser.cpp"
    break;

  case 99: // relational: relational TOK_LEQ additive
#line 548 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2023 "parser/parser.cpp"
    break;

  case 100: // relational: relational TOK_GREATER additive
#line 549 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2029 "parser/parser.cpp"
    break;

  case 101: // relational: relational TOK_GEQ additive
#line 550 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2035 "parser/parser.cpp"
    break;

  case 102: // additive: multiplicative
#line 554 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2041 "parser/parser.cpp"
    break;

  case 103: // additive: additive TOK_PLUS multiplicative
#line 555 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2047 "parser/parser.cpp"
    break;

  case 104: // additive: additive TOK_MINUS multiplicative
#line 556 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2053 "parser/parser.cpp"
    break;

  case 105: // multiplicative: unary
#line 560 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2059 "parser/parser.cpp"
    break;

  case 106: // multiplicative: multiplicative TOK_STAR unary
#line 561 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2065 "parser/parser.cpp"
    break;

  case 107: // multiplicative: multiplicative TOK_SLASH unary
#line 562 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2071 "parser/parser.cpp"
    break;

  case 108: // multiplicative: multiplicative TOK_MODULO unary
#line 563 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2077 "parser/parser.cpp"
    break;

  case 109: // unary: TOK_NEG unary
#line 567 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::negation, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2083 "parser/parser.cpp"
    break;

  case 110: // unary: TOK_NEGATION unary
#line 568 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2089 "parser/parser.cpp"
    break;

  case 111: // unary: TOK_INC unary
#line 569 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2095 "parser/parser.cpp"
    break;

  case 112: // unary: TOK_DEC unary
#line 570 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2101 "parser/parser.cpp"
    break;

  case 113: // unary: postfix
#line 571 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 2107 "parser/parser.cpp"
    break;

  case 114: // postfix: primary
#line 575 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2113 "parser/parser.cpp"
    break;

  case 115: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 577 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_call_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2119 "parser/parser.cpp"
    break;

  case 116: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 579 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_index(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2125 "parser/parser.cpp"
    break;

  case 117: // postfix: postfix TOK_DOT ident
#line 581 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_field_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2131 "parser/parser.cpp"
    break;

  case 118: // postfix: postfix TOK_INC
#line 583 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2137 "parser/parser.cpp"
    break;

  case 119: // postfix: postfix TOK_DEC
#line 585 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2143 "parser/parser.cpp"
    break;

  case 120: // arg_list_opt: %empty
#line 589 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::vector<ast::ExprPtr>{}; }
#line 2149 "parser/parser.cpp"
    break;

  case 121: // arg_list_opt: arg_list
#line 590 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::ExprPtr> > ());  }
#line 2155 "parser/parser.cpp"
    break;

  case 122: // arg_list: expr
#line 594 "parser/parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(v); }
#line 2161 "parser/parser.cpp"
    break;

  case 123: // arg_list: arg_list TOK_COMMA expr
#line 595 "parser/parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2167 "parser/parser.cpp"
    break;

  case 124: // arg_list: arg_list TOK_COMMA
#line 596 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2173 "parser/parser.cpp"
    break;

  case 125: // primary: ident
#line 600 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2179 "parser/parser.cpp"
    break;

  case 126: // primary: TOK_INT_LITERAL
#line 601 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_int_literal_expr(yystack_[0].value.as < kl_int > (), yystack_[0].location); }
#line 2185 "parser/parser.cpp"
    break;

  case 127: // primary: TOK_FLOAT_LITERAL
#line 602 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_float_literal_expr(yystack_[0].value.as < kl_float > (), yystack_[0].location); }
#line 2191 "parser/parser.cpp"
    break;

  case 128: // primary: TOK_STRING_LITERAL
#line 603 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2197 "parser/parser.cpp"
    break;

  case 129: // primary: TOK_BOOL_LITERAL
#line 604 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl_bool > (), yystack_[0].location); }
#line 2203 "parser/parser.cpp"
    break;

  case 130: // primary: TOK_LPAR expr TOK_RPAR
#line 605 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[1].value.as < ast::ExprPtr > ()); }
#line 2209 "parser/parser.cpp"
    break;

  case 131: // primary: struct_lit
#line 606 "parser/parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = static_cast<ast::ExprPtr>(yystack_[0].value.as < ast::PathLiteralExpr* > ()); }
#line 2215 "parser/parser.cpp"
    break;

  case 132: // struct_lit: path_type_expr TOK_LCBRA field_inits_opt TOK_RCBRA
#line 611 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathLiteralExpr* > () = ast.mk_obj_literal_expr(yystack_[3].value.as < ast::PathTypeExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2221 "parser/parser.cpp"
    break;

  case 133: // field_inits_opt: %empty
#line 615 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::vector<ast::FieldInitPtr>{}; }
#line 2227 "parser/parser.cpp"
    break;

  case 134: // field_inits_opt: field_inits
#line 616 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2233 "parser/parser.cpp"
    break;

  case 135: // field_inits: field_init
#line 620 "parser/parser_rules.y"
                                         { std::vector<ast::FieldInitPtr> v; v.push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(v); }
#line 2239 "parser/parser.cpp"
    break;

  case 136: // field_inits: field_inits TOK_COMMA field_init
#line 621 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ().push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2245 "parser/parser.cpp"
    break;

  case 137: // field_inits: field_inits TOK_COMMA
#line 622 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2251 "parser/parser.cpp"
    break;

  case 138: // field_init: ident TOK_COLON expr
#line 627 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitPtr > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2257 "parser/parser.cpp"
    break;


#line 2261 "parser/parser.cpp"

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


  const short parser::yypact_ninf_ = -134;

  const signed char parser::yytable_ninf_ = -60;

  const short
  parser::yypact_[] =
  {
      -1,   -31,    35,  -134,  -134,    29,  -134,  -134,    14,  -134,
     -31,   -31,  -134,    21,  -134,    18,    24,    24,   184,  -134,
    -134,  -134,  -134,   -31,  -134,  -134,   -43,     8,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,    -6,     3,  -134,  -134,  -134,  -134,  -134,    20,
    -134,    22,   169,  -134,   184,  -134,  -134,   184,  -134,  -134,
     205,    24,    24,  -134,   184,    30,   169,  -134,   -18,    40,
      39,  -134,   -18,    44,  -134,  -134,  -134,  -134,   205,   205,
     205,   205,   205,    48,    59,    63,  -134,  -134,    46,    45,
     -33,    99,   -17,    31,  -134,   179,  -134,  -134,   -50,  -134,
     -18,  -134,  -134,    79,    77,   184,  -134,    89,  -134,    28,
    -134,  -134,  -134,    24,  -134,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
      24,  -134,  -134,   205,   205,   205,   205,   205,  -134,   205,
      84,  -134,   184,   -25,  -134,  -134,    92,    87,   100,  -134,
      45,   -33,    99,    99,   -17,   -17,   -17,   -17,    31,    31,
    -134,  -134,  -134,  -134,   106,   102,   107,  -134,  -134,  -134,
    -134,  -134,  -134,   104,  -134,    44,  -134,  -134,  -134,   205,
    -134,    24,  -134,   205,  -134,  -134,    57,  -134,  -134,  -134,
     113,   114,   112,   184,   205,   118,   119,  -134,  -134,  -134,
    -134,   140,   205,   205,   194,  -134,   173,  -134,  -134,  -134,
    -134,   181,   182,   186,  -134,   105,   112,   205,  -134,  -134,
     183,   180,  -134
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    11,     0,     9,     1,    12,     4,
       0,     0,     6,     2,    10,     0,     0,     0,     0,    13,
      14,    16,    15,     0,     7,    58,     0,     0,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    54,    77,    34,    35,    36,    37,    59,    52,
      76,     0,    21,    20,    28,    55,    56,     0,    78,    79,
       0,     0,     0,     8,     0,     0,    22,    23,     0,     0,
      29,    30,     0,    57,   126,   127,   128,   129,     0,     0,
       0,     0,     0,     0,   125,     0,    82,    83,    89,    90,
      92,    94,    97,   102,   105,   113,   114,   131,     0,    60,
       0,    19,    24,     0,     0,    32,    33,     0,   110,   113,
     109,   111,   112,   133,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,     0,
       0,   118,   119,     0,     0,     0,     0,     0,    80,     0,
       0,    25,     0,     0,    31,   130,     0,     0,   134,   135,
      91,    93,    95,    96,    98,    99,   100,   101,   103,   104,
     106,   107,   108,   122,     0,   121,     0,   117,    84,    85,
      86,    87,    88,     0,    26,    27,    62,    18,    17,     0,
     132,   137,   115,   124,   116,    81,     0,   138,   136,   123,
       0,     0,     0,     0,    73,     0,     0,    61,    71,    63,
      64,     0,     0,     0,     0,    75,     0,    74,    69,    70,
      72,     0,     0,     0,    65,     0,     0,     0,    66,    67,
       0,     0,    68
  };

  const short
  parser::yypgoto_[] =
  {
    -134,  -134,  -134,  -134,  -134,   228,     2,  -134,  -134,  -134,
    -134,  -134,  -134,   174,  -134,  -134,  -134,   136,   -48,  -134,
     -15,  -134,  -134,  -134,   -16,  -134,  -133,  -134,    27,  -134,
    -134,  -134,  -134,    52,   -55,    -2,  -134,  -134,   131,   132,
     -54,    74,   -52,   -60,    64,  -134,  -134,  -134,  -134,  -134,
    -134,    66
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    12,     5,     6,    13,    19,    20,
      21,    65,    66,    67,   143,    69,    70,    71,    43,    44,
      83,    46,    57,    47,    84,    49,   198,   186,   199,   206,
     200,    22,    61,    50,   201,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,   164,   165,    96,    97,   147,
     148,   149
  };

  const short
  parser::yytable_[] =
  {
      26,    27,    48,    45,    68,    85,    72,   138,    55,    73,
     178,    52,    14,     4,    53,    56,   100,    58,    68,   108,
     110,   111,   112,   107,    59,    51,    25,     1,    16,   176,
     139,    17,   177,    18,    60,     7,    48,    45,    48,    45,
      11,    48,    45,   117,   118,    98,    99,    23,    48,    45,
      48,    45,   103,   123,   124,    60,   106,    72,    54,   204,
     190,   191,   192,   152,   153,   160,   161,   162,    25,   193,
     194,   158,   159,   163,   166,    24,    62,    10,   128,    63,
     129,   195,   196,   219,   140,   101,     9,   130,    10,    48,
      45,   104,   131,   132,   175,   105,    60,   146,   125,   126,
     127,    25,   113,    74,    75,    76,    77,    78,   190,   191,
     192,   176,   197,   -59,   167,   -59,   114,   193,   194,    79,
      80,    81,    82,   116,   187,   115,    48,    45,   189,   195,
     196,   168,   169,   170,   171,   172,   141,   173,   142,   207,
     145,   174,   180,   109,   109,   109,   109,   211,   212,    25,
     179,    74,    75,    76,    77,    78,   181,   182,   183,   176,
     184,   185,   220,   202,   203,   146,   176,    79,    80,    81,
      82,   119,   120,   121,   122,   208,   209,    48,    45,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,    64,   154,   155,   156,   157,   210,   213,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    25,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    25,   128,
     214,   129,   215,   216,   221,    42,   217,   222,   130,    15,
     102,   144,   218,   131,   132,   205,   150,   188,   151,    25,
      42,    74,    75,    76,    77,    78,     0,     0,     0,   133,
     134,   135,   136,   137,     0,     0,     0,    79,    80,    81,
      82
  };

  const short
  parser::yycheck_[] =
  {
      16,    17,    18,    18,    52,    60,    54,    57,    14,    57,
     143,    54,    10,    44,    57,    21,    64,    14,    66,    79,
      80,    81,    82,    78,    21,    23,    44,    28,     7,    54,
      80,    10,    57,    12,    52,     0,    52,    52,    54,    54,
      26,    57,    57,    76,    77,    61,    62,    29,    64,    64,
      66,    66,    68,    70,    71,    52,    72,   105,    50,   192,
       3,     4,     5,   117,   118,   125,   126,   127,    44,    12,
      13,   123,   124,   128,   129,    57,    56,    59,    50,    57,
      52,    24,    25,   216,   100,    55,    57,    59,    59,   105,
     105,    51,    64,    65,   142,    56,    52,   113,    67,    68,
      69,    44,    54,    46,    47,    48,    49,    50,     3,     4,
       5,    54,    55,    54,   130,    56,    53,    12,    13,    62,
      63,    64,    65,    78,   179,    79,   142,   142,   183,    24,
      25,   133,   134,   135,   136,   137,    57,   139,    61,   194,
      51,    57,    55,    79,    80,    81,    82,   202,   203,    44,
      58,    46,    47,    48,    49,    50,    56,    51,    56,    54,
      53,    57,   217,    50,    50,   181,    54,    62,    63,    64,
      65,    72,    73,    74,    75,    57,    57,   193,   193,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    23,   119,   120,   121,   122,    57,     4,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    50,
      57,    52,    51,    51,    51,    66,    50,    57,    59,    11,
      66,   105,   215,    64,    65,   193,   115,   181,   116,    44,
      66,    46,    47,    48,    49,    50,    -1,    -1,    -1,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    62,    63,    64,
      65
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    28,    89,    90,    44,    93,    94,     0,    91,    57,
      59,    26,    92,    95,    94,    93,     7,    10,    12,    96,
      97,    98,   119,    29,    57,    44,   112,   112,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    66,   106,   107,   108,   109,   111,   112,   113,
     121,    94,    54,    57,    50,    14,    21,   110,    14,    21,
      52,   120,    56,    57,    23,    99,   100,   101,   106,   103,
     104,   105,   106,   106,    46,    47,    48,    49,    50,    62,
      63,    64,    65,   108,   112,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   135,   136,   112,   112,
     106,    55,   101,   112,    51,    56,   112,   122,   131,   132,
     131,   131,   131,    54,    53,    79,    78,    76,    77,    72,
      73,    74,    75,    70,    71,    67,    68,    69,    50,    52,
      59,    64,    65,    80,    81,    82,    83,    84,    57,    80,
     112,    57,    61,   102,   105,    51,   112,   137,   138,   139,
     126,   127,   128,   128,   129,   129,   129,   129,   130,   130,
     131,   131,   131,   122,   133,   134,   122,   112,   123,   123,
     123,   123,   123,   123,    57,   106,    54,    57,   114,    58,
      55,    56,    51,    56,    53,    57,   115,   122,   139,   122,
       3,     4,     5,    12,    13,    24,    25,    55,   114,   116,
     118,   122,    50,    50,   114,   121,   117,   122,    57,    57,
      57,   122,   122,     4,    57,    51,    51,    50,   116,   114,
     122,    51,    57
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    88,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   102,   103,   103,
     104,   104,   104,   105,   106,   106,   106,   106,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   109,   110,   110,   110,   111,   112,   113,
     113,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   119,   120,   120,   120,
     121,   121,   122,   123,   123,   123,   123,   123,   123,   124,
     125,   125,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   128,   129,   129,   129,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   132,   132,   132,   132,   132,   132,
     133,   133,   134,   134,   134,   135,   135,   135,   135,   135,
     135,   135,   136,   137,   137,   138,   138,   138,   139
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     1,
       3,     1,     0,     2,     1,     1,     1,     7,     7,     5,
       3,     0,     1,     1,     2,     3,     4,     2,     0,     1,
       1,     3,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     0,     1,     1,     3,     1,     1,
       3,     3,     0,     2,     1,     3,     5,     5,     7,     2,
       2,     1,     2,     0,     1,     2,     2,     0,     1,     1,
       4,     6,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     2,
       2,     2,     2,     1,     1,     4,     4,     3,     2,     2,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       3,     1,     4,     0,     1,     1,     3,     2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_ENUM", "TOK_TRAIT", "TOK_FN",
  "TOK_TYPE", "TOK_LET", "TOK_RETURN", "TOK_IMM", "TOK_INT", "TOK_BIGINT",
  "TOK_MAGICINT", "TOK_DOUBLE", "TOK_VOID", "TOK_STRING", "TOK_MUT",
  "TOK_STATIC", "TOK_PUB", "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT",
  "TOK_EXPORT", "TOK_PACKAGE", "TOK_AS", "TOK_I8", "TOK_U8", "TOK_I16",
  "TOK_U16", "TOK_I32", "TOK_U32", "TOK_I64", "TOK_U64", "TOK_I128",
  "TOK_U128", "TOK_F32", "TOK_F64", "TOK_BOOL", "TOK_CHAR",
  "TOK_IDENTIFIER", "TOK_TYPE_NAME", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA",
  "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON", "TOK_DOT",
  "TOK_QUESTION", "TOK_ARROW", "TOK_NEGATION", "TOK_NEG", "TOK_INC",
  "TOK_DEC", "TOK_AMP", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit",
  "opt_package", "import_list", "import_decl", "names_separated_by_dots",
  "name", "decl_list", "decl", "fn_decl", "struct_decl",
  "field_decl_list_opt", "field_decl_list", "field_decl", "ret_type_expr",
  "param_list_opt", "param_list", "param", "type_expr",
  "builtin_type_expr", "path_type_expr", "array_type_expr",
  "ref_mutability", "ref_type_expr", "ident", "ident_list", "block",
  "stmt_list", "stmt", "expr_opt", "var_decl_stmt", "top_decl",
  "var_mutability", "var_decl", "expr", "assign", "cond", "logic_or",
  "logic_and", "equality", "relational", "additive", "multiplicative",
  "unary", "postfix", "arg_list_opt", "arg_list", "primary", "struct_lit",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   271,   271,   282,   283,   290,   291,   298,   300,   306,
     308,   313,   319,   320,   324,   325,   326,   330,   334,   341,
     343,   348,   349,   353,   354,   358,   360,   365,   369,   370,
     374,   375,   376,   380,   386,   387,   388,   389,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   410,   414,   419,   420,   421,   425,   430,   434,
     435,   441,   446,   447,   451,   452,   453,   455,   457,   459,
     460,   461,   462,   471,   472,   479,   485,   489,   490,   491,
     495,   499,   509,   513,   514,   515,   516,   517,   518,   522,
     526,   527,   532,   533,   538,   539,   541,   546,   547,   548,
     549,   550,   554,   555,   556,   560,   561,   562,   563,   567,
     568,   569,   570,   571,   575,   576,   578,   580,   582,   584,
     589,   590,   594,   595,   596,   600,   601,   602,   603,   604,
     605,   606,   610,   615,   616,   620,   621,   622,   626
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
#line 3054 "parser/parser.cpp"

#line 630 "parser/parser_rules.y"


/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
