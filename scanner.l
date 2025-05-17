%{ 
#include <stdio.h>
#include <stdlib.h>    // malloc, exit, atof, atoi
#include <string.h>    // strncpy, strdup
#include "ast.hpp"     // para YYSTYPE complejo
#include "parser.tab.h"// tokens T_IDENTIFIER, YYSTYPE, etc.

/* Prototipo para manejar errores desde el scanner */
extern void yyerror(const char *s);

/* Función auxiliar para copiar yytext */
char *copy_yytext() {
    char *new_str = (char*)malloc(yyleng + 1);
    if (!new_str) {
        yyerror("Error de memoria en copy_yytext");
        exit(EXIT_FAILURE);
    }
    strncpy(new_str, yytext, yyleng);
    new_str[yyleng] = '\0';
    return new_str;
}
%}

%option nounput     
%option yylineno noyywrap

DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*
WHITESPACE  [ \t\r]+
NEWLINE     \n

%%

{WHITESPACE}       { /* Ignorar espacios, tabuladores y retornos de carro */ }
{NEWLINE}          { /* Flex actualiza yylineno automáticamente */ }

"//".*             { /* Ignorar comentario de línea */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignorar comentario de bloque */ }

"int"              { return T_INT; }
"float"            { return T_FLOAT; }
"string"           { return T_STRING_TYPE; }
"if"               { return T_IF; }
"else"             { return T_ELSE; }
"while"            { return T_WHILE; }
"print"            { return T_PRINT; }
"read"             { return T_READ; }

"="                { return T_ASSIGN; }
"+"                { return T_PLUS; }
"-"                { return T_MINUS; }
"*"                { return T_MULTIPLY; }
"/"                { return T_DIVIDE; }

"=="               { return T_EQ; }
"!="               { return T_NEQ; }
"<="               { return T_LTE; }
">="               { return T_GTE; }
"<"                { return T_LT; }
">"                { return T_GT; }

"("                { return T_LPAREN; }
")"                { return T_RPAREN; }
"{"                { return T_LBRACE; }
"}"                { return T_RBRACE; }
";"                { return T_SEMICOLON; }

{DIGIT}+"."{DIGIT}+ {
                     yylval.fval = atof(yytext);
                     return T_FLOAT_LITERAL;
                   }
{DIGIT}+           {
                     yylval.ival = atoi(yytext);
                     return T_INTEGER_LITERAL;
                   }

{ID}               {
                     yylval.sval = copy_yytext();
                     return T_IDENTIFIER;
                   }

\"([^\"\n])*\"     {
                     /* extrae sin las comillas */
                     char *s = (char*)malloc(yyleng - 1);
                     if (!s) {
                         yyerror("Error de memoria en literal de cadena");
                         return T_ERROR;
                     }
                     strncpy(s, yytext + 1, yyleng - 2);
                     s[yyleng - 2] = '\0';
                     yylval.sval = s;
                     return T_STRING_LITERAL;
                   }

.                  {
                     char msg[256];
                     snprintf(msg, sizeof(msg),
                              "Caracter inesperado: '%.*s'",
                              yyleng > 200 ? 200 : yyleng,
                              yytext);
                     yyerror(msg);
                     /* opcional: return T_ERROR; */
                   }

%%
