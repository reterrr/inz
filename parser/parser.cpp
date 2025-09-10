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
#line 60 "parser_rules.y"

  #include "../lexer/lexer.hpp"   // Scanner definition
  #include "../ast/ast.hpp"       // AST factory class declarations (mk_*)
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.begin.line << ':' << loc.begin.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    (void)scanner.yylex(); // advance; fills current_token_
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

#line 147 "parser.cpp"


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
#line 240 "parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner& scanner_yyarg, ast::AST& ast_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
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

      case symbol_kind::S_decl: // decl
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

      case symbol_kind::S_field_init: // field_init
        value.YY_MOVE_OR_COPY< ast::FieldInitPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.YY_MOVE_OR_COPY< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init_declarator_stmt: // init_declarator_stmt
      case symbol_kind::S_init_declarator_decl: // init_declarator_decl
        value.YY_MOVE_OR_COPY< ast::InitDeclarator* > (YY_MOVE (that.value));
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

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.YY_MOVE_OR_COPY< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.YY_MOVE_OR_COPY< ast::TypeRegion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.YY_MOVE_OR_COPY< ast::TypeSpecifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_qtype_spec: // qtype_spec
        value.YY_MOVE_OR_COPY< ast::TypeWithQual > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.YY_MOVE_OR_COPY< ast::VarDeclStatement* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::DeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldInitPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init_declarator_stmt_list: // init_declarator_stmt_list
      case symbol_kind::S_init_declarator_decl_list: // init_declarator_decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::InitDeclarator*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_decl: // decl
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

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init_declarator_stmt: // init_declarator_stmt
      case symbol_kind::S_init_declarator_decl: // init_declarator_decl
        value.move< ast::InitDeclarator* > (YY_MOVE (that.value));
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

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.move< ast::TypeRegion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.move< ast::TypeSpecifier > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_qtype_spec: // qtype_spec
        value.move< ast::TypeWithQual > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (YY_MOVE (that.value));
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
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::DeclPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitPtr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_init_declarator_stmt_list: // init_declarator_stmt_list
      case symbol_kind::S_init_declarator_decl_list: // init_declarator_decl_list
        value.move< std::vector<ast::InitDeclarator*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_decl: // decl
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

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitPtr > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.copy< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_init_declarator_stmt: // init_declarator_stmt
      case symbol_kind::S_init_declarator_decl: // init_declarator_decl
        value.copy< ast::InitDeclarator* > (that.value);
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

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.copy< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.copy< ast::TypeRegion > (that.value);
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.copy< ast::TypeSpecifier > (that.value);
        break;

      case symbol_kind::S_qtype_spec: // qtype_spec
        value.copy< ast::TypeWithQual > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.copy< ast::VarDeclStatement* > (that.value);
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
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< std::vector<ast::DeclPtr> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitPtr> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_init_declarator_stmt_list: // init_declarator_stmt_list
      case symbol_kind::S_init_declarator_decl_list: // init_declarator_decl_list
        value.copy< std::vector<ast::InitDeclarator*> > (that.value);
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

      case symbol_kind::S_decl: // decl
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

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitPtr > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_init_declarator_stmt: // init_declarator_stmt
      case symbol_kind::S_init_declarator_decl: // init_declarator_decl
        value.move< ast::InitDeclarator* > (that.value);
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

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        value.move< ast::TypePtr > (that.value);
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        value.move< ast::TypeRegion > (that.value);
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        value.move< ast::TypeSpecifier > (that.value);
        break;

      case symbol_kind::S_qtype_spec: // qtype_spec
        value.move< ast::TypeWithQual > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (that.value);
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
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::DeclPtr> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::ExprPtr> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitPtr> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_init_declarator_stmt_list: // init_declarator_stmt_list
      case symbol_kind::S_init_declarator_decl_list: // init_declarator_decl_list
        value.move< std::vector<ast::InitDeclarator*> > (that.value);
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
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_name: // name
      case symbol_kind::S_type_atom: // type_atom
      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Str > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< ast::BlockStatement* > ();
        break;

      case symbol_kind::S_decl: // decl
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

      case symbol_kind::S_field_init: // field_init
        yylhs.value.emplace< ast::FieldInitPtr > ();
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        yylhs.value.emplace< ast::FunctionDecl* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_init_declarator_stmt: // init_declarator_stmt
      case symbol_kind::S_init_declarator_decl: // init_declarator_decl
        yylhs.value.emplace< ast::InitDeclarator* > ();
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

      case symbol_kind::S_ret_type: // ret_type
      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_builtin_type: // builtin_type
        yylhs.value.emplace< ast::TypePtr > ();
        break;

      case symbol_kind::S_type_region_opt: // type_region_opt
        yylhs.value.emplace< ast::TypeRegion > ();
        break;

      case symbol_kind::S_type_specifier_opt: // type_specifier_opt
        yylhs.value.emplace< ast::TypeSpecifier > ();
        break;

      case symbol_kind::S_qtype_spec: // qtype_spec
        yylhs.value.emplace< ast::TypeWithQual > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< ast::VarDecl* > ();
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        yylhs.value.emplace< ast::VarDeclStatement* > ();
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
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< std::vector<ast::DeclPtr> > ();
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        yylhs.value.emplace< std::vector<ast::ExprPtr> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        yylhs.value.emplace< std::vector<ast::FieldInitPtr> > ();
        break;

      case symbol_kind::S_import_list: // import_list
        yylhs.value.emplace< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_init_declarator_stmt_list: // init_declarator_stmt_list
      case symbol_kind::S_init_declarator_decl_list: // init_declarator_decl_list
        yylhs.value.emplace< std::vector<ast::InitDeclarator*> > ();
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
#line 260 "parser_rules.y"
    { yylhs.value.as < ast::ModulePtr > () = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::DeclPtr> > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1380 "parser.cpp"
    break;

  case 3: // opt_package: %empty
#line 266 "parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1386 "parser.cpp"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 268 "parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1392 "parser.cpp"
    break;

  case 5: // import_list: %empty
#line 274 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1398 "parser.cpp"
    break;

  case 6: // import_list: import_list import_decl
#line 276 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1404 "parser.cpp"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 285 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1410 "parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 287 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1416 "parser.cpp"
    break;

  case 9: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 289 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/true,  combine(yystack_[3].location, yystack_[0].location)); }
