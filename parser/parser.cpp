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
#line 41 "parser/parser_rules.y"

  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.end.line << ':' << loc.end.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    scanner.yylex();

    const lex::Token& t = scanner.getCurrentToken();
    const lex::Loc    L = t.loc_;

    using T = lex::Type;
    switch (t.type_) {
      /* payload-bearing */
      case T::TOK_IDENTIFIER:     return yy::parser::make_TOK_IDENTIFIER(t.u_.sym, L);
      case T::TOK_INT_LITERAL:    return yy::parser::make_TOK_INT_LITERAL(t.u_.sym, L);
      case T::TOK_FLOAT_LITERAL:  return yy::parser::make_TOK_FLOAT_LITERAL(t.u_.sym, L);
      case T::TOK_STRING_LITERAL: return yy::parser::make_TOK_STRING_LITERAL(t.u_.sym, L);
      case T::TOK_BOOL_LITERAL:   return yy::parser::make_TOK_BOOL_LITERAL(t.u_.boolean, L);
      case T::TOK_CHAR_LITERAL:   return yy::parser::make_TOK_CHAR_LITERAL(t.u_.ch, L);

      /* keywords */
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

      /* builtin type keywords */
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

      /* punctuation */
      case T::TOK_LPAR:        return yy::parser::make_TOK_LPAR(L);
      case T::TOK_RPAR:        return yy::parser::make_TOK_RPAR(L);
      case T::TOK_LBRACK:      return yy::parser::make_TOK_LBRACK(L);
      case T::TOK_RBRACK:      return yy::parser::make_TOK_RBRACK(L);
      case T::TOK_LCBRA:       return yy::parser::make_TOK_LCBRA(L);
      case T::TOK_RCBRA:       return yy::parser::make_TOK_RCBRA(L);
      case T::TOK_COMMA:       return yy::parser::make_TOK_COMMA(L);
      case T::TOK_SMCLN:       return yy::parser::make_TOK_SMCLN(L);
      case T::TOK_COLON:       return yy::parser::make_TOK_COLON(L);
      case T::TOK_COLONCOLON:  return yy::parser::make_TOK_COLONCOLON(L);
      case T::TOK_DOT:         return yy::parser::make_TOK_DOT(L);
      case T::TOK_QUESTION:    return yy::parser::make_TOK_QUESTION(L);
      case T::TOK_ARROW:       return yy::parser::make_TOK_ARROW(L);
      case T::TOK_TURBOFISH_S: return yy::parser::make_TOK_TURBOFISH_S(L);

      /* operators */
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

      /* EOF / unknown */
      case T::TOK_END: return yy::parser::make_YYEOF(L);
      default:         return yy::parser::make_YYUNDEF(L);
    }
  }

  static inline lex::Loc combine(const lex::Loc& a, const lex::Loc& b) {
    lex::Loc L{};
    L.begin = a.begin;
    L.end   = b.end;
    return L;
  }

#line 163 "parser/parser.cpp"


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

#line 8 "parser/parser_rules.y"
namespace yy {
#line 256 "parser/parser.cpp"

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
      case symbol_kind::S_ident: // ident
        value.YY_MOVE_OR_COPY< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.YY_MOVE_OR_COPY< ast::BreakStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.YY_MOVE_OR_COPY< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.YY_MOVE_OR_COPY< ast::ContinueStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
        value.YY_MOVE_OR_COPY< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.YY_MOVE_OR_COPY< ast::DoWhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.YY_MOVE_OR_COPY< ast::ElseIfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.YY_MOVE_OR_COPY< ast::ElseStatement* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.YY_MOVE_OR_COPY< ast::ExprStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.YY_MOVE_OR_COPY< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.YY_MOVE_OR_COPY< ast::FieldInitExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_fn_decl_def: // fn_decl_def
      case symbol_kind::S_fn_decl_proto: // fn_decl_proto
        value.YY_MOVE_OR_COPY< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.YY_MOVE_OR_COPY< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_module: // module
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

      case symbol_kind::S_return_stmt: // return_stmt
        value.YY_MOVE_OR_COPY< ast::ReturnStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.YY_MOVE_OR_COPY< ast::Statement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
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

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_var_decl_default: // var_decl_default
      case symbol_kind::S_var_decl_imm: // var_decl_imm
      case symbol_kind::S_var_decl_mut: // var_decl_mut
        value.YY_MOVE_OR_COPY< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.YY_MOVE_OR_COPY< ast::VarDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.YY_MOVE_OR_COPY< ast::WhileStatement* > (YY_MOVE (that.value));
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

      case symbol_kind::S_package_opt: // package_opt
      case symbol_kind::S_path: // path
        value.YY_MOVE_OR_COPY< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
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

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<ast::Statement*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_ident: // ident
        value.move< Str > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.move< ast::BreakStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.move< ast::ContinueStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
        value.move< ast::Decl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.move< ast::DoWhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (YY_MOVE (that.value));
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
        value.move< ast::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.move< ast::ExprStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_fn_decl_def: // fn_decl_def
      case symbol_kind::S_fn_decl_proto: // fn_decl_proto
        value.move< ast::FunctionDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_module: // module
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

      case symbol_kind::S_return_stmt: // return_stmt
        value.move< ast::ReturnStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.move< ast::Statement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
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

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_var_decl_default: // var_decl_default
      case symbol_kind::S_var_decl_imm: // var_decl_imm
      case symbol_kind::S_var_decl_mut: // var_decl_mut
        value.move< ast::VarDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (YY_MOVE (that.value));
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

      case symbol_kind::S_package_opt: // package_opt
      case symbol_kind::S_path: // path
        value.move< std::vector<Str> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
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

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_ident: // ident
        value.copy< Str > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.copy< ast::BreakStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.copy< ast::BuiltinTypeExpr* > (that.value);
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.copy< ast::ContinueStatement* > (that.value);
        break;

      case symbol_kind::S_decl: // decl
        value.copy< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.copy< ast::DoWhileStatement* > (that.value);
        break;

      case symbol_kind::S_elseif: // elseif
        value.copy< ast::ElseIfStatement* > (that.value);
        break;

      case symbol_kind::S_else_part: // else_part
        value.copy< ast::ElseStatement* > (that.value);
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
        value.copy< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.copy< ast::ExprStatement* > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.copy< ast::FieldInitExpr* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_fn_decl_def: // fn_decl_def
      case symbol_kind::S_fn_decl_proto: // fn_decl_proto
        value.copy< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_module: // module
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

      case symbol_kind::S_return_stmt: // return_stmt
        value.copy< ast::ReturnStatement* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.copy< ast::Statement* > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
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

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_var_decl_default: // var_decl_default
      case symbol_kind::S_var_decl_imm: // var_decl_imm
      case symbol_kind::S_var_decl_mut: // var_decl_mut
        value.copy< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.copy< ast::VarDeclStatement* > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.copy< ast::WhileStatement* > (that.value);
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

      case symbol_kind::S_package_opt: // package_opt
      case symbol_kind::S_path: // path
        value.copy< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
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

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.copy< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<ast::Statement*> > (that.value);
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
      case symbol_kind::S_ident: // ident
        value.move< Str > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< ast::BlockStatement* > (that.value);
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        value.move< ast::BreakStatement* > (that.value);
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        value.move< ast::BuiltinTypeExpr* > (that.value);
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        value.move< ast::ContinueStatement* > (that.value);
        break;

