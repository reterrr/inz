/* =============================================================================
 * parser_rules.y
 * ============================================================================= */

%define api.token.constructor
%define api.value.type variant
%language "c++"
%define api.namespace {yy}
%define api.location.type {lex::Loc}
%define lr.type ielr

%define parse.lac full
%define parse.error verbose
%define parse.trace

%lex-param   { Scanner& scanner }
%parse-param { Scanner& scanner }
%parse-param { ast::Ast& ast }
%parse-param { Translation& unit }
%parse-param { std::string_view filePath}

/* ============================== HEADER PROLOGUE ============================== */
%code requires {
  #include "generated/token.hpp"
  #include "types.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"

  #include <string>
  #include <vector>
  #include <optional>

  class Scanner;

  using Str = lex::SymId;
}

/* ============== DECLARATIONS PROVIDED AFTER yy::parser EXISTS =============== */
%code provides {
  namespace yy {
    parser::symbol_type yylex(Scanner& scanner);
  }
}

/* ============================ IMPLEMENTATION PROLOGUE ======================= */
%code {
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
}

/* ================================= START SYMBOL ============================= */
%start translation_unit

/* ================================ TOKENS ==================================== */
%token TOK_IF TOK_WHILE TOK_DO TOK_ELSE
%token TOK_STRUCT TOK_FN TOK_RETURN
%token TOK_MUT TOK_IMM TOK_PUB
%token TOK_BREAK TOK_CONTINUE
%token TOK_IMPORT TOK_PACKAGE TOK_AS TOK_LOAD

%token TOK_I8 TOK_U8 TOK_I16 TOK_U16 TOK_I32 TOK_U32 TOK_I64 TOK_U64 TOK_I128 TOK_U128
%token TOK_F32 TOK_F64 TOK_BOOL TOK_CHAR TOK_VOID

%token <Str>               TOK_IDENTIFIER
%token <Str>               TOK_SELF
%token <Str>               TOK_INT_LITERAL
%token <Str>               TOK_FLOAT_LITERAL
%token <Str>               TOK_STRING_LITERAL
%token <kl::rt::boolean>   TOK_BOOL_LITERAL
%token <kl::rt::character> TOK_CHAR_LITERAL

%token TOK_LPAR TOK_RPAR TOK_LBRACK TOK_RBRACK TOK_LCBRA TOK_RCBRA
%token TOK_COMMA TOK_SMCLN TOK_COLON
%token TOK_DOT TOK_ARROW TOK_COLONCOLON TOK_TURBOFISH_S

%token TOK_NEGATION TOK_INC TOK_DEC TOK_AMP
%token TOK_STAR TOK_SLASH TOK_MODULO
%token TOK_PLUS TOK_MINUS
%token TOK_LESS TOK_LEQ TOK_GREATER TOK_GEQ
%token TOK_EQUAL TOK_NEQUAL
%token TOK_BOOL_AND TOK_BOOL_OR
%token TOK_ASSIGN

/* ============================== PRECEDENCE ================================== */
%right  TOK_ASSIGN
%right  TERNARY
%left   TOK_BOOL_OR
%left   TOK_BOOL_AND
%left   TOK_EQUAL TOK_NEQUAL
%left   TOK_LESS TOK_LEQ TOK_GREATER TOK_GEQ
%left   TOK_PLUS TOK_MINUS
%left   TOK_STAR TOK_SLASH TOK_MODULO
%right  UMINUS UPRE

/* ============================== NONTERMINAL TYPES =========================== */

/* module / top level */
%type <kl::rt::boolean>                      pub_opt

%type <std::vector<ast::ImportDecl*>>        import_list_opt
%type <std::vector<ast::ImportDecl*>>        import_list
%type <ast::ImportDecl*>                     import_decl

%type <std::vector<ast::Decl*>>              decl_list_opt
%type <std::vector<ast::Decl*>>              decl_list
%type <ast::Decl*>                           decl

/* identifiers / paths */
%type <Str>                                  ident_no_self
%type <Str>                                  ident_any
%type <std::vector<Str>>                     path
%type <std::vector<Str>>                     qpath

%type <ast::PathExpr*>                       path_expr
%type <ast::PathExpr*>                       qpath_expr
%nonassoc LOWER_THAN_ASSIGN

