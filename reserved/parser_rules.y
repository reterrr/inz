/* =============================================================================
 * parser_reserved_rules.y
 *
 * Signature-only grammar for reserved/builtin declarations.
 * - Supports: package/imports, struct forward/type-ctor declarations, fn signatures,
 *   load fn signatures.
 * - No function bodies, no statements, no expressions (except const int in array types).
 *
 * This file reuses your existing Scanner, ast::Ast builders, Translation integration,
 * and token set.
 * ============================================================================= */

%define api.token.constructor
%define api.value.type variant
%language "c++"
%define api.namespace {yy::reserved}
%define api.location.type {lex::Loc}
%define lr.type ielr

%define parse.lac full
%define parse.error verbose
%define parse.trace

%lex-param   { Scanner& scanner }
%parse-param { Scanner& scanner }
%parse-param { ast::Ast& ast }
%parse-param { Translation& unit }
%parse-param { std::string_view filePath }

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

/* ============== DECLARATIONS PROVIDED AFTER yy::reserved::parser EXISTS =============== */
%code provides {
  namespace yy::reserved {
    parser::symbol_type yylex(Scanner& scanner);
  }
}


/* ============================ IMPLEMENTATION PROLOGUE ======================= */
%code {
  #include "lexer/lexer.hpp"
  #include "ast/ast.hpp"
  #include "translation.hpp"
  #include <iostream>
  #include <utility>

  void yy::reserved::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << filePath << ':' << loc.begin.line << ':' << loc.begin.column
              << ": " << msg << '\n';
  }

  yy::reserved::parser::symbol_type yy::reserved::yylex(Scanner& scanner) {
    scanner.yylex();

    const lex::Token& t = scanner.getCurrentToken();
    const lex::Loc    L = t.loc_;

    using T = lex::Type;
    switch (t.type_) {
      /* payload-bearing */
      case T::TOK_IDENTIFIER:     return yy::reserved::parser::make_TOK_IDENTIFIER(t.u_.sym, L);
      case T::TOK_INT_LITERAL:    return yy::reserved::parser::make_TOK_INT_LITERAL(t.u_.sym, L);
      case T::TOK_FLOAT_LITERAL:  return yy::reserved::parser::make_TOK_FLOAT_LITERAL(t.u_.sym, L);
      case T::TOK_STRING_LITERAL: return yy::reserved::parser::make_TOK_STRING_LITERAL(t.u_.sym, L);
      case T::TOK_BOOL_LITERAL:   return yy::reserved::parser::make_TOK_BOOL_LITERAL(t.u_.boolean, L);
      case T::TOK_CHAR_LITERAL:   return yy::reserved::parser::make_TOK_CHAR_LITERAL(t.u_.ch, L);
      case T::TOK_SELF:           return yy::reserved::parser::make_TOK_SELF(t.u_.sym, L);

      /* keywords */
      case T::TOK_FN:       return yy::reserved::parser::make_TOK_FN(L);
      case T::TOK_STRUCT:   return yy::reserved::parser::make_TOK_STRUCT(L);
      case T::TOK_IMPORT:   return yy::reserved::parser::make_TOK_IMPORT(L);
      case T::TOK_EXPORT:   return yy::reserved::parser::make_TOK_EXPORT(L);
      case T::TOK_PACKAGE:  return yy::reserved::parser::make_TOK_PACKAGE(L);
      case T::TOK_AS:       return yy::reserved::parser::make_TOK_AS(L);
      case T::TOK_PUB:      return yy::reserved::parser::make_TOK_PUB(L);
      case T::TOK_MUT:      return yy::reserved::parser::make_TOK_MUT(L);
      case T::TOK_IMM:      return yy::reserved::parser::make_TOK_IMM(L);
      case T::TOK_STATIC:   return yy::reserved::parser::make_TOK_STATIC(L);
      case T::TOK_LOAD:     return yy::reserved::parser::make_TOK_LOAD(L);

      /* builtin type keywords */
      case T::TOK_I8:   return yy::reserved::parser::make_TOK_I8(L);
      case T::TOK_U8:   return yy::reserved::parser::make_TOK_U8(L);
      case T::TOK_I16:  return yy::reserved::parser::make_TOK_I16(L);
      case T::TOK_U16:  return yy::reserved::parser::make_TOK_U16(L);
      case T::TOK_I32:  return yy::reserved::parser::make_TOK_I32(L);
      case T::TOK_U32:  return yy::reserved::parser::make_TOK_U32(L);
      case T::TOK_I64:  return yy::reserved::parser::make_TOK_I64(L);
      case T::TOK_U64:  return yy::reserved::parser::make_TOK_U64(L);
      case T::TOK_I128: return yy::reserved::parser::make_TOK_I128(L);
      case T::TOK_U128: return yy::reserved::parser::make_TOK_U128(L);
      case T::TOK_F32:  return yy::reserved::parser::make_TOK_F32(L);
      case T::TOK_F64:  return yy::reserved::parser::make_TOK_F64(L);
      case T::TOK_BOOL: return yy::reserved::parser::make_TOK_BOOL(L);
      case T::TOK_CHAR: return yy::reserved::parser::make_TOK_CHAR(L);
      case T::TOK_VOID: return yy::reserved::parser::make_TOK_VOID(L);

      /* punctuation */
      case T::TOK_LPAR:        return yy::reserved::parser::make_TOK_LPAR(L);
      case T::TOK_RPAR:        return yy::reserved::parser::make_TOK_RPAR(L);
      case T::TOK_LBRACK:      return yy::reserved::parser::make_TOK_LBRACK(L);
      case T::TOK_RBRACK:      return yy::reserved::parser::make_TOK_RBRACK(L);
      case T::TOK_LCBRA:       return yy::reserved::parser::make_TOK_LCBRA(L);
      case T::TOK_RCBRA:       return yy::reserved::parser::make_TOK_RCBRA(L);
      case T::TOK_COMMA:       return yy::reserved::parser::make_TOK_COMMA(L);
      case T::TOK_SMCLN:       return yy::reserved::parser::make_TOK_SMCLN(L);
      case T::TOK_COLON:       return yy::reserved::parser::make_TOK_COLON(L);
      case T::TOK_COLONCOLON:  return yy::reserved::parser::make_TOK_COLONCOLON(L);
      case T::TOK_ARROW:       return yy::reserved::parser::make_TOK_ARROW(L);
      case T::TOK_TURBOFISH_S: return yy::reserved::parser::make_TOK_TURBOFISH_S(L);
      case T::TOK_LESS: return yy::reserved::parser::make_TOK_LESS(L);
      case T::TOK_GREATER: return yy::reserved::parser::make_TOK_GREATER(L);

      /* operators used in type refs */
      case T::TOK_AMP:         return yy::reserved::parser::make_TOK_AMP(L);

      /* EOF / unknown */
      case T::TOK_END: return yy::reserved::parser::make_YYEOF(L);
      default:         return yy::reserved::parser::make_YYUNDEF(L);
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
%token TOK_STRUCT TOK_FN TOK_IMPORT TOK_EXPORT TOK_PACKAGE TOK_AS TOK_LOAD
%token TOK_MUT TOK_IMM TOK_STATIC TOK_PUB

%token TOK_I8 TOK_U8 TOK_I16 TOK_U16 TOK_I32 TOK_U32 TOK_I64 TOK_U64 TOK_I128 TOK_U128
%token TOK_F32 TOK_F64 TOK_BOOL TOK_CHAR TOK_VOID

%token <Str>               TOK_IDENTIFIER
%token <Str>               TOK_SELF
%token <Str>               TOK_INT_LITERAL
%token <Str>               TOK_FLOAT_LITERAL
%token <Str>               TOK_STRING_LITERAL
%token <kl::rt::boolean>   TOK_BOOL_LITERAL
%token <kl::rt::character> TOK_CHAR_LITERAL

%token TOK_LPAR TOK_RPAR TOK_LBRACK TOK_RBRACK TOK_LCBRA TOK_RCBRA TOK_LESS TOK_GREATER
%token TOK_COMMA TOK_SMCLN TOK_COLON TOK_COLONCOLON TOK_ARROW TOK_TURBOFISH_S

%token TOK_AMP

/* ============================== NONTERMINAL TYPES =========================== */

/* top-level */
%type <kl::rt::boolean>                      pub_opt

%type <std::vector<ast::ImportDecl*>>        import_list_opt
%type <std::vector<ast::ImportDecl*>>        import_list
%type <ast::ImportDecl*>                     import_decl

%type <std::vector<ast::Decl*>>              sig_decl_list_opt
%type <std::vector<ast::Decl*>>              sig_decl_list
%type <ast::Decl*>                           sig_decl

%type <ast::FnDecl*>                         sig_fn_decl
%type <ast::LoadFnDecl*>                     sig_load_fn_decl
%type <ast::StructDecl*>                     sig_struct_decl

/* identifiers / paths */
%type <Str>                                  ident_no_self
%type <Str>                                  ident_any
%type <std::vector<Str>>                     path
%type <ast::PathExpr*>                       path_expr

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

/* params */
%type <std::vector<ast::ParamDecl*>>         param_list_opt
%type <std::vector<ast::ParamDecl*>>         param_list
%type <ast::ParamDecl*>                      param
%type <ast::ParamDecl*>                      self_param

/* const int expr for array sizes (signature-only) */
%type <ast::Expr*>                           const_int_expr

%%

/* =============================================================================
 * Top level (signature-only module)
 * ============================================================================= */

translation_unit
  : sig_module
    { }
  ;

sig_module
  : TOK_PACKAGE path_expr TOK_SMCLN import_list_opt sig_decl_list_opt
    {
      ast.mk_module($2, std::move($4), std::move($5), combine(@1, @5));
      unit.addModule(std::move(ast));
    }
  ;

/* =============================================================================
 * Imports
 * ============================================================================= */

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

ident_no_self
  : TOK_IDENTIFIER
    { $$ = $1; }
  ;

ident_any
  : TOK_IDENTIFIER
    { $$ = $1; }
  | TOK_SELF
    { $$ = $1; }
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
    { $$ = std::move($1); }
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
    { $$ = std::move($1); }
  ;

/* =============================================================================
 * Signature-only declarations
 * ============================================================================= */

pub_opt
  : %empty   { $$ = false; }
  | TOK_PUB  { $$ = true;  }
  ;

sig_decl_list_opt
  : %empty
    { $$ = std::vector<ast::Decl*>{}; }
  | sig_decl_list
    { $$ = std::move($1); }
  ;

sig_decl_list
  : sig_decl
    { $$ = std::vector<ast::Decl*>{ $1 }; }
  | sig_decl_list sig_decl
    { $1.push_back($2); $$ = std::move($1); }
  ;

sig_decl
  : sig_fn_decl
    { $$ = static_cast<ast::Decl*>($1); }
  | sig_load_fn_decl
    { $$ = static_cast<ast::Decl*>($1); }
  | sig_struct_decl
    { $$ = static_cast<ast::Decl*>($1); }
  ;

/* function signature: must end with semicolon, body is forbidden */
sig_fn_decl
  : pub_opt TOK_FN ident_no_self type_params_opt TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
    {
      auto start = $1 ? @1 : @2; /* TOK_PUB if present else TOK_FN */

      /* IMPORTANT:
       * Your ast.mk_fn_decl() in the full grammar takes a body (BlockStatement*).
       * For signature-only declarations, you must allow body==nullptr.
       * If your mk_fn_decl cannot accept nullptr, add mk_fn_sig_decl() and call it here.
       */
      $$ = ast.mk_fn_decl(
            $3,                 /* name */
            std::move($4),      /* type params */
            std::move($6),      /* params */
            $8,                 /* ret */
            /*body*/ ast.mk_block_stmt(std::vector<ast::Statement*>{}, ast::BlockKind::Fn, {}),   /* signature-only */
            $1,                 /* is_pub */
            combine(start, @9)
          );
    }
  ;

/* load fn signature: already semicolon-terminated in your main grammar */
sig_load_fn_decl
  : pub_opt TOK_LOAD TOK_FN ident_no_self TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
    {
      auto start = $1 ? @1 : @2; /* TOK_PUB if present else TOK_LOAD */
      $$ = ast.mk_load_fn_decl($4, std::move($6), $8, $1, combine(start, @9));
    }
  ;

/* struct signature: forward/type-ctor only (no fields) */
sig_struct_decl
  : pub_opt TOK_STRUCT ident_no_self type_params_opt TOK_SMCLN
    {
      auto start = $1 ? @1 : @2; /* TOK_PUB if present else TOK_STRUCT */
      $$ = ast.mk_struct_decl(
            $3,
            std::move($4),
            std::vector<ast::FieldDecl*>{}, /* no fields in reserved signatures */
            $1,
            combine(start, @5)
          );
    }
  ;

/* =============================================================================
 * Params
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
    { $$ = std::move($1); }
  ;

param
  : self_param
    { $$ = $1; }
  | ident_no_self TOK_COLON type_expr
    { $$ = ast.mk_param_decl($1, $3, combine(@1, @3)); }
  ;

/* Keep receiver forms for compatibility; reserved signatures can ignore self */
self_param
  : TOK_SELF
    { $$ = ast.mk_self_param_decl($1, ast::SelfParamKind::Value, @1); }
  | TOK_AMP TOK_SELF
    { $$ = ast.mk_self_param_decl($2, ast::SelfParamKind::Ref, combine(@1, @2)); }
  | TOK_AMP TOK_MUT TOK_SELF
    { $$ = ast.mk_self_param_decl($3, ast::SelfParamKind::RefMut, combine(@1, @3)); }
  ;

/* =============================================================================
 * Types (signature-only)
 * - Supports refs and array suffix with const integer length.
 * ============================================================================= */

ret_type_expr
  : TOK_ARROW type_expr
    { $$ = $2; }
  ;

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
  : %empty   { $$ = ast::Mutability::Imm; }
  | TOK_IMM  { $$ = ast::Mutability::Imm; }
  | TOK_MUT  { $$ = ast::Mutability::Mut; }
  ;

/* array suffix uses const_int_expr to avoid full expression grammar */
type_postfix
  : type_primary
    { $$ = $1; }
  | type_postfix TOK_LBRACK const_int_expr TOK_RBRACK
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
 * Const int expr for array lengths (signature-only)
 * - Accepts only an int literal, no arithmetic.
 * - You can later extend this to allow simple constant folding if needed.
 * ============================================================================= */

const_int_expr
  : TOK_INT_LITERAL
    {
      /* If your mk_int_literal_expr requires a suffix, pass std::nullopt. */
      $$ = ast.mk_int_literal_expr($1, std::nullopt, @1);
    }
  ;

%%

/* End of parser_reserved_rules.y */
