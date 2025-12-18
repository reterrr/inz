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
#line 37 "parser/parser_rules.y"

  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.end.line << ':' << loc.end.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    scanner.yylex();

    const lex::Token& t = scanner.getCurrentToken();
    const lex::Loc   L  = t.loc_;

    using T = lex::Type;
    switch (t.type_) {
      // payload-bearing
      case T::TOK_IDENTIFIER:     return yy::parser::make_TOK_IDENTIFIER(t.u_.sym, L);
      case T::TOK_INT_LITERAL:    return yy::parser::make_TOK_INT_LITERAL(t.u_.sym, L);
      case T::TOK_FLOAT_LITERAL:  return yy::parser::make_TOK_FLOAT_LITERAL(t.u_.sym, L);
      case T::TOK_STRING_LITERAL: return yy::parser::make_TOK_STRING_LITERAL(t.u_.sym, L);
      case T::TOK_BOOL_LITERAL:   return yy::parser::make_TOK_BOOL_LITERAL(t.u_.boolean, L);
      case T::TOK_CHAR_LITERAL:   return yy::parser::make_TOK_CHAR_LITERAL(t.u_.ch, L);

      // keywords
      case T::TOK_IF:       return yy::parser::make_TOK_IF(L);
      case T::TOK_ELSE:     return yy::parser::make_TOK_ELSE(L);
      case T::TOK_WHILE:    return yy::parser::make_TOK_WHILE(L);
      case T::TOK_DO:       return yy::parser::make_TOK_DO(L);
      case T::TOK_FN:       return yy::parser::make_TOK_FN(L);
      case T::TOK_RETURN:   return yy::parser::make_TOK_RETURN(L);
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
      case T::TOK_IMM:      return yy::parser::make_TOK_IMM(L);
      case T::TOK_STATIC:   return yy::parser::make_TOK_STATIC(L);
      case T::TOK_BREAK:    return yy::parser::make_TOK_BREAK(L);
      case T::TOK_CONTINUE: return yy::parser::make_TOK_CONTINUE(L);

      // builtin type keywords
      case T::TOK_I8:   return yy::parser::make_TOK_I8(L);
      case T::TOK_U8:   return yy::parser::make_TOK_U8(L);
      case T::TOK_I16:  return yy::parser::make_TOK_I16(L);
      case T::TOK_U16:  return yy::parser::make_TOK_U16(L);
      case T::TOK_I32:  return yy::parser::make_TOK_I32(L);
      case T::TOK_U32:  return yy::parser::make_TOK_U32(L);
      case T::TOK_I64:  return yy::parser::make_TOK_I64(L);
      case T::TOK_U64:  return yy::parser::make_TOK_U64(L);
      case T::TOK_I128: return yy::parser::make_TOK_I128(L);
      case T::TOK_U128: return yy::parser::make_TOK_U128(L);
      case T::TOK_F32:  return yy::parser::make_TOK_F32(L);
      case T::TOK_F64:  return yy::parser::make_TOK_F64(L);
      case T::TOK_BOOL: return yy::parser::make_TOK_BOOL(L);
      case T::TOK_CHAR: return yy::parser::make_TOK_CHAR(L);

      // punct
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

      // operators
      case T::TOK_AMP:         return yy::parser::make_TOK_AMP(L);
      case T::TOK_INC:         return yy::parser::make_TOK_INC(L);
      case T::TOK_DEC:         return yy::parser::make_TOK_DEC(L);
      case T::TOK_NEGATION:    return yy::parser::make_TOK_NEGATION(L);
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

      // EOF / unknown
      case T::TOK_END:      return yy::parser::make_YYEOF(L);
      case T::TOK_UNKNOWN:  return yy::parser::make_YYUNDEF(L);
      default:              return yy::parser::make_YYUNDEF(L);
    }
  }

  static inline lex::Loc combine(const lex::Loc& a, const lex::Loc& b) {
    lex::Loc L; L.begin = a.begin; L.end = b.end; return L;
  }