/* generic params (declarations) */
%type <std::vector<ast::TypeParamDecl*>>     type_params_opt
%type <std::vector<ast::TypeParamDecl*>>     type_param_list
%type <ast::TypeParamDecl*>                  type_param

%type <std::vector<ast::TypeExpr*>>          type_args
%type <std::vector<ast::TypeExpr*>>          type_arg_list

/* types */
%type <ast::TypeExpr*>                       type_expr
%type <ast::TypeExpr*>                       type_postfix
%type <ast::TypeExpr*>                       type_primary
%type <ast::TypeExpr*>                       ret_type_expr
%type <ast::BuiltinTypeExpr*>                builtin_type_expr
%type <ast::PathTypeExpr*>                   path_type_expr
%type <ast::RefTypeExpr*>                    ref_type_expr
%type <ast::Mutability>                      ref_mutability

/* decls */
%type <ast::FnDecl*>                         fn_decl
%type <ast::LoadFnDecl*>                     load_fn_decl

%type <ast::StructDecl*>                     struct_decl
%type <ast::StructDecl*>                     struct_decl_def
%type <ast::StructDecl*>                     struct_decl_fwd

%type <std::vector<ast::FieldDecl*>>         field_decl_list_opt
%type <std::vector<ast::FieldDecl*>>         field_decl_list
%type <ast::FieldDecl*>                      field_decl

/* params */
%type <std::vector<ast::ParamDecl*>>         param_list_opt
%type <std::vector<ast::ParamDecl*>>         param_list
%type <ast::ParamDecl*>                      param

/* statements */
%type <ast::Statement*>                      stmt
%type <ast::Statement*>                      simple_stmt
%type <ast::Statement*>                      compound_stmt

%type <ast::BlockStatement*>                 anon_block
%type <ast::BlockStatement*>                 fn_block
%type <ast::BlockStatement*>                 if_block
%type <ast::BlockStatement*>                 else_if_block
%type <ast::BlockStatement*>                 else_block
%type <ast::BlockStatement*>                 while_block
%type <ast::BlockStatement*>                 do_while_block
%type <std::vector<ast::Statement*>>         stmt_list_opt
%type <std::vector<ast::Statement*>>         stmt_list

%type <ast::ReturnStatement*>                return_stmt
%type <ast::IfStatement*>                    if_stmt
%type <std::vector<ast::ElseIfStatement*>>   elseif_list
%type <ast::ElseIfStatement*>                elseif
%type <ast::ElseStatement*>                  else_part
%type <ast::WhileStatement*>                 while_stmt
%type <ast::DoWhileStatement*>               do_while_stmt
%type <ast::BreakStatement*>                 break_stmt
%type <ast::ContinueStatement*>              continue_stmt
%type <ast::ExprStatement*>                  expr_stmt

%type <std::vector<ast::Expr*>>              array_elems_opt
%type <std::vector<ast::Expr*>>              array_elems

/* var decls */
%type <ast::VarStmt*>                        var_stmt
%type <ast::VarStmt*>                        var_stmt_default
%type <ast::VarStmt*>                        var_stmt_imm
%type <ast::VarStmt*>                        var_stmt_mut

/* expressions */
%type <ast::Expr*>                           expr expr_opt
%type <ast::Expr*>                           assign cond
%type <ast::Expr*>                           logic_or logic_and
%type <ast::Expr*>                           equality relational
%type <ast::Expr*>                           additive multiplicative
%type <ast::Expr*>                           unary postfix primary

%type <std::vector<ast::Expr*>>              arg_list_opt
%type <std::vector<ast::Expr*>>              arg_list

/* struct literal fields */
%type <std::vector<ast::FieldInitExpr*>>     field_inits_opt
%type <std::vector<ast::FieldInitExpr*>>     field_inits
%type <ast::FieldInitExpr*>                  field_init

/* literal type suffix */
%type <std::optional<kl::rt::IntKind>>       int_literal_type_opt
%type <std::optional<kl::rt::FloatKind>>     float_literal_type_opt

%%

/* =============================================================================
 * Top level
 * ============================================================================= */

translation_unit
  : module
    { }
  ;

module
  : TOK_PACKAGE path_expr TOK_SMCLN import_list_opt decl_list_opt
    {
      ast.mk_module($2, std::move($4), std::move($5), combine(@1, @5));
      unit.addModule(std::move(ast));
    }
  ;

