#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>

struct ErrorSemantico {
    std::string mensaje;
    int linea;
};

bool analizarSemantica(Nodo* raiz, std::vector<ErrorSemantico>& errores);