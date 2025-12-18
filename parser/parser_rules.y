%define api.token.constructor
%define api.value.type variant
%language "c++"
%define api.namespace {yy}
%define api.location.type {lex::Loc}

%define parse.lac full
%define parse.error verbose
%define parse.trace

/* We pass both the scanner and the AST factory into the parser. */
%lex-param   { Scanner& scanner }
%parse-param { Scanner& scanner }
%parse-param { ast::AST& ast }

/* ================= HEADER-SIDE PROLOGUE (goes into parser.hpp) ================= */
%code requires {
  #include "generated/token.hpp"
  #include "ast/ast.hpp"
  #include "types.hpp"
  #include <vector>
  #include <string>
  #include <optional>

  class Scanner;

  using Str = lex::SymId;
}


/* ============== DECLARATIONS PROVIDED AFTER yy::parser EXISTS ================== */
%code provides {
  yy::parser::symbol_type yylex(Scanner& scanner);
}

/* ================== IMPL-SIDE PROLOGUE (goes into parser.cpp) ================== */
%code {
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
}



/* ================================== START SYMBOL ================================== */
%start translation_unit

/* =============================== TYPED TOKENS ===================================== */
%token TOK_IF TOK_WHILE TOK_DO TOK_ELSE
%token TOK_STRUCT TOK_ENUM TOK_TRAIT TOK_FN TOK_TYPE TOK_RETURN
%token TOK_MUT TOK_IMM TOK_STATIC TOK_PUB
%token TOK_BREAK TOK_CONTINUE
%token TOK_IMPORT TOK_EXPORT TOK_PACKAGE TOK_AS

%token TOK_I8 TOK_U8 TOK_I16 TOK_U16 TOK_I32 TOK_U32 TOK_I64 TOK_U64 TOK_I128 TOK_U128
%token TOK_F32 TOK_F64 TOK_BOOL TOK_CHAR

%token <Str>                 TOK_IDENTIFIER
%token <Str>                 TOK_INT_LITERAL
%token <Str>                 TOK_FLOAT_LITERAL
%token <Str>                 TOK_STRING_LITERAL
%token <kl::rt::boolean>     TOK_BOOL_LITERAL
%token <kl::rt::character>   TOK_CHAR_LITERAL

%token TOK_LPAR TOK_RPAR TOK_LBRACK TOK_RBRACK TOK_LCBRA TOK_RCBRA
%token TOK_COMMA TOK_SMCLN TOK_COLON
%token TOK_DOT TOK_QUESTION TOK_ARROW

%token TOK_NEGATION TOK_INC TOK_DEC TOK_AMP
%token TOK_STAR TOK_SLASH TOK_MODULO
%token TOK_PLUS TOK_MINUS
%token TOK_LESS TOK_LEQ TOK_GREATER TOK_GEQ
%token TOK_EQUAL TOK_NEQUAL
%token TOK_BOOL_AND TOK_BOOL_OR
%token TOK_ASSIGN TOK_PLUS_ASSIGN TOK_MIN_ASSIGN TOK_MUL_ASSIGN TOK_DIV_ASSIGN


/* =============================== PRECEDENCE ======================================= */
%right  TOK_ASSIGN TOK_PLUS_ASSIGN TOK_MIN_ASSIGN TOK_MUL_ASSIGN TOK_DIV_ASSIGN
%right  TERNARY
%left   TOK_BOOL_OR
%left   TOK_BOOL_AND
%left   TOK_EQUAL TOK_NEQUAL
%left   TOK_LESS TOK_LEQ TOK_GREATER TOK_GEQ
%left   TOK_PLUS TOK_MINUS
%left   TOK_STAR TOK_SLASH TOK_MODULO
%right  UMINUS UPRE

/* ============================ TYPED NONTERMINALS ================================== */
/* program & decls */
%type <ast::Module*>                    translation_unit