import_list_opt
  : %empty
    { $$ = std::vector<ast::ImportDecl*>{}; }
  | import_list
    { $$ = std::move($1); }
  ;

import_list
  : import_decl
    { $$ = std::vector<ast::ImportDecl*>{ $1 }; }
  | import_list import_decl
    { $1.push_back($2); $$ = std::move($1); }
  ;

import_decl
  : TOK_IMPORT path_expr TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::nullopt, /*is_public*/false, combine(@1, @3)); }
  | TOK_IMPORT path_expr TOK_AS ident_no_self TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::optional<Str>{$4}, /*is_public*/false, combine(@1, @5)); }
  ;

/* =============================================================================
 * Identifiers / paths
 * ============================================================================= */

path
  : ident_any
    { $$ = std::vector<Str>{ $1 }; }
  | path TOK_COLONCOLON ident_any
    { $1.push_back($3); $$ = std::move($1); }
  ;

path_expr
  : path
    { $$ = ast.mk_path_expr(std::move($1), @1); }
  ;

qpath
  : ident_any TOK_COLONCOLON ident_any
    { $$ = std::vector<Str>{ $1, $3 }; }
  | qpath TOK_COLONCOLON ident_any
    { $1.push_back($3); $$ = std::move($1); }
  ;

qpath_expr
  : qpath
    { $$ = ast.mk_path_expr(std::move($1), @1); }
  ;

ident_no_self
  : TOK_IDENTIFIER
    { $$ = $1; }
  ;

ident_any
  : TOK_IDENTIFIER
    { $$ = $1; }
  | TOK_SELF
    { $$ = $1; }   /* SymId from lexer */
  ;

/* =============================================================================
 * Generic parameters (declarations)
 * ============================================================================= */

type_params_opt
  : %empty
    { $$ = std::vector<ast::TypeParamDecl*>{}; }
  | TOK_LESS type_param_list TOK_GREATER
    { $$ = std::move($2); }
  ;

type_param_list
  : type_param
    { $$ = std::vector<ast::TypeParamDecl*>{ $1 }; }
  | type_param_list TOK_COMMA type_param
    { $1.push_back($3); $$ = std::move($1); }
  | type_param_list TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

type_param
  : ident_no_self
    { $$ = ast.mk_type_param_decl($1, @1); }
  ;

type_args
  : %empty
    { $$ = std::vector<ast::TypeExpr*>{}; }
  | TOK_TURBOFISH_S type_arg_list TOK_GREATER
    { $$ = std::move($2); }
  ;

type_arg_list
  : type_expr
    { $$ = std::vector<ast::TypeExpr*>{ $1 }; }
  | type_arg_list TOK_COMMA type_expr
    { $1.push_back($3); $$ = std::move($1); }
  | type_arg_list TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

/* =============================================================================
 * Declarations
 * ============================================================================= */

pub_opt
  : %empty { $$ = false; }
  | TOK_PUB { $$ = true; }
  ;

decl_list_opt
  : %empty
    { $$ = std::vector<ast::Decl*>{}; }
  | decl_list
    { $$ = std::move($1); }
  ;

decl_list
  : decl
    { $$ = std::vector<ast::Decl*>{ $1 }; }
  | decl_list decl
    { $1.push_back($2); $$ = std::move($1); }
  ;

decl
  : fn_decl
    { $$ = static_cast<ast::Decl*>($1); }
  | load_fn_decl
    { $$ = static_cast<ast::Decl*>($1); }
  | struct_decl
    { $$ = static_cast<ast::Decl*>($1); }
  ;

fn_decl
  : pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr fn_block
    {
      auto start = $1 ? @1 : @2; /* TOK_PUB if present else TOK_FN */
      $$ = ast.mk_fn_decl($3, std::move($4), std::move($6), $8, $9, $1, combine(start, @9));
    }
  ;

load_fn_decl
  : pub_opt TOK_LOAD TOK_FN ident_no_self TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
    {
      auto start = $1 ? @1 : @2; /* TOK_PUB if present else TOK_LOAD */
      $$ = ast.mk_load_fn_decl($4, std::move($6), $8, $1, combine(start, @9));
    }
  ;

struct_decl
  : struct_decl_def
    { $$ = $1; }
  | struct_decl_fwd
    { $$ = $1; }
  ;

