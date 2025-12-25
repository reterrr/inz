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
#line 43 "parser/parser_rules.y"

  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"
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

#line 164 "parser/parser.cpp"


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
#line 257 "parser/parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner& scanner_yyarg, ast::Ast& ast_yyarg, Translation& unit_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      scanner (scanner_yyarg),
      ast (ast_yyarg),
      unit (unit_yyarg)
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

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
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
      case symbol_kind::S_fn_decl_fwd: // fn_decl_fwd
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

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.YY_MOVE_OR_COPY< ast::VarStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.YY_MOVE_OR_COPY< ast::WhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
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

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
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
      case symbol_kind::S_fn_decl_fwd: // fn_decl_fwd
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

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.move< ast::VarStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
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

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
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
      case symbol_kind::S_fn_decl_fwd: // fn_decl_fwd
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

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.copy< ast::VarStmt* > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.copy< ast::WhileStatement* > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
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

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
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
      case symbol_kind::S_fn_decl_fwd: // fn_decl_fwd
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

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        value.move< ast::VarStmt* > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< ast::WhileStatement* > (that.value);
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
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

      case symbol_kind::S_anon_block: // anon_block
      case symbol_kind::S_fn_block: // fn_block
      case symbol_kind::S_if_block: // if_block
      case symbol_kind::S_else_if_block: // else_if_block
      case symbol_kind::S_else_block: // else_block
      case symbol_kind::S_while_block: // while_block
      case symbol_kind::S_do_while_block: // do_while_block
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
      case symbol_kind::S_fn_decl_fwd: // fn_decl_fwd
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

      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_var_stmt_default: // var_stmt_default
      case symbol_kind::S_var_stmt_imm: // var_stmt_imm
      case symbol_kind::S_var_stmt_mut: // var_stmt_mut
      case symbol_kind::S_var_stmt_static_default: // var_stmt_static_default
      case symbol_kind::S_var_stmt_static_imm: // var_stmt_static_imm
      case symbol_kind::S_var_stmt_static_mut: // var_stmt_static_mut
        yylhs.value.emplace< ast::VarStmt* > ();
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        yylhs.value.emplace< ast::WhileStatement* > ();
        break;

      case symbol_kind::S_TOK_BOOL_LITERAL: // TOK_BOOL_LITERAL
      case symbol_kind::S_pub_opt: // pub_opt
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
#line 325 "parser/parser_rules.y"
    { yylhs.value.as < ast::Module* > () = yystack_[0].value.as < ast::Module* > (); }
#line 1784 "parser/parser.cpp"
    break;

  case 3: // module: TOK_PACKAGE path_expr TOK_SMCLN import_list_opt decl_list_opt
#line 330 "parser/parser_rules.y"
    {
      auto* m = ast.mk_module(yystack_[3].value.as < ast::PathExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[4].location, yystack_[0].location));
      unit.addModule(m);
      yylhs.value.as < ast::Module* > () = m;
    }
#line 1794 "parser/parser.cpp"
    break;

  case 4: // import_list_opt: %empty
#line 339 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1800 "parser/parser.cpp"
    break;

  case 5: // import_list_opt: import_list
#line 341 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1806 "parser/parser.cpp"
    break;

  case 6: // import_list: import_decl
#line 346 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{ yystack_[0].value.as < ast::ImportDecl* > () }; }
#line 1812 "parser/parser.cpp"
    break;

  case 7: // import_list: import_list import_decl
#line 348 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1818 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT path_expr TOK_SMCLN
#line 353 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < ast::PathExpr* > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1824 "parser/parser.cpp"
    break;

  case 9: // import_decl: TOK_IMPORT path_expr TOK_AS ident TOK_SMCLN
#line 355 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < ast::PathExpr* > ()), std::optional<Str>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1830 "parser/parser.cpp"
    break;

  case 10: // path: ident
#line 365 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[0].value.as < Str > () }; }
#line 1836 "parser/parser.cpp"
    break;

  case 11: // path: path TOK_COLONCOLON ident
#line 367 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1842 "parser/parser.cpp"
    break;

  case 12: // path_expr: path
#line 372 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1848 "parser/parser.cpp"
    break;

  case 13: // ident: TOK_IDENTIFIER
#line 377 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1854 "parser/parser.cpp"
    break;

  case 14: // type_params_opt: %empty
#line 386 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{}; }
#line 1860 "parser/parser.cpp"
    break;

  case 15: // type_params_opt: TOK_LESS type_param_list TOK_GREATER
#line 388 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1866 "parser/parser.cpp"
    break;

  case 16: // type_param_list: type_param
#line 393 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{ yystack_[0].value.as < ast::TypeParamDecl* > () }; }
#line 1872 "parser/parser.cpp"
    break;

  case 17: // type_param_list: type_param_list TOK_COMMA type_param
#line 395 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ().push_back(yystack_[0].value.as < ast::TypeParamDecl* > ()); yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1878 "parser/parser.cpp"
    break;

  case 18: // type_param_list: type_param_list TOK_COMMA
#line 397 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1884 "parser/parser.cpp"
    break;

  case 19: // type_param: ident
#line 402 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeParamDecl* > () = ast.mk_type_param_decl(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1890 "parser/parser.cpp"
    break;

  case 20: // type_args: %empty
#line 407 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{}; }
#line 1896 "parser/parser.cpp"
    break;

  case 21: // type_args: TOK_TURBOFISH_S type_arg_list TOK_GREATER
#line 409 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1902 "parser/parser.cpp"
    break;

  case 22: // type_arg_list: type_expr
#line 414 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{ yystack_[0].value.as < ast::TypeExpr* > () }; }
#line 1908 "parser/parser.cpp"
    break;

  case 23: // type_arg_list: type_arg_list TOK_COMMA type_expr