#line 159 "parser/parser.cpp"


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
#line 252 "parser/parser.cpp"

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
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
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
        value.YY_MOVE_OR_COPY< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.YY_MOVE_OR_COPY< ast::ElseIfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.YY_MOVE_OR_COPY< ast::ElseStatement* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.YY_MOVE_OR_COPY< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.YY_MOVE_OR_COPY< ast::FieldInitExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.YY_MOVE_OR_COPY< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.YY_MOVE_OR_COPY< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.YY_MOVE_OR_COPY< ast::Module* > (YY_MOVE (that.value));
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

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.YY_MOVE_OR_COPY< ast::RefTypeExpr::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< ast::Statement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.YY_MOVE_OR_COPY< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.YY_MOVE_OR_COPY< ast::StructLiteralExpr* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< kl::rt::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.YY_MOVE_OR_COPY< kl::rt::character > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.YY_MOVE_OR_COPY< std::optional<kl::rt::FloatKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.YY_MOVE_OR_COPY< std::optional<kl::rt::IntKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ElseIfStatement*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.YY_MOVE_OR_COPY< std::vector<ast::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.YY_MOVE_OR_COPY< std::vector<ast::FieldInitExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<ast::Statement*> > (YY_MOVE (that.value));
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
        value.move< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (YY_MOVE (that.value));
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
        value.move< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::Module* > (YY_MOVE (that.value));
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

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::RefTypeExpr::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::Statement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::StructLiteralExpr* > (YY_MOVE (that.value));
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
        value.move< kl::rt::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.move< std::optional<kl::rt::FloatKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.move< std::optional<kl::rt::IntKind> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::Decl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.move< std::vector<ast::ElseIfStatement*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::Expr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (YY_MOVE (that.value));
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
        value.copy< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_elseif: // elseif
        value.copy< ast::ElseIfStatement* > (that.value);
        break;

      case symbol_kind::S_else_part: // else_part
        value.copy< ast::ElseStatement* > (that.value);
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
        value.copy< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitExpr* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.copy< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.copy< ast::Module* > (that.value);
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

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.copy< ast::RefTypeExpr::Mutability > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< ast::Statement* > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.copy< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.copy< ast::StructLiteralExpr* > (that.value);
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
        value.copy< kl::rt::boolean > (that.value);
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.copy< kl::rt::character > (that.value);
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.copy< std::optional<kl::rt::FloatKind> > (that.value);
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.copy< std::optional<kl::rt::IntKind> > (that.value);
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< std::vector<ast::Decl*> > (that.value);
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.copy< std::vector<ast::ElseIfStatement*> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.copy< std::vector<ast::Expr*> > (that.value);
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.copy< std::vector<ast::FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.copy< std::vector<ast::FieldInitExpr*> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<ast::Statement*> > (that.value);
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
        value.move< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (that.value);
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (that.value);
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
        value.move< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        value.move< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        value.move< ast::Module* > (that.value);
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

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::RefTypeExpr::Mutability > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< ast::Statement* > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        value.move< ast::StructDecl* > (that.value);
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        value.move< ast::StructLiteralExpr* > (that.value);
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
        value.move< kl::rt::boolean > (that.value);
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        value.move< kl::rt::character > (that.value);
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        value.move< std::optional<kl::rt::FloatKind> > (that.value);
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        value.move< std::optional<kl::rt::IntKind> > (that.value);
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<ast::Decl*> > (that.value);
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        value.move< std::vector<ast::ElseIfStatement*> > (that.value);
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        value.move< std::vector<ast::Expr*> > (that.value);
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< std::vector<ast::FieldDecl*> > (that.value);
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        value.move< std::vector<ast::FieldInitExpr*> > (that.value);
        break;

      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (that.value);
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
        yylhs.value.emplace< ast::Decl* > ();
        break;

      case symbol_kind::S_elseif: // elseif
        yylhs.value.emplace< ast::ElseIfStatement* > ();
        break;

      case symbol_kind::S_else_part: // else_part
        yylhs.value.emplace< ast::ElseStatement* > ();
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
        yylhs.value.emplace< ast::Expr* > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        yylhs.value.emplace< ast::FieldDecl* > ();
        break;

      case symbol_kind::S_field_init: // field_init
        yylhs.value.emplace< ast::FieldInitExpr* > ();
        break;

      case symbol_kind::S_fn_decl: // fn_decl
        yylhs.value.emplace< ast::FunctionDecl* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        yylhs.value.emplace< ast::IfStatement* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
        yylhs.value.emplace< ast::Module* > ();
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

      case symbol_kind::S_ref_mutability: // ref_mutability
        yylhs.value.emplace< ast::RefTypeExpr::Mutability > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< ast::Statement* > ();
        break;

      case symbol_kind::S_struct_decl: // struct_decl
        yylhs.value.emplace< ast::StructDecl* > ();
        break;

      case symbol_kind::S_struct_lit: // struct_lit
        yylhs.value.emplace< ast::StructLiteralExpr* > ();
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
        yylhs.value.emplace< kl::rt::boolean > ();
        break;

      case symbol_kind::S_TOK_CHAR_LITERAL: // TOK_CHAR_LITERAL
        yylhs.value.emplace< kl::rt::character > ();
        break;

      case symbol_kind::S_float_literal_type_opt: // float_literal_type_opt
        yylhs.value.emplace< std::optional<kl::rt::FloatKind> > ();
        break;

      case symbol_kind::S_int_literal_type_opt: // int_literal_type_opt
        yylhs.value.emplace< std::optional<kl::rt::IntKind> > ();
        break;

      case symbol_kind::S_opt_package: // opt_package
      case symbol_kind::S_names_separated_by_dots: // names_separated_by_dots
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< std::vector<ast::Decl*> > ();
        break;

      case symbol_kind::S_elseif_list: // elseif_list
        yylhs.value.emplace< std::vector<ast::ElseIfStatement*> > ();
        break;

      case symbol_kind::S_arg_list_opt: // arg_list_opt
      case symbol_kind::S_arg_list: // arg_list
        yylhs.value.emplace< std::vector<ast::Expr*> > ();
        break;

      case symbol_kind::S_field_decl_list_opt: // field_decl_list_opt
      case symbol_kind::S_field_decl_list: // field_decl_list
        yylhs.value.emplace< std::vector<ast::FieldDecl*> > ();
        break;

      case symbol_kind::S_field_inits_opt: // field_inits_opt
      case symbol_kind::S_field_inits: // field_inits
        yylhs.value.emplace< std::vector<ast::FieldInitExpr*> > ();
        break;

      case symbol_kind::S_import_list: // import_list
        yylhs.value.emplace< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<ast::ParamDecl*> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<ast::Statement*> > ();
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
#line 265 "parser/parser_rules.y"
    {
        auto* m = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[2].location, yystack_[0].location));
        ast.project_add_module(m);
        yylhs.value.as < ast::Module* > () = m;
    }
#line 1557 "parser/parser.cpp"
    break;

  case 3: // opt_package: %empty
#line 275 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1563 "parser/parser.cpp"
    break;

  case 4: // opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN
#line 277 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1569 "parser/parser.cpp"
    break;

  case 5: // import_list: %empty
#line 283 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1575 "parser/parser.cpp"
    break;

  case 6: // import_list: import_list import_decl
#line 285 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1581 "parser/parser.cpp"
    break;

  case 7: // import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN
#line 292 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1587 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
#line 294 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<lex::SymId>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1593 "parser/parser.cpp"
    break;

  case 9: // path_expr: names_separated_by_dots
