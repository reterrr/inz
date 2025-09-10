/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser_rules.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_IF = 3,                     /* TOK_IF  */
  YYSYMBOL_TOK_WHILE = 4,                  /* TOK_WHILE  */
  YYSYMBOL_TOK_DO = 5,                     /* TOK_DO  */
  YYSYMBOL_TOK_ELSE = 6,                   /* TOK_ELSE  */
  YYSYMBOL_TOK_STRUCT = 7,                 /* TOK_STRUCT  */
  YYSYMBOL_TOK_TRAIT = 8,                  /* TOK_TRAIT  */
  YYSYMBOL_TOK_ENUM = 9,                   /* TOK_ENUM  */
  YYSYMBOL_TOK_FN = 10,                    /* TOK_FN  */
  YYSYMBOL_TOK_TYPE = 11,                  /* TOK_TYPE  */
  YYSYMBOL_TOK_LET = 12,                   /* TOK_LET  */
  YYSYMBOL_TOK_RETURN = 13,                /* TOK_RETURN  */
  YYSYMBOL_TOK_INT = 14,                   /* TOK_INT  */
  YYSYMBOL_TOK_BIGINT = 15,                /* TOK_BIGINT  */
  YYSYMBOL_TOK_MAGICINT = 16,              /* TOK_MAGICINT  */
  YYSYMBOL_TOK_DOUBLE = 17,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_BOOL = 18,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_VOID = 19,                  /* TOK_VOID  */
  YYSYMBOL_TOK_STRING = 20,                /* TOK_STRING  */
  YYSYMBOL_TOK_BREAK = 21,                 /* TOK_BREAK  */
  YYSYMBOL_TOK_CONTINUE = 22,              /* TOK_CONTINUE  */
  YYSYMBOL_TOK_IMPORT = 23,                /* TOK_IMPORT  */
  YYSYMBOL_TOK_EXPORT = 24,                /* TOK_EXPORT  */
  YYSYMBOL_TOK_PACKAGE = 25,               /* TOK_PACKAGE  */
  YYSYMBOL_TOK_AS = 26,                    /* TOK_AS  */
  YYSYMBOL_TOK_IDENTIFIER = 27,            /* TOK_IDENTIFIER  */
  YYSYMBOL_TOK_TYPE_NAME = 28,             /* TOK_TYPE_NAME  */
  YYSYMBOL_TOK_INT_LITERAL = 29,           /* TOK_INT_LITERAL  */
  YYSYMBOL_TOK_FLOAT_LITERAL = 30,         /* TOK_FLOAT_LITERAL  */
  YYSYMBOL_TOK_STRING_LITERAL = 31,        /* TOK_STRING_LITERAL  */
  YYSYMBOL_TOK_BOOL_LITERAL = 32,          /* TOK_BOOL_LITERAL  */
  YYSYMBOL_TOK_LPAR = 33,                  /* TOK_LPAR  */
  YYSYMBOL_TOK_RPAR = 34,                  /* TOK_RPAR  */
  YYSYMBOL_TOK_LBRACK = 35,                /* TOK_LBRACK  */
  YYSYMBOL_TOK_RBRACK = 36,                /* TOK_RBRACK  */
  YYSYMBOL_TOK_LCBRA = 37,                 /* TOK_LCBRA  */
  YYSYMBOL_TOK_RCBRA = 38,                 /* TOK_RCBRA  */
  YYSYMBOL_TOK_COMMA = 39,                 /* TOK_COMMA  */
  YYSYMBOL_TOK_SMCLN = 40,                 /* TOK_SMCLN  */
  YYSYMBOL_TOK_COLON = 41,                 /* TOK_COLON  */
  YYSYMBOL_TOK_DOT = 42,                   /* TOK_DOT  */
  YYSYMBOL_TOK_QUESTION = 43,              /* TOK_QUESTION  */
  YYSYMBOL_TOK_ARROW = 44,                 /* TOK_ARROW  */
  YYSYMBOL_TOK_NEGATION = 45,              /* TOK_NEGATION  */
  YYSYMBOL_TOK_NEG = 46,                   /* TOK_NEG  */
  YYSYMBOL_TOK_INC = 47,                   /* TOK_INC  */
  YYSYMBOL_TOK_DEC = 48,                   /* TOK_DEC  */
  YYSYMBOL_TOK_STAR = 49,                  /* TOK_STAR  */
  YYSYMBOL_TOK_SLASH = 50,                 /* TOK_SLASH  */
  YYSYMBOL_TOK_MODULO = 51,                /* TOK_MODULO  */
  YYSYMBOL_TOK_PLUS = 52,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 53,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_LESS = 54,                  /* TOK_LESS  */
  YYSYMBOL_TOK_LEQ = 55,                   /* TOK_LEQ  */
  YYSYMBOL_TOK_GREATER = 56,               /* TOK_GREATER  */
  YYSYMBOL_TOK_GEQ = 57,                   /* TOK_GEQ  */
  YYSYMBOL_TOK_EQUAL = 58,                 /* TOK_EQUAL  */
  YYSYMBOL_TOK_NEQUAL = 59,                /* TOK_NEQUAL  */
  YYSYMBOL_TOK_BOOL_AND = 60,              /* TOK_BOOL_AND  */
  YYSYMBOL_TOK_BOOL_OR = 61,               /* TOK_BOOL_OR  */
  YYSYMBOL_TOK_ASSIGN = 62,                /* TOK_ASSIGN  */
  YYSYMBOL_TOK_PLUS_ASSIGN = 63,           /* TOK_PLUS_ASSIGN  */
  YYSYMBOL_TOK_MIN_ASSIGN = 64,            /* TOK_MIN_ASSIGN  */
  YYSYMBOL_TOK_MUL_ASSIGN = 65,            /* TOK_MUL_ASSIGN  */
  YYSYMBOL_TOK_DIV_ASSIGN = 66,            /* TOK_DIV_ASSIGN  */
  YYSYMBOL_TERNARY = 67,                   /* TERNARY  */
  YYSYMBOL_UMINUS = 68,                    /* UMINUS  */
  YYSYMBOL_UPRE = 69,                      /* UPRE  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_translation_unit = 71,          /* translation_unit  */
  YYSYMBOL_opt_package = 72,               /* opt_package  */
  YYSYMBOL_import_list = 73,               /* import_list  */
  YYSYMBOL_import_decl = 74,               /* import_decl  */
  YYSYMBOL_names_separated_by_dots = 75,   /* names_separated_by_dots  */
  YYSYMBOL_name = 76,                      /* name  */
  YYSYMBOL_decl_list = 77,                 /* decl_list  */
  YYSYMBOL_decl = 78,                      /* decl  */
  YYSYMBOL_maybe_export = 79,              /* maybe_export  */
  YYSYMBOL_fn_decl = 80,                   /* fn_decl  */
  YYSYMBOL_param_list_opt = 81,            /* param_list_opt  */
  YYSYMBOL_param_list = 82,                /* param_list  */
  YYSYMBOL_param = 83,                     /* param  */
  YYSYMBOL_ret_type = 84,                  /* ret_type  */
  YYSYMBOL_type_alias = 85,                /* type_alias  */
  YYSYMBOL_type_spec = 86,                 /* type_spec  */
  YYSYMBOL_builtin_type = 87,              /* builtin_type  */
  YYSYMBOL_type_path = 88,                 /* type_path  */
  YYSYMBOL_type_atom = 89,                 /* type_atom  */
  YYSYMBOL_ident = 90,                     /* ident  */
  YYSYMBOL_block = 91,                     /* block  */
  YYSYMBOL_stmt_list = 92,                 /* stmt_list  */
  YYSYMBOL_stmt = 93,                      /* stmt  */
  YYSYMBOL_else_opt = 94,                  /* else_opt  */
  YYSYMBOL_expr_opt = 95,                  /* expr_opt  */
  YYSYMBOL_var_decl = 96,                  /* var_decl  */
  YYSYMBOL_init_declarator_list = 97,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 98,           /* init_declarator  */
  YYSYMBOL_expr = 99,                      /* expr  */
  YYSYMBOL_assign = 100,                   /* assign  */
  YYSYMBOL_cond = 101,                     /* cond  */
  YYSYMBOL_logic_or = 102,                 /* logic_or  */
  YYSYMBOL_logic_and = 103,                /* logic_and  */
  YYSYMBOL_equality = 104,                 /* equality  */
  YYSYMBOL_relational = 105,               /* relational  */
  YYSYMBOL_additive = 106,                 /* additive  */
  YYSYMBOL_multiplicative = 107,           /* multiplicative  */
  YYSYMBOL_unary = 108,                    /* unary  */
  YYSYMBOL_postfix = 109,                  /* postfix  */
  YYSYMBOL_arg_list_opt = 110,             /* arg_list_opt  */
  YYSYMBOL_arg_list = 111,                 /* arg_list  */
  YYSYMBOL_primary = 112,                  /* primary  */
  YYSYMBOL_struct_lit = 113,               /* struct_lit  */
  YYSYMBOL_field_inits_opt = 114,          /* field_inits_opt  */
  YYSYMBOL_field_inits = 115,              /* field_inits  */
  YYSYMBOL_field_init = 116                /* field_init  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 52 "parser_rules.y"

  #include "../ast/nodes/decl/param_decl.hpp"  // only if parser.cc needs it
  #include "../ast/nodes/type/type.hpp"
  #include "../types.hpp"

  using Str = lex::SymId;

  // statements
  ast::StatementPtr mk_block_stmt(std::vector<ast::StatementPtr>&&, const lex::Loc&);
  ast::StatementPtr mk_return_stmt(ast::ExprPtr, const lex::Loc&);
  ast::StatementPtr mk_if_stmt(ast::ExprPtr, ast::StatementPtr, ast::StatementPtr, const lex::Loc&);
  ast::StatementPtr mk_while_stmt(ast::ExprPtr, ast::StatementPtr, const lex::Loc&);
  ast::StatementPtr mk_do_while_stmt(ast::StatementPtr, ast::ExprPtr, const lex::Loc&);
  ast::StatementPtr mk_break_stmt(const lex::Loc&);
  ast::StatementPtr mk_continue_stmt(const lex::Loc&);

  // decls
  ast::StatementPtr mk_fn_decl(const Str& name,
                               std::vector<ast::ParamDecl*>&& params, // <-- pointer, see note below
                               ast::TypePtr ret_type,
                               ast::StatementPtr body,
                               const lex::Loc& loc);
  ast::StatementPtr mk_var_decl(ast::TypePtr, Str, ast::ExprPtr, const lex::Loc&);

  // expressions
  ast::ExprPtr mk_ref_expr(const Str&, const lex::Loc&);
  ast::ExprPtr mk_int_literal_expr(long long, const lex::Loc&);
  ast::ExprPtr mk_float_literal_expr(double, const lex::Loc&);
  ast::ExprPtr mk_str_literal_expr(const Str&, const lex::Loc&);
  ast::ExprPtr mk_bool_literal_expr(bool, const lex::Loc&);
  ast::ExprPtr mk_call_expr(ast::ExprPtr, std::vector<ast::ExprPtr>&&, const lex::Loc&);
  ast::ExprPtr mk_index_expr(ast::ExprPtr, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_field_expr(ast::ExprPtr, const Str&, const lex::Loc&);
  ast::ExprPtr mk_postfix_incdec_expr(ast::ExprPtr, bool, const lex::Loc&);
  ast::ExprPtr mk_prefix_incdec_expr(ast::ExprPtr, bool, const lex::Loc&);
  ast::ExprPtr mk_unary_expr_neg(ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_unary_expr_not(ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_binary_expr(ast::ExprPtr, int, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_assign_expr(ast::ExprPtr, int, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_cond_expr(ast::ExprPtr, ast::ExprPtr, ast::ExprPtr, const lex::Loc&);
  ast::ExprPtr mk_struct_literal_expr(ast::PathType,
                                      std::vector<ast::FieldInitExpr *>&&, const lex::Loc&);
  ast::ExprPtr mk_field_init(const Str&, ast::ExprPtr, const lex::Loc&);

  // types
  ast::TypePtr mk_builtin_type(int, const lex::Loc&);
  ast::TypePtr mk_array_type(ast::TypePtr, const lex::Loc&);
  ast::TypePtr mk_type_from_path(const ast::PathType&, const lex::Loc&);

#line 270 "parser_rules.tab.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  123
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   191,   191,   199,   200,   208,   209,   217,   222,   229,
     231,   236,   243,   244,   249,   250,   251,   252,   256,   257,
     263,   267,   275,   276,   280,   282,   284,   289,   298,   302,
     312,   313,   314,   319,   320,   321,   322,   323,   324,   325,
     329,   335,   344,   345,   349,   355,   361,   362,   367,   368,
     370,   372,   374,   376,   378,   380,   381,   390,   391,   395,
     396,   401,   412,   414,   419,   421,   435,   439,   440,   441,
     442,   443,   444,   448,   449,   454,   455,   460,   461,   466,
     467,   469,   474,   475,   476,   477,   478,   482,   483,   484,
     488,   489,   490,   491,   495,   496,   497,   498,   499,   503,
     504,   506,   508,   510,   512,   517,   518,   522,   523,   524,
     528,   530,   532,   534,   536,   538,   540,   544,   550,   551,
     555,   557,   559,   564
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IF", "TOK_WHILE",
  "TOK_DO", "TOK_ELSE", "TOK_STRUCT", "TOK_TRAIT", "TOK_ENUM", "TOK_FN",
  "TOK_TYPE", "TOK_LET", "TOK_RETURN", "TOK_INT", "TOK_BIGINT",
  "TOK_MAGICINT", "TOK_DOUBLE", "TOK_BOOL", "TOK_VOID", "TOK_STRING",
  "TOK_BREAK", "TOK_CONTINUE", "TOK_IMPORT", "TOK_EXPORT", "TOK_PACKAGE",
  "TOK_AS", "TOK_IDENTIFIER", "TOK_TYPE_NAME", "TOK_INT_LITERAL",
  "TOK_FLOAT_LITERAL", "TOK_STRING_LITERAL", "TOK_BOOL_LITERAL",
  "TOK_LPAR", "TOK_RPAR", "TOK_LBRACK", "TOK_RBRACK", "TOK_LCBRA",
  "TOK_RCBRA", "TOK_COMMA", "TOK_SMCLN", "TOK_COLON", "TOK_DOT",
  "TOK_QUESTION", "TOK_ARROW", "TOK_NEGATION", "TOK_NEG", "TOK_INC",
  "TOK_DEC", "TOK_STAR", "TOK_SLASH", "TOK_MODULO", "TOK_PLUS",
  "TOK_MINUS", "TOK_LESS", "TOK_LEQ", "TOK_GREATER", "TOK_GEQ",
  "TOK_EQUAL", "TOK_NEQUAL", "TOK_BOOL_AND", "TOK_BOOL_OR", "TOK_ASSIGN",
  "TOK_PLUS_ASSIGN", "TOK_MIN_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TERNARY", "UMINUS", "UPRE", "$accept", "translation_unit",
  "opt_package", "import_list", "import_decl", "names_separated_by_dots",
  "name", "decl_list", "decl", "maybe_export", "fn_decl", "param_list_opt",
  "param_list", "param", "ret_type", "type_alias", "type_spec",
  "builtin_type", "type_path", "type_atom", "ident", "block", "stmt_list",
  "stmt", "else_opt", "expr_opt", "var_decl", "init_declarator_list",
  "init_declarator", "expr", "assign", "cond", "logic_or", "logic_and",
  "equality", "relational", "additive", "multiplicative", "unary",
  "postfix", "arg_list_opt", "arg_list", "primary", "struct_lit",
  "field_inits_opt", "field_inits", "field_init", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-108)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,    -3,    19,  -108,  -108,   -29,  -108,  -108,    12,  -108,
      -3,    -3,  -108,     5,  -108,    50,  -108,  -108,   108,    -3,
    -108,    60,    60,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,   231,  -108,  -108,    60,  -108,    49,  -108,  -108,
      53,  -108,    66,    48,    81,    67,    29,  -108,    70,  -108,
     231,   231,  -108,   134,    60,  -108,  -108,    68,    92,  -108,
      60,    93,    40,  -108,  -108,  -108,  -108,   134,   134,   134,
     134,   134,    44,  -108,  -108,  -108,   -35,    77,    21,    52,
      51,   -12,  -108,   -17,  -108,  -108,  -108,    94,   231,  -108,
    -108,   106,  -108,  -108,    97,  -108,  -108,  -108,    60,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,    60,  -108,  -108,   134,   134,
     134,   134,   134,   231,   -30,  -108,  -108,   101,   109,   107,
    -108,   112,    77,    21,    52,    52,    51,    51,    51,    51,
     -12,   -12,  -108,  -108,  -108,  -108,   120,   117,   121,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,   134,
    -108,    60,   134,  -108,   134,  -108,   171,  -108,  -108,  -108,
    -108,   125,   126,   207,   134,   128,   129,  -108,    44,  -108,
    -108,  -108,   130,   134,   134,   156,   131,  -108,  -108,  -108,
    -108,   138,   139,   161,  -108,   207,   207,   134,   189,  -108,
     162,   207,  -108,   157,  -108,  -108
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     5,    11,     0,     9,     1,    12,     4,
       0,     0,     6,    18,    10,     0,    19,    13,    17,     0,
       7,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      43,    42,     0,    14,    15,     0,    30,    31,    40,    16,
       0,    44,     0,     0,     0,    64,     0,    62,     0,     8,
      22,     0,    32,     0,     0,    61,    41,     0,    23,    24,
       0,     0,    44,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,   110,    65,    67,    73,    75,    77,    79,
      82,    87,    90,    98,    99,   116,    63,     0,    26,    27,
      29,     0,    66,    95,    98,    94,    96,    97,   118,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   103,   104,     0,     0,
       0,     0,     0,     0,     0,    25,   115,     0,     0,   119,
     120,     0,    76,    78,    80,    81,    83,    84,    85,    86,
      88,    89,    91,    92,    93,   107,     0,   106,     0,   102,
      68,    69,    70,    71,    72,    28,    46,    21,    20,     0,
     117,   122,     0,   100,   109,   101,     0,   123,   121,    74,
     108,     0,     0,     0,    59,     0,     0,    45,    31,    55,
      47,    48,     0,     0,     0,     0,     0,    60,    53,    54,
      56,     0,     0,     0,    49,     0,     0,     0,    57,    51,
       0,     0,    50,     0,    58,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,  -108,   194,    -7,  -108,  -108,  -108,
    -108,  -108,  -108,   119,  -108,  -108,   -23,  -108,   -18,   165,
     -20,    90,  -108,  -107,  -108,  -108,   197,  -108,   176,   -63,
     -47,    69,  -108,   132,   140,    10,    45,     7,   -27,   -48,
    -108,  -108,  -108,  -108,  -108,  -108,    72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     8,    12,     5,     6,    13,    17,    18,
      33,    57,    58,    59,   124,    34,    35,    36,    72,    38,
      73,   179,   166,   180,   202,   186,   181,    46,    47,   182,
      92,    75,    76,    77,    78,    79,    80,    81,    82,    83,
     146,   147,    84,    85,   128,   129,   130
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,    42,    43,    14,    91,    -2,    74,   156,    99,    44,
     157,     9,    40,    10,    37,    45,   113,     1,   114,     7,
      94,    94,    94,    94,     4,   115,   100,    60,    61,    16,
     116,   117,    37,    37,    45,    11,   131,   110,   111,   112,
      89,    93,    95,    96,    97,   118,   119,   120,   121,   122,
     145,   148,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    60,   185,   -43,    54,    55,
      37,   150,   151,   152,   153,   154,    19,   -43,   127,   102,
     103,    98,   -43,   142,   143,   144,    48,    41,   198,   199,
      20,    48,    10,    49,   204,   149,   167,    30,    31,    50,
     155,   170,    87,   108,   109,    37,   104,   105,   106,   107,
      51,   187,   134,   135,    94,   140,   141,    52,    21,    22,
     191,   192,    23,    24,    25,    26,    27,    28,    29,    53,
     113,    88,   114,    90,   200,    30,    31,   101,   123,   115,
     126,   127,   159,    32,   116,   117,   161,   160,   178,   136,
     137,   138,   139,   162,   163,   178,   164,   165,   183,   184,
     193,    62,    31,    63,    64,    65,    66,    67,   188,   189,
     190,   194,   195,   196,   171,   172,   173,   178,   178,    68,
      69,    70,    71,   178,   174,    23,    24,    25,    26,    27,
      28,    29,   175,   176,   197,   201,   203,   205,    62,    31,
      63,    64,    65,    66,    67,    15,    32,   125,   156,   177,
     171,   172,   173,    56,   158,    39,    68,    69,    70,    71,
     174,    23,    24,    25,    26,    27,    28,    29,   175,   176,
      86,   169,   132,   168,    62,    31,    63,    64,    65,    66,
      67,   133,    32,     0,   156,    23,    24,    25,    26,    27,
      28,    29,    68,    69,    70,    71,     0,     0,    30,    31,
       0,     0,     0,     0,     0,     0,    32
};

static const yytype_int16 yycheck[] =
{
      18,    21,    22,    10,    67,     0,    53,    37,    43,    32,
      40,    40,    19,    42,    32,    35,    33,    25,    35,     0,
      68,    69,    70,    71,    27,    42,    61,    50,    51,    24,
      47,    48,    50,    51,    54,    23,    99,    49,    50,    51,
      60,    68,    69,    70,    71,    62,    63,    64,    65,    66,
     113,   114,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    88,   173,    27,    39,    40,
      88,   118,   119,   120,   121,   122,    26,    37,    98,    58,
      59,    37,    42,   110,   111,   112,    42,    27,   195,   196,
      40,    42,    42,    40,   201,   115,   159,    27,    28,    33,
     123,   164,    34,    52,    53,   123,    54,    55,    56,    57,
      62,   174,   102,   103,   162,   108,   109,    36,    10,    11,
     183,   184,    14,    15,    16,    17,    18,    19,    20,    62,
      33,    39,    35,    40,   197,    27,    28,    60,    44,    42,
      34,   161,    41,    35,    47,    48,    39,    38,   166,   104,
     105,   106,   107,    41,    34,   173,    39,    36,    33,    33,
       4,    27,    28,    29,    30,    31,    32,    33,    40,    40,
      40,    40,    34,    34,     3,     4,     5,   195,   196,    45,
      46,    47,    48,   201,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    33,     6,    34,    40,    27,    28,
      29,    30,    31,    32,    33,    11,    35,    88,    37,    38,
       3,     4,     5,    48,   124,    18,    45,    46,    47,    48,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      54,   162,   100,   161,    27,    28,    29,    30,    31,    32,
      33,   101,    35,    -1,    37,    14,    15,    16,    17,    18,
      19,    20,    45,    46,    47,    48,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    71,    72,    27,    75,    76,     0,    73,    40,
      42,    23,    74,    77,    76,    75,    24,    78,    79,    26,
      40,    10,    11,    14,    15,    16,    17,    18,    19,    20,
      27,    28,    35,    80,    85,    86,    87,    88,    89,    96,
      76,    27,    90,    90,    86,    90,    97,    98,    42,    40,
      33,    62,    36,    62,    39,    40,    89,    81,    82,    83,
      86,    86,    27,    29,    30,    31,    32,    33,    45,    46,
      47,    48,    88,    90,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   112,   113,    98,    34,    39,    90,
      40,    99,   100,   108,   109,   108,   108,   108,    37,    43,
      61,    60,    58,    59,    54,    55,    56,    57,    52,    53,
      49,    50,    51,    33,    35,    42,    47,    48,    62,    63,
      64,    65,    66,    44,    84,    83,    34,    90,   114,   115,
     116,    99,   103,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   108,    99,   110,   111,    99,    90,
     100,   100,   100,   100,   100,    86,    37,    40,    91,    41,
      38,    39,    41,    34,    39,    36,    92,    99,   116,   101,
      99,     3,     4,     5,    13,    21,    22,    38,    88,    91,
      93,    96,    99,    33,    33,    93,    95,    99,    40,    40,
      40,    99,    99,     4,    40,    34,    34,    33,    93,    93,
      99,     6,    94,    34,    93,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    83,    84,    85,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    90,    91,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    94,    95,
      95,    96,    97,    97,    98,    98,    99,   100,   100,   100,
     100,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   105,   105,   105,   105,   105,   106,   106,   106,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   109,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   113,   114,   114,
     115,   115,   115,   116
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     3,     0,     2,     3,     5,     1,
       3,     1,     0,     2,     2,     2,     2,     1,     0,     1,
       7,     7,     0,     1,     1,     3,     2,     2,     2,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     0,     2,     1,     3,
       6,     5,     7,     2,     2,     1,     2,     0,     2,     0,
       1,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       3,     3,     3,     1,     5,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     2,     2,     2,     2,     1,     1,
       4,     4,     3,     2,     2,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     3,     1,     4,     0,     1,
       1,     3,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Scanner& scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Scanner& scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, Scanner& scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Scanner& scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (Scanner& scanner)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* translation_unit: opt_package import_list decl_list  */