#line 416 "parser/parser_rules.y"
      { yystack_[2].value.as < std::vector<ast::TypeExpr*> > ().push_back(yystack_[0].value.as < ast::TypeExpr* > ()); yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1914 "parser/parser.cpp"
    break;

  case 24: // type_arg_list: type_arg_list TOK_COMMA
#line 418 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1920 "parser/parser.cpp"
    break;

  case 25: // pub_opt: %empty
#line 427 "parser/parser_rules.y"
                { yylhs.value.as < kl::rt::boolean > () = false; }
#line 1926 "parser/parser.cpp"
    break;

  case 26: // pub_opt: TOK_PUB
#line 428 "parser/parser_rules.y"
                { yylhs.value.as < kl::rt::boolean > () = true;  }
#line 1932 "parser/parser.cpp"
    break;

  case 27: // decl_list_opt: %empty
#line 433 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 1938 "parser/parser.cpp"
    break;

  case 28: // decl_list_opt: decl_list
#line 435 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()); }
#line 1944 "parser/parser.cpp"
    break;

  case 29: // decl_list: decl
#line 440 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{ yystack_[0].value.as < ast::Decl* > () }; }
#line 1950 "parser/parser.cpp"
    break;

  case 30: // decl_list: decl_list decl
#line 442 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(yystack_[0].value.as < ast::Decl* > ()); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 1956 "parser/parser.cpp"
    break;

  case 31: // decl: fn_decl
#line 447 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FunctionDecl* > ()); }
#line 1962 "parser/parser.cpp"
    break;

  case 32: // decl: struct_decl
#line 449 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1968 "parser/parser.cpp"
    break;

  case 33: // fn_decl: fn_decl_def
#line 454 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = yystack_[0].value.as < ast::FunctionDecl* > (); }
#line 1974 "parser/parser.cpp"
    break;

  case 34: // fn_decl: fn_decl_fwd
#line 456 "parser/parser_rules.y"
    { yylhs.value.as < ast::FunctionDecl* > () = yystack_[0].value.as < ast::FunctionDecl* > (); }
#line 1980 "parser/parser.cpp"
    break;

  case 35: // fn_decl_def: pub_opt TOK_FN ident type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
#line 461 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* if pub exists start at TOK_PUB, else TOK_FN */
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(
            yystack_[6].value.as < Str > (),
            std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()),
            yystack_[1].value.as < ast::TypeExpr* > (),
            yystack_[0].value.as < ast::BlockStatement* > (),
            yystack_[8].value.as < kl::rt::boolean > (),                  /* <- second last arg: is_pub */
            combine(start, yystack_[0].location)
          );
    }
#line 1997 "parser/parser.cpp"
    break;

  case 36: // fn_decl_fwd: pub_opt TOK_FN ident type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 477 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* if pub exists start at TOK_PUB, else TOK_FN */
      yylhs.value.as < ast::FunctionDecl* > () = ast.mk_fn_decl(
            yystack_[6].value.as < Str > (),
            std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()),
            yystack_[1].value.as < ast::TypeExpr* > (),
            nullptr,
            yystack_[8].value.as < kl::rt::boolean > (),                  /* <- second last arg: is_pub */
            combine(start, yystack_[1].location)    /* keep old behavior: span ends at ret_type_expr */
          );
    }
#line 2014 "parser/parser.cpp"
    break;

  case 37: // struct_decl: struct_decl_def
#line 494 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2020 "parser/parser.cpp"
    break;

  case 38: // struct_decl: struct_decl_fwd
#line 496 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2026 "parser/parser.cpp"
    break;

  case 39: // struct_decl_def: pub_opt TOK_STRUCT ident type_params_opt TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 501 "parser/parser_rules.y"
    {
      auto start = yystack_[6].value.as < kl::rt::boolean > () ? yystack_[6].location : yystack_[5].location; /* if pub exists start at TOK_PUB, else TOK_STRUCT */
      yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(
            yystack_[4].value.as < Str > (),
            std::move(yystack_[3].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()),
            yystack_[6].value.as < kl::rt::boolean > (),                  /* <- second last arg: is_pub */
            combine(start, yystack_[0].location)
          );
    }
#line 2041 "parser/parser.cpp"
    break;

  case 40: // struct_decl_fwd: pub_opt TOK_STRUCT ident type_params_opt TOK_SMCLN
#line 515 "parser/parser_rules.y"
    {
      auto start = yystack_[4].value.as < kl::rt::boolean > () ? yystack_[4].location : yystack_[3].location; /* if pub exists start at TOK_PUB, else TOK_STRUCT */
      yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(
            yystack_[2].value.as < Str > (),
            std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::vector<ast::FieldDecl*>{},
            yystack_[4].value.as < kl::rt::boolean > (),                  /* <- second last arg: is_pub */
            combine(start, yystack_[0].location)    /* keep old behavior: include semicolon */
          );
    }
#line 2056 "parser/parser.cpp"
    break;

  case 41: // field_decl_list_opt: %empty
#line 530 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 2062 "parser/parser.cpp"
    break;

  case 42: // field_decl_list_opt: field_decl_list
#line 532 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2068 "parser/parser.cpp"
    break;

  case 43: // field_decl_list: field_decl
#line 537 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{ yystack_[0].value.as < ast::FieldDecl* > () }; }
#line 2074 "parser/parser.cpp"
    break;

  case 44: // field_decl_list: field_decl_list field_decl
#line 539 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2080 "parser/parser.cpp"
    break;

  case 45: // field_decl: ident TOK_COLON type_expr TOK_SMCLN
#line 544 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Priv, combine(yystack_[3].location, yystack_[0].location)); }
#line 2086 "parser/parser.cpp"
    break;

  case 46: // field_decl: TOK_PUB ident TOK_COLON type_expr TOK_SMCLN
#line 546 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Publ, combine(yystack_[4].location, yystack_[0].location)); }
#line 2092 "parser/parser.cpp"
    break;

  case 47: // ret_type_expr: TOK_ARROW type_expr
#line 551 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2098 "parser/parser.cpp"
    break;

  case 48: // param_list_opt: %empty
#line 556 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 2104 "parser/parser.cpp"
    break;

  case 49: // param_list_opt: param_list
#line 558 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2110 "parser/parser.cpp"
    break;

  case 50: // param_list: param
#line 563 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{ yystack_[0].value.as < ast::ParamDecl* > () }; }
#line 2116 "parser/parser.cpp"
    break;

  case 51: // param_list: param_list TOK_COMMA param
#line 565 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2122 "parser/parser.cpp"
    break;

  case 52: // param_list: param_list TOK_COMMA
#line 567 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2128 "parser/parser.cpp"
    break;

  case 53: // param: ident TOK_COLON type_expr
#line 572 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2134 "parser/parser.cpp"
    break;

  case 54: // type_expr: ref_type_expr
#line 584 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 2140 "parser/parser.cpp"
    break;

  case 55: // type_expr: type_postfix
#line 586 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2146 "parser/parser.cpp"
    break;

  case 56: // ref_type_expr: TOK_AMP ref_mutability type_postfix
#line 591 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2152 "parser/parser.cpp"
    break;

  case 57: // ref_mutability: %empty
