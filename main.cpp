// main.cpp
// Punto de entrada del compilador.

#include <cstdio>    // FILE, fopen, fclose, perror, stdin, printf
#include <iostream>  // std::cout
#include "ast.hpp"   // Nodo, imprimirAST
#include <sstream>   // std::ostringstream
#include "semantic.hpp"

// Variables y funciones externas (definidas en Flex/Bison o en parser.y)
extern FILE* entradaAnalizador;         // Archivo de entrada para Flex/Bison
extern Nodo* raizAST;                   // Raíz del AST (poblada por Bison)
extern int analizarSintactico(void);    // Función de análisis sintáctico generada por Bison

int main(int argc, char** argv) {
    // ------------------------------------------------------------------------
    // 1. Preparar la fuente de entrada (archivo o stdin)
    // ------------------------------------------------------------------------
    if (argc > 1) {
        entradaAnalizador = fopen(argv[1], "r");
        if (!entradaAnalizador) {
            perror(argv[1]);  // Error al abrir el archivo
            return 1;
        }
    } else {
        std::printf(
            "Usando entrada estándar. "
            "Escribe código y presiona Ctrl+D (Linux/macOS) "
            "o Ctrl+Z Enter (Windows) para finalizar.\n"
        );
        entradaAnalizador = stdin;
    }

    // ------------------------------------------------------------------------
    // 2. Invocar el parser de Bison
    // ------------------------------------------------------------------------
    std::printf("Iniciando análisis sintáctico...\n");
    int resultado = analizarSintactico();

    // Cerrar el archivo si no es stdin
    if (entradaAnalizador != stdin && entradaAnalizador != nullptr) {
        fclose(entradaAnalizador);
        entradaAnalizador = nullptr;
    }

    // ------------------------------------------------------------------------
    // 3. Revisar el resultado del análisis sintáctico
    // ------------------------------------------------------------------------
    if (resultado == 0) {
        std::printf("Análisis sintáctico completado exitosamente.\n");

        if (raizAST) {
            std::vector<ErrorSemantico> errores;
            if (!analizarSemantica(raizAST, errores)) {
                std::printf("\nErrores semánticos detectados:\n");
                for (const auto& err : errores)
                    std::printf("  - %s\n", err.mensaje.c_str());
                delete raizAST;
                raizAST = nullptr;
                return 2;
            }
            std::printf("\n--- Árbol de Sintaxis Abstracta (AST) ---\n");
            imprimirAST(raizAST, std::cout);
            // Generar código C en un archivo
            FILE* archivoSalida = fopen("output.c", "w");
            if (archivoSalida) {
                std::fprintf(archivoSalida, "// Código generado por el compilador\n");
                std::ostringstream oss;
                generarCodigoDesdeAST(raizAST, oss);
                std::fprintf(archivoSalida, "%s", oss.str().c_str());
                fclose(archivoSalida);
                std::printf("\nCódigo C generado en output.c\n");
            } else {
                std::printf("No se pudo abrir output.c para escritura.\n");
            }
            delete raizAST;      // Liberar memoria del AST
            raizAST = nullptr;
        } else {
            std::printf(
                "No se generó ningún AST "
                "(entrada vacía o sólo errores léxicos/lógicos).\n"
            );
        }
    } else {
        std::printf(
            "Análisis sintáctico fallido. "
            "Código de retorno de analizarSintactico(): %d\n",
            resultado
        );
        // En caso de haber construido parcialmente el AST, liberarlo
        if (raizAST) {
            delete raizAST;
            raizAST = nullptr;
        }
    }

    return resultado;
}
