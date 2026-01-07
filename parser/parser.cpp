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
      case T::TOK_SELF:           return yy::parser::make_TOK_SELF(t.u_.sym, L);

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

      case T::TOK_IMPL:        return yy::parser::make_TOK_IMPL(L);
      case T::TOK_FOR:         return yy::parser::make_TOK_FOR(L);
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

#line 171 "parser/parser.cpp"


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
#line 264 "parser/parser.cpp"

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
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
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

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.YY_MOVE_OR_COPY< ast::ImplFnDecl* > (YY_MOVE (that.value));
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
      case symbol_kind::S_self_param: // self_param
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

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.YY_MOVE_OR_COPY< ast::TraitFnDecl* > (YY_MOVE (that.value));
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

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.YY_MOVE_OR_COPY< std::vector<ast::ImplFnDecl*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.YY_MOVE_OR_COPY< std::vector<ast::TraitFnDecl*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
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

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.move< ast::ImplFnDecl* > (YY_MOVE (that.value));
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
      case symbol_kind::S_self_param: // self_param
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

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.move< ast::TraitFnDecl* > (YY_MOVE (that.value));
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

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.move< std::vector<ast::ImplFnDecl*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.move< std::vector<ast::TraitFnDecl*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
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

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.copy< ast::ImplFnDecl* > (that.value);
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
      case symbol_kind::S_self_param: // self_param
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

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.copy< ast::TraitFnDecl* > (that.value);
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

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.copy< std::vector<ast::ImplFnDecl*> > (that.value);
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

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.copy< std::vector<ast::TraitFnDecl*> > (that.value);
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
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
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

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        value.move< ast::ImplFnDecl* > (that.value);
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
      case symbol_kind::S_self_param: // self_param
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

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        value.move< ast::TraitFnDecl* > (that.value);
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

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        value.move< std::vector<ast::ImplFnDecl*> > (that.value);
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

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        value.move< std::vector<ast::TraitFnDecl*> > (that.value);
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
      case symbol_kind::S_trait_decl: // trait_decl
      case symbol_kind::S_impl_decl: // impl_decl
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

      case symbol_kind::S_impl_fn_decl: // impl_fn_decl
      case symbol_kind::S_impl_item: // impl_item
        yylhs.value.emplace< ast::ImplFnDecl* > ();
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
      case symbol_kind::S_self_param: // self_param
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

      case symbol_kind::S_trait_fn_decl: // trait_fn_decl
      case symbol_kind::S_trait_item: // trait_item
        yylhs.value.emplace< ast::TraitFnDecl* > ();
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

      case symbol_kind::S_array_elems_opt: // array_elems_opt
      case symbol_kind::S_array_elems: // array_elems
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

      case symbol_kind::S_impl_item_list_opt: // impl_item_list_opt
      case symbol_kind::S_impl_item_list: // impl_item_list
        yylhs.value.emplace< std::vector<ast::ImplFnDecl*> > ();
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

      case symbol_kind::S_trait_item_list_opt: // trait_item_list_opt
      case symbol_kind::S_trait_item_list: // trait_item_list
        yylhs.value.emplace< std::vector<ast::TraitFnDecl*> > ();
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
#line 359 "parser/parser_rules.y"
    {  }
#line 1922 "parser/parser.cpp"
    break;

  case 3: // module: TOK_PACKAGE path_expr TOK_SMCLN import_list_opt decl_list_opt
#line 364 "parser/parser_rules.y"
    {
      ast.mk_module(yystack_[3].value.as < ast::PathExpr* > (), std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()), std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()), combine(yystack_[4].location, yystack_[0].location));
      unit.addModule(std::move(ast));
    }
#line 1931 "parser/parser.cpp"
    break;

  case 4: // import_list_opt: %empty
#line 372 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{}; }
#line 1937 "parser/parser.cpp"
    break;

  case 5: // import_list_opt: import_list
#line 374 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1943 "parser/parser.cpp"
    break;

  case 6: // import_list: import_decl
#line 379 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::vector<ast::ImportDecl*>{ yystack_[0].value.as < ast::ImportDecl* > () }; }
#line 1949 "parser/parser.cpp"
    break;

  case 7: // import_list: import_list import_decl
#line 381 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImportDecl*> > ().push_back(yystack_[0].value.as < ast::ImportDecl* > ()); yylhs.value.as < std::vector<ast::ImportDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImportDecl*> > ()); }
#line 1955 "parser/parser.cpp"
    break;

  case 8: // import_decl: TOK_IMPORT path_expr TOK_SMCLN
#line 386 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[1].value.as < ast::PathExpr* > ()), std::nullopt, /*is_public*/false, combine(yystack_[2].location, yystack_[0].location)); }
#line 1961 "parser/parser.cpp"
    break;

  case 9: // import_decl: TOK_IMPORT path_expr TOK_AS ident_no_self TOK_SMCLN
#line 388 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImportDecl* > () = ast.mk_import_decl(std::move(yystack_[3].value.as < ast::PathExpr* > ()), std::optional<Str>{yystack_[1].value.as < Str > ()}, /*is_public*/false, combine(yystack_[4].location, yystack_[0].location)); }
#line 1967 "parser/parser.cpp"
    break;

  case 10: // path: ident_any
#line 398 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[0].value.as < Str > () }; }
#line 1973 "parser/parser.cpp"
    break;

  case 11: // path: path TOK_COLONCOLON ident_any
#line 400 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1979 "parser/parser.cpp"
    break;

  case 12: // path_expr: path
#line 405 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 1985 "parser/parser.cpp"
    break;

  case 13: // qpath: ident_any TOK_COLONCOLON ident_any
#line 410 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<Str> > () = std::vector<Str>{ yystack_[2].value.as < Str > (), yystack_[0].value.as < Str > () }; }
#line 1991 "parser/parser.cpp"
    break;

  case 14: // qpath: qpath TOK_COLONCOLON ident_any
#line 412 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<Str> > ().push_back(yystack_[0].value.as < Str > ()); yylhs.value.as < std::vector<Str> > () = std::move(yystack_[2].value.as < std::vector<Str> > ()); }
#line 1997 "parser/parser.cpp"
    break;

  case 15: // qpath_expr: qpath
#line 417 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathExpr* > () = ast.mk_path_expr(std::move(yystack_[0].value.as < std::vector<Str> > ()), yystack_[0].location); }
#line 2003 "parser/parser.cpp"
    break;

  case 16: // ident_no_self: TOK_IDENTIFIER
#line 422 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 2009 "parser/parser.cpp"
    break;

  case 17: // ident_any: TOK_IDENTIFIER
#line 427 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 2015 "parser/parser.cpp"
    break;

  case 18: // ident_any: TOK_SELF
#line 429 "parser/parser_rules.y"
    { yylhs.value.as < Str > () = yystack_[0].value.as < Str > (); }
#line 2021 "parser/parser.cpp"
    break;

  case 19: // type_params_opt: %empty
#line 438 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{}; }
#line 2027 "parser/parser.cpp"
    break;

  case 20: // type_params_opt: TOK_LESS type_param_list TOK_GREATER
#line 440 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 2033 "parser/parser.cpp"
    break;

  case 21: // type_param_list: type_param
#line 445 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::vector<ast::TypeParamDecl*>{ yystack_[0].value.as < ast::TypeParamDecl* > () }; }
#line 2039 "parser/parser.cpp"
    break;

  case 22: // type_param_list: type_param_list TOK_COMMA type_param
#line 447 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ().push_back(yystack_[0].value.as < ast::TypeParamDecl* > ()); yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 2045 "parser/parser.cpp"
    break;

  case 23: // type_param_list: type_param_list TOK_COMMA
#line 449 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TypeParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeParamDecl*> > ()); }
#line 2051 "parser/parser.cpp"
    break;

  case 24: // type_param: ident_no_self
#line 454 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeParamDecl* > () = ast.mk_type_param_decl(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 2057 "parser/parser.cpp"
    break;

  case 25: // type_args: %empty
#line 459 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{}; }
#line 2063 "parser/parser.cpp"
    break;

  case 26: // type_args: TOK_TURBOFISH_S type_arg_list TOK_GREATER
