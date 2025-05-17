%{
// parser.y (skeleton C para g++)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>       // para std::string
#include "ast.hpp"    // definiciones de Node, DataType, etc.

// Prototipos de funciones y variables de Flex/Bison
extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

// Función de error (Bison la llama en caso de error sintáctico)
void yyerror(const char *s);
%}

// Incluir ast.hpp antes de definir YYSTYPE
%code requires {
    #include "ast.hpp"
}

%union {
    Node*                   node;
    StatementListNode*      stmt_list_node;
    IdentifierNode*         id_node;
    VariableDeclarationNode* var_decl_node;
    AssignmentNode*         assign_node;
    IfStatementNode*        if_node;
    WhileStatementNode*     while_node;
    PrintStatementNode*     print_node;
    ReadStatementNode*      read_node;

    char*   sval;
    int     ival;
    float   fval;
    DataType dtype;
}

/* Tokens */
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

/* No-terminals */
%type <node> program statement expression arithmetic_expression term factor primary_expression comparison_expression
%type <stmt_list_node> statement_list block
%type <id_node> identifier
%type <var_decl_node> variable_declaration
%type <assign_node> assignment_statement
%type <if_node> if_statement
%type <while_node> while_statement
%type <print_node> print_statement
%type <read_node> read_statement
%type <dtype> type_specifier

/* Precedencia */
%left T_EQ T_NEQ
%left T_LT T_GT T_LTE T_GTE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_ASSIGN

%code {
    // ast_root global para guardar el AST final
    Node* ast_root = nullptr;
}

%%

program:
    statement_list            { ast_root = new ProgramNode($1); }
;

statement_list:
      /* vacío */            { $$ = new StatementListNode(); }
    | statement_list statement {
        if ($2) $1->statements.push_back($2);
        $$ = $1;
      }
;

statement:
      variable_declaration    { $$ = $1; }
    | assignment_statement    { $$ = $1; }
    | if_statement            { $$ = $1; }
    | while_statement         { $$ = $1; }
    | print_statement         { $$ = $1; }
    | read_statement          { $$ = $1; }
    | block                   { $$ = $1; }
    | T_SEMICOLON             { $$ = nullptr; }
    | T_ERROR T_SEMICOLON     { yyerrok; $$ = nullptr; }
;

block:
    T_LBRACE statement_list T_RBRACE { $$ = $2; }
;

// Declaración de tipos

type_specifier:
      T_INT                   { $$ = DataType::INT; }
    | T_FLOAT                 { $$ = DataType::FLOAT; }
    | T_STRING_TYPE           { $$ = DataType::STRING; }
;

variable_declaration:
      type_specifier identifier T_SEMICOLON               { $$ = new VariableDeclarationNode($1,$2,nullptr); }
    | type_specifier identifier T_ASSIGN expression T_SEMICOLON { $$ = new VariableDeclarationNode($1,$2,$4); }
;

assignment_statement:
    identifier T_ASSIGN expression T_SEMICOLON            { $$ = new AssignmentNode($1,$3); }
;

if_statement:
      T_IF T_LPAREN expression T_RPAREN block           { $$ = new IfStatementNode($3,$5,nullptr); }
    | T_IF T_LPAREN expression T_RPAREN block T_ELSE block { $$ = new IfStatementNode($3,$5,$7); }
;

while_statement:
    T_WHILE T_LPAREN expression T_RPAREN block           { $$ = new WhileStatementNode($3,$5); }
;

print_statement:
    T_PRINT T_LPAREN expression T_RPAREN T_SEMICOLON     { $$ = new PrintStatementNode($3); }
;

read_statement:
    T_READ T_LPAREN identifier T_RPAREN T_SEMICOLON      { $$ = new ReadStatementNode($3); }
;

expression:
    comparison_expression                               { $$ = $1; }
;

comparison_expression:
      arithmetic_expression                             { $$ = $1; }
    | arithmetic_expression T_EQ arithmetic_expression   { $$ = new BinaryOperationNode("==",$1,$3); }
    | arithmetic_expression T_NEQ arithmetic_expression  { $$ = new BinaryOperationNode("!=",$1,$3); }
    | arithmetic_expression T_LT arithmetic_expression   { $$ = new BinaryOperationNode("<",$1,$3); }
    | arithmetic_expression T_GT arithmetic_expression   { $$ = new BinaryOperationNode(">",$1,$3); }
    | arithmetic_expression T_LTE arithmetic_expression  { $$ = new BinaryOperationNode("<=",$1,$3); }
    | arithmetic_expression T_GTE arithmetic_expression  { $$ = new BinaryOperationNode(">=",$1,$3); }
;

arithmetic_expression:
      term                                             { $$ = $1; }
    | arithmetic_expression T_PLUS term                 { $$ = new BinaryOperationNode("+",$1,$3); }
    | arithmetic_expression T_MINUS term                { $$ = new BinaryOperationNode("-",$1,$3); }
;

term:
      factor                                           { $$ = $1; }
    | term T_MULTIPLY factor                            { $$ = new BinaryOperationNode("*",$1,$3); }
    | term T_DIVIDE factor                              { $$ = new BinaryOperationNode("/",$1,$3); }
;

factor:
    primary_expression                                 { $$ = $1; }
;

primary_expression:
      identifier                                       { $$ = $1; }
    | T_INTEGER_LITERAL                                { $$ = new NumberLiteralNode($1); }
    | T_FLOAT_LITERAL                                  { $$ = new FloatLiteralNode($1); }
    | T_STRING_LITERAL { std::string s($1); free($1); $$ = new StringLiteralNode(s); }
    | T_LPAREN expression T_RPAREN                     { $$ = $2; }
;

identifier:
    T_IDENTIFIER { std::string n($1); free($1); $$ = new IdentifierNode(n); }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error en línea %d cerca de '%s': %s\n", yylineno, yytext, s);
}
