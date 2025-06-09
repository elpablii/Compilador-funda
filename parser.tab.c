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




/* First part of user prologue.  */
#line 1 "parser.y"

// parser.y (skeleton en C++ para Bison)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>        // std::string
#include "ast.hpp"       // definiciones de Node, DataType, etc.

// Prototipos de Flex/Bison
extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

// Función de error (se llama en errores sintácticos)
void yyerror(const char *mensaje);

#line 90 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_IDENTIFIER = 3,               /* T_IDENTIFIER  */
  YYSYMBOL_T_INTEGER_LITERAL = 4,          /* T_INTEGER_LITERAL  */
  YYSYMBOL_T_FLOAT_LITERAL = 5,            /* T_FLOAT_LITERAL  */
  YYSYMBOL_T_STRING_LITERAL = 6,           /* T_STRING_LITERAL  */
  YYSYMBOL_T_INT = 7,                      /* T_INT  */
  YYSYMBOL_T_FLOAT = 8,                    /* T_FLOAT  */
  YYSYMBOL_T_STRING_TYPE = 9,              /* T_STRING_TYPE  */
  YYSYMBOL_T_IF = 10,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 11,                    /* T_ELSE  */
  YYSYMBOL_T_WHILE = 12,                   /* T_WHILE  */
  YYSYMBOL_T_PRINT = 13,                   /* T_PRINT  */
  YYSYMBOL_T_READ = 14,                    /* T_READ  */
  YYSYMBOL_T_ASSIGN = 15,                  /* T_ASSIGN  */
  YYSYMBOL_T_PLUS = 16,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 17,                   /* T_MINUS  */
  YYSYMBOL_T_MULTIPLY = 18,                /* T_MULTIPLY  */
  YYSYMBOL_T_DIVIDE = 19,                  /* T_DIVIDE  */
  YYSYMBOL_T_EQ = 20,                      /* T_EQ  */
  YYSYMBOL_T_NEQ = 21,                     /* T_NEQ  */
  YYSYMBOL_T_LT = 22,                      /* T_LT  */
  YYSYMBOL_T_GT = 23,                      /* T_GT  */
  YYSYMBOL_T_LTE = 24,                     /* T_LTE  */
  YYSYMBOL_T_GTE = 25,                     /* T_GTE  */
  YYSYMBOL_T_LPAREN = 26,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 27,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 28,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 29,                  /* T_RBRACE  */
  YYSYMBOL_T_SEMICOLON = 30,               /* T_SEMICOLON  */
  YYSYMBOL_T_ERROR = 31,                   /* T_ERROR  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_statement_list = 34,            /* statement_list  */
  YYSYMBOL_statement = 35,                 /* statement  */
  YYSYMBOL_block = 36,                     /* block  */
  YYSYMBOL_type_specifier = 37,            /* type_specifier  */
  YYSYMBOL_variable_declaration = 38,      /* variable_declaration  */
  YYSYMBOL_assignment_statement = 39,      /* assignment_statement  */
  YYSYMBOL_if_statement = 40,              /* if_statement  */
  YYSYMBOL_while_statement = 41,           /* while_statement  */
  YYSYMBOL_print_statement = 42,           /* print_statement  */
  YYSYMBOL_read_statement = 43,            /* read_statement  */
  YYSYMBOL_expression = 44,                /* expression  */
  YYSYMBOL_comparison_expression = 45,     /* comparison_expression  */
  YYSYMBOL_arithmetic_expression = 46,     /* arithmetic_expression  */
  YYSYMBOL_term = 47,                      /* term  */
  YYSYMBOL_factor = 48,                    /* factor  */
  YYSYMBOL_primary_expression = 49,        /* primary_expression  */
  YYSYMBOL_identifier = 50                 /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 96 "parser.y"

    // ast_root guarda el AST generado
    Node* ast_root = nullptr;