      case symbol_kind::S_decl: // decl
        value.move< ast::Decl* > (that.value);
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        value.move< ast::DoWhileStatement* > (that.value);
        break;

      case symbol_kind::S_elseif: // elseif
        value.move< ast::ElseIfStatement* > (that.value);
        break;

      case symbol_kind::S_else_part: // else_part
        value.move< ast::ElseStatement* > (that.value);
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
        value.move< ast::Expr* > (that.value);
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        value.move< ast::ExprStatement* > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< ast::FieldDecl* > (that.value);
        break;

      case symbol_kind::S_field_init: // field_init
        value.move< ast::FieldInitExpr* > (that.value);
        break;

      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_fn_decl_def: // fn_decl_def
      case symbol_kind::S_fn_decl_proto: // fn_decl_proto
        value.move< ast::FunctionDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_module: // module
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

      case symbol_kind::S_return_stmt: // return_stmt
        value.move< ast::ReturnStatement* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        value.move< ast::Statement* > (that.value);
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
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

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_var_decl_default: // var_decl_default
      case symbol_kind::S_var_decl_imm: // var_decl_imm
      case symbol_kind::S_var_decl_mut: // var_decl_mut
        value.move< ast::VarDecl* > (that.value);
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        value.move< ast::VarDeclStatement* > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (that.value);
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

      case symbol_kind::S_package_opt: // package_opt
      case symbol_kind::S_path: // path
        value.move< std::vector<Str> > (that.value);
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
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

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        value.move< std::vector<ast::ImportDecl*> > (that.value);
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<ast::ParamDecl*> > (that.value);
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<ast::Statement*> > (that.value);
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
      case symbol_kind::S_ident: // ident
        yylhs.value.emplace< Str > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< ast::BlockStatement* > ();
        break;

      case symbol_kind::S_break_stmt: // break_stmt
        yylhs.value.emplace< ast::BreakStatement* > ();
        break;

      case symbol_kind::S_builtin_type_expr: // builtin_type_expr
        yylhs.value.emplace< ast::BuiltinTypeExpr* > ();
        break;

      case symbol_kind::S_continue_stmt: // continue_stmt
        yylhs.value.emplace< ast::ContinueStatement* > ();
        break;

      case symbol_kind::S_decl: // decl
        yylhs.value.emplace< ast::Decl* > ();
        break;

      case symbol_kind::S_do_while_stmt: // do_while_stmt
        yylhs.value.emplace< ast::DoWhileStatement* > ();
        break;

      case symbol_kind::S_elseif: // elseif
        yylhs.value.emplace< ast::ElseIfStatement* > ();
        break;

      case symbol_kind::S_else_part: // else_part
        yylhs.value.emplace< ast::ElseStatement* > ();
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
        yylhs.value.emplace< ast::Expr* > ();
        break;

      case symbol_kind::S_expr_stmt: // expr_stmt
        yylhs.value.emplace< ast::ExprStatement* > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        yylhs.value.emplace< ast::FieldDecl* > ();
        break;

      case symbol_kind::S_field_init: // field_init
        yylhs.value.emplace< ast::FieldInitExpr* > ();
        break;

      case symbol_kind::S_fn_decl: // fn_decl
      case symbol_kind::S_fn_decl_def: // fn_decl_def
      case symbol_kind::S_fn_decl_proto: // fn_decl_proto
        yylhs.value.emplace< ast::FunctionDecl* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        yylhs.value.emplace< ast::IfStatement* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_translation_unit: // translation_unit
      case symbol_kind::S_module: // module
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

      case symbol_kind::S_return_stmt: // return_stmt
        yylhs.value.emplace< ast::ReturnStatement* > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_simple_stmt: // simple_stmt
      case symbol_kind::S_compound_stmt: // compound_stmt
        yylhs.value.emplace< ast::Statement* > ();
        break;

      case symbol_kind::S_struct_decl: // struct_decl
      case symbol_kind::S_struct_decl_def: // struct_decl_def
      case symbol_kind::S_struct_decl_fwd: // struct_decl_fwd
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

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_var_decl_default: // var_decl_default
      case symbol_kind::S_var_decl_imm: // var_decl_imm
      case symbol_kind::S_var_decl_mut: // var_decl_mut
        yylhs.value.emplace< ast::VarDecl* > ();
        break;

      case symbol_kind::S_var_decl_stmt: // var_decl_stmt
        yylhs.value.emplace< ast::VarDeclStatement* > ();
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        yylhs.value.emplace< ast::WhileStatement* > ();
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

      case symbol_kind::S_package_opt: // package_opt
      case symbol_kind::S_path: // path
        yylhs.value.emplace< std::vector<Str> > ();
        break;

      case symbol_kind::S_decl_list_opt: // decl_list_opt
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

      case symbol_kind::S_import_list_opt: // import_list_opt
      case symbol_kind::S_import_list: // import_list
        yylhs.value.emplace< std::vector<ast::ImportDecl*> > ();
        break;

      case symbol_kind::S_param_list_opt: // param_list_opt
      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<ast::ParamDecl*> > ();
        break;

      case symbol_kind::S_stmt_list_opt: // stmt_list_opt
      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<ast::Statement*> > ();
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
  case 2: // translation_unit: module
#line 311 "parser/parser_rules.y"
    { yylhs.value.as < ast::Module* > () = yystack_[0].value.as < ast::Module* > (); }
#line 1757 "parser/parser.cpp"
    break;

  case 3: // module: package_opt import_list_opt decl_list_opt
#line 316 "parser/parser_rules.y"
    {
      auto* m = ast.mk_module(std::move(yystack_[2].value.as < std::vector<Str> > ()), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[2].location, yystack_[0].location));
      ast.project_add_module(m);
      yylhs.value.as < ast::Module* > () = m;
    }
#line 1767 "parser/parser.cpp"
    break;

  case 4: // package_opt: %empty
#line 325 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{}; }
#line 1773 "parser/parser.cpp"
    break;

  case 5: // package_opt: TOK_PACKAGE path TOK_SMCLN
#line 327 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::move(yystack_[1].value.as < std::vector<Str> > ()); }
#line 1779 "parser/parser.cpp"
    break;

  case 6: // import_list_opt: %empty
#line 332 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1785 "parser/parser.cpp"
    break;

  case 7: // import_list_opt: import_list
#line 334 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1791 "parser/parser.cpp"
    break;

  case 8: // import_list: import_decl
#line 339 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{ yystack_[0].value.as < ast::ImportDecl* > () }; }
#line 1797 "parser/parser.cpp"
    break;

  case 9: // import_list: import_list import_decl
#line 341 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1803 "parser/parser.cpp"
    break;

  case 10: // import_decl: TOK_IMPORT path TOK_SMCLN
#line 346 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < std::vector<Str> > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1809 "parser/parser.cpp"
    break;

  case 11: // import_decl: TOK_IMPORT path TOK_AS ident TOK_SMCLN
#line 348 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < std::vector<Str> > ()), std::optional<Str>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1815 "parser/parser.cpp"
    break;

  case 12: // path: ident
#line 358 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[0].value.as < Str > () }; }
#line 1821 "parser/parser.cpp"
    break;

  case 13: // path: path TOK_COLONCOLON ident
#line 360 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1827 "parser/parser.cpp"
    break;

  case 14: // path_expr: path
#line 365 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1833 "parser/parser.cpp"
    break;

  case 15: // ident: TOK_IDENTIFIER
