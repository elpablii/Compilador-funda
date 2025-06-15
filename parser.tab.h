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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 24 "parser.y"

    #include "ast.hpp"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_IDENTIFIER = 258,            /* T_IDENTIFIER  */
    T_INTEGER_LITERAL = 259,       /* T_INTEGER_LITERAL  */
    T_FLOAT_LITERAL = 260,         /* T_FLOAT_LITERAL  */
    T_STRING_LITERAL = 261,        /* T_STRING_LITERAL  */
    T_INT = 262,                   /* T_INT  */
    T_FLOAT = 263,                 /* T_FLOAT  */
    T_STRING_TYPE = 264,           /* T_STRING_TYPE  */
    T_IF = 265,                    /* T_IF  */
    T_ELSE = 266,                  /* T_ELSE  */
    T_WHILE = 267,                 /* T_WHILE  */
    T_FOR = 268,                   /* T_FOR  */
    T_PRINT = 269,                 /* T_PRINT  */
    T_READ = 270,                  /* T_READ  */
    T_ASSIGN = 271,                /* T_ASSIGN  */
    T_PLUS = 272,                  /* T_PLUS  */
    T_MINUS = 273,                 /* T_MINUS  */
    T_MULTIPLY = 274,              /* T_MULTIPLY  */
    T_DIVIDE = 275,                /* T_DIVIDE  */
    T_EQ = 276,                    /* T_EQ  */
    T_NEQ = 277,                   /* T_NEQ  */
    T_LT = 278,                    /* T_LT  */
    T_GT = 279,                    /* T_GT  */
    T_LTE = 280,                   /* T_LTE  */
    T_GTE = 281,                   /* T_GTE  */
    T_LPAREN = 282,                /* T_LPAREN  */
    T_RPAREN = 283,                /* T_RPAREN  */
    T_LBRACE = 284,                /* T_LBRACE  */
    T_RBRACE = 285,                /* T_RBRACE  */
    T_SEMICOLON = 286,             /* T_SEMICOLON  */
    T_ERROR = 287,                 /* T_ERROR  */
    T_BOOL = 288,                  /* T_BOOL  */
    T_TRUE = 289,                  /* T_TRUE  */
    T_FALSE = 290,                 /* T_FALSE  */
    T_AND = 291,                   /* T_AND  */
    T_OR = 292,                    /* T_OR  */
    T_NOT = 293                    /* T_NOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    Nodo*                     nodo;
    NodoListaInstrucciones*   nodo_lista_instr;
    NodoIdentificador*        nodo_id;
    NodoDeclaracionVariable*  nodo_decl_var;
    NodoAsignacion*           nodo_asig;
    NodoSi*                   nodo_si;
    NodoMientras*             nodo_mientras;
    NodoImprimir*             nodo_imprimir;
    NodoLeer*                 nodo_leer;

    char*   sval;
    int     ival;
    float   fval;
    TipoDato tipo_dato;

#line 125 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
