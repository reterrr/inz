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
#line 64 "parser_rules.y"

  #include "../lexer/lexer.hpp"   // Scanner definition
  #include "../ast/ast.hpp"       // AST factory class declarations (mk_*)
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.end.line << ':' << loc.end.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    int rc = scanner.yylex(); // advance; fills current_token_

    if (rc == 0) {                            // true EOF
        // Use the last token's end as the EOF location (or synthesize one)
        lex::Loc L = scanner.getCurrentToken().loc_;
        L.begin = L.end;                        // make it a point loc at end
        return yy::parser::make_YYEOF(L);
    }
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

#line 156 "parser.cpp"


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
#line 249 "parser.cpp"

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

      case symbol_kind::S_struct_decl: // struct_decl
        value.YY_MOVE_OR_COPY< ast::StructDecl* > (YY_MOVE (that.value));
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

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (YY_MOVE (that.value));
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

      case symbol_kind::S_struct_decl: // struct_decl
        value.copy< ast::StructDecl* > (that.value);
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

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (that.value);
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

      case symbol_kind::S_struct_decl: // struct_decl
        yylhs.value.emplace< ast::StructDecl* > ();
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
#line 278 "parser_rules.y"
    {
        auto* m = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::DeclPtr> > ()), combine(yystack_[2].location, yystack_[0].location));
        ast.project_add_module(m);
        yylhs.value.as < ast::ModulePtr > () = m;
    }
#line 1459 "parser.cpp"
    break;

  case 3: // opt_package: %empty
#line 288 "parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1465 "parser.cpp"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 290 "parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1471 "parser.cpp"
    break;

  case 5: // import_list: %empty
#line 296 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1477 "parser.cpp"
    break;

  case 6: // import_list: import_list import_decl
#line 298 "parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1483 "parser.cpp"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 307 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1489 "parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 309 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1495 "parser.cpp"
    break;

  case 9: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 311 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/true,  combine(yystack_[3].location, yystack_[0].location)); }
#line 1501 "parser.cpp"
    break;

  case 10: // import_decl: TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 313 "parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/true,  combine(yystack_[5].location, yystack_[0].location)); }
#line 1507 "parser.cpp"
    break;

  case 11: // names_separated_by_dots: name
#line 319 "parser_rules.y"
    { std::vector<lex::SymId> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1513 "parser.cpp"
    break;

  case 12: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 321 "parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1519 "parser.cpp"
    break;

  case 13: // name: TOK_IDENTIFIER
#line 326 "parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1525 "parser.cpp"
    break;

  case 14: // decl_list: %empty
#line 331 "parser_rules.y"
                                   { yylhs.value.as < std::vector<ast::DeclPtr> > () = std::vector<ast::DeclPtr>{}; }
#line 1531 "parser.cpp"
    break;

  case 15: // decl_list: decl_list decl
#line 332 "parser_rules.y"
                                   { yystack_[1].value.as < std::vector<ast::DeclPtr> > ().push_back(std::move(yystack_[0].value.as < ast::DeclPtr > ())); yylhs.value.as < std::vector<ast::DeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::DeclPtr> > ()); }
#line 1537 "parser.cpp"
    break;

  case 16: // decl: maybe_export fn_decl
#line 336 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1543 "parser.cpp"
    break;

  case 17: // decl: maybe_export var_decl
#line 337 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::VarDecl* > ()); }
#line 1549 "parser.cpp"
    break;

  case 18: // decl: maybe_export struct_decl
#line 338 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = static_cast<ast::DeclPtr>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1555 "parser.cpp"
    break;

  case 19: // decl: maybe_export
#line 339 "parser_rules.y"
                              { yylhs.value.as < ast::DeclPtr > () = nullptr; }
#line 1561 "parser.cpp"
    break;

  case 20: // maybe_export: %empty
#line 343 "parser_rules.y"
                  { yylhs.value.as < int > () = 0; }
#line 1567 "parser.cpp"
    break;

  case 21: // maybe_export: TOK_EXPORT
#line 344 "parser_rules.y"
                  { yylhs.value.as < int > () = 1; }
#line 1573 "parser.cpp"
    break;

  case 22: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block
#line 349 "parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (),/*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1581 "parser.cpp"
    break;

  case 23: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN
#line 353 "parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), /*callable type*/ nullptr, std::move(yystack_[3].value.as < std::vector<ast::ParamDeclPtr> > ()), yystack_[1].value.as < ast::TypePtr > (), nullptr, combine(yystack_[6].location, yystack_[1].location)); /* prototype */
    }
#line 1589 "parser.cpp"
    break;

  case 24: // struct_decl: TOK_STRUCT ident TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 359 "parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[3].value.as < Str > (), std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 1595 "parser.cpp"
    break;

  case 25: // struct_decl: TOK_STRUCT ident TOK_SMCLN
