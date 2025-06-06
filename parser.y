%{
// parser.y (skeleton en C++ para Bison, refactorizado a español)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>        // std::string
#include "ast.hpp"       // definiciones de Node, DataType, etc.

// Prototipos de Flex/Bison
extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *entradaAnalizador;

// Función de error (se llama en errores sintácticos)
void yyerror(const char *mensaje);
%}

/* Incluir ast.hpp antes de definir YYSTYPE */
%code requires {
    #include "ast.hpp"
}

%union {
    Node*                     nodo;
    ListaSentenciasNode*      listaSentenciasNodo;
    IdentificadorNode*        identificadorNodo;
    DeclaracionVariableNode*  declaracionVariableNodo;
    AsignacionNode*           asignacionNodo;
    SiStatementNode*          siNodo;
    MientrasStatementNode*    mientrasNodo;
    ImprimirStatementNode*    imprimirNodo;
    LeerStatementNode*        leerNodo;

    char*   sval;
    int     ival;
    float   fval;
    DataType dtype;
}

/* Definición de tokens */
%token <sval> T_IDENTIFIER
%token <ival> T_INTEGER_LITERAL
%token <fval> T_FLOAT_LITERAL
%token <sval> T_STRING_LITERAL

%token T_INT T_FLOAT T_STRING_TYPE
%token T_IF T_ELSE T_WHILE
%token T_PRINT T_READ
%token T_ASSIGN T_PLUS T_MINUS T_MULTIPLY T_DIVIDE
%token T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_SEMICOLON
%token T_ERROR

/* Tipos para no-terminales */
%type <nodo> programa sentencia expresion expresionAritmetica termino factor expresionComparacion expresionPrimaria
%type <listaSentenciasNodo> sentenciaLista bloque
%type <identificadorNodo> identificador
%type <declaracionVariableNodo> declaracionVariable
%type <asignacionNodo> asignacionSentencia
%type <siNodo> siSentencia
%type <mientrasNodo> mientrasSentencia
%type <imprimirNodo> imprimirSentencia
%type <leerNodo> leerSentencia
%type <dtype> especificadorTipo

/* Precedencia de operadores */
%left T_EQ T_NEQ
%left T_LT T_GT T_LTE T_GTE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_ASSIGN

%code {
    // ast_root guarda el AST generado
    Node* ast_root = nullptr;
}

%%

programa:
    sentenciaLista
    {
        ast_root = new ProgramaNode($1);
    }
;

sentenciaLista:
      /* vacío */
    {
        $$ = new ListaSentenciasNode();
    }
  | sentenciaLista sentencia
    {
        if ($2) {
            $1->sentencias.push_back($2);
        }
        $$ = $1;
    }
;

sentencia:
      declaracionVariable
    {
        $$ = $1;
    }
  | asignacionSentencia
    {
        $$ = $1;
    }
  | siSentencia
    {
        $$ = $1;
    }
  | mientrasSentencia
    {
        $$ = $1;
    }
  | imprimirSentencia
    {
        $$ = $1;
    }
  | leerSentencia
    {
        $$ = $1;
    }
  | bloque
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

bloque:
    T_LBRACE sentenciaLista T_RBRACE
    {
        $$ = $2;
    }
;

/* Especificador de tipos */
especificadorTipo:
      T_INT
    {
        $$ = DataType::INT;
    }
  | T_FLOAT
    {
        $$ = DataType::FLOAT;
    }
  | T_STRING_TYPE
    {
        $$ = DataType::STRING;
    }
;

declaracionVariable:
      especificadorTipo identificador T_SEMICOLON
    {
        $$ = new DeclaracionVariableNode($1, $2, nullptr);
    }
  | especificadorTipo identificador T_ASSIGN expresion T_SEMICOLON
    {
        $$ = new DeclaracionVariableNode($1, $2, $4);
    }
;

asignacionSentencia:
    identificador T_ASSIGN expresion T_SEMICOLON
    {
        $$ = new AsignacionNode($1, $3);
    }
;

siSentencia:
      T_IF T_LPAREN expresion T_RPAREN bloque
    {
        $$ = new SiStatementNode($3, $5, nullptr);
    }
  | T_IF T_LPAREN expresion T_RPAREN bloque T_ELSE bloque
    {
        $$ = new SiStatementNode($3, $5, $7);
    }
;

mientrasSentencia:
    T_WHILE T_LPAREN expresion T_RPAREN bloque
    {
        $$ = new MientrasStatementNode($3, $5);
    }
;

imprimirSentencia:
    T_PRINT T_LPAREN expresion T_RPAREN T_SEMICOLON
    {
        $$ = new ImprimirStatementNode($3);
    }
;

leerSentencia:
    T_READ T_LPAREN identificador T_RPAREN T_SEMICOLON
    {
        $$ = new LeerStatementNode($3);
    }
;

expresion:
    expresionComparacion
    {
        $$ = $1;
    }
;

expresionComparacion:
      expresionAritmetica
    {
        $$ = $1;
    }
  | expresionAritmetica T_EQ expresionAritmetica
    {
        $$ = new BinaryOperationNode("==", $1, $3);
    }
  | expresionAritmetica T_NEQ expresionAritmetica
    {
        $$ = new BinaryOperationNode("!=", $1, $3);
    }
  | expresionAritmetica T_LT expresionAritmetica
    {
        $$ = new BinaryOperationNode("<", $1, $3);
    }
  | expresionAritmetica T_GT expresionAritmetica
    {
        $$ = new BinaryOperationNode(">", $1, $3);
    }
  | expresionAritmetica T_LTE expresionAritmetica
    {
        $$ = new BinaryOperationNode("<=", $1, $3);
    }
  | expresionAritmetica T_GTE expresionAritmetica
    {
        $$ = new BinaryOperationNode(">=", $1, $3);
    }
;

expresionAritmetica:
      termino
    {
        $$ = $1;
    }
  | expresionAritmetica T_PLUS termino
    {
        $$ = new BinaryOperationNode("+", $1, $3);
    }
  | expresionAritmetica T_MINUS termino
    {
        $$ = new BinaryOperationNode("-", $1, $3);
    }
;

termino:
      factor
    {
        $$ = $1;
    }
  | termino T_MULTIPLY factor
    {
        $$ = new BinaryOperationNode("*", $1, $3);
    }
  | termino T_DIVIDE factor
    {
        $$ = new BinaryOperationNode("/", $1, $3);
    }
;

factor:
    expresionPrimaria
    {
        $$ = $1;
    }
;

expresionPrimaria:
      identificador
    {
        $$ = $1;
    }
  | T_INTEGER_LITERAL
    {
        $$ = new NumberLiteralNode($1);
    }
  | T_FLOAT_LITERAL
    {
        $$ = new FloatLiteralNode($1);
    }
  | T_STRING_LITERAL
    {
        std::string cad($1);
        free($1);
        $$ = new StringLiteralNode(cad);
    }
  | T_LPAREN expresion T_RPAREN
    {
        $$ = $2;
    }
;

identificador:
    T_IDENTIFIER
    {
        std::string nombre($1);
        free($1);
        $$ = new IdentificadorNode(nombre);
    }
;

%%

void yyerror(const char *mensaje) {
    std::fprintf(stderr, "Error en línea %d cerca de '%s': %s\n",
                 yylineno, yytext, mensaje);
}
