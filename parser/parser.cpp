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
#line 46 "parser/parser_rules.y"

  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << filePath << ':' << loc.begin.line << ':' << loc.begin.column
              << ": " << msg << '\n';
  }

  yy::parser::symbol_type yy::yylex(Scanner& scanner) {
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
      case T::TOK_IMPORT:   return yy::parser::make_TOK_IMPORT(L);
      case T::TOK_PACKAGE:  return yy::parser::make_TOK_PACKAGE(L);
      case T::TOK_AS:       return yy::parser::make_TOK_AS(L);
      case T::TOK_PUB:      return yy::parser::make_TOK_PUB(L);
      case T::TOK_MUT:      return yy::parser::make_TOK_MUT(L);
      case T::TOK_IMM:      return yy::parser::make_TOK_IMM(L);
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
      case T::TOK_VOID: return yy::parser::make_TOK_VOID(L);

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

      case T::TOK_LOAD:        return yy::parser::make_TOK_LOAD(L);

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

#line 158 "parser/parser.cpp"


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
#line 251 "parser/parser.cpp"

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
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
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
        value.YY_MOVE_OR_COPY< ast::FnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.YY_MOVE_OR_COPY< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.YY_MOVE_OR_COPY< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.YY_MOVE_OR_COPY< ast::LoadFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.YY_MOVE_OR_COPY< ast::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< ast::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
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
      case symbol_kind::S_qpath: // qpath
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
      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
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
        value.move< ast::FnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.move< ast::LoadFnDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
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
      case symbol_kind::S_qpath: // qpath
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
      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
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
        value.copy< ast::FnDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.copy< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.copy< ast::LoadFnDecl* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.copy< ast::Mutability > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< ast::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
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
      case symbol_kind::S_qpath: // qpath
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
      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
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
        value.move< ast::FnDecl* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ast::IfStatement* > (that.value);
        break;

      case symbol_kind::S_import_decl: // import_decl
        value.move< ast::ImportDecl* > (that.value);
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        value.move< ast::LoadFnDecl* > (that.value);
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        value.move< ast::Mutability > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< ast::ParamDecl* > (that.value);
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
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
      case symbol_kind::S_qpath: // qpath
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
      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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
      case symbol_kind::S_TOK_SELF: // TOK_SELF
      case symbol_kind::S_TOK_INT_LITERAL: // TOK_INT_LITERAL
      case symbol_kind::S_TOK_FLOAT_LITERAL: // TOK_FLOAT_LITERAL
      case symbol_kind::S_TOK_STRING_LITERAL: // TOK_STRING_LITERAL
      case symbol_kind::S_ident_no_self: // ident_no_self
      case symbol_kind::S_ident_any: // ident_any
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
        yylhs.value.emplace< ast::FnDecl* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        yylhs.value.emplace< ast::IfStatement* > ();
        break;

      case symbol_kind::S_import_decl: // import_decl
        yylhs.value.emplace< ast::ImportDecl* > ();
        break;

      case symbol_kind::S_load_fn_decl: // load_fn_decl
        yylhs.value.emplace< ast::LoadFnDecl* > ();
        break;

      case symbol_kind::S_ref_mutability: // ref_mutability
        yylhs.value.emplace< ast::Mutability > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< ast::ParamDecl* > ();
        break;

      case symbol_kind::S_path_expr: // path_expr
      case symbol_kind::S_qpath_expr: // qpath_expr
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
      case symbol_kind::S_qpath: // qpath
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
      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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
#line 323 "parser/parser_rules.y"
    { }
#line 1779 "parser/parser.cpp"
    break;

  case 3: // module: TOK_PACKAGE path_expr TOK_SMCLN import_list_opt decl_list_opt
#line 328 "parser/parser_rules.y"
    {
      ast.mk_module(yystack_[3].value.as < ast::PathExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[4].location, yystack_[0].location));
      unit.addModule(std::move(ast));
    }
#line 1788 "parser/parser.cpp"
    break;

  case 4: // import_list_opt: %empty
#line 336 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1794 "parser/parser.cpp"
    break;

  case 5: // import_list_opt: import_list
#line 338 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1800 "parser/parser.cpp"
    break;

  case 6: // import_list: import_decl
#line 343 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{ yystack_[0].value.as < ast::ImportDecl* > () }; }
#line 1806 "parser/parser.cpp"
    break;

  case 7: // import_list: import_list import_decl
#line 345 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1812 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT path_expr TOK_SMCLN
#line 350 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < ast::PathExpr* > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1818 "parser/parser.cpp"
    break;

  case 9: // import_decl: TOK_IMPORT path_expr TOK_AS ident_no_self TOK_SMCLN
#line 352 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < ast::PathExpr* > ()), std::optional<Str>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1824 "parser/parser.cpp"
    break;

  case 10: // path: ident_any
#line 361 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[0].value.as < Str > () }; }
#line 1830 "parser/parser.cpp"
    break;

  case 11: // path: path TOK_COLONCOLON ident_any
#line 363 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1836 "parser/parser.cpp"
    break;

  case 12: // path_expr: path
#line 368 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1842 "parser/parser.cpp"
    break;

  case 13: // qpath: ident_any TOK_COLONCOLON ident_any
#line 373 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[2].value.as < Str > (), yystack_[0].value.as < Str > () }; }
#line 1848 "parser/parser.cpp"
    break;

  case 14: // qpath: qpath TOK_COLONCOLON ident_any
#line 375 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1854 "parser/parser.cpp"
    break;

  case 15: // qpath_expr: qpath
#line 380 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1860 "parser/parser.cpp"
    break;

  case 16: // ident_no_self: TOK_IDENTIFIER
#line 385 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1866 "parser/parser.cpp"
    break;

  case 17: // ident_any: TOK_IDENTIFIER
#line 390 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1872 "parser/parser.cpp"
    break;

  case 18: // ident_any: TOK_SELF
#line 392 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 1878 "parser/parser.cpp"
    break;

  case 19: // type_params_opt: %empty
#line 401 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{}; }
#line 1884 "parser/parser.cpp"
    break;

  case 20: // type_params_opt: TOK_LESS type_param_list TOK_GREATER
#line 403 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1890 "parser/parser.cpp"
    break;

  case 21: // type_param_list: type_param
#line 408 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{ yystack_[0].value.as < ast::TypeParamDecl* > () }; }
#line 1896 "parser/parser.cpp"
    break;

  case 22: // type_param_list: type_param_list TOK_COMMA type_param
#line 410 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ().push_back(yystack_[0].value.as < ast::TypeParamDecl* > ()); yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1902 "parser/parser.cpp"
    break;

  case 23: // type_param_list: type_param_list TOK_COMMA
#line 412 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 1908 "parser/parser.cpp"
    break;

  case 24: // type_param: ident_no_self