/* names & imports */
%type <Str>                               ident name
%type <std::vector<Str>>                  ident_list
%type <ast::PathExpr*>                    path_expr
%type <std::vector<Str>>                  names_separated_by_dots
%type <ast::ImportDecl*>                  import_decl
%type <std::vector<ast::ImportDecl*>>     import_list
%type <std::vector<Str>>                  opt_package

%type <std::optional<kl::rt::IntKind>>   int_literal_type_opt
%type <std::optional<kl::rt::FloatKind>> float_literal_type_opt

/* decls */
%type <std::vector<ast::Decl*>>         decl_list
%type <ast::Decl*>                      decl
%type <ast::FunctionDecl*>                fn_decl
%type <ast::VarDecl*>                     var_decl   /* top-level var decl */

%type <ast::RefTypeExpr::Mutability>      ref_mutability
%type <ast::VarDecl::Mutability>          var_mutability
/* types */
%type <ast::TypeExpr*>                    type_expr ret_type_expr
%type <ast::ArrayTypeExpr*>               array_type_expr
%type <ast::BuiltinTypeExpr*>             builtin_type_expr
%type <ast::PathTypeExpr*>                path_type_expr
%type <ast::RefTypeExpr*>                 ref_type_expr

/* statements */
%type <ast::Statement*>                 stmt
%type <ast::BlockStatement*>              block
%type <std::vector<ast::Statement*>>    stmt_list
%type <ast::IfStatement*>                    if_stmt
%type <std::vector<ast::ElseIfStatement*>>   elseif_list
%type <ast::ElseIfStatement*>                elseif
%type <ast::ElseStatement*>                  else_part

/* local var decls (statement-level) */
%type <ast::VarDeclStatement*>            var_decl_stmt
/* top-level var decls (declaration-level) */

/* parameters */
%type <ast::ParamDecl*>                 param
%type <std::vector<ast::ParamDecl*>>    param_list param_list_opt

%type <std::vector<ast::FieldDecl*>>      field_decl_list field_decl_list_opt
%type <ast::FieldDecl*>                   field_decl

/* expressions */
%type <ast::Expr*>                      expr assign cond logic_or logic_and equality relational additive multiplicative unary postfix primary expr_opt
%type <ast::StructLiteralExpr*>             struct_lit
%type <std::vector<ast::Expr*>>         arg_list arg_list_opt

/* struct literal fields */
%type <std::vector<ast::FieldInitExpr*>>    field_inits field_inits_opt
%type <ast::FieldInitExpr*>                 field_init

%type <ast::StructDecl*>                  struct_decl



%%
/* ============================ modules / top level ============================ */

translation_unit
  : opt_package import_list decl_list
    {
        auto* m = ast.mk_module(std::move($1), std::move($2), std::move($3), combine(@1, @3));
        ast.project_add_module(m);
        $$ = m;
    }
  ;

/* Produce the package path as a vector<SymId>. Empty means “no package”. */
opt_package
  : /* empty */
    { $$ = std::vector<Str>{}; }
  | TOK_PACKAGE names_separated_by_dots TOK_SMCLN
    { $$ = std::move($2); }
  ;

/* Accumulate ImportDecl* into a vector. */
import_list
  : /* empty */
    { $$ = std::vector<ast::ImportDecl*>{}; }
  | import_list import_decl
    { $1.push_back($2); $$ = std::move($1); }
  ;

/* import path;                -> no alias, not public
   import path as name;        -> alias, not public */
import_decl
  : TOK_IMPORT names_separated_by_dots TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::nullopt, /*is_public*/false, combine(@1, @3)); }
  | TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::optional<lex::SymId>{$4}, /*is_public*/false, combine(@1, @5)); }
  ;

path_expr
    : names_separated_by_dots   { $$ = ast.mk_path_expr(std::move($1), @1); }
    ;

/* dotted path → vector<SymId> */
names_separated_by_dots
  : name
    { std::vector<lex::SymId> v; v.push_back($1); $$ = std::move(v); }
  | names_separated_by_dots TOK_DOT name
    { $1.push_back($3); $$ = std::move($1); }
  ;

name
  : TOK_IDENTIFIER
    { $$ = $1; }
  ;
