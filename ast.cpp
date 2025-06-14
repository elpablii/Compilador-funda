// ast.cpp
// Implementación de los métodos de los nodos del AST.

#include "ast.hpp"
#include <iostream>
#include <unordered_map>

// Función auxiliar para convertir DataType a cadena
std::string tipoDatoAString(DataType dt) {
    switch (dt) {
        case DataType::INT:    return "INT";
        case DataType::FLOAT:  return "FLOAT";
        case DataType::STRING: return "STRING";
        case DataType::BOOL:   return "BOOL";
        case DataType::VOID:   return "VOID";
        default:               return "UNKNOWN_TYPE";
    }
}

void ProgramNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "ProgramNode:\n";
    if (statementList) {
        statementList->print(os, indent + 2);
    }
}

void StatementListNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "StatementListNode:\n";
    for (const auto* stmt : statements) {
        if (stmt) {
            stmt->print(os, indent + 2);
        } else {
            os << std::string(indent + 2, ' ')
               << "NullStatementNode (instrucción vacía)\n";
        }
    }
}

void NumberLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NumberLiteralNode: " << value << "\n";
}

void FloatLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "FloatLiteralNode: " << value << "\n";
}

void StringLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "StringLiteralNode: \"" << value << "\"\n";
}

void IdentifierNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "IdentifierNode: " << name << "\n";
}

void BinaryOperationNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "BinaryOperationNode: " << op << "\n";
    if (left) {
        os << std::string(indent + 2, ' ') << "Left:\n";
        left->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Left: (null)\n";
    }
    if (right) {
        os << std::string(indent + 2, ' ') << "Right:\n";
        right->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Right: (null)\n";
    }
}

void VariableDeclarationNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "VariableDeclarationNode: Type=" << tipoDatoAString(varType) << "\n";
    if (identifier) {
        os << std::string(indent + 2, ' ')
           << "Identifier:\n";
        identifier->print(os, indent + 4);
    }
    if (initialization) {
        os << std::string(indent + 2, ' ')
           << "Initialization:\n";
        initialization->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Initialization: (none)\n";
    }
}

void AssignmentNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "AssignmentNode:\n";
    if (identifier) {
        os << std::string(indent + 2, ' ')
           << "Identifier:\n";
        identifier->print(os, indent + 4);
    }
    if (expression) {
        os << std::string(indent + 2, ' ')
           << "Expression:\n";
        expression->print(os, indent + 4);
    }
}

void IfStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "IfStatementNode:\n";
    if (condition) {
        os << std::string(indent + 2, ' ')
           << "Condition:\n";
        condition->print(os, indent + 4);
    }
    if (thenBranch) {
        os << std::string(indent + 2, ' ')
           << "ThenBranch:\n";
        thenBranch->print(os, indent + 4);
    }
    if (elseBranch) {
        os << std::string(indent + 2, ' ')
           << "ElseBranch:\n";
        elseBranch->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "ElseBranch: (none)\n";
    }
}

void WhileStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "WhileStatementNode:\n";
    if (condition) {
        os << std::string(indent + 2, ' ')
           << "Condition:\n";
        condition->print(os, indent + 4);
    }
    if (body) {
        os << std::string(indent + 2, ' ')
           << "Body:\n";
        body->print(os, indent + 4);
    }
}

void PrintStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "PrintStatementNode:\n";
    if (expression) {
        os << std::string(indent + 2, ' ')
           << "Expression:\n";
        expression->print(os, indent + 4);
    }
}

void ReadStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "ReadStatementNode:\n";
    if (identifier) {
        os << std::string(indent + 2, ' ')
           << "TargetIdentifier:\n";
        identifier->print(os, indent + 4);
    }
}

void BoolLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "BoolLiteralNode: " << (value ? "true" : "false") << "\n";
}
void BoolLiteralNode::generateCode(std::ostream& os) const {
    os << (value ? "1" : "0");
}

std::unordered_map<std::string, DataType> variableTypes;

// Función global para imprimir el AST completo
void printAST(const Node* root, std::ostream& os) {
    if (root) {
        root->print(os, 0);
    } else {
        os << "AST está vacío (raíz nula).\n";
    }
}

