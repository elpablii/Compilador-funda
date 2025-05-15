%{
// parser.y

// Incluye cabeceras estándar de C y prototipos de Flex/yyerror
// Estas son necesarias para el código en las acciones o para yyerror.
#include <stdio.h>
#include <stdlib.h> // Para malloc, free, strdup, etc.
#include <string.h> // Para strdup

// Prototipos de funciones de Flex
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

// Función de error (Bison la llama en caso de error sintáctico)
// La definición completa estará al final del archivo.
void yyerror(const char *s);

// NO definimos ast_root aquí.
%}

// Este bloque %code requires asegura que ast.hpp se incluya ANTES de que
// Bison defina YYSTYPE (basado en %union) y otras estructuras internas.
// Es crucial para que los tipos del AST sean conocidos por Bison.
%code requires {
    #include "ast.hpp" // Aquí se incluyen las definiciones de Node, DataType, etc.
}

/* Unión para los tipos de valores semánticos asociados con tokens y no terminales.
   Los tipos como Node*, StatementListNode*, DataType están definidos gracias
   a la inclusión de ast.hpp mediante %code requires. Esto ya fue corregido.
*/
%union {
    Node* node;                   // Tipo genérico para nodos del AST
    StatementListNode* stmt_list_node;
    IdentifierNode* id_node;
    VariableDeclarationNode* var_decl_node;
    AssignmentNode* assign_node;
    IfStatementNode* if_node;
    WhileStatementNode* while_node;
    PrintStatementNode* print_node;
    ReadStatementNode* read_node;

    char* sval;                   // Para T_IDENTIFIER, T_STRING_LITERAL
    int ival;                     // Para T_INTEGER_LITERAL
    float fval;                   // Para T_FLOAT_LITERAL
    DataType dtype;               // Para tipos de datos como T_INT, T_FLOAT
}

/* Declaración de tokens (terminales) */
%token <sval> T_IDENTIFIER
%token <ival> T_INTEGER_LITERAL
%token <fval> T_FLOAT_LITERAL
%token <sval> T_STRING_LITERAL // Asumo que esta estaba en tu parser original

%token T_INT T_FLOAT T_STRING_TYPE
%token T_IF T_ELSE T_WHILE
%token T_PRINT T_READ
%token T_ASSIGN
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE
%token T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_SEMICOLON
%token T_ERROR // Asumo que esta estaba en tu parser original


/* Declaración de tipos para no terminales. */
// Asegúrate de que todos tus no terminales que devuelven un valor tengan un tipo aquí.
%type <node> program expression term factor primary_expression comparison_expression statement arithmetic_expression
%type <stmt_list_node> statement_list block
%type <id_node> identifier
%type <var_decl_node> variable_declaration
%type <assign_node> assignment_statement
%type <if_node> if_statement
%type <while_node> while_statement
%type <print_node> print_statement
%type <read_node> read_statement
%type <dtype> type_specifier


/* Precedencia y asociatividad de operadores */
// (Estas líneas se basan en tu parser.y original)
%left T_EQ T_NEQ
%left T_LT T_GT T_LTE T_GTE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_ASSIGN


// Este bloque %code se inserta en el archivo .c generado por Bison.
// Se coloca después de las inclusiones de cabecera y definiciones de tipos de Bison (como yylval).
// En este punto, 'Node' (de ast.hpp, incluido vía %code requires) debería estar completamente definido.
// Si tu error parser.y:31:1 se refiere a esta línea, es aquí donde 'Node' debe ser un tipo conocido.
%code {
    Node* ast_root = nullptr;
}


%%

/* Reglas gramaticales */
// (Estas reglas se basan en tu parser.y original)

program:
    statement_list
        {
            // ast_root (definido en el bloque %code de arriba) debería ser visible aquí.
            // Si tu error parser.y:100:13 se refiere a esta línea, significa que la definición
            // de ast_root anterior no fue exitosa o no está en el ámbito correcto.
            ast_root = new ProgramNode($1);
        }
    ;

statement_list:
    /* lista vacía de sentencias */
        { $$ = new StatementListNode(); }
    | statement_list statement
        {
            if ($2 != nullptr) { // Importante chequear si la sentencia produjo un nodo
                $1->statements.push_back($2);
            }
            $$ = $1;
        }
    ;

statement:
    variable_declaration    { $$ = $1; }
    | assignment_statement  { $$ = $1; }
    | if_statement          { $$ = $1; }
    | while_statement       { $$ = $1; }
    | print_statement       { $$ = $1; }
    | read_statement        { $$ = $1; }
    | block                 { $$ = $1; }
    | T_SEMICOLON           { $$ = nullptr; /* Sentencia vacía, no crea nodo */ }
    | T_ERROR T_SEMICOLON   { yyerrok; $$ = nullptr; /* Recuperación de error simple */ }
    ;

