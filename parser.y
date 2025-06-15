%{
// parser.y (esqueleto en C++ para Bison)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>        // std::string
#include "ast.hpp"       // definiciones de Nodo, TipoDato, etc.

// Prototipos de Flex/Bison
extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

// Variable global para el AST
Nodo* raiz_ast = nullptr;

// Función de error (se llama en errores sintácticos)
void yyerror(const char *mensaje);
%}

/* Incluir ast.hpp antes de definir YYSTYPE */
%code requires {
    #include "ast.hpp"
}

%union {
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
}

/* Definición de tokens personalizados Star Wars */
%token <sval> T_IDENTIFIER
%token <ival> T_INTEGER_LITERAL
%token <fval> T_FLOAT_LITERAL
%token <sval> T_STRING_LITERAL

%token T_INT T_FLOAT T_STRING_TYPE
%token T_IF T_ELSE T_WHILE T_FOR
%token T_PRINT T_READ
%token T_ASSIGN T_PLUS T_MINUS T_MULTIPLY T_DIVIDE
%token T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_SEMICOLON
%token T_ERROR
%token T_BOOL T_TRUE T_FALSE
%token T_AND T_OR T_NOT

/* Tipos para no-terminales */
%type <nodo> program statement expression arithmetic_expression term factor primary_expression comparison_expression
%type <nodo_lista_instr> statement_list block
%type <nodo_id> identifier
%type <nodo_decl_var> variable_declaration
%type <nodo_asig> assignment_statement
%type <nodo_si> if_statement
%type <nodo_mientras> while_statement
%type <nodo_imprimir> print_statement
%type <nodo_leer> read_statement
%type <tipo_dato> type_specifier
%type <nodo> bool_literal

/* Precedencia de operadores */
%left T_EQ T_NEQ
%left T_LT T_GT T_LTE T_GTE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_ASSIGN

%%

program:
    statement_list
    {
        raiz_ast = new NodoPrograma($1);
    }
;

statement_list:
      /* vacío */
    {
        $$ = new NodoListaInstrucciones();
    }
  | statement_list statement
    {
        if ($2) {
            $1->instrucciones.push_back($2);
        }
        $$ = $1;
    }
;

statement:
      variable_declaration
    {
        $$ = $1;
    }
  | assignment_statement
    {
        $$ = $1;
    }
  | if_statement
    {
        $$ = $1;
    }
  | while_statement
    {
        $$ = $1;
    }
  | print_statement
    {
        $$ = $1;
    }
  | read_statement
    {
        $$ = $1;
    }
  | block
    {
        $$ = $1;
    }
  | T_SEMICOLON
    {
        $$ = nullptr;  // Instrucción vacía
    }
  | T_ERROR T_SEMICOLON
    {
        yyerrok;
        $$ = nullptr;
    }
;

block:
    T_LBRACE statement_list T_RBRACE
    {
        $$ = $2;
    }
;

/* Especificador de tipos */
type_specifier:
      T_INT
    { $$ = TipoDato::ENTERO; }
  | T_FLOAT
    { $$ = TipoDato::FLOTANTE; }
  | T_STRING_TYPE
    { $$ = TipoDato::CADENA; }
  | T_BOOL
    { $$ = TipoDato::BOOLEANO; }
;

variable_declaration:
      type_specifier identifier T_SEMICOLON
    {
        $$ = new NodoDeclaracionVariable($1, $2, nullptr);
    }
  | type_specifier identifier T_ASSIGN expression T_SEMICOLON
    {
        $$ = new NodoDeclaracionVariable($1, $2, $4);
    }
;

assignment_statement:
    identifier T_ASSIGN expression T_SEMICOLON
    {
        $$ = new NodoAsignacion($1, $3);
    }
;

if_statement:
      T_IF T_LPAREN expression T_RPAREN block
    {
        $$ = new NodoSi($3, $5, nullptr);
    }
  | T_IF T_LPAREN expression T_RPAREN block T_ELSE block
    {
        $$ = new NodoSi($3, $5, $7);
    }
;

while_statement:
    T_WHILE T_LPAREN expression T_RPAREN block
    {
        $$ = new NodoMientras($3, $5);
    }
;

print_statement:
    T_PRINT T_LPAREN expression T_RPAREN T_SEMICOLON
    {
        $$ = new NodoImprimir($3);
    }
;

read_statement:
    T_READ T_LPAREN identifier T_RPAREN T_SEMICOLON
    {
        $$ = new NodoLeer($3);
    }
;

expression:
    expression T_AND expression { $$ = new NodoOperacionBinaria("&&", $1, $3); }
  | expression T_OR expression { $$ = new NodoOperacionBinaria("||", $1, $3); }
  | T_NOT expression           { $$ = new NodoOperacionBinaria("!", $2, nullptr); }
  | comparison_expression     { $$ = $1; }
;

comparison_expression:
      arithmetic_expression
    {
        $$ = $1;
    }
  | arithmetic_expression T_EQ arithmetic_expression
    {
        $$ = new NodoOperacionBinaria("==", $1, $3);
    }
  | arithmetic_expression T_NEQ arithmetic_expression
    {
        $$ = new NodoOperacionBinaria("!=", $1, $3);
    }
  | arithmetic_expression T_LT arithmetic_expression
    {
        $$ = new NodoOperacionBinaria("<", $1, $3);
    }
  | arithmetic_expression T_GT arithmetic_expression
    {
        $$ = new NodoOperacionBinaria(">", $1, $3);
    }
  | arithmetic_expression T_LTE arithmetic_expression
    {
        $$ = new NodoOperacionBinaria("<=", $1, $3);
    }
  | arithmetic_expression T_GTE arithmetic_expression
    {
        $$ = new NodoOperacionBinaria(">=", $1, $3);
    }
;

arithmetic_expression:
      term
    {
        $$ = $1;
    }
  | arithmetic_expression T_PLUS term
    {
        $$ = new NodoOperacionBinaria("+", $1, $3);
    }
  | arithmetic_expression T_MINUS term
    {
        $$ = new NodoOperacionBinaria("-", $1, $3);
    }
;

term:
      factor
    {
        $$ = $1;
    }
  | term T_MULTIPLY factor
    {
        $$ = new NodoOperacionBinaria("*", $1, $3);
    }
  | term T_DIVIDE factor
    {
        $$ = new NodoOperacionBinaria("/", $1, $3);
    }
;

factor:
    primary_expression
    {
        $$ = $1;
    }
;

primary_expression:
      identifier
    { $$ = $1; }
  | T_INTEGER_LITERAL
    { $$ = new NodoLiteralEntero($1); }
  | T_FLOAT_LITERAL
    { $$ = new NodoLiteralFlotante($1); }
  | T_STRING_LITERAL
    { std::string cad($1); free($1); $$ = new NodoLiteralCadena(cad); }
  | bool_literal
    { $$ = $1; }
  | T_LPAREN expression T_RPAREN
    { $$ = $2; }
;
bool_literal:
      T_TRUE  { $$ = new NodoLiteralBooleano(true); }
    | T_FALSE { $$ = new NodoLiteralBooleano(false); }
;

identifier:
    T_IDENTIFIER
    {
        std::string nombre($1);
        free($1);
        $$ = new NodoIdentificador(nombre);
    }
;

%%

void yyerror(const char *mensaje) {
    std::fprintf(stderr, "Error en línea %d cerca de '%s': %s\n",
                 yylineno, yytext, mensaje);
}
