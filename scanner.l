//Flex

%{
#include "parser.tab.hpp"
#include <string>
#include <cstdlib>
%}

%option c++
%option noyywrap
%option yylineno

%%

//Definiendo identificadores para los tipos de variables

<<<<<<< Updated upstream
[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.ide = new std::string(yytext);
    return ID; 
=======
"//".*               { /* Ignorar comentario de línea */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* Ignorar comentario de bloque */ }

"enterito"           { return T_INT; }
"racional"           { return T_FLOAT; }
"textito"          { return T_STRING_TYPE; }
"SI"                 { return T_IF; }
"entonces"           { return T_ELSE; }
"mientras"         { return T_WHILE; }
"imprima"          { return T_PRINT; }
"lease"            { return T_READ; }

"igual"            { return T_ASSIGN; }
"suma"             { return T_PLUS; }
"resta"            { return T_MINUS; }
"por"              { return T_MULTIPLY; }
"dividido"         { return T_DIVIDE; }

"equivalea"        { return T_EQ; }
"noequivalea"      { return T_NEQ; }
"menoroigual"      { return T_LTE; }
"mayoroigual"      { return T_GTE; }
"mayorcito"        { return T_GT; }
"menorcito"        { return T_LT; }

"fin"                { return T_SEMICOLON; }

"("                  { return T_LPAREN; }
")"                  { return T_RPAREN; }
"{"                  { return T_LBRACE; }
"}"                  { return T_RBRACE; }

{DIGITO}+"."{DIGITO}+ {
    yylval.fval = atof(yytext);
    return T_FLOAT_LITERAL;
>>>>>>> Stashed changes
}

//Palabras reservadas enteros

"zi"        {return ZETA:}
"fl"        {return FLOTANTE_KEYWORD:}

// Definiendo la regla correspondiendo a los enteros
[-+]?[0-9]+ {
    yyval.tero = std::stoi(yytext);
    return ENTERO; 
}

// Definiendo la regla correspondiendo a los flotantes
[-+]?([0-9]*\.[0-9]+|[0-9]+\.)([eE][-+]?[0-9]+)? {
    yylval.fval = std::stod(yytext);
    return FLOTANTE_LITERAL;
}



// Operadores y simbolos
"="         {return IGUAL;}
"+"         {return SUMA;}
"-"         { return MENOS; }  
"*"         { return MULTIPLICACION; } 
"/"         { return DIVIDE; }
";"         {return PUNTO_COMA;}
"("         {return PRTSII}
")"         {return PRTSID}
\n          { return FINL; }    
[ \t]       ; //ignora espacio y tabs
.           { std::cerr << "Error: Carácter inválido\n"; }
%%