#line 192 "parser_rules.y"
    {
      // If you have a Program node, build it here. For now, just wrap decls in a block.
      (yyval.ast::StatementPtr) = mk_block_stmt(std::move((yyvsp[0].std::vector<ast::StatementPtr>)), (yylsp[-2]) + (yylsp[0]));
    }
#line 1516 "parser_rules.tab.c"
    break;

  case 3: /* opt_package: %empty  */
#line 199 "parser_rules.y"
                                                { (yyval.ast::StatementPtr) = nullptr; }
#line 1522 "parser_rules.tab.c"
    break;

  case 4: /* opt_package: TOK_PACKAGE names_separated_by_dots TOK_SMCLN  */
#line 201 "parser_rules.y"
    {
      // If you model packages, create a node. Otherwise ignore.
      (yyval.ast::StatementPtr) = nullptr;
    }
#line 1531 "parser_rules.tab.c"
    break;

  case 5: /* import_list: %empty  */
#line 208 "parser_rules.y"
                                                { (yyval.std::vector<ast::StatementPtr>) = std::vector<ast::StatementPtr>{}; }
#line 1537 "parser_rules.tab.c"
    break;

  case 6: /* import_list: import_list import_decl  */
#line 210 "parser_rules.y"
    {
      (yyvsp[-1].std::vector<ast::StatementPtr>).push_back(std::move((yyvsp[0].ast::StatementPtr)));
      (yyval.std::vector<ast::StatementPtr>) = std::move((yyvsp[-1].std::vector<ast::StatementPtr>));
    }