/* ================================ decls ===================================== */

decl_list
  : /* empty */                    { $$ = std::vector<ast::Decl*>{}; }
  | decl_list decl                 { $1.push_back(std::move($2)); $$ = std::move($1); }
  ;

decl
  : fn_decl      { $$ = static_cast<ast::Decl*>($1); }
  | struct_decl  { $$ = static_cast<ast::Decl*>($1); }
  ;

fn_decl
  : TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr block
    {
      $$ = ast.mk_fn_decl($2, std::move($4), $6, $7, combine(@1, @7));
    }
  | TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type_expr TOK_SMCLN
    {
      $$ = ast.mk_fn_decl($2, std::move($4), $6, nullptr, combine(@1, @6)); /* prototype */
    }
  ;

struct_decl
    : TOK_STRUCT ident TOK_LCBRA field_decl_list_opt TOK_RCBRA
      { $$ = ast.mk_struct_decl($2, std::move($4), combine(@1, @5)); }
    | TOK_STRUCT ident TOK_SMCLN
      { $$ = ast.mk_struct_decl($2, std::vector<ast::FieldDecl*>{}, combine(@1, @3)); }
    ;

field_decl_list_opt
    :                                   { $$ = std::vector<ast::FieldDecl*>{}; }
    | field_decl_list                   { $$ = std::move($1); }
    ;

field_decl_list
    : field_decl                        { std::vector<ast::FieldDecl*> v; v.push_back($1); $$ = std::move(v); }
    | field_decl_list field_decl        { $1.push_back($2); $$ = std::move($1); }
    ;

field_decl
  : ident TOK_COLON type_expr TOK_SMCLN
    { $$ = ast.mk_field_decl($1, $3, ast::FieldDecl::Visibility::Priv, combine(@1, @4)); }
  | TOK_PUB ident TOK_COLON type_expr TOK_SMCLN
    { $$ = ast.mk_field_decl($2, $4, ast::FieldDecl::Visibility::Publ, combine(@1, @5)); }
  ;

ret_type_expr
    : TOK_ARROW type_expr                { $$ = $2; }
    ;

param_list_opt
    : /* empty */                        { $$ = std::vector<ast::ParamDecl*>{}; }
    | param_list                         { $$ = std::move($1); }
    ;

param_list
    : param                              { std::vector<ast::ParamDecl*> v; v.push_back($1); $$ = std::move(v); }
    | param_list TOK_COMMA param         { $1.push_back($3); $$ = std::move($1); }
    | param_list TOK_COMMA               { $$ = std::move($1); } /* trailing comma */
    ;

param
  : ident TOK_COLON type_expr
    { $$ = ast.mk_param_decl($1, $3, combine(@1, @3)); }
  ;

/* ================================= types ==================================== */

type_expr
  : builtin_type_expr      { $$ = static_cast<ast::TypeExpr*>($1); }
  | path_type_expr        { $$ = static_cast<ast::TypeExpr*>($1); }
  | array_type_expr  { $$ = static_cast<ast::TypeExpr*>($1); }
  | ref_type_expr     { $$ = static_cast<ast::TypeExpr*>($1); }
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
  ;

path_type_expr
    : path_expr    { $$ = ast.mk_path_type_expr($1, @1); }
    ;

array_type_expr
    : type_expr TOK_LBRACK expr TOK_RBRACK
    { $$ = ast.mk_array_type_expr($1, $3, combine(@1, @3)); }
    ;

ref_mutability
    :           { $$ = ast::RefTypeExpr::Mutability::Imm; }
    | TOK_IMM   { $$ = ast::RefTypeExpr::Mutability::Imm; }
    | TOK_MUT   { $$ = ast::RefTypeExpr::Mutability::Mut; }
    ;

ref_type_expr
    : TOK_AMP ref_mutability type_expr
    { $$ = ast.mk_ref_type_expr($3, $2, combine(@1, @3)); }
    ;

ident
    : TOK_IDENTIFIER    { $$ = std::move($1); }
    ;