block:
    T_LBRACE statement_list T_RBRACE
        { $$ = $2; } // $2 es un StatementListNode*
    ;

type_specifier:
    T_INT           { $$ = DataType::INT; }
    | T_FLOAT         { $$ = DataType::FLOAT; }
    | T_STRING_TYPE { $$ = DataType::STRING; }
    ;

variable_declaration:
    type_specifier identifier T_SEMICOLON
        { $$ = new VariableDeclarationNode($1, $2, nullptr); }
    | type_specifier identifier T_ASSIGN expression T_SEMICOLON
        { $$ = new VariableDeclarationNode($1, $2, $4); }
    ;

assignment_statement:
    identifier T_ASSIGN expression T_SEMICOLON
        { $$ = new AssignmentNode($1, $3); }
    ;

if_statement:
    T_IF T_LPAREN expression T_RPAREN block
        { $$ = new IfStatementNode($3, $5, nullptr); }
    | T_IF T_LPAREN expression T_RPAREN block T_ELSE block
        { $$ = new IfStatementNode($3, $5, $7); }
    ;

while_statement:
    T_WHILE T_LPAREN expression T_RPAREN block
        { $$ = new WhileStatementNode($3, $5); }
    ;

print_statement:
    T_PRINT T_LPAREN expression T_RPAREN T_SEMICOLON
        { $$ = new PrintStatementNode($3); }
    ;

read_statement:
    T_READ T_LPAREN identifier T_RPAREN T_SEMICOLON
        { $$ = new ReadStatementNode($3); }
    ;

expression:
    comparison_expression { $$ = $1; }
    ;

comparison_expression:
    arithmetic_expression { $$ = $1; }
    | arithmetic_expression T_EQ arithmetic_expression    { $$ = new BinaryOperationNode("==", $1, $3); }
    | arithmetic_expression T_NEQ arithmetic_expression   { $$ = new BinaryOperationNode("!=", $1, $3); }
    | arithmetic_expression T_LT arithmetic_expression    { $$ = new BinaryOperationNode("<", $1, $3); }
    | arithmetic_expression T_GT arithmetic_expression    { $$ = new BinaryOperationNode(">", $1, $3); }
    | arithmetic_expression T_LTE arithmetic_expression   { $$ = new BinaryOperationNode("<=", $1, $3); }
    | arithmetic_expression T_GTE arithmetic_expression   { $$ = new BinaryOperationNode(">=", $1, $3); }
    ;

arithmetic_expression:
    term { $$ = $1; }
    | arithmetic_expression T_PLUS term     { $$ = new BinaryOperationNode("+", $1, $3); }
    | arithmetic_expression T_MINUS term    { $$ = new BinaryOperationNode("-", $1, $3); }
    ;

term:
    factor { $$ = $1; }
    | term T_MULTIPLY factor { $$ = new BinaryOperationNode("*", $1, $3); }
    | term T_DIVIDE factor   { $$ = new BinaryOperationNode("/", $1, $3); }
    ;

factor:
    primary_expression { $$ = $1; }
    ;

primary_expression:
    identifier              { $$ = $1; } // $1 es IdentifierNode*
    | T_INTEGER_LITERAL     { $$ = new NumberLiteralNode($1); }
    | T_FLOAT_LITERAL       { $$ = new FloatLiteralNode($1); }
    | T_STRING_LITERAL      {
                                // $1 (yylval.sval) es una cadena asignada por el scanner (strndup o copy_yytext)
                                // y contiene el valor de la cadena sin comillas.
                                // StringLiteralNode toma std::string. Creamos una y liberamos la memoria de $1.
                                std::string s_val_str($1); // Crear std::string a partir de char*
                                free($1); // Liberar la memoria asignada por strndup/copy_yytext en el scanner
                                $$ = new StringLiteralNode(s_val_str);
                            }
    | T_LPAREN expression T_RPAREN { $$ = $2; }
    ;

identifier:
    T_IDENTIFIER {
                                // $1 (yylval.sval) es una cadena de copy_yytext.
                                // IdentifierNode toma std::string. Creamos una y liberamos la memoria de $1.
                                std::string id_name_str($1); // Crear std::string a partir de char*
                                free($1); // Liberar la memoria asignada por copy_yytext en el scanner
                                $$ = new IdentifierNode(id_name_str);
                            }
    ;

%%

/* Código C adicional */
void yyerror(const char *s) {
    // yytext es el token actual que causó el problema (o cercano).
    // yylineno es el número de línea actual.
    fprintf(stderr, "Error en línea %d cerca de '%s': %s\n", yylineno, yytext, s);
}