#line 361 "parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[1].value.as < Str > (), std::vector<ast::FieldDecl*>{}, combine(yystack_[2].location, yystack_[0].location)); }
#line 1601 "parser.cpp"
    break;

  case 26: // field_decl_list_opt: %empty
#line 365 "parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 1607 "parser.cpp"
    break;

  case 27: // field_decl_list_opt: field_decl_list
#line 366 "parser_rules.y"
      { yylhs.value.as < std::vector<ast::FieldDecl*> > () = yystack_[0].value.as < std::vector<ast::FieldDecl*> > (); }
#line 1613 "parser.cpp"
    break;

  case 28: // field_decl_list: field_decl
#line 370 "parser_rules.y"
                                        { std::vector<ast::FieldDecl*> v; v.push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(v); }
#line 1619 "parser.cpp"
    break;

  case 29: // field_decl_list: field_decl_list field_decl
#line 371 "parser_rules.y"
                                        { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1625 "parser.cpp"
    break;

  case 30: // field_decl: qtype_spec ident TOK_SMCLN
#line 376 "parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypeWithQual > ().ty, yystack_[2].value.as < ast::TypeWithQual > ().spec, false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1631 "parser.cpp"
    break;

  case 31: // field_decl: TOK_PUB qtype_spec ident TOK_SMCLN
#line 378 "parser_rules.y"
        { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[1].value.as < Str > (), yystack_[2].value.as < ast::TypeWithQual > ().ty, yystack_[2].value.as < ast::TypeWithQual > ().spec, true, combine(yystack_[3].location, yystack_[0].location)); }
#line 1637 "parser.cpp"
    break;

  case 32: // ret_type: TOK_ARROW type_spec
