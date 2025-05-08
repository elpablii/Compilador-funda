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

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.ide = new std::string(yytext);
    return ID; 
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