#line 1546 "parser_rules.tab.c"
    break;

  case 7: /* import_decl: TOK_IMPORT names_separated_by_dots TOK_SMCLN  */
#line 218 "parser_rules.y"
    {
      // Build an import node if you have one; otherwise return nullptr placeholder.
      (yyval.ast::StatementPtr) = nullptr;
    }
#line 1555 "parser_rules.tab.c"
    break;

  case 8: /* import_decl: TOK_IMPORT names_separated_by_dots TOK_AS name TOK_SMCLN  */
#line 223 "parser_rules.y"
    {
      (yyval.ast::StatementPtr) = nullptr;
    }
#line 1563 "parser_rules.tab.c"
    break;

  case 9: /* names_separated_by_dots: name  */
#line 230 "parser_rules.y"
    { std::vector<Str> v; v.push_back((yyvsp[0].Str)); (yyval.std::vector<Str>) = std::move(v); }
#line 1569 "parser_rules.tab.c"
    break;

  case 10: /* names_separated_by_dots: names_separated_by_dots TOK_DOT name  */
#line 232 "parser_rules.y"
    { (yyvsp[-2].std::vector<Str>).push_back((yyvsp[0].Str)); (yyval.std::vector<Str>) = std::move((yyvsp[-2].std::vector<Str>)); }