#line 417 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeParamDecl* > () = ast.mk_type_param_decl(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 1914 "parser/parser.cpp"
    break;

  case 25: // type_args: %empty
#line 422 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{}; }
#line 1920 "parser/parser.cpp"
    break;

  case 26: // type_args: TOK_TURBOFISH_S type_arg_list TOK_GREATER
#line 424 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1926 "parser/parser.cpp"
    break;

  case 27: // type_arg_list: type_expr
#line 429 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{ yystack_[0].value.as < ast::TypeExpr* > () }; }
#line 1932 "parser/parser.cpp"
    break;

  case 28: // type_arg_list: type_arg_list TOK_COMMA type_expr
#line 431 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeExpr*> > ().push_back(yystack_[0].value.as < ast::TypeExpr* > ()); yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1938 "parser/parser.cpp"
    break;

  case 29: // type_arg_list: type_arg_list TOK_COMMA
#line 433 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 1944 "parser/parser.cpp"
    break;

  case 30: // pub_opt: %empty
#line 441 "parser/parser_rules.y"
           { yylhs.value.as < kl::rt::boolean > () = false; }
#line 1950 "parser/parser.cpp"
    break;

  case 31: // pub_opt: TOK_PUB
#line 442 "parser/parser_rules.y"
            { yylhs.value.as < kl::rt::boolean > () = true; }
#line 1956 "parser/parser.cpp"
    break;

  case 32: // decl_list_opt: %empty
#line 447 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 1962 "parser/parser.cpp"
    break;

  case 33: // decl_list_opt: decl_list
#line 449 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()); }
#line 1968 "parser/parser.cpp"
    break;

  case 34: // decl_list: decl
#line 454 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{ yystack_[0].value.as < ast::Decl* > () }; }
#line 1974 "parser/parser.cpp"
    break;

  case 35: // decl_list: decl_list decl
#line 456 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(yystack_[0].value.as < ast::Decl* > ()); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 1980 "parser/parser.cpp"
    break;

  case 36: // decl: fn_decl
#line 461 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FnDecl* > ()); }
#line 1986 "parser/parser.cpp"
    break;

  case 37: // decl: load_fn_decl
#line 463 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::LoadFnDecl* > ()); }
#line 1992 "parser/parser.cpp"
    break;

  case 38: // decl: struct_decl
#line 465 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 1998 "parser/parser.cpp"
    break;

  case 39: // fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
#line 470 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_FN */
      yylhs.value.as < ast::FnDecl* > () = ast.mk_fn_decl(yystack_[6].value.as < Str > (), std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 2007 "parser/parser.cpp"
    break;

  case 40: // load_fn_decl: pub_opt TOK_LOAD TOK_FN ident_no_self TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 478 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_LOAD */
      yylhs.value.as < ast::LoadFnDecl* > () = ast.mk_load_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 2016 "parser/parser.cpp"
    break;

  case 41: // struct_decl: struct_decl_def
#line 486 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2022 "parser/parser.cpp"
    break;

  case 42: // struct_decl: struct_decl_fwd
#line 488 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2028 "parser/parser.cpp"
    break;

  case 43: // struct_decl_def: pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 493 "parser/parser_rules.y"
    {
      auto start = yystack_[6].value.as < kl::rt::boolean > () ? yystack_[6].location : yystack_[5].location;
      yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(
            yystack_[4].value.as < Str > (),
            std::move(yystack_[3].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()),
            yystack_[6].value.as < kl::rt::boolean > (),                  /* isExported */
            combine(start, yystack_[0].location)
          );
    }
#line 2043 "parser/parser.cpp"
    break;

  case 44: // struct_decl_fwd: pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_SMCLN
#line 507 "parser/parser_rules.y"
    {
      auto start = yystack_[4].value.as < kl::rt::boolean > () ? yystack_[4].location : yystack_[3].location;
      yylhs.value.as < ast::StructDecl* > () = ast.mk_struct_decl(
            yystack_[2].value.as < Str > (),
            std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()),
            std::vector<ast::FieldDecl*>{},
            yystack_[4].value.as < kl::rt::boolean > (),                  /* isExported */
            combine(start, yystack_[0].location)
          );
    }
#line 2058 "parser/parser.cpp"
    break;

  case 45: // field_decl_list_opt: %empty
#line 521 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 2064 "parser/parser.cpp"
    break;

  case 46: // field_decl_list_opt: field_decl_list
#line 523 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2070 "parser/parser.cpp"
    break;

  case 47: // field_decl_list: field_decl
#line 528 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{ yystack_[0].value.as < ast::FieldDecl* > () }; }
#line 2076 "parser/parser.cpp"
    break;

  case 48: // field_decl_list: field_decl_list field_decl
#line 530 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2082 "parser/parser.cpp"
    break;

  case 49: // field_decl: ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 535 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Priv, combine(yystack_[3].location, yystack_[0].location)); }
#line 2088 "parser/parser.cpp"
    break;

  case 50: // field_decl: TOK_PUB ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 537 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Publ, combine(yystack_[4].location, yystack_[0].location)); }
#line 2094 "parser/parser.cpp"
    break;

  case 51: // ret_type_expr: TOK_ARROW type_expr
#line 542 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2100 "parser/parser.cpp"
    break;

  case 52: // param_list_opt: %empty
#line 551 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 2106 "parser/parser.cpp"
    break;

  case 53: // param_list_opt: param_list
#line 553 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2112 "parser/parser.cpp"
    break;

  case 54: // param_list: param
#line 558 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{ yystack_[0].value.as < ast::ParamDecl* > () }; }
#line 2118 "parser/parser.cpp"
    break;

  case 55: // param_list: param_list TOK_COMMA param
#line 560 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2124 "parser/parser.cpp"
    break;

  case 56: // param_list: param_list TOK_COMMA
#line 562 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2130 "parser/parser.cpp"
    break;

  case 57: // param: ident_no_self TOK_COLON type_expr
#line 567 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2136 "parser/parser.cpp"
    break;

  case 58: // type_expr: ref_type_expr
#line 576 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 2142 "parser/parser.cpp"
    break;

  case 59: // type_expr: type_postfix
#line 578 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2148 "parser/parser.cpp"
    break;

  case 60: // ref_type_expr: TOK_AMP ref_mutability type_postfix
#line 583 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2154 "parser/parser.cpp"
    break;

  case 61: // ref_mutability: %empty