ident_list
    : ident                        { $$ = std::vector<Str>({$1}; }
    | ident_list TOK_COMMA ident   { $1.push_back(std::move($3)); $$ = std::move($1); }
    ;

/* =============================== statements ================================= */

block
  : TOK_LCBRA stmt_list TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), combine(@1, @2)); }
  ;

stmt_list
  : /* empty */               { $$ = std::vector<ast::Statement*>{}; }
  | stmt_list stmt            { $1.push_back(std::move($2)); $$ = std::move($1); }
  ;

stmt
  : var_decl_stmt                         { $$ = static_cast<ast::Statement*>($1); }
  | TOK_RETURN expr_opt TOK_SMCLN         { $$ = ast.mk_return_stmt($2, @1); }
  | if_stmt
      { $$ = static_cast<ast::Statement*>($1); }
  | TOK_WHILE TOK_LPAR expr TOK_RPAR block
      { $$ = ast.mk_while_stmt($3, $5, combine(@1, @5)); }
  | TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
      { $$ = ast.mk_do_while_stmt($5, $2, combine(@1, @7)); }
  | TOK_BREAK TOK_SMCLN                   { $$ = ast.mk_break_stmt(combine(@1, @2)); }
  | TOK_CONTINUE TOK_SMCLN                { $$ = ast.mk_continue_stmt(combine(@1, @2)); }
  | block                                 { $$ = static_cast<ast::Statement*>($1); }
  | expr TOK_SMCLN                        { $$ = ast.mk_expr_stmt($1, combine(@1, @2)); }
  ;


if_stmt
  : TOK_IF TOK_LPAR expr TOK_RPAR block elseif_list else_part
    {
      $$ = ast.mk_if_stmt($3, $5, std::move($6), $7, combine(@1, @7));
    }
  ;

elseif_list
  : /* empty */
    { $$ = std::vector<ast::ElseIfStatement*>{}; }
  | elseif_list elseif
    { $1.push_back($2); $$ = std::move($1); }
  ;

elseif
  : TOK_ELSE TOK_IF TOK_LPAR expr TOK_RPAR block
    {
      $$ = ast.mk_else_if_stmt($4, $6, combine(@1, @6));
    }
  ;

else_part
  : /* empty */
    { $$ = nullptr; }
  | TOK_ELSE block
    {
      $$ = ast.mk_else_stmt($2, combine(@1, @2));
    }
  ;



expr_opt
  : /* empty */   { $$ = nullptr; }
  | expr          { $$ = std::move($1); }
  ;

/* ================== local (statement-level) var declarations ================== */
/* let T a, b=1; — typed mid-rule ($0) threads the type to declarators. */

var_decl_stmt
  : var_decl
    { $$ = ast.mk_var_decl_stmt($1, @1); }
  ;

/* ================== top-level (declaration-level) var declarations ============ */
var_mutability
    :          { $$ = ast::VarDecl::Mutability::Imm; }
    | TOK_IMM  { $$ = ast::VarDecl::Mutability::Imm; }
    | TOK_MUT  { $$ = ast::VarDecl::Mutability::Mut; }
    ;

var_decl
  : var_mutability ident TOK_COLON type_expr TOK_SMCLN
    {
      $$ = ast.mk_var_decl($2, $4, $1, /*init*/nullptr, combine(@1, @5));
    }
  | var_mutability ident TOK_COLON type_expr TOK_ASSIGN assign TOK_SMCLN
    {
      $$ = ast.mk_var_decl($2, $4, $1, /*init*/$6, combine(@1, @7));
    }
  ;


/* =============================== expressions ================================ */

expr
  : assign
  ;