#line 595 "parser/parser_rules.y"
                { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2158 "parser/parser.cpp"
    break;

  case 58: // ref_mutability: TOK_IMM
#line 596 "parser/parser_rules.y"
                { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2164 "parser/parser.cpp"
    break;

  case 59: // ref_mutability: TOK_MUT
#line 597 "parser/parser_rules.y"
                { yylhs.value.as < ast::Mutability > () = ast::Mutability::Mut; }
#line 2170 "parser/parser.cpp"
    break;

  case 60: // type_postfix: type_primary
#line 602 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2176 "parser/parser.cpp"
    break;

  case 61: // type_postfix: type_postfix TOK_LBRACK expr TOK_RBRACK
#line 604 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location))); }
#line 2182 "parser/parser.cpp"
    break;

  case 62: // type_primary: builtin_type_expr
#line 609 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 2188 "parser/parser.cpp"
    break;

  case 63: // type_primary: path_type_expr
#line 611 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 2194 "parser/parser.cpp"
    break;

  case 64: // type_primary: TOK_LPAR type_expr TOK_RPAR
#line 613 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[1].value.as < ast::TypeExpr* > (); }
#line 2200 "parser/parser.cpp"
    break;

  case 65: // builtin_type_expr: TOK_I8
#line 617 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 2206 "parser/parser.cpp"
    break;

  case 66: // builtin_type_expr: TOK_U8
#line 618 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 2212 "parser/parser.cpp"
    break;

  case 67: // builtin_type_expr: TOK_I16
#line 619 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 2218 "parser/parser.cpp"
    break;

  case 68: // builtin_type_expr: TOK_U16
#line 620 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 2224 "parser/parser.cpp"
    break;

  case 69: // builtin_type_expr: TOK_I32
#line 621 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 2230 "parser/parser.cpp"
    break;

  case 70: // builtin_type_expr: TOK_U32
#line 622 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 2236 "parser/parser.cpp"
    break;

  case 71: // builtin_type_expr: TOK_I64
#line 623 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 2242 "parser/parser.cpp"
    break;

  case 72: // builtin_type_expr: TOK_U64
#line 624 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 2248 "parser/parser.cpp"
    break;

  case 73: // builtin_type_expr: TOK_I128
#line 625 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 2254 "parser/parser.cpp"
    break;

  case 74: // builtin_type_expr: TOK_U128
#line 626 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 2260 "parser/parser.cpp"
    break;

  case 75: // builtin_type_expr: TOK_F32
#line 627 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 2266 "parser/parser.cpp"
    break;

  case 76: // builtin_type_expr: TOK_F64
#line 628 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 2272 "parser/parser.cpp"
    break;

  case 77: // builtin_type_expr: TOK_BOOL
#line 629 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 2278 "parser/parser.cpp"
    break;

  case 78: // builtin_type_expr: TOK_CHAR
#line 630 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 2284 "parser/parser.cpp"
    break;

  case 79: // path_type_expr: path_expr type_args
#line 635 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[1].value.as < ast::PathExpr* > (), std::move(yystack_[0].value.as < std::vector<ast::TypeExpr*> > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2290 "parser/parser.cpp"
    break;

  case 80: // anon_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 644 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Anon, combine(yystack_[2].location, yystack_[0].location)); }
#line 2296 "parser/parser.cpp"
    break;

  case 81: // fn_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 649 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Fn, combine(yystack_[2].location, yystack_[0].location)); }
#line 2302 "parser/parser.cpp"
    break;

  case 82: // if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 654 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::If, combine(yystack_[2].location, yystack_[0].location)); }
#line 2308 "parser/parser.cpp"
    break;

  case 83: // else_if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 659 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::ElseIf, combine(yystack_[2].location, yystack_[0].location)); }
#line 2314 "parser/parser.cpp"
    break;

  case 84: // else_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 664 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Else, combine(yystack_[2].location, yystack_[0].location)); }
#line 2320 "parser/parser.cpp"
    break;

  case 85: // while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 669 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::While, combine(yystack_[2].location, yystack_[0].location)); }
#line 2326 "parser/parser.cpp"
    break;

  case 86: // do_while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 674 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::DoWhile, combine(yystack_[2].location, yystack_[0].location)); }
#line 2332 "parser/parser.cpp"
    break;

  case 87: // stmt_list_opt: %empty
#line 679 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{}; }
#line 2338 "parser/parser.cpp"
    break;

  case 88: // stmt_list_opt: stmt_list
#line 681 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[0].value.as < std::vector<ast::Statement*> > ()); }
#line 2344 "parser/parser.cpp"
    break;

  case 89: // stmt_list: stmt
#line 686 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{ yystack_[0].value.as < ast::Statement* > () }; }
#line 2350 "parser/parser.cpp"
    break;

  case 90: // stmt_list: stmt_list stmt
#line 688 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Statement*> > ().push_back(yystack_[0].value.as < ast::Statement* > ()); yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()); }
#line 2356 "parser/parser.cpp"
    break;

  case 91: // stmt: simple_stmt
#line 693 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2362 "parser/parser.cpp"
    break;

  case 92: // stmt: compound_stmt
#line 695 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2368 "parser/parser.cpp"
    break;

  case 93: // simple_stmt: var_stmt
#line 699 "parser/parser_rules.y"
                  { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::VarStmt* > ()); }
#line 2374 "parser/parser.cpp"
    break;

  case 94: // simple_stmt: return_stmt
#line 700 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ReturnStatement* > ()); }
#line 2380 "parser/parser.cpp"
    break;

  case 95: // simple_stmt: break_stmt
#line 701 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BreakStatement* > ()); }
#line 2386 "parser/parser.cpp"
    break;

  case 96: // simple_stmt: continue_stmt
#line 702 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ContinueStatement* > ()); }
#line 2392 "parser/parser.cpp"
    break;

  case 97: // simple_stmt: expr_stmt
#line 703 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ExprStatement* > ()); }
#line 2398 "parser/parser.cpp"
    break;

  case 98: // compound_stmt: anon_block
#line 707 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 2404 "parser/parser.cpp"
    break;

  case 99: // compound_stmt: if_stmt
#line 708 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::IfStatement* > ()); }
#line 2410 "parser/parser.cpp"
    break;

  case 100: // compound_stmt: while_stmt
#line 709 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::WhileStatement* > ()); }
#line 2416 "parser/parser.cpp"
    break;

  case 101: // compound_stmt: do_while_stmt
#line 710 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::DoWhileStatement* > ()); }
#line 2422 "parser/parser.cpp"
    break;

  case 102: // return_stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 715 "parser/parser_rules.y"
    { yylhs.value.as < ast::ReturnStatement* > () = ast.mk_return_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2428 "parser/parser.cpp"
    break;

  case 103: // if_stmt: TOK_IF TOK_LPAR expr TOK_RPAR if_block elseif_list else_part
#line 720 "parser/parser_rules.y"
    { yylhs.value.as < ast::IfStatement* > () = ast.mk_if_stmt(yystack_[4].value.as < ast::Expr* > (), yystack_[2].value.as < ast::BlockStatement* > (), std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()), yystack_[0].value.as < ast::ElseStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2434 "parser/parser.cpp"
    break;

  case 104: // elseif_list: %empty
#line 725 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::vector<ast::ElseIfStatement*>{}; }
#line 2440 "parser/parser.cpp"
    break;

  case 105: // elseif_list: elseif_list elseif
#line 727 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ().push_back(yystack_[0].value.as < ast::ElseIfStatement* > ()); yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()); }
#line 2446 "parser/parser.cpp"
    break;

  case 106: // elseif: TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR else_if_block
#line 732 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseIfStatement* > () = ast.mk_else_if_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[5].location, yystack_[0].location)); }
#line 2452 "parser/parser.cpp"
    break;

  case 107: // else_part: %empty
#line 737 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = nullptr; }
#line 2458 "parser/parser.cpp"
    break;

  case 108: // else_part: TOK_ELSE else_block
#line 739 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = ast.mk_else_stmt(yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2464 "parser/parser.cpp"
    break;

  case 109: // while_stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR while_block
#line 744 "parser/parser_rules.y"
    { yylhs.value.as < ast::WhileStatement* > () = ast.mk_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 2470 "parser/parser.cpp"
    break;

  case 110: // do_while_stmt: TOK_DO do_while_block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 749 "parser/parser_rules.y"
    { yylhs.value.as < ast::DoWhileStatement* > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2476 "parser/parser.cpp"
    break;

  case 111: // break_stmt: TOK_BREAK TOK_SMCLN
#line 754 "parser/parser_rules.y"
    { yylhs.value.as < ast::BreakStatement* > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2482 "parser/parser.cpp"
    break;

  case 112: // continue_stmt: TOK_CONTINUE TOK_SMCLN
#line 759 "parser/parser_rules.y"
    { yylhs.value.as < ast::ContinueStatement* > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2488 "parser/parser.cpp"
    break;

  case 113: // expr_stmt: expr TOK_SMCLN
#line 764 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprStatement* > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2494 "parser/parser.cpp"
    break;

  case 114: // var_stmt: var_stmt_default
#line 784 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2500 "parser/parser.cpp"
    break;

  case 115: // var_stmt: var_stmt_imm
#line 785 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2506 "parser/parser.cpp"
    break;

  case 116: // var_stmt: var_stmt_mut
#line 786 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2512 "parser/parser.cpp"
    break;

  case 117: // var_stmt: var_stmt_static_default
#line 787 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2518 "parser/parser.cpp"
    break;

  case 118: // var_stmt: var_stmt_static_imm
#line 788 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2524 "parser/parser.cpp"
    break;

  case 119: // var_stmt: var_stmt_static_mut
#line 789 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2530 "parser/parser.cpp"
    break;

  case 120: // var_stmt_default: ident TOK_COLON type_expr TOK_SMCLN
#line 798 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),                                /* name */
             yystack_[1].value.as < ast::TypeExpr* > (),                                /* type */
             ast::Mutability::Imm,
             ast::Storage::Auto,
             /*init*/nullptr,
             combine(yystack_[3].location, yystack_[0].location)
           );
    }
#line 2545 "parser/parser.cpp"
    break;

  case 121: // var_stmt_default: ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 809 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[5].location, yystack_[0].location)
           );
    }
#line 2560 "parser/parser.cpp"
    break;

  case 122: // var_stmt_imm: TOK_IMM ident TOK_COLON type_expr TOK_SMCLN
#line 823 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),
             yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             /*init*/nullptr,
             combine(yystack_[4].location, yystack_[0].location)
           );
    }
#line 2575 "parser/parser.cpp"
    break;

  case 123: // var_stmt_imm: TOK_IMM ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 834 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[6].location, yystack_[0].location)
           );
    }