#line 1575 "parser_rules.tab.c"
    break;

  case 11: /* name: TOK_IDENTIFIER  */
#line 237 "parser_rules.y"
    { (yyval.Str) = std::move((yyvsp[0].Str)); }
#line 1581 "parser_rules.tab.c"
    break;

  case 12: /* decl_list: %empty  */
#line 243 "parser_rules.y"
    { (yyval.std::vector<ast::StatementPtr>) = std::vector<ast::StatementPtr>{}; }
#line 1587 "parser_rules.tab.c"
    break;

  case 13: /* decl_list: decl_list decl  */
#line 245 "parser_rules.y"
    { (yyvsp[-1].std::vector<ast::StatementPtr>).push_back(std::move((yyvsp[0].ast::StatementPtr))); (yyval.std::vector<ast::StatementPtr>) = std::move((yyvsp[-1].std::vector<ast::StatementPtr>)); }
#line 1593 "parser_rules.tab.c"
    break;

  case 14: /* decl: maybe_export fn_decl  */
#line 249 "parser_rules.y"
                              { (yyval.ast::StatementPtr) = std::move((yyvsp[0].ast::StatementPtr)); }
#line 1599 "parser_rules.tab.c"
    break;

  case 15: /* decl: maybe_export type_alias  */
#line 250 "parser_rules.y"
                              { (yyval.ast::StatementPtr) = std::move((yyvsp[0].ast::StatementPtr)); }