#line 587 "parser/parser_rules.y"
           { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2160 "parser/parser.cpp"
    break;

  case 62: // ref_mutability: TOK_IMM
#line 588 "parser/parser_rules.y"
            { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2166 "parser/parser.cpp"
    break;

  case 63: // ref_mutability: TOK_MUT
#line 589 "parser/parser_rules.y"
            { yylhs.value.as < ast::Mutability > () = ast::Mutability::Mut; }
#line 2172 "parser/parser.cpp"
    break;

  case 64: // type_postfix: type_primary
#line 594 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2178 "parser/parser.cpp"
    break;

  case 65: // type_postfix: type_postfix TOK_LBRACK expr TOK_RBRACK
#line 596 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location))); }
#line 2184 "parser/parser.cpp"
    break;

  case 66: // type_primary: builtin_type_expr
#line 601 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 2190 "parser/parser.cpp"
    break;

  case 67: // type_primary: path_type_expr
#line 603 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 2196 "parser/parser.cpp"
    break;

  case 68: // type_primary: TOK_LPAR type_expr TOK_RPAR
#line 605 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[1].value.as < ast::TypeExpr* > (); }
#line 2202 "parser/parser.cpp"
    break;

  case 69: // builtin_type_expr: TOK_I8
#line 609 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 2208 "parser/parser.cpp"
    break;

  case 70: // builtin_type_expr: TOK_U8
#line 610 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 2214 "parser/parser.cpp"
    break;

  case 71: // builtin_type_expr: TOK_I16
#line 611 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 2220 "parser/parser.cpp"
    break;

  case 72: // builtin_type_expr: TOK_U16
#line 612 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 2226 "parser/parser.cpp"
    break;

  case 73: // builtin_type_expr: TOK_I32
#line 613 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 2232 "parser/parser.cpp"
    break;

  case 74: // builtin_type_expr: TOK_U32
#line 614 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 2238 "parser/parser.cpp"
    break;

  case 75: // builtin_type_expr: TOK_I64
#line 615 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 2244 "parser/parser.cpp"
    break;

  case 76: // builtin_type_expr: TOK_U64
#line 616 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 2250 "parser/parser.cpp"
    break;

  case 77: // builtin_type_expr: TOK_I128
#line 617 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 2256 "parser/parser.cpp"
    break;

  case 78: // builtin_type_expr: TOK_U128
#line 618 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 2262 "parser/parser.cpp"
    break;

  case 79: // builtin_type_expr: TOK_F32
#line 619 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 2268 "parser/parser.cpp"
    break;

  case 80: // builtin_type_expr: TOK_F64
#line 620 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 2274 "parser/parser.cpp"
    break;

  case 81: // builtin_type_expr: TOK_BOOL
#line 621 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 2280 "parser/parser.cpp"
    break;

  case 82: // builtin_type_expr: TOK_CHAR
#line 622 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 2286 "parser/parser.cpp"
    break;

  case 83: // builtin_type_expr: TOK_VOID
#line 623 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Void, yystack_[0].location); }
#line 2292 "parser/parser.cpp"
    break;

  case 84: // path_type_expr: path_expr type_args
#line 628 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[1].value.as < ast::PathExpr* > (), std::move(yystack_[0].value.as < std::vector<ast::TypeExpr*> > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2298 "parser/parser.cpp"
    break;

  case 85: // anon_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 637 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Anon, combine(yystack_[2].location, yystack_[0].location)); }
#line 2304 "parser/parser.cpp"
    break;

  case 86: // fn_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 642 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Fn, combine(yystack_[2].location, yystack_[0].location)); }
#line 2310 "parser/parser.cpp"
    break;

  case 87: // if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 647 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::If, combine(yystack_[2].location, yystack_[0].location)); }
#line 2316 "parser/parser.cpp"
    break;

  case 88: // else_if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 652 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::ElseIf, combine(yystack_[2].location, yystack_[0].location)); }
#line 2322 "parser/parser.cpp"
    break;

  case 89: // else_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 657 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Else, combine(yystack_[2].location, yystack_[0].location)); }
#line 2328 "parser/parser.cpp"
    break;

  case 90: // while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 662 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::While, combine(yystack_[2].location, yystack_[0].location)); }
#line 2334 "parser/parser.cpp"
    break;

  case 91: // do_while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 667 "parser/parser_rules.y"
    { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::DoWhile, combine(yystack_[2].location, yystack_[0].location)); }
#line 2340 "parser/parser.cpp"
    break;

  case 92: // stmt_list_opt: %empty
#line 672 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{}; }
#line 2346 "parser/parser.cpp"
    break;

  case 93: // stmt_list_opt: stmt_list
#line 674 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[0].value.as < std::vector<ast::Statement*> > ()); }
#line 2352 "parser/parser.cpp"
    break;

  case 94: // stmt_list: stmt
#line 679 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{ yystack_[0].value.as < ast::Statement* > () }; }
#line 2358 "parser/parser.cpp"
    break;

  case 95: // stmt_list: stmt_list stmt
#line 681 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Statement*> > ().push_back(yystack_[0].value.as < ast::Statement* > ()); yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()); }
#line 2364 "parser/parser.cpp"
    break;

  case 96: // stmt: simple_stmt
#line 686 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2370 "parser/parser.cpp"
    break;

  case 97: // stmt: compound_stmt
#line 688 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2376 "parser/parser.cpp"
    break;

  case 98: // simple_stmt: var_stmt
#line 692 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::VarStmt* > ()); }
#line 2382 "parser/parser.cpp"
    break;

  case 99: // simple_stmt: return_stmt
#line 693 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ReturnStatement* > ()); }
#line 2388 "parser/parser.cpp"
    break;

  case 100: // simple_stmt: break_stmt
#line 694 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BreakStatement* > ()); }
#line 2394 "parser/parser.cpp"
    break;

  case 101: // simple_stmt: continue_stmt
#line 695 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ContinueStatement* > ()); }
#line 2400 "parser/parser.cpp"
    break;

  case 102: // simple_stmt: expr_stmt
#line 696 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ExprStatement* > ()); }
#line 2406 "parser/parser.cpp"
    break;

  case 103: // compound_stmt: anon_block
#line 700 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 2412 "parser/parser.cpp"
    break;

  case 104: // compound_stmt: if_stmt
#line 701 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::IfStatement* > ()); }
#line 2418 "parser/parser.cpp"
    break;

  case 105: // compound_stmt: while_stmt
#line 702 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::WhileStatement* > ()); }
#line 2424 "parser/parser.cpp"
    break;

  case 106: // compound_stmt: do_while_stmt
#line 703 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::DoWhileStatement* > ()); }
#line 2430 "parser/parser.cpp"
    break;

  case 107: // return_stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 708 "parser/parser_rules.y"
    { yylhs.value.as < ast::ReturnStatement* > () = ast.mk_return_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2436 "parser/parser.cpp"
    break;

  case 108: // if_stmt: TOK_IF TOK_LPAR expr TOK_RPAR if_block elseif_list else_part
#line 713 "parser/parser_rules.y"
    { yylhs.value.as < ast::IfStatement* > () = ast.mk_if_stmt(yystack_[4].value.as < ast::Expr* > (), yystack_[2].value.as < ast::BlockStatement* > (), std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()), yystack_[0].value.as < ast::ElseStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2442 "parser/parser.cpp"
    break;

  case 109: // elseif_list: %empty
#line 718 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::vector<ast::ElseIfStatement*>{}; }
#line 2448 "parser/parser.cpp"
    break;

  case 110: // elseif_list: elseif_list elseif
#line 720 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ().push_back(yystack_[0].value.as < ast::ElseIfStatement* > ()); yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()); }
#line 2454 "parser/parser.cpp"
    break;

  case 111: // elseif: TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR else_if_block
#line 725 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseIfStatement* > () = ast.mk_else_if_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[5].location, yystack_[0].location)); }
#line 2460 "parser/parser.cpp"
    break;

  case 112: // else_part: %empty
#line 730 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = nullptr; }
#line 2466 "parser/parser.cpp"
    break;

  case 113: // else_part: TOK_ELSE else_block
#line 732 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = ast.mk_else_stmt(yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2472 "parser/parser.cpp"
    break;

  case 114: // while_stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR while_block
#line 737 "parser/parser_rules.y"
    { yylhs.value.as < ast::WhileStatement* > () = ast.mk_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 2478 "parser/parser.cpp"
    break;

  case 115: // do_while_stmt: TOK_DO do_while_block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 742 "parser/parser_rules.y"
    { yylhs.value.as < ast::DoWhileStatement* > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2484 "parser/parser.cpp"
    break;

  case 116: // break_stmt: TOK_BREAK TOK_SMCLN
#line 747 "parser/parser_rules.y"
    { yylhs.value.as < ast::BreakStatement* > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2490 "parser/parser.cpp"
    break;

  case 117: // continue_stmt: TOK_CONTINUE TOK_SMCLN
#line 752 "parser/parser_rules.y"
    { yylhs.value.as < ast::ContinueStatement* > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2496 "parser/parser.cpp"
    break;

  case 118: // expr_stmt: expr TOK_SMCLN
#line 757 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprStatement* > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2502 "parser/parser.cpp"
    break;

  case 119: // var_stmt: var_stmt_default
#line 765 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2508 "parser/parser.cpp"
    break;

  case 120: // var_stmt: var_stmt_imm
#line 766 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2514 "parser/parser.cpp"
    break;

  case 121: // var_stmt: var_stmt_mut
#line 767 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2520 "parser/parser.cpp"
    break;

  case 122: // var_stmt_default: ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 774 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             nullptr,
             combine(yystack_[3].location, yystack_[0].location)
           );
    }
#line 2534 "parser/parser.cpp"
    break;

  case 123: // var_stmt_default: ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 784 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[5].location, yystack_[0].location)
           );
    }
#line 2548 "parser/parser.cpp"
    break;

  case 124: // var_stmt_imm: TOK_IMM ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 797 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             nullptr,
             combine(yystack_[4].location, yystack_[0].location)
           );
    }
#line 2562 "parser/parser.cpp"
    break;

  case 125: // var_stmt_imm: TOK_IMM ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 807 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Imm,
             ast::Storage::Auto,
             yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[6].location, yystack_[0].location)
           );
    }