#line 2590 "parser/parser.cpp"
    break;

  case 124: // var_stmt_mut: TOK_MUT ident TOK_COLON type_expr TOK_SMCLN
#line 848 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),
             yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Auto,
             /*init*/nullptr,
             combine(yystack_[4].location, yystack_[0].location)
           );
    }
#line 2605 "parser/parser.cpp"
    break;

  case 125: // var_stmt_mut: TOK_MUT ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 859 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Auto,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[6].location, yystack_[0].location)
           );
    }
#line 2620 "parser/parser.cpp"
    break;

  case 126: // var_stmt_static_default: TOK_STATIC ident TOK_COLON type_expr TOK_SMCLN
#line 877 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),
             yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Static,
             /*init*/nullptr,
             combine(yystack_[4].location, yystack_[0].location)
           );
    }
#line 2635 "parser/parser.cpp"
    break;

  case 127: // var_stmt_static_default: TOK_STATIC ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 888 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Static,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[6].location, yystack_[0].location)
           );
    }
#line 2650 "parser/parser.cpp"
    break;

  case 128: // var_stmt_static_imm: TOK_STATIC TOK_IMM ident TOK_COLON type_expr TOK_SMCLN
#line 902 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),
             yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Static,
             /*init*/nullptr,
             combine(yystack_[5].location, yystack_[0].location)
           );
    }
#line 2665 "parser/parser.cpp"
    break;

  case 129: // var_stmt_static_imm: TOK_STATIC TOK_IMM ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 913 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Static,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[7].location, yystack_[0].location)
           );
    }
#line 2680 "parser/parser.cpp"
    break;

  case 130: // var_stmt_static_mut: TOK_STATIC TOK_MUT ident TOK_COLON type_expr TOK_SMCLN
#line 927 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (),
             yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Static,
             /*init*/nullptr,
             combine(yystack_[5].location, yystack_[0].location)
           );
    }
#line 2695 "parser/parser.cpp"
    break;

  case 131: // var_stmt_static_mut: TOK_STATIC TOK_MUT ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 938 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (),
             yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Static,
             /*init*/yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[7].location, yystack_[0].location)
           );
    }
#line 2710 "parser/parser.cpp"
    break;

  case 132: // expr: assign
#line 958 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2716 "parser/parser.cpp"
    break;

  case 133: // expr_opt: %empty
#line 962 "parser/parser_rules.y"
                { yylhs.value.as < ast::Expr* > () = nullptr; }
#line 2722 "parser/parser.cpp"
    break;

  case 134: // expr_opt: expr
#line 963 "parser/parser_rules.y"
                { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2728 "parser/parser.cpp"
    break;

  case 135: // assign: cond
#line 968 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2734 "parser/parser.cpp"
    break;

  case 136: // assign: postfix TOK_ASSIGN assign
#line 969 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Assign,   combine(yystack_[2].location, yystack_[0].location)); }
#line 2740 "parser/parser.cpp"
    break;

  case 137: // assign: postfix TOK_PLUS_ASSIGN assign
#line 970 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Add,      combine(yystack_[2].location, yystack_[0].location)); }
#line 2746 "parser/parser.cpp"
    break;

  case 138: // assign: postfix TOK_MIN_ASSIGN assign
#line 971 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 2752 "parser/parser.cpp"
    break;

  case 139: // assign: postfix TOK_MUL_ASSIGN assign
#line 972 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 2758 "parser/parser.cpp"
    break;

  case 140: // assign: postfix TOK_DIV_ASSIGN assign
#line 973 "parser/parser_rules.y"
                                   { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Divide,   combine(yystack_[2].location, yystack_[0].location)); }