#line 1605 "parser_rules.tab.c"
    break;

  case 16: /* decl: maybe_export var_decl  */
#line 251 "parser_rules.y"
                              { (yyval.ast::StatementPtr) = std::move((yyvsp[0].ast::StatementPtr)); }
#line 1611 "parser_rules.tab.c"
    break;

  case 17: /* decl: maybe_export  */
#line 252 "parser_rules.y"
                                                          { (yyval.ast::StatementPtr) = nullptr; }
#line 1617 "parser_rules.tab.c"
    break;

  case 18: /* maybe_export: %empty  */
#line 256 "parser_rules.y"
                  { (yyval.ast::StatementPtr) = nullptr; }
#line 1623 "parser_rules.tab.c"
    break;

  case 19: /* maybe_export: TOK_EXPORT  */
#line 257 "parser_rules.y"
                  { (yyval.ast::StatementPtr) = nullptr; }
#line 1629 "parser_rules.tab.c"
    break;

  case 20: /* fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type block  */
#line 264 "parser_rules.y"
    {
      (yyval.ast::StatementPtr) = mk_fn_decl((yyvsp[-5].Str), std::move((yyvsp[-3].std::vector<ast::ParamDecl>)), (yyvsp[-1].ast::TypePtr), std::move((yyvsp[0].ast::StatementPtr)), (yylsp[-6]) + (yylsp[0]));
    }
#line 1637 "parser_rules.tab.c"
    break;

  case 21: /* fn_decl: TOK_FN ident TOK_LPAR param_list_opt TOK_RPAR ret_type TOK_SMCLN  */
#line 268 "parser_rules.y"
    {
      (yyval.ast::StatementPtr) = mk_fn_decl((yyvsp[-5].Str), std::move((yyvsp[-3].std::vector<ast::ParamDecl>)), (yyvsp[-1].ast::TypePtr), nullptr, (yylsp[-6]) + (yylsp[-1]));
    }
#line 1645 "parser_rules.tab.c"
    break;

  case 22: /* param_list_opt: %empty  */
#line 275 "parser_rules.y"
    { (yyval.std::vector<ast::ParamDecl>) = std::vector<ast::ParamDecl>{}; }
#line 1651 "parser_rules.tab.c"
    break;

  case 24: /* param_list: param  */
#line 281 "parser_rules.y"
    { std::vector<ast::ParamDecl> v; v.push_back(std::move((yyvsp[0].ast::ParamDecl))); (yyval.std::vector<ast::ParamDecl>) = std::move(v); }
#line 1657 "parser_rules.tab.c"
    break;

  case 25: /* param_list: param_list TOK_COMMA param  */
#line 283 "parser_rules.y"
    { (yyvsp[-2].std::vector<ast::ParamDecl>).push_back(std::move((yyvsp[0].ast::ParamDecl))); (yyval.std::vector<ast::ParamDecl>) = std::move((yyvsp[-2].std::vector<ast::ParamDecl>)); }
#line 1663 "parser_rules.tab.c"
    break;

  case 26: /* param_list: param_list TOK_COMMA  */
#line 285 "parser_rules.y"
    { (yyval.std::vector<ast::ParamDecl>) = std::move((yyvsp[-1].std::vector<ast::ParamDecl>)); }
#line 1669 "parser_rules.tab.c"
    break;

  case 27: /* param: type_spec ident  */
#line 290 "parser_rules.y"
    {
      // Build your ParamDecl here; assuming ParamDecl{TypePtr, string, Loc}
      extern ast::ParamDecl mk_param(ast::TypePtr, const Str&, const lex::Loc&);
      (yyval.ast::ParamDecl) = mk_param((yyvsp[-1].ast::TypePtr), (yyvsp[0].Str), (yylsp[-1]) + (yylsp[0]));
    }
#line 1679 "parser_rules.tab.c"
    break;

  case 28: /* ret_type: TOK_ARROW type_spec  */
#line 298 "parser_rules.y"
                          { (yyval.ast::TypePtr) = (yyvsp[0].ast::TypePtr); }
#line 1685 "parser_rules.tab.c"
    break;

  case 29: /* type_alias: TOK_TYPE ident TOK_ASSIGN type_spec TOK_SMCLN  */
#line 303 "parser_rules.y"
    {
      // Build a type alias node if you have one; for now, stub:
      (yyval.ast::StatementPtr) = nullptr;
    }
#line 1694 "parser_rules.tab.c"
    break;

  case 31: /* type_spec: type_path  */
#line 313 "parser_rules.y"
                      { (yyval.ast::TypePtr) = mk_type_from_path((yyvsp[0].ast::PathType), (yylsp[0])); }
#line 1700 "parser_rules.tab.c"
    break;

  case 32: /* type_spec: TOK_LBRACK type_spec TOK_RBRACK  */
