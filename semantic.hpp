#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>

// Estructura para errores semánticos
struct ErrorSemantico {
    std::string mensaje;
    int linea;
};

// Analiza la semántica del AST y llena el vector de errores si los hay
bool analizarSemantica(Nodo* raiz, std::vector<ErrorSemantico>& errores);