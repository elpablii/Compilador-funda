// main.cpp
// Punto de entrada del compilador.

#include <cstdio>    // FILE, fopen, fclose, perror, stdin, printf
#include <iostream>  // std::cout
#include "ast.hpp"   // Nodo, imprimirAST
#include <sstream>   // std::ostringstream
#include "semantic.hpp"

// Variables y funciones externas (definidas en Flex/Bison o en parser.y)
extern FILE* yyin;         // Archivo de entrada para Flex/Bison
extern Nodo* raiz_ast;     // Raíz del AST (poblada por Bison)
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

        if (raiz_ast) {
            std::vector<ErrorSemantico> errores;
            if (!analizarSemantica(raiz_ast, errores)) {
                std::printf("\nErrores semánticos detectados:\n");
                for (const auto& err : errores)
                    std::printf("  - %s\n", err.mensaje.c_str());
                delete raiz_ast;
                raiz_ast = nullptr;
                return 2;
            }
            std::printf("\n--- Árbol de Sintaxis Abstracta (AST) ---\n");
            imprimirAST(raiz_ast, std::cout);
            // Generar código C en un archivo
            FILE* fout = fopen("output.c", "w");
            if (fout) {
                std::fprintf(fout, "// Código generado por el compilador\n");
                std::ostringstream oss;
                generarCodigoDesdeAST(raiz_ast, oss);
                std::fprintf(fout, "%s", oss.str().c_str());
                fclose(fout);
                std::printf("\nCódigo C generado en output.c\n");
            } else {
                std::printf("No se pudo abrir output.c para escritura.\n");
            }
            delete raiz_ast;      // Liberar memoria del AST
            raiz_ast = nullptr;
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
        if (raiz_ast) {
            delete raiz_ast;
            raiz_ast = nullptr;
        }
    }

    return resultado;
}