#line 1422 "parser.cpp"
    break;

  case 10: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 291 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/true,  combine(yystack_[5].location, yystack_[0].location)); }
#line 1428 "parser.cpp"
    break;

  case 11: // names_separated_by_dots: name
#line 297 "parser_rules.y"
    { std::vector<lex::SymId> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1434 "parser.cpp"
    break;

  case 12: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 299 "parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1440 "parser.cpp"
    break;

  case 13: // name: TOK_IDENTIFIER
#line 304 "parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1446 "parser.cpp"
    break;

  case 14: // decl_list: %empty
#line 309 "parser_rules.y"
                                   { yylhs.value.as < std::vector<ast::DeclPtr> > () = std::vector<ast::DeclPtr>{}; }
#line 1452 "parser.cpp"
    break;

  case 15: // decl_list: decl_list decl
#line 310 "parser_rules.y"
                                   { yystack_[1].value.as < std::vector<ast::DeclPtr> > ().push_back(std::move(yystack_[0].value.as < ast::DeclPtr > ())); yylhs.value.as < std::vector<ast::DeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::DeclPtr> > ()); }
#line 1458 "parser.cpp"
    break;

  case 16: // decl: maybe_export fn_decl
#line 314 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1464 "parser.cpp"
    break;

  case 17: // decl: maybe_export var_decl
#line 315 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::VarDecl* > ()); }
#line 1470 "parser.cpp"
    break;

  case 18: // decl: maybe_export
#line 316 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = nullptr; }
#line 1476 "parser.cpp"
    break;

  case 19: // maybe_export: %empty
#line 320 "parser_rules.y"
                  { yylhs.value.as < int > () = 0; }
#line 1482 "parser.cpp"
    break;

  case 20: // maybe_export: TOK_EXPORT
#line 321 "parser_rules.y"
                  { yylhs.value.as < int > () = 1; }
#line 1488 "parser.cpp"
    break;

  case 21: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block
#line 326 "parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (),/*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1496 "parser.cpp"
    break;

  case 22: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN
#line 330 "parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), /*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), nullptr, combine(yystack_[6].location, yystack_[1].location)); /* prototype */
    }
#line 1504 "parser.cpp"
    break;

  case 23: // ret_type: TOK_ARROW type_spec