#line 315 "parser_rules.y"
    { (yyval.ast::TypePtr) = mk_array_type((yyvsp[-1].ast::TypePtr), (yylsp[-2]) + (yylsp[0])); }
#line 1706 "parser_rules.tab.c"
    break;

  case 33: /* builtin_type: TOK_INT  */
#line 319 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_INT, (yylsp[0])); }
#line 1712 "parser_rules.tab.c"
    break;

  case 34: /* builtin_type: TOK_BIGINT  */
#line 320 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_BIGINT, (yylsp[0])); }
#line 1718 "parser_rules.tab.c"
    break;

  case 35: /* builtin_type: TOK_MAGICINT  */
#line 321 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_MAGICINT, (yylsp[0])); }
#line 1724 "parser_rules.tab.c"
    break;

  case 36: /* builtin_type: TOK_DOUBLE  */
#line 322 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_DOUBLE, (yylsp[0])); }
#line 1730 "parser_rules.tab.c"
    break;

  case 37: /* builtin_type: TOK_BOOL  */
#line 323 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_BOOL, (yylsp[0])); }
#line 1736 "parser_rules.tab.c"
    break;

  case 38: /* builtin_type: TOK_VOID  */
#line 324 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_VOID, (yylsp[0])); }
#line 1742 "parser_rules.tab.c"
    break;

  case 39: /* builtin_type: TOK_STRING  */
#line 325 "parser_rules.y"
                  { (yyval.ast::TypePtr) = mk_builtin_type(TOK_STRING, (yylsp[0])); }
#line 1748 "parser_rules.tab.c"
    break;

  case 40: /* type_path: type_atom  */
#line 330 "parser_rules.y"
    {
      // Build a single-segment path
      extern ast::PathType mk_type_path_single(const Str&, const lex::Loc&);
      (yyval.ast::PathType) = mk_type_path_single((yyvsp[0].Str), (yylsp[0]));
    }
#line 1758 "parser_rules.tab.c"
    break;

  case 41: /* type_path: type_path TOK_DOT type_atom  */
#line 336 "parser_rules.y"
    {
      // Append segment
      extern ast::PathType mk_type_path_append(ast::PathType, const Str&, const lex::Loc&);
      (yyval.ast::PathType) = mk_type_path_append((yyvsp[-2].ast::PathType), (yyvsp[0].Str), (yylsp[-2]) + (yylsp[0]));
    }
#line 1768 "parser_rules.tab.c"
    break;

  case 42: /* type_atom: TOK_TYPE_NAME  */
#line 344 "parser_rules.y"
                      { (yyval.Str) = std::move((yyvsp[0].Str)); }
#line 1774 "parser_rules.tab.c"
    break;

  case 43: /* type_atom: TOK_IDENTIFIER  */
#line 345 "parser_rules.y"
                      { (yyval.Str) = std::move((yyvsp[0].Str)); }
#line 1780 "parser_rules.tab.c"
    break;

  case 44: /* ident: TOK_IDENTIFIER  */
#line 349 "parser_rules.y"
                      { (yyval.Str) = std::move((yyvsp[0].Str)); }
#line 1786 "parser_rules.tab.c"
    break;

  case 45: /* block: TOK_LCBRA stmt_list TOK_RCBRA  */
#line 356 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_block_stmt(std::move((yyvsp[-1].std::vector<ast::StatementPtr>)), (yylsp[-2]) + (yylsp[0])); }
#line 1792 "parser_rules.tab.c"
    break;

  case 46: /* stmt_list: %empty  */
#line 361 "parser_rules.y"
    { (yyval.std::vector<ast::StatementPtr>) = std::vector<ast::StatementPtr>{}; }
#line 1798 "parser_rules.tab.c"
    break;

  case 47: /* stmt_list: stmt_list stmt  */
#line 363 "parser_rules.y"
    { (yyvsp[-1].std::vector<ast::StatementPtr>).push_back(std::move((yyvsp[0].ast::StatementPtr))); (yyval.std::vector<ast::StatementPtr>) = std::move((yyvsp[-1].std::vector<ast::StatementPtr>)); }
#line 1804 "parser_rules.tab.c"
    break;

  case 49: /* stmt: TOK_RETURN expr_opt TOK_SMCLN  */
#line 369 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_return_stmt(std::move((yyvsp[-1].ast::ExprPtr)), (yylsp[-2])); }
#line 1810 "parser_rules.tab.c"
    break;

  case 50: /* stmt: TOK_IF TOK_LPAR expr TOK_RPAR stmt else_opt  */
#line 371 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_if_stmt(std::move((yyvsp[-3].ast::ExprPtr)), std::move((yyvsp[-1].ast::StatementPtr)), std::move((yyvsp[0].ast::StatementPtr)), (yylsp[-5]) + (yylsp[-1])); }
#line 1816 "parser_rules.tab.c"
    break;

  case 51: /* stmt: TOK_WHILE TOK_LPAR expr TOK_RPAR stmt  */
#line 373 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_while_stmt(std::move((yyvsp[-2].ast::ExprPtr)), std::move((yyvsp[0].ast::StatementPtr)), (yylsp[-4]) + (yylsp[0])); }
#line 1822 "parser_rules.tab.c"
    break;

  case 52: /* stmt: TOK_DO stmt TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SMCLN  */
#line 375 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_do_while_stmt(std::move((yyvsp[-5].ast::StatementPtr)), std::move((yyvsp[-2].ast::ExprPtr)), (yylsp[-6]) + (yylsp[0])); }
#line 1828 "parser_rules.tab.c"
    break;

  case 53: /* stmt: TOK_BREAK TOK_SMCLN  */
#line 377 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_break_stmt((yylsp[-1]) + (yylsp[0])); }
#line 1834 "parser_rules.tab.c"
    break;

  case 54: /* stmt: TOK_CONTINUE TOK_SMCLN  */
#line 379 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_continue_stmt((yylsp[-1]) + (yylsp[0])); }
#line 1840 "parser_rules.tab.c"
    break;

  case 56: /* stmt: expr TOK_SMCLN  */
#line 382 "parser_rules.y"
    {
      // Expression statement: wrap as statement if you model it, else drop
      extern ast::StatementPtr mk_expr_stmt(ast::ExprPtr, const lex::Loc&);
      (yyval.ast::StatementPtr) = mk_expr_stmt(std::move((yyvsp[-1].ast::ExprPtr)), (yylsp[-1]) + (yylsp[0]));
    }
#line 1850 "parser_rules.tab.c"
    break;

  case 57: /* else_opt: %empty  */
#line 390 "parser_rules.y"
                  { (yyval.ast::StatementPtr) = nullptr; }
#line 1856 "parser_rules.tab.c"
    break;

  case 58: /* else_opt: TOK_ELSE stmt  */
#line 391 "parser_rules.y"
                  { (yyval.ast::StatementPtr) = std::move((yyvsp[0].ast::StatementPtr)); }
