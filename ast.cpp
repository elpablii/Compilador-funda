// ast.cpp
// Implementación de los métodos de los nodos del AST.

#include "ast.hpp"
#include <iostream>

// Helper para convertir DataType a string
std::string dataTypeToString(DataType dt) {
    switch (dt) {
        case DataType::INT: return "INT";
        case DataType::FLOAT: return "FLOAT";
        case DataType::STRING: return "STRING";
        case DataType::VOID: return "VOID";
        default: return "UNKNOWN_TYPE";
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
            os << std::string(indent + 2, ' ') << "NullStatementNode (or empty statement)\n";
        }
    }
}

void NumberLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NumberLiteralNode: " << value << "\n";
}

void FloatLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "FloatLiteralNode: " << value << "\n";
}

void StringLiteralNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "StringLiteralNode: \"" << value << "\"\n";
}

void IdentifierNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "IdentifierNode: " << name << "\n";
}

void BinaryOperationNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "BinaryOperationNode: " << op << "\n";
    if (left) {
        os << std::string(indent + 2, ' ') << "Left:\n";
        left->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ') << "Left: (null)\n";
    }
    if (right) {
        os << std::string(indent + 2, ' ') << "Right:\n";
        right->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ') << "Right: (null)\n";
    }
}

void VariableDeclarationNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "VariableDeclarationNode: Type=" << dataTypeToString(varType) << "\n";
    if (identifier) {
        os << std::string(indent + 2, ' ') << "Identifier:\n";
        identifier->print(os, indent + 4);
    }
    if (initialization) {
        os << std::string(indent + 2, ' ') << "Initialization:\n";
        initialization->print(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ') << "Initialization: (none)\n";
    }
}

void AssignmentNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "AssignmentNode:\n";
    if (identifier) {
        os << std::string(indent + 2, ' ') << "Identifier:\n";
        identifier->print(os, indent + 4);
    }
    if (expression) {
        os << std::string(indent + 2, ' ') << "Expression:\n";
        expression->print(os, indent + 4);
    }
}

void IfStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "IfStatementNode:\n";
    if (condition) {
        os << std::string(indent + 2, ' ') << "Condition:\n";
        condition->print(os, indent + 4);
    }
    if (thenBranch) {
        os << std::string(indent + 2, ' ') << "ThenBranch:\n";
        thenBranch->print(os, indent + 4);
    }
    if (elseBranch) {
        os << std::string(indent + 2, ' ') << "ElseBranch:\n";
        elseBranch->print(os, indent + 4);
    } else {
         os << std::string(indent + 2, ' ') << "ElseBranch: (none)\n";
    }
}

void WhileStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "WhileStatementNode:\n";
    if (condition) {
        os << std::string(indent + 2, ' ') << "Condition:\n";
        condition->print(os, indent + 4);
    }
    if (body) {
        os << std::string(indent + 2, ' ') << "Body:\n";
        body->print(os, indent + 4);
    }
}

void PrintStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "PrintStatementNode:\n";
    if (expression) {
        os << std::string(indent + 2, ' ') << "Expression:\n";
        expression->print(os, indent + 4);
    }
}

void ReadStatementNode::print(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "ReadStatementNode:\n";
    if (identifier) {
        os << std::string(indent + 2, ' ') << "TargetIdentifier:\n";
        identifier->print(os, indent + 4);
    }
}


// Función global para imprimir el AST
void printAST(const Node* root, std::ostream& os) {
    if (root) {
        root->print(os, 0);
    } else {
        os << "AST is empty (null root).\n";
    }
}