#line 461 "parser/parser_rules.y"
        { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 2069 "parser/parser.cpp"
    break;

  case 27: // type_arg_list: type_expr
#line 466 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::vector<ast::TypeExpr*>{ yystack_[0].value.as < ast::TypeExpr* > () }; }
#line 2075 "parser/parser.cpp"
    break;

  case 28: // type_arg_list: type_arg_list TOK_COMMA type_expr
#line 468 "parser/parser_rules.y"
      { yystack_[2].value.as < std::vector<ast::TypeExpr*> > ().push_back(yystack_[0].value.as < ast::TypeExpr* > ()); yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 2081 "parser/parser.cpp"
    break;

  case 29: // type_arg_list: type_arg_list TOK_COMMA
#line 470 "parser/parser_rules.y"
      { yylhs.value.as < std::vector<ast::TypeExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::TypeExpr*> > ()); }
#line 2087 "parser/parser.cpp"
    break;

  case 30: // pub_opt: %empty
#line 479 "parser/parser_rules.y"
           { yylhs.value.as < kl::rt::boolean > () = false; }
#line 2093 "parser/parser.cpp"
    break;

  case 31: // pub_opt: TOK_PUB
#line 480 "parser/parser_rules.y"
                { yylhs.value.as < kl::rt::boolean > () = true;  }
#line 2099 "parser/parser.cpp"
    break;

  case 32: // decl_list_opt: %empty
#line 485 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{}; }
#line 2105 "parser/parser.cpp"
    break;

  case 33: // decl_list_opt: decl_list
#line 487 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[0].value.as < std::vector<ast::Decl*> > ()); }
#line 2111 "parser/parser.cpp"
    break;

  case 34: // decl_list: decl
#line 492 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Decl*> > () = std::vector<ast::Decl*>{ yystack_[0].value.as < ast::Decl* > () }; }
#line 2117 "parser/parser.cpp"
    break;

  case 35: // decl_list: decl_list decl
#line 494 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Decl*> > ().push_back(yystack_[0].value.as < ast::Decl* > ()); yylhs.value.as < std::vector<ast::Decl*> > () = std::move(yystack_[1].value.as < std::vector<ast::Decl*> > ()); }
#line 2123 "parser/parser.cpp"
    break;

  case 36: // decl: fn_decl
#line 499 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::FnDecl* > ()); }
#line 2129 "parser/parser.cpp"
    break;

  case 37: // decl: load_fn_decl
#line 501 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::LoadFnDecl* > ()); }
#line 2135 "parser/parser.cpp"
    break;

  case 38: // decl: struct_decl
#line 503 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::StructDecl* > ()); }
#line 2141 "parser/parser.cpp"
    break;

  case 39: // decl: trait_decl
#line 505 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::Decl* > ()); }
#line 2147 "parser/parser.cpp"
    break;

  case 40: // decl: impl_decl
#line 507 "parser/parser_rules.y"
    { yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(yystack_[0].value.as < ast::Decl* > ()); }
#line 2153 "parser/parser.cpp"
    break;

  case 41: // fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
#line 512 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_FN */
      yylhs.value.as < ast::FnDecl* > () = ast.mk_fn_decl(yystack_[6].value.as < Str > (), std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 2162 "parser/parser.cpp"
    break;

  case 42: // load_fn_decl: pub_opt TOK_LOAD TOK_FN ident_no_self TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 520 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_LOAD */
      yylhs.value.as < ast::LoadFnDecl* > () = ast.mk_load_fn_decl(yystack_[5].value.as < Str > (), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 2171 "parser/parser.cpp"
    break;

  case 43: // impl_fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
#line 528 "parser/parser_rules.y"
    {
      auto start = yystack_[8].value.as < kl::rt::boolean > () ? yystack_[8].location : yystack_[7].location; /* TOK_PUB if present else TOK_FN */
      yylhs.value.as < ast::ImplFnDecl* > () = ast.mk_impl_fn_decl(yystack_[6].value.as < Str > (), std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()), std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()), yystack_[1].value.as < ast::TypeExpr* > (), yystack_[0].value.as < ast::BlockStatement* > (), yystack_[8].value.as < kl::rt::boolean > (), combine(start, yystack_[0].location));
    }
#line 2180 "parser/parser.cpp"
    break;

  case 44: // trait_fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
#line 537 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::TraitFnDecl* > () = ast.mk_trait_fn_decl(
            yystack_[6].value.as < Str > (),                 /* name */
            std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()),      /* type params */
            std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()),      /* params */
            yystack_[1].value.as < ast::TypeExpr* > (),                 /* ret */
            nullptr,            /* body absent */
            yystack_[8].value.as < kl::rt::boolean > (),
            combine(yystack_[8].location, yystack_[0].location)     /* include semicolon */
          );
    }
#line 2196 "parser/parser.cpp"
    break;

  case 45: // trait_fn_decl: pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
#line 549 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::TraitFnDecl* > () = ast.mk_trait_fn_decl(
            yystack_[6].value.as < Str > (),                 /* name */
            std::move(yystack_[5].value.as < std::vector<ast::TypeParamDecl*> > ()),      /* type params */
            std::move(yystack_[3].value.as < std::vector<ast::ParamDecl*> > ()),      /* params */
            yystack_[1].value.as < ast::TypeExpr* > (),                 /* ret */
            yystack_[0].value.as < ast::BlockStatement* > (),                 /* body present */
            yystack_[8].value.as < kl::rt::boolean > (),
            combine(yystack_[8].location, yystack_[0].location)
          );
    }
#line 2212 "parser/parser.cpp"
    break;

  case 46: // struct_decl: struct_decl_def
#line 566 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2218 "parser/parser.cpp"
    break;

  case 47: // struct_decl: struct_decl_fwd
#line 568 "parser/parser_rules.y"
    { yylhs.value.as < ast::StructDecl* > () = yystack_[0].value.as < ast::StructDecl* > (); }
#line 2224 "parser/parser.cpp"
    break;

  case 48: // struct_decl_def: pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_LCBRA field_decl_list_opt TOK_RCBRA
#line 573 "parser/parser_rules.y"
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
#line 2239 "parser/parser.cpp"
    break;

  case 49: // array_elems_opt: %empty
#line 587 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 2245 "parser/parser.cpp"
    break;

  case 50: // array_elems_opt: array_elems
#line 589 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 2251 "parser/parser.cpp"
    break;

  case 51: // array_elems: expr
#line 594 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 2257 "parser/parser.cpp"
    break;

  case 52: // array_elems: array_elems TOK_COMMA expr
#line 596 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 2263 "parser/parser.cpp"
    break;

  case 53: // array_elems: array_elems TOK_COMMA
#line 598 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 2269 "parser/parser.cpp"
    break;

  case 54: // struct_decl_fwd: pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_SMCLN
#line 603 "parser/parser_rules.y"
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
#line 2284 "parser/parser.cpp"
    break;

  case 55: // field_decl_list_opt: %empty
#line 618 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{}; }
#line 2290 "parser/parser.cpp"
    break;

  case 56: // field_decl_list_opt: field_decl_list
#line 620 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2296 "parser/parser.cpp"
    break;

  case 57: // field_decl_list: field_decl
#line 625 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::vector<ast::FieldDecl*>{ yystack_[0].value.as < ast::FieldDecl* > () }; }
#line 2302 "parser/parser.cpp"
    break;

  case 58: // field_decl_list: field_decl_list field_decl
#line 627 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::FieldDecl*> > ().push_back(yystack_[0].value.as < ast::FieldDecl* > ()); yylhs.value.as < std::vector<ast::FieldDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldDecl*> > ()); }
#line 2308 "parser/parser.cpp"
    break;

  case 59: // field_decl: ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 632 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Priv, combine(yystack_[3].location, yystack_[0].location)); }
#line 2314 "parser/parser.cpp"
    break;

  case 60: // field_decl: TOK_PUB ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 634 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldDecl* > () = ast.mk_field_decl(yystack_[3].value.as < Str > (), yystack_[1].value.as < ast::TypeExpr* > (), ast::Visibility::Publ, combine(yystack_[4].location, yystack_[0].location)); }
#line 2320 "parser/parser.cpp"
    break;

  case 61: // trait_decl: pub_opt TOK_TRAIT ident_no_self type_params_opt TOK_LCBRA trait_item_list_opt TOK_RCBRA
#line 639 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Decl* > () = ast.mk_trait_decl(
        yystack_[4].value.as < Str > (),                 /* name */
        std::move(yystack_[3].value.as < std::vector<ast::TypeParamDecl*> > ()),      /* tparams: vector<TypeParamDecl*> */
        std::move(yystack_[1].value.as < std::vector<ast::TraitFnDecl*> > ()),      /* methods: vector<FunctionDecl*> */
        /*exported=*/yystack_[6].value.as < kl::rt::boolean > (),
        combine(yystack_[6].location, yystack_[0].location)
      );
    }
#line 2334 "parser/parser.cpp"
    break;

  case 62: // trait_item_list_opt: %empty
#line 652 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TraitFnDecl*> > () = std::vector<ast::TraitFnDecl*>{}; }
#line 2340 "parser/parser.cpp"
    break;

  case 63: // trait_item_list_opt: trait_item_list
#line 654 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TraitFnDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::TraitFnDecl*> > ()); }
#line 2346 "parser/parser.cpp"
    break;

  case 64: // trait_item_list: trait_item
#line 659 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::TraitFnDecl*> > () = std::vector<ast::TraitFnDecl*>{ yystack_[0].value.as < ast::TraitFnDecl* > () }; }
#line 2352 "parser/parser.cpp"
    break;

  case 65: // trait_item_list: trait_item_list trait_item
#line 661 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::TraitFnDecl*> > ().push_back(yystack_[0].value.as < ast::TraitFnDecl* > ()); yylhs.value.as < std::vector<ast::TraitFnDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::TraitFnDecl*> > ()); }
#line 2358 "parser/parser.cpp"
    break;

  case 66: // trait_item: trait_fn_decl
#line 666 "parser/parser_rules.y"
    { yylhs.value.as < ast::TraitFnDecl* > () = yystack_[0].value.as < ast::TraitFnDecl* > (); }
#line 2364 "parser/parser.cpp"
    break;

  case 67: // impl_decl: TOK_IMPL type_params_opt type_expr TOK_FOR type_expr TOK_LCBRA impl_item_list_opt TOK_RCBRA
#line 672 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(
        ast.mk_impl_decl(
          std::move(yystack_[6].value.as < std::vector<ast::TypeParamDecl*> > ()),   // tparams
          yystack_[5].value.as < ast::TypeExpr* > (),              // traitType (TypeExpr*)
          yystack_[3].value.as < ast::TypeExpr* > (),              // selfType  (TypeExpr*)
          std::move(yystack_[1].value.as < std::vector<ast::ImplFnDecl*> > ()),   // methods   (vector<FunctionDecl*>)
          combine(yystack_[7].location, yystack_[0].location)
        )
      );
    }
#line 2380 "parser/parser.cpp"
    break;

  case 68: // impl_decl: TOK_IMPL type_params_opt type_expr TOK_LCBRA impl_item_list_opt TOK_RCBRA
