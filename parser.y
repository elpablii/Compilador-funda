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
    NodoFuncion*              nodo_funcion;
    NodoReturn*               nodo_return;
    NodoLlamadaFuncion*       nodo_llamada_funcion;

    char*   sval;
    int     ival;
    float   fval;
    TipoDato tipo_dato;
    std::vector<NodoDeclaracionVariable*>* param_list;
    std::vector<Nodo*>*       expr_list;
    std::vector<Nodo*>*       nodo_expr_list;
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
%token T_COMMA
%token T_ERROR
%token T_BOOL T_TRUE T_FALSE
%token T_AND T_OR T_NOT
%token T_FUNCTION T_RETURN

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
%type <nodo_funcion> function_declaration
%type <nodo_return> return_statement
%type <param_list> parameter_list parameter_list_nonempty
%type <nodo_decl_var> parameter_declaration
%type <nodo_llamada_funcion> function_call
%type <expr_list> argument_list argument_list_nonempty
%type <nodo_expr_list> print_arg_list print_arg_list_nonempty

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
  | function_declaration
    {
        $$ = $1;
    }
  | return_statement
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
        // Si es un entero y la expresión es flotante, convertimos implícitamente
        if ($1 == TipoDato::ENTERO && dynamic_cast<NodoLiteralFlotante*>($4)) {
            auto* flotante = static_cast<NodoLiteralFlotante*>($4);
            auto* entero = new NodoLiteralEntero(static_cast<int>(flotante->valor));
            delete $4;
            $$ = new NodoDeclaracionVariable($1, $2, entero);
        } else {
            $$ = new NodoDeclaracionVariable($1, $2, $4);
        }
    }
;

assignment_statement:
    identifier T_ASSIGN expression T_SEMICOLON
    {
        // Si la variable es entera y la expresión es flotante, convertimos implícitamente
        if (dynamic_cast<NodoLiteralFlotante*>($3)) {
            auto* flotante = static_cast<NodoLiteralFlotante*>($3);
            auto* entero = new NodoLiteralEntero(static_cast<int>(flotante->valor));
            delete $3;
            $$ = new NodoAsignacion($1, entero);
        } else {
            $$ = new NodoAsignacion($1, $3);
        }
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
    T_PRINT T_LPAREN print_arg_list T_RPAREN T_SEMICOLON
    {
        $$ = new NodoImprimir($3);
    }
;
print_arg_list:
      /* vacío */ { $$ = new std::vector<Nodo*>(); }
    | print_arg_list_nonempty { $$ = $1; }
;
print_arg_list_nonempty:
      expression { auto v = new std::vector<Nodo*>(); v->push_back($1); $$ = v; }
    | print_arg_list_nonempty T_COMMA expression { $1->push_back($3); $$ = $1; }
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
  | function_call             { $$ = $1; }
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
      T_INTEGER_LITERAL
    {
        $$ = new NodoLiteralEntero($1);
    }
  | T_FLOAT_LITERAL
    {
        $$ = new NodoLiteralFlotante($1);
    }
  | T_STRING_LITERAL
    {
        $$ = new NodoLiteralCadena($1);
    }
  | T_TRUE
    {
        $$ = new NodoLiteralBooleano(true);
    }
  | T_FALSE
    {
        $$ = new NodoLiteralBooleano(false);
    }
  | identifier
    {
        $$ = $1;
    }
  | T_LPAREN expression T_RPAREN
    {
        $$ = $2;
    }
  | function_call
    {
        $$ = $1;
    }
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

function_declaration:
    T_FUNCTION type_specifier identifier T_LPAREN parameter_list T_RPAREN block
    {
        $$ = new NodoFuncion($2, $3, $5, $7);
    }
;

parameter_list:
      /* vacío */ { $$ = new std::vector<NodoDeclaracionVariable*>(); }
    | parameter_list_nonempty { $$ = $1; }
;
parameter_list_nonempty:
      parameter_declaration { auto v = new std::vector<NodoDeclaracionVariable*>(); v->push_back($1); $$ = v; }
    | parameter_list_nonempty T_COMMA parameter_declaration { $1->push_back($3); $$ = $1; }
;
parameter_declaration:
    type_specifier identifier { $$ = new NodoDeclaracionVariable($1, $2, nullptr); }
;

return_statement:
    T_RETURN expression T_SEMICOLON { $$ = new NodoReturn($2); }
;

function_call:
    identifier T_LPAREN argument_list T_RPAREN { $$ = new NodoLlamadaFuncion($1, $3); }
;
argument_list:
      /* vacío */ { $$ = new std::vector<Nodo*>(); }
    | argument_list_nonempty { $$ = $1; }
;
argument_list_nonempty:
      expression { auto v = new std::vector<Nodo*>(); v->push_back($1); $$ = v; }
    | argument_list_nonempty T_COMMA expression { $1->push_back($3); $$ = $1; }
;

%%

void yyerror(const char *mensaje) {
    std::fprintf(stderr, "Error en línea %d cerca de '%s': %s\n",
                 yylineno, yytext, mensaje);
}