#line 2764 "parser/parser.cpp"
    break;

  case 141: // cond: logic_or
#line 978 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2770 "parser/parser.cpp"
    break;

  case 142: // logic_or: logic_and
#line 983 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2776 "parser/parser.cpp"
    break;

  case 143: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 985 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2782 "parser/parser.cpp"
    break;

  case 144: // logic_and: equality
#line 990 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2788 "parser/parser.cpp"
    break;

  case 145: // logic_and: logic_and TOK_BOOL_AND equality
#line 992 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2794 "parser/parser.cpp"
    break;

  case 146: // equality: relational
#line 997 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2800 "parser/parser.cpp"
    break;

  case 147: // equality: equality TOK_EQUAL relational
#line 999 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::equal,     yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2806 "parser/parser.cpp"
    break;

  case 148: // equality: equality TOK_NEQUAL relational
#line 1001 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2812 "parser/parser.cpp"
    break;

  case 149: // relational: additive
#line 1006 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2818 "parser/parser.cpp"
    break;

  case 150: // relational: relational TOK_LESS additive
#line 1008 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less,          yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2824 "parser/parser.cpp"
    break;

  case 151: // relational: relational TOK_LEQ additive
#line 1010 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal,    yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2830 "parser/parser.cpp"
    break;

  case 152: // relational: relational TOK_GREATER additive
#line 1012 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater,       yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2836 "parser/parser.cpp"
    break;

  case 153: // relational: relational TOK_GEQ additive
#line 1014 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2842 "parser/parser.cpp"
    break;

  case 154: // additive: multiplicative
#line 1019 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2848 "parser/parser.cpp"
    break;

  case 155: // additive: additive TOK_PLUS multiplicative
#line 1021 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::add,      yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2854 "parser/parser.cpp"
    break;

  case 156: // additive: additive TOK_MINUS multiplicative
#line 1023 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2860 "parser/parser.cpp"
    break;

  case 157: // multiplicative: unary
#line 1028 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2866 "parser/parser.cpp"
    break;

  case 158: // multiplicative: multiplicative TOK_STAR unary
#line 1030 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2872 "parser/parser.cpp"
    break;

  case 159: // multiplicative: multiplicative TOK_SLASH unary
#line 1032 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::divide,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2878 "parser/parser.cpp"
    break;

  case 160: // multiplicative: multiplicative TOK_MODULO unary
#line 1034 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2884 "parser/parser.cpp"
    break;

  case 161: // unary: TOK_MINUS unary
#line 1039 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::negation,     yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2890 "parser/parser.cpp"
    break;

  case 162: // unary: TOK_NEGATION unary
#line 1041 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2896 "parser/parser.cpp"
    break;

  case 163: // unary: TOK_INC unary
#line 1043 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2902 "parser/parser.cpp"
    break;

  case 164: // unary: TOK_DEC unary
#line 1045 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2908 "parser/parser.cpp"
    break;

  case 165: // unary: postfix
#line 1047 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2914 "parser/parser.cpp"
    break;

  case 166: // postfix: primary
#line 1052 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2920 "parser/parser.cpp"
    break;

  case 167: // postfix: postfix type_args TOK_LPAR arg_list_opt TOK_RPAR
#line 1054 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Expr* > () = ast.mk_call_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[4].location, yystack_[0].location));
    }
#line 2928 "parser/parser.cpp"
    break;

  case 168: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 1058 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_index(yystack_[3].value.as < ast::Expr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location)); }
#line 2934 "parser/parser.cpp"
    break;

  case 169: // postfix: postfix TOK_DOT ident
#line 1060 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_field_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2940 "parser/parser.cpp"
    break;

  case 170: // postfix: postfix TOK_INC
#line 1062 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2946 "parser/parser.cpp"
    break;

  case 171: // postfix: postfix TOK_DEC
#line 1064 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2952 "parser/parser.cpp"
    break;

  case 172: // postfix: postfix type_args TOK_LCBRA field_inits_opt TOK_RCBRA
#line 1066 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_struct_literal_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()), combine(yystack_[4].location, yystack_[1].location)); }
#line 2958 "parser/parser.cpp"
    break;

  case 173: // arg_list_opt: %empty
#line 1071 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2964 "parser/parser.cpp"
    break;

  case 174: // arg_list_opt: arg_list
#line 1073 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 2970 "parser/parser.cpp"
    break;

  case 175: // arg_list: expr
#line 1078 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 2976 "parser/parser.cpp"
    break;

  case 176: // arg_list: arg_list TOK_COMMA expr
#line 1080 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2982 "parser/parser.cpp"
    break;

  case 177: // arg_list: arg_list TOK_COMMA
#line 1082 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2988 "parser/parser.cpp"
    break;

  case 178: // int_literal_type_opt: %empty
#line 1090 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = std::nullopt; }
#line 2994 "parser/parser.cpp"
    break;

  case 179: // int_literal_type_opt: TOK_AS TOK_I8
#line 1091 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I8; }
#line 3000 "parser/parser.cpp"
    break;

  case 180: // int_literal_type_opt: TOK_AS TOK_U8
#line 1092 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U8; }
#line 3006 "parser/parser.cpp"
    break;

  case 181: // int_literal_type_opt: TOK_AS TOK_I16
#line 1093 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I16; }
#line 3012 "parser/parser.cpp"
    break;

  case 182: // int_literal_type_opt: TOK_AS TOK_U16
#line 1094 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U16; }
#line 3018 "parser/parser.cpp"
    break;

  case 183: // int_literal_type_opt: TOK_AS TOK_I32
#line 1095 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I32; }
#line 3024 "parser/parser.cpp"
    break;

  case 184: // int_literal_type_opt: TOK_AS TOK_U32
#line 1096 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U32; }
#line 3030 "parser/parser.cpp"
    break;

  case 185: // int_literal_type_opt: TOK_AS TOK_I64
#line 1097 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I64; }
#line 3036 "parser/parser.cpp"
    break;

  case 186: // int_literal_type_opt: TOK_AS TOK_U64
#line 1098 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U64; }
#line 3042 "parser/parser.cpp"
    break;

  case 187: // int_literal_type_opt: TOK_AS TOK_I128
#line 1099 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I128; }
#line 3048 "parser/parser.cpp"
    break;

  case 188: // int_literal_type_opt: TOK_AS TOK_U128
#line 1100 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U128; }
#line 3054 "parser/parser.cpp"
    break;

  case 189: // float_literal_type_opt: %empty