#line 684 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Decl* > () = static_cast<ast::Decl*>(
        ast.mk_impl_decl(
          std::move(yystack_[4].value.as < std::vector<ast::TypeParamDecl*> > ()),   // tparams
          nullptr,         // traitType absent => inherent impl
          yystack_[3].value.as < ast::TypeExpr* > (),              // selfType
          std::move(yystack_[1].value.as < std::vector<ast::ImplFnDecl*> > ()),   // methods
          combine(yystack_[5].location, yystack_[0].location)
        )
      );
    }
#line 2396 "parser/parser.cpp"
    break;

  case 69: // impl_item_list_opt: %empty
#line 699 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImplFnDecl*> > () = std::vector<ast::ImplFnDecl*>{}; }
#line 2402 "parser/parser.cpp"
    break;

  case 70: // impl_item_list_opt: impl_item_list
#line 701 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImplFnDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ImplFnDecl*> > ()); }
#line 2408 "parser/parser.cpp"
    break;

  case 71: // impl_item_list: impl_item
#line 706 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ImplFnDecl*> > () = std::vector<ast::ImplFnDecl*>{ yystack_[0].value.as < ast::ImplFnDecl* > () }; }
#line 2414 "parser/parser.cpp"
    break;

  case 72: // impl_item_list: impl_item_list impl_item
#line 708 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ImplFnDecl*> > ().push_back(yystack_[0].value.as < ast::ImplFnDecl* > ()); yylhs.value.as < std::vector<ast::ImplFnDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ImplFnDecl*> > ()); }
#line 2420 "parser/parser.cpp"
    break;

  case 73: // impl_item: impl_fn_decl
#line 713 "parser/parser_rules.y"
    { yylhs.value.as < ast::ImplFnDecl* > () = yystack_[0].value.as < ast::ImplFnDecl* > (); }
#line 2426 "parser/parser.cpp"
    break;

  case 74: // ret_type_expr: TOK_ARROW type_expr
#line 719 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2432 "parser/parser.cpp"
    break;

  case 75: // param_list_opt: %empty
#line 724 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{}; }
#line 2438 "parser/parser.cpp"
    break;

  case 76: // param_list_opt: param_list
#line 726 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[0].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2444 "parser/parser.cpp"
    break;

  case 77: // param_list: param
#line 731 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::vector<ast::ParamDecl*>{ yystack_[0].value.as < ast::ParamDecl* > () }; }
#line 2450 "parser/parser.cpp"
    break;

  case 78: // param_list: param_list TOK_COMMA param
#line 733 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::ParamDecl*> > ().push_back(yystack_[0].value.as < ast::ParamDecl* > ()); yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[2].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2456 "parser/parser.cpp"
    break;

  case 79: // param_list: param_list TOK_COMMA
#line 735 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ParamDecl*> > () = std::move(yystack_[1].value.as < std::vector<ast::ParamDecl*> > ()); }
#line 2462 "parser/parser.cpp"
    break;

  case 80: // param: self_param
#line 740 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = yystack_[0].value.as < ast::ParamDecl* > (); }
#line 2468 "parser/parser.cpp"
    break;

  case 81: // param: ident_no_self TOK_COLON type_expr
#line 742 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_param_decl(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::TypeExpr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2474 "parser/parser.cpp"
    break;

  case 82: // self_param: TOK_SELF
#line 748 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_self_param_decl(yystack_[0].value.as < Str > (), ast::SelfParamKind::Value, yystack_[0].location); }
#line 2480 "parser/parser.cpp"
    break;

  case 83: // self_param: TOK_AMP TOK_SELF
#line 750 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_self_param_decl(yystack_[0].value.as < Str > (), ast::SelfParamKind::Ref, combine(yystack_[1].location, yystack_[0].location)); }
#line 2486 "parser/parser.cpp"
    break;

  case 84: // self_param: TOK_AMP TOK_MUT TOK_SELF
#line 752 "parser/parser_rules.y"
    { yylhs.value.as < ast::ParamDecl* > () = ast.mk_self_param_decl(yystack_[0].value.as < Str > (), ast::SelfParamKind::RefMut, combine(yystack_[2].location, yystack_[0].location)); }
#line 2492 "parser/parser.cpp"
    break;

  case 85: // type_expr: ref_type_expr
#line 764 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::RefTypeExpr* > ()); }
#line 2498 "parser/parser.cpp"
    break;

  case 86: // type_expr: type_postfix
#line 766 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2504 "parser/parser.cpp"
    break;

  case 87: // ref_type_expr: TOK_AMP ref_mutability type_postfix
#line 771 "parser/parser_rules.y"
    { yylhs.value.as < ast::RefTypeExpr* > () = ast.mk_ref_type_expr(yystack_[0].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Mutability > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2510 "parser/parser.cpp"
    break;

  case 88: // ref_mutability: %empty
#line 775 "parser/parser_rules.y"
           { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2516 "parser/parser.cpp"
    break;

  case 89: // ref_mutability: TOK_IMM
#line 776 "parser/parser_rules.y"
                { yylhs.value.as < ast::Mutability > () = ast::Mutability::Imm; }
#line 2522 "parser/parser.cpp"
    break;

  case 90: // ref_mutability: TOK_MUT
#line 777 "parser/parser_rules.y"
                { yylhs.value.as < ast::Mutability > () = ast::Mutability::Mut; }
#line 2528 "parser/parser.cpp"
    break;

  case 91: // type_postfix: type_primary
#line 782 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[0].value.as < ast::TypeExpr* > (); }
#line 2534 "parser/parser.cpp"
    break;

  case 92: // type_postfix: type_postfix TOK_LBRACK expr TOK_RBRACK
#line 784 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr(yystack_[3].value.as < ast::TypeExpr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location))); }
#line 2540 "parser/parser.cpp"
    break;

  case 93: // type_primary: builtin_type_expr
#line 789 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::BuiltinTypeExpr* > ()); }
#line 2546 "parser/parser.cpp"
    break;

  case 94: // type_primary: path_type_expr
#line 791 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = static_cast<ast::TypeExpr*>(yystack_[0].value.as < ast::PathTypeExpr* > ()); }
#line 2552 "parser/parser.cpp"
    break;

  case 95: // type_primary: TOK_LPAR type_expr TOK_RPAR
#line 793 "parser/parser_rules.y"
    { yylhs.value.as < ast::TypeExpr* > () = yystack_[1].value.as < ast::TypeExpr* > (); }
#line 2558 "parser/parser.cpp"
    break;

  case 96: // builtin_type_expr: TOK_I8
#line 797 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   yystack_[0].location); }
#line 2564 "parser/parser.cpp"
    break;

  case 97: // builtin_type_expr: TOK_U8
#line 798 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   yystack_[0].location); }
#line 2570 "parser/parser.cpp"
    break;

  case 98: // builtin_type_expr: TOK_I16
#line 799 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  yystack_[0].location); }
#line 2576 "parser/parser.cpp"
    break;

  case 99: // builtin_type_expr: TOK_U16
#line 800 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  yystack_[0].location); }
#line 2582 "parser/parser.cpp"
    break;

  case 100: // builtin_type_expr: TOK_I32
#line 801 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  yystack_[0].location); }
#line 2588 "parser/parser.cpp"
    break;

  case 101: // builtin_type_expr: TOK_U32
#line 802 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  yystack_[0].location); }
#line 2594 "parser/parser.cpp"
    break;

  case 102: // builtin_type_expr: TOK_I64
#line 803 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  yystack_[0].location); }
#line 2600 "parser/parser.cpp"
    break;

  case 103: // builtin_type_expr: TOK_U64
#line 804 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  yystack_[0].location); }
#line 2606 "parser/parser.cpp"
    break;

  case 104: // builtin_type_expr: TOK_I128
#line 805 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, yystack_[0].location); }
#line 2612 "parser/parser.cpp"
    break;

  case 105: // builtin_type_expr: TOK_U128
#line 806 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, yystack_[0].location); }
#line 2618 "parser/parser.cpp"
    break;

  case 106: // builtin_type_expr: TOK_F32
#line 807 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  yystack_[0].location); }
#line 2624 "parser/parser.cpp"
    break;

  case 107: // builtin_type_expr: TOK_F64
#line 808 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  yystack_[0].location); }
#line 2630 "parser/parser.cpp"
    break;

  case 108: // builtin_type_expr: TOK_BOOL
#line 809 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, yystack_[0].location); }
#line 2636 "parser/parser.cpp"
    break;

  case 109: // builtin_type_expr: TOK_CHAR
#line 810 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, yystack_[0].location); }
#line 2642 "parser/parser.cpp"
    break;

  case 110: // builtin_type_expr: TOK_VOID
#line 811 "parser/parser_rules.y"
              { yylhs.value.as < ast::BuiltinTypeExpr* > () = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Void, yystack_[0].location); }
#line 2648 "parser/parser.cpp"
    break;

  case 111: // path_type_expr: path_expr type_args
#line 816 "parser/parser_rules.y"
    { yylhs.value.as < ast::PathTypeExpr* > () = ast.mk_path_type_expr(yystack_[1].value.as < ast::PathExpr* > (), std::move(yystack_[0].value.as < std::vector<ast::TypeExpr*> > ()), combine(yystack_[1].location, yystack_[0].location)); }
#line 2654 "parser/parser.cpp"
    break;

  case 112: // anon_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 825 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Anon, combine(yystack_[2].location, yystack_[0].location)); }
#line 2660 "parser/parser.cpp"
    break;

  case 113: // fn_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 830 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Fn, combine(yystack_[2].location, yystack_[0].location)); }
#line 2666 "parser/parser.cpp"
    break;

  case 114: // if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 835 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::If, combine(yystack_[2].location, yystack_[0].location)); }
#line 2672 "parser/parser.cpp"
    break;

  case 115: // else_if_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 840 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::ElseIf, combine(yystack_[2].location, yystack_[0].location)); }
#line 2678 "parser/parser.cpp"
    break;

  case 116: // else_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 845 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::Else, combine(yystack_[2].location, yystack_[0].location)); }
#line 2684 "parser/parser.cpp"
    break;

  case 117: // while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 850 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::While, combine(yystack_[2].location, yystack_[0].location)); }
#line 2690 "parser/parser.cpp"
    break;

  case 118: // do_while_block: TOK_LCBRA stmt_list_opt TOK_RCBRA
#line 855 "parser/parser_rules.y"
      { yylhs.value.as < ast::BlockStatement* > () = ast.mk_block_stmt(std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()), ast::BlockKind::DoWhile, combine(yystack_[2].location, yystack_[0].location)); }
#line 2696 "parser/parser.cpp"
    break;

  case 119: // stmt_list_opt: %empty
#line 860 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{}; }
#line 2702 "parser/parser.cpp"
    break;

  case 120: // stmt_list_opt: stmt_list
#line 862 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[0].value.as < std::vector<ast::Statement*> > ()); }
#line 2708 "parser/parser.cpp"
    break;

  case 121: // stmt_list: stmt
#line 867 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Statement*> > () = std::vector<ast::Statement*>{ yystack_[0].value.as < ast::Statement* > () }; }
#line 2714 "parser/parser.cpp"
    break;

  case 122: // stmt_list: stmt_list stmt
#line 869 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::Statement*> > ().push_back(yystack_[0].value.as < ast::Statement* > ()); yylhs.value.as < std::vector<ast::Statement*> > () = std::move(yystack_[1].value.as < std::vector<ast::Statement*> > ()); }
#line 2720 "parser/parser.cpp"
    break;

  case 123: // stmt: simple_stmt
#line 874 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2726 "parser/parser.cpp"
    break;

  case 124: // stmt: compound_stmt
#line 876 "parser/parser_rules.y"
    { yylhs.value.as < ast::Statement* > () = yystack_[0].value.as < ast::Statement* > (); }
#line 2732 "parser/parser.cpp"
    break;

  case 125: // simple_stmt: var_stmt
#line 880 "parser/parser_rules.y"
                  { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::VarStmt* > ()); }