#line 298 "parser/parser_rules.y"
                                { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1599 "parser/parser.cpp"
    break;

  case 10: // names_separated_by_dots: name
#line 304 "parser/parser_rules.y"
    { std::vector<lex::SymId> v; v.push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(v); }
#line 1605 "parser/parser.cpp"
    break;

  case 11: // names_separated_by_dots: names_separated_by_dots TOK_DOT name
#line 306 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1611 "parser/parser.cpp"
    break;

  case 12: // name: TOK_IDENTIFIER
#line 311 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1617 "parser/parser.cpp"
    break;

  case 13: // decl_list: %empty
#line 316 "parser/parser_rules.y"
                                   { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 1623 "parser/parser.cpp"
    break;

  case 14: // decl_list: decl_list decl
#line 317 "parser/parser_rules.y"
                                   { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(std::move(yystack_[0].value.as < ast::Decl* > ())); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 1629 "parser/parser.cpp"
    break;

  case 15: // decl: fn_decl
#line 321 "parser/parser_rules.y"
                 { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1635 "parser/parser.cpp"
    break;

  case 16: // decl: struct_decl
#line 322 "parser/parser_rules.y"
                 { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1641 "parser/parser.cpp"
    break;

  case 17: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr block
#line 327 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1649 "parser/parser.cpp"
    break;

  case 18: // fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 331 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), nullptr, combine(yystack_[6].location, yystack_[1].location)); /* prototype */
    }
#line 1657 "parser/parser.cpp"
    break;

  case 19: // struct_decl: TOK_STRUCT ident TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 338 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[3].value.as < Str > (), std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 1663 "parser/parser.cpp"
    break;

  case 20: // struct_decl: TOK_STRUCT ident TOK_SMCLN
#line 340 "parser/parser_rules.y"
      { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[1].value.as < Str > (), std::vector<ast::FieldDecl*>{}, combine(yystack_[2].location, yystack_[0].location)); }
#line 1669 "parser/parser.cpp"
    break;

  case 21: // field_decl_list_opt: %empty
#line 344 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 1675 "parser/parser.cpp"
    break;

  case 22: // field_decl_list_opt: field_decl_list
#line 345 "parser/parser_rules.y"
                                        { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1681 "parser/parser.cpp"
    break;

  case 23: // field_decl_list: field_decl
#line 349 "parser/parser_rules.y"
                                        { std::vector<ast::FieldDecl*> v; v.push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(v); }
#line 1687 "parser/parser.cpp"
    break;

  case 24: // field_decl_list: field_decl_list field_decl
#line 350 "parser/parser_rules.y"
                                        { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 1693 "parser/parser.cpp"
    break;

  case 25: // field_decl: ident TOK_COLON type_expr TOK_SMCLN
#line 355 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Priv, combine(yystack_[3].location, yystack_[0].location)); }
#line 1699 "parser/parser.cpp"
    break;

  case 26: // field_decl: TOK_PUB ident TOK_COLON type_expr TOK_SMCLN
#line 357 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Publ, combine(yystack_[4].location, yystack_[0].location)); }
#line 1705 "parser/parser.cpp"
    break;

  case 27: // ret_type_expr: TOK_ARROW type_expr
#line 361 "parser/parser_rules.y"
                                         { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 1711 "parser/parser.cpp"
    break;

  case 28: // param_list_opt: %empty
#line 365 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 1717 "parser/parser.cpp"
    break;

  case 29: // param_list_opt: param_list
#line 366 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1723 "parser/parser.cpp"
    break;

  case 30: // param_list: param
#line 370 "parser/parser_rules.y"
                                         { std::vector<ast::ParamDecl*> v; v.push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(v); }
#line 1729 "parser/parser.cpp"
    break;

  case 31: // param_list: param_list TOK_COMMA param
#line 371 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1735 "parser/parser.cpp"
    break;

  case 32: // param_list: param_list TOK_COMMA
#line 372 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 1741 "parser/parser.cpp"
    break;

  case 33: // param: ident TOK_COLON type_expr
#line 377 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1747 "parser/parser.cpp"
    break;

  case 34: // type_expr: builtin_type_expr
#line 383 "parser/parser_rules.y"
                           { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 1753 "parser/parser.cpp"
    break;

  case 35: // type_expr: path_type_expr
#line 384 "parser/parser_rules.y"
                          { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 1759 "parser/parser.cpp"
    break;

  case 36: // type_expr: array_type_expr
#line 385 "parser/parser_rules.y"
                     { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::ArrayTypeExpr* > ()); }
#line 1765 "parser/parser.cpp"
    break;

  case 37: // type_expr: ref_type_expr
#line 386 "parser/parser_rules.y"
                      { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 1771 "parser/parser.cpp"
    break;

  case 38: // builtin_type_expr: TOK_I8
#line 390 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 1777 "parser/parser.cpp"
    break;

  case 39: // builtin_type_expr: TOK_U8
#line 391 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 1783 "parser/parser.cpp"
    break;

  case 40: // builtin_type_expr: TOK_I16
#line 392 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 1789 "parser/parser.cpp"
    break;

  case 41: // builtin_type_expr: TOK_U16
#line 393 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 1795 "parser/parser.cpp"
    break;

  case 42: // builtin_type_expr: TOK_I32
#line 394 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 1801 "parser/parser.cpp"
    break;

  case 43: // builtin_type_expr: TOK_U32
#line 395 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 1807 "parser/parser.cpp"
    break;

  case 44: // builtin_type_expr: TOK_I64
#line 396 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 1813 "parser/parser.cpp"
    break;

  case 45: // builtin_type_expr: TOK_U64
#line 397 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 1819 "parser/parser.cpp"
    break;

  case 46: // builtin_type_expr: TOK_I128
#line 398 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 1825 "parser/parser.cpp"
    break;

  case 47: // builtin_type_expr: TOK_U128
#line 399 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 1831 "parser/parser.cpp"
    break;

  case 48: // builtin_type_expr: TOK_F32
#line 400 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 1837 "parser/parser.cpp"
    break;

  case 49: // builtin_type_expr: TOK_F64
#line 401 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 1843 "parser/parser.cpp"
    break;

  case 50: // builtin_type_expr: TOK_BOOL
#line 402 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 1849 "parser/parser.cpp"
    break;

  case 51: // builtin_type_expr: TOK_CHAR
#line 403 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 1855 "parser/parser.cpp"
    break;

  case 52: // path_type_expr: path_expr
#line 407 "parser/parser_rules.y"
                   { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[0].value.as < ast::PathExpr* > (), yystack_[0].location); }
#line 1861 "parser/parser.cpp"
    break;

  case 53: // array_type_expr: type_expr TOK_LBRACK expr TOK_RBRACK
#line 412 "parser/parser_rules.y"
    { yylhs.value.as < ast::ArrayTypeExpr* > () = ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[1].location)); }
#line 1867 "parser/parser.cpp"
    break;

  case 54: // ref_mutability: %empty
#line 416 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 1873 "parser/parser.cpp"
    break;

  case 55: // ref_mutability: TOK_IMM
#line 417 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 1879 "parser/parser.cpp"
    break;

  case 56: // ref_mutability: TOK_MUT
#line 418 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Mut; }
#line 1885 "parser/parser.cpp"
    break;

  case 57: // ref_type_expr: TOK_AMP ref_mutability type_expr
#line 423 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::RefTypeExpr::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 1891 "parser/parser.cpp"
    break;

  case 58: // ident: TOK_IDENTIFIER
#line 427 "parser/parser_rules.y"
                        { yylhs.value.as < Str > () = std::move(yystack_[0].value.as < Str > ()); }
#line 1897 "parser/parser.cpp"
    break;

  case 59: // block: TOK_LCBRA stmt_list TOK_RCBRA
#line 439 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), combine(yystack_[2].location, yystack_[1].location)); }
#line 1903 "parser/parser.cpp"
    break;

  case 60: // stmt_list: %empty
#line 443 "parser/parser_rules.y"
                              { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{}; }
#line 1909 "parser/parser.cpp"
    break;

  case 61: // stmt_list: stmt_list stmt
#line 444 "parser/parser_rules.y"
                              { yystack_[1].value.as < std::vector<ast::Statement*> > ().push_back(std::move(yystack_[0].value.as < ast::Statement* > ())); yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()); }
#line 1915 "parser/parser.cpp"
    break;

  case 62: // stmt: var_decl_stmt
#line 448 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 1921 "parser/parser.cpp"
    break;

  case 63: // stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 449 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = ast.mk_return_stmt(yystack_[1].value.as < ast::Expr* > (), yystack_[2].location); }
#line 1927 "parser/parser.cpp"
    break;

  case 64: // stmt: if_stmt
#line 451 "parser/parser_rules.y"
      { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::IfStatement* > ()); }
#line 1933 "parser/parser.cpp"
    break;

  case 65: // stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 453 "parser/parser_rules.y"
      { yylhs.value.as < ast::Statement* > () = ast.mk_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 1939 "parser/parser.cpp"
    break;

  case 66: // stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 455 "parser/parser_rules.y"
      { yylhs.value.as < ast::Statement* > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 1945 "parser/parser.cpp"
    break;

  case 67: // stmt: TOK_BREAK TOK_SMCLN
#line 456 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1951 "parser/parser.cpp"
    break;

  case 68: // stmt: TOK_CONTINUE TOK_SMCLN
#line 457 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 1957 "parser/parser.cpp"
    break;

  case 69: // stmt: block
#line 458 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 1963 "parser/parser.cpp"
    break;

  case 70: // stmt: expr TOK_SMCLN
#line 459 "parser/parser_rules.y"
                                          { yylhs.value.as < ast::Statement* > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 1969 "parser/parser.cpp"
    break;

  case 71: // if_stmt: TOK_IF TOK_LPAR expr TOK_RPAR block elseif_list else_part
#line 465 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::IfStatement* > () = ast.mk_if_stmt(yystack_[4].value.as < ast::Expr* > (), yystack_[2].value.as < ast::BlockStatement* > (), std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()), yystack_[0].value.as < ast::ElseStatement* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 1977 "parser/parser.cpp"
    break;

  case 72: // elseif_list: %empty
#line 472 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::vector<ast::ElseIfStatement*>{}; }
#line 1983 "parser/parser.cpp"
    break;

  case 73: // elseif_list: elseif_list elseif
#line 474 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ().push_back(yystack_[0].value.as < ast::ElseIfStatement* > ()); yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()); }
#line 1989 "parser/parser.cpp"
    break;

  case 74: // elseif: TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR block
#line 479 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::ElseIfStatement* > () = ast.mk_else_if_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[5].location, yystack_[0].location));
    }
#line 1997 "parser/parser.cpp"
    break;

  case 75: // else_part: %empty
#line 486 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = nullptr; }
#line 2003 "parser/parser.cpp"
    break;

  case 76: // else_part: TOK_ELSE block
#line 488 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::ElseStatement* > () = ast.mk_else_stmt(yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[1].location, yystack_[0].location));
    }
#line 2011 "parser/parser.cpp"
    break;

  case 77: // expr_opt: %empty
#line 496 "parser/parser_rules.y"
                  { yylhs.value.as < ast::Expr* > () = nullptr; }
#line 2017 "parser/parser.cpp"
    break;

  case 78: // expr_opt: expr
#line 497 "parser/parser_rules.y"
                  { yylhs.value.as < ast::Expr* > () = std::move(yystack_[0].value.as < ast::Expr* > ()); }
#line 2023 "parser/parser.cpp"
    break;

  case 79: // var_decl_stmt: var_decl
#line 505 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(yystack_[0].value.as < ast::VarDecl* > (), yystack_[0].location); }
#line 2029 "parser/parser.cpp"
    break;

  case 80: // var_mutability: %empty
#line 510 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Imm; }
#line 2035 "parser/parser.cpp"
    break;

  case 81: // var_mutability: TOK_IMM
#line 511 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Imm; }
#line 2041 "parser/parser.cpp"
    break;

  case 82: // var_mutability: TOK_MUT
#line 512 "parser/parser_rules.y"
               { yylhs.value.as < ast::VarDecl::Mutability > () = ast::VarDecl::Mutability::Mut; }
#line 2047 "parser/parser.cpp"
    break;

  case 83: // var_decl: var_mutability ident TOK_COLON type_expr TOK_SMCLN
#line 517 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[4].value.as < ast::VarDecl::Mutability > (), /*init*/nullptr, combine(yystack_[4].location, yystack_[0].location));
    }
#line 2055 "parser/parser.cpp"
    break;

  case 84: // var_decl: var_mutability ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 521 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (), yystack_[6].value.as < ast::VarDecl::Mutability > (), /*init*/yystack_[1].value.as < ast::Expr* > (), combine(yystack_[6].location, yystack_[0].location));
    }
#line 2063 "parser/parser.cpp"
    break;

  case 85: // expr: assign
#line 530 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2069 "parser/parser.cpp"
    break;

  case 86: // assign: cond
#line 534 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2075 "parser/parser.cpp"
    break;

  case 87: // assign: postfix TOK_ASSIGN assign
#line 535 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), /*Assign*/AssignOp::Assign, combine(yystack_[2].location, yystack_[0].location)); }
#line 2081 "parser/parser.cpp"
    break;

  case 88: // assign: postfix TOK_PLUS_ASSIGN assign
#line 536 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), /*AddEq*/AssignOp::Add, combine(yystack_[2].location, yystack_[0].location)); }
#line 2087 "parser/parser.cpp"
    break;

  case 89: // assign: postfix TOK_MIN_ASSIGN assign
#line 537 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), /*SubEq*/AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 2093 "parser/parser.cpp"
    break;

  case 90: // assign: postfix TOK_MUL_ASSIGN assign
#line 538 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), /*MulEq*/AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 2099 "parser/parser.cpp"
    break;

  case 91: // assign: postfix TOK_DIV_ASSIGN assign
#line 539 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), /*DivEq*/AssignOp::Divide, combine(yystack_[2].location, yystack_[0].location)); }
#line 2105 "parser/parser.cpp"
    break;

  case 92: // cond: logic_or
#line 543 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2111 "parser/parser.cpp"
    break;

  case 93: // logic_or: logic_and
#line 547 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2117 "parser/parser.cpp"
    break;

  case 94: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 549 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2123 "parser/parser.cpp"
    break;

  case 95: // logic_and: equality
#line 553 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2129 "parser/parser.cpp"
    break;

  case 96: // logic_and: logic_and TOK_BOOL_AND equality
#line 555 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2135 "parser/parser.cpp"
    break;

  case 97: // equality: relational
#line 559 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2141 "parser/parser.cpp"
    break;

  case 98: // equality: equality TOK_EQUAL relational
#line 561 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2147 "parser/parser.cpp"
    break;

  case 99: // equality: equality TOK_NEQUAL relational
#line 563 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2153 "parser/parser.cpp"
    break;

  case 100: // relational: additive
#line 567 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2159 "parser/parser.cpp"
    break;

  case 101: // relational: relational TOK_LESS additive
#line 568 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2165 "parser/parser.cpp"
    break;

  case 102: // relational: relational TOK_LEQ additive
#line 569 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2171 "parser/parser.cpp"
    break;

  case 103: // relational: relational TOK_GREATER additive
#line 570 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2177 "parser/parser.cpp"
    break;

  case 104: // relational: relational TOK_GEQ additive
#line 571 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2183 "parser/parser.cpp"
    break;

  case 105: // additive: multiplicative
#line 575 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2189 "parser/parser.cpp"
    break;

  case 106: // additive: additive TOK_PLUS multiplicative
#line 576 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2195 "parser/parser.cpp"
    break;

  case 107: // additive: additive TOK_MINUS multiplicative
#line 577 "parser/parser_rules.y"
                                      { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2201 "parser/parser.cpp"
    break;

  case 108: // multiplicative: unary
#line 581 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2207 "parser/parser.cpp"
    break;

  case 109: // multiplicative: multiplicative TOK_STAR unary
#line 582 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2213 "parser/parser.cpp"
    break;

  case 110: // multiplicative: multiplicative TOK_SLASH unary
#line 583 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2219 "parser/parser.cpp"
    break;

  case 111: // multiplicative: multiplicative TOK_MODULO unary
#line 584 "parser/parser_rules.y"
                                    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move(yystack_[2].value.as < ast::Expr* > ()), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2225 "parser/parser.cpp"
    break;

  case 112: // unary: TOK_MINUS unary
#line 588 "parser/parser_rules.y"
                                  { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::negation, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location,yystack_[0].location)); }
#line 2231 "parser/parser.cpp"
    break;

  case 113: // unary: TOK_NEGATION unary
#line 589 "parser/parser_rules.y"
                                  { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location,yystack_[0].location)); }