#line 1104 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = std::nullopt; }
#line 3060 "parser/parser.cpp"
    break;

  case 190: // float_literal_type_opt: TOK_AS TOK_F32
#line 1105 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F32; }
#line 3066 "parser/parser.cpp"
    break;

  case 191: // float_literal_type_opt: TOK_AS TOK_F64
#line 1106 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F64; }
#line 3072 "parser/parser.cpp"
    break;

  case 192: // primary: path_expr
#line 1115 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(yystack_[0].value.as < ast::PathExpr* > ()); }
#line 3078 "parser/parser.cpp"
    break;

  case 193: // primary: TOK_INT_LITERAL int_literal_type_opt
#line 1117 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::IntKind> > (), yystack_[1].location); }
#line 3084 "parser/parser.cpp"
    break;

  case 194: // primary: TOK_FLOAT_LITERAL float_literal_type_opt
#line 1119 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_float_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::FloatKind> > (), yystack_[1].location); }
#line 3090 "parser/parser.cpp"
    break;

  case 195: // primary: TOK_STRING_LITERAL
#line 1121 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3096 "parser/parser.cpp"
    break;

  case 196: // primary: TOK_BOOL_LITERAL
#line 1123 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl::rt::boolean > (), yystack_[0].location); }
#line 3102 "parser/parser.cpp"
    break;

  case 197: // primary: TOK_CHAR_LITERAL
#line 1125 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_char_literal_expr(yystack_[0].value.as < kl::rt::character > (), yystack_[0].location); }
#line 3108 "parser/parser.cpp"
    break;

  case 198: // primary: TOK_LPAR expr TOK_RPAR
#line 1127 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[1].value.as < ast::Expr* > (); }
#line 3114 "parser/parser.cpp"
    break;

  case 199: // field_inits_opt: %empty
#line 1132 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{}; }
#line 3120 "parser/parser.cpp"
    break;

  case 200: // field_inits_opt: field_inits
#line 1134 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3126 "parser/parser.cpp"
    break;

  case 201: // field_inits: field_init
#line 1139 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{ yystack_[0].value.as < ast::FieldInitExpr* > () }; }
#line 3132 "parser/parser.cpp"
    break;

  case 202: // field_inits: field_inits TOK_COMMA field_init
#line 1141 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ().push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3138 "parser/parser.cpp"
    break;

  case 203: // field_inits: field_inits TOK_COMMA
#line 1143 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3144 "parser/parser.cpp"
    break;

  case 204: // field_init: ident TOK_COLON expr
#line 1148 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr* > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3150 "parser/parser.cpp"
    break;


