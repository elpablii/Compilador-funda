// main.cpp
// Punto de entrada del compilador.

#include <cstdio>    // FILE, fopen, fclose, perror, stdin, printf
#include <iostream>  // std::cout
#include "ast.hpp"   // Node, printAST
#include <sstream>   // std::ostringstream
#include "semantic.hpp"

// Variables y funciones externas (definidas en Flex/Bison o en parser.y)
extern FILE* yyin;         // Archivo de entrada para Flex/Bison
extern Node* ast_root;     // Raíz del AST (poblada por Bison)
extern int yyparse(void);  // Función de análisis sintáctico generada por Bison

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // 1. Preparar la fuente de entrada (archivo o stdin)
    // ------------------------------------------------------------------------
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);  // Error al abrir el archivo
            return 1;
        }
    } else {
        std::printf(
            "Usando entrada estándar. "
            "Escribe código y presiona Ctrl+D (Linux/macOS) "
            "o Ctrl+Z Enter (Windows) para finalizar.\n"
        );
        yyin = stdin;
    }

    // ------------------------------------------------------------------------
    // 2. Invocar el parser de Bison
    // ------------------------------------------------------------------------
    std::printf("Iniciando análisis sintáctico...\n");
    int resultado = yyparse();

    // Cerrar el archivo si no es stdin
    if (yyin != stdin && yyin != nullptr) {
        fclose(yyin);
        yyin = nullptr;
    }

    // ------------------------------------------------------------------------
    // 3. Revisar el resultado del análisis sintáctico
    // ------------------------------------------------------------------------
    if (resultado == 0) {
        std::printf("Análisis sintáctico completado exitosamente.\n");

        if (ast_root) {
            std::vector<SemanticError> errores;
            if (!analizarSemantica(ast_root, errores)) {
                std::printf("\nErrores semánticos detectados:\n");
                for (const auto& err : errores)
                    std::printf("  - %s\n", err.mensaje.c_str());
                delete ast_root;
                ast_root = nullptr;
                return 2;
            }
            std::printf("\n--- Árbol de Sintaxis Abstracta (AST) ---\n");
            printAST(ast_root, std::cout);
            // Generar código C en un archivo
            FILE* fout = fopen("output.c", "w");
            if (fout) {
                std::fprintf(fout, "// Código generado por el compilador\n");
                std::ostringstream oss;
                generateCodeFromAST(ast_root, oss);
                std::fprintf(fout, "%s", oss.str().c_str());
                fclose(fout);
                std::printf("\nCódigo C generado en output.c\n");
            } else {
                std::printf("No se pudo abrir output.c para escritura.\n");
            }
            delete ast_root;      // Liberar memoria del AST
            ast_root = nullptr;
        } else {
            std::printf(
                "No se generó ningún AST "
                "(entrada vacía o sólo errores léxicos/lógicos).\n"
            );
        }
    } else {
        std::printf(
            "Análisis sintáctico fallido. "
            "Código de retorno de yyparse(): %d\n",
            resultado
        );
        // En caso de haber construido parcialmente el AST, liberarlo
        if (ast_root) {
            delete ast_root;
            ast_root = nullptr;
        }
    }

    return resultado;
}