#line 2576 "parser/parser.cpp"
    break;

  case 126: // var_stmt_mut: TOK_MUT ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 820 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Auto,
             nullptr,
             combine(yystack_[4].location, yystack_[0].location)
           );
    }
#line 2590 "parser/parser.cpp"
    break;

  case 127: // var_stmt_mut: TOK_MUT ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 830 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::VarStmt* > () = ast.mk_var_stmt(
             yystack_[5].value.as < Str > (), yystack_[3].value.as < ast::TypeExpr* > (),
             ast::Mutability::Mut,
             ast::Storage::Auto,
             yystack_[1].value.as < ast::Expr* > (),
             combine(yystack_[6].location, yystack_[0].location)
           );
    }
#line 2604 "parser/parser.cpp"
    break;

  case 128: // expr: assign
#line 846 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2610 "parser/parser.cpp"
    break;

  case 129: // expr_opt: %empty
#line 850 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = nullptr; }
#line 2616 "parser/parser.cpp"
    break;

  case 130: // expr_opt: expr
#line 851 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2622 "parser/parser.cpp"
    break;

  case 131: // assign: cond
#line 856 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2628 "parser/parser.cpp"
    break;

  case 132: // assign: unary TOK_ASSIGN assign
#line 858 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Assign,   combine(yystack_[2].location, yystack_[0].location)); }
#line 2634 "parser/parser.cpp"
    break;

  case 133: // cond: logic_or
#line 863 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2640 "parser/parser.cpp"
    break;

  case 134: // logic_or: logic_and
#line 868 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2646 "parser/parser.cpp"
    break;

  case 135: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 870 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2652 "parser/parser.cpp"
    break;

  case 136: // logic_and: equality
#line 875 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2658 "parser/parser.cpp"
    break;

  case 137: // logic_and: logic_and TOK_BOOL_AND equality
#line 877 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2664 "parser/parser.cpp"
    break;

  case 138: // equality: relational
#line 882 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2670 "parser/parser.cpp"
    break;

  case 139: // equality: equality TOK_EQUAL relational
#line 884 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::equal,     yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2676 "parser/parser.cpp"
    break;

  case 140: // equality: equality TOK_NEQUAL relational
#line 886 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2682 "parser/parser.cpp"
    break;

  case 141: // relational: additive
#line 891 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2688 "parser/parser.cpp"
    break;

  case 142: // relational: relational TOK_LESS additive
#line 893 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less,          yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2694 "parser/parser.cpp"
    break;

  case 143: // relational: relational TOK_LEQ additive
#line 895 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal,    yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2700 "parser/parser.cpp"
    break;

  case 144: // relational: relational TOK_GREATER additive
#line 897 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater,       yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2706 "parser/parser.cpp"
    break;

  case 145: // relational: relational TOK_GEQ additive
#line 899 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2712 "parser/parser.cpp"
    break;

  case 146: // additive: multiplicative
#line 904 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2718 "parser/parser.cpp"
    break;

  case 147: // additive: additive TOK_PLUS multiplicative
#line 906 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::add,      yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2724 "parser/parser.cpp"
    break;

  case 148: // additive: additive TOK_MINUS multiplicative
#line 908 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2730 "parser/parser.cpp"
    break;

  case 149: // multiplicative: unary
#line 913 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2736 "parser/parser.cpp"
    break;

  case 150: // multiplicative: multiplicative TOK_STAR unary
#line 915 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2742 "parser/parser.cpp"
    break;

  case 151: // multiplicative: multiplicative TOK_SLASH unary
#line 917 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::divide,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2748 "parser/parser.cpp"
    break;

  case 152: // multiplicative: multiplicative TOK_MODULO unary
