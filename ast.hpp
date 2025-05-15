// ast.hpp
// Define la estructura básica para los nodos del Árbol de Sintaxis Abstracta (AST).

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream> // Para std::ostream
#include <variant>  // Para representar diferentes tipos de valores

// Enumeración para los tipos de nodos del AST
enum class NodeType {
    PROGRAM,
    STATEMENT_LIST,
    VARIABLE_DECLARATION,
    ASSIGNMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    PRINT_STATEMENT,
    READ_STATEMENT, // Placeholder, la lectura real requiere más infraestructura
    BINARY_OPERATION,
    UNARY_OPERATION, // Para -num, por ejemplo
    NUMBER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    IDENTIFIER
};

// Enumeración para los tipos de datos del lenguaje
enum class DataType {
    INT,
    FLOAT,
    STRING,
    VOID // Para funciones o sentencias sin valor de retorno
};

// Estructura base para todos los nodos del AST
struct Node {
    NodeType type;
    virtual ~Node() = default; // Destructor virtual para la herencia
    Node(NodeType t) : type(t) {}

    // Método virtual para imprimir el AST (útil para depuración)
    virtual void print(std::ostream& os, int indent = 0) const {
        os << std::string(indent, ' ') << "Node (Unknown)\n";
    }
};

// Nodo para una lista de sentencias
struct StatementListNode : public Node {
    std::vector<Node*> statements;
    StatementListNode() : Node(NodeType::STATEMENT_LIST) {}
    ~StatementListNode() {
        for (Node* stmt : statements) {
            if (stmt) delete stmt; // Añadir comprobación de nulidad antes de borrar
        }
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo raíz del programa
struct ProgramNode : public Node {
    StatementListNode* statementList;
    ProgramNode(StatementListNode* sl) : Node(NodeType::PROGRAM), statementList(sl) {}
    ~ProgramNode() {
        if (statementList) delete statementList; // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para literales numéricos (enteros)
struct NumberLiteralNode : public Node {
    int value;
    NumberLiteralNode(int val) : Node(NodeType::NUMBER_LITERAL), value(val) {}
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para literales de punto flotante
struct FloatLiteralNode : public Node {
    float value;
    FloatLiteralNode(float val) : Node(NodeType::FLOAT_LITERAL), value(val) {}
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para literales de cadena
struct StringLiteralNode : public Node {
    std::string value;
    StringLiteralNode(const std::string& val) : Node(NodeType::STRING_LITERAL), value(val) {}
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para identificadores (nombres de variables)
struct IdentifierNode : public Node {
    std::string name;
    IdentifierNode(const std::string& n) : Node(NodeType::IDENTIFIER), name(n) {}
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para operaciones binarias (ej. a + b, c > d)
struct BinaryOperationNode : public Node {
    std::string op; // El operador como cadena (ej. "+", "==")
    Node* left;
    Node* right;
    BinaryOperationNode(const std::string& o, Node* l, Node* r)
        : Node(NodeType::BINARY_OPERATION), op(o), left(l), right(r) {}
    ~BinaryOperationNode() {
        if (left) delete left;   // Añadir comprobación de nulidad
        if (right) delete right; // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para declaración de variables
struct VariableDeclarationNode : public Node {
    DataType varType;
    IdentifierNode* identifier;
    Node* initialization; // Expresión opcional de inicialización
    VariableDeclarationNode(DataType vt, IdentifierNode* id, Node* init = nullptr)
        : Node(NodeType::VARIABLE_DECLARATION), varType(vt), identifier(id), initialization(init) {}
    ~VariableDeclarationNode() {
        if (identifier) delete identifier; // Añadir comprobación de nulidad
        if (initialization) delete initialization;
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para asignaciones (ej. x = 10)
struct AssignmentNode : public Node {
    IdentifierNode* identifier;
    Node* expression;
    AssignmentNode(IdentifierNode* id, Node* expr)
        : Node(NodeType::ASSIGNMENT), identifier(id), expression(expr) {}
    ~AssignmentNode() {
        if (identifier) delete identifier; // Añadir comprobación de nulidad
        if (expression) delete expression; // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para sentencias if-else
struct IfStatementNode : public Node {
    Node* condition;
    StatementListNode* thenBranch;
    StatementListNode* elseBranch; // Puede ser nullptr si no hay else
    IfStatementNode(Node* cond, StatementListNode* thenB, StatementListNode* elseB = nullptr)
        : Node(NodeType::IF_STATEMENT), condition(cond), thenBranch(thenB), elseBranch(elseB) {}
    ~IfStatementNode() {
        if (condition) delete condition;   // Añadir comprobación de nulidad
        if (thenBranch) delete thenBranch; // Añadir comprobación de nulidad
        if (elseBranch) delete elseBranch;
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para sentencias while
struct WhileStatementNode : public Node {
    Node* condition;
    StatementListNode* body;
    WhileStatementNode(Node* cond, StatementListNode* b)
        : Node(NodeType::WHILE_STATEMENT), condition(cond), body(b) {}
    ~WhileStatementNode() {
        if (condition) delete condition; // Añadir comprobación de nulidad
        if (body) delete body;           // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para la sentencia print
struct PrintStatementNode : public Node {
    Node* expression;
    PrintStatementNode(Node* expr) : Node(NodeType::PRINT_STATEMENT), expression(expr) {}
    ~PrintStatementNode() {
        if (expression) delete expression; // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};

// Nodo para la sentencia read (placeholder)
struct ReadStatementNode : public Node {
    IdentifierNode* identifier;
    ReadStatementNode(IdentifierNode* id) : Node(NodeType::READ_STATEMENT), identifier(id) {}
    ~ReadStatementNode() {
        if (identifier) delete identifier; // Añadir comprobación de nulidad
    }
    void print(std::ostream& os, int indent = 0) const override;
};


// Prototipo de la función para imprimir el AST globalmente
void printAST(const Node* root, std::ostream& os);

#endif // AST_HPP