struct_decl_def
  : pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_LCBRA field_decl_list_opt TOK_RCBRA
    {
      auto start = $1 ? @1 : @2;
      $$ = ast.mk_struct_decl(
            $3,
            std::move($4),
            std::move($6),
            $1,                  /* isExported */
            combine(start, @7)
          );
    }
  ;

struct_decl_fwd
  : pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_SMCLN
    {
      auto start = $1 ? @1 : @2;
      $$ = ast.mk_struct_decl(
            $3,
            std::move($4),
            std::vector<ast::FieldDecl*>{},
            $1,                  /* isExported */
            combine(start, @5)
          );
    }
  ;

field_decl_list_opt
  : %empty
    { $$ = std::vector<ast::FieldDecl*>{}; }
  | field_decl_list
    { $$ = std::move($1); }
  ;

field_decl_list
  : field_decl
    { $$ = std::vector<ast::FieldDecl*>{ $1 }; }
  | field_decl_list field_decl
    { $1.push_back($2); $$ = std::move($1); }
  ;

field_decl
  : ident_no_self TOK_COLON type_expr TOK_SMCLN
    { $$ = ast.mk_field_decl($1, $3, ast::Visibility::Priv, combine(@1, @4)); }
  | TOK_PUB ident_no_self TOK_COLON type_expr TOK_SMCLN
    { $$ = ast.mk_field_decl($2, $4, ast::Visibility::Publ, combine(@1, @5)); }
  ;

ret_type_expr
  : TOK_ARROW type_expr
    { $$ = $2; }
  ;

/* =============================================================================
 * Params  (NO self_param support here)
 * ============================================================================= */

param_list_opt
  : %empty
    { $$ = std::vector<ast::ParamDecl*>{}; }
  | param_list
    { $$ = std::move($1); }
  ;

param_list
  : param
    { $$ = std::vector<ast::ParamDecl*>{ $1 }; }
  | param_list TOK_COMMA param
    { $1.push_back($3); $$ = std::move($1); }
  | param_list TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

param
  : ident_no_self TOK_COLON type_expr
    { $$ = ast.mk_param_decl($1, $3, combine(@1, @3)); }
  ;

/* =============================================================================
 * Types
 * ============================================================================= */

type_expr
  : ref_type_expr
    { $$ = static_cast<ast::TypeExpr*>($1); }
  | type_postfix
    { $$ = $1; }
  ;

ref_type_expr
  : TOK_AMP ref_mutability type_postfix
    { $$ = ast.mk_ref_type_expr($3, $2, combine(@1, @3)); }
  ;

ref_mutability
  : %empty { $$ = ast::Mutability::Imm; }
  | TOK_IMM { $$ = ast::Mutability::Imm; }
  | TOK_MUT { $$ = ast::Mutability::Mut; }
  ;

type_postfix
  : type_primary
    { $$ = $1; }
  | type_postfix TOK_LBRACK expr TOK_RBRACK
    { $$ = static_cast<ast::TypeExpr*>(ast.mk_array_type_expr($1, $3, combine(@1, @4))); }
  ;

type_primary
  : builtin_type_expr
    { $$ = static_cast<ast::TypeExpr*>($1); }
  | path_type_expr
    { $$ = static_cast<ast::TypeExpr*>($1); }
  | TOK_LPAR type_expr TOK_RPAR
    { $$ = $2; }
  ;

builtin_type_expr
  : TOK_I8    { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I8,   @1); }
  | TOK_U8    { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U8,   @1); }
  | TOK_I16   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I16,  @1); }
  | TOK_U16   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U16,  @1); }
  | TOK_I32   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I32,  @1); }
  | TOK_U32   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U32,  @1); }
  | TOK_I64   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I64,  @1); }
  | TOK_U64   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U64,  @1); }
  | TOK_I128  { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::I128, @1); }
  | TOK_U128  { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::U128, @1); }
  | TOK_F32   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F32,  @1); }
  | TOK_F64   { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::F64,  @1); }
  | TOK_BOOL  { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Bool, @1); }
  | TOK_CHAR  { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Char, @1); }
  | TOK_VOID  { $$ = ast.mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind::Void, @1); }
  ;

path_type_expr
  : path_expr type_args
    { $$ = ast.mk_path_type_expr($1, std::move($2), combine(@1, @2)); }
  ;