#line 919 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2754 "parser/parser.cpp"
    break;

  case 153: // unary: TOK_MINUS unary
#line 924 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::negation,      yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2760 "parser/parser.cpp"
    break;

  case 154: // unary: TOK_NEGATION unary
#line 926 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not,   yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2766 "parser/parser.cpp"
    break;

  case 155: // unary: TOK_INC unary
#line 928 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2772 "parser/parser.cpp"
    break;

  case 156: // unary: TOK_DEC unary
#line 930 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2778 "parser/parser.cpp"
    break;

  case 157: // unary: TOK_STAR unary
#line 932 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::deref,         yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2784 "parser/parser.cpp"
    break;

  case 158: // unary: TOK_AMP unary
#line 934 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::addr_of,       yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2790 "parser/parser.cpp"
    break;

  case 159: // unary: TOK_AMP TOK_MUT unary
#line 936 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::addr_of_mut,   yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2796 "parser/parser.cpp"
    break;

  case 160: // unary: postfix
#line 938 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2802 "parser/parser.cpp"
    break;

  case 161: // postfix: primary
#line 943 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 2808 "parser/parser.cpp"
    break;

  case 162: // postfix: postfix type_args TOK_LPAR arg_list_opt TOK_RPAR
#line 945 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_call_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 2814 "parser/parser.cpp"
    break;

  case 163: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 947 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_index(yystack_[3].value.as < ast::Expr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location)); }
#line 2820 "parser/parser.cpp"
    break;

  case 164: // postfix: postfix TOK_DOT ident_no_self
#line 949 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_field_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2826 "parser/parser.cpp"
    break;

  case 165: // postfix: postfix TOK_INC
#line 951 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2832 "parser/parser.cpp"
    break;

  case 166: // postfix: postfix TOK_DEC
#line 953 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2838 "parser/parser.cpp"
    break;

  case 167: // postfix: postfix type_args TOK_LCBRA field_inits_opt TOK_RCBRA
#line 955 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_struct_literal_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()), combine(yystack_[4].location, yystack_[0].location)); }
#line 2844 "parser/parser.cpp"
    break;

  case 168: // postfix: TOK_LBRACK array_elems_opt TOK_RBRACK
#line 957 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(ast.mk_array_literal_expr(std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[2].location, yystack_[0].location))); }
#line 2850 "parser/parser.cpp"
    break;

  case 169: // arg_list_opt: %empty
#line 962 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2856 "parser/parser.cpp"
    break;

  case 170: // arg_list_opt: arg_list
#line 964 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 2862 "parser/parser.cpp"
    break;

  case 171: // arg_list: expr
#line 969 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 2868 "parser/parser.cpp"
    break;

  case 172: // arg_list: arg_list TOK_COMMA expr
#line 971 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2874 "parser/parser.cpp"
    break;

  case 173: // arg_list: arg_list TOK_COMMA
#line 973 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2880 "parser/parser.cpp"
    break;

  case 174: // array_elems_opt: %empty
#line 978 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2886 "parser/parser.cpp"
    break;

  case 175: // array_elems_opt: array_elems
#line 980 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 2892 "parser/parser.cpp"
    break;

  case 176: // array_elems: expr
#line 985 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 2898 "parser/parser.cpp"
    break;

  case 177: // array_elems: array_elems TOK_COMMA expr
#line 987 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2904 "parser/parser.cpp"
    break;

  case 178: // array_elems: array_elems TOK_COMMA
#line 989 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2910 "parser/parser.cpp"
    break;

  case 179: // int_literal_type_opt: %empty
#line 997 "parser/parser_rules.y"
               { yylhs.value.as < std::optional<kl::rt::IntKind> > () = std::nullopt; }
#line 2916 "parser/parser.cpp"
    break;

  case 180: // int_literal_type_opt: TOK_AS TOK_I8
#line 998 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I8; }
#line 2922 "parser/parser.cpp"
    break;

  case 181: // int_literal_type_opt: TOK_AS TOK_U8
#line 999 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U8; }
#line 2928 "parser/parser.cpp"
    break;

  case 182: // int_literal_type_opt: TOK_AS TOK_I16
#line 1000 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I16; }
#line 2934 "parser/parser.cpp"
    break;

  case 183: // int_literal_type_opt: TOK_AS TOK_U16
#line 1001 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U16; }
#line 2940 "parser/parser.cpp"
    break;

  case 184: // int_literal_type_opt: TOK_AS TOK_I32
#line 1002 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I32; }
#line 2946 "parser/parser.cpp"
    break;

  case 185: // int_literal_type_opt: TOK_AS TOK_U32
#line 1003 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U32; }
#line 2952 "parser/parser.cpp"
    break;

  case 186: // int_literal_type_opt: TOK_AS TOK_I64
#line 1004 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I64; }
#line 2958 "parser/parser.cpp"
    break;

  case 187: // int_literal_type_opt: TOK_AS TOK_U64
#line 1005 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U64; }
#line 2964 "parser/parser.cpp"
    break;

  case 188: // int_literal_type_opt: TOK_AS TOK_I128
#line 1006 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I128; }
#line 2970 "parser/parser.cpp"
    break;

  case 189: // int_literal_type_opt: TOK_AS TOK_U128
#line 1007 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U128; }
#line 2976 "parser/parser.cpp"
    break;

  case 190: // float_literal_type_opt: %empty
#line 1011 "parser/parser_rules.y"
               { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = std::nullopt; }
#line 2982 "parser/parser.cpp"
    break;

  case 191: // float_literal_type_opt: TOK_AS TOK_F32
#line 1012 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F32; }
#line 2988 "parser/parser.cpp"
    break;

  case 192: // float_literal_type_opt: TOK_AS TOK_F64
#line 1013 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F64; }
#line 2994 "parser/parser.cpp"
    break;

  case 193: // primary: ident_no_self
#line 1022 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3000 "parser/parser.cpp"
    break;

  case 194: // primary: TOK_SELF
#line 1024 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3006 "parser/parser.cpp"
    break;

  case 195: // primary: qpath_expr
#line 1026 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(yystack_[0].value.as < ast::PathExpr* > ()); }
#line 3012 "parser/parser.cpp"
    break;

  case 196: // primary: TOK_INT_LITERAL int_literal_type_opt
#line 1028 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::IntKind> > (), yystack_[1].location); }
#line 3018 "parser/parser.cpp"
    break;

  case 197: // primary: TOK_FLOAT_LITERAL float_literal_type_opt
#line 1030 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_float_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::FloatKind> > (), yystack_[1].location); }
#line 3024 "parser/parser.cpp"
    break;

  case 198: // primary: TOK_STRING_LITERAL
#line 1032 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3030 "parser/parser.cpp"
    break;

  case 199: // primary: TOK_BOOL_LITERAL