assign
  : cond
  | postfix TOK_ASSIGN      assign  { $$ = ast.mk_assign_expr($1, $3, /*Assign*/AssignOp::Assign, combine(@1, @3)); }
  | postfix TOK_PLUS_ASSIGN assign  { $$ = ast.mk_assign_expr($1, $3, /*AddEq*/AssignOp::Add, combine(@1, @3)); }
  | postfix TOK_MIN_ASSIGN  assign  { $$ = ast.mk_assign_expr($1, $3, /*SubEq*/AssignOp::Subtract, combine(@1, @3)); }
  | postfix TOK_MUL_ASSIGN  assign  { $$ = ast.mk_assign_expr($1, $3, /*MulEq*/AssignOp::Multiply, combine(@1, @3)); }
  | postfix TOK_DIV_ASSIGN  assign  { $$ = ast.mk_assign_expr($1, $3, /*DivEq*/AssignOp::Divide, combine(@1, @3)); }
  ;

cond
  : logic_or
  ;

logic_or
  : logic_and
  | logic_or TOK_BOOL_OR logic_and
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::logical_or,  std::move($1), std::move($3), combine(@1, @3)); }
  ;

logic_and
  : equality
  | logic_and TOK_BOOL_AND equality
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::logical_and, std::move($1), std::move($3), combine(@1, @3)); }
  ;

equality
  : relational
  | equality TOK_EQUAL  relational
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::equal, std::move($1), std::move($3), combine(@1, @3)); }
  | equality TOK_NEQUAL relational
    { $$ = ast.mk_binary_op_expr(ast::BinaryOp::not_equal, std::move($1), std::move($3), combine(@1, @3)); }
  ;

relational
  : additive
  | relational TOK_LESS    additive { $$ = ast.mk_binary_op_expr(ast::BinaryOp::less, std::move($1), std::move($3), combine(@1, @3)); }
  | relational TOK_LEQ     additive { $$ = ast.mk_binary_op_expr(ast::BinaryOp::less_equal, std::move($1), std::move($3), combine(@1, @3)); }
  | relational TOK_GREATER additive { $$ = ast.mk_binary_op_expr(ast::BinaryOp::greater, std::move($1), std::move($3), combine(@1, @3)); }
  | relational TOK_GEQ     additive { $$ = ast.mk_binary_op_expr(ast::BinaryOp::greater_equal, std::move($1), std::move($3), combine(@1, @3)); }
  ;

additive
  : multiplicative
  | additive TOK_PLUS  multiplicative { $$ = ast.mk_binary_op_expr(ast::BinaryOp::add, std::move($1), std::move($3), combine(@1, @3)); }
  | additive TOK_MINUS multiplicative { $$ = ast.mk_binary_op_expr(ast::BinaryOp::subtract, std::move($1), std::move($3), combine(@1, @3)); }
  ;

multiplicative
  : unary
  | multiplicative TOK_STAR   unary { $$ = ast.mk_binary_op_expr(ast::BinaryOp::multiply, std::move($1), std::move($3), combine(@1, @3)); }
  | multiplicative TOK_SLASH  unary { $$ = ast.mk_binary_op_expr(ast::BinaryOp::divide, std::move($1), std::move($3), combine(@1, @3)); }
  | multiplicative TOK_MODULO unary { $$ = ast.mk_binary_op_expr(ast::BinaryOp::modulo, std::move($1), std::move($3), combine(@1, @3)); }
  ;

unary
  : TOK_MINUS unary  %prec UMINUS { $$ = ast.mk_unary_op_expr(ast::UnaryOp::negation, $2, combine(@1,@2)); }
  | TOK_NEGATION unary %prec UPRE { $$ = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, $2, combine(@1,@2)); }
  | TOK_INC unary      %prec UPRE { $$ = ast.mk_unary_op_expr(ast::UnaryOp::preincrement, $2, combine(@1,@2)); }
  | TOK_DEC unary      %prec UPRE { $$ = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, $2, combine(@1,@2)); }
  | postfix                        { $$ = $1; }
  ;