#line 180 "parser.tab.c"

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
typedef yytype_int8 yy_state_t;

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   84

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   112,   115,   125,   129,   133,   137,   141,
     145,   149,   153,   157,   165,   173,   177,   181,   188,   192,
     199,   206,   210,   217,   224,   231,   238,   245,   249,   253,
     257,   261,   265,   269,   276,   280,   284,   291,   295,   299,
     306,   313,   317,   321,   325,   331,   338
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
  "\"end of file\"", "error", "\"invalid token\"", "T_IDENTIFIER",
  "T_INTEGER_LITERAL", "T_FLOAT_LITERAL", "T_STRING_LITERAL", "T_INT",
  "T_FLOAT", "T_STRING_TYPE", "T_IF", "T_ELSE", "T_WHILE", "T_PRINT",
  "T_READ", "T_ASSIGN", "T_PLUS", "T_MINUS", "T_MULTIPLY", "T_DIVIDE",
  "T_EQ", "T_NEQ", "T_LT", "T_GT", "T_LTE", "T_GTE", "T_LPAREN",
  "T_RPAREN", "T_LBRACE", "T_RBRACE", "T_SEMICOLON", "T_ERROR", "$accept",
  "program", "statement_list", "statement", "block", "type_specifier",
  "variable_declaration", "assignment_statement", "if_statement",
  "while_statement", "print_statement", "read_statement", "expression",
  "comparison_expression", "arithmetic_expression", "term", "factor",
  "primary_expression", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -53,     2,    12,   -53,   -53,   -53,   -53,   -53,   -22,    -9,
      -3,     1,   -53,   -53,    11,   -53,   -53,    50,   -53,   -53,
     -53,   -53,   -53,   -53,    49,    31,    31,    31,    50,     0,
     -53,   -14,    31,   -53,   -53,   -53,    31,    39,   -53,    38,
     -13,   -53,   -53,   -53,    40,    48,    51,   -53,    31,   -53,
      35,    52,    53,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    53,    46,    47,    54,   -53,   -53,    69,
     -13,   -13,    22,    22,    22,    22,    22,    22,   -53,   -53,
     -53,   -53,   -53,   -53,    53,   -53
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    46,    15,    16,    17,     0,     0,
       0,     0,     3,    12,     0,     4,    11,     0,     5,     6,
       7,     8,     9,    10,     0,     0,     0,     0,     0,     0,
      13,     0,     0,    42,    43,    44,     0,     0,    26,    27,
      34,    37,    40,    41,     0,     0,     0,    14,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    45,    21,
      35,    36,    28,    29,    30,    31,    32,    33,    38,    39,
      23,    24,    25,    19,     0,    22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,    70,   -53,   -52,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,    20,   -53,    14,    -5,   -11,   -53,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    37,    38,    39,    40,    41,    42,    43
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      69,    48,     3,     4,    25,    61,    62,     5,     6,     7,
       8,    80,     9,    10,    11,     4,    49,    26,    24,     5,
       6,     7,     8,    27,     9,    10,    11,    28,    12,    47,
      13,    14,    85,    31,     4,    33,    34,    35,    53,    54,
      12,    30,    13,    14,    46,    24,    44,    45,    70,    71,
      78,    79,    50,     4,    53,    54,    51,    36,    55,    56,
      57,    58,    59,    60,    32,    67,    52,    63,    66,    72,
      73,    74,    75,    76,    77,    64,    81,    82,    65,    68,
      84,    12,    29,     0,    83
};