#line 1034 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl::rt::boolean > (), yystack_[0].location); }
#line 3036 "parser/parser.cpp"
    break;

  case 200: // primary: TOK_CHAR_LITERAL
#line 1036 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_char_literal_expr(yystack_[0].value.as < kl::rt::character > (), yystack_[0].location); }
#line 3042 "parser/parser.cpp"
    break;

  case 201: // primary: TOK_LPAR expr TOK_RPAR
#line 1038 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[1].value.as < ast::Expr* > (); }
#line 3048 "parser/parser.cpp"
    break;

  case 202: // field_inits_opt: %empty
#line 1043 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{}; }
#line 3054 "parser/parser.cpp"
    break;

  case 203: // field_inits_opt: field_inits
#line 1045 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3060 "parser/parser.cpp"
    break;

  case 204: // field_inits: field_init
#line 1050 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{ yystack_[0].value.as < ast::FieldInitExpr* > () }; }
#line 3066 "parser/parser.cpp"
    break;

  case 205: // field_inits: field_inits TOK_COMMA field_init
#line 1052 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ().push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3072 "parser/parser.cpp"
    break;

  case 206: // field_inits: field_inits TOK_COMMA
#line 1054 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3078 "parser/parser.cpp"
    break;

  case 207: // field_init: ident_no_self TOK_COLON expr
#line 1059 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr* > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3084 "parser/parser.cpp"
    break;


