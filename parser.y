%{
#include <iostream>
#include <string>
#include <map>

extern int yylex();
void yyerror(const char *msg);

// tabla de simbolos

std::map<std::string, int> tabla_simbolos;
%}


%language "c++"

%union {
    int tero;
    std::string* ide;
}
//Definicion de tokens
%token <tero> ENTERO
%token <ide> ID
%token IGUAL SUMA MENOS MULTIPLICACION DIVIDE
%token PRTSII PRTSID PUNTO_COMA FINL
// tipo de las declaraciones

%token ZETA


//Precedencias
%left SUMA MENOS
%left MULTIPLICACION DIVIDE
%left NEGATIVO

%%

programa:
    | programa linea
;
linea:
    declaracion PUNTO_COMA  FINL
    | asignamiento PUNTO_COMA FINL
    | prtsi PUNTO_COMA FINL {std::cout << "Resultado: " << $1 << "\n";}
    
;

asignamiento:
    ID IGUAL prtsi {
    } 


prtsi:
 NUMERO                 { $$ = $1; }  
  | prtsi SUMA prtsi         { $$ = $1 + $3; }  
  | prtsi MENOS prtsi        { $$ = $1 - $3; }  
  | prtsi MULTIPLICACION prtsi        { $$ = $1 * $3; }  
  | prtsi DIVIDE prtsi       { $$ = $1 / $3; }  
  | '(' prtsi ')'           { $$ = $2; } 
;

%%

void yyerror(const char *msg) {
    std::cerr << "Error: " << msg << std::endl;
}

int main() {
    yyparse();  
    return 0;
}