postfix
  : primary
  | postfix TOK_LPAR arg_list_opt TOK_RPAR
    { $$ = ast.mk_call_expr(std::move($1), std::move($3), combine(@1, @4)); }
  | postfix TOK_LBRACK expr TOK_RBRACK
    { $$ = ast.mk_index(std::move($1), std::move($3), combine(@1, @4)); }
  | postfix TOK_DOT ident
    { $$ = ast.mk_field_expr(std::move($1), $3, combine(@1, @3)); }
  | postfix TOK_INC
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::postincrement, std::move($1), combine(@1, @2)); }
  | postfix TOK_DEC
    { $$ = ast.mk_unary_op_expr(ast::UnaryOp::postdecrement, std::move($1), combine(@1, @2)); }
  ;

arg_list_opt
  : /* empty */                  { $$ = std::vector<ast::Expr*>{}; }
  | arg_list                     { $$ = std::move($1);  }
  ;

arg_list
  : expr                         { std::vector<ast::Expr*> v; v.push_back(std::move($1)); $$ = std::move(v); }
  | arg_list TOK_COMMA expr      { $1.push_back(std::move($3)); $$ = std::move($1); }
  | arg_list TOK_COMMA           { $$ = std::move($1); } /* trailing comma */
  ;

int_literal_type_opt
  : /* empty */ { $$ = std::nullopt; }
  | TOK_AS TOK_I8      { $$ = kl::rt::IntKind::I8; }
  | TOK_AS TOK_U8      { $$ = kl::rt::IntKind::U8; }
  | TOK_AS TOK_I16     { $$ = kl::rt::IntKind::I16; }
  | TOK_AS TOK_U16     { $$ = kl::rt::IntKind::U16; }
  | TOK_AS TOK_I32     { $$ = kl::rt::IntKind::I32; }
  | TOK_AS TOK_U32     { $$ = kl::rt::IntKind::U32; }
  | TOK_AS TOK_I64     { $$ = kl::rt::IntKind::I64; }
  | TOK_AS TOK_U64     { $$ = kl::rt::IntKind::U64; }
  | TOK_AS TOK_I128    { $$ = kl::rt::IntKind::I128; }
  | TOK_AS TOK_U128    { $$ = kl::rt::IntKind::U128; }
  ;

float_literal_type_opt
  : /* empty */ { $$ = std::nullopt; }
  | TOK_AS TOK_F32     { $$ = kl::rt::FloatKind::F32; }
  | TOK_AS TOK_F64     { $$ = kl::rt::FloatKind::F64; }
  ;

primary
  : ident                                           { $$ = ast.mk_ref_expr($1, @1); }
  | TOK_INT_LITERAL int_literal_type_opt     { $$ = ast.mk_int_literal_expr($1, $2, @1); }
  | TOK_FLOAT_LITERAL float_literal_type_opt { $$ = ast.mk_float_literal_expr($1, $2, @1); }
  | TOK_STRING_LITERAL                              { $$ = ast.mk_str_literal_expr($1, @1); }
  | TOK_BOOL_LITERAL                                { $$ = ast.mk_bool_literal_expr($1, @1); }
  | TOK_LPAR expr TOK_RPAR                          { $$ = std::move($2); }
  | struct_lit                                      { $$ = static_cast<ast::Expr*>($1); }
  ;

struct_lit
  : path_type_expr TOK_LCBRA field_inits_opt TOK_RCBRA
    { $$ = ast.mk_obj_literal_expr($1, std::move($3), combine(@1, @4)); }
  ;

field_inits_opt
  : /* empty */        { $$ = std::vector<ast::FieldInitExpr*>{}; }
  | field_inits        { $$ = std::move($1); }
  ;

field_inits
  : field_init                           { std::vector<ast::FieldInitExpr*> v; v.push_back($1); $$ = std::move(v); }
  | field_inits TOK_COMMA field_init     { $1.push_back($3); $$ = std::move($1); }
  | field_inits TOK_COMMA                { $$ = std::move($1); } /* trailing comma */
  ;

field_init
  : ident TOK_COLON expr
    { $$ = ast.mk_field_init_expr($1, std::move($3), combine(@1, @3)); }
  ;

%%

/* Optional: yyerror, etc. You can add:
   void yy::parser::error(const lex::Loc& l, const std::string& m) { ... } */
