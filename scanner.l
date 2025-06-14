%{
#include <stdio.h>
#include <stdlib.h>    // malloc, exit, atof, atoi
#include <string.h>    // strncpy, strdup
#include "ast.hpp"     // para YYSTYPE complejo
#include "parser.tab.h"// tokens T_IDENTIFIER, YYSTYPE, etc.

/* Prototipo para reportar errores desde el scanner */
extern void yyerror(const char *mensaje);

/* Función auxiliar para copiar el texto actual de yytext */
char *copiarTexto() {
    char *cadena = (char *) malloc(yyleng + 1);
    if (!cadena) {
        yyerror("Error de memoria en copiarTexto");
        exit(EXIT_FAILURE);
    }
    strncpy(cadena, yytext, yyleng);
    cadena[yyleng] = '\0';
    return cadena;
}
%}

%option nounput
%option yylineno noyywrap

DIGITO         [0-9]
IDENTIFICADOR  [a-zA-Z_][a-zA-Z0-9_]*
ESPACIO        [ \t\r]+
NUEVALINEA     \n

%%

{ESPACIO}            { /* Ignorar espacios, tabulaciones y retornos de carro */ }
{NUEVALINEA}         { /* Flex actualiza yylineno automáticamente */ }

"//".*               { /* Ignorar comentario de línea */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* Ignorar comentario de bloque */ }

"enteros"                { return T_INT; }
"flotantes"              { return T_FLOAT; }
"texto"                  { return T_STRING_TYPE; }
"if"                     { return T_IF; }
"else"                   { return T_ELSE; }
"while"                  { return T_WHILE; }
"print"                  { return T_PRINT; }
"read"                   { return T_READ; }
"booleano"                { return T_BOOL; }
"true"                    { yylval.ival = 1; return T_TRUE; }
"false"                   { yylval.ival = 0; return T_FALSE; }

"="                      { return T_ASSIGN; }
"+"                      { return T_PLUS; }
"-"                      { return T_MINUS; }
"*"                      { return T_MULTIPLY; }
"/"                      { return T_DIVIDE; }

"=="                     { return T_EQ; }
"!="                     { return T_NEQ; }
"<="                     { return T_LTE; }
">="                     { return T_GTE; }
"<"                      { return T_LT; }
">"                      { return T_GT; }

"("                      { return T_LPAREN; }
")"                      { return T_RPAREN; }
"{"                      { return T_LBRACE; }
"}"                      { return T_RBRACE; }
";"                      { return T_SEMICOLON; }

"&&"                     { return T_AND; }
"||"                     { return T_OR; }
"!"                      { return T_NOT; }

{DIGITO}+"."{DIGITO}+ {
    yylval.fval = atof(yytext);
    return T_FLOAT_LITERAL;
}

{DIGITO}+           {
    yylval.ival = atoi(yytext);
    return T_INTEGER_LITERAL;
}

{IDENTIFICADOR}      {
    yylval.sval = copiarTexto();
    return T_IDENTIFIER;
}

\"([^\"\n])*\"       {
    /* Extraer literales de cadena sin las comillas */
    size_t longitud = yyleng - 2;
    char *cadena = (char *) malloc(longitud + 1);
    if (!cadena) {
        yyerror("Error de memoria en literal de cadena");
        return T_ERROR;
    }
    strncpy(cadena, yytext + 1, longitud);
    cadena[longitud] = '\0';
    yylval.sval = cadena;
    return T_STRING_LITERAL;
}

[\x80-\xFF]     { /* descartar bytes de alto bit */ }
.                    {
    char mensaje[256];
    int tamanno = yyleng > 200 ? 200 : yyleng;
    snprintf(mensaje, sizeof(mensaje),
             "Caracter inesperado: '%.*s'",
             tamanno,
             yytext);
    yyerror(mensaje);
    /* Opcional: return T_ERROR; */
}

%%