/* =============================================================================
 * Statements
 * ============================================================================= */

anon_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::Anon, combine(@1, @3)); }
  ;

fn_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::Fn, combine(@1, @3)); }
  ;

if_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::If, combine(@1, @3)); }
  ;

else_if_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::ElseIf, combine(@1, @3)); }
  ;

else_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::Else, combine(@1, @3)); }
  ;

while_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::While, combine(@1, @3)); }
  ;

do_while_block
  : TOK_LCBRA stmt_list_opt TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), ast::BlockKind::DoWhile, combine(@1, @3)); }
  ;

stmt_list_opt
  : %empty
    { $$ = std::vector<ast::Statement*>{}; }
  | stmt_list
    { $$ = std::move($1); }
  ;

stmt_list
  : stmt
    { $$ = std::vector<ast::Statement*>{ $1 }; }
  | stmt_list stmt
    { $1.push_back($2); $$ = std::move($1); }
  ;

stmt
  : simple_stmt
    { $$ = $1; }
  | compound_stmt
    { $$ = $1; }
  ;

simple_stmt
  : var_stmt       { $$ = static_cast<ast::Statement*>($1); }
  | return_stmt    { $$ = static_cast<ast::Statement*>($1); }
  | break_stmt     { $$ = static_cast<ast::Statement*>($1); }
  | continue_stmt  { $$ = static_cast<ast::Statement*>($1); }
  | expr_stmt      { $$ = static_cast<ast::Statement*>($1); }
  ;

compound_stmt
  : anon_block     { $$ = static_cast<ast::Statement*>($1); }
  | if_stmt        { $$ = static_cast<ast::Statement*>($1); }
  | while_stmt     { $$ = static_cast<ast::Statement*>($1); }
  | do_while_stmt  { $$ = static_cast<ast::Statement*>($1); }
  ;

return_stmt
  : TOK_RETURN expr_opt TOK_SMCLN
    { $$ = ast.mk_return_stmt($2, combine(@1, @3)); }
  ;

if_stmt
  : TOK_IF TOK_LPAR expr TOK_RPAR if_block elseif_list else_part
    { $$ = ast.mk_if_stmt($3, $5, std::move($6), $7, combine(@1, @7)); }
  ;

elseif_list
  : %empty
    { $$ = std::vector<ast::ElseIfStatement*>{}; }
  | elseif_list elseif
    { $1.push_back($2); $$ = std::move($1); }
  ;

elseif
  : TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR else_if_block
    { $$ = ast.mk_else_if_stmt($4, $6, combine(@1, @6)); }
  ;

else_part
  : %empty
    { $$ = nullptr; }
  | TOK_ELSE else_block
    { $$ = ast.mk_else_stmt($2, combine(@1, @2)); }
  ;

while_stmt
  : TOK_WHILE TOK_LPAR expr TOK_RPAR while_block
    { $$ = ast.mk_while_stmt($3, $5, combine(@1, @5)); }
  ;

do_while_stmt
  : TOK_DO do_while_block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
    { $$ = ast.mk_do_while_stmt($5, $2, combine(@1, @7)); }
  ;

break_stmt
  : TOK_BREAK TOK_SMCLN
    { $$ = ast.mk_break_stmt(combine(@1, @2)); }
  ;

continue_stmt
  : TOK_CONTINUE TOK_SMCLN
    { $$ = ast.mk_continue_stmt(combine(@1, @2)); }
  ;

expr_stmt
  : expr TOK_SMCLN
    { $$ = ast.mk_expr_stmt($1, combine(@1, @2)); }
  ;

/* =============================================================================
 * Var declarations
 * ============================================================================= */

var_stmt
  : var_stmt_default        { $$ = $1; }
  | var_stmt_imm            { $$ = $1; }
  | var_stmt_mut            { $$ = $1; }
  ;

/* non-static (Auto) */

var_stmt_default
  : ident_no_self TOK_COLON type_expr TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $1, $3,
             ast::Mutability::Imm,
             ast::Storage::Auto,
             nullptr,
             combine(@1, @4)
           );
    }
  | ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $1, $3,
             ast::Mutability::Imm,
             ast::Storage::Auto,
             $5,
             combine(@1, @6)
           );
    }
  ;

