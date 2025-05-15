%{
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt; // Para malloc, exit, atof, atoi
#include &lt;string.h&gt; // Para strncpy, strdup
#include &quot;ast.hpp&quot;      // Para yylval si es complejo
#include &quot;parser.tab.h&quot; // Para los tokens (T_IDENTIFIER, etc.) y YYSTYPE (yylval)

// Prototipo de yyerror para que el scanner pueda llamarlo.
extern void yyerror(const char \*s);

// Función para duplicar yytext y asegurar que la cadena termine en null.
char\* copy\_yytext() {
char\* new\_str = (char\*)malloc(yyleng + 1);
if (new\_str == NULL) {
yyerror("Error de memoria en copy\_yytext");
exit(EXIT\_FAILURE);
}
strncpy(new\_str, yytext, yyleng);
new\_str[yyleng] = '\\0';
return new\_str;
}

%}

%option yylineno
%option noyywrap

DIGIT       [0-9]
ID          [a-zA-Z\_][a-zA-Z0-9\_]*
WHITESPACE  [ \\t\\r]+
NEWLINE     \\n

%%

{WHITESPACE}            { /\* Ignorar espacios en blanco, tabuladores, retornos de carro */ }
{NEWLINE}               { /* yylineno se actualiza automáticamente por Flex. No es necesario hacer nada aquí. \*/ }

"//".\* { /\* Ignorar comentarios de una línea */ }
"/*"([^\*]|\*+[^\*/])*\*+"/" { /* Ignorar comentarios de bloque (manejo básico) \*/ }

"int"                   { return T\_INT; }
"float"                 { return T\_FLOAT; }
"string"                { return T\_STRING\_TYPE; }
"if"                    { return T\_IF; }
"else"                  { return T\_ELSE; }
"while"                 { return T\_WHILE; }
"print"                 { return T\_PRINT; }
"read"                  { return T\_READ; }

"="                     { return T\_ASSIGN; }
"+"                     { return T\_PLUS; }
"-"                     { return T\_MINUS; }
"\*"                     { return T\_MULTIPLY; }
"/"                     { return T\_DIVIDE; }

"=="                    { return T\_EQ; }
"\!="                    { return T\_NEQ; }
"\<"                     { return T\_LT; }
"\>"                     { return T\_GT; }
"\<="                    { return T\_LTE; }
"\>="                    { return T\_GTE; }

"("                     { return T\_LPAREN; }
")"                     { return T\_RPAREN; }
"{"                     { return T\_LBRACE; }
"}"                     { return T\_RBRACE; }
";"                     { return T\_SEMICOLON; }

{DIGIT}+.{DIGIT}+      { yylval.fval = atof(yytext); return T\_FLOAT\_LITERAL; }
{DIGIT}+                { yylval.ival = atoi(yytext); return T\_INTEGER\_LITERAL; }

{ID}                    { yylval.sval = copy\_yytext(); return T\_IDENTIFIER; }

"                             { /\* Inicio de string literal \*/
int c;
char buf[1024]; // Buffer para el contenido del string
int i = 0;
while ((c = input()) \!= '"' && c \!= EOF && c \!= '\\n') {
if (i \< 1023) { // Deja espacio para el terminador nulo
buf[i++] = c;
} else {
yyerror("String literal demasiado largo, excede el buffer interno");
while ((c = input()) \!= '"' && c \!= EOF && c \!= '\\n'); // Consumir el resto
return T\_ERROR; // Retornar token de error (debe estar definido en parser.y)
}
}
buf[i] = '\\0'; // Terminar el string
if (c == '"') {
yylval.sval = strdup(buf);
if (yylval.sval == NULL) {
yyerror("Error de memoria duplicando string literal");
return T\_ERROR;
}
} else {
yyerror("String literal no terminado");
return T\_ERROR;
}
return T\_STRING\_LITERAL;
}

.                       { /\* Caracter inválido \*/
char msg[256];
snprintf(msg, sizeof(msg), "Caracter inesperado: '%.\*s'", yyleng \> 200 ? 200 : yyleng, yytext);
yyerror(msg);
// Considera retornar un token T\_ERROR si lo tienes definido en parser.y
// para permitir que el parser intente recuperarse.
// return T\_ERROR;
}

%%

// La función copy\_yytext() ya está definida en la sección %{ %} de arriba.
// No se necesita yywrap() si se usa %option noyywrap.
// No se necesita main() aquí, ya que el tuyo está en main.cpp.