#line 382 "parser_rules.y"
                                         { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1643 "parser.cpp"
    break;

  case 33: // param_list_opt: %empty
#line 386 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::vector<ast::ParamDeclPtr>{}; }
#line 1649 "parser.cpp"
    break;

  case 34: // param_list_opt: param_list
#line 387 "parser_rules.y"
      { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = yystack_[0].value.as < std::vector<ast::ParamDeclPtr> > (); }
#line 1655 "parser.cpp"
    break;

  case 35: // param_list: param
#line 391 "parser_rules.y"
                                         { std::vector<ast::ParamDeclPtr> v; v.push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(v); }
#line 1661 "parser.cpp"
    break;

  case 36: // param_list: param_list TOK_COMMA param
#line 392 "parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ().push_back(yystack_[0].value.as < ast::ParamDeclPtr > ()); yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1667 "parser.cpp"
    break;

  case 37: // param_list: param_list TOK_COMMA
#line 393 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDeclPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDeclPtr> > ()); }
#line 1673 "parser.cpp"
    break;

  case 38: // param: qtype_spec ident
#line 397 "parser_rules.y"
                                          { yylhs.value.as < ast::ParamDeclPtr > () = ast.mk_param_decl(yystack_[0].value.as < Str > (), yystack_[1].value.as < ast::TypeWithQual > ().ty, yystack_[1].value.as < ast::TypeWithQual > ().spec,  combine(yystack_[1].location, yystack_[0].location)); }
#line 1679 "parser.cpp"
    break;

  case 39: // type_specifier_opt: %empty
#line 405 "parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Imm; }
#line 1685 "parser.cpp"
    break;

  case 40: // type_specifier_opt: TOK_MUT
#line 407 "parser_rules.y"
    { yylhs.value.as < ast::TypeSpecifier > () = ast::TypeSpecifier::Mut; }
#line 1691 "parser.cpp"
    break;

  case 41: // type_region_opt: %empty
#line 412 "parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Auto; }
#line 1697 "parser.cpp"
    break;

  case 42: // type_region_opt: TOK_STATIC
#line 414 "parser_rules.y"
    { yylhs.value.as < ast::TypeRegion > () = ast::TypeRegion::Static; }
#line 1703 "parser.cpp"
    break;

  case 43: // qtype_spec: type_specifier_opt type_region_opt type_spec
#line 419 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), yystack_[2].value.as < ast::TypeSpecifier > (), yystack_[1].value.as < ast::TypeRegion > (), yystack_[0].location }; }
#line 1709 "parser.cpp"
    break;

  case 44: // qtype_spec: type_specifier_opt type_spec
#line 421 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), yystack_[1].value.as < ast::TypeSpecifier > (), ast::TypeRegion::Auto, yystack_[0].location }; }
#line 1715 "parser.cpp"
    break;

  case 45: // qtype_spec: type_region_opt type_spec
#line 423 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, yystack_[1].value.as < ast::TypeRegion > (), yystack_[0].location }; }
#line 1721 "parser.cpp"
    break;

  case 46: // qtype_spec: type_spec type_specifier_opt
#line 425 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[1].value.as < ast::TypePtr > (), yystack_[0].value.as < ast::TypeSpecifier > (), ast::TypeRegion::Auto, yystack_[1].location }; }
#line 1727 "parser.cpp"
    break;

  case 47: // qtype_spec: type_spec type_region_opt
#line 427 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[1].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, yystack_[0].value.as < ast::TypeRegion > (), yystack_[1].location }; }
#line 1733 "parser.cpp"
    break;

  case 48: // qtype_spec: type_spec
#line 429 "parser_rules.y"
    { yylhs.value.as < ast::TypeWithQual > () = ast::TypeWithQual{ yystack_[0].value.as < ast::TypePtr > (), ast::TypeSpecifier::Imm, ast::TypeRegion::Auto, yystack_[0].location }; }
#line 1739 "parser.cpp"
    break;

  case 49: // type_spec: builtin_type
#line 433 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = yystack_[0].value.as < ast::TypePtr > (); }
#line 1745 "parser.cpp"
    break;

  case 50: // type_spec: type_path
#line 434 "parser_rules.y"
                      { yylhs.value.as < ast::TypePtr > () = ast.mk_type_from_path(yystack_[0].value.as < ast::PathTypePtr > (), yystack_[0].location); }
#line 1751 "parser.cpp"
    break;

  case 51: // type_spec: type_spec TOK_LBRACK TOK_INT_LITERAL TOK_RBRACK
#line 436 "parser_rules.y"
    { yylhs.value.as < ast::TypePtr > () = ast.mk_fixed_array_type(yystack_[3].value.as < ast::TypePtr > (), yystack_[1].value.as < kl_int > (), combine(yystack_[3].location, yystack_[1].location)); }
#line 1757 "parser.cpp"
    break;

  case 52: // builtin_type: TOK_INT
#line 440 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Int, yystack_[0].location); }
#line 1763 "parser.cpp"
    break;

  case 53: // builtin_type: TOK_BIGINT
#line 441 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::BigInt, yystack_[0].location); }
#line 1769 "parser.cpp"
    break;

  case 54: // builtin_type: TOK_MAGICINT
#line 442 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::MagicInt, yystack_[0].location); }
#line 1775 "parser.cpp"
    break;

  case 55: // builtin_type: TOK_DOUBLE
#line 443 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Double, yystack_[0].location); }
#line 1781 "parser.cpp"
    break;

  case 56: // builtin_type: TOK_BOOL
#line 444 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Bool, yystack_[0].location); }
#line 1787 "parser.cpp"
    break;

  case 57: // builtin_type: TOK_VOID
#line 445 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::Void, yystack_[0].location); }
#line 1793 "parser.cpp"
    break;

  case 58: // builtin_type: TOK_STRING
#line 446 "parser_rules.y"
                  { yylhs.value.as < ast::TypePtr > () = ast.mk_builtin_type(ast::BuiltinTy::String, yystack_[0].location); }
#line 1799 "parser.cpp"
    break;

  case 59: // type_path: type_atom
#line 451 "parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_single(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1805 "parser.cpp"
    break;

  case 60: // type_path: type_path TOK_DOT type_atom
#line 453 "parser_rules.y"
    { yylhs.value.as < ast::PathTypePtr > () = ast.mk_type_path_append(yystack_[2].value.as < ast::PathTypePtr > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1811 "parser.cpp"
    break;

  case 61: // type_atom: TOK_TYPE_NAME
#line 457 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1817 "parser.cpp"
    break;

  case 62: // type_atom: TOK_IDENTIFIER
#line 458 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1823 "parser.cpp"
    break;

  case 63: // ident: TOK_IDENTIFIER
#line 462 "parser_rules.y"
                      { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1829 "parser.cpp"
    break;

  case 64: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 469 "parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()), combine(yystack_[2].location, yystack_[1].location)); }
#line 1835 "parser.cpp"
    break;

  case 65: // stmt_list: %empty
#line 473 "parser_rules.y"
                              { yylhs.value.as < std::vector<ast::StatementPtr> > () = std::vector<ast::StatementPtr>{}; }
#line 1841 "parser.cpp"
    break;

  case 66: // stmt_list: stmt_list stmt
#line 474 "parser_rules.y"
                              { yystack_[1].value.as < std::vector<ast::StatementPtr> > ().push_back(std::move(yystack_[0].value.as < ast::StatementPtr > ())); yylhs.value.as < std::vector<ast::StatementPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::StatementPtr> > ()); }
#line 1847 "parser.cpp"
    break;

  case 67: // stmt: var_decl_stmt
#line 478 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 1853 "parser.cpp"
    break;

  case 68: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 479 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_return_stmt(yystack_[1].value.as < ast::ExprPtr > (), yystack_[2].location); }
#line 1859 "parser.cpp"
    break;

  case 69: // stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt
#line 481 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_if_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::StatementPtr > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1865 "parser.cpp"
    break;

  case 70: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 483 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1871 "parser.cpp"
    break;

  case 71: // stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 485 "parser_rules.y"
      { yylhs.value.as < ast::StatementPtr > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::ExprPtr > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 1877 "parser.cpp"
    break;

  case 72: // stmt: TOK_BREAK TOK_SMCLN
#line 486 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1883 "parser.cpp"
    break;

  case 73: // stmt: TOK_CONTINUE TOK_SMCLN
#line 487 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1889 "parser.cpp"
    break;

  case 74: // stmt: block
#line 488 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = static_cast<ast::StatementPtr>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 1895 "parser.cpp"
    break;

  case 75: // stmt: expr TOK_SMCLN
#line 489 "parser_rules.y"
                                          { yylhs.value.as < ast::StatementPtr > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::ExprPtr > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1901 "parser.cpp"
    break;

  case 76: // expr_opt: %empty
#line 498 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = nullptr; }
#line 1907 "parser.cpp"
    break;

  case 77: // expr_opt: expr
#line 499 "parser_rules.y"
                  { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 1913 "parser.cpp"
    break;

  case 78: // var_decl_stmt: var_decl
#line 507 "parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(yystack_[0].value.as < ast::VarDecl* > (), yystack_[0].location); }
#line 1919 "parser.cpp"
    break;

  case 79: // var_decl: qtype_spec init_declarator_decl_list TOK_SMCLN
#line 528 "parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(std::move(yystack_[1].value.as < std::vector<ast::InitDeclarator*> > ()), yystack_[2].value.as < ast::TypeWithQual > ().ty, yystack_[2].value.as < ast::TypeWithQual > ().spec, yystack_[2].value.as < ast::TypeWithQual > ().region, combine(yystack_[2].location, yystack_[0].location)); }
#line 1925 "parser.cpp"
    break;

  case 80: // init_declarator_decl_list: init_declarator_decl
#line 533 "parser_rules.y"
    { std::vector<ast::InitDeclarator*> v; v.push_back(yystack_[0].value.as < ast::InitDeclarator* > ()); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(v); }
#line 1931 "parser.cpp"
    break;

  case 81: // init_declarator_decl_list: init_declarator_decl_list TOK_COMMA init_declarator_decl
#line 535 "parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ().push_back(yystack_[0].value.as < ast::InitDeclarator* > ()); yylhs.value.as < std::vector<ast::InitDeclarator*> > () = std::move(yystack_[2].value.as < std::vector<ast::InitDeclarator*> > ()); }
#line 1937 "parser.cpp"
    break;

  case 82: // init_declarator_decl: ident
#line 540 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[0].value.as < Str > (), nullptr, yystack_[0].location); }
#line 1943 "parser.cpp"
    break;

  case 83: // init_declarator_decl: ident TOK_ASSIGN assign
#line 542 "parser_rules.y"
    { yylhs.value.as < ast::InitDeclarator* > () = ast.mk_var_declarator_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 1949 "parser.cpp"
    break;

  case 84: // expr: assign
#line 548 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1955 "parser.cpp"
    break;

  case 85: // assign: cond
#line 552 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1961 "parser.cpp"
    break;

  case 86: // assign: postfix TOK_ASSIGN assign
#line 553 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*Assign*/AssignOp::Assign, combine(yystack_[2].location, yystack_[0].location)); }
#line 1967 "parser.cpp"
    break;

  case 87: // assign: postfix TOK_PLUS_ASSIGN assign
#line 554 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*AddEq*/AssignOp::Add, combine(yystack_[2].location, yystack_[0].location)); }
#line 1973 "parser.cpp"
    break;

  case 88: // assign: postfix TOK_MIN_ASSIGN assign
#line 555 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*SubEq*/AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 1979 "parser.cpp"
    break;

  case 89: // assign: postfix TOK_MUL_ASSIGN assign
#line 556 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*MulEq*/AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 1985 "parser.cpp"
    break;

  case 90: // assign: postfix TOK_DIV_ASSIGN assign
#line 557 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_assign_expr(yystack_[2].value.as < ast::ExprPtr > (), yystack_[0].value.as < ast::ExprPtr > (), /*DivEq*/AssignOp::Divide, combine(yystack_[2].location, yystack_[0].location)); }
#line 1991 "parser.cpp"
    break;

  case 91: // cond: logic_or
#line 561 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 1997 "parser.cpp"
    break;

  case 92: // logic_or: logic_and
#line 565 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2003 "parser.cpp"
    break;

  case 93: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 567 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2009 "parser.cpp"
    break;

  case 94: // logic_and: equality
#line 571 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2015 "parser.cpp"
    break;

  case 95: // logic_and: logic_and TOK_BOOL_AND equality
#line 573 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2021 "parser.cpp"
    break;

  case 96: // equality: relational
#line 577 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2027 "parser.cpp"
    break;

  case 97: // equality: equality TOK_EQUAL relational
#line 579 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2033 "parser.cpp"
    break;

  case 98: // equality: equality TOK_NEQUAL relational
#line 581 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2039 "parser.cpp"
    break;

  case 99: // relational: additive
#line 585 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2045 "parser.cpp"
    break;

  case 100: // relational: relational TOK_LESS additive
#line 586 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2051 "parser.cpp"
    break;

  case 101: // relational: relational TOK_LEQ additive
#line 587 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2057 "parser.cpp"
    break;

  case 102: // relational: relational TOK_GREATER additive
#line 588 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2063 "parser.cpp"
    break;

  case 103: // relational: relational TOK_GEQ additive
#line 589 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2069 "parser.cpp"
    break;

  case 104: // additive: multiplicative
#line 593 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2075 "parser.cpp"
    break;

  case 105: // additive: additive TOK_PLUS multiplicative
#line 594 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2081 "parser.cpp"
    break;

  case 106: // additive: additive TOK_MINUS multiplicative
#line 595 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2087 "parser.cpp"
    break;

  case 107: // multiplicative: unary
#line 599 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2093 "parser.cpp"
    break;

  case 108: // multiplicative: multiplicative TOK_STAR unary
#line 600 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2099 "parser.cpp"
    break;

  case 109: // multiplicative: multiplicative TOK_SLASH unary
#line 601 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2105 "parser.cpp"
    break;

  case 110: // multiplicative: multiplicative TOK_MODULO unary
#line 602 "parser_rules.y"
                                    { yylhs.value.as < ast::ExprPtr > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move(yystack_[2].value.as < ast::ExprPtr > ()), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2111 "parser.cpp"
    break;

  case 111: // unary: TOK_NEG unary
#line 606 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::negation, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2117 "parser.cpp"
    break;

  case 112: // unary: TOK_NEGATION unary
#line 607 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2123 "parser.cpp"
    break;

  case 113: // unary: TOK_INC unary
#line 608 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2129 "parser.cpp"
    break;

  case 114: // unary: TOK_DEC unary
#line 609 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2135 "parser.cpp"
    break;

  case 115: // unary: postfix
#line 610 "parser_rules.y"
                                      { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[0].value.as < ast::ExprPtr > ()); }
#line 2141 "parser.cpp"
    break;

  case 116: // postfix: primary
#line 614 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = yystack_[0].value.as < ast::ExprPtr > (); }
#line 2147 "parser.cpp"
    break;

  case 117: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 616 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_call_expr(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2153 "parser.cpp"
    break;

  case 118: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 618 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_index(std::move(yystack_[3].value.as < ast::ExprPtr > ()), std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2159 "parser.cpp"
    break;

  case 119: // postfix: postfix TOK_DOT ident
#line 620 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_field_expr(std::move(yystack_[2].value.as < ast::ExprPtr > ()), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2165 "parser.cpp"
    break;

  case 120: // postfix: postfix TOK_INC
#line 622 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2171 "parser.cpp"
    break;

  case 121: // postfix: postfix TOK_DEC
#line 624 "parser_rules.y"
    { yylhs.value.as < ast::ExprPtr > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, std::move(yystack_[1].value.as < ast::ExprPtr > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2177 "parser.cpp"
    break;

  case 122: // arg_list_opt: %empty
#line 628 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::vector<ast::ExprPtr>{}; }
#line 2183 "parser.cpp"
    break;

  case 123: // arg_list_opt: arg_list
#line 629 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::ExprPtr> > () = yystack_[0].value.as < std::vector<ast::ExprPtr> > (); }
#line 2189 "parser.cpp"
    break;

  case 124: // arg_list: expr
#line 633 "parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(v); }
#line 2195 "parser.cpp"
    break;

  case 125: // arg_list: arg_list TOK_COMMA expr
#line 634 "parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::ExprPtr> > ().push_back(std::move(yystack_[0].value.as < ast::ExprPtr > ())); yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2201 "parser.cpp"
    break;

  case 126: // arg_list: arg_list TOK_COMMA
#line 635 "parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::ExprPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::ExprPtr> > ()); }
#line 2207 "parser.cpp"
    break;

  case 127: // primary: ident
#line 639 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2213 "parser.cpp"
    break;

  case 128: // primary: TOK_INT_LITERAL
#line 640 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_int_literal_expr(yystack_[0].value.as < kl_int > (), yystack_[0].location); }
#line 2219 "parser.cpp"
    break;

  case 129: // primary: TOK_FLOAT_LITERAL
#line 641 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_float_literal_expr(yystack_[0].value.as < kl_float > (), yystack_[0].location); }
#line 2225 "parser.cpp"
    break;

  case 130: // primary: TOK_STRING_LITERAL
#line 642 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2231 "parser.cpp"
    break;

  case 131: // primary: TOK_BOOL_LITERAL
#line 643 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl_bool > (), yystack_[0].location); }
#line 2237 "parser.cpp"
    break;

  case 132: // primary: TOK_LPAR expr TOK_RPAR
#line 644 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = std::move(yystack_[1].value.as < ast::ExprPtr > ()); }
#line 2243 "parser.cpp"
    break;

  case 133: // primary: struct_lit
#line 645 "parser_rules.y"
                           { yylhs.value.as < ast::ExprPtr > () = static_cast<ast::ExprPtr>(yystack_[0].value.as < ast::ObjLiteralExpr* > ()); }
#line 2249 "parser.cpp"
    break;

  case 134: // struct_lit: type_path TOK_LCBRA field_inits_opt TOK_RCBRA
#line 650 "parser_rules.y"
    { yylhs.value.as < ast::ObjLiteralExpr* > () = ast.mk_obj_literal_expr(yystack_[3].value.as < ast::PathTypePtr > (), std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2255 "parser.cpp"
    break;

  case 135: // field_inits_opt: %empty
#line 654 "parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::vector<ast::FieldInitPtr>{}; }
#line 2261 "parser.cpp"
    break;

  case 136: // field_inits_opt: field_inits
#line 655 "parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = yystack_[0].value.as < std::vector<ast::FieldInitPtr> > (); }
#line 2267 "parser.cpp"
    break;

  case 137: // field_inits: field_init
#line 659 "parser_rules.y"
                                         { std::vector<ast::FieldInitPtr> v; v.push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(v); }
#line 2273 "parser.cpp"
    break;

  case 138: // field_inits: field_inits TOK_COMMA field_init
#line 660 "parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ().push_back(yystack_[0].value.as < ast::FieldInitPtr > ()); yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2279 "parser.cpp"
    break;

  case 139: // field_inits: field_inits TOK_COMMA
#line 661 "parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::FieldInitPtr> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitPtr> > ()); }
#line 2285 "parser.cpp"
    break;

  case 140: // field_init: ident TOK_COLON expr
#line 666 "parser_rules.y"
    { yylhs.value.as < ast::FieldInitPtr > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::ExprPtr > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2291 "parser.cpp"
    break;


#line 2295 "parser.cpp"

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


  const short parser::yypact_ninf_ = -140;

  const signed char parser::yytable_ninf_ = -63;

  const short
  parser::yypact_[] =
  {
     -11,    16,    63,  -140,  -140,    47,  -140,  -140,   -18,  -140,
      16,    16,    41,  -140,     7,  -140,   -15,    16,  -140,  -140,
     254,    16,  -140,    43,    24,    24,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   308,
     317,    24,    10,  -140,    48,  -140,  -140,    60,    16,  -140,
    -140,    22,    73,   317,    84,    84,    66,    33,  -140,    96,
    -140,  -140,    68,  -140,    89,   272,  -140,   290,    84,   194,
      24,  -140,    99,  -140,  -140,   290,    98,   272,  -140,    24,
     103,   111,  -140,    24,    28,  -140,  -140,  -140,  -140,   194,
     194,   194,   194,   194,    -5,  -140,  -140,  -140,    92,    94,
      23,   -21,    59,    54,  -140,    51,  -140,  -140,  -140,  -140,
      24,  -140,  -140,   115,   112,   290,  -140,   131,  -140,  -140,
      91,  -140,  -140,  -140,    24,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
      24,  -140,  -140,   194,   194,   194,   194,   194,   124,  -140,
     317,    34,  -140,  -140,   129,   133,   140,  -140,    94,    23,
     -21,   -21,    59,    59,    59,    59,    54,    54,  -140,  -140,
    -140,  -140,   146,   142,   156,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,    84,  -140,  -140,  -140,   194,  -140,    24,  -140,
     194,  -140,   130,  -140,  -140,  -140,   162,   163,   160,   194,
     166,   167,  -140,    -5,  -140,  -140,  -140,  -140,   168,   194,
     194,   213,   175,  -140,  -140,  -140,  -140,   182,   195,   197,
    -140,   172,   160,   194,  -140,  -140,   198,   188,  -140
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    13,     0,    11,     1,    14,     4,
       0,     0,     0,     6,    20,    12,     0,     0,    21,    15,
      19,     0,     7,     0,     0,     0,    52,    53,    54,    55,
      56,    57,    58,    40,    42,    62,    61,    16,    18,     0,
       0,     0,    39,    49,    50,    59,    17,     0,     0,     9,
      63,     0,     0,     0,    44,    45,    82,     0,    80,     0,
      46,    47,     0,     8,     0,    26,    25,    33,    43,     0,
       0,    79,     0,    60,    10,     0,     0,    27,    28,     0,
       0,    34,    35,     0,    63,   128,   129,   130,   131,     0,
       0,     0,     0,     0,     0,   127,    83,    85,    91,    92,
      94,    96,    99,   104,   107,   115,   116,   133,    81,    51,
       0,    24,    29,     0,     0,    37,    38,     0,    84,   112,
     115,   111,   113,   114,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,     0,
       0,   120,   121,     0,     0,     0,     0,     0,     0,    30,
       0,     0,    36,   132,     0,     0,   136,   137,    93,    95,
      97,    98,   100,   101,   102,   103,   105,   106,   108,   109,
     110,   124,     0,   123,     0,   119,    86,    87,    88,    89,
      90,    31,    32,    65,    23,    22,     0,   134,   139,   117,
     126,   118,     0,   140,   138,   125,     0,     0,     0,    76,
       0,     0,    64,    50,    74,    66,    67,    78,     0,     0,
       0,     0,     0,    77,    72,    73,    75,     0,     0,     0,
      68,     0,     0,     0,    69,    70,     0,     0,    71
  };

  const short
  parser::yypgoto_[] =
  {
    -140,  -140,  -140,  -140,  -140,    -1,     8,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,   157,  -140,  -140,  -140,   121,   196,
      55,   -54,   -38,  -140,   -20,   177,   -19,  -139,  -140,    19,
    -140,  -140,   217,  -140,   171,   -86,   -65,  -140,  -140,   122,
     120,   -17,   -88,    -8,   -66,   123,  -140,  -140,  -140,  -140,
    -140,  -140,    74
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    13,     5,     6,    14,    19,    20,
      37,    38,    76,    77,    78,   151,    80,    81,    82,    39,
      40,    41,    42,    43,    94,    45,    95,   204,   192,   205,
     212,   206,   207,    57,    58,   208,   118,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   172,   173,   106,   107,
     155,   156,   157
  };

  const short
  parser::yytable_[] =
  {
      44,    54,    55,   117,    96,    51,    52,    -2,    11,    12,
      16,    79,   185,    83,    21,    68,    23,     1,    15,    44,
      44,   110,    56,    79,   119,   121,   122,   123,    22,    47,
      10,    33,    34,    44,    18,   124,   129,   130,   131,   132,
      62,   162,   163,   164,   165,    44,     4,    44,    59,   -62,
     -62,    56,   171,   174,    50,    44,    64,    44,   -62,   211,
     113,    83,    65,     7,   116,    66,   -62,    17,   -62,   168,
     169,   170,    48,   -62,   183,    70,    71,   184,   176,   177,
     178,   179,   180,   225,   127,   128,    49,   138,    10,   139,
       9,   148,    10,    62,    53,    44,   140,    61,    35,    36,
     193,   141,   142,    63,   195,   154,   135,   136,   137,    67,
     160,   161,   182,   213,   133,   134,   143,   144,   145,   146,
     147,   175,    59,   217,   218,   166,   167,   138,    72,   139,
      44,    69,    74,   196,   197,   198,   140,   226,   109,   111,
     114,   141,   142,   199,    26,    27,    28,    29,    30,    31,
      32,    33,    34,   115,   200,   201,   125,   126,   149,   150,
      84,    36,    85,    86,    87,    88,    89,   181,   153,   154,
     183,   202,   203,   186,   187,   196,   197,   198,    90,    91,
      92,    93,   188,   189,   190,   199,    26,    27,    28,    29,
      30,    31,    32,    33,    34,   191,   200,   201,   209,   210,
     183,   203,    84,    36,    85,    86,    87,    88,    89,   214,
     215,   216,   183,   120,   120,   120,   120,   219,   220,   221,
      90,    91,    92,    93,    84,    36,    85,    86,    87,    88,
      89,   228,   222,   223,   112,   227,   152,    46,    60,    73,
     224,   108,    90,    91,    92,    93,   159,   158,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,    24,   194,     0,    25,     0,     0,     0,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    75,     0,     0,     0,     0,
       0,     0,    35,    36,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    26,    27,    28,    29,    30,    31,    32,     0,
      34,    26,    27,    28,    29,    30,    31,    32,    35,    36,
       0,     0,     0,     0,     0,     0,     0,    35,    36
  };

  const short
  parser::yycheck_[] =
  {
      20,    39,    40,    89,    69,    24,    25,     0,    26,    27,
      11,    65,   151,    67,    29,    53,    17,    28,    10,    39,
      40,    75,    41,    77,    90,    91,    92,    93,    43,    21,
      45,    21,    22,    53,    27,    40,    57,    58,    59,    60,
      45,   129,   130,   131,   132,    65,    30,    67,    38,    21,
      22,    70,   138,   139,    30,    75,    48,    77,    30,   198,
      79,   115,    40,     0,    83,    43,    38,    26,    40,   135,
     136,   137,    29,    45,    40,    42,    43,    43,   143,   144,
     145,   146,   147,   222,    61,    62,    43,    36,    45,    38,
      43,   110,    45,    45,    39,   115,    45,    42,    30,    31,
     186,    50,    51,    43,   190,   124,    52,    53,    54,    36,
     127,   128,   150,   199,    55,    56,    65,    66,    67,    68,
      69,   140,    38,   209,   210,   133,   134,    36,    32,    38,
     150,    65,    43,     3,     4,     5,    45,   223,    39,    41,
      37,    50,    51,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    42,    24,    25,    64,    63,    43,    47,
      30,    31,    32,    33,    34,    35,    36,    43,    37,   188,
      40,    41,   192,    44,    41,     3,     4,     5,    48,    49,
      50,    51,    42,    37,    42,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    39,    24,    25,    36,    36,
      40,   221,    30,    31,    32,    33,    34,    35,    36,    43,
      43,    43,    40,    90,    91,    92,    93,     4,    43,    37,
      48,    49,    50,    51,    30,    31,    32,    33,    34,    35,
      36,    43,    37,    36,    77,    37,   115,    20,    42,    62,
     221,    70,    48,    49,    50,    51,   126,   125,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,     7,   188,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    14,    15,    16,    17,    18,    19,    20,    -1,
      22,    14,    15,    16,    17,    18,    19,    20,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31
  };

  const signed char
  parser::yystos_[] =
  {
       0,    28,    74,    75,    30,    78,    79,     0,    76,    43,
      45,    26,    27,    77,    80,    79,    78,    26,    27,    81,
      82,    29,    43,    78,     7,    10,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    30,    31,    83,    84,    92,
      93,    94,    95,    96,    97,    98,   105,    79,    29,    43,
      30,    99,    99,    93,    95,    95,    99,   106,   107,    38,
      92,    93,    45,    43,    79,    40,    43,    36,    95,    65,
      42,    43,    32,    98,    43,    23,    85,    86,    87,    94,
      89,    90,    91,    94,    30,    32,    33,    34,    35,    36,
      48,    49,    50,    51,    97,    99,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   121,   122,   107,    39,
      94,    41,    87,    99,    37,    42,    99,   108,   109,   117,
     118,   117,   117,   117,    40,    64,    63,    61,    62,    57,
      58,    59,    60,    55,    56,    52,    53,    54,    36,    38,
      45,    50,    51,    65,    66,    67,    68,    69,    99,    43,
      47,    88,    91,    37,    99,   123,   124,   125,   112,   113,
     114,   114,   115,   115,   115,   115,   116,   116,   117,   117,
     117,   108,   119,   120,   108,    99,   109,   109,   109,   109,
     109,    43,    95,    40,    43,   100,    44,    41,    42,    37,
      42,    39,   101,   108,   125,   108,     3,     4,     5,    13,
      24,    25,    41,    97,   100,   102,   104,   105,   108,    36,
      36,   100,   103,   108,    43,    43,    43,   108,   108,     4,
      43,    37,    37,    36,   102,   100,   108,    37,    43
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    78,    78,    79,    80,    80,    81,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    87,    88,    89,    89,    90,    90,    90,    91,    92,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    97,
      97,    98,    98,    99,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   104,   105,
     106,   106,   107,   107,   108,   109,   109,   109,   109,   109,
     109,   110,   111,   111,   112,   112,   113,   113,   113,   114,
     114,   114,   114,   114,   115,   115,   115,   116,   116,   116,
     116,   117,   117,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   119,   119,   120,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   122,   123,   123,   124,   124,   124,
     125
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     4,
       6,     1,     3,     1,     0,     2,     2,     2,     2,     1,
       0,     1,     7,     7,     5,     3,     0,     1,     1,     2,
       3,     4,     2,     0,     1,     1,     3,     2,     2,     0,
       1,     0,     1,     3,     2,     2,     2,     2,     1,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     0,     2,     1,     3,     5,
       5,     7,     2,     2,     1,     2,     0,     1,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     3,     3,     3,
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
  "qtype_spec", "type_spec", "builtin_type", "type_path", "type_atom",
  "ident", "block", "stmt_list", "stmt", "expr_opt", "var_decl_stmt",
  "var_decl", "init_declarator_decl_list", "init_declarator_decl", "expr",
  "assign", "cond", "logic_or", "logic_and", "equality", "relational",
  "additive", "multiplicative", "unary", "postfix", "arg_list_opt",
  "arg_list", "primary", "struct_lit", "field_inits_opt", "field_inits",
  "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   277,   277,   288,   289,   296,   297,   306,   308,   310,
     312,   318,   320,   325,   331,   332,   336,   337,   338,   339,
     343,   344,   348,   352,   358,   360,   365,   366,   370,   371,
     375,   377,   382,   386,   387,   391,   392,   393,   397,   405,
     406,   412,   413,   418,   420,   422,   424,   426,   428,   433,
     434,   435,   440,   441,   442,   443,   444,   445,   446,   450,
     452,   457,   458,   462,   468,   473,   474,   478,   479,   480,
     482,   484,   486,   487,   488,   489,   498,   499,   506,   527,
     532,   534,   539,   541,   548,   552,   553,   554,   555,   556,
     557,   561,   565,   566,   571,   572,   577,   578,   580,   585,
     586,   587,   588,   589,   593,   594,   595,   599,   600,   601,
     602,   606,   607,   608,   609,   610,   614,   615,   617,   619,
     621,   623,   628,   629,   633,   634,   635,   639,   640,   641,
     642,   643,   644,   645,   649,   654,   655,   659,   660,   661,
     665
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
#line 3103 "parser.cpp"

#line 669 "parser_rules.y"


/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