// Implementación de generación de código para cada nodo
void ProgramNode::generateCode(std::ostream& os) const {
    os << "#include <stdio.h>\n";
    os << "int main() {\n";
    if (statementList) statementList->generateCode(os);
    os << "    return 0;\n";
    os << "}\n";
}

void StatementListNode::generateCode(std::ostream& os) const {
    for (const auto* stmt : statements) {
        if (stmt) stmt->generateCode(os);
    }
}

void NumberLiteralNode::generateCode(std::ostream& os) const {
    os << value;
}

void FloatLiteralNode::generateCode(std::ostream& os) const {
    os << value;
}

void StringLiteralNode::generateCode(std::ostream& os) const {
    os << '"' << value << '"';
}

void IdentifierNode::generateCode(std::ostream& os) const {
    os << name;
}

void BinaryOperationNode::generateCode(std::ostream& os) const {
    if (op == "!") {
        os << "(!";
        if (left) left->generateCode(os);
        os << ")";
        return;
    }
    os << "(";
    if (left) left->generateCode(os);
    os << " " << op << " ";
    if (right) right->generateCode(os);
    os << ")";
}

void VariableDeclarationNode::generateCode(std::ostream& os) const {
    std::string tipo;
    switch (varType) {
        case DataType::INT: tipo = "int"; break;
        case DataType::FLOAT: tipo = "float"; break;
        case DataType::STRING: tipo = "char*"; break;
        case DataType::BOOL: tipo = "int"; break; // Representar booleanos como int en C
        default: tipo = "int"; break;
    }
    if (identifier) variableTypes[identifier->name] = varType;
    os << "    " << tipo << " ";
    if (identifier) identifier->generateCode(os);
    if (initialization) {
        os << " = ";
        initialization->generateCode(os);
    }
    os << ";\n";
}

void AssignmentNode::generateCode(std::ostream& os) const {
    os << "    ";
    if (identifier) identifier->generateCode(os);
    os << " = ";
    if (expression) expression->generateCode(os);
    os << ";\n";
}

void IfStatementNode::generateCode(std::ostream& os) const {
    os << "    if (";
    if (condition) condition->generateCode(os);
    os << ") {\n";
    if (thenBranch) thenBranch->generateCode(os);
    os << "    }";
    if (elseBranch) {
        os << " else {\n";
        elseBranch->generateCode(os);
        os << "    }";
    }
    os << "\n";
}

void WhileStatementNode::generateCode(std::ostream& os) const {
    os << "    while (";
    if (condition) condition->generateCode(os);
    os << ") {\n";
    if (body) body->generateCode(os);
    os << "    }\n";
}

void PrintStatementNode::generateCode(std::ostream& os) const {
    os << "    printf(";
    if (expression) {
        DataType tipo = DataType::INT;
        if (expression->type == NodeType::IDENTIFIER) {
            auto* id = static_cast<const IdentifierNode*>(expression);
            auto it = variableTypes.find(id->name);
            if (it != variableTypes.end()) tipo = it->second;
        } else if (expression->type == NodeType::STRING_LITERAL) {
            tipo = DataType::STRING;
        } else if (expression->type == NodeType::FLOAT_LITERAL) {
            tipo = DataType::FLOAT;
        } else if (expression->type == NodeType::BOOL_LITERAL) {
            tipo = DataType::BOOL;
        }
        switch (tipo) {
            case DataType::STRING:
                os << "\"%s\\n\", ";
                break;
            case DataType::FLOAT:
                os << "\"%f\\n\", ";
                break;
            case DataType::BOOL:
                os << "\"%d\\n\", ";
                break;
            default:
                os << "\"%d\\n\", ";
        }
        expression->generateCode(os);
    }
    os << ");\n";
}

void ReadStatementNode::generateCode(std::ostream& os) const {
    os << "    scanf(\"%d\", &";
    if (identifier && identifier->type == NodeType::IDENTIFIER) {
        identifier->generateCode(os);
    }
    os << ");\n";
}

void generateCodeFromAST(const Node* root, std::ostream& os) {
    if (root) root->generateCode(os);
    else os << "// AST vacío, no se generó código.\n";
}