#line 2738 "parser/parser.cpp"
    break;

  case 126: // simple_stmt: return_stmt
#line 881 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ReturnStatement* > ()); }
#line 2744 "parser/parser.cpp"
    break;

  case 127: // simple_stmt: break_stmt
#line 882 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BreakStatement* > ()); }
#line 2750 "parser/parser.cpp"
    break;

  case 128: // simple_stmt: continue_stmt
#line 883 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ContinueStatement* > ()); }
#line 2756 "parser/parser.cpp"
    break;

  case 129: // simple_stmt: expr_stmt
#line 884 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::ExprStatement* > ()); }
#line 2762 "parser/parser.cpp"
    break;

  case 130: // compound_stmt: anon_block
#line 888 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::BlockStatement* > ()); }
#line 2768 "parser/parser.cpp"
    break;

  case 131: // compound_stmt: if_stmt
#line 889 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::IfStatement* > ()); }
#line 2774 "parser/parser.cpp"
    break;

  case 132: // compound_stmt: while_stmt
#line 890 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::WhileStatement* > ()); }
#line 2780 "parser/parser.cpp"
    break;

  case 133: // compound_stmt: do_while_stmt
#line 891 "parser/parser_rules.y"
                   { yylhs.value.as < ast::Statement* > () = static_cast<ast::Statement*>(yystack_[0].value.as < ast::DoWhileStatement* > ()); }
#line 2786 "parser/parser.cpp"
    break;

  case 134: // return_stmt: TOK_RETURN expr_opt TOK_SMCLN
