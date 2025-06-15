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

"r2d2"                   { printf("TOKEN: T_INT (%s)\n", yytext); return T_INT; }
"c3p0"                   { printf("TOKEN: T_FLOAT (%s)\n", yytext); return T_FLOAT; }
"deathStar"               { printf("TOKEN: T_STRING_TYPE (%s)\n", yytext); return T_STRING_TYPE; }
"jedi"                    { printf("TOKEN: T_IF (%s)\n", yytext); return T_IF; }
"sith"                    { printf("TOKEN: T_ELSE (%s)\n", yytext); return T_ELSE; }
"cloneWar"                { printf("TOKEN: T_WHILE (%s)\n", yytext); return T_WHILE; }
"stormTroopers"           { printf("TOKEN: T_FOR (%s)\n", yytext); return T_FOR; }
"palpatine"               { printf("TOKEN: T_PRINT (%s)\n", yytext); return T_PRINT; }
"leia"                    { printf("TOKEN: T_READ (%s)\n", yytext); return T_READ; }
"obiwan"                  { printf("TOKEN: T_TRUE (%s)\n", yytext); yylval.ival = 1; return T_TRUE; }
"anakin"                  { printf("TOKEN: T_FALSE (%s)\n", yytext); yylval.ival = 0; return T_FALSE; }
"booleano"                 { printf("TOKEN: T_BOOL (%s)\n", yytext); return T_BOOL; }

"teOtorgamos"             { printf("TOKEN: T_ASSIGN (%s)\n", yytext); return T_ASSIGN; }
"luz"                     { printf("TOKEN: T_PLUS (%s)\n", yytext); return T_PLUS; }
"oscuridad"               { printf("TOKEN: T_MINUS (%s)\n", yytext); return T_MINUS; }
"unlimitedPower"          { printf("TOKEN: T_MULTIPLY (%s)\n", yytext); return T_MULTIPLY; }
"lightsable"              { printf("TOKEN: T_DIVIDE (%s)\n", yytext); return T_DIVIDE; }

"equilibrio"              { printf("TOKEN: T_EQ (%s)\n", yytext); return T_EQ; }
"rebelde"                 { printf("TOKEN: T_NEQ (%s)\n", yytext); return T_NEQ; }
"padawan"                 { printf("TOKEN: T_LTE (%s)\n", yytext); return T_LTE; }
"maestro"                 { printf("TOKEN: T_GTE (%s)\n", yytext); return T_GTE; }
"highground"              { printf("TOKEN: T_LT (%s)\n", yytext); return T_LT; }
"youUnderestimateMyPower" { printf("TOKEN: T_GT (%s)\n", yytext); return T_GT; }

";"                        { printf("TOKEN: T_SEMICOLON (%s)\n", yytext); return T_SEMICOLON; }

"("                      { printf("TOKEN: T_LPAREN (%s)\n", yytext); return T_LPAREN; }
")"                      { printf("TOKEN: T_RPAREN (%s)\n", yytext); return T_RPAREN; }
"{"                      { printf("TOKEN: T_LBRACE (%s)\n", yytext); return T_LBRACE; }
"}"                      { printf("TOKEN: T_RBRACE (%s)\n", yytext); return T_RBRACE; }

{DIGITO}+"."{DIGITO}+ {
    printf("TOKEN: T_FLOAT_LITERAL (%s)\n", yytext);
    yylval.fval = atof(yytext);
    return T_FLOAT_LITERAL;
}

{DIGITO}+           {
    printf("TOKEN: T_INTEGER_LITERAL (%s)\n", yytext);
    yylval.ival = atoi(yytext);
    return T_INTEGER_LITERAL;
}

{IDENTIFICADOR}      {
    printf("TOKEN: T_IDENTIFIER (%s)\n", yytext);
    yylval.sval = copiarTexto();
    return T_IDENTIFIER;
}

\"([^\"\n])*\"       {
    printf("TOKEN: T_STRING_LITERAL (%s)\n", yytext);
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
    printf("TOKEN: ERROR (%s)\n", yytext);
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