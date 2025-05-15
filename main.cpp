// main.cpp
// Archivo principal para ejecutar el compilador.

#include <cstdio>   // Para FILE, fopen, fclose, perror, stdin, printf
#include <iostream> // Para std::cout
#include "ast.hpp"  // Para Node, printAST, y la declaración de printAST

// Variables y funciones externas definidas en otros lugares (generadas por Flex/Bison o en parser.y)
extern FILE* yyin;      // Puntero al archivo de entrada actual para Flex
extern Node* ast_root;  // Raíz del AST, será poblada por Bison
extern int yyparse(void); // Función de parsing generada por Bison
// extern int yylineno; // Número de línea actual (manejado por Flex, usado en yyerror)

// La función yyerror es definida en parser.y y es llamada por yyparse.
// No necesita ser declarada aquí si main no la llama directamente.

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]); // Imprime el error del sistema si fopen falla
            return 1;
        }
    } else {
        printf("Usando entrada estándar. Escribe código y presiona Ctrl+D (Linux/macOS) o Ctrl+Z Enter (Windows) para finalizar.\n");
        yyin = stdin; // Leer de la entrada estándar si no se provee archivo
    }

    printf("Iniciando parsing...\n");
    int result = yyparse(); // Inicia el análisis sintáctico

    if (yyin != stdin && yyin != nullptr) { // Solo cerrar si no es stdin y fue abierto exitosamente
        fclose(yyin);
    }

    if (result == 0) {
        printf("Parsing completado exitosamente.\n");
        if (ast_root) {
            printf("\n--- Árbol de Sintaxis Abstracta (AST) ---\n");
            printAST(ast_root, std::cout); // Imprime el AST a la consola
            delete ast_root; // Liberar memoria del AST
            ast_root = nullptr;
        } else {
            printf("AST no generado (posiblemente entrada vacía o solo errores).\n");
        }
    } else {
        // yyerror (en parser.y) ya habrá impreso los detalles del error sintáctico.
        printf("Parsing fallido. Código de retorno de yyparse(): %d\n", result);
        if (ast_root) { // Podría haber un AST parcial si hubo errores y recuperación
            // Decidir si imprimir o no un AST parcial puede depender de la estrategia de recuperación.
            // Por ahora, lo liberamos si existe.
            delete ast_root;
            ast_root = nullptr;
        }
    }

    return result; // 0 si éxito, no cero si hay errores.
}