#line 3088 "parser/parser.cpp"

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


  const short parser::yypact_ninf_ = -209;

  const signed char parser::yytable_ninf_ = -34;

  const short
  parser::yypact_[] =
  {
       2,    56,    29,  -209,  -209,  -209,    -8,   -10,  -209,  -209,
      56,    48,  -209,    56,    34,    48,  -209,   -11,  -209,    52,
    -209,    36,  -209,  -209,  -209,  -209,  -209,  -209,  -209,    31,
    -209,    31,    31,    60,  -209,  -209,    23,    14,    14,    31,
    -209,    31,    10,    74,    75,  -209,   -33,  -209,    -4,  -209,
      31,    31,    31,  -209,    31,    70,    78,    -4,  -209,    71,
      79,    76,  -209,    83,  -209,    80,   294,  -209,  -209,   294,
      81,    31,    81,   294,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   294,
      87,    73,    82,  -209,    90,  -209,  -209,  -209,  -209,   294,
      89,  -209,    88,    91,    95,  -209,  -209,   346,   294,  -209,
    -209,   302,  -209,   200,  -209,  -209,  -209,  -209,    90,   -14,
    -209,    86,    93,   123,   125,  -209,  -209,  -209,   302,   302,
     302,   302,   302,   250,   302,   302,   109,  -209,  -209,   110,
      99,  -209,  -209,    94,    96,    32,    22,    43,    15,    92,
      11,  -209,   126,   128,   121,   302,    31,    31,   122,   127,
     200,   129,  -209,   130,   200,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   131,
     294,  -209,   202,  -209,    77,  -209,   132,  -209,   133,   124,
    -209,  -209,  -209,   302,  -209,  -209,  -209,    56,    56,  -209,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,    31,  -209,  -209,    -6,   302,
     302,   200,   177,  -209,   134,   135,   136,  -209,  -209,   141,
     294,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   302,
    -209,  -209,  -209,    96,  -209,    32,    22,    22,    43,    43,
      43,    43,    15,    15,  -209,  -209,  -209,  -209,   144,  -209,
     302,    31,   147,   148,   149,   152,  -209,   294,   294,  -209,
     -31,  -209,  -209,  -209,   154,   155,   145,   153,   159,  -209,
     162,   163,  -209,   302,   -28,   -24,  -209,   302,  -209,   302,
     302,  -209,    31,   200,  -209,   200,  -209,   170,  -209,   302,
    -209,   302,   167,  -209,  -209,  -209,   171,   210,   172,   183,
     196,   198,  -209,  -209,     4,  -209,  -209,  -209,  -209,  -209,
    -209,   206,   200,  -209,   302,   203,   208,  -209,   207,   200,
    -209,   205,  -209
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,    17,    18,    12,     0,    10,     1,
       0,     4,    11,     0,    30,     5,     6,     0,    31,     0,
       3,    30,    34,    36,    37,    38,    41,    42,     7,     0,
       8,     0,     0,     0,    35,    16,     0,    19,    19,     0,
       9,     0,     0,     0,     0,    24,     0,    21,    45,    44,
      52,    52,    23,    20,     0,     0,     0,    46,    47,     0,
       0,    53,    54,     0,    22,     0,     0,    43,    48,     0,
       0,    56,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      61,    25,     0,    58,    59,    64,    66,    67,    57,     0,
       0,    55,     0,     0,     0,    63,    62,     0,     0,    84,
      49,     0,    51,    92,    39,    40,    50,    68,    60,     0,
      27,    16,   194,   179,   190,   198,   199,   200,     0,   174,
       0,     0,     0,     0,     0,     0,    15,   195,   193,     0,
       0,   128,   131,   133,   134,   136,   138,   141,   146,   149,
     160,   161,     0,     0,     0,   129,     0,     0,     0,     0,
      92,   193,   103,     0,    93,    94,    96,    97,    99,   104,
     105,   106,   100,   101,   102,    98,   119,   120,   121,     0,
      29,    26,     0,   196,     0,   197,     0,   176,     0,   175,
     154,   155,   156,     0,   158,   157,   153,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,   166,     0,     0,
       0,    92,     0,   130,     0,     0,     0,   116,   117,     0,
       0,    86,    95,   118,    28,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   191,   192,   201,   168,   178,
     159,    14,    13,   135,   149,   137,   139,   140,   142,   143,
     144,   145,   147,   148,   150,   151,   152,   132,     0,   164,
     169,   202,     0,     0,     0,     0,   107,     0,     0,    85,
       0,   177,   163,   171,     0,   170,     0,     0,   203,   204,
       0,     0,    91,     0,     0,     0,   122,     0,   162,   173,
       0,   167,   206,    92,   109,    92,   114,     0,   126,     0,
     124,     0,     0,   172,   207,   205,     0,   112,     0,     0,
       0,     0,   123,    87,     0,   110,   108,    90,   115,   127,
     125,     0,    92,   113,     0,     0,     0,    89,     0,    92,
     111,     0,    88
  };

  const short
  parser::yypgoto_[] =
  {
    -209,  -209,  -209,  -209,  -209,   233,  -209,    44,  -209,  -209,
     -29,     3,   215,  -209,   209,   113,  -209,  -209,  -209,  -209,
     238,  -209,  -209,  -209,  -209,  -209,  -209,  -209,   211,   192,
     214,  -209,   195,   -58,  -209,  -209,   160,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -159,  -209,   105,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -102,  -209,  -208,  -209,
    -209,    72,    69,   -94,  -111,   -95,   -52,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,   -27
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     2,     3,    14,    15,    16,     6,    91,   136,   137,
     138,   139,    42,    46,    47,   109,   119,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    56,    57,    58,   100,
      60,    61,    62,    92,    93,   107,    94,    95,    96,    97,
     162,   114,   304,   340,   333,   306,   222,   163,   164,   165,
     166,   167,   168,   169,   317,   325,   326,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   224,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   284,   285,
     188,   189,   183,   185,   151,   287,   288,   289
  };

  const short
  parser::yytable_[] =
  {
      36,   229,    37,    38,     8,   267,    29,   331,    54,   140,
      44,    98,    45,    12,    52,   103,     8,   296,     1,    55,
     308,    59,    59,    45,   310,    65,   186,   187,    55,     9,
      35,   104,    53,   180,   -32,   270,   -33,    30,    11,   271,
     297,   112,    59,   309,    10,     7,    18,   311,    18,   332,
     120,   181,   -25,   223,   214,    48,   -25,    17,    49,    31,
      32,   215,   274,    13,   108,    35,   216,   217,    39,     8,
      33,    40,     8,   210,   211,   212,     8,    41,   190,   191,
     192,   194,   195,   196,   161,   204,   205,   206,   207,   312,
       4,     5,     8,   258,   259,   260,   261,   105,   106,   202,
     203,   320,     8,   321,   208,   209,   245,   246,   256,   257,
       8,     8,   268,   262,   263,    50,    51,   272,   273,    66,
      69,    70,   234,    71,    67,    72,   108,   225,   226,    73,
     110,   161,    99,   111,   113,   161,   115,   117,   -17,   116,
     182,   250,   184,   199,   316,   -18,   318,   281,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   264,   265,
     266,   197,   198,   213,   200,   201,   221,   219,   283,   220,
     227,   249,   280,   335,   247,   228,   231,   248,   230,   233,
     341,   275,   276,     8,   277,   278,   269,   279,   282,   290,
     291,   307,   161,   293,   300,   292,   298,   313,   314,   301,
     251,   252,   299,   152,   153,   154,   302,   303,   305,   155,
     156,   157,   319,   158,   159,   322,   324,   323,   327,   294,
     295,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   328,   336,     8,   121,   122,   123,   124,   125,   126,
     127,   128,   286,   129,   329,   160,   330,   334,    28,   337,
     338,   342,   339,    43,   130,   131,   132,   133,   134,    34,
     193,    64,   135,   218,   102,    63,   101,   118,    68,   232,
     255,     0,   253,   286,   161,   315,   161,     0,     0,     0,
       8,     8,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   128,     0,   129,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   161,   130,   131,   132,   133,   134,     0,
     161,     0,   135,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     4,     5,
       0,     0,     0,     0,     0,    89,   121,   122,   123,   124,
     125,   126,   127,   128,     0,   129,     0,     0,     0,     0,
       0,    90,     0,     0,     0,     0,   130,   131,   132,   133,
     134,     0,     0,     0,   135,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
       4,     5,     0,     0,     0,     0,     0,    89
  };

  const short
  parser::yycheck_[] =
  {
      29,   160,    31,    32,     1,   213,    17,     3,    12,   111,
      39,    69,    41,    10,    47,    73,    13,    48,    16,    48,
      48,    50,    51,    52,    48,    54,   128,   129,    57,     0,
      34,    89,    65,    47,     0,    41,     0,    48,    48,    45,
      71,    99,    71,    71,    52,     1,    12,    71,    12,    45,
     108,    65,    41,   155,    43,    45,    45,    13,    48,     7,
       8,    50,   221,    15,    53,    34,    55,    56,     8,    66,
      18,    48,    69,    58,    59,    60,    73,    63,   130,   131,
     132,   133,   134,   135,   113,    63,    64,    65,    66,   297,
      34,    35,    89,   204,   205,   206,   207,    10,    11,    67,
      68,   309,    99,   311,    61,    62,    29,    30,   202,   203,
     107,   108,   214,   208,   209,    41,    41,   219,   220,    49,
      49,    42,   180,    47,    46,    42,    53,   156,   157,    49,
      48,   160,    51,    43,    45,   164,    48,    42,    52,    48,
      17,   193,    17,    44,   303,    52,   305,   249,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,    52,    52,    71,    70,    69,    45,    41,   270,    41,
      48,    47,   230,   332,    42,    48,    46,    44,    49,    48,
     339,     4,    48,   180,    49,    49,   215,    46,    44,    42,
      42,   293,   221,    41,    49,    46,    42,   299,   300,    46,
     197,   198,    47,     3,     4,     5,    47,    45,    45,     9,
      10,    11,    42,    13,    14,    48,     6,    46,    46,   277,
     278,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    48,   334,   230,    34,    35,    36,    37,    38,    39,
      40,    41,   271,    43,    48,    45,    48,    41,    15,    46,
      42,    46,    45,    38,    54,    55,    56,    57,    58,    21,
      10,    52,    62,   150,    72,    51,    71,   107,    57,   164,
     201,    -1,   200,   302,   303,   302,   305,    -1,    -1,    -1,
     277,   278,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   332,    54,    55,    56,    57,    58,    -1,
     339,    -1,    62,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    62,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    16,    77,    78,    34,    35,    82,    83,    87,     0,
      52,    48,    87,    15,    79,    80,    81,    83,    12,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    81,    17,
      48,     7,     8,    18,    96,    34,    86,    86,    86,     8,
      48,    63,    88,    88,    86,    86,    89,    90,    45,    48,
      41,    41,    47,    65,    12,    86,   102,   103,   104,    86,
     106,   107,   108,   106,    90,    86,    49,    46,   104,    49,
      42,    47,    42,    49,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    41,
      57,    83,   109,   110,   112,   113,   114,   115,   109,    51,
     105,   108,   105,   109,   109,    10,    11,   111,    53,    91,
      48,    43,   109,    45,   117,    48,    48,    42,   112,    92,
     109,    34,    35,    36,    37,    38,    39,    40,    41,    43,
      54,    55,    56,    57,    58,    62,    84,    85,    86,    87,
     142,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   160,     3,     4,     5,     9,    10,    11,    13,    14,
      45,    86,   116,   123,   124,   125,   126,   127,   128,   129,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
      47,    65,    17,   158,    17,   159,   142,   142,   156,   157,
     152,   152,   152,    10,   152,   152,   152,    52,    52,    44,
      70,    69,    67,    68,    63,    64,    65,    66,    61,    62,
      58,    59,    60,    71,    43,    50,    55,    56,    91,    41,
      41,    45,   122,   142,   143,    86,    86,    48,    48,   123,
      49,    46,   125,    48,   109,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    42,    44,    47,
     152,    87,    87,   147,   152,   148,   149,   149,   150,   150,
     150,   150,   151,   151,   152,   152,   152,   144,   142,    86,
      41,    45,   142,   142,   123,     4,    48,    49,    49,    46,
     109,   142,    44,   142,   154,   155,    86,   161,   162,   163,
      42,    42,    46,    41,   109,   109,    48,    71,    42,    47,
      49,    46,    47,    45,   118,    45,   121,   142,    48,    71,
      48,    71,   144,   142,   142,   163,   123,   130,   123,    42,
     144,   144,    48,    46,     6,   131,   132,    46,    48,    48,
      48,     3,    45,   120,    41,   123,   142,    46,    42,    45,
     119,   123,    46
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    76,    77,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    83,    84,    84,    85,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    91,    91,    92,    92,    92,
      93,    93,    94,    94,    95,    95,    96,    96,    96,    97,
      98,    99,    99,   100,   101,   102,   102,   103,   103,   104,
     104,   105,   106,   106,   107,   107,   107,   108,   109,   109,
     110,   111,   111,   111,   112,   112,   113,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     126,   126,   126,   127,   127,   127,   127,   128,   129,   130,
     130,   131,   132,   132,   133,   134,   135,   136,   137,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   143,
     143,   144,   144,   145,   146,   146,   147,   147,   148,   148,
     148,   149,   149,   149,   149,   149,   150,   150,   150,   151,
     151,   151,   151,   152,   152,   152,   152,   152,   152,   152,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   154,
     154,   155,   155,   155,   156,   156,   157,   157,   157,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   159,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   161,   161,   162,   162,   162,   163
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     5,     0,     1,     1,     2,     3,     5,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     0,
       3,     1,     3,     2,     1,     0,     3,     1,     3,     2,
       0,     1,     0,     1,     1,     2,     1,     1,     1,     9,
       9,     1,     1,     7,     5,     0,     1,     1,     2,     4,
       5,     2,     0,     1,     1,     3,     2,     3,     1,     1,
       3,     0,     1,     1,     1,     4,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     7,     0,
       2,     6,     0,     2,     5,     7,     2,     2,     2,     1,
       1,     1,     4,     6,     5,     7,     5,     7,     1,     0,
       1,     1,     3,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       1,     1,     5,     4,     3,     2,     2,     5,     3,     0,
       1,     1,     3,     2,     0,     1,     1,     3,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       0,     2,     2,     1,     1,     1,     2,     2,     1,     1,
       1,     3,     0,     1,     1,     3,     2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_FN", "TOK_RETURN", "TOK_MUT",
  "TOK_IMM", "TOK_PUB", "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT",
  "TOK_PACKAGE", "TOK_AS", "TOK_LOAD", "TOK_I8", "TOK_U8", "TOK_I16",
  "TOK_U16", "TOK_I32", "TOK_U32", "TOK_I64", "TOK_U64", "TOK_I128",
  "TOK_U128", "TOK_F32", "TOK_F64", "TOK_BOOL", "TOK_CHAR", "TOK_VOID",
  "TOK_IDENTIFIER", "TOK_SELF", "TOK_INT_LITERAL", "TOK_FLOAT_LITERAL",
  "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL", "TOK_CHAR_LITERAL", "TOK_LPAR",
  "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA", "TOK_RCBRA",
  "TOK_COMMA", "TOK_SMCLN", "TOK_COLON", "TOK_DOT", "TOK_ARROW",
  "TOK_COLONCOLON", "TOK_TURBOFISH_S", "TOK_NEGATION", "TOK_INC",
  "TOK_DEC", "TOK_AMP", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "LOWER_THAN_ASSIGN", "$accept",
  "translation_unit", "module", "import_list_opt", "import_list",
  "import_decl", "path", "path_expr", "qpath", "qpath_expr",
  "ident_no_self", "ident_any", "type_params_opt", "type_param_list",
  "type_param", "type_args", "type_arg_list", "pub_opt", "decl_list_opt",
  "decl_list", "decl", "fn_decl", "load_fn_decl", "struct_decl",
  "struct_decl_def", "struct_decl_fwd", "field_decl_list_opt",
  "field_decl_list", "field_decl", "ret_type_expr", "param_list_opt",
  "param_list", "param", "type_expr", "ref_type_expr", "ref_mutability",
  "type_postfix", "type_primary", "builtin_type_expr", "path_type_expr",
  "anon_block", "fn_block", "if_block", "else_if_block", "else_block",
  "while_block", "do_while_block", "stmt_list_opt", "stmt_list", "stmt",
  "simple_stmt", "compound_stmt", "return_stmt", "if_stmt", "elseif_list",
  "elseif", "else_part", "while_stmt", "do_while_stmt", "break_stmt",
  "continue_stmt", "expr_stmt", "var_stmt", "var_stmt_default",
  "var_stmt_imm", "var_stmt_mut", "expr", "expr_opt", "assign", "cond",
  "logic_or", "logic_and", "equality", "relational", "additive",
  "multiplicative", "unary", "postfix", "arg_list_opt", "arg_list",
  "array_elems_opt", "array_elems", "int_literal_type_opt",
  "float_literal_type_opt", "primary", "field_inits_opt", "field_inits",
  "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   322,   322,   327,   335,   337,   342,   344,   349,   351,
     360,   362,   367,   372,   374,   379,   384,   389,   391,   400,
     402,   407,   409,   411,   416,   421,   423,   428,   430,   432,
     441,   442,   446,   448,   453,   455,   460,   462,   464,   469,
     477,   485,   487,   492,   506,   520,   522,   527,   529,   534,
     536,   541,   550,   552,   557,   559,   561,   566,   575,   577,
     582,   587,   588,   589,   593,   595,   600,   602,   604,   609,
     610,   611,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   621,   622,   623,   627,   636,   641,   646,   651,   656,
     661,   666,   671,   673,   678,   680,   685,   687,   692,   693,
     694,   695,   696,   700,   701,   702,   703,   707,   712,   717,
     719,   724,   729,   731,   736,   741,   746,   751,   756,   765,
     766,   767,   773,   783,   796,   806,   819,   829,   846,   850,
     851,   855,   857,   862,   867,   869,   874,   876,   881,   883,
     885,   890,   892,   894,   896,   898,   903,   905,   907,   912,
     914,   916,   918,   923,   925,   927,   929,   931,   933,   935,
     937,   942,   944,   946,   948,   950,   952,   954,   956,   961,
     963,   968,   970,   972,   977,   979,   984,   986,   988,   997,
     998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1006,  1007,
    1011,  1012,  1013,  1021,  1023,  1025,  1027,  1029,  1031,  1033,
    1035,  1037,  1042,  1044,  1049,  1051,  1053,  1058
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
#line 3972 "parser/parser.cpp"

#line 1062 "parser/parser_rules.y"