#line 336 "parser_rules.y"
                                         { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1510 "parser.cpp"
    break;

  case 24: // param_list_opt: %empty
#line 340 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::vector<ast::ParamDeclPtr>{}; }
#line 1516 "parser.cpp"
    break;

  case 25: // param_list_opt: param_list
#line 341 "parser_rules.y"
      { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = yystack_[0].value.as < std::vector<ast::ParamDeclPtr> > (); }
#line 1522 "parser.cpp"
    break;

  case 26: // param_list: param
#line 345 "parser_rules.y"
                                         { std::vector<ast::ParamDeclPtr> v; v.push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(v); }
#line 1528 "parser.cpp"
    break;

  case 27: // param_list: param_list TOK_COMMA param
#line 346 "parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ().push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1534 "parser.cpp"
    break;

  case 28: // param_list: param_list TOK_COMMA
#line 347 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1540 "parser.cpp"
    break;

  case 29: // param: qtype_spec ident
#line 351 "parser_rules.y"
                                          { yylhs.value.as < ast::ParamDeclPtr > () = ast.mk_param_decl(yystack_[0].value.as < Str > (), yystack_[1].value.as < ast::TypeWithQual > ().ty, yystack_[1].value.as < ast::TypeWithQual > ().spec,  combine(yystack_[1].location, yystack_[0].location)); }
#line 1546 "parser.cpp"
    break;

  case 30: // type_specifier_opt: %empty
#line 359 "parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Imm; }
#line 1552 "parser.cpp"
    break;

  case 31: // type_specifier_opt: TOK_MUT
#line 361 "parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Mut; }
#line 1558 "parser.cpp"
    break;

  case 32: // type_region_opt: %empty
#line 366 "parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Auto; }
#line 1564 "parser.cpp"
    break;

  case 33: // type_region_opt: TOK_STATIC
#line 368 "parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Static; }
#line 1570 "parser.cpp"
    break;

  case 34: // qtype_spec: type_specifier_opt type_region_opt type_spec
#line 373 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), yystack_[2].value.as < ast::TypeSpecifier > (), yystack_[1].value.as < ast::TypeRegion > (), yystack_[0].location }; }
#line 1576 "parser.cpp"
    break;

  case 35: // qtype_spec: type_specifier_opt type_spec
#line 375 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), yystack_[1].value.as < ast::TypeSpecifier > (), ast::TypeRegion::Auto, yystack_[0].location }; }
#line 1582 "parser.cpp"
    break;

  case 36: // qtype_spec: type_region_opt type_spec
#line 377 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, yystack_[1].value.as < ast::TypeRegion > (), yystack_[0].location }; }
#line 1588 "parser.cpp"
    break;

  case 37: // qtype_spec: type_spec type_specifier_opt
#line 379 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < ast::TypeSpecifier > (), ast::TypeRegion::Auto, yystack_[1].location }; }
#line 1594 "parser.cpp"
    break;

  case 38: // qtype_spec: type_spec type_region_opt
#line 381 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[1].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, yystack_[0].value.as < ast::TypeRegion > (), yystack_[1].location }; }
#line 1600 "parser.cpp"
    break;

  case 39: // qtype_spec: type_spec
#line 383 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, ast::TypeRegion::Auto, yystack_[0].location }; }
#line 1606 "parser.cpp"
    break;

  case 40: // type_spec: builtin_type
#line 387 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1612 "parser.cpp"
    break;

  case 41: // type_spec: type_path
#line 388 "parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = ast.mk_type_from_path(yystack_[0].value.as < ast::PathTypePtr > (), yystack_[0].location); }
#line 1618 "parser.cpp"
    break;

  case 42: // type_spec: type_spec TOK_LBRACK TOK_INT_LITERAL TOK_RBRACK
#line 390 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = ast.mk_fixed_array_type(yystack_[3].value.as < ast::TypePtr > (), yystack_[1].value.as < kl_int > (), combine(yystack_[3].location, yystack_[1].location)); }
#line 1624 "parser.cpp"
    break;

  case 43: // builtin_type: TOK_INT
#line 394 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Int, yystack_[0].location); }
#line 1630 "parser.cpp"
    break;

  case 44: // builtin_type: TOK_BIGINT
#line 395 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::BigInt, yystack_[0].location); }
#line 1636 "parser.cpp"
    break;

  case 45: // builtin_type: TOK_MAGICINT
#line 396 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::MagicInt, yystack_[0].location); }
#line 1642 "parser.cpp"
    break;

  case 46: // builtin_type: TOK_DOUBLE
#line 397 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Double, yystack_[0].location); }
#line 1648 "parser.cpp"
    break;

  case 47: // builtin_type: TOK_BOOL
#line 398 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Bool, yystack_[0].location); }
#line 1654 "parser.cpp"
    break;

  case 48: // builtin_type: TOK_VOID
#line 399 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Void, yystack_[0].location); }
#line 1660 "parser.cpp"
    break;

  case 49: // builtin_type: TOK_STRING
#line 400 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::String, yystack_[0].location); }
#line 1666 "parser.cpp"
    break;

  case 50: // type_path: type_atom
#line 405 "parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_single(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1672 "parser.cpp"
    break;

  case 51: // type_path: type_path TOK_DOT type_atom
#line 407 "parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_append(yystack_[2].value.as < ast::PathTypePtr > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1678 "parser.cpp"
    break;

  case 52: // type_atom: TOK_TYPE_NAME
#line 411 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1684 "parser.cpp"
    break;

  case 53: // type_atom: TOK_IDENTIFIER
#line 412 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1690 "parser.cpp"
    break;

  case 54: // ident: TOK_IDENTIFIER
#line 416 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1696 "parser.cpp"
    break;

  case 55: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 423 "parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()), combine(yystack_[2].location, yystack_[1].location)); }
#line 1702 "parser.cpp"
    break;

  case 56: // stmt_list: %empty
#line 427 "parser_rules.y"
                              { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1708 "parser.cpp"
    break;

  case 57: // stmt_list: stmt_list stmt
#line 428 "parser_rules.y"
                              { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1714 "parser.cpp"
    break;

  case 58: // stmt: var_decl_stmt
#line 432 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 1720 "parser.cpp"
    break;

  case 59: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 433 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_return_stmt(yystack_[1].value.as < ast::ExprPtr > (), yystack_[2].location); }
#line 1726 "parser.cpp"
    break;

  case 60: // stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt
#line 435 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_if_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::StatementPtr > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1732 "parser.cpp"
    break;

  case 61: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 437 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1738 "parser.cpp"
    break;

  case 62: // stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 439 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 1744 "parser.cpp"
    break;

  case 63: // stmt: TOK_BREAK TOK_SMCLN
#line 440 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1750 "parser.cpp"
    break;

  case 64: // stmt: TOK_CONTINUE TOK_SMCLN
#line 441 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1756 "parser.cpp"
    break;

  case 65: // stmt: block
#line 442 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 1762 "parser.cpp"
    break;

  case 66: // stmt: expr TOK_SMCLN
#line 443 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::ExprPtr > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1768 "parser.cpp"
    break;

  case 67: // expr_opt: %empty
#line 452 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = nullptr; }
#line 1774 "parser.cpp"
    break;

  case 68: // expr_opt: expr
#line 453 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1780 "parser.cpp"
    break;

  case 69: // var_decl_stmt: qtype_spec init_declarator_stmt_list TOK_SMCLN
#line 461 "parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(std::move(yystack_[1].value.as < std::vector<ast::InitDeclarator*> > ()), yystack_[2].value.as < ast::TypeWithQual > ().ty, yystack_[2].value.as < ast::TypeWithQual > ().spec, yystack_[2].value.as < ast::TypeWithQual > ().region, combine(yystack_[2].location, yystack_[0].location)); }
#line 1786 "parser.cpp"
    break;

  case 70: // init_declarator_stmt_list: init_declarator_stmt
#line 466 "parser_rules.y"
    { std::vector<ast::InitDeclarator *> v; v.push_back(std::move(yystack_[0].value.as < ast::InitDeclarator* > ())); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(v); }
#line 1792 "parser.cpp"
    break;

  case 71: // init_declarator_stmt_list: init_declarator_stmt_list TOK_COMMA init_declarator_stmt
#line 468 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ().push_back(std::move(yystack_[0].value.as < ast::InitDeclarator* > ())); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ()); }
#line 1798 "parser.cpp"
    break;

  case 72: // init_declarator_stmt: ident
#line 473 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[0].value.as < Str > (), nullptr, yystack_[0].location); }
#line 1804 "parser.cpp"
    break;

  case 73: // init_declarator_stmt: ident TOK_ASSIGN assign
#line 475 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1810 "parser.cpp"
    break;

  case 74: // var_decl: qtype_spec init_declarator_decl_list TOK_SMCLN
#line 482 "parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(std::move(yystack_[1].value.as < std::vector<ast::InitDeclarator*> > ()), yystack_[2].value.as < ast::TypeWithQual > ().ty, yystack_[2].value.as < ast::TypeWithQual > ().spec, yystack_[2].value.as < ast::TypeWithQual > ().region, combine(yystack_[2].location, yystack_[0].location)); }
#line 1816 "parser.cpp"
    break;

  case 75: // init_declarator_decl_list: init_declarator_decl
#line 487 "parser_rules.y"
    { std::vector<ast::InitDeclarator*> v; v.push_back(yystack_[0].value.as < ast::InitDeclarator* > ()); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(v); }
#line 1822 "parser.cpp"
    break;

  case 76: // init_declarator_decl_list: init_declarator_decl_list TOK_COMMA init_declarator_decl
#line 489 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ().push_back(yystack_[0].value.as < ast::InitDeclarator* > ()); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ()); }
#line 1828 "parser.cpp"
    break;

  case 77: // init_declarator_decl: ident
#line 494 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[0].value.as < Str > (), nullptr, yystack_[0].location); }
#line 1834 "parser.cpp"
    break;

  case 78: // init_declarator_decl: ident TOK_ASSIGN assign
#line 496 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1840 "parser.cpp"
    break;

  case 79: // expr: assign
#line 502 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1846 "parser.cpp"
    break;

  case 80: // assign: cond
#line 506 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1852 "parser.cpp"
    break;

  case 81: // assign: postfix TOK_ASSIGN assign
#line 507 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*Assign*/AssignOp::Assign, combine(yystack_[2].location, yystack_[0].location)); }
#line 1858 "parser.cpp"
    break;

  case 82: // assign: postfix TOK_PLUS_ASSIGN assign
#line 508 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*AddEq*/AssignOp::Add, combine(yystack_[2].location, yystack_[0].location)); }
#line 1864 "parser.cpp"
    break;

  case 83: // assign: postfix TOK_MIN_ASSIGN assign
#line 509 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*SubEq*/AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 1870 "parser.cpp"
    break;

  case 84: // assign: postfix TOK_MUL_ASSIGN assign
#line 510 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*MulEq*/AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 1876 "parser.cpp"
    break;

  case 85: // assign: postfix TOK_DIV_ASSIGN assign
#line 511 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*DivEq*/AssignOp::Divide, combine(yystack_[2].location, yystack_[0].location)); }
#line 1882 "parser.cpp"
    break;

  case 86: // cond: logic_or
#line 515 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1888 "parser.cpp"
    break;

  case 87: // logic_or: logic_and
#line 519 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1894 "parser.cpp"
    break;

  case 88: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 521 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1900 "parser.cpp"
    break;

  case 89: // logic_and: equality
#line 525 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1906 "parser.cpp"
    break;

  case 90: // logic_and: logic_and TOK_BOOL_AND equality
#line 527 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1912 "parser.cpp"
    break;

  case 91: // equality: relational
#line 531 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1918 "parser.cpp"
    break;

  case 92: // equality: equality TOK_EQUAL relational
#line 533 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1924 "parser.cpp"
    break;

  case 93: // equality: equality TOK_NEQUAL relational
#line 535 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1930 "parser.cpp"
    break;

  case 94: // relational: additive
#line 539 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1936 "parser.cpp"
    break;

  case 95: // relational: relational TOK_LESS additive
#line 540 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1942 "parser.cpp"
    break;

  case 96: // relational: relational TOK_LEQ additive
#line 541 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1948 "parser.cpp"
    break;

  case 97: // relational: relational TOK_GREATER additive
#line 542 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1954 "parser.cpp"
    break;

  case 98: // relational: relational TOK_GEQ additive
#line 543 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1960 "parser.cpp"
    break;

  case 99: // additive: multiplicative
#line 547 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1966 "parser.cpp"
    break;

  case 100: // additive: additive TOK_PLUS multiplicative
#line 548 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1972 "parser.cpp"
    break;

  case 101: // additive: additive TOK_MINUS multiplicative
#line 549 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1978 "parser.cpp"
    break;

  case 102: // multiplicative: unary
#line 553 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1984 "parser.cpp"
    break;

  case 103: // multiplicative: multiplicative TOK_STAR unary
#line 554 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1990 "parser.cpp"
    break;

  case 104: // multiplicative: multiplicative TOK_SLASH unary
#line 555 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1996 "parser.cpp"
    break;

  case 105: // multiplicative: multiplicative TOK_MODULO unary
#line 556 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2002 "parser.cpp"
    break;

  case 106: // unary: TOK_NEG unary
#line 560 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::negation, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2008 "parser.cpp"
    break;

  case 107: // unary: TOK_NEGATION unary
#line 561 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2014 "parser.cpp"
    break;

  case 108: // unary: TOK_INC unary
#line 562 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2020 "parser.cpp"
    break;

  case 109: // unary: TOK_DEC unary
#line 563 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2026 "parser.cpp"
    break;

  case 110: // unary: postfix
#line 564 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 2032 "parser.cpp"
    break;

  case 111: // postfix: primary
#line 568 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2038 "parser.cpp"
    break;

  case 112: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 570 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_call_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2044 "parser.cpp"
    break;

  case 113: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 572 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_index(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2050 "parser.cpp"
    break;

  case 114: // postfix: postfix TOK_DOT ident
#line 574 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_field_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2056 "parser.cpp"
    break;

  case 115: // postfix: postfix TOK_INC
#line 576 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2062 "parser.cpp"
    break;

  case 116: // postfix: postfix TOK_DEC
#line 578 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2068 "parser.cpp"
    break;

  case 117: // arg_list_opt: %empty
#line 582 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::vector<ast::ExprPtr>{}; }
#line 2074 "parser.cpp"
    break;

  case 118: // arg_list_opt: arg_list
#line 583 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ExprPtr> > () = yystack_[0].value.as < std::vector<ast::ExprPtr> > (); }
#line 2080 "parser.cpp"
    break;

  case 119: // arg_list: expr
#line 587 "parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(v); }
#line 2086 "parser.cpp"
    break;

  case 120: // arg_list: arg_list TOK_COMMA expr
#line 588 "parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2092 "parser.cpp"
    break;

  case 121: // arg_list: arg_list TOK_COMMA
#line 589 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2098 "parser.cpp"
    break;

  case 122: // primary: ident
#line 593 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2104 "parser.cpp"
    break;

  case 123: // primary: TOK_INT_LITERAL
#line 594 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_int_literal_expr(yystack_[0].value.as < kl_int > (), yystack_[0].location); }
#line 2110 "parser.cpp"
    break;

  case 124: // primary: TOK_FLOAT_LITERAL
#line 595 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_float_literal_expr(yystack_[0].value.as < kl_float > (), yystack_[0].location); }
#line 2116 "parser.cpp"
    break;

  case 125: // primary: TOK_STRING_LITERAL
#line 596 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2122 "parser.cpp"
    break;

  case 126: // primary: TOK_BOOL_LITERAL
#line 597 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl_bool > (), yystack_[0].location); }
#line 2128 "parser.cpp"
    break;

  case 127: // primary: TOK_LPAR expr TOK_RPAR
#line 598 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[1].value.as < ast::ExprPtr > ()); }
#line 2134 "parser.cpp"
    break;

  case 128: // primary: struct_lit
#line 599 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = static_cast<ast::ExprPtr>(yystack_[0].value.as < ast::ObjLiteralExpr* > ()); }
#line 2140 "parser.cpp"
    break;

  case 129: // struct_lit: type_path TOK_LCBRA field_inits_opt TOK_RCBRA
#line 604 "parser_rules.y"
    { yylhs.value.as < ast::ObjLiteralExpr* > () = ast.mk_obj_literal_expr(yystack_[3].value.as < ast::PathTypePtr > (), std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2146 "parser.cpp"
    break;

  case 130: // field_inits_opt: %empty
#line 608 "parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::vector<ast::FieldInitPtr>{}; }
#line 2152 "parser.cpp"
    break;

  case 131: // field_inits_opt: field_inits
#line 609 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = yystack_[0].value.as < std::vector<ast::FieldInitPtr> > (); }
#line 2158 "parser.cpp"
    break;

  case 132: // field_inits: field_init
#line 613 "parser_rules.y"
                                         { std::vector<ast::FieldInitPtr> v; v.push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(v); }
#line 2164 "parser.cpp"
    break;

  case 133: // field_inits: field_inits TOK_COMMA field_init
#line 614 "parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ().push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2170 "parser.cpp"
    break;

  case 134: // field_inits: field_inits TOK_COMMA
#line 615 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2176 "parser.cpp"
    break;

  case 135: // field_init: ident TOK_COLON expr
#line 620 "parser_rules.y"
    { yylhs.value.as < ast::FieldInitPtr > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2182 "parser.cpp"
    break;


#line 2186 "parser.cpp"

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









  const short parser::yypact_ninf_ = -132;

  const signed char parser::yytable_ninf_ = -54;

  const short
  parser::yypact_[] =
  {
       5,    15,    47,  -132,  -132,    -7,  -132,  -132,    40,  -132,
      15,    15,    52,  -132,     8,  -132,    30,    15,  -132,  -132,
     159,    15,  -132,    50,    46,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,   274,   124,    46,
       2,  -132,    35,  -132,  -132,    44,    15,  -132,  -132,    56,
     124,    58,    58,    34,    63,  -132,    80,  -132,  -132,    78,
    -132,    71,   257,    58,   117,    46,  -132,    97,  -132,  -132,
      79,    96,  -132,    46,    -1,  -132,  -132,  -132,  -132,   117,
     117,   117,   117,   117,   -17,  -132,  -132,  -132,    99,   101,
      49,    26,    77,     4,  -132,    -4,  -132,  -132,  -132,  -132,
     122,   257,  -132,   134,  -132,  -132,   262,  -132,  -132,  -132,
      46,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,    46,  -132,  -132,   117,
     117,   117,   117,   117,   124,   -13,  -132,  -132,   128,   142,
     143,  -132,   101,    49,    26,    26,    77,    77,    77,    77,
       4,     4,  -132,  -132,  -132,  -132,   147,   151,   155,  -132,
    -132,  -132,  -132,  -132,  -132,    58,  -132,  -132,  -132,   117,
    -132,    46,  -132,   117,  -132,   182,  -132,  -132,  -132,   172,
     173,   170,   117,   168,   176,  -132,    46,   -17,  -132,  -132,
    -132,   177,   117,   117,   216,   184,  -132,  -132,  -132,   163,
      92,  -132,  -132,   192,   209,   211,  -132,   117,    46,  -132,
     220,   170,   117,  -132,  -132,  -132,  -132,   212,   205,  -132
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    13,     0,    11,     1,    14,     4,
       0,     0,     0,     6,    19,    12,     0,     0,    20,    15,
      18,     0,     7,     0,     0,    43,    44,    45,    46,    47,
      48,    49,    31,    33,    53,    52,    16,     0,     0,     0,
      30,    40,    41,    50,    17,     0,     0,     9,    54,     0,
       0,    35,    36,    77,     0,    75,     0,    37,    38,     0,
       8,     0,    24,    34,     0,     0,    74,     0,    51,    10,
       0,    25,    26,     0,    54,   123,   124,   125,   126,     0,
       0,     0,     0,     0,     0,   122,    78,    80,    86,    87,
      89,    91,    94,    99,   102,   110,   111,   128,    76,    42,
       0,    28,    29,     0,    79,   107,   110,   106,   108,   109,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,    27,   127,     0,     0,
     131,   132,    88,    90,    92,    93,    95,    96,    97,    98,
     100,   101,   103,   104,   105,   119,     0,   118,     0,   114,
      81,    82,    83,    84,    85,    23,    56,    22,    21,     0,
     129,   134,   112,   121,   113,     0,   135,   133,   120,     0,
       0,     0,    67,     0,     0,    55,     0,    41,    65,    57,
      58,     0,     0,     0,     0,     0,    68,    63,    64,    72,
       0,    70,    66,     0,     0,     0,    59,     0,     0,    69,
       0,     0,     0,    73,    71,    60,    61,     0,     0,    62
  };

  const short
  parser::yypgoto_[] =
  {
    -132,  -132,  -132,  -132,  -132,    -2,    -5,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,   156,   218,    36,   -19,   -31,  -132,
     -20,   197,   -14,  -131,  -132,    51,  -132,  -132,  -132,    54,
    -132,  -132,   195,   -76,   -62,  -132,  -132,   152,   153,    45,
     -16,    41,   -69,     7,  -132,  -132,  -132,  -132,  -132,  -132,
      93
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    13,     5,     6,    14,    19,    20,
      36,   135,    70,    71,    72,    37,    38,    73,    40,    41,
      84,    43,    85,   188,   175,   189,   195,   190,   200,   201,
      44,    54,    55,   191,   104,    87,    88,    89,    90,    91,
      92,    93,    94,    95,   156,   157,    96,    97,   139,   140,
     141
  };

  const short
  parser::yytable_[] =
  {
      42,    39,    86,   103,   168,    15,    51,    52,    -2,    16,
      49,   105,   107,   108,   109,    23,    45,    42,    42,    63,
     -53,   -53,   110,    32,    33,    53,   166,    59,   -53,   167,
      42,   124,     1,   125,    18,     9,   -53,    10,   -53,    56,
     126,    61,    42,   -53,     4,   127,   128,     7,   155,   158,
     194,    53,   152,   153,   154,   121,   122,   123,    21,   102,
     129,   130,   131,   132,   133,    11,    12,   160,   161,   162,
     163,   164,    22,    50,    10,    48,    58,    17,    46,    59,
     216,    42,   115,   116,   117,   118,    60,   106,   106,   106,
     106,    62,    47,   176,    10,    56,   138,   178,    64,   146,
     147,   148,   149,   165,    65,    66,   196,    34,    35,   113,
     114,    67,   159,    69,    42,   100,   203,   204,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   119,   120,   208,   209,    99,   217,   101,    25,    26,
      27,    28,    29,    30,    31,   213,    74,    35,    75,    76,
      77,    78,    79,    34,    35,   187,   186,   138,   144,   145,
     150,   151,   111,   112,    80,    81,    82,    83,   134,    24,
     137,   169,   199,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   170,   172,   171,   179,   180,   181,    34,    35,
     187,   186,   173,   174,   199,   182,    25,    26,    27,    28,
      29,    30,    31,    32,    33,   183,   184,   192,   193,   166,
     197,    74,    35,    75,    76,    77,    78,    79,   198,   202,
     205,   166,   185,   179,   180,   181,   206,   207,   210,    80,
      81,    82,    83,   182,    25,    26,    27,    28,    29,    30,
      31,    32,    33,   183,   184,   211,   212,   219,   218,    74,
      35,    75,    76,    77,    78,    79,    68,   136,    57,   166,
      98,   215,   214,   142,   177,   143,     0,    80,    81,    82,
      83,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,     0,     0,     0,     0,     0,    34,    35,    25,    26,
      27,    28,    29,    30,    31,     0,    33,   124,     0,   125,
       0,     0,     0,    34,    35,     0,   126,     0,     0,     0,
       0,   127,   128
  };

  const short
  parser::yycheck_[] =
  {
      20,    20,    64,    79,   135,    10,    37,    38,     0,    11,
      24,    80,    81,    82,    83,    17,    21,    37,    38,    50,
      21,    22,    39,    21,    22,    39,    39,    44,    29,    42,
      50,    35,    27,    37,    26,    42,    37,    44,    39,    37,
      44,    46,    62,    44,    29,    49,    50,     0,   124,   125,
     181,    65,   121,   122,   123,    51,    52,    53,    28,    73,
      64,    65,    66,    67,    68,    25,    26,   129,   130,   131,
     132,   133,    42,    37,    44,    29,    40,    25,    28,    44,
     211,   101,    56,    57,    58,    59,    42,    80,    81,    82,
      83,    35,    42,   169,    44,    37,   110,   173,    64,   115,
     116,   117,   118,   134,    41,    42,   182,    29,    30,    60,
      61,    31,   126,    42,   134,    36,   192,   193,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,    54,    55,    41,    42,    38,   212,    41,    14,    15,
      16,    17,    18,    19,    20,   207,    29,    30,    31,    32,
      33,    34,    35,    29,    30,   175,   175,   171,   113,   114,
     119,   120,    63,    62,    47,    48,    49,    50,    46,    10,
      36,    43,   186,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    40,    36,    41,     3,     4,     5,    29,    30,
     210,   210,    41,    38,   208,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    35,    35,    39,
      42,    29,    30,    31,    32,    33,    34,    35,    42,    42,
       4,    39,    40,     3,     4,     5,    42,    64,    36,    47,
      48,    49,    50,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    36,    35,    42,    36,    29,
      30,    31,    32,    33,    34,    35,    59,   101,    40,    39,
      65,   210,   208,   111,   171,   112,    -1,    47,    48,    49,
      50,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    35,    -1,    37,
      -1,    -1,    -1,    29,    30,    -1,    44,    -1,    -1,    -1,
      -1,    49,    50
  };

  const signed char
  parser::yystos_[] =
  {
       0,    27,    73,    74,    29,    77,    78,     0,    75,    42,
      44,    25,    26,    76,    79,    78,    77,    25,    26,    80,
      81,    28,    42,    77,    10,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    29,    30,    82,    87,    88,    89,
      90,    91,    92,    93,   102,    78,    28,    42,    29,    94,
      88,    90,    90,    94,   103,   104,    37,    87,    88,    44,
      42,    78,    35,    90,    64,    41,    42,    31,    93,    42,
      84,    85,    86,    89,    29,    31,    32,    33,    34,    35,
      47,    48,    49,    50,    92,    94,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   118,   119,   104,    38,
      36,    41,    94,   105,   106,   114,   115,   114,   114,   114,
      39,    63,    62,    60,    61,    56,    57,    58,    59,    54,
      55,    51,    52,    53,    35,    37,    44,    49,    50,    64,
      65,    66,    67,    68,    46,    83,    86,    36,    94,   120,
     121,   122,   109,   110,   111,   111,   112,   112,   112,   112,
     113,   113,   114,   114,   114,   105,   116,   117,   105,    94,
     106,   106,   106,   106,   106,    90,    39,    42,    95,    43,
      40,    41,    36,    41,    38,    96,   105,   122,   105,     3,
       4,     5,    13,    23,    24,    40,    89,    92,    95,    97,
      99,   105,    35,    35,    95,    98,   105,    42,    42,    94,
     100,   101,    42,   105,   105,     4,    42,    64,    41,    42,
      36,    36,    35,   106,   101,    97,    95,   105,    36,    42
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    72,    73,    74,    74,    75,    75,    76,    76,    76,
      76,    77,    77,    78,    79,    79,    80,    80,    80,    81,
      81,    82,    82,    83,    84,    84,    85,    85,    85,    86,
      87,    87,    88,    88,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      92,    92,    93,    93,    94,    95,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    98,    99,
     100,   100,   101,   101,   102,   103,   103,   104,   104,   105,
     106,   106,   106,   106,   106,   106,   107,   108,   108,   109,
     109,   110,   110,   110,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   116,   116,   117,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   119,
     120,   120,   121,   121,   121,   122
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     4,
       6,     1,     3,     1,     0,     2,     2,     2,     1,     0,
       1,     7,     7,     2,     0,     1,     1,     3,     2,     2,
       0,     1,     0,     1,     3,     2,     2,     2,     2,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     0,     2,     1,     3,
       5,     5,     7,     2,     2,     1,     2,     0,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     2,     2,     2,     2,
       1,     1,     4,     4,     3,     2,     2,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       0,     1,     1,     3,     2,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_ENUM", "TOK_TRAIT", "TOK_FN",
  "TOK_TYPE", "TOK_LET", "TOK_RETURN", "TOK_INT", "TOK_BIGINT",
  "TOK_MAGICINT", "TOK_DOUBLE", "TOK_BOOL", "TOK_VOID", "TOK_STRING",
  "TOK_MUT", "TOK_STATIC", "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT",
  "TOK_EXPORT", "TOK_PACKAGE", "TOK_AS", "TOK_IDENTIFIER", "TOK_TYPE_NAME",
  "TOK_INT_LITERAL", "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL",
  "TOK_BOOL_LITERAL", "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK",
  "TOK_LCBRA", "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON",
  "TOK_DOT", "TOK_QUESTION", "TOK_ARROW", "TOK_NEGATION", "TOK_NEG",
  "TOK_INC", "TOK_DEC", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit",
  "opt_package", "import_list", "import_decl", "names_separated_by_dots",
  "name", "decl_list", "decl", "maybe_export", "fn_decl", "ret_type",
  "param_list_opt", "param_list", "param", "type_specifier_opt",
  "type_region_opt", "qtype_spec", "type_spec", "builtin_type",
  "type_path", "type_atom", "ident", "block", "stmt_list", "stmt",
  "expr_opt", "var_decl_stmt", "init_declarator_stmt_list",
  "init_declarator_stmt", "var_decl", "init_declarator_decl_list",
  "init_declarator_decl", "expr", "assign", "cond", "logic_or",
  "logic_and", "equality", "relational", "additive", "multiplicative",
  "unary", "postfix", "arg_list_opt", "arg_list", "primary", "struct_lit",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   259,   259,   266,   267,   274,   275,   284,   286,   288,
     290,   296,   298,   303,   309,   310,   314,   315,   316,   320,
     321,   325,   329,   336,   340,   341,   345,   346,   347,   351,
     359,   360,   366,   367,   372,   374,   376,   378,   380,   382,
     387,   388,   389,   394,   395,   396,   397,   398,   399,   400,
     404,   406,   411,   412,   416,   422,   427,   428,   432,   433,
     434,   436,   438,   440,   441,   442,   443,   452,   453,   460,
     465,   467,   472,   474,   481,   486,   488,   493,   495,   502,
     506,   507,   508,   509,   510,   511,   515,   519,   520,   525,
     526,   531,   532,   534,   539,   540,   541,   542,   543,   547,
     548,   549,   553,   554,   555,   556,   560,   561,   562,   563,
     564,   568,   569,   571,   573,   575,   577,   582,   583,   587,
     588,   589,   593,   594,   595,   596,   597,   598,   599,   603,
     608,   609,   613,   614,   615,   619
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
#line 2685 "parser.cpp"

#line 623 "parser_rules.y"


/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
