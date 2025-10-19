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
  #include "../generated/token.hpp"   // defines lex::Loc, lex::SymId, token enum
  #include "../types.hpp"             // kl_int, kl_double, kl_bool, etc.
  #include <memory>
  #include <vector>
  #include <string>
  #include "../ast/ast.hpp"

  class Scanner;                      // forward only (no lexer.hpp here)

  /* Keep the header light: only forward decls + pointer aliases. */
  namespace ast {
    class AST;                        // factory passed via %parse-param

    /* base node categories */
    struct Expr;          using ExprPtr      = Expr*;
    struct Statement;     using StatementPtr = Statement*;
    struct Decl;          using DeclPtr      = Decl*;
    struct Module;        using ModulePtr    = Module*;

    /* specific statements / decls used in %type */
    struct BlockStatement;
    struct VarDeclStatement;
    struct FunctionDecl;
    struct TypeAliasDecl;
    struct VarDecl;

    /* helper node used for top-level var declarators */

    /* types */
    struct Type;          using TypePtr      = Type*;
    struct PathType;      using PathTypePtr  = PathType*;

    /* params & struct field inits */
    struct ParamDecl;     using ParamDeclPtr = ParamDecl*;
    struct FieldInitExpr; using FieldInitPtr = FieldInitExpr*;
  }

  using Str = lex::SymId;
}

/* ============== DECLARATIONS PROVIDED AFTER yy::parser EXISTS ================== */
%code provides {
  yy::parser::symbol_type yylex(Scanner& scanner);
}

/* ================== IMPL-SIDE PROLOGUE (goes into parser.cpp) ================== */
%code {
  #include "../lexer/lexer.hpp"   // Scanner definition
  #include "../ast/ast.hpp"       // AST factory class declarations (mk_*)
  #include <iostream>

  void yy::parser::error(const location_type& loc, const std::string& msg) {
    std::cerr << loc.end.line << ':' << loc.end.column << ": " << msg << '\n';
  }

  yy::parser::symbol_type yylex(Scanner& scanner) {
    int rc = scanner.yylex(); // advance; fills current_token_

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
}

/* ================================== START SYMBOL ================================== */
%start translation_unit

/* =============================== TYPED TOKENS ===================================== */
%token TOK_IF TOK_WHILE TOK_DO TOK_ELSE
%token TOK_STRUCT TOK_ENUM TOK_TRAIT TOK_FN TOK_TYPE TOK_LET TOK_RETURN
%token TOK_INT TOK_BIGINT TOK_MAGICINT TOK_DOUBLE TOK_BOOL TOK_VOID TOK_STRING TOK_MUT TOK_STATIC TOK_PUB
%token TOK_BREAK TOK_CONTINUE
%token TOK_IMPORT TOK_EXPORT TOK_PACKAGE TOK_AS

%token <Str>        TOK_IDENTIFIER
%token <Str>        TOK_TYPE_NAME
%token <kl_int>     TOK_INT_LITERAL
%token <kl_float>   TOK_FLOAT_LITERAL
%token <Str>        TOK_STRING_LITERAL
%token <kl_bool>    TOK_BOOL_LITERAL

%token TOK_LPAR TOK_RPAR TOK_LBRACK TOK_RBRACK TOK_LCBRA TOK_RCBRA
%token TOK_COMMA TOK_SMCLN TOK_COLON
%token TOK_DOT TOK_QUESTION TOK_ARROW

%token TOK_NEGATION TOK_NEG TOK_INC TOK_DEC
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
%type <ast::ModulePtr>                    translation_unit

/* names & imports */
%type <Str>                               ident name
%type <std::vector<Str>>                  ident_list
%type <std::vector<Str>>                  names_separated_by_dots
%type <ast::ImportDecl*>                  import_decl
%type <std::vector<ast::ImportDecl*>>     import_list
%type <std::vector<Str>>                  opt_package
%type <int>                               maybe_export  /* 0/1 flag is easier */

/* decls */
%type <std::vector<ast::DeclPtr>>         decl_list
%type <ast::DeclPtr>                      decl
%type <ast::FunctionDecl*>                fn_decl
%type <ast::VarDecl*>                     var_decl   /* top-level var decl */
%type <ast::VarsDecl*>                    vars_decl
%type <std::vector<Str>>                  vars_group
%type <ast::DeclPtr>                      top_decl

/* types */
%type <ast::TypeSpecifier>                type_specifier_opt
%type <ast::TypeRegion>                   type_region_opt
%type <ast::TypePtr>                      type_spec ret_type
%type <ast::TypePtr>                      type_with_spec
%type <ast::FixedArrayType*>              fixed_array_type
%type <ast::BuiltinType *>                builtin_type
%type <ast::PathTypePtr>                  type_path
%type <Str>                               type_atom

/* statements */
%type <ast::StatementPtr>                 stmt
%type <ast::BlockStatement*>              block
%type <std::vector<ast::StatementPtr>>    stmt_list
%type <ast::StatementPtr>                 else_opt

/* local var decls (statement-level) */
%type <ast::VarDeclStatement*>            var_decl_stmt
%type <ast::VarsDeclStatement*>           vars_decl_stmt

/* top-level var decls (declaration-level) */

/* parameters */
%type <ast::ParamDeclPtr>                 param
%type <std::vector<ast::ParamDeclPtr>>    param_list param_list_opt

%type <std::vector<ast::FieldDecl*>>      field_decl_list field_decl_list_opt
%type <ast::FieldDecl*>                   field_decl

/* expressions */
%type <ast::ExprPtr>                      expr assign cond logic_or logic_and equality relational additive multiplicative unary postfix primary expr_opt
%type <ast::ObjLiteralExpr*>              struct_lit
%type <std::vector<ast::ExprPtr>>         arg_list arg_list_opt

/* struct literal fields */
%type <std::vector<ast::FieldInitPtr>>    field_inits field_inits_opt
%type <ast::FieldInitPtr>                 field_init

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
   import path as name;        -> alias, not public
   export import path;         -> public re-export (no alias)
   export import path as name; -> public re-export with alias */
import_decl
  : TOK_IMPORT names_separated_by_dots TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::nullopt, /*is_public*/false, combine(@1, @3)); }
  | TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($2), std::optional<lex::SymId>{$4}, /*is_public*/false, combine(@1, @5)); }
  | TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($3), std::nullopt, /*is_public*/true,  combine(@1, @4)); }
  | TOK_EXPORT TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN
    { $$ = ast.mk_import_decl(std::move($3), std::optional<lex::SymId>{$5}, /*is_public*/true,  combine(@1, @6)); }
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
  : /* empty */                    { $$ = std::vector<ast::DeclPtr>{}; }
  | decl_list decl                 { $1.push_back(std::move($2)); $$ = std::move($1); }
  ;

