#include "semantic.hpp"
#include <iostream>
#include <typeinfo>

struct SymbolInfo {
    DataType tipo;
    bool inicializada;
};

using TablaSimbolos = std::unordered_map<std::string, SymbolInfo>;

static void recorrerAST(Node* node, TablaSimbolos& tabla, std::vector<SemanticError>& errores);

static DataType obtenerTipo(Node* node, TablaSimbolos& tabla, std::vector<SemanticError>& errores) {
    if (!node) return DataType::VOID;
    switch (node->type) {
        case NodeType::NUMBER_LITERAL: return DataType::INT;
        case NodeType::FLOAT_LITERAL:  return DataType::FLOAT;
        case NodeType::STRING_LITERAL: return DataType::STRING;
        case NodeType::IDENTIFIER: {
            auto* id = static_cast<IdentifierNode*>(node);
            auto it = tabla.find(id->name);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + id->name, 0});
                return DataType::VOID;
            }
            return it->second.tipo;
        }
        case NodeType::BINARY_OPERATION: {
            auto* bin = static_cast<BinaryOperationNode*>(node);
            DataType izq = obtenerTipo(bin->left, tabla, errores);
            DataType der = obtenerTipo(bin->right, tabla, errores);
            if (izq == der) return izq;
            if ((izq == DataType::INT && der == DataType::FLOAT) ||
                (izq == DataType::FLOAT && der == DataType::INT))
                return DataType::FLOAT;
            errores.push_back({"Operación entre tipos incompatibles", 0});
            return DataType::VOID;
        }
        default: return DataType::VOID;
    }
}

static void recorrerAST(Node* node, TablaSimbolos& tabla, std::vector<SemanticError>& errores) {
    if (!node) return;
    switch (node->type) {
        case NodeType::PROGRAM: {
            auto* prog = static_cast<ProgramNode*>(node);
            recorrerAST(prog->statementList, tabla, errores);
            break;
        }
        case NodeType::STATEMENT_LIST: {
            auto* list = static_cast<StatementListNode*>(node);
            for (auto* stmt : list->statements)
                recorrerAST(stmt, tabla, errores);
            break;
        }
        case NodeType::VARIABLE_DECLARATION: {
            auto* decl = static_cast<VariableDeclarationNode*>(node);
            std::string nombre = decl->identifier->name;
            if (tabla.count(nombre)) {
                errores.push_back({"Variable redeclarada: " + nombre, 0});
            } else {
                tabla[nombre] = {decl->varType, decl->initialization != nullptr};
            }
            if (decl->initialization) {
                DataType tipoInit = obtenerTipo(decl->initialization, tabla, errores);
                if (tipoInit != decl->varType && tipoInit != DataType::VOID) {
                    errores.push_back({"Inicialización de tipo incompatible para variable: " + nombre, 0});
                }
            }
            break;
        }
        case NodeType::ASSIGNMENT: {
            auto* asig = static_cast<AssignmentNode*>(node);
            std::string nombre = asig->identifier->name;
            auto it = tabla.find(nombre);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + nombre, 0});
            } else {
                DataType tipoExpr = obtenerTipo(asig->expression, tabla, errores);
                if (tipoExpr != it->second.tipo && tipoExpr != DataType::VOID) {
                    errores.push_back({"Asignación de tipo incompatible a variable: " + nombre, 0});
                }
                it->second.inicializada = true;
            }
            break;
        }
        case NodeType::IF_STATEMENT: {
            auto* ifs = static_cast<IfStatementNode*>(node);
            recorrerAST(ifs->condition, tabla, errores);
            recorrerAST(ifs->thenBranch, tabla, errores);
            if (ifs->elseBranch) recorrerAST(ifs->elseBranch, tabla, errores);
            break;
        }
        case NodeType::WHILE_STATEMENT: {
            auto* wh = static_cast<WhileStatementNode*>(node);
            recorrerAST(wh->condition, tabla, errores);
            recorrerAST(wh->body, tabla, errores);
            break;
        }
        case NodeType::PRINT_STATEMENT: {
            auto* pr = static_cast<PrintStatementNode*>(node);
            recorrerAST(pr->expression, tabla, errores);
            break;
        }
        case NodeType::READ_STATEMENT: {
            auto* rd = static_cast<ReadStatementNode*>(node);
            std::string nombre = rd->identifier->name;
            if (!tabla.count(nombre)) {
                errores.push_back({"Variable no declarada para leer: " + nombre, 0});
            }
            break;
        }
        default: break;
    }
}

bool analizarSemantica(Node* root, std::vector<SemanticError>& errores) {
    TablaSimbolos tabla;
    recorrerAST(root, tabla, errores);
    return errores.empty();
}