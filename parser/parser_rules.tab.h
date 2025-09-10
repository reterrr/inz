/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_RULES_TAB_H_INCLUDED
# define YY_YY_PARSER_RULES_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 11 "parser_rules.y"

  #include "../generated/token.hpp"   // lex::Loc, lex::SymId
  #include <string>
  #include <vector>
  #include <memory>

  using namespace lex;

  // If you use these in %token/%type, they must be visible here:
  using Str = lex::SymId;

  class Scanner;
  namespace yy { class parser; }   // forward-declare the parser class
  yy::parser::symbol_type yylex(Scanner& scanner);  // ⬅️ declaration

  #include <location.hh>

  // If you referenced kl_* in your %token types, define them (or stop using them):
  //using kl_bool   = bool;
  //using kl_double = double;
  //using kl_int    = long long;   // or int64_t
  //using kl_string = Str;

  namespace ast {
    struct Expr;        using ExprPtr      = Expr*;
    struct Statement;   using StatementPtr = Statement*;
    struct Type;        using TypePtr      = Type*;
    struct PathType;
    struct ParamDecl;   // forward decl is OK if you only pass pointers

    // If FieldInitExpr is a semantic value **by value**, give a full def here.
    struct FieldInitExpr { std::string name; ExprPtr value; lex::Loc loc; };
  }

  // If you insist on semantic values like std::vector<ast::ParamDecl> (by value),
  // you MUST also include its full definition here:
  #include "../ast/nodes/decl/param_decl.hpp"
  #include "../types.hpp"

#line 89 "parser_rules.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_IF = 258,                  /* TOK_IF  */
    TOK_WHILE = 259,               /* TOK_WHILE  */
    TOK_DO = 260,                  /* TOK_DO  */
    TOK_ELSE = 261,                /* TOK_ELSE  */
    TOK_STRUCT = 262,              /* TOK_STRUCT  */
    TOK_TRAIT = 263,               /* TOK_TRAIT  */
    TOK_ENUM = 264,                /* TOK_ENUM  */
    TOK_FN = 265,                  /* TOK_FN  */
    TOK_TYPE = 266,                /* TOK_TYPE  */
    TOK_LET = 267,                 /* TOK_LET  */
    TOK_RETURN = 268,              /* TOK_RETURN  */
    TOK_INT = 269,                 /* TOK_INT  */
    TOK_BIGINT = 270,              /* TOK_BIGINT  */
    TOK_MAGICINT = 271,            /* TOK_MAGICINT  */
    TOK_DOUBLE = 272,              /* TOK_DOUBLE  */
    TOK_BOOL = 273,                /* TOK_BOOL  */
    TOK_VOID = 274,                /* TOK_VOID  */
    TOK_STRING = 275,              /* TOK_STRING  */
    TOK_BREAK = 276,               /* TOK_BREAK  */
    TOK_CONTINUE = 277,            /* TOK_CONTINUE  */
    TOK_IMPORT = 278,              /* TOK_IMPORT  */
    TOK_EXPORT = 279,              /* TOK_EXPORT  */
    TOK_PACKAGE = 280,             /* TOK_PACKAGE  */
    TOK_AS = 281,                  /* TOK_AS  */
    TOK_IDENTIFIER = 282,          /* TOK_IDENTIFIER  */
    TOK_TYPE_NAME = 283,           /* TOK_TYPE_NAME  */
    TOK_INT_LITERAL = 284,         /* TOK_INT_LITERAL  */
    TOK_FLOAT_LITERAL = 285,       /* TOK_FLOAT_LITERAL  */
    TOK_STRING_LITERAL = 286,      /* TOK_STRING_LITERAL  */
    TOK_BOOL_LITERAL = 287,        /* TOK_BOOL_LITERAL  */
    TOK_LPAR = 288,                /* TOK_LPAR  */
    TOK_RPAR = 289,                /* TOK_RPAR  */
    TOK_LBRACK = 290,              /* TOK_LBRACK  */
    TOK_RBRACK = 291,              /* TOK_RBRACK  */
    TOK_LCBRA = 292,               /* TOK_LCBRA  */
    TOK_RCBRA = 293,               /* TOK_RCBRA  */
    TOK_COMMA = 294,               /* TOK_COMMA  */
    TOK_SMCLN = 295,               /* TOK_SMCLN  */
    TOK_COLON = 296,               /* TOK_COLON  */
    TOK_DOT = 297,                 /* TOK_DOT  */
    TOK_QUESTION = 298,            /* TOK_QUESTION  */
    TOK_ARROW = 299,               /* TOK_ARROW  */
    TOK_NEGATION = 300,            /* TOK_NEGATION  */
    TOK_NEG = 301,                 /* TOK_NEG  */
    TOK_INC = 302,                 /* TOK_INC  */
    TOK_DEC = 303,                 /* TOK_DEC  */
    TOK_STAR = 304,                /* TOK_STAR  */
    TOK_SLASH = 305,               /* TOK_SLASH  */
    TOK_MODULO = 306,              /* TOK_MODULO  */
    TOK_PLUS = 307,                /* TOK_PLUS  */
    TOK_MINUS = 308,               /* TOK_MINUS  */
    TOK_LESS = 309,                /* TOK_LESS  */
    TOK_LEQ = 310,                 /* TOK_LEQ  */
    TOK_GREATER = 311,             /* TOK_GREATER  */
    TOK_GEQ = 312,                 /* TOK_GEQ  */
    TOK_EQUAL = 313,               /* TOK_EQUAL  */
    TOK_NEQUAL = 314,              /* TOK_NEQUAL  */
    TOK_BOOL_AND = 315,            /* TOK_BOOL_AND  */
    TOK_BOOL_OR = 316,             /* TOK_BOOL_OR  */
    TOK_ASSIGN = 317,              /* TOK_ASSIGN  */
    TOK_PLUS_ASSIGN = 318,         /* TOK_PLUS_ASSIGN  */
    TOK_MIN_ASSIGN = 319,          /* TOK_MIN_ASSIGN  */
    TOK_MUL_ASSIGN = 320,          /* TOK_MUL_ASSIGN  */
    TOK_DIV_ASSIGN = 321,          /* TOK_DIV_ASSIGN  */
    TERNARY = 322,                 /* TERNARY  */
    UMINUS = 323,                  /* UMINUS  */
    UPRE = 324                     /* UPRE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (Scanner& scanner);


#endif /* !YY_YY_PARSER_RULES_TAB_H_INCLUDED  */