#line 3154 "parser/parser.cpp"

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


  const short parser::yypact_ninf_ = -147;

  const signed char parser::yytable_ninf_ = -29;

  const short
  parser::yypact_[] =
  {
      -2,   -30,    12,  -147,  -147,   -11,    44,  -147,  -147,   -30,
      83,  -147,   -30,    69,    83,  -147,   -14,  -147,    57,  -147,
      93,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,   -30,
    -147,   -30,   -30,  -147,    50,    -3,    -3,  -147,   -30,    60,
      65,  -147,   -21,  -147,    -5,  -147,   -30,   -30,  -147,   -30,
      89,    98,    -5,  -147,    97,    90,   113,  -147,  -147,   100,
     332,  -147,  -147,   332,   112,   -30,   332,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,   332,   115,   114,   130,  -147,   136,  -147,  -147,  -147,
    -147,   332,    86,  -147,   132,   139,  -147,  -147,   353,   332,
    -147,  -147,    40,  -147,   289,  -147,  -147,  -147,  -147,   136,
      38,  -147,   162,   164,  -147,  -147,  -147,    40,    40,    40,
      40,    40,  -147,   141,  -147,  -147,   116,   118,    67,    47,
      92,    81,  -147,    14,  -147,   156,   158,   157,    40,   -30,
     -30,    13,   155,   159,   289,   160,  -147,   166,   289,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,   165,   332,  -147,    95,
    -147,   131,  -147,   163,  -147,   102,  -147,  -147,  -147,  -147,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,   -30,  -147,  -147,    40,    40,    40,
      40,    40,   -13,    40,    40,   289,   202,  -147,   167,   168,
     169,   -30,   -30,   170,  -147,  -147,   175,   332,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,   118,    67,    47,    47,    92,
      92,    92,    92,    81,    81,  -147,  -147,  -147,   172,  -147,
    -147,  -147,  -147,  -147,  -147,    40,   -30,   180,   181,   178,
     184,  -147,   332,   332,   177,   179,   332,  -147,   -41,  -147,
    -147,   185,   161,   186,   183,   187,  -147,   188,   191,  -147,
      40,   -35,   -32,   332,   332,   -29,  -147,    40,  -147,    40,
      40,  -147,   -30,   289,  -147,   289,  -147,   195,  -147,    40,
    -147,    40,   -26,    10,  -147,    40,   182,  -147,  -147,  -147,
     192,   235,   194,   193,   198,   199,  -147,    40,  -147,    40,
     200,  -147,  -147,    11,  -147,  -147,  -147,  -147,  -147,  -147,
     201,   203,  -147,   209,   289,  -147,  -147,  -147,    40,   196,
     225,  -147,   223,   289,  -147,   197,  -147
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,    13,    12,     0,    10,     1,     0,
       4,    11,     0,    25,     5,     6,     0,    26,     0,     3,
      25,    29,    31,    33,    34,    32,    37,    38,     7,     0,
       8,     0,     0,    30,     0,    14,    14,     9,     0,     0,
       0,    19,     0,    16,    41,    40,    48,    18,    15,     0,
       0,     0,    42,    43,     0,     0,    49,    50,    17,     0,
       0,    39,    44,     0,     0,    52,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,    57,    20,     0,    54,    55,    60,    62,    63,
      53,     0,     0,    51,     0,     0,    59,    58,     0,     0,
      79,    45,     0,    47,    87,    36,    35,    46,    64,    56,
       0,    22,   178,   189,   195,   196,   197,     0,     0,     0,
       0,     0,   192,     0,   132,   135,   141,   142,   144,   146,
     149,   154,   157,   165,   166,     0,     0,     0,   133,     0,
       0,     0,     0,     0,    87,    10,    98,     0,    88,    89,
      91,    92,    94,    99,   100,   101,    95,    96,    97,    93,
     114,   115,   116,   117,   118,   119,     0,    24,    21,     0,
     193,     0,   194,     0,   162,   165,   163,   164,   161,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   170,   171,     0,     0,     0,
       0,     0,     0,     0,     0,    87,     0,   134,     0,     0,
       0,     0,     0,     0,   111,   112,     0,     0,    81,    90,
     113,    23,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   190,   191,   198,   143,   145,   147,   148,   150,
     151,   152,   153,   155,   156,   158,   159,   160,     0,   169,
     136,   137,   138,   139,   140,   173,   199,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,    80,     0,   168,
     175,     0,   174,     0,     0,   200,   201,     0,     0,    86,
       0,     0,     0,     0,     0,     0,   120,     0,   167,   177,
       0,   172,   203,    87,   104,    87,   109,     0,   124,     0,
     122,     0,     0,     0,   126,     0,     0,   176,   204,   202,
       0,   107,     0,     0,     0,     0,   130,     0,   128,     0,
       0,   121,    82,     0,   105,   103,    85,   110,   125,   123,
       0,     0,   127,     0,    87,   108,   131,   129,     0,     0,
       0,    84,     0,    87,   106,     0,    83
  };

  const short
  parser::yypgoto_[] =
  {
    -147,  -147,  -147,  -147,  -147,   258,  -147,     5,    -9,   237,
    -147,   227,   125,  -147,  -147,  -147,  -147,   255,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,   224,  -147,  -147,  -147,
     212,   -50,  -147,  -147,   189,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -143,  -147,   133,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,   -92,  -147,  -146,
    -147,  -147,    99,   101,    -4,   -10,   -20,  -116,    74,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,   -12
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     2,     3,    13,    14,    15,     5,   122,     7,    39,
      42,    43,   202,   110,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    51,    52,    53,    92,    55,    56,
      57,    84,    85,    98,    86,    87,    88,    89,   146,   106,
     294,   344,   335,   296,   206,   147,   148,   149,   150,   151,
     152,   153,   311,   324,   325,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   208,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   271,
     272,   170,   172,   134,   274,   275,   276
  };

  const short
  parser::yytable_[] =
  {
      11,   216,   174,   176,   177,   178,     6,     4,    29,   286,
     123,    49,     8,    90,   333,   298,    94,    16,   300,     1,
      34,   304,    35,    36,   316,   173,   211,   212,    47,    41,
     255,    95,     4,   287,   256,    50,    30,    54,    41,   299,
      59,   103,   301,    50,     9,   305,   207,    48,   317,   111,
       4,   250,   251,   252,   253,   254,    54,   -20,   334,   193,
     318,   -20,   259,    38,    31,    83,   194,    32,    83,   -27,
      99,    83,   195,   196,   245,   246,   247,     4,   112,   113,
     114,   115,   116,   117,   319,    17,    83,   167,   197,   198,
     199,   200,   201,   -28,    10,   145,    83,   118,   119,   120,
      37,   248,    12,    83,    83,   121,   168,    44,    46,    17,
      45,   257,   258,   184,   185,   186,   187,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,    96,    97,
     209,   210,   213,   104,    64,   145,   105,   182,   183,   145,
      60,   306,   190,   191,   192,   -20,    61,   193,    63,   -20,
     310,    66,   312,   314,   194,   315,   188,   189,    99,   320,
     195,   196,    65,   270,   232,   233,    91,   268,   243,   244,
      99,   330,    83,   331,   239,   240,   241,   242,   237,   238,
     101,   102,   107,   108,   169,   249,   171,   179,   297,   180,
     181,   339,   175,   175,   175,   175,   145,   307,   308,   203,
     345,   204,   264,   265,   205,   214,   260,   234,   100,   215,
     289,   217,   281,   282,   218,   220,   285,   261,   269,   262,
     263,   266,    83,   267,   277,   278,   279,   280,   283,   288,
     284,   291,   321,   302,   303,   293,   292,   290,   295,   313,
     322,   323,   326,   327,   341,   346,   340,   273,   328,   329,
     332,   336,   338,   337,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,    83,    83,   342,
     343,    83,    28,    40,    58,    33,    62,    93,     0,   235,
     309,   219,   236,   273,   145,     0,   145,   109,    83,    83,
       0,     0,   135,   136,   137,     0,     0,     0,     0,     0,
       0,   138,   139,   140,   141,     0,   142,   143,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,     4,   112,   113,   114,
     115,   116,   117,     0,   145,     0,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,     0,
       0,     0,     0,     0,   121,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     4,
       0,     0,     0,     0,     0,    81,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       4,     0,    82,     0,     0,     0,    81
  };

  const short
  parser::yycheck_[] =
  {
       9,   144,   118,   119,   120,   121,     1,    37,    22,    50,
     102,    16,     0,    63,     3,    50,    66,    12,    50,    21,
      29,    50,    31,    32,    50,   117,    13,    14,    49,    38,
      43,    81,    37,    74,    47,    44,    50,    46,    47,    74,
      49,    91,    74,    52,    55,    74,   138,    68,    74,    99,
      37,   197,   198,   199,   200,   201,    65,    43,    47,    45,
      50,    47,   205,    66,     7,    60,    52,    10,    63,     0,
      56,    66,    58,    59,   190,   191,   192,    37,    38,    39,
      40,    41,    42,    43,    74,    16,    81,    49,    74,    75,
      76,    77,    78,     0,    50,   104,    91,    57,    58,    59,
      50,   193,    19,    98,    99,    65,    68,    47,    43,    16,
      50,   203,   204,    66,    67,    68,    69,   167,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    13,    14,
     139,   140,   141,    47,    44,   144,    50,    70,    71,   148,
      51,   287,    61,    62,    63,    43,    48,    45,    51,    47,
     293,    51,   295,   299,    52,   301,    64,    65,    56,   305,
      58,    59,    49,   255,    33,    34,    54,   217,   188,   189,
      56,   317,   167,   319,   184,   185,   186,   187,   182,   183,
      50,    45,    50,    44,    22,   194,    22,    46,   280,    73,
      72,   334,   118,   119,   120,   121,   205,   289,   290,    43,
     343,    43,   211,   212,    47,    50,     4,    44,    83,    50,
      49,    51,   262,   263,    48,    50,   266,    50,    46,    51,
      51,    51,   217,    48,    44,    44,    48,    43,    51,    44,
      51,    48,    50,   283,   284,    47,    49,    51,    47,    44,
      48,     6,    48,    50,    48,    48,   338,   256,    50,    50,
      50,    50,    43,    50,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   262,   263,    44,
      47,   266,    14,    36,    47,    20,    52,    65,    -1,   180,
     292,   148,   181,   292,   293,    -1,   295,    98,   283,   284,
      -1,    -1,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   334,    37,    38,    39,    40,
      41,    42,    43,    -1,   343,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    43,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    60,    -1,    -1,    -1,    43
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    21,    83,    84,    37,    88,    89,    90,     0,    55,
      50,    90,    19,    85,    86,    87,    89,    16,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    87,    22,
      50,     7,    10,    99,    90,    90,    90,    50,    66,    91,
      91,    90,    92,    93,    47,    50,    43,    49,    68,    16,
      90,   106,   107,   108,    90,   110,   111,   112,    93,    90,
      51,    48,   108,    51,    44,    49,    51,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    43,    60,    89,   113,   114,   116,   117,   118,   119,
     113,    54,   109,   112,   113,   113,    13,    14,   115,    56,
      94,    50,    45,   113,    47,    50,   121,    50,    44,   116,
      95,   113,    38,    39,    40,    41,    42,    43,    57,    58,
      59,    65,    89,   149,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   165,     3,     4,     5,    12,    13,
      14,    15,    17,    18,    47,    90,   120,   127,   128,   129,
     130,   131,   132,   133,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,    49,    68,    22,
     163,    22,   164,   149,   159,   160,   159,   159,   159,    46,
      73,    72,    70,    71,    66,    67,    68,    69,    64,    65,
      61,    62,    63,    45,    52,    58,    59,    74,    75,    76,
      77,    78,    94,    43,    43,    47,   126,   149,   150,    90,
      90,    13,    14,    90,    50,    50,   127,    51,    48,   129,
      50,   113,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    44,   154,   155,   156,   156,   157,
     157,   157,   157,   158,   158,   159,   159,   159,   149,    90,
     151,   151,   151,   151,   151,    43,    47,   149,   149,   127,
       4,    50,    51,    51,    90,    90,    51,    48,   113,    46,
     149,   161,   162,    90,   166,   167,   168,    44,    44,    48,
      43,   113,   113,    51,    51,   113,    50,    74,    44,    49,
      51,    48,    49,    47,   122,    47,   125,   149,    50,    74,
      50,    74,   113,   113,    50,    74,   151,   149,   149,   168,
     127,   134,   127,    44,   151,   151,    50,    74,    50,    74,
     151,    50,    48,     6,   135,   136,    48,    50,    50,    50,
     151,   151,    50,     3,    47,   124,    50,    50,    43,   127,
     149,    48,    44,    47,   123,   127,    48
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    90,    91,    91,    92,    92,    92,    93,
      94,    94,    95,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   102,   103,   103,   104,
     105,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111,   111,   111,   112,   113,   113,   114,   115,   115,   115,
     116,   116,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   127,   128,
     128,   129,   129,   130,   130,   130,   130,   130,   131,   131,
     131,   131,   132,   133,   134,   134,   135,   136,   136,   137,
     138,   139,   140,   141,   142,   142,   142,   142,   142,   142,
     143,   143,   144,   144,   145,   145,   146,   146,   147,   147,
     148,   148,   149,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   153,   153,   154,   154,   155,   155,   155,   156,
     156,   156,   156,   156,   157,   157,   157,   158,   158,   158,
     158,   159,   159,   159,   159,   159,   160,   160,   160,   160,
     160,   160,   160,   161,   161,   162,   162,   162,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   164,
     164,   164,   165,   165,   165,   165,   165,   165,   165,   166,
     166,   167,   167,   167,   168
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     5,     0,     1,     1,     2,     3,     5,
       1,     3,     1,     1,     0,     3,     1,     3,     2,     1,
       0,     3,     1,     3,     2,     0,     1,     0,     1,     1,
       2,     1,     1,     1,     1,     9,     9,     1,     1,     7,
       5,     0,     1,     1,     2,     4,     5,     2,     0,     1,
       1,     3,     2,     3,     1,     1,     3,     0,     1,     1,
       1,     4,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     0,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     7,     0,     2,     6,     0,     2,     5,
       7,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       4,     6,     5,     7,     5,     7,     5,     7,     6,     8,
       6,     8,     1,     0,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     2,     2,     2,     2,     1,     1,     5,     4,     3,
       2,     2,     5,     0,     1,     1,     3,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     1,     2,     2,     1,     1,     1,     3,     0,
       1,     1,     3,     2,     3
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
  "import_list_opt", "import_list", "import_decl", "path", "path_expr",
  "ident", "type_params_opt", "type_param_list", "type_param", "type_args",
  "type_arg_list", "pub_opt", "decl_list_opt", "decl_list", "decl",
  "fn_decl", "fn_decl_def", "fn_decl_fwd", "struct_decl",
  "struct_decl_def", "struct_decl_fwd", "field_decl_list_opt",
  "field_decl_list", "field_decl", "ret_type_expr", "param_list_opt",
  "param_list", "param", "type_expr", "ref_type_expr", "ref_mutability",
  "type_postfix", "type_primary", "builtin_type_expr", "path_type_expr",
  "anon_block", "fn_block", "if_block", "else_if_block", "else_block",
  "while_block", "do_while_block", "stmt_list_opt", "stmt_list", "stmt",
  "simple_stmt", "compound_stmt", "return_stmt", "if_stmt", "elseif_list",
  "elseif", "else_part", "while_stmt", "do_while_stmt", "break_stmt",
  "continue_stmt", "expr_stmt", "var_stmt", "var_stmt_default",
  "var_stmt_imm", "var_stmt_mut", "var_stmt_static_default",
  "var_stmt_static_imm", "var_stmt_static_mut", "expr", "expr_opt",
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
       0,   324,   324,   329,   339,   340,   345,   347,   352,   354,
     364,   366,   371,   376,   386,   387,   392,   394,   396,   401,
     407,   408,   413,   415,   417,   427,   428,   433,   434,   439,
     441,   446,   448,   453,   455,   460,   476,   493,   495,   500,
     514,   530,   531,   536,   538,   543,   545,   550,   556,   557,
     562,   564,   566,   571,   583,   585,   590,   595,   596,   597,
     601,   603,   608,   610,   612,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   634,
     643,   648,   653,   658,   663,   668,   673,   679,   680,   685,
     687,   692,   694,   699,   700,   701,   702,   703,   707,   708,
     709,   710,   714,   719,   725,   726,   731,   737,   738,   743,
     748,   753,   758,   763,   784,   785,   786,   787,   788,   789,
     797,   808,   822,   833,   847,   858,   876,   887,   901,   912,
     926,   937,   957,   962,   963,   967,   969,   970,   971,   972,
     973,   977,   982,   984,   989,   991,   996,   998,  1000,  1005,
    1007,  1009,  1011,  1013,  1018,  1020,  1022,  1027,  1029,  1031,
    1033,  1038,  1040,  1042,  1044,  1046,  1051,  1053,  1057,  1059,
    1061,  1063,  1065,  1071,  1072,  1077,  1079,  1081,  1090,  1091,
    1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1104,
    1105,  1106,  1114,  1116,  1118,  1120,  1122,  1124,  1126,  1132,
    1133,  1138,  1140,  1142,  1147
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
#line 4041 "parser/parser.cpp"

#line 1151 "parser/parser_rules.y"