var_stmt_imm
  : TOK_IMM ident_no_self TOK_COLON type_expr TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $2, $4,
             ast::Mutability::Imm,
             ast::Storage::Auto,
             nullptr,
             combine(@1, @5)
           );
    }
  | TOK_IMM ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $2, $4,
             ast::Mutability::Imm,
             ast::Storage::Auto,
             $6,
             combine(@1, @7)
           );
    }
  ;

var_stmt_mut
  : TOK_MUT ident_no_self TOK_COLON type_expr TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $2, $4,
             ast::Mutability::Mut,
             ast::Storage::Auto,
             nullptr,
             combine(@1, @5)
           );
    }
  | TOK_MUT ident_no_self TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
    {
      $$ = ast.mk_var_stmt(
             $2, $4,
             ast::Mutability::Mut,
             ast::Storage::Auto,
             $6,
             combine(@1, @7)
           );
    }
  ;

/* =============================================================================
 * Expressions
 * ============================================================================= */

expr
  : assign { $$ = $1; }
  ;

expr_opt
  : %empty { $$ = nullptr; }
  | expr   { $$ = $1; }
  ;

assign
  : cond %prec LOWER_THAN_ASSIGN
    { $$ = $1; }
  | unary TOK_ASSIGN      assign
    { $$ = ast.mk_assign_expr($1, $3, ast::AssignOp::Assign,   combine(@1, @3)); }
  ;

cond
  : logic_or
    { $$ = $1; }
  ;

logic_or
  : logic_and
    { $$ = $1; }
  | logic_or TOK_BOOL_OR logic_and
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::logical_or, $1, $3, combine(@1, @3)); }
  ;

logic_and
  : equality
    { $$ = $1; }
  | logic_and TOK_BOOL_AND equality
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, $1, $3, combine(@1, @3)); }
  ;

equality
  : relational
    { $$ = $1; }
  | equality TOK_EQUAL  relational
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::equal,     $1, $3, combine(@1, @3)); }
  | equality TOK_NEQUAL relational
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, $1, $3, combine(@1, @3)); }
  ;

relational
  : additive
    { $$ = $1; }
  | relational TOK_LESS    additive
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::less,          $1, $3, combine(@1, @3)); }
  | relational TOK_LEQ     additive
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::less_equal,    $1, $3, combine(@1, @3)); }
  | relational TOK_GREATER additive
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::greater,       $1, $3, combine(@1, @3)); }
  | relational TOK_GEQ     additive
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, $1, $3, combine(@1, @3)); }
  ;

additive
  : multiplicative
    { $$ = $1; }
  | additive TOK_PLUS multiplicative
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::add,      $1, $3, combine(@1, @3)); }
  | additive TOK_MINUS multiplicative
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::subtract, $1, $3, combine(@1, @3)); }
  ;

multiplicative
  : unary
    { $$ = $1; }
  | multiplicative TOK_STAR unary
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::multiply, $1, $3, combine(@1, @3)); }
  | multiplicative TOK_SLASH unary
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::divide,   $1, $3, combine(@1, @3)); }
  | multiplicative TOK_MODULO unary
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::modulo,   $1, $3, combine(@1, @3)); }
  ;

unary
  : TOK_MINUS unary %prec UMINUS
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::negation,      $2, combine(@1, @2)); }
  | TOK_NEGATION unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::logical_not,   $2, combine(@1, @2)); }
  | TOK_INC unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  $2, combine(@1, @2)); }
  | TOK_DEC unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::predecrement,  $2, combine(@1, @2)); }
  | TOK_STAR unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::deref,         $2, combine(@1, @2)); }
  | TOK_AMP unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::addr_of,       $2, combine(@1, @2)); }
  | TOK_AMP TOK_MUT unary %prec UPRE
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::addr_of_mut,   $3, combine(@1, @3)); }
  | postfix
    { $$ = $1; }
  ;

postfix
  : primary
    { $$ = $1; }
  | postfix type_args TOK_LPAR arg_list_opt TOK_RPAR
    { $$ = ast.mk_call_expr($1, std::move($2), std::move($4), combine(@1, @5)); }
  | postfix TOK_LBRACK expr TOK_RBRACK
    { $$ = ast.mk_index($1, $3, combine(@1, @4)); }
  | postfix TOK_DOT ident_no_self
    { $$ = ast.mk_field_expr($1, $3, combine(@1, @3)); }
  | postfix TOK_INC
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, $1, combine(@1, @2)); }
  | postfix TOK_DEC
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, $1, combine(@1, @2)); }
  | postfix type_args TOK_LCBRA field_inits_opt TOK_RCBRA
    { $$ = ast.mk_struct_literal_expr($1, std::move($2), std::move($4), combine(@1, @5)); }
  | TOK_LBRACK array_elems_opt TOK_RBRACK
    { $$ = static_cast<ast::Expr*>(ast.mk_array_literal_expr(std::move($2), combine(@1, @3))); }
  ;