static const yytype_int8 yycheck[] =
{
      52,    15,     0,     3,    26,    18,    19,     7,     8,     9,
      10,    63,    12,    13,    14,     3,    30,    26,     2,     7,
       8,     9,    10,    26,    12,    13,    14,    26,    28,    29,
      30,    31,    84,    17,     3,     4,     5,     6,    16,    17,
      28,    30,    30,    31,    28,    29,    26,    27,    53,    54,
      61,    62,    32,     3,    16,    17,    36,    26,    20,    21,
      22,    23,    24,    25,    15,    30,    27,    27,    48,    55,
      56,    57,    58,    59,    60,    27,    30,    30,    27,    27,
      11,    28,    12,    -1,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,     3,     7,     8,     9,    10,    12,
      13,    14,    28,    30,    31,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    50,    26,    26,    26,    26,    34,
      30,    50,    15,     4,     5,     6,    26,    44,    45,    46,
      47,    48,    49,    50,    44,    44,    50,    29,    15,    30,
      44,    44,    27,    16,    17,    20,    21,    22,    23,    24,
      25,    18,    19,    27,    27,    27,    44,    30,    27,    36,
      47,    47,    46,    46,    46,    46,    46,    46,    48,    48,
      36,    30,    30,    30,    11,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    36,    37,    37,    37,    38,    38,
      39,    40,    40,    41,    42,    43,    44,    45,    45,    45,
      45,    45,    45,    45,    46,    46,    46,    47,    47,    47,
      48,    49,    49,    49,    49,    49,    50
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     1,     3,     5,
       4,     5,     7,     5,     5,     5,     1,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     3,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement_list  */
#line 105 "parser.y"
    {
        ast_root = new ProgramNode((yyvsp[0].stmt_list_node));
    }
#line 1188 "parser.tab.c"
    break;

  case 3: /* statement_list: %empty  */
#line 112 "parser.y"
    {
        (yyval.stmt_list_node) = new StatementListNode();
    }
#line 1196 "parser.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 116 "parser.y"
    {
        if ((yyvsp[0].node)) {
            (yyvsp[-1].stmt_list_node)->statements.push_back((yyvsp[0].node));
        }
        (yyval.stmt_list_node) = (yyvsp[-1].stmt_list_node);
    }
#line 1207 "parser.tab.c"
    break;

  case 5: /* statement: variable_declaration  */
#line 126 "parser.y"
    {
        (yyval.node) = (yyvsp[0].var_decl_node);
    }
#line 1215 "parser.tab.c"
    break;

  case 6: /* statement: assignment_statement  */
#line 130 "parser.y"
    {
        (yyval.node) = (yyvsp[0].assign_node);
    }
#line 1223 "parser.tab.c"
    break;

  case 7: /* statement: if_statement  */
#line 134 "parser.y"
    {
        (yyval.node) = (yyvsp[0].if_node);
    }
#line 1231 "parser.tab.c"
    break;

  case 8: /* statement: while_statement  */
#line 138 "parser.y"
    {
        (yyval.node) = (yyvsp[0].while_node);
    }
#line 1239 "parser.tab.c"
    break;

  case 9: /* statement: print_statement  */
#line 142 "parser.y"
    {
        (yyval.node) = (yyvsp[0].print_node);
    }
#line 1247 "parser.tab.c"
    break;

  case 10: /* statement: read_statement  */
#line 146 "parser.y"
    {
        (yyval.node) = (yyvsp[0].read_node);
    }
#line 1255 "parser.tab.c"
    break;

  case 11: /* statement: block  */
#line 150 "parser.y"
    {
        (yyval.node) = (yyvsp[0].stmt_list_node);
    }
#line 1263 "parser.tab.c"
    break;

  case 12: /* statement: T_SEMICOLON  */
#line 154 "parser.y"
    {
        (yyval.node) = nullptr;  // Instrucción vacía
    }
#line 1271 "parser.tab.c"
    break;

  case 13: /* statement: T_ERROR T_SEMICOLON  */
#line 158 "parser.y"
    {
        yyerrok;
        (yyval.node) = nullptr;
    }
#line 1280 "parser.tab.c"
    break;

  case 14: /* block: T_LBRACE statement_list T_RBRACE  */
#line 166 "parser.y"
    {
        (yyval.stmt_list_node) = (yyvsp[-1].stmt_list_node);
    }
#line 1288 "parser.tab.c"
    break;

  case 15: /* type_specifier: T_INT  */
#line 174 "parser.y"
    {
        (yyval.dtype) = DataType::INT;
    }
#line 1296 "parser.tab.c"
    break;

  case 16: /* type_specifier: T_FLOAT  */
#line 178 "parser.y"
    {
        (yyval.dtype) = DataType::FLOAT;
    }
#line 1304 "parser.tab.c"
    break;

  case 17: /* type_specifier: T_STRING_TYPE  */
#line 182 "parser.y"
    {
        (yyval.dtype) = DataType::STRING;
    }
#line 1312 "parser.tab.c"
    break;

  case 18: /* variable_declaration: type_specifier identifier T_SEMICOLON  */
#line 189 "parser.y"
    {
        (yyval.var_decl_node) = new VariableDeclarationNode((yyvsp[-2].dtype), (yyvsp[-1].id_node), nullptr);
    }
#line 1320 "parser.tab.c"
    break;

  case 19: /* variable_declaration: type_specifier identifier T_ASSIGN expression T_SEMICOLON  */
#line 193 "parser.y"
    {
        (yyval.var_decl_node) = new VariableDeclarationNode((yyvsp[-4].dtype), (yyvsp[-3].id_node), (yyvsp[-1].node));
    }
#line 1328 "parser.tab.c"
    break;

  case 20: /* assignment_statement: identifier T_ASSIGN expression T_SEMICOLON  */
#line 200 "parser.y"
    {
        (yyval.assign_node) = new AssignmentNode((yyvsp[-3].id_node), (yyvsp[-1].node));
    }
#line 1336 "parser.tab.c"
    break;

  case 21: /* if_statement: T_IF T_LPAREN expression T_RPAREN block  */
#line 207 "parser.y"
    {
        (yyval.if_node) = new IfStatementNode((yyvsp[-2].node), (yyvsp[0].stmt_list_node), nullptr);
    }
#line 1344 "parser.tab.c"
    break;

  case 22: /* if_statement: T_IF T_LPAREN expression T_RPAREN block T_ELSE block  */
#line 211 "parser.y"
    {
        (yyval.if_node) = new IfStatementNode((yyvsp[-4].node), (yyvsp[-2].stmt_list_node), (yyvsp[0].stmt_list_node));
    }
#line 1352 "parser.tab.c"
    break;

  case 23: /* while_statement: T_WHILE T_LPAREN expression T_RPAREN block  */
#line 218 "parser.y"
    {
        (yyval.while_node) = new WhileStatementNode((yyvsp[-2].node), (yyvsp[0].stmt_list_node));
    }
#line 1360 "parser.tab.c"
    break;

  case 24: /* print_statement: T_PRINT T_LPAREN expression T_RPAREN T_SEMICOLON  */
#line 225 "parser.y"
    {
        (yyval.print_node) = new PrintStatementNode((yyvsp[-2].node));
    }
#line 1368 "parser.tab.c"
    break;

  case 25: /* read_statement: T_READ T_LPAREN identifier T_RPAREN T_SEMICOLON  */
#line 232 "parser.y"
    {
        (yyval.read_node) = new ReadStatementNode((yyvsp[-2].id_node));
    }
#line 1376 "parser.tab.c"
    break;

  case 26: /* expression: comparison_expression  */
#line 239 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1384 "parser.tab.c"
    break;

  case 27: /* comparison_expression: arithmetic_expression  */
#line 246 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1392 "parser.tab.c"
    break;

  case 28: /* comparison_expression: arithmetic_expression T_EQ arithmetic_expression  */
#line 250 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("==", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1400 "parser.tab.c"
    break;

  case 29: /* comparison_expression: arithmetic_expression T_NEQ arithmetic_expression  */
#line 254 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("!=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1408 "parser.tab.c"
    break;

  case 30: /* comparison_expression: arithmetic_expression T_LT arithmetic_expression  */
#line 258 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("<", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1416 "parser.tab.c"
    break;

  case 31: /* comparison_expression: arithmetic_expression T_GT arithmetic_expression  */
#line 262 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode(">", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1424 "parser.tab.c"
    break;

  case 32: /* comparison_expression: arithmetic_expression T_LTE arithmetic_expression  */
#line 266 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("<=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1432 "parser.tab.c"
    break;

  case 33: /* comparison_expression: arithmetic_expression T_GTE arithmetic_expression  */
#line 270 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode(">=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1440 "parser.tab.c"
    break;

  case 34: /* arithmetic_expression: term  */
#line 277 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1448 "parser.tab.c"
    break;

  case 35: /* arithmetic_expression: arithmetic_expression T_PLUS term  */
#line 281 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("+", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1456 "parser.tab.c"
    break;

  case 36: /* arithmetic_expression: arithmetic_expression T_MINUS term  */
#line 285 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("-", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1464 "parser.tab.c"
    break;

  case 37: /* term: factor  */
#line 292 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1472 "parser.tab.c"
    break;

  case 38: /* term: term T_MULTIPLY factor  */
#line 296 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("*", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1480 "parser.tab.c"
    break;

  case 39: /* term: term T_DIVIDE factor  */
#line 300 "parser.y"
    {
        (yyval.node) = new BinaryOperationNode("/", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1488 "parser.tab.c"
    break;

  case 40: /* factor: primary_expression  */
#line 307 "parser.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1496 "parser.tab.c"
    break;

  case 41: /* primary_expression: identifier  */
#line 314 "parser.y"
    {
        (yyval.node) = (yyvsp[0].id_node);
    }
#line 1504 "parser.tab.c"
    break;

  case 42: /* primary_expression: T_INTEGER_LITERAL  */
#line 318 "parser.y"
    {
        (yyval.node) = new NumberLiteralNode((yyvsp[0].ival));
    }
#line 1512 "parser.tab.c"
    break;

  case 43: /* primary_expression: T_FLOAT_LITERAL  */
#line 322 "parser.y"
    {
        (yyval.node) = new FloatLiteralNode((yyvsp[0].fval));
    }
#line 1520 "parser.tab.c"
    break;

  case 44: /* primary_expression: T_STRING_LITERAL  */
#line 326 "parser.y"
    {
        std::string cad((yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.node) = new StringLiteralNode(cad);
    }
#line 1530 "parser.tab.c"
    break;

  case 45: /* primary_expression: T_LPAREN expression T_RPAREN  */
#line 332 "parser.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1538 "parser.tab.c"
    break;

  case 46: /* identifier: T_IDENTIFIER  */
#line 339 "parser.y"
    {
        std::string nombre((yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.id_node) = new IdentifierNode(nombre);
    }
#line 1548 "parser.tab.c"
    break;


#line 1552 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 346 "parser.y"


void yyerror(const char *mensaje) {
    std::fprintf(stderr, "Error en línea %d cerca de '%s': %s\n",
                 yylineno, yytext, mensaje);
}