decl
  : maybe_export fn_decl      { $$ = static_cast<ast::DeclPtr>($2); }
  | maybe_export top_decl     { $$ = static_cast<ast::DeclPtr>($2); }
  | maybe_export struct_decl  { $$ = static_cast<ast::DeclPtr>($2); }
  ;

maybe_export
  : /* empty */   { $$ = 0; }
  | TOK_EXPORT    { $$ = 1; }
  ;

fn_decl
  : TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block
    {
      $$ = ast.mk_fn_decl($2,/*callable type*/ nullptr, std::move($4), $6, $7, combine(@1, @7));
    }
  | TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN
    {
      $$ = ast.mk_fn_decl($2, /*callable type*/ nullptr, std::move($4), $6, nullptr, combine(@1, @6)); /* prototype */
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
    : type_with_spec ident TOK_SMCLN
        { $$ = ast.mk_field_decl($2, $1, false, combine(@1, @3)); }
    | TOK_PUB type_with_spec ident TOK_SMCLN
        { $$ = ast.mk_field_decl($3, $2, true, combine(@1, @4)); }
    ;

ret_type
    : TOK_ARROW type_with_spec                { $$ = $2; }
    ;

param_list_opt
    : /* empty */                        { $$ = std::vector<ast::ParamDeclPtr>{}; }
    | param_list                         { $$ = std::move($1); }
    ;

param_list
    : param                              { std::vector<ast::ParamDeclPtr> v; v.push_back($1); $$ = std::move(v); }
    | param_list TOK_COMMA param         { $1.push_back($3); $$ = std::move($1); }
    | param_list TOK_COMMA               { $$ = std::move($1); } /* trailing comma */
    ;

param
    : type_with_spec ident                { $$ = ast.mk_param_decl($2, $1, combine(@1, @2)); }
    ;


/* ================================= types ==================================== */

type_specifier_opt
    :
    { $$ = ast::TypeSpecifier::Imm; }
    | TOK_MUT
    { $$ = ast::TypeSpecifier::Mut; }
    ;

type_region_opt
    :
    { $$ = ast::TypeRegion::Auto; }
    | TOK_STATIC
    { $$ = ast::TypeRegion::Static; }
    ;

type_with_spec
    : type_specifier_opt type_spec
    { $2->specifier = $1; $$ = $2; }
    ;

type_spec
  : builtin_type      { $$ = static_cast<ast::TypePtr>($1); }
  | type_path         { $$ = static_cast<ast::TypePtr>(ast.mk_type_from_path($1, @1)); }
  | fixed_array_type  { $$ = static_cast<ast::TypePtr>($1); }
  ;

builtin_type
  : TOK_INT       { $$ = ast.mk_builtin_type(ast::BuiltinTy::Int, @1); }
  | TOK_BIGINT    { $$ = ast.mk_builtin_type(ast::BuiltinTy::BigInt, @1); }
  | TOK_MAGICINT  { $$ = ast.mk_builtin_type(ast::BuiltinTy::MagicInt, @1); }
  | TOK_DOUBLE    { $$ = ast.mk_builtin_type(ast::BuiltinTy::Double, @1); }
  | TOK_BOOL      { $$ = ast.mk_builtin_type(ast::BuiltinTy::Bool, @1); }
  | TOK_VOID      { $$ = ast.mk_builtin_type(ast::BuiltinTy::Void, @1); }
  | TOK_STRING    { $$ = ast.mk_builtin_type(ast::BuiltinTy::String, @1); }
  ;

type_path
  : type_atom
    { $$ = ast.mk_type_path_single($1, @1); }
  | type_path TOK_DOT type_atom
    { $$ = ast.mk_type_path_append($1, $3, combine(@1, @3)); }
  ;

type_atom
  : TOK_IDENTIFIER    { $$ = std::move($1); } /* keep until lexer distinguishes */
  ;

fixed_array_type
    : type_spec TOK_LBRACK TOK_INT_LITERAL TOK_RBRACK
    { $$ = ast.mk_fixed_array_type($1, $3, combine(@1, @3)); }
    ;

ident
  : TOK_IDENTIFIER    { $$ = std::move($1); }
  ;

ident_list
    : ident                        { $$ = std::vector<Str>(std::move($1)); }
    | ident_list TOK_COMMA ident   { $1.push_back(std::move($3)); $$ = std::move($1); }
    ;

/* =============================== statements ================================= */

block
  : TOK_LCBRA stmt_list TOK_RCBRA
    { $$ = ast.mk_block_stmt(std::move($2), combine(@1, @2)); }
  ;

stmt_list
  : /* empty */               { $$ = std::vector<ast::StatementPtr>{}; }
  | stmt_list stmt            { $1.push_back(std::move($2)); $$ = std::move($1); }
  ;

stmt
  : var_decl_stmt                         { $$ = static_cast<ast::StatementPtr>($1); }
  | vars_decl_stmt                        { $$ = static_cast<ast::StatementPtr>($1); }
  | TOK_RETURN expr_opt TOK_SMCLN         { $$ = ast.mk_return_stmt($2, @1); }
  | TOK_IF TOK_LPAR expr TOK_RPAR stmt
      { $$ = ast.mk_if_stmt($3, $5, combine(@1, @5)); }
  | TOK_WHILE TOK_LPAR expr TOK_RPAR block
      { $$ = ast.mk_while_stmt($3, $5, combine(@1, @5)); }
  | TOK_DO block TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN
      { $$ = ast.mk_do_while_stmt($5, $2, combine(@1, @7)); }
  | TOK_BREAK TOK_SMCLN                   { $$ = ast.mk_break_stmt(combine(@1, @2)); }
  | TOK_CONTINUE TOK_SMCLN                { $$ = ast.mk_continue_stmt(combine(@1, @2)); }
  | block                                 { $$ = static_cast<ast::StatementPtr>($1); }
  | expr TOK_SMCLN                        { $$ = ast.mk_expr_stmt($1, combine(@1, @2)); }
  ;

else_opt
  : /* empty */   { $$ = nullptr; }
  | TOK_ELSE stmt { $$ = std::move($2); }
  ;

expr_opt
  : /* empty */   { $$ = nullptr; }
  | expr          { $$ = std::move($1); }
  ;

/* ================== local (statement-level) var declarations ================== */
/* let T a, b=1; — typed mid-rule ($0) threads the type to declarators. */

var_decl_stmt
  : TOK_LET var_decl
    { $$ = ast.mk_var_decl_stmt($2, @2); }
  ;

vars_decl_stmt
  : TOK_LET vars_decl
  { $$ = ast.mk_vars_decl_stmt($2, @2); }
;

/* ================== top-level (declaration-level) var declarations ============ */

vars_group
  : TOK_LPAR ident_list TOK_RPAR
    { $$ = std::move($2); }
  ;

top_decl
  : TOK_LET var_decl      { $$ = static_cast<ast::DeclPtr>($2); }
  | TOK_LET vars_decl     { $$ = static_cast<ast::DeclPtr>($2); }
  ;

vars_decl
  : type_region_opt type_with_spec vars_group TOK_SMCLN
    {
      // No initializers
      $$ = ast.mk_vars_decl(/*names*/std::move($3),
                            /*assignments*/std::vector<ast::ExprPtr>{},
                            /*type*/$2,
                            /*region*/$1,
                            /*range*/combine(@1, @3));
    }
  | type_region_opt type_with_spec vars_group TOK_ASSIGN arg_list_opt TOK_SMCLN
    {
      // Initializers: either empty, one expr, or N exprs
      $$ = ast.mk_vars_decl(/*names*/std::move($3),
                            /*assignments*/std::move($5),
                            /*type*/$2,
                            /*region*/$1,
                            /*range*/combine(@1, @3));
    }
  ;

var_decl
  : type_region_opt type_with_spec ident TOK_SMCLN
    {
      auto decl = ast.mk_var_declarator_expr($3, nullptr, @3);
      $$ = ast.mk_var_decl(std::move(decl), $2, $1, combine(@1, @3));
    }
  | type_region_opt type_with_spec ident TOK_ASSIGN assign TOK_SMCLN
    {
      auto decl = ast.mk_var_declarator_expr($3, std::move($5), combine(@3, @5));
      $$ = ast.mk_var_decl(std::move(decl), $2, $1, combine(@1, @5));
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
  : TOK_NEG       unary  %prec UMINUS { $$ = ast.mk_unary_op_expr(ast::UnaryOp::negation, std::move($2), combine(@1, @2)); }
  | TOK_NEGATION  unary  %prec UPRE   { $$ = ast.mk_unary_op_expr(ast::UnaryOp::logical_not, std::move($2), combine(@1, @2)); }
  | TOK_INC       unary  %prec UPRE   { $$ = ast.mk_unary_op_expr(ast::UnaryOp::preincrement,  std::move($2), combine(@1, @2)); }
  | TOK_DEC       unary  %prec UPRE   { $$ = ast.mk_unary_op_expr(ast::UnaryOp::predecrement, std::move($2), combine(@1, @2)); }
  | postfix                           { $$ = std::move($1); }
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
  : /* empty */                  { $$ = std::vector<ast::ExprPtr>{}; }
  | arg_list                     { $$ = std::move($1);  }
  ;

arg_list
  : expr                         { std::vector<ast::ExprPtr> v; v.push_back(std::move($1)); $$ = std::move(v); }
  | arg_list TOK_COMMA expr      { $1.push_back(std::move($3)); $$ = std::move($1); }
  | arg_list TOK_COMMA           { $$ = std::move($1); } /* trailing comma */
  ;

primary
  : ident                  { $$ = ast.mk_ref_expr($1, @1); }
  | TOK_INT_LITERAL        { $$ = ast.mk_int_literal_expr($1, @1); }
  | TOK_FLOAT_LITERAL      { $$ = ast.mk_float_literal_expr($1, @1); }
  | TOK_STRING_LITERAL     { $$ = ast.mk_str_literal_expr($1, @1); }
  | TOK_BOOL_LITERAL       { $$ = ast.mk_bool_literal_expr($1, @1); }
  | TOK_LPAR expr TOK_RPAR { $$ = std::move($2); }
  | struct_lit             { $$ = static_cast<ast::ExprPtr>($1); }
  ;

struct_lit
  : type_path TOK_LCBRA field_inits_opt TOK_RCBRA
    { $$ = ast.mk_obj_literal_expr($1, std::move($3), combine(@1, @4)); }
  ;

field_inits_opt
  : /* empty */        { $$ = std::vector<ast::FieldInitPtr>{}; }
  | field_inits        { $$ = std::move($1); }
  ;

field_inits
  : field_init                           { std::vector<ast::FieldInitPtr> v; v.push_back($1); $$ = std::move(v); }
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
