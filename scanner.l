%{
#include "parser.tab.hpp"
#include <string>
%}

%option c++
%option noyywrap

%%

//Definiendo identificadores para los tipos de variables

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.ide = new std::string(yytext);
    return ID; 
}

//Palabras reservadas enteros

"zi"        {return ZETA:}

// Definiendo la regla correspondiendo a los enteros
[-+]?[0-9]+ {
    yyval.tero = std::stoi(yytext);
    return ENTERO; 
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
[ \t]       ; 
.           { std::cerr << "Error: Carácter inválido\n"; }
%%