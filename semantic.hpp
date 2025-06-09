#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>

struct SemanticError {
    std::string mensaje;
    int linea;
};

bool analizarSemantica(Node* root, std::vector<SemanticError>& errores);