#line 1862 "parser_rules.tab.c"
    break;

  case 59: /* expr_opt: %empty  */
#line 395 "parser_rules.y"
                  { (yyval.ast::ExprPtr) = nullptr; }
#line 1868 "parser_rules.tab.c"
    break;

  case 60: /* expr_opt: expr  */
#line 396 "parser_rules.y"
                  { (yyval.ast::ExprPtr) = std::move((yyvsp[0].ast::ExprPtr)); }
#line 1874 "parser_rules.tab.c"
    break;

  case 61: /* var_decl: type_spec init_declarator_list TOK_SMCLN  */
#line 402 "parser_rules.y"
    {
      // Fold a list of decls into multiple var_decl statements wrapped in a block
      // If you prefer a single multi-decl node, change this.
      std::vector<ast::StatementPtr> decls = std::move((yyvsp[-1].std::vector<ast::StatementPtr>));
      (yyval.ast::StatementPtr) = mk_block_stmt(std::move(decls), (yylsp[-2]) + (yylsp[0]));
    }
#line 1885 "parser_rules.tab.c"
    break;

  case 62: /* init_declarator_list: init_declarator  */
#line 413 "parser_rules.y"
    { std::vector<ast::StatementPtr> v; v.push_back(std::move((yyvsp[0].ast::StatementPtr))); (yyval.std::vector<ast::StatementPtr>) = std::move(v); }
#line 1891 "parser_rules.tab.c"
    break;

  case 63: /* init_declarator_list: init_declarator_list TOK_COMMA init_declarator  */
#line 415 "parser_rules.y"
    { (yyvsp[-2].std::vector<ast::StatementPtr>).push_back(std::move((yyvsp[0].ast::StatementPtr))); (yyval.std::vector<ast::StatementPtr>) = std::move((yyvsp[-2].std::vector<ast::StatementPtr>)); }
#line 1897 "parser_rules.tab.c"
    break;

  case 64: /* init_declarator: ident  */
#line 420 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_var_decl($(-1) /* type_spec from left context — see note below */, (yyvsp[0].Str), nullptr, (yylsp[0])); }
#line 1903 "parser_rules.tab.c"
    break;

  case 65: /* init_declarator: ident TOK_ASSIGN assign  */