#line 370 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1839 "parser/parser.cpp"
    break;

  case 16: // type_params_opt: %empty
#line 379 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{}; }
#line 1845 "parser/parser.cpp"
    break;

  case 17: // type_params_opt: TOK_LESS type_param_list TOK_GREATER
#line 381 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1851 "parser/parser.cpp"
    break;

  case 18: // type_param_list: type_param
#line 386 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{ yystack_[0].value.as < ast::TypeParamDecl* > () }; }
#line 1857 "parser/parser.cpp"
    break;

  case 19: // type_param_list: type_param_list TOK_COMMA type_param
#line 388 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ().push_back(yystack_[0].value.as < ast::TypeParamDecl* > ()); yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1863 "parser/parser.cpp"
    break;

  case 20: // type_param_list: type_param_list TOK_COMMA
#line 390 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1869 "parser/parser.cpp"
    break;

  case 21: // type_param: ident
#line 395 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeParamDecl* > () = ast.mk_type_param_decl(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1875 "parser/parser.cpp"
    break;

  case 22: // type_args: %empty
#line 400 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{}; }
#line 1881 "parser/parser.cpp"
    break;

  case 23: // type_args: TOK_TURBOFISH_S type_arg_list TOK_GREATER
#line 402 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1887 "parser/parser.cpp"
    break;

  case 24: // type_arg_list: type_expr
#line 407 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{ yystack_[0].value.as < ast::TypeExpr* > () }; }
#line 1893 "parser/parser.cpp"
    break;

  case 25: // type_arg_list: type_arg_list TOK_COMMA type_expr