#line 896 "parser/parser_rules.y"
    { yylhs.value.as < ast::ReturnStatement* > () = ast.mk_return_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 2792 "parser/parser.cpp"
    break;

  case 135: // if_stmt: TOK_IF TOK_LPAR expr TOK_RPAR if_block elseif_list else_part
#line 901 "parser/parser_rules.y"
    { yylhs.value.as < ast::IfStatement* > () = ast.mk_if_stmt(yystack_[4].value.as < ast::Expr* > (), yystack_[2].value.as < ast::BlockStatement* > (), std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()), yystack_[0].value.as < ast::ElseStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2798 "parser/parser.cpp"
    break;

  case 136: // elseif_list: %empty
#line 906 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::vector<ast::ElseIfStatement*>{}; }
#line 2804 "parser/parser.cpp"
    break;

  case 137: // elseif_list: elseif_list elseif
#line 908 "parser/parser_rules.y"
    { yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ().push_back(yystack_[0].value.as < ast::ElseIfStatement* > ()); yylhs.value.as < std::vector<ast::ElseIfStatement*> > () = std::move(yystack_[1].value.as < std::vector<ast::ElseIfStatement*> > ()); }
#line 2810 "parser/parser.cpp"
    break;

  case 138: // elseif: TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR else_if_block
#line 913 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseIfStatement* > () = ast.mk_else_if_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[5].location, yystack_[0].location)); }
#line 2816 "parser/parser.cpp"
    break;

  case 139: // else_part: %empty
#line 918 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = nullptr; }
#line 2822 "parser/parser.cpp"
    break;

  case 140: // else_part: TOK_ELSE else_block
#line 920 "parser/parser_rules.y"
    { yylhs.value.as < ast::ElseStatement* > () = ast.mk_else_stmt(yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2828 "parser/parser.cpp"
    break;

  case 141: // while_stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR while_block
#line 925 "parser/parser_rules.y"
    { yylhs.value.as < ast::WhileStatement* > () = ast.mk_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::BlockStatement* > (), combine(yystack_[4].location, yystack_[0].location)); }
#line 2834 "parser/parser.cpp"
    break;

  case 142: // do_while_stmt: TOK_DO do_while_block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
#line 930 "parser/parser_rules.y"
    { yylhs.value.as < ast::DoWhileStatement* > () = ast.mk_do_while_stmt(yystack_[2].value.as < ast::Expr* > (), yystack_[5].value.as < ast::BlockStatement* > (), combine(yystack_[6].location, yystack_[0].location)); }
#line 2840 "parser/parser.cpp"
    break;

  case 143: // break_stmt: TOK_BREAK TOK_SMCLN
#line 935 "parser/parser_rules.y"
    { yylhs.value.as < ast::BreakStatement* > () = ast.mk_break_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2846 "parser/parser.cpp"
    break;

  case 144: // continue_stmt: TOK_CONTINUE TOK_SMCLN
#line 940 "parser/parser_rules.y"
    { yylhs.value.as < ast::ContinueStatement* > () = ast.mk_continue_stmt(combine(yystack_[1].location, yystack_[0].location)); }
#line 2852 "parser/parser.cpp"
    break;

  case 145: // expr_stmt: expr TOK_SMCLN
#line 945 "parser/parser_rules.y"
    { yylhs.value.as < ast::ExprStatement* > () = ast.mk_expr_stmt(yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 2858 "parser/parser.cpp"
    break;

  case 146: // var_stmt: var_stmt_default
#line 965 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2864 "parser/parser.cpp"
    break;

  case 147: // var_stmt: var_stmt_imm
#line 966 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2870 "parser/parser.cpp"
    break;

  case 148: // var_stmt: var_stmt_mut
#line 967 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2876 "parser/parser.cpp"
    break;

  case 149: // var_stmt: var_stmt_static_default
#line 968 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2882 "parser/parser.cpp"
    break;

  case 150: // var_stmt: var_stmt_static_imm
#line 969 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2888 "parser/parser.cpp"
    break;

  case 151: // var_stmt: var_stmt_static_mut
#line 970 "parser/parser_rules.y"
                            { yylhs.value.as < ast::VarStmt* > () = yystack_[0].value.as < ast::VarStmt* > (); }
#line 2894 "parser/parser.cpp"
    break;

  case 152: // var_stmt_default: ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 979 "parser/parser_rules.y"
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
#line 2909 "parser/parser.cpp"
    break;

  case 153: // var_stmt_default: ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 990 "parser/parser_rules.y"
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
#line 2924 "parser/parser.cpp"
    break;

  case 154: // var_stmt_imm: TOK_IMM ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 1004 "parser/parser_rules.y"
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
#line 2939 "parser/parser.cpp"
    break;

  case 155: // var_stmt_imm: TOK_IMM ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 1015 "parser/parser_rules.y"
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
#line 2954 "parser/parser.cpp"
    break;

  case 156: // var_stmt_mut: TOK_MUT ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 1029 "parser/parser_rules.y"
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
#line 2969 "parser/parser.cpp"
    break;

  case 157: // var_stmt_mut: TOK_MUT ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 1040 "parser/parser_rules.y"
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
#line 2984 "parser/parser.cpp"
    break;

  case 158: // var_stmt_static_default: TOK_STATIC ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 1058 "parser/parser_rules.y"
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
#line 2999 "parser/parser.cpp"
    break;

  case 159: // var_stmt_static_default: TOK_STATIC ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 1069 "parser/parser_rules.y"
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
#line 3014 "parser/parser.cpp"
    break;

  case 160: // var_stmt_static_imm: TOK_STATIC TOK_IMM ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 1083 "parser/parser_rules.y"
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
#line 3029 "parser/parser.cpp"
    break;

  case 161: // var_stmt_static_imm: TOK_STATIC TOK_IMM ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 1094 "parser/parser_rules.y"
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
#line 3044 "parser/parser.cpp"
    break;

  case 162: // var_stmt_static_mut: TOK_STATIC TOK_MUT ident_no_self TOK_COLON type_expr TOK_SMCLN
#line 1108 "parser/parser_rules.y"
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
#line 3059 "parser/parser.cpp"
    break;

  case 163: // var_stmt_static_mut: TOK_STATIC TOK_MUT ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
#line 1119 "parser/parser_rules.y"
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
#line 3074 "parser/parser.cpp"
    break;

  case 164: // expr: assign
#line 1138 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3080 "parser/parser.cpp"
    break;

  case 165: // expr_opt: %empty
#line 1142 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = nullptr; }
#line 3086 "parser/parser.cpp"
    break;

  case 166: // expr_opt: expr
#line 1143 "parser/parser_rules.y"
           { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3092 "parser/parser.cpp"
    break;

  case 167: // assign: cond
#line 1148 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3098 "parser/parser.cpp"
    break;

  case 168: // assign: unary TOK_ASSIGN assign
#line 1150 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Assign,   combine(yystack_[2].location, yystack_[0].location)); }
#line 3104 "parser/parser.cpp"
    break;

  case 169: // assign: unary TOK_PLUS_ASSIGN assign
#line 1152 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Add,      combine(yystack_[2].location, yystack_[0].location)); }
#line 3110 "parser/parser.cpp"
    break;

  case 170: // assign: unary TOK_MIN_ASSIGN assign
#line 1154 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Subtract, combine(yystack_[2].location, yystack_[0].location)); }
#line 3116 "parser/parser.cpp"
    break;

  case 171: // assign: unary TOK_MUL_ASSIGN assign
#line 1156 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Multiply, combine(yystack_[2].location, yystack_[0].location)); }
#line 3122 "parser/parser.cpp"
    break;

  case 172: // assign: unary TOK_DIV_ASSIGN assign
#line 1158 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_assign_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), ast::AssignOp::Divide,   combine(yystack_[2].location, yystack_[0].location)); }
#line 3128 "parser/parser.cpp"
    break;

  case 173: // cond: logic_or
#line 1162 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3134 "parser/parser.cpp"
    break;

  case 174: // logic_or: logic_and
#line 1167 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3140 "parser/parser.cpp"
    break;

  case 175: // logic_or: logic_or TOK_BOOL_OR logic_and
#line 1169 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_or, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3146 "parser/parser.cpp"
    break;

  case 176: // logic_and: equality
#line 1174 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3152 "parser/parser.cpp"
    break;

  case 177: // logic_and: logic_and TOK_BOOL_AND equality
#line 1176 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3158 "parser/parser.cpp"
    break;

  case 178: // equality: relational
#line 1181 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3164 "parser/parser.cpp"
    break;

  case 179: // equality: equality TOK_EQUAL relational
#line 1183 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::equal,     yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3170 "parser/parser.cpp"
    break;

  case 180: // equality: equality TOK_NEQUAL relational
#line 1185 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3176 "parser/parser.cpp"
    break;

  case 181: // relational: additive
#line 1190 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3182 "parser/parser.cpp"
    break;

  case 182: // relational: relational TOK_LESS additive
#line 1192 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less,          yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3188 "parser/parser.cpp"
    break;

  case 183: // relational: relational TOK_LEQ additive
#line 1194 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::less_equal,    yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3194 "parser/parser.cpp"
    break;

  case 184: // relational: relational TOK_GREATER additive
#line 1196 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater,       yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3200 "parser/parser.cpp"
    break;

  case 185: // relational: relational TOK_GEQ additive
#line 1198 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3206 "parser/parser.cpp"
    break;

  case 186: // additive: multiplicative
#line 1203 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3212 "parser/parser.cpp"
    break;

  case 187: // additive: additive TOK_PLUS multiplicative
#line 1205 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::add,      yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3218 "parser/parser.cpp"
    break;

  case 188: // additive: additive TOK_MINUS multiplicative
#line 1207 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::subtract, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3224 "parser/parser.cpp"
    break;

  case 189: // multiplicative: unary
#line 1212 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3230 "parser/parser.cpp"
    break;

  case 190: // multiplicative: multiplicative TOK_STAR unary
#line 1214 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::multiply, yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3236 "parser/parser.cpp"
    break;

  case 191: // multiplicative: multiplicative TOK_SLASH unary
#line 1216 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::divide,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3242 "parser/parser.cpp"
    break;

  case 192: // multiplicative: multiplicative TOK_MODULO unary
#line 1218 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_binary_op_expr(ast::BinaryOp::modulo,   yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3248 "parser/parser.cpp"
    break;

  case 193: // unary: TOK_MINUS unary
#line 1223 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::negation,     yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3254 "parser/parser.cpp"
    break;

  case 194: // unary: TOK_NEGATION unary
#line 1225 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::logical_not,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3260 "parser/parser.cpp"
    break;

  case 195: // unary: TOK_INC unary
#line 1227 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3266 "parser/parser.cpp"
    break;

  case 196: // unary: TOK_DEC unary
#line 1229 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3272 "parser/parser.cpp"
    break;

  case 197: // unary: TOK_STAR unary
#line 1231 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::deref,        yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3278 "parser/parser.cpp"
    break;

  case 198: // unary: TOK_AMP unary
#line 1233 "parser/parser_rules.y"
      { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::addr_of,      yystack_[0].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3284 "parser/parser.cpp"
    break;

  case 199: // unary: TOK_AMP TOK_MUT unary
#line 1235 "parser/parser_rules.y"
      { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::addr_of_mut,  yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3290 "parser/parser.cpp"
    break;

  case 200: // unary: postfix
#line 1237 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3296 "parser/parser.cpp"
    break;

  case 201: // postfix: primary
#line 1242 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[0].value.as < ast::Expr* > (); }
#line 3302 "parser/parser.cpp"
    break;

  case 202: // postfix: postfix type_args TOK_LPAR arg_list_opt TOK_RPAR
#line 1244 "parser/parser_rules.y"
    {
      yylhs.value.as < ast::Expr* > () = ast.mk_call_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[4].location, yystack_[0].location));
    }
#line 3310 "parser/parser.cpp"
    break;

  case 203: // postfix: postfix TOK_LBRACK expr TOK_RBRACK
#line 1248 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_index(yystack_[3].value.as < ast::Expr* > (), yystack_[1].value.as < ast::Expr* > (), combine(yystack_[3].location, yystack_[0].location)); }
#line 3316 "parser/parser.cpp"
    break;

  case 204: // postfix: postfix TOK_DOT ident_no_self
#line 1250 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_field_expr(yystack_[2].value.as < ast::Expr* > (), yystack_[0].value.as < Str > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3322 "parser/parser.cpp"
    break;

  case 205: // postfix: postfix TOK_INC
#line 1252 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3328 "parser/parser.cpp"
    break;

  case 206: // postfix: postfix TOK_DEC
#line 1254 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, yystack_[1].value.as < ast::Expr* > (), combine(yystack_[1].location, yystack_[0].location)); }
#line 3334 "parser/parser.cpp"
    break;

  case 207: // postfix: postfix type_args TOK_LCBRA field_inits_opt TOK_RCBRA
#line 1256 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_struct_literal_expr(yystack_[4].value.as < ast::Expr* > (), std::move(yystack_[3].value.as < std::vector<ast::TypeExpr*> > ()), std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()), combine(yystack_[4].location, yystack_[1].location)); }
#line 3340 "parser/parser.cpp"
    break;

  case 208: // postfix: TOK_LBRACK array_elems_opt TOK_RBRACK
#line 1258 "parser/parser_rules.y"
      {
        yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(
               ast.mk_array_literal_expr(std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()), combine(yystack_[2].location, yystack_[0].location))
             );
      }
#line 3350 "parser/parser.cpp"
    break;

  case 209: // arg_list_opt: %empty
#line 1267 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{}; }
#line 3356 "parser/parser.cpp"
    break;

  case 210: // arg_list_opt: arg_list
#line 1269 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[0].value.as < std::vector<ast::Expr*> > ()); }
#line 3362 "parser/parser.cpp"
    break;

  case 211: // arg_list: expr
#line 1274 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::vector<ast::Expr*>{ yystack_[0].value.as < ast::Expr* > () }; }
#line 3368 "parser/parser.cpp"
    break;

  case 212: // arg_list: arg_list TOK_COMMA expr
#line 1276 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::Expr*> > ().push_back(yystack_[0].value.as < ast::Expr* > ()); yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[2].value.as < std::vector<ast::Expr*> > ()); }
#line 3374 "parser/parser.cpp"
    break;

  case 213: // arg_list: arg_list TOK_COMMA
#line 1278 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::Expr*> > () = std::move(yystack_[1].value.as < std::vector<ast::Expr*> > ()); }
#line 3380 "parser/parser.cpp"
    break;

  case 214: // int_literal_type_opt: %empty
#line 1286 "parser/parser_rules.y"
               { yylhs.value.as < std::optional<kl::rt::IntKind> > () = std::nullopt; }
#line 3386 "parser/parser.cpp"
    break;

  case 215: // int_literal_type_opt: TOK_AS TOK_I8
#line 1287 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I8; }
#line 3392 "parser/parser.cpp"
    break;

  case 216: // int_literal_type_opt: TOK_AS TOK_U8
#line 1288 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U8; }
#line 3398 "parser/parser.cpp"
    break;

  case 217: // int_literal_type_opt: TOK_AS TOK_I16
#line 1289 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I16; }
#line 3404 "parser/parser.cpp"
    break;

  case 218: // int_literal_type_opt: TOK_AS TOK_U16
#line 1290 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U16; }
#line 3410 "parser/parser.cpp"
    break;

  case 219: // int_literal_type_opt: TOK_AS TOK_I32
#line 1291 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I32; }
#line 3416 "parser/parser.cpp"
    break;

  case 220: // int_literal_type_opt: TOK_AS TOK_U32
#line 1292 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U32; }
#line 3422 "parser/parser.cpp"
    break;

  case 221: // int_literal_type_opt: TOK_AS TOK_I64
#line 1293 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I64; }
#line 3428 "parser/parser.cpp"
    break;

  case 222: // int_literal_type_opt: TOK_AS TOK_U64
#line 1294 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U64; }
#line 3434 "parser/parser.cpp"
    break;

  case 223: // int_literal_type_opt: TOK_AS TOK_I128
#line 1295 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::I128; }
#line 3440 "parser/parser.cpp"
    break;

  case 224: // int_literal_type_opt: TOK_AS TOK_U128
#line 1296 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::IntKind> > () = kl::rt::IntKind::U128; }
#line 3446 "parser/parser.cpp"
    break;

  case 225: // float_literal_type_opt: %empty
#line 1300 "parser/parser_rules.y"
               { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = std::nullopt; }
#line 3452 "parser/parser.cpp"
    break;

  case 226: // float_literal_type_opt: TOK_AS TOK_F32
#line 1301 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F32; }
#line 3458 "parser/parser.cpp"
    break;

  case 227: // float_literal_type_opt: TOK_AS TOK_F64
#line 1302 "parser/parser_rules.y"
                    { yylhs.value.as < std::optional<kl::rt::FloatKind> > () = kl::rt::FloatKind::F64; }
#line 3464 "parser/parser.cpp"
    break;

  case 228: // primary: ident_no_self
#line 1311 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_ref_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3470 "parser/parser.cpp"
    break;

  case 229: // primary: qpath_expr
#line 1313 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = static_cast<ast::Expr*>(yystack_[0].value.as < ast::PathExpr* > ()); }
#line 3476 "parser/parser.cpp"
    break;

  case 230: // primary: TOK_INT_LITERAL int_literal_type_opt
#line 1315 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_int_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::IntKind> > (), yystack_[1].location); }
#line 3482 "parser/parser.cpp"
    break;

  case 231: // primary: TOK_FLOAT_LITERAL float_literal_type_opt
#line 1317 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_float_literal_expr(yystack_[1].value.as < Str > (), yystack_[0].value.as < std::optional<kl::rt::FloatKind> > (), yystack_[1].location); }
#line 3488 "parser/parser.cpp"
    break;

  case 232: // primary: TOK_STRING_LITERAL
#line 1319 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_str_literal_expr(yystack_[0].value.as < Str > (), yystack_[0].location); }
#line 3494 "parser/parser.cpp"
    break;

  case 233: // primary: TOK_BOOL_LITERAL
#line 1321 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_bool_literal_expr(yystack_[0].value.as < kl::rt::boolean > (), yystack_[0].location); }
#line 3500 "parser/parser.cpp"
    break;

  case 234: // primary: TOK_CHAR_LITERAL
#line 1323 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = ast.mk_char_literal_expr(yystack_[0].value.as < kl::rt::character > (), yystack_[0].location); }
#line 3506 "parser/parser.cpp"
    break;

  case 235: // primary: TOK_LPAR expr TOK_RPAR
#line 1325 "parser/parser_rules.y"
    { yylhs.value.as < ast::Expr* > () = yystack_[1].value.as < ast::Expr* > (); }
#line 3512 "parser/parser.cpp"
    break;

  case 236: // field_inits_opt: %empty
#line 1330 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{}; }
#line 3518 "parser/parser.cpp"
    break;

  case 237: // field_inits_opt: field_inits
#line 1332 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[0].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3524 "parser/parser.cpp"
    break;

  case 238: // field_inits: field_init
#line 1337 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::vector<ast::FieldInitExpr*>{ yystack_[0].value.as < ast::FieldInitExpr* > () }; }
#line 3530 "parser/parser.cpp"
    break;

  case 239: // field_inits: field_inits TOK_COMMA field_init
#line 1339 "parser/parser_rules.y"
    { yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ().push_back(yystack_[0].value.as < ast::FieldInitExpr* > ()); yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[2].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3536 "parser/parser.cpp"
    break;

  case 240: // field_inits: field_inits TOK_COMMA
#line 1341 "parser/parser_rules.y"
    { yylhs.value.as < std::vector<ast::FieldInitExpr*> > () = std::move(yystack_[1].value.as < std::vector<ast::FieldInitExpr*> > ()); }
#line 3542 "parser/parser.cpp"
    break;

  case 241: // field_init: ident_no_self TOK_COLON expr
#line 1346 "parser/parser_rules.y"
    { yylhs.value.as < ast::FieldInitExpr* > () = ast.mk_field_init_expr(yystack_[2].value.as < Str > (), yystack_[0].value.as < ast::Expr* > (), combine(yystack_[2].location, yystack_[0].location)); }
#line 3548 "parser/parser.cpp"
    break;


#line 3552 "parser/parser.cpp"

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


  const short parser::yypact_ninf_ = -304;

  const signed char parser::yytable_ninf_ = -71;

  const short
  parser::yypact_[] =
  {
      13,    90,   106,  -304,  -304,  -304,    64,    93,  -304,  -304,
      90,   115,  -304,    90,   105,   115,  -304,     9,    79,  -304,
     110,  -304,   112,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,   114,  -304,   114,    18,   114,   114,   114,   153,
    -304,  -304,   121,  -304,    25,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,    18,    81,   129,    11,  -304,   131,  -304,  -304,  -304,
      79,    79,    79,   114,  -304,   114,  -304,   145,  -304,  -304,
     421,    18,  -304,    18,    14,   376,   -24,   161,   179,   183,
    -304,  -304,   131,    38,  -304,   180,   223,  -304,   181,    16,
    -304,   176,   213,   219,  -304,  -304,  -304,   376,   376,   376,
     376,   376,   279,   376,   376,   184,  -304,  -304,   185,   198,
    -304,  -304,   174,   173,   123,    55,   132,   111,   206,   178,
    -304,    54,  -304,    17,    39,    39,    18,  -304,    14,   114,
    -304,  -304,   140,  -304,   172,  -304,   205,   204,   203,  -304,
    -304,  -304,  -304,   376,  -304,  -304,  -304,    90,    90,  -304,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   114,
    -304,  -304,    26,   114,   202,   207,    54,  -304,   249,  -304,
     209,    20,  -304,  -304,    47,   210,   214,   211,  -304,  -304,
     218,  -304,   215,    79,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,   376,  -304,
    -304,  -304,   173,  -304,   123,    55,    55,   132,   132,   132,
     132,   111,   111,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,   221,  -304,   376,   114,   217,    18,  -304,  -304,   114,
    -304,  -304,   233,  -304,    18,   220,    39,   220,  -304,   229,
    -304,  -304,  -304,   231,   228,   227,   237,   238,  -304,    18,
     240,    79,  -304,  -304,    18,   241,  -304,   242,    39,  -304,
     376,   376,  -304,   114,   243,  -304,   248,  -304,   141,  -304,
    -304,   250,  -304,  -304,  -304,  -304,    39,   252,   256,   253,
     376,   114,   114,    24,   254,   255,   141,   257,  -304,   258,
     141,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,   259,   220,
     263,   376,   376,   141,   311,  -304,   261,   272,   274,   114,
     114,   275,  -304,  -304,   266,    18,  -304,  -304,  -304,   241,
     220,   283,   284,   281,   287,  -304,    18,    18,   282,   291,
      18,  -304,   -18,  -304,    97,   285,   288,  -304,   376,    21,
      29,    18,    18,    30,  -304,   376,  -304,  -304,   141,  -304,
     141,  -304,   290,  -304,   376,  -304,   376,    31,    36,  -304,
     376,   295,   298,   353,   307,   306,   310,   313,  -304,   376,
    -304,   376,   314,  -304,  -304,    19,  -304,  -304,  -304,  -304,
    -304,  -304,   315,   316,  -304,   318,   141,  -304,  -304,  -304,
     376,   309,   323,  -304,   321,   141,  -304,   322,  -304
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,    17,    18,    12,     0,    10,     1,
       0,     4,    11,     0,    30,     5,     6,     0,    19,    31,
       0,     3,    30,    34,    36,    37,    38,    46,    47,    39,
      40,     7,     0,     8,     0,     0,     0,     0,     0,     0,
      35,    16,     0,    24,     0,    21,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,    88,    25,     0,    85,    86,    91,    93,    94,
      19,    19,    19,     0,     9,    23,    20,     0,    90,    89,
       0,     0,   111,     0,    30,     0,     0,     0,     0,     0,
      22,    95,    87,     0,    27,     0,     0,    73,     0,    30,
      71,    16,   214,   225,   232,   233,   234,     0,    49,     0,
       0,     0,     0,     0,     0,    15,   229,   228,     0,     0,
     164,   167,   173,   174,   176,   178,   181,   186,   189,   200,
     201,    55,    54,    30,    75,    75,    29,    26,    30,     0,
      68,    72,     0,   230,     0,   231,     0,     0,    50,    51,
     194,   195,   196,     0,   198,   197,   193,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,   206,     0,     0,     0,     0,    56,    57,     0,    66,
       0,    30,    64,    82,     0,     0,     0,    76,    77,    80,
       0,    28,     0,    19,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   226,   227,   235,   208,    53,   199,
      14,    13,   175,   189,   177,   179,   180,   182,   183,   184,
     185,   187,   188,   190,   191,   192,   168,   169,   170,   171,
     172,     0,   204,   209,   236,     0,     0,    48,    58,     0,
      61,    65,     0,    83,     0,     0,    79,     0,    67,     0,
      52,   203,   211,     0,   210,     0,     0,   237,   238,     0,
       0,    19,    84,    81,     0,     0,    78,     0,    75,   202,
     213,     0,   207,   240,     0,    59,     0,    74,   119,    41,
      42,     0,   212,   241,   239,    60,    75,     0,     0,     0,
     165,     0,     0,     0,     0,     0,   119,   228,   130,     0,
     120,   121,   123,   124,   126,   131,   132,   133,   127,   128,
     129,   125,   146,   147,   148,   149,   150,   151,     0,     0,
       0,     0,     0,   119,     0,   166,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,   113,   122,   145,     0,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
       0,   112,     0,    43,     0,     0,     0,   118,     0,     0,
       0,     0,     0,     0,   152,     0,    44,    45,   119,   136,
     119,   141,     0,   156,     0,   154,     0,     0,     0,   158,
       0,     0,     0,   139,     0,     0,     0,     0,   162,     0,
     160,     0,     0,   153,   114,     0,   137,   135,   117,   142,
     157,   155,     0,     0,   159,     0,   119,   140,   163,   161,
       0,     0,     0,   116,     0,   119,   138,     0,   115
  };

  const short
  parser::yypgoto_[] =
  {
    -304,  -304,  -304,  -304,  -304,   359,  -304,   120,  -304,  -304,
     -32,     7,   -61,  -304,   301,   251,  -304,     4,  -304,  -304,
     355,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,   195,  -304,  -304,  -304,   191,  -304,   245,  -304,
     286,  -236,  -116,  -304,   130,  -304,   -54,  -304,  -304,   308,
    -304,  -304,  -304,  -304,  -248,  -304,  -304,  -304,  -304,  -304,
    -303,  -304,    77,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,  -304,   -84,  -304,  -161,  -304,  -304,   230,   234,    56,
     -26,    53,   244,  -304,  -304,  -304,  -304,  -304,  -304,  -304,
    -304,   108
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     2,     3,    14,    15,    16,     6,    63,   115,   116,
     117,   118,    35,    44,    45,    82,    93,    96,    21,    22,
      23,    24,    25,    97,   189,    26,    27,   147,   148,    28,
     185,   186,   187,    29,   190,   191,   192,    30,    98,    99,
     100,   275,   196,   197,   198,   199,    64,    65,    80,    66,
      67,    68,    69,   308,   289,   379,   426,   417,   381,   334,
     309,   310,   311,   312,   313,   314,   315,   393,   406,   407,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   336,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   263,   264,   143,   145,   130,   266,
     267,   268
  };

  const short
  parser::yytable_[] =
  {
      42,   119,    43,   344,    70,    71,    72,    77,     8,    86,
      87,    88,   236,   237,   238,   239,   240,    12,    20,   200,
       8,   277,   415,   146,   149,    83,    20,    94,   131,    95,
     353,   132,    19,    32,    19,    19,     1,   374,    19,   339,
     340,    89,     8,    43,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     4,
       5,   375,   252,    84,    33,    41,    61,   -69,     8,   -70,
     -62,   416,   183,   -63,   243,   392,   383,   394,   244,    75,
      41,   193,   201,    62,   385,   389,   398,     8,     8,   253,
       8,   400,   136,   349,   241,    41,    78,    79,    76,   184,
     384,   363,   195,   195,   194,   -32,     9,   203,   386,   390,
     399,   137,   -33,   421,   364,   401,   377,    36,    18,    37,
      38,     7,   427,    19,    10,    18,   164,   165,   166,   167,
      19,     4,     5,    17,   260,    39,    13,   188,   227,   228,
     229,   230,   259,     8,   297,   298,   299,   242,    11,   288,
      34,   245,   376,   300,   184,    41,   301,   302,   303,   262,
     304,   305,   291,    73,   220,   221,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,    74,   170,   171,   172,
     330,    85,   101,     5,   102,   103,   104,   105,   106,   107,
      81,   108,   270,   306,    91,   188,   292,   293,   162,   163,
     273,   168,   169,   109,   110,   111,   112,   113,   214,   215,
     286,   114,   265,   133,   391,   284,   335,   271,   225,   226,
     287,   231,   232,   396,   195,   397,   -25,   134,   178,   402,
     -25,   135,   138,   139,   140,   179,   -17,   142,   412,    81,
     413,   180,   181,   144,   157,   158,   195,   351,   352,   159,
     161,   265,   160,     8,   216,   217,   307,   218,   246,   249,
     247,     8,   250,   255,   195,   256,   254,   257,   258,   337,
     338,   341,   261,   269,   307,   272,     8,   278,   307,   274,
     279,     8,   280,   281,   382,   173,   174,   175,   176,   177,
     282,   362,   283,   288,   153,   285,   296,   290,   295,   329,
     331,   307,   369,   370,   332,   333,   373,   358,   359,   342,
     343,   346,   350,   345,   348,   354,   355,   387,   388,   361,
     101,     5,   102,   103,   104,   105,   106,   107,   356,   108,
     357,   360,   365,   366,   367,   368,   422,   378,   371,   395,
     380,   109,   110,   111,   112,   113,   307,   372,   307,   114,
     403,   404,     8,   150,   151,   152,   154,   155,   156,   405,
     408,   409,   423,     8,     8,   410,   420,     8,   411,   414,
     418,   419,   424,   425,    31,   428,    90,    40,     8,     8,
     182,   248,   251,   202,   307,   141,   276,   347,    92,     0,
     222,   294,     0,   307,     0,   224,     0,   219,     0,     0,
       0,     0,     0,     0,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   233,   234,   235,   101,     5,   102,
     103,   104,   105,   106,   107,     0,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   110,
     111,   112,   113,     0,     0,     0,   114,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     4,     5,     0,     0,     0,     0,     0,    61
  };

  const short
  parser::yycheck_[] =
  {
      32,    85,    34,   306,    36,    37,    38,    61,     1,    70,
      71,    72,   173,   174,   175,   176,   177,    10,    14,   135,
      13,   257,     3,   107,   108,    14,    22,    81,    52,    83,
     333,    55,    18,    24,    18,    18,    23,    55,    18,    15,
      16,    73,    35,    75,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    79,    15,    52,    55,    41,    48,    53,    61,    53,
      53,    52,    18,    53,    48,   378,    55,   380,    52,    54,
      41,    42,   136,    65,    55,    55,    55,    80,    81,    42,
      83,    55,    54,   329,   178,    41,    15,    16,    73,   131,
      79,   349,   134,   135,    65,     0,     0,   139,    79,    79,
      79,    73,     0,   416,   350,    79,   364,     7,    13,     9,
      10,     1,   425,    18,    60,    13,    71,    72,    73,    74,
      18,    41,    42,    13,   218,    25,    21,   133,   164,   165,
     166,   167,   203,   136,     3,     4,     5,   179,    55,    52,
      71,   183,    55,    12,   186,    41,    15,    16,    17,   243,
      19,    20,   278,    10,   157,   158,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    55,    66,    67,    68,
     296,    50,    41,    42,    43,    44,    45,    46,    47,    48,
      61,    50,   246,    52,    49,   191,   280,   281,    75,    76,
     254,    69,    70,    62,    63,    64,    65,    66,    36,    37,
     271,    70,   244,    52,   375,   269,   300,   249,   162,   163,
     274,   168,   169,   384,   256,   386,    48,    48,    50,   390,
      52,    48,    52,    10,    53,    57,    60,    24,   399,    61,
     401,    63,    64,    24,    60,    60,   278,   331,   332,    51,
      77,   283,    78,   246,    49,    51,   288,    54,    56,    10,
      53,   254,    53,    49,   296,    54,    56,    49,    53,   301,
     302,   303,    51,    56,   306,    42,   269,    48,   310,    59,
      49,   274,    54,    56,   368,    79,    80,    81,    82,    83,
      53,   345,    54,    52,    15,    55,    48,    55,    55,    49,
      48,   333,   356,   357,    48,    52,   360,   339,   340,    55,
      55,    53,    49,    56,    55,     4,    55,   371,   372,    53,
      41,    42,    43,    44,    45,    46,    47,    48,    56,    50,
      56,    56,    49,    49,    53,    48,   420,    52,    56,    49,
      52,    62,    63,    64,    65,    66,   378,    56,   380,    70,
      55,    53,   345,   109,   110,   111,   112,   113,   114,     6,
      53,    55,    53,   356,   357,    55,    48,   360,    55,    55,
      55,    55,    49,    52,    15,    53,    75,    22,   371,   372,
     129,   186,   191,   138,   416,    99,   256,   310,    80,    -1,
     160,   283,    -1,   425,    -1,   161,    -1,   153,    -1,    -1,
      -1,    -1,    -1,    -1,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    48
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    23,    89,    90,    41,    42,    94,    95,    99,     0,
      60,    55,    99,    21,    91,    92,    93,    95,    13,    18,
     105,   106,   107,   108,   109,   110,   113,   114,   117,   121,
     125,    93,    24,    55,    71,   100,     7,     9,    10,    25,
     108,    41,    98,    98,   101,   102,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    48,    65,    95,   134,   135,   137,   138,   139,   140,
      98,    98,    98,    10,    55,    54,    73,   134,    15,    16,
     136,    61,   103,    14,    52,    50,   100,   100,   100,    98,
     102,    49,   137,   104,   134,   134,   105,   111,   126,   127,
     128,    41,    43,    44,    45,    46,    47,    48,    50,    62,
      63,    64,    65,    66,    70,    96,    97,    98,    99,   170,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     186,    52,    55,    52,    48,    48,    54,    73,    52,    10,
      53,   128,    24,   184,    24,   185,   170,   115,   116,   170,
     180,   180,   180,    15,   180,   180,   180,    60,    60,    51,
      78,    77,    75,    76,    71,    72,    73,    74,    69,    70,
      66,    67,    68,    79,    80,    81,    82,    83,    50,    57,
      63,    64,   103,    18,    98,   118,   119,   120,   105,   112,
     122,   123,   124,    42,    65,    98,   130,   131,   132,   133,
     130,   134,   126,    98,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    49,    51,    54,   180,
      99,    99,   175,   180,   176,   177,   177,   178,   178,   178,
     178,   179,   179,   180,   180,   180,   172,   172,   172,   172,
     172,   170,    98,    48,    52,    98,    56,    53,   120,    10,
      53,   124,    15,    42,    56,    49,    54,    49,    53,   100,
     170,    51,   170,   182,   183,    98,   187,   188,   189,    56,
     134,    98,    42,   134,    59,   129,   132,   129,    48,    49,
      54,    56,    53,    54,   134,    55,   100,   134,    52,   142,
      55,   130,   170,   170,   189,    55,    48,     3,     4,     5,
      12,    15,    16,    17,    19,    20,    52,    98,   141,   148,
     149,   150,   151,   152,   153,   154,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,    49,
     130,    48,    48,    52,   147,   170,   171,    98,    98,    15,
      16,    98,    55,    55,   148,    56,    53,   150,    55,   129,
      49,   170,   170,   148,     4,    55,    56,    56,    98,    98,
      56,    53,   134,   142,   129,    49,    49,    53,    48,   134,
     134,    56,    56,   134,    55,    79,    55,   142,    52,   143,
      52,   146,   170,    55,    79,    55,    79,   134,   134,    55,
      79,   172,   148,   155,   148,    49,   172,   172,    55,    79,
      55,    79,   172,    55,    53,     6,   156,   157,    53,    55,
      55,    55,   172,   172,    55,     3,    52,   145,    55,    55,
      48,   148,   170,    53,    49,    52,   144,   148,    53
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    88,    89,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    96,    96,    97,    98,    99,    99,   100,
     100,   101,   101,   101,   102,   103,   103,   104,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     108,   109,   110,   111,   112,   112,   113,   113,   114,   115,
     115,   116,   116,   116,   117,   118,   118,   119,   119,   120,
     120,   121,   122,   122,   123,   123,   124,   125,   125,   126,
     126,   127,   127,   128,   129,   130,   130,   131,   131,   131,
     132,   132,   133,   133,   133,   134,   134,   135,   136,   136,
     136,   137,   137,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     148,   149,   149,   150,   150,   151,   151,   151,   151,   151,
     152,   152,   152,   152,   153,   154,   155,   155,   156,   157,
     157,   158,   159,   160,   161,   162,   163,   163,   163,   163,
     163,   163,   164,   164,   165,   165,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   171,   171,   172,   172,   172,
     172,   172,   172,   173,   174,   174,   175,   175,   176,   176,
     176,   177,   177,   177,   177,   177,   178,   178,   178,   179,
     179,   179,   179,   180,   180,   180,   180,   180,   180,   180,
     180,   181,   181,   181,   181,   181,   181,   181,   181,   182,
     182,   183,   183,   183,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   185,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   187,   187,   188,   188,
     188,   189
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     5,     0,     1,     1,     2,     3,     5,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     0,
       3,     1,     3,     2,     1,     0,     3,     1,     3,     2,
       0,     1,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     9,     9,     9,     9,     9,     1,     1,     7,     0,
       1,     1,     3,     2,     5,     0,     1,     1,     2,     4,
       5,     7,     0,     1,     1,     2,     1,     8,     6,     0,
       1,     1,     2,     1,     2,     0,     1,     1,     3,     2,
       1,     3,     1,     2,     3,     1,     1,     3,     0,     1,
       1,     1,     4,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     0,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     7,     0,     2,     6,     0,
       2,     5,     7,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     4,     6,     5,     7,     5,     7,     5,     7,
       6,     8,     6,     8,     1,     0,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       1,     1,     5,     4,     3,     2,     2,     5,     3,     0,
       1,     1,     3,     2,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     0,     2,     2,     1,     1,
       2,     2,     1,     1,     1,     3,     0,     1,     1,     3,
       2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_ENUM", "TOK_TRAIT", "TOK_FN",
  "TOK_TYPE", "TOK_RETURN", "TOK_IMPL", "TOK_FOR", "TOK_MUT", "TOK_IMM",
  "TOK_STATIC", "TOK_PUB", "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT",
  "TOK_EXPORT", "TOK_PACKAGE", "TOK_AS", "TOK_LOAD", "TOK_I8", "TOK_U8",
  "TOK_I16", "TOK_U16", "TOK_I32", "TOK_U32", "TOK_I64", "TOK_U64",
  "TOK_I128", "TOK_U128", "TOK_F32", "TOK_F64", "TOK_BOOL", "TOK_CHAR",
  "TOK_VOID", "TOK_IDENTIFIER", "TOK_SELF", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_CHAR_LITERAL", "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK",
  "TOK_LCBRA", "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON",
  "TOK_DOT", "TOK_QUESTION", "TOK_ARROW", "TOK_COLONCOLON",
  "TOK_TURBOFISH_S", "TOK_NEGATION", "TOK_INC", "TOK_DEC", "TOK_AMP",
  "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS", "TOK_MINUS",
  "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ", "TOK_EQUAL",
  "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "LOWER_THAN_ASSIGN", "$accept",
  "translation_unit", "module", "import_list_opt", "import_list",
  "import_decl", "path", "path_expr", "qpath", "qpath_expr",
  "ident_no_self", "ident_any", "type_params_opt", "type_param_list",
  "type_param", "type_args", "type_arg_list", "pub_opt", "decl_list_opt",
  "decl_list", "decl", "fn_decl", "load_fn_decl", "impl_fn_decl",
  "trait_fn_decl", "struct_decl", "struct_decl_def", "array_elems_opt",
  "array_elems", "struct_decl_fwd", "field_decl_list_opt",
  "field_decl_list", "field_decl", "trait_decl", "trait_item_list_opt",
  "trait_item_list", "trait_item", "impl_decl", "impl_item_list_opt",
  "impl_item_list", "impl_item", "ret_type_expr", "param_list_opt",
  "param_list", "param", "self_param", "type_expr", "ref_type_expr",
  "ref_mutability", "type_postfix", "type_primary", "builtin_type_expr",
  "path_type_expr", "anon_block", "fn_block", "if_block", "else_if_block",
  "else_block", "while_block", "do_while_block", "stmt_list_opt",
  "stmt_list", "stmt", "simple_stmt", "compound_stmt", "return_stmt",
  "if_stmt", "elseif_list", "elseif", "else_part", "while_stmt",
  "do_while_stmt", "break_stmt", "continue_stmt", "expr_stmt", "var_stmt",
  "var_stmt_default", "var_stmt_imm", "var_stmt_mut",
  "var_stmt_static_default", "var_stmt_static_imm", "var_stmt_static_mut",
  "expr", "expr_opt", "assign", "cond", "logic_or", "logic_and",
  "equality", "relational", "additive", "multiplicative", "unary",
  "postfix", "arg_list_opt", "arg_list", "int_literal_type_opt",
  "float_literal_type_opt", "primary", "field_inits_opt", "field_inits",
  "field_init", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   358,   358,   363,   371,   373,   378,   380,   385,   387,
     397,   399,   404,   409,   411,   416,   421,   426,   428,   437,
     439,   444,   446,   448,   453,   458,   460,   465,   467,   469,
     479,   480,   484,   486,   491,   493,   498,   500,   502,   504,
     506,   511,   519,   527,   536,   548,   565,   567,   572,   586,
     588,   593,   595,   597,   602,   617,   619,   624,   626,   631,
     633,   638,   651,   653,   658,   660,   665,   671,   683,   698,
     700,   705,   707,   712,   718,   723,   725,   730,   732,   734,
     739,   741,   747,   749,   751,   763,   765,   770,   775,   776,
     777,   781,   783,   788,   790,   792,   797,   798,   799,   800,
     801,   802,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   815,   824,   829,   834,   839,   844,   849,   854,   859,
     861,   866,   868,   873,   875,   880,   881,   882,   883,   884,
     888,   889,   890,   891,   895,   900,   905,   907,   912,   917,
     919,   924,   929,   934,   939,   944,   965,   966,   967,   968,
     969,   970,   978,   989,  1003,  1014,  1028,  1039,  1057,  1068,
    1082,  1093,  1107,  1118,  1138,  1142,  1143,  1147,  1149,  1151,
    1153,  1155,  1157,  1161,  1166,  1168,  1173,  1175,  1180,  1182,
    1184,  1189,  1191,  1193,  1195,  1197,  1202,  1204,  1206,  1211,
    1213,  1215,  1217,  1222,  1224,  1226,  1228,  1230,  1232,  1234,
    1236,  1241,  1243,  1247,  1249,  1251,  1253,  1255,  1257,  1266,
    1268,  1273,  1275,  1277,  1286,  1287,  1288,  1289,  1290,  1291,
    1292,  1293,  1294,  1295,  1296,  1300,  1301,  1302,  1310,  1312,
    1314,  1316,  1318,  1320,  1322,  1324,  1329,  1331,  1336,  1338,
    1340,  1345
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
#line 4499 "parser/parser.cpp"

#line 1349 "parser/parser_rules.y"