arg_list_opt
  : %empty
    { $$ = std::vector<ast::Expr*>{}; }
  | arg_list
    { $$ = std::move($1); }
  ;

arg_list
  : expr
    { $$ = std::vector<ast::Expr*>{ $1 }; }
  | arg_list TOK_COMMA expr
    { $1.push_back($3); $$ = std::move($1); }
  | arg_list TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

array_elems_opt
  : %empty
    { $$ = std::vector<ast::Expr*>{}; }
  | array_elems
    { $$ = std::move($1); }
  ;

array_elems
  : expr
    { $$ = std::vector<ast::Expr*>{ $1 }; }
  | array_elems TOK_COMMA expr
    { $1.push_back($3); $$ = std::move($1); }
  | array_elems TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

/* =============================================================================
 * Literal type suffix: "123 as u8"
 * ============================================================================= */

int_literal_type_opt
  : %empty     { $$ = std::nullopt; }
  | TOK_AS TOK_I8   { $$ = kl::rt::IntKind::I8; }
  | TOK_AS TOK_U8   { $$ = kl::rt::IntKind::U8; }
  | TOK_AS TOK_I16  { $$ = kl::rt::IntKind::I16; }
  | TOK_AS TOK_U16  { $$ = kl::rt::IntKind::U16; }
  | TOK_AS TOK_I32  { $$ = kl::rt::IntKind::I32; }
  | TOK_AS TOK_U32  { $$ = kl::rt::IntKind::U32; }
  | TOK_AS TOK_I64  { $$ = kl::rt::IntKind::I64; }
  | TOK_AS TOK_U64  { $$ = kl::rt::IntKind::U64; }
  | TOK_AS TOK_I128 { $$ = kl::rt::IntKind::I128; }
  | TOK_AS TOK_U128 { $$ = kl::rt::IntKind::U128; }
  ;

float_literal_type_opt
  : %empty     { $$ = std::nullopt; }
  | TOK_AS TOK_F32  { $$ = kl::rt::FloatKind::F32; }
  | TOK_AS TOK_F64  { $$ = kl::rt::FloatKind::F64; }
  ;

/* =============================================================================
 * Primary expressions
 * ============================================================================= */

primary
  : ident_no_self
    { $$ = ast.mk_ref_expr($1, @1); }
  | TOK_SELF
    { $$ = ast.mk_ref_expr($1, @1); }
  | qpath_expr
    { $$ = static_cast<ast::Expr*>($1); }
  | TOK_INT_LITERAL int_literal_type_opt
    { $$ = ast.mk_int_literal_expr($1, $2, @1); }
  | TOK_FLOAT_LITERAL float_literal_type_opt
    { $$ = ast.mk_float_literal_expr($1, $2, @1); }
  | TOK_STRING_LITERAL
    { $$ = ast.mk_str_literal_expr($1, @1); }
  | TOK_BOOL_LITERAL
    { $$ = ast.mk_bool_literal_expr($1, @1); }
  | TOK_CHAR_LITERAL
    { $$ = ast.mk_char_literal_expr($1, @1); }
  | TOK_LPAR expr TOK_RPAR
    { $$ = $2; }
  ;

field_inits_opt
  : %empty
    { $$ = std::vector<ast::FieldInitExpr*>{}; }
  | field_inits
    { $$ = std::move($1); }
  ;

field_inits
  : field_init
    { $$ = std::vector<ast::FieldInitExpr*>{ $1 }; }
  | field_inits TOK_COMMA field_init
    { $1.push_back($3); $$ = std::move($1); }
  | field_inits TOK_COMMA
    { $$ = std::move($1); } /* trailing comma */
  ;

field_init
  : ident_no_self TOK_COLON expr
    { $$ = ast.mk_field_init_expr($1, $3, combine(@1, @3)); }
  ;

%%