#line 422 "parser_rules.y"
    { (yyval.ast::StatementPtr) = mk_var_decl($(-3) /* type_spec */, (yyvsp[-2].Str), std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1909 "parser_rules.tab.c"
    break;

  case 68: /* assign: postfix TOK_ASSIGN assign  */
#line 440 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_assign_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Simple*/0, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1915 "parser_rules.tab.c"
    break;

  case 69: /* assign: postfix TOK_PLUS_ASSIGN assign  */
#line 441 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_assign_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Add*/1,    std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1921 "parser_rules.tab.c"
    break;

  case 70: /* assign: postfix TOK_MIN_ASSIGN assign  */
#line 442 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_assign_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Sub*/2,    std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1927 "parser_rules.tab.c"
    break;

  case 71: /* assign: postfix TOK_MUL_ASSIGN assign  */
#line 443 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_assign_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Mul*/3,    std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1933 "parser_rules.tab.c"
    break;

  case 72: /* assign: postfix TOK_DIV_ASSIGN assign  */
#line 444 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_assign_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Div*/4,    std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1939 "parser_rules.tab.c"
    break;

  case 74: /* cond: logic_or TOK_QUESTION expr TOK_COLON cond  */
#line 450 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_cond_expr(std::move((yyvsp[-4].ast::ExprPtr)), std::move((yyvsp[-2].ast::ExprPtr)), std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-4]) + (yylsp[0])); }
#line 1945 "parser_rules.tab.c"
    break;

  case 76: /* logic_or: logic_or TOK_BOOL_OR logic_and  */
#line 456 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*LOr*/10, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1951 "parser_rules.tab.c"
    break;

  case 78: /* logic_and: logic_and TOK_BOOL_AND equality  */
#line 462 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*LAnd*/11, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1957 "parser_rules.tab.c"
    break;

  case 80: /* equality: equality TOK_EQUAL relational  */
#line 468 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Eq*/20, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1963 "parser_rules.tab.c"
    break;

  case 81: /* equality: equality TOK_NEQUAL relational  */
#line 470 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Ne*/21, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1969 "parser_rules.tab.c"
    break;

  case 83: /* relational: relational TOK_LESS additive  */
#line 475 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Lt*/30, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1975 "parser_rules.tab.c"
    break;

  case 84: /* relational: relational TOK_LEQ additive  */
#line 476 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Le*/31, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1981 "parser_rules.tab.c"
    break;

  case 85: /* relational: relational TOK_GREATER additive  */
#line 477 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Gt*/32, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1987 "parser_rules.tab.c"
    break;

  case 86: /* relational: relational TOK_GEQ additive  */
#line 478 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Ge*/33, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1993 "parser_rules.tab.c"
    break;

  case 88: /* additive: additive TOK_PLUS multiplicative  */
#line 483 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Add*/40, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 1999 "parser_rules.tab.c"
    break;

  case 89: /* additive: additive TOK_MINUS multiplicative  */
#line 484 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Sub*/41, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 2005 "parser_rules.tab.c"
    break;

  case 91: /* multiplicative: multiplicative TOK_STAR unary  */
#line 489 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Mul*/50, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 2011 "parser_rules.tab.c"
    break;

  case 92: /* multiplicative: multiplicative TOK_SLASH unary  */
#line 490 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Div*/51, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 2017 "parser_rules.tab.c"
    break;

  case 93: /* multiplicative: multiplicative TOK_MODULO unary  */
#line 491 "parser_rules.y"
                                    { (yyval.ast::ExprPtr) = mk_binary_expr(std::move((yyvsp[-2].ast::ExprPtr)), /*Mod*/52, std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 2023 "parser_rules.tab.c"
    break;

  case 94: /* unary: TOK_NEG unary  */
#line 495 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_unary_expr_neg(std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-1]) + (yylsp[0])); }
#line 2029 "parser_rules.tab.c"
    break;

  case 95: /* unary: TOK_NEGATION unary  */
#line 496 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_unary_expr_not(std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-1]) + (yylsp[0])); }
#line 2035 "parser_rules.tab.c"
    break;

  case 96: /* unary: TOK_INC unary  */
#line 497 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_prefix_incdec_expr(std::move((yyvsp[0].ast::ExprPtr)), true,  (yylsp[-1]) + (yylsp[0])); }
#line 2041 "parser_rules.tab.c"
    break;

  case 97: /* unary: TOK_DEC unary  */
#line 498 "parser_rules.y"
                                      { (yyval.ast::ExprPtr) = mk_prefix_incdec_expr(std::move((yyvsp[0].ast::ExprPtr)), false, (yylsp[-1]) + (yylsp[0])); }
#line 2047 "parser_rules.tab.c"
    break;

  case 98: /* unary: postfix  */
#line 499 "parser_rules.y"
                                        { (yyval.ast::ExprPtr) = std::move((yyvsp[0].ast::ExprPtr)); }
#line 2053 "parser_rules.tab.c"
    break;

  case 100: /* postfix: postfix TOK_LPAR arg_list_opt TOK_RPAR  */
#line 505 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_call_expr(std::move((yyvsp[-3].ast::ExprPtr)), std::move((yyvsp[-1].std::vector<ast::ExprPtr>)), (yylsp[-3]) + (yylsp[0])); }
#line 2059 "parser_rules.tab.c"
    break;

  case 101: /* postfix: postfix TOK_LBRACK expr TOK_RBRACK  */
#line 507 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_index_expr(std::move((yyvsp[-3].ast::ExprPtr)), std::move((yyvsp[-1].ast::ExprPtr)), (yylsp[-3]) + (yylsp[0])); }
#line 2065 "parser_rules.tab.c"
    break;

  case 102: /* postfix: postfix TOK_DOT ident  */
#line 509 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_field_expr(std::move((yyvsp[-2].ast::ExprPtr)), (yyvsp[0].Str), (yylsp[-2]) + (yylsp[0])); }
#line 2071 "parser_rules.tab.c"
    break;

  case 103: /* postfix: postfix TOK_INC  */
#line 511 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_postfix_incdec_expr(std::move((yyvsp[-1].ast::ExprPtr)), true,  (yylsp[-1]) + (yylsp[0])); }
#line 2077 "parser_rules.tab.c"
    break;

  case 104: /* postfix: postfix TOK_DEC  */
#line 513 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_postfix_incdec_expr(std::move((yyvsp[-1].ast::ExprPtr)), false, (yylsp[-1]) + (yylsp[0])); }
#line 2083 "parser_rules.tab.c"
    break;

  case 105: /* arg_list_opt: %empty  */
#line 517 "parser_rules.y"
                                 { (yyval.std::vector<ast::ExprPtr>) = std::vector<ast::ExprPtr>{}; }
#line 2089 "parser_rules.tab.c"
    break;

  case 107: /* arg_list: expr  */
#line 522 "parser_rules.y"
                                 { std::vector<ast::ExprPtr> v; v.push_back(std::move((yyvsp[0].ast::ExprPtr))); (yyval.std::vector<ast::ExprPtr>) = std::move(v); }
#line 2095 "parser_rules.tab.c"
    break;

  case 108: /* arg_list: arg_list TOK_COMMA expr  */
#line 523 "parser_rules.y"
                                 { (yyvsp[-2].std::vector<ast::ExprPtr>).push_back(std::move((yyvsp[0].ast::ExprPtr))); (yyval.std::vector<ast::ExprPtr>) = std::move((yyvsp[-2].std::vector<ast::ExprPtr>)); }
#line 2101 "parser_rules.tab.c"
    break;

  case 109: /* arg_list: arg_list TOK_COMMA  */
#line 524 "parser_rules.y"
                                 { (yyval.std::vector<ast::ExprPtr>) = std::move((yyvsp[-1].std::vector<ast::ExprPtr>)); }
#line 2107 "parser_rules.tab.c"
    break;

  case 110: /* primary: ident  */
#line 529 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_ref_expr((yyvsp[0].Str), (yylsp[0])); }
#line 2113 "parser_rules.tab.c"
    break;

  case 111: /* primary: TOK_INT_LITERAL  */
#line 531 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_int_literal_expr((yyvsp[0].kl_int), (yylsp[0])); }
#line 2119 "parser_rules.tab.c"
    break;

  case 112: /* primary: TOK_FLOAT_LITERAL  */
#line 533 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_float_literal_expr((yyvsp[0].kl_double), (yylsp[0])); }
#line 2125 "parser_rules.tab.c"
    break;

  case 113: /* primary: TOK_STRING_LITERAL  */
#line 535 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_str_literal_expr((yyvsp[0].kl_string), (yylsp[0])); }
#line 2131 "parser_rules.tab.c"
    break;

  case 114: /* primary: TOK_BOOL_LITERAL  */
#line 537 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_bool_literal_expr((yyvsp[0].kl_bool), (yylsp[0])); }
#line 2137 "parser_rules.tab.c"
    break;

  case 115: /* primary: TOK_LPAR expr TOK_RPAR  */
#line 539 "parser_rules.y"
    { (yyval.ast::ExprPtr) = std::move((yyvsp[-1].ast::ExprPtr)); (yyval.ast::ExprPtr)->loc = (yylsp[-2]) + (yylsp[0]); }
#line 2143 "parser_rules.tab.c"
    break;

  case 117: /* struct_lit: type_path TOK_LCBRA field_inits_opt TOK_RCBRA  */
#line 545 "parser_rules.y"
    { (yyval.ast::ExprPtr) = mk_struct_literal_expr(std::move((yyvsp[-3].ast::PathType)), std::move((yyvsp[-1].std::vector<ast::FieldInitExpr>)), (yylsp[-3]) + (yylsp[0])); }
#line 2149 "parser_rules.tab.c"
    break;

  case 118: /* field_inits_opt: %empty  */
#line 550 "parser_rules.y"
    { (yyval.std::vector<ast::FieldInitExpr>) = std::vector<ast::FieldInitExpr>{}; }
#line 2155 "parser_rules.tab.c"
    break;

  case 120: /* field_inits: field_init  */
#line 556 "parser_rules.y"
    { std::vector<ast::FieldInitExpr> v; v.push_back(std::move((yyvsp[0].ast::FieldInitExpr))); (yyval.std::vector<ast::FieldInitExpr>) = std::move(v); }
#line 2161 "parser_rules.tab.c"
    break;

  case 121: /* field_inits: field_inits TOK_COMMA field_init  */
#line 558 "parser_rules.y"
    { (yyvsp[-2].std::vector<ast::FieldInitExpr>).push_back(std::move((yyvsp[0].ast::FieldInitExpr))); (yyval.std::vector<ast::FieldInitExpr>) = std::move((yyvsp[-2].std::vector<ast::FieldInitExpr>)); }
#line 2167 "parser_rules.tab.c"
    break;

  case 122: /* field_inits: field_inits TOK_COMMA  */
#line 560 "parser_rules.y"
    { (yyval.std::vector<ast::FieldInitExpr>) = std::move((yyvsp[-1].std::vector<ast::FieldInitExpr>)); }
#line 2173 "parser_rules.tab.c"
    break;

  case 123: /* field_init: ident TOK_COLON expr  */
#line 565 "parser_rules.y"
    { (yyval.ast::FieldInitExpr) = mk_field_init((yyvsp[-2].Str), std::move((yyvsp[0].ast::ExprPtr)), (yylsp[-2]) + (yylsp[0])); }
#line 2179 "parser_rules.tab.c"
    break;


#line 2183 "parser_rules.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 568 "parser_rules.y"


/* Optionally: yyerror, yylex wrappers, etc. */