#line 2237 "parser/parser.cpp"
    break;

  case 114: // unary: TOK_INC unary
#line 590 "parser/parser_rules.y"
                                  { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location,yystack_[0].location)); }
#line 2243 "parser/parser.cpp"
    break;

  case 115: // unary: TOK_DEC unary
#line 591 "parser/parser_rules.y"
                                  { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location,yystack_[0].location)); }
#line 2249 "parser/parser.cpp"
    break;

  case 116: // unary: postfix
#line 592 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2255 "parser/parser.cpp"
    break;

  case 117: // postfix: primary
#line 597 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2261 "parser/parser.cpp"
    break;

  case 118: // postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR
#line 599 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_call_expr(std::move(yystack_[3].value.as < ast::Expr* > ()), std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2267 "parser/parser.cpp"
    break;

  case 119: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 601 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_index(std::move(yystack_[3].value.as < ast::Expr* > ()), std::move(yystack_[1].value.as < ast::Expr* > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2273 "parser/parser.cpp"
    break;

  case 120: // postfix: postfix TOK_DOT ident
#line 603 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_field_expr(std::move(yystack_[2].value.as < ast::Expr* > ()), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2279 "parser/parser.cpp"
    break;

  case 121: // postfix: postfix TOK_INC
#line 605 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, std::move(yystack_[1].value.as < ast::Expr* > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2285 "parser/parser.cpp"
    break;

  case 122: // postfix: postfix TOK_DEC
#line 607 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, std::move(yystack_[1].value.as < ast::Expr* > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2291 "parser/parser.cpp"
    break;

  case 123: // arg_list_opt: %empty
#line 611 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2297 "parser/parser.cpp"
    break;

  case 124: // arg_list_opt: arg_list
#line 612 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ());  }
#line 2303 "parser/parser.cpp"
    break;

  case 125: // arg_list: expr
#line 616 "parser/parser_rules.y"
                                 { std::vector<ast::Expr*> v; v.push_back(std::move(yystack_[0].value.as < ast::Expr* > ())); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(v); }
#line 2309 "parser/parser.cpp"
    break;

  case 126: // arg_list: arg_list TOK_COMMA expr
#line 617 "parser/parser_rules.y"
                                 { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(std::move(yystack_[0].value.as < ast::Expr* > ())); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2315 "parser/parser.cpp"
    break;

  case 127: // arg_list: arg_list TOK_COMMA
#line 618 "parser/parser_rules.y"
                                 { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2321 "parser/parser.cpp"
    break;

  case 128: // int_literal_type_opt: %empty
#line 622 "parser/parser_rules.y"
                { yylhs.value.as < std::optional<kl::rt::IntKind> > () = std::nullopt; }
#line 2327 "parser/parser.cpp"
    break;

  case 129: // int_literal_type_opt: TOK_AS TOK_I8
#line 623 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I8; }
#line 2333 "parser/parser.cpp"
    break;

  case 130: // int_literal_type_opt: TOK_AS TOK_U8
#line 624 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U8; }
#line 2339 "parser/parser.cpp"
    break;

  case 131: // int_literal_type_opt: TOK_AS TOK_I16
#line 625 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I16; }
#line 2345 "parser/parser.cpp"
    break;

  case 132: // int_literal_type_opt: TOK_AS TOK_U16
#line 626 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U16; }
#line 2351 "parser/parser.cpp"
    break;

  case 133: // int_literal_type_opt: TOK_AS TOK_I32
#line 627 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I32; }
#line 2357 "parser/parser.cpp"
    break;

  case 134: // int_literal_type_opt: TOK_AS TOK_U32
#line 628 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U32; }
#line 2363 "parser/parser.cpp"
    break;

  case 135: // int_literal_type_opt: TOK_AS TOK_I64
#line 629 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I64; }
#line 2369 "parser/parser.cpp"
    break;

  case 136: // int_literal_type_opt: TOK_AS TOK_U64
#line 630 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U64; }
#line 2375 "parser/parser.cpp"
    break;

  case 137: // int_literal_type_opt: TOK_AS TOK_I128
#line 631 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I128; }
#line 2381 "parser/parser.cpp"
    break;

  case 138: // int_literal_type_opt: TOK_AS TOK_U128
#line 632 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U128; }
#line 2387 "parser/parser.cpp"
    break;

  case 139: // float_literal_type_opt: %empty
#line 636 "parser/parser_rules.y"
                { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = std::nullopt; }
#line 2393 "parser/parser.cpp"
    break;

  case 140: // float_literal_type_opt: TOK_AS TOK_F32
#line 637 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F32; }
#line 2399 "parser/parser.cpp"
    break;

  case 141: // float_literal_type_opt: TOK_AS TOK_F64
#line 638 "parser/parser_rules.y"
                       { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F64; }
#line 2405 "parser/parser.cpp"
    break;

  case 142: // primary: ident
#line 642 "parser/parser_rules.y"
                                                    { yylhs.value.as < ast::Expr* > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2411 "parser/parser.cpp"
    break;

  case 143: // primary: TOK_INT_LITERAL int_literal_type_opt
#line 643 "parser/parser_rules.y"
                                             { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::IntKind> > (), yystack_[1].location); }
#line 2417 "parser/parser.cpp"
    break;

  case 144: // primary: TOK_FLOAT_LITERAL float_literal_type_opt
#line 644 "parser/parser_rules.y"
                                             { yylhs.value.as < ast::Expr* > () = ast.mk_float_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::FloatKind> > (), yystack_[1].location); }
#line 2423 "parser/parser.cpp"
    break;

  case 145: // primary: TOK_STRING_LITERAL
#line 645 "parser/parser_rules.y"
                                                    { yylhs.value.as < ast::Expr* > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2429 "parser/parser.cpp"
    break;

  case 146: // primary: TOK_BOOL_LITERAL
#line 646 "parser/parser_rules.y"
                                                    { yylhs.value.as < ast::Expr* > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl::rt::boolean > (), yystack_[0].location); }
#line 2435 "parser/parser.cpp"
    break;

  case 147: // primary: TOK_LPAR expr TOK_RPAR
#line 647 "parser/parser_rules.y"
                                                    { yylhs.value.as < ast::Expr* > () = std::move(yystack_[1].value.as < ast::Expr* > ()); }
#line 2441 "parser/parser.cpp"
    break;

  case 148: // primary: struct_lit
#line 648 "parser/parser_rules.y"
                                                    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(yystack_[0].value.as < ast::StructLiteralExpr* > ()); }
#line 2447 "parser/parser.cpp"
    break;

  case 149: // struct_lit: path_type_expr TOK_LCBRA field_inits_opt TOK_RCBRA
#line 653 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructLiteralExpr* > () = ast.mk_obj_literal_expr(yystack_[3].value.as < ast::PathTypeExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()), combine(yystack_[3].location, yystack_[0].location)); }
#line 2453 "parser/parser.cpp"
    break;

  case 150: // field_inits_opt: %empty
#line 657 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{}; }
#line 2459 "parser/parser.cpp"
    break;

  case 151: // field_inits_opt: field_inits
#line 658 "parser/parser_rules.y"
                       { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2465 "parser/parser.cpp"
    break;

  case 152: // field_inits: field_init
#line 662 "parser/parser_rules.y"
                                         { std::vector<ast::FieldInitExpr*> v; v.push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(v); }
#line 2471 "parser/parser.cpp"
    break;

  case 153: // field_inits: field_inits TOK_COMMA field_init
#line 663 "parser/parser_rules.y"
                                         { yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ().push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2477 "parser/parser.cpp"
    break;

  case 154: // field_inits: field_inits TOK_COMMA
#line 664 "parser/parser_rules.y"
                                         { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2483 "parser/parser.cpp"
    break;

  case 155: // field_init: ident TOK_COLON expr
#line 669 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr* > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), std::move(yystack_[0].value.as < ast::Expr* > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2489 "parser/parser.cpp"
    break;


#line 2493 "parser/parser.cpp"

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


  const signed char parser::yypact_ninf_ = -125;

  const signed char parser::yytable_ninf_ = -13;

  const short
  parser::yypact_[] =
  {
      25,   -10,    64,  -125,  -125,   -36,  -125,  -125,    65,  -125,
     -10,   -10,  -125,    73,  -125,   -14,    33,    33,  -125,  -125,
    -125,   -10,  -125,  -125,    -2,    29,    42,    -6,  -125,    33,
    -125,    33,    54,    -6,  -125,    77,    86,    85,  -125,    84,
      88,  -125,  -125,   160,    87,    33,   160,   160,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,    91,  -125,    90,     4,  -125,  -125,  -125,  -125,
     160,    53,  -125,    95,    18,  -125,  -125,   160,   182,  -125,
      95,  -125,  -125,  -125,  -125,    95,    35,   114,   121,  -125,
    -125,   182,   182,   182,   182,   182,    98,  -125,   100,  -125,
    -125,    76,    78,    43,    24,    51,    48,  -125,   156,  -125,
    -125,    38,   144,  -125,    82,  -125,   106,  -125,    17,  -125,
    -125,  -125,    33,  -125,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,    33,
    -125,  -125,   182,   182,   182,   182,   182,   122,   134,   117,
     182,  -125,  -125,   128,   129,  -125,  -125,  -125,  -125,  -125,
      33,  -125,   131,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,   149,   154,   155,  -125,
      78,    43,    24,    24,    51,    51,    51,    51,    48,    48,
    -125,  -125,  -125,  -125,   159,   157,   161,  -125,  -125,  -125,
    -125,  -125,  -125,   182,   182,   201,   164,  -125,  -125,  -125,
     158,  -125,   182,  -125,    33,  -125,   182,  -125,   166,   167,
     172,  -125,   160,  -125,  -125,  -125,   117,   117,   182,   -11,
    -125,  -125,   173,  -125,   182,   210,   174,   176,     6,  -125,
    -125,  -125,  -125,   184,  -125,   182,   189,   117,  -125
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     5,    12,     0,    10,     1,    13,     4,
       0,     0,     6,     2,    11,     0,     0,     0,    14,    15,
      16,     0,     7,    58,     0,     0,     0,    21,    20,    28,
       8,     0,     0,    22,    23,     0,     0,    29,    30,     0,
       0,    19,    24,     0,     0,    32,     0,     0,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    54,    52,     9,     0,    34,    35,    36,    37,
       0,     0,    31,    33,     0,    56,    55,     0,     0,    25,
      27,    60,    18,    17,    26,    57,    58,   128,   139,   145,
     146,     0,     0,     0,     0,     0,     0,   142,     0,    85,
      86,    92,    93,    95,    97,   100,   105,   108,   116,   117,
     148,     0,     0,   143,     0,   144,     0,   113,   116,   114,
     115,   112,   150,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,     0,     0,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
      77,    82,    81,     0,     0,    59,    69,    61,    64,    62,
       0,    79,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   140,   141,   147,     0,     0,   151,   152,
      94,    96,    98,    99,   101,   102,   103,   104,   106,   107,
     109,   110,   111,   125,     0,   124,     0,   120,    87,    88,
      89,    90,    91,     0,     0,     0,     0,    78,    67,    68,
       0,    70,     0,   149,   154,   118,   127,   119,     0,     0,
       0,    63,     0,   155,   153,   126,     0,     0,     0,     0,
      72,    65,     0,    83,     0,    75,     0,     0,     0,    73,
      71,    66,    84,     0,    76,     0,     0,     0,    74
  };

  const short
  parser::yypgoto_[] =
  {
    -125,  -125,  -125,  -125,  -125,  -125,    46,    23,  -125,  -125,
    -125,  -125,  -125,  -125,   202,  -125,  -125,  -125,   191,   -42,
    -125,   -40,  -125,  -125,  -125,   -16,  -109,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,   -79,  -124,  -125,
    -125,   110,   115,     0,   -32,    -1,   -69,    27,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,    28
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    12,    63,    64,     6,    13,    18,
      19,    20,    32,    33,    34,    71,    36,    37,    38,    65,
      66,    96,    68,    77,    69,    97,    83,   111,   157,   158,
     235,   239,   240,   206,   159,   160,   161,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   194,   195,
     113,   115,   109,   110,   177,   178,   179
  };

  const short
  parser::yytable_[] =
  {
      24,    25,   156,    67,    73,    74,    67,    67,    21,   243,
      31,    35,   116,    39,     9,    40,    10,    35,   198,   199,
     200,   201,   202,   117,   119,   120,   121,     4,    80,    39,
      67,    23,   162,    14,    78,    85,    22,    67,    10,   233,
     205,   147,   148,   149,    26,    27,     1,     5,    28,    78,
     150,   151,   152,    81,    79,   153,   154,    15,   193,   196,
     137,   234,   138,    78,     7,   190,   191,   192,    84,   139,
      23,   207,    29,   140,   141,    86,    87,    88,    89,    90,
      16,    91,   -12,    17,    11,    81,   155,   -12,   128,   129,
     130,   131,    30,    92,    93,    94,   184,   185,   186,   187,
      81,    95,    41,    82,    75,    76,   176,   134,   135,   136,
     237,   126,   127,   132,   133,   173,   174,   230,   231,   118,
     118,   118,   118,   197,   218,   219,   182,   183,    43,   244,
      44,   188,   189,   223,    45,    46,   112,   225,   248,    47,
      78,    70,    10,   114,   210,   122,   123,   124,   125,   232,
     175,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,    81,   203,   246,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   204,   208,   209,
     229,   211,    67,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,     4,   176,   137,
     212,   138,   213,   215,   214,   220,   216,   217,   139,   222,
     226,   227,   140,   141,   221,   228,   238,   236,    62,    86,
      87,    88,    89,    90,   241,    91,   242,   245,   142,   143,
     144,   145,   146,   247,   180,    42,    72,    92,    93,    94,
     181,     0,   224,     0,     0,    95
  };

  const short
  parser::yycheck_[] =
  {
      16,    17,   111,    43,    46,    47,    46,    47,    22,     3,
      16,    27,    91,    29,    50,    31,    52,    33,   142,   143,
     144,   145,   146,    92,    93,    94,    95,    37,    70,    45,
      70,    37,   111,    10,    45,    77,    50,    77,    52,    50,
     149,     3,     4,     5,    21,    47,    21,     1,    50,    45,
      12,    13,    14,    47,    50,    17,    18,    11,   137,   138,
      43,    72,    45,    45,     0,   134,   135,   136,    50,    52,
      37,   150,    43,    56,    57,    37,    38,    39,    40,    41,
       7,    43,    47,    10,    19,    47,    48,    52,    64,    65,
      66,    67,    50,    55,    56,    57,   128,   129,   130,   131,
      47,    63,    48,    50,    13,    14,   122,    59,    60,    61,
     234,    68,    69,    62,    63,    33,    34,   226,   227,    92,
      93,    94,    95,   139,   203,   204,   126,   127,    51,   238,
      44,   132,   133,   212,    49,    51,    22,   216,   247,    51,
      45,    54,    52,    22,   160,    47,    46,    71,    70,   228,
      44,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,    47,    43,   245,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    43,    50,    50,
     222,    50,   222,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   214,    43,
      51,    45,    48,    44,    49,     4,    49,    46,    52,    51,
      44,    44,    56,    57,    50,    43,     6,    44,    58,    37,
      38,    39,    40,    41,    50,    43,    50,    43,    72,    73,
      74,    75,    76,    44,   124,    33,    45,    55,    56,    57,
     125,    -1,   214,    -1,    -1,    63
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    21,    81,    82,    37,    86,    87,     0,    83,    50,
      52,    19,    84,    88,    87,    86,     7,    10,    89,    90,
      91,    22,    50,    37,   105,   105,    87,    47,    50,    43,
      50,    16,    92,    93,    94,   105,    96,    97,    98,   105,
     105,    48,    94,    51,    44,    49,    51,    51,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    58,    85,    86,    99,   100,   101,   102,   104,
      54,    95,    98,    99,    99,    13,    14,   103,    45,    50,
      99,    47,    50,   106,    50,    99,    37,    38,    39,    40,
      41,    43,    55,    56,    57,    63,   101,   105,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   132,
     133,   107,    22,   130,    22,   131,   117,   126,   127,   126,
     126,   126,    47,    46,    71,    70,    68,    69,    64,    65,
      66,    67,    62,    63,    59,    60,    61,    43,    45,    52,
      56,    57,    72,    73,    74,    75,    76,     3,     4,     5,
      12,    13,    14,    17,    18,    48,   106,   108,   109,   114,
     115,   116,   117,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    44,   105,   134,   135,   136,
     121,   122,   123,   123,   124,   124,   124,   124,   125,   125,
     126,   126,   126,   117,   128,   129,   117,   105,   118,   118,
     118,   118,   118,    43,    43,   106,   113,   117,    50,    50,
     105,    50,    51,    48,    49,    44,    49,    46,   117,   117,
       4,    50,    51,   117,   136,   117,    44,    44,    43,    99,
     106,   106,   117,    50,    72,   110,    44,   118,     6,   111,
     112,    50,    50,     3,   106,    43,   117,    44,   106
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    80,    81,    82,    82,    83,    83,    84,    84,    85,
      86,    86,    87,    88,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    94,    95,    96,    96,
      97,    97,    97,    98,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   102,   103,   103,   103,   104,   105,   106,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   110,   110,   111,   112,   112,   113,   113,   114,
     115,   115,   115,   116,   116,   117,   118,   118,   118,   118,
     118,   118,   119,   120,   120,   121,   121,   122,   122,   122,
     123,   123,   123,   123,   123,   124,   124,   124,   125,   125,
     125,   125,   126,   126,   126,   126,   126,   127,   127,   127,
     127,   127,   127,   128,   128,   129,   129,   129,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   132,   132,   132,   132,   132,   132,   132,   133,
     134,   134,   135,   135,   135,   136
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     0,     3,     0,     2,     3,     5,     1,
       1,     3,     1,     0,     2,     1,     1,     7,     7,     5,
       3,     0,     1,     1,     2,     4,     5,     2,     0,     1,
       1,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     0,     1,     1,     3,     1,     3,
       0,     2,     1,     3,     1,     5,     7,     2,     2,     1,
       2,     7,     0,     2,     6,     0,     2,     0,     1,     1,
       0,     1,     1,     5,     7,     1,     1,     3,     3,     3,
       3,     3,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     2,     2,     2,     2,     1,     1,     4,     4,
       3,     2,     2,     0,     1,     1,     3,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     1,     2,     2,     1,     1,     3,     1,     4,
       0,     1,     1,     3,     2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_ENUM", "TOK_TRAIT", "TOK_FN",
  "TOK_TYPE", "TOK_RETURN", "TOK_MUT", "TOK_IMM", "TOK_STATIC", "TOK_PUB",
  "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT", "TOK_EXPORT", "TOK_PACKAGE",
  "TOK_AS", "TOK_I8", "TOK_U8", "TOK_I16", "TOK_U16", "TOK_I32", "TOK_U32",
  "TOK_I64", "TOK_U64", "TOK_I128", "TOK_U128", "TOK_F32", "TOK_F64",
  "TOK_BOOL", "TOK_CHAR", "TOK_IDENTIFIER", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_CHAR_LITERAL", "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK",
  "TOK_LCBRA", "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON",
  "TOK_DOT", "TOK_QUESTION", "TOK_ARROW", "TOK_NEGATION", "TOK_INC",
  "TOK_DEC", "TOK_AMP", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit",
  "opt_package", "import_list", "import_decl", "path_expr",
  "names_separated_by_dots", "name", "decl_list", "decl", "fn_decl",
  "struct_decl", "field_decl_list_opt", "field_decl_list", "field_decl",
  "ret_type_expr", "param_list_opt", "param_list", "param", "type_expr",
  "builtin_type_expr", "path_type_expr", "array_type_expr",
  "ref_mutability", "ref_type_expr", "ident", "block", "stmt_list", "stmt",
  "if_stmt", "elseif_list", "elseif", "else_part", "expr_opt",
  "var_decl_stmt", "var_mutability", "var_decl", "expr", "assign", "cond",
  "logic_or", "logic_and", "equality", "relational", "additive",
  "multiplicative", "unary", "postfix", "arg_list_opt", "arg_list",
  "int_literal_type_opt", "float_literal_type_opt", "primary",
  "struct_lit", "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   264,   264,   275,   276,   283,   284,   291,   293,   298,
     303,   305,   310,   316,   317,   321,   322,   326,   330,   337,
     339,   344,   345,   349,   350,   354,   356,   361,   365,   366,
     370,   371,   372,   376,   383,   384,   385,   386,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   407,   411,   416,   417,   418,   422,   427,   438,
     443,   444,   448,   449,   450,   452,   454,   456,   457,   458,
     459,   464,   472,   473,   478,   486,   487,   496,   497,   504,
     510,   511,   512,   516,   520,   530,   534,   535,   536,   537,
     538,   539,   543,   547,   548,   553,   554,   559,   560,   562,
     567,   568,   569,   570,   571,   575,   576,   577,   581,   582,
     583,   584,   588,   589,   590,   591,   592,   597,   598,   600,
     602,   604,   606,   611,   612,   616,   617,   618,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   636,
     637,   638,   642,   643,   644,   645,   646,   647,   648,   652,
     657,   658,   662,   663,   664,   668
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
#line 3291 "parser/parser.cpp"

#line 672 "parser/parser_rules.y"


/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