#line 409 "parser/parser_rules.y"
      { yystack_[2].value.as < std::vector<ast::TypeExpr*> > ().push_back(yystack_[0].value.as < ast::TypeExpr* > ()); yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1899 "parser/parser.cpp"
    break;

  case 26: // type_arg_list: type_arg_list TOK_COMMA
#line 411 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1905 "parser/parser.cpp"
    break;

  case 27: // decl_list_opt: %empty
#line 421 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 1911 "parser/parser.cpp"
    break;

  case 28: // decl_list_opt: decl_list
#line 423 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()); }
#line 1917 "parser/parser.cpp"
    break;

  case 29: // decl_list: decl
#line 428 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{ yystack_[0].value.as < ast::Decl* > () }; }
#line 1923 "parser/parser.cpp"
    break;

  case 30: // decl_list: decl_list decl
#line 430 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(yystack_[0].value.as < ast::Decl* > ()); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 1929 "parser/parser.cpp"
    break;

  case 31: // decl: fn_decl
#line 435 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1935 "parser/parser.cpp"
    break;

  case 32: // decl: struct_decl
#line 437 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1941 "parser/parser.cpp"
    break;

  case 33: // fn_decl: fn_decl_def
#line 442 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = yystack_[0].value.as < ast::FunctionDecl* > (); }
#line 1947 "parser/parser.cpp"
    break;

  case 34: // fn_decl: fn_decl_proto
#line 444 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = yystack_[0].value.as < ast::FunctionDecl* > (); }
#line 1953 "parser/parser.cpp"
    break;

  case 35: // fn_decl_def: TOK_FN ident type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr block
#line 449 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[6].value.as < Str > (), std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[7].location, yystack_[0].location)); }
#line 1959 "parser/parser.cpp"
    break;

  case 36: // fn_decl_proto: TOK_FN ident type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 454 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(yystack_[6].value.as < Str > (), std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), nullptr, combine(yystack_[7].location, yystack_[1].location)); }
#line 1965 "parser/parser.cpp"
    break;

  case 37: // struct_decl: struct_decl_def
#line 459 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 1971 "parser/parser.cpp"
    break;

  case 38: // struct_decl: struct_decl_fwd
#line 461 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 1977 "parser/parser.cpp"
    break;

  case 39: // struct_decl_def: TOK_STRUCT ident type_params_opt TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 466 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[4].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()), combine(yystack_[5].location, yystack_[0].location)); }
#line 1983 "parser/parser.cpp"
    break;

  case 40: // struct_decl_fwd: TOK_STRUCT ident type_params_opt TOK_SMCLN
#line 471 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(yystack_[2].value.as < Str > (), std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()), std::vector<ast::FieldDecl*>{}, combine(yystack_[3].location, yystack_[0].location)); }
#line 1989 "parser/parser.cpp"
    break;

  case 41: // field_decl_list_opt: %empty
#line 476 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 1995 "parser/parser.cpp"
    break;

  case 42: // field_decl_list_opt: field_decl_list
#line 478 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2001 "parser/parser.cpp"
    break;

  case 43: // field_decl_list: field_decl
#line 483 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{ yystack_[0].value.as < ast::FieldDecl* > () }; }
#line 2007 "parser/parser.cpp"
    break;

  case 44: // field_decl_list: field_decl_list field_decl
#line 485 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2013 "parser/parser.cpp"
    break;

  case 45: // field_decl: ident TOK_COLON type_expr TOK_SMCLN
#line 490 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Priv, combine(yystack_[3].location, yystack_[0].location)); }
#line 2019 "parser/parser.cpp"
    break;

  case 46: // field_decl: TOK_PUB ident TOK_COLON type_expr TOK_SMCLN
#line 492 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::FieldDecl::Visibility::Publ, combine(yystack_[4].location, yystack_[0].location)); }
#line 2025 "parser/parser.cpp"
    break;

  case 47: // ret_type_expr: TOK_ARROW type_expr
#line 497 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2031 "parser/parser.cpp"
    break;

  case 48: // param_list_opt: %empty
#line 502 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 2037 "parser/parser.cpp"
    break;

  case 49: // param_list_opt: param_list
#line 504 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2043 "parser/parser.cpp"
    break;

  case 50: // param_list: param
#line 509 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{ yystack_[0].value.as < ast::ParamDecl* > () }; }
#line 2049 "parser/parser.cpp"
    break;

  case 51: // param_list: param_list TOK_COMMA param
#line 511 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2055 "parser/parser.cpp"
    break;

  case 52: // param_list: param_list TOK_COMMA
#line 513 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2061 "parser/parser.cpp"
    break;

  case 53: // param: ident TOK_COLON type_expr
#line 518 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2067 "parser/parser.cpp"
    break;

  case 54: // type_expr: ref_type_expr
#line 530 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 2073 "parser/parser.cpp"
    break;

  case 55: // type_expr: type_postfix
#line 532 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2079 "parser/parser.cpp"
    break;

  case 56: // ref_type_expr: TOK_AMP ref_mutability type_postfix
#line 537 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::RefTypeExpr::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2085 "parser/parser.cpp"
    break;

  case 57: // ref_mutability: %empty
#line 541 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 2091 "parser/parser.cpp"
    break;

  case 58: // ref_mutability: TOK_IMM
#line 542 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Imm; }
#line 2097 "parser/parser.cpp"
    break;

  case 59: // ref_mutability: TOK_MUT
#line 543 "parser/parser_rules.y"
                { yylhs.value.as < ast::RefTypeExpr::Mutability > () = ast::RefTypeExpr::Mutability::Mut; }
#line 2103 "parser/parser.cpp"
    break;

  case 60: // type_postfix: type_primary
#line 548 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2109 "parser/parser.cpp"
    break;

  case 61: // type_postfix: type_postfix TOK_LBRACK expr TOK_RBRACK
#line 550 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location))); }
#line 2115 "parser/parser.cpp"
    break;

  case 62: // type_primary: builtin_type_expr
#line 555 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 2121 "parser/parser.cpp"
    break;

  case 63: // type_primary: path_type_expr
#line 557 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 2127 "parser/parser.cpp"
    break;

  case 64: // type_primary: TOK_LPAR type_expr TOK_RPAR
#line 559 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[1].value.as < ast::TypeExpr* > (); }
#line 2133 "parser/parser.cpp"
    break;

  case 65: // builtin_type_expr: TOK_I8
#line 563 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 2139 "parser/parser.cpp"
    break;

  case 66: // builtin_type_expr: TOK_U8
#line 564 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 2145 "parser/parser.cpp"
    break;

  case 67: // builtin_type_expr: TOK_I16
#line 565 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 2151 "parser/parser.cpp"
    break;

  case 68: // builtin_type_expr: TOK_U16
#line 566 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 2157 "parser/parser.cpp"
    break;

  case 69: // builtin_type_expr: TOK_I32
#line 567 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 2163 "parser/parser.cpp"
    break;

  case 70: // builtin_type_expr: TOK_U32
#line 568 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 2169 "parser/parser.cpp"
    break;

  case 71: // builtin_type_expr: TOK_I64
#line 569 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 2175 "parser/parser.cpp"
    break;

  case 72: // builtin_type_expr: TOK_U64
#line 570 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 2181 "parser/parser.cpp"
    break;

  case 73: // builtin_type_expr: TOK_I128
#line 571 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 2187 "parser/parser.cpp"
    break;

  case 74: // builtin_type_expr: TOK_U128
#line 572 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 2193 "parser/parser.cpp"
    break;

  case 75: // builtin_type_expr: TOK_F32
#line 573 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 2199 "parser/parser.cpp"
    break;

  case 76: // builtin_type_expr: TOK_F64
#line 574 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 2205 "parser/parser.cpp"
    break;

  case 77: // builtin_type_expr: TOK_BOOL
#line 575 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 2211 "parser/parser.cpp"
    break;

  case 78: // builtin_type_expr: TOK_CHAR
#line 576 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 2217 "parser/parser.cpp"
    break;

  case 79: // path_type_expr: path_expr type_args
#line 581 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[1].value.as < ast::PathExpr* > (), std::move(yystack_[0].value.as < std::vector<ast::TypeExpr*> > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2223 "parser/parser.cpp"
    break;

  case 80: // block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 590 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), combine(yystack_[2].location, yystack_[0].location)); }
#line 2229 "parser/parser.cpp"
    break;

  case 81: // stmt_list_opt: %empty
#line 595 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{}; }
#line 2235 "parser/parser.cpp"
    break;

  case 82: // stmt_list_opt: stmt_list
#line 597 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[0].value.as < std::vector<ast::Statement*> > ()); }
#line 2241 "parser/parser.cpp"
    break;

  case 83: // stmt_list: stmt
#line 602 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{ yystack_[0].value.as < ast::Statement* > () }; }
#line 2247 "parser/parser.cpp"
    break;

  case 84: // stmt_list: stmt_list stmt
#line 604 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Statement*> > ().push_back(yystack_[0].value.as < ast::Statement* > ()); yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()); }
#line 2253 "parser/parser.cpp"
    break;

  case 85: // stmt: simple_stmt
#line 609 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2259 "parser/parser.cpp"
    break;

  case 86: // stmt: compound_stmt
#line 611 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2265 "parser/parser.cpp"
    break;

  case 87: // simple_stmt: var_decl_stmt
#line 615 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::VarDeclStatement* > ()); }
#line 2271 "parser/parser.cpp"
    break;

  case 88: // simple_stmt: return_stmt
#line 616 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ReturnStatement* > ()); }
#line 2277 "parser/parser.cpp"
    break;

  case 89: // simple_stmt: break_stmt
#line 617 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BreakStatement* > ()); }
#line 2283 "parser/parser.cpp"
    break;

  case 90: // simple_stmt: continue_stmt
#line 618 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ContinueStatement* > ()); }
#line 2289 "parser/parser.cpp"
    break;

  case 91: // simple_stmt: expr_stmt
#line 619 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ExprStatement* > ()); }
#line 2295 "parser/parser.cpp"
    break;

  case 92: // compound_stmt: block
#line 623 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 2301 "parser/parser.cpp"
    break;

  case 93: // compound_stmt: if_stmt
#line 624 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::IfStatement* > ()); }
#line 2307 "parser/parser.cpp"
    break;

  case 94: // compound_stmt: while_stmt
#line 625 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::WhileStatement* > ()); }
#line 2313 "parser/parser.cpp"
    break;

  case 95: // compound_stmt: do_while_stmt
#line 626 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::DoWhileStatement* > ()); }
#line 2319 "parser/parser.cpp"
    break;

  case 96: // return_stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 631 "parser/parser_rules.y"
    { yylhs.value.as < ast::ReturnStatement* > () = ast.mk_return_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2325 "parser/parser.cpp"
    break;

  case 97: // if_stmt: TOK_IF TOK_LPAR expr TOK_RPAR block elseif_list else_part
#line 636 "parser/parser_rules.y"
    { yylhs.value.as < ast::IfStatement* > () = ast.mk_if_stmt(yystack_[4].value.as < ast::Expr* > (), yystack_[2].value.as < ast::BlockStatement* > (), std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()), yystack_[0].value.as < ast::ElseStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2331 "parser/parser.cpp"
    break;

  case 98: // elseif_list: %empty
#line 641 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::vector<ast::ElseIfStatement*>{}; }
#line 2337 "parser/parser.cpp"
    break;

  case 99: // elseif_list: elseif_list elseif
#line 643 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ().push_back(yystack_[0].value.as < ast::ElseIfStatement* > ()); yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()); }
#line 2343 "parser/parser.cpp"
    break;

  case 100: // elseif: TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR block
#line 648 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseIfStatement* > () = ast.mk_else_if_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[5].location, yystack_[0].location)); }
#line 2349 "parser/parser.cpp"
    break;

  case 101: // else_part: %empty
#line 653 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = nullptr; }
#line 2355 "parser/parser.cpp"
    break;

  case 102: // else_part: TOK_ELSE block
#line 655 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = ast.mk_else_stmt(yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2361 "parser/parser.cpp"
    break;

  case 103: // while_stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR block
#line 660 "parser/parser_rules.y"
    { yylhs.value.as < ast::WhileStatement* > () = ast.mk_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 2367 "parser/parser.cpp"
    break;

  case 104: // do_while_stmt: TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 665 "parser/parser_rules.y"
    { yylhs.value.as < ast::DoWhileStatement* > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2373 "parser/parser.cpp"
    break;

  case 105: // break_stmt: TOK_BREAK TOK_SMCLN
#line 670 "parser/parser_rules.y"
    { yylhs.value.as < ast::BreakStatement* > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2379 "parser/parser.cpp"
    break;

  case 106: // continue_stmt: TOK_CONTINUE TOK_SMCLN
#line 675 "parser/parser_rules.y"
    { yylhs.value.as < ast::ContinueStatement* > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2385 "parser/parser.cpp"
    break;

  case 107: // expr_stmt: expr TOK_SMCLN
#line 680 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprStatement* > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2391 "parser/parser.cpp"
    break;

  case 108: // var_decl_stmt: var_decl
#line 692 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDeclStatement* > () = ast.mk_var_decl_stmt(yystack_[0].value.as < ast::VarDecl* > (), yystack_[0].location); }
#line 2397 "parser/parser.cpp"
    break;

  case 109: // var_decl: var_decl_default
#line 696 "parser/parser_rules.y"
                     { yylhs.value.as < ast::VarDecl* > () = yystack_[0].value.as < ast::VarDecl* > (); }
#line 2403 "parser/parser.cpp"
    break;

  case 110: // var_decl: var_decl_imm
#line 697 "parser/parser_rules.y"
                     { yylhs.value.as < ast::VarDecl* > () = yystack_[0].value.as < ast::VarDecl* > (); }
#line 2409 "parser/parser.cpp"
    break;

  case 111: // var_decl: var_decl_mut
#line 698 "parser/parser_rules.y"
                     { yylhs.value.as < ast::VarDecl* > () = yystack_[0].value.as < ast::VarDecl* > (); }
#line 2415 "parser/parser.cpp"
    break;

  case 112: // var_decl_default: ident TOK_COLON type_expr TOK_SMCLN
#line 703 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Imm, /*init*/nullptr, combine(yystack_[3].location, yystack_[0].location)); }
#line 2421 "parser/parser.cpp"
    break;

  case 113: // var_decl_default: ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 705 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Imm, /*init*/yystack_[1].value.as < ast::Expr* > (), combine(yystack_[5].location, yystack_[0].location)); }
#line 2427 "parser/parser.cpp"
    break;

  case 114: // var_decl_imm: TOK_IMM ident TOK_COLON type_expr TOK_SMCLN
#line 710 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Imm, /*init*/nullptr, combine(yystack_[4].location, yystack_[0].location)); }
#line 2433 "parser/parser.cpp"
    break;

  case 115: // var_decl_imm: TOK_IMM ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 712 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Imm, /*init*/yystack_[1].value.as < ast::Expr* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2439 "parser/parser.cpp"
    break;

  case 116: // var_decl_mut: TOK_MUT ident TOK_COLON type_expr TOK_SMCLN
#line 717 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Mut, /*init*/nullptr, combine(yystack_[4].location, yystack_[0].location)); }
#line 2445 "parser/parser.cpp"
    break;

  case 117: // var_decl_mut: TOK_MUT ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 719 "parser/parser_rules.y"
    { yylhs.value.as < ast::VarDecl* > () = ast.mk_var_decl(yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (), ast::VarDecl::Mutability::Mut, /*init*/yystack_[1].value.as < ast::Expr* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2451 "parser/parser.cpp"
    break;

  case 118: // expr: assign
#line 728 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2457 "parser/parser.cpp"
    break;

  case 119: // expr_opt: %empty
#line 732 "parser/parser_rules.y"
                { yylhs.value.as < ast::Expr* > () = nullptr; }
#line 2463 "parser/parser.cpp"
    break;

  case 120: // expr_opt: expr
#line 733 "parser/parser_rules.y"
                { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2469 "parser/parser.cpp"
    break;

  case 121: // assign: cond
#line 738 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2475 "parser/parser.cpp"
    break;

  case 122: // assign: postfix TOK_ASSIGN assign
#line 739 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), AssignOp::Assign,   combine(yystack_[2].location, yystack_[0].location)); }
#line 2481 "parser/parser.cpp"
    break;

  case 123: // assign: postfix TOK_PLUS_ASSIGN assign
#line 740 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), AssignOp::Add,      combine(yystack_[2].location, yystack_[0].location)); }
#line 2487 "parser/parser.cpp"
    break;

  case 124: // assign: postfix TOK_MIN_ASSIGN assign
#line 741 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 2493 "parser/parser.cpp"
    break;

  case 125: // assign: postfix TOK_MUL_ASSIGN assign
#line 742 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 2499 "parser/parser.cpp"
    break;

  case 126: // assign: postfix TOK_DIV_ASSIGN assign
#line 743 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), AssignOp::Divide,   combine(yystack_[2].location, yystack_[0].location)); }
#line 2505 "parser/parser.cpp"
    break;

  case 127: // cond: logic_or
#line 748 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2511 "parser/parser.cpp"
    break;

  case 128: // logic_or: logic_and
#line 753 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2517 "parser/parser.cpp"
    break;

  case 129: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 755 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2523 "parser/parser.cpp"
    break;

  case 130: // logic_and: equality
#line 760 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2529 "parser/parser.cpp"
    break;

  case 131: // logic_and: logic_and TOK_BOOL_AND equality
#line 762 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2535 "parser/parser.cpp"
    break;

  case 132: // equality: relational
#line 767 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2541 "parser/parser.cpp"
    break;

  case 133: // equality: equality TOK_EQUAL relational
#line 769 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::equal,     yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2547 "parser/parser.cpp"
    break;

  case 134: // equality: equality TOK_NEQUAL relational
#line 771 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2553 "parser/parser.cpp"
    break;

  case 135: // relational: additive
#line 776 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2559 "parser/parser.cpp"
    break;

  case 136: // relational: relational TOK_LESS additive
#line 778 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less,          yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2565 "parser/parser.cpp"
    break;

  case 137: // relational: relational TOK_LEQ additive
#line 780 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal,    yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2571 "parser/parser.cpp"
    break;

  case 138: // relational: relational TOK_GREATER additive
#line 782 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater,       yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2577 "parser/parser.cpp"
    break;

  case 139: // relational: relational TOK_GEQ additive
#line 784 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2583 "parser/parser.cpp"
    break;

  case 140: // additive: multiplicative
#line 789 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2589 "parser/parser.cpp"
    break;

  case 141: // additive: additive TOK_PLUS multiplicative
#line 791 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::add,      yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2595 "parser/parser.cpp"
    break;

  case 142: // additive: additive TOK_MINUS multiplicative
#line 793 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2601 "parser/parser.cpp"
    break;

  case 143: // multiplicative: unary
#line 798 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2607 "parser/parser.cpp"
    break;

  case 144: // multiplicative: multiplicative TOK_STAR unary
#line 800 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2613 "parser/parser.cpp"
    break;

  case 145: // multiplicative: multiplicative TOK_SLASH unary
#line 802 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::divide,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2619 "parser/parser.cpp"
    break;

  case 146: // multiplicative: multiplicative TOK_MODULO unary
#line 804 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2625 "parser/parser.cpp"
    break;

  case 147: // unary: TOK_MINUS unary
#line 809 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::negation,     yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2631 "parser/parser.cpp"
    break;

  case 148: // unary: TOK_NEGATION unary
#line 811 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2637 "parser/parser.cpp"
    break;

  case 149: // unary: TOK_INC unary
#line 813 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2643 "parser/parser.cpp"
    break;

  case 150: // unary: TOK_DEC unary
#line 815 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2649 "parser/parser.cpp"
    break;

  case 151: // unary: postfix
#line 817 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2655 "parser/parser.cpp"
    break;

  case 152: // postfix: primary
#line 822 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2661 "parser/parser.cpp"
    break;

  case 153: // postfix: postfix type_args TOK_LPAR arg_list_opt TOK_RPAR
#line 824 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Expr* > () = ast.mk_call_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[4].location, yystack_[0].location));
    }
#line 2669 "parser/parser.cpp"
    break;

  case 154: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 828 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_index(yystack_[3].value.as < ast::Expr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location)); }
#line 2675 "parser/parser.cpp"
    break;

  case 155: // postfix: postfix TOK_DOT ident
#line 830 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_field_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2681 "parser/parser.cpp"
    break;

  case 156: // postfix: postfix TOK_INC
#line 832 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2687 "parser/parser.cpp"
    break;

  case 157: // postfix: postfix TOK_DEC
#line 834 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2693 "parser/parser.cpp"
    break;

  case 158: // postfix: postfix type_args TOK_LCBRA field_inits_opt TOK_RCBRA
#line 836 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_struct_literal_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()), combine(yystack_[4].location, yystack_[1].location)); }
#line 2699 "parser/parser.cpp"
    break;

  case 159: // arg_list_opt: %empty
#line 841 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2705 "parser/parser.cpp"
    break;

  case 160: // arg_list_opt: arg_list
#line 843 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 2711 "parser/parser.cpp"
    break;

  case 161: // arg_list: expr
#line 848 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 2717 "parser/parser.cpp"
    break;

  case 162: // arg_list: arg_list TOK_COMMA expr
#line 850 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2723 "parser/parser.cpp"
    break;

  case 163: // arg_list: arg_list TOK_COMMA
#line 852 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2729 "parser/parser.cpp"
    break;

  case 164: // int_literal_type_opt: %empty
#line 860 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = std::nullopt; }
#line 2735 "parser/parser.cpp"
    break;

  case 165: // int_literal_type_opt: TOK_AS TOK_I8
#line 861 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I8; }
#line 2741 "parser/parser.cpp"
    break;

  case 166: // int_literal_type_opt: TOK_AS TOK_U8
#line 862 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U8; }
#line 2747 "parser/parser.cpp"
    break;

  case 167: // int_literal_type_opt: TOK_AS TOK_I16
#line 863 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I16; }
#line 2753 "parser/parser.cpp"
    break;

  case 168: // int_literal_type_opt: TOK_AS TOK_U16
#line 864 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U16; }
#line 2759 "parser/parser.cpp"
    break;

  case 169: // int_literal_type_opt: TOK_AS TOK_I32
#line 865 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I32; }
#line 2765 "parser/parser.cpp"
    break;

  case 170: // int_literal_type_opt: TOK_AS TOK_U32
#line 866 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U32; }
#line 2771 "parser/parser.cpp"
    break;

  case 171: // int_literal_type_opt: TOK_AS TOK_I64
#line 867 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I64; }
#line 2777 "parser/parser.cpp"
    break;

  case 172: // int_literal_type_opt: TOK_AS TOK_U64
#line 868 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U64; }
#line 2783 "parser/parser.cpp"
    break;

  case 173: // int_literal_type_opt: TOK_AS TOK_I128
#line 869 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I128; }
#line 2789 "parser/parser.cpp"
    break;

  case 174: // int_literal_type_opt: TOK_AS TOK_U128
#line 870 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U128; }
#line 2795 "parser/parser.cpp"
    break;

  case 175: // float_literal_type_opt: %empty
#line 874 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = std::nullopt; }
#line 2801 "parser/parser.cpp"
    break;

  case 176: // float_literal_type_opt: TOK_AS TOK_F32
#line 875 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F32; }
#line 2807 "parser/parser.cpp"
    break;

  case 177: // float_literal_type_opt: TOK_AS TOK_F64
#line 876 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F64; }
#line 2813 "parser/parser.cpp"
    break;

  case 178: // primary: path_expr
#line 885 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(yystack_[0].value.as < ast::PathExpr* > ()); }
#line 2819 "parser/parser.cpp"
    break;

  case 179: // primary: TOK_INT_LITERAL int_literal_type_opt
#line 887 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::IntKind> > (), yystack_[1].location); }
#line 2825 "parser/parser.cpp"
    break;

  case 180: // primary: TOK_FLOAT_LITERAL float_literal_type_opt
#line 889 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_float_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::FloatKind> > (), yystack_[1].location); }
#line 2831 "parser/parser.cpp"
    break;

  case 181: // primary: TOK_STRING_LITERAL
#line 891 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2837 "parser/parser.cpp"
    break;

  case 182: // primary: TOK_BOOL_LITERAL
#line 893 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl::rt::boolean > (), yystack_[0].location); }
#line 2843 "parser/parser.cpp"
    break;

  case 183: // primary: TOK_CHAR_LITERAL
#line 895 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_char_literal_expr(yystack_[0].value.as < kl::rt::character > (), yystack_[0].location); }
#line 2849 "parser/parser.cpp"
    break;

  case 184: // primary: TOK_LPAR expr TOK_RPAR
#line 897 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[1].value.as < ast::Expr* > (); }
#line 2855 "parser/parser.cpp"
    break;

  case 185: // field_inits_opt: %empty
#line 902 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{}; }
#line 2861 "parser/parser.cpp"
    break;

  case 186: // field_inits_opt: field_inits
#line 904 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2867 "parser/parser.cpp"
    break;

  case 187: // field_inits: field_init
#line 909 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{ yystack_[0].value.as < ast::FieldInitExpr* > () }; }
#line 2873 "parser/parser.cpp"
    break;

  case 188: // field_inits: field_inits TOK_COMMA field_init
#line 911 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ().push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2879 "parser/parser.cpp"
    break;

  case 189: // field_inits: field_inits TOK_COMMA
#line 913 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 2885 "parser/parser.cpp"
    break;

  case 190: // field_init: ident TOK_COLON expr
#line 918 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr* > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2891 "parser/parser.cpp"
    break;


#line 2895 "parser/parser.cpp"

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


  const short parser::yypact_ninf_ = -142;

  const signed char parser::yytable_ninf_ = -23;

  const short
  parser::yypact_[] =
  {
       2,   -12,    56,  -142,    43,  -142,   -26,  -142,  -142,   -12,
      63,    43,  -142,  -142,   -12,    -8,   -12,   -12,  -142,    63,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   -12,
    -142,    44,    44,  -142,    72,   -12,    64,    83,  -142,  -142,
      22,  -142,   -10,  -142,   -12,   -12,  -142,   -12,    81,    88,
     -10,  -142,    87,    96,    94,  -142,  -142,    93,   210,  -142,
    -142,   210,    91,   -12,   210,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   210,
      79,    95,    90,   102,  -142,   108,  -142,  -142,  -142,  -142,
     210,    71,  -142,   105,   115,  -142,  -142,   261,   210,  -142,
    -142,    58,  -142,   144,  -142,  -142,  -142,  -142,   108,    23,
    -142,   138,   141,  -142,  -142,  -142,    58,    58,    58,    58,
      58,  -142,   118,  -142,  -142,    92,    97,    32,    -9,    48,
      67,  -142,   205,  -142,   123,   124,   121,    58,   -12,   -12,
     129,   130,   120,  -142,   126,   144,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,   139,   210,  -142,   282,  -142,    86,  -142,   146,  -142,
     168,  -142,  -142,  -142,  -142,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,   -12,
    -142,  -142,    58,    58,    58,    58,    58,   -34,    58,    58,
     184,  -142,   142,   143,   145,  -142,  -142,   210,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,    97,    32,    -9,    -9,    48,
      48,    48,    48,    67,    67,  -142,  -142,  -142,   147,  -142,
    -142,  -142,  -142,  -142,  -142,    58,   -12,   151,   153,   162,
    -142,   210,   210,   -40,  -142,  -142,   163,   157,   161,   160,
     165,  -142,   121,   121,    58,    13,    14,  -142,    58,  -142,
      58,    58,  -142,   -12,  -142,  -142,   172,  -142,    58,  -142,
      58,   167,  -142,  -142,  -142,   212,   169,   171,   175,  -142,
       1,  -142,  -142,  -142,  -142,  -142,   185,  -142,    58,   186,
     121,  -142
  };

  const unsigned char
  parser::yydefact_[] =
  {
       4,     0,     0,     2,     6,    15,     0,    12,     1,     0,
      27,     7,     8,     5,     0,     0,     0,     0,     3,    28,
      29,    31,    33,    34,    32,    37,    38,     9,    13,     0,
      10,    16,    16,    30,     0,     0,     0,     0,    11,    21,
       0,    18,    41,    40,    48,    20,    17,     0,     0,     0,
      42,    43,     0,     0,    49,    50,    19,     0,     0,    39,
      44,     0,     0,    52,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
      57,    14,    22,     0,    54,    55,    60,    62,    63,    53,
       0,     0,    51,     0,     0,    59,    58,     0,     0,    79,
      45,     0,    47,    81,    36,    35,    46,    64,    56,     0,
      24,   164,   175,   181,   182,   183,     0,     0,     0,     0,
       0,   178,     0,   118,   121,   127,   128,   130,   132,   135,
     140,   143,   151,   152,     0,     0,     0,   119,     0,     0,
       0,     0,    12,    92,     0,    82,    83,    85,    86,    88,
      93,    94,    95,    89,    90,    91,    87,   108,   109,   110,
     111,     0,    26,    23,     0,   179,     0,   180,     0,   148,
     151,   149,   150,   147,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     156,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,     0,     0,     0,   105,   106,     0,    80,    84,
     107,    25,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   176,   177,   184,   129,   131,   133,   134,   136,
     137,   138,   139,   141,   142,   144,   145,   146,     0,   155,
     122,   123,   124,   125,   126,   159,   185,     0,     0,     0,
      96,     0,     0,     0,   154,   161,     0,   160,     0,     0,
     186,   187,     0,     0,     0,     0,     0,   112,     0,   153,
     163,     0,   158,   189,    98,   103,     0,   116,     0,   114,
       0,     0,   162,   190,   188,   101,     0,     0,     0,   113,
       0,    99,    97,   104,   117,   115,     0,   102,     0,     0,
       0,   100
  };

  const short
  parser::yypgoto_[] =
  {
    -142,  -142,  -142,  -142,  -142,  -142,   218,    11,   -53,   -14,
     199,  -142,   204,   173,  -142,  -142,  -142,   232,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,   206,  -142,  -142,  -142,
     191,   -29,  -142,  -142,   170,  -142,  -142,  -142,   -90,  -142,
    -142,   113,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   -94,
    -142,  -141,  -142,  -142,    85,    89,   -43,  -114,   -42,   -79,
    -101,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   -11
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     2,     3,     4,    10,    11,    12,    81,   121,     7,
      36,    40,    41,   197,   109,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    49,    50,    51,    91,    53,    54,
      55,    83,    84,    97,    85,    86,    87,    88,   143,   144,
     145,   146,   147,   148,   149,   150,   285,   291,   292,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     202,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   256,   257,   165,   167,   133,   259,   260,   261
  };

  const short
  parser::yytable_[] =
  {
      28,   105,    31,    32,   296,    82,    47,   122,    82,   245,
     267,    82,     6,   246,    29,    34,   170,   170,   170,   170,
      15,    39,   168,     1,    13,     5,    82,     5,    48,    14,
      52,    39,    89,    57,   268,    93,    48,    82,   169,   171,
     172,   173,    30,   201,    82,    82,   200,    14,   103,    52,
      94,   240,   241,   242,   243,   244,     8,   179,   180,   181,
     182,   102,     9,   277,   279,   229,   230,   231,   232,   110,
      16,    45,   162,    17,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   278,   280,   142,
      46,   163,    95,    96,   238,     5,   111,   112,   113,   114,
     115,   116,   177,   178,   247,   248,   235,   236,   237,    82,
      35,    42,   183,   184,    43,   117,   118,   119,   103,   222,
     223,   104,    38,   120,   203,   204,    44,   281,   185,   186,
     187,   142,    58,   211,   227,   228,    59,   287,    61,   288,
      62,   233,   234,    63,    64,    90,    98,   134,   135,   136,
      14,   255,   100,   101,    82,   106,   137,   138,   139,   107,
     164,   140,   141,   166,   174,   175,   198,   199,   103,   176,
     276,   207,   274,   275,   208,   239,   282,   283,   253,   205,
     206,     5,   111,   112,   113,   114,   115,   116,   249,   210,
     224,   103,   250,   254,   251,   262,   252,   263,    82,    82,
     297,   117,   118,   119,   299,   264,   270,   269,   272,   120,
     301,   -22,   271,   188,   273,   -22,   286,   289,   290,   293,
     189,   294,   265,   266,    98,   295,   190,   191,   298,    27,
     300,    37,   258,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     5,   -22,    56,
     188,    33,   -22,    79,    92,    99,    60,   189,   209,   258,
     225,    98,   284,   190,   191,   226,     0,   108,     0,     0,
      80,     0,     0,     0,     0,     0,     0,     0,     0,   192,
     193,   194,   195,   196,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     5,     0,
       0,     0,     0,     0,    79,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221
  };

  const short
  parser::yycheck_[] =
  {
      14,    91,    16,    17,     3,    58,    16,   101,    61,    43,
      50,    64,     1,    47,    22,    29,   117,   118,   119,   120,
       9,    35,   116,    21,    50,    37,    79,    37,    42,    55,
      44,    45,    61,    47,    74,    64,    50,    90,   117,   118,
     119,   120,    50,   137,    97,    98,   136,    55,    47,    63,
      79,   192,   193,   194,   195,   196,     0,    66,    67,    68,
      69,    90,    19,    50,    50,   179,   180,   181,   182,    98,
       7,    49,    49,    10,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,    74,    74,   103,
      68,    68,    13,    14,   188,    37,    38,    39,    40,    41,
      42,    43,    70,    71,   198,   199,   185,   186,   187,   162,
      66,    47,    64,    65,    50,    57,    58,    59,    47,    33,
      34,    50,    50,    65,   138,   139,    43,   268,    61,    62,
      63,   145,    51,   162,   177,   178,    48,   278,    51,   280,
      44,   183,   184,    49,    51,    54,    56,     3,     4,     5,
      55,   245,    50,    45,   207,    50,    12,    13,    14,    44,
      22,    17,    18,    22,    46,    73,    43,    43,    47,    72,
     264,    51,   262,   263,    48,   189,   270,   271,   207,    50,
      50,    37,    38,    39,    40,    41,    42,    43,     4,    50,
      44,    47,    50,    46,    51,    44,    51,    44,   251,   252,
     290,    57,    58,    59,   298,    43,    49,    44,    48,    65,
     300,    43,    51,    45,    49,    47,    44,    50,     6,    50,
      52,    50,   251,   252,    56,    50,    58,    59,    43,    11,
      44,    32,   246,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    43,    45,
      45,    19,    47,    43,    63,    82,    50,    52,   145,   273,
     175,    56,   273,    58,    59,   176,    -1,    97,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      75,    76,    77,    78,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    43,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    21,    83,    84,    85,    37,    89,    91,     0,    19,
      86,    87,    88,    50,    55,    89,     7,    10,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    88,    91,    22,
      50,    91,    91,    99,    91,    66,    92,    92,    50,    91,
      93,    94,    47,    50,    43,    49,    68,    16,    91,   106,
     107,   108,    91,   110,   111,   112,    94,    91,    51,    48,
     108,    51,    44,    49,    51,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    43,
      60,    89,    90,   113,   114,   116,   117,   118,   119,   113,
      54,   109,   112,   113,   113,    13,    14,   115,    56,    95,
      50,    45,   113,    47,    50,   120,    50,    44,   116,    96,
     113,    38,    39,    40,    41,    42,    43,    57,    58,    59,
      65,    90,   141,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   157,     3,     4,     5,    12,    13,    14,
      17,    18,    91,   120,   121,   122,   123,   124,   125,   126,
     127,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,    49,    68,    22,   155,    22,   156,   141,   151,
     152,   151,   151,   151,    46,    73,    72,    70,    71,    66,
      67,    68,    69,    64,    65,    61,    62,    63,    45,    52,
      58,    59,    74,    75,    76,    77,    78,    95,    43,    43,
     120,   141,   142,    91,    91,    50,    50,    51,    48,   123,
      50,   113,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    44,   146,   147,   148,   148,   149,
     149,   149,   149,   150,   150,   151,   151,   151,   141,    91,
     143,   143,   143,   143,   143,    43,    47,   141,   141,     4,
      50,    51,    51,   113,    46,   141,   153,   154,    91,   158,
     159,   160,    44,    44,    43,   113,   113,    50,    74,    44,
      49,    51,    48,    49,   120,   120,   141,    50,    74,    50,
      74,   143,   141,   141,   160,   128,    44,   143,   143,    50,
       6,   129,   130,    50,    50,    50,     3,   120,    43,   141,
      44,   120
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    91,    92,    92,    93,    93,
      93,    94,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   102,   103,   103,   104,
     105,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111,   111,   111,   112,   113,   113,   114,   115,   115,   115,
     116,   116,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   124,
     124,   124,   125,   125,   125,   125,   126,   127,   128,   128,
     129,   130,   130,   131,   132,   133,   134,   135,   136,   137,
     137,   137,   138,   138,   139,   139,   140,   140,   141,   142,
     142,   143,   143,   143,   143,   143,   143,   144,   145,   145,
     146,   146,   147,   147,   147,   148,   148,   148,   148,   148,
     149,   149,   149,   150,   150,   150,   150,   151,   151,   151,
     151,   151,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   154,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   156,   156,   156,   157,   157,
     157,   157,   157,   157,   157,   158,   158,   159,   159,   159,
     160
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     0,     3,     0,     1,     1,     2,
       3,     5,     1,     3,     1,     1,     0,     3,     1,     3,
       2,     1,     0,     3,     1,     3,     2,     0,     1,     1,
       2,     1,     1,     1,     1,     8,     8,     1,     1,     6,
       4,     0,     1,     1,     2,     4,     5,     2,     0,     1,
       1,     3,     2,     3,     1,     1,     3,     0,     1,     1,
       1,     4,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     0,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     7,     0,     2,
       6,     0,     2,     5,     7,     2,     2,     2,     1,     1,
       1,     1,     4,     6,     5,     7,     5,     7,     1,     0,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     2,     2,     2,
       2,     1,     1,     5,     4,     3,     2,     2,     5,     0,
       1,     1,     3,     2,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     0,     2,     2,     1,     2,
       2,     1,     1,     1,     3,     0,     1,     1,     3,     2,
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
  "TOK_TYPE", "TOK_RETURN", "TOK_MUT", "TOK_IMM", "TOK_STATIC", "TOK_PUB",
  "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT", "TOK_EXPORT", "TOK_PACKAGE",
  "TOK_AS", "TOK_I8", "TOK_U8", "TOK_I16", "TOK_U16", "TOK_I32", "TOK_U32",
  "TOK_I64", "TOK_U64", "TOK_I128", "TOK_U128", "TOK_F32", "TOK_F64",
  "TOK_BOOL", "TOK_CHAR", "TOK_IDENTIFIER", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_CHAR_LITERAL", "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK",
  "TOK_LCBRA", "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON",
  "TOK_DOT", "TOK_QUESTION", "TOK_ARROW", "TOK_COLONCOLON",
  "TOK_TURBOFISH_S", "TOK_NEGATION", "TOK_INC", "TOK_DEC", "TOK_AMP",
  "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS", "TOK_MINUS",
  "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ", "TOK_EQUAL",
  "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit", "module",
  "package_opt", "import_list_opt", "import_list", "import_decl", "path",
  "path_expr", "ident", "type_params_opt", "type_param_list", "type_param",
  "type_args", "type_arg_list", "decl_list_opt", "decl_list", "decl",
  "fn_decl", "fn_decl_def", "fn_decl_proto", "struct_decl",
  "struct_decl_def", "struct_decl_fwd", "field_decl_list_opt",
  "field_decl_list", "field_decl", "ret_type_expr", "param_list_opt",
  "param_list", "param", "type_expr", "ref_type_expr", "ref_mutability",
  "type_postfix", "type_primary", "builtin_type_expr", "path_type_expr",
  "block", "stmt_list_opt", "stmt_list", "stmt", "simple_stmt",
  "compound_stmt", "return_stmt", "if_stmt", "elseif_list", "elseif",
  "else_part", "while_stmt", "do_while_stmt", "break_stmt",
  "continue_stmt", "expr_stmt", "var_decl_stmt", "var_decl",
  "var_decl_default", "var_decl_imm", "var_decl_mut", "expr", "expr_opt",
  "assign", "cond", "logic_or", "logic_and", "equality", "relational",
  "additive", "multiplicative", "unary", "postfix", "arg_list_opt",
  "arg_list", "int_literal_type_opt", "float_literal_type_opt", "primary",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   310,   310,   315,   325,   326,   332,   333,   338,   340,
     345,   347,   357,   359,   364,   369,   379,   380,   385,   387,
     389,   394,   400,   401,   406,   408,   410,   421,   422,   427,
     429,   434,   436,   441,   443,   448,   453,   458,   460,   465,
     470,   476,   477,   482,   484,   489,   491,   496,   502,   503,
     508,   510,   512,   517,   529,   531,   536,   541,   542,   543,
     547,   549,   554,   556,   558,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   580,
     589,   595,   596,   601,   603,   608,   610,   615,   616,   617,
     618,   619,   623,   624,   625,   626,   630,   635,   641,   642,
     647,   653,   654,   659,   664,   669,   674,   679,   691,   696,
     697,   698,   702,   704,   709,   711,   716,   718,   727,   732,
     733,   737,   739,   740,   741,   742,   743,   747,   752,   754,
     759,   761,   766,   768,   770,   775,   777,   779,   781,   783,
     788,   790,   792,   797,   799,   801,   803,   808,   810,   812,
     814,   816,   821,   823,   827,   829,   831,   833,   835,   841,
     842,   847,   849,   851,   860,   861,   862,   863,   864,   865,
     866,   867,   868,   869,   870,   874,   875,   876,   884,   886,
     888,   890,   892,   894,   896,   902,   903,   908,   910,   912,
     917
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


#line 8 "parser/parser_rules.y"
} // yy
#line 3747 "parser/parser.cpp"

#line 921 "parser/parser_rules.y"

