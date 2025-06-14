// ast.hpp
// Define la estructura básica para los nodos del Árbol de Sintaxis Abstracta (AST).

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream> // Para std::ostream
#include <unordered_map>

// Enumeración para los tipos de nodos del AST
enum class NodeType {
    PROGRAM,
    STATEMENT_LIST,
    VARIABLE_DECLARATION,
    ASSIGNMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    PRINT_STATEMENT,
    READ_STATEMENT,       // Lectura (placeholder: requiere más infraestructura)
    BINARY_OPERATION,
    UNARY_OPERATION,      // Por ejemplo, -num
    NUMBER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    BOOL_LITERAL,         // Nuevo tipo de nodo para booleanos
    IDENTIFIER
};

// Enumeración para los tipos de datos del lenguaje
enum class DataType {
    INT,
    FLOAT,
    STRING,
    BOOL,                 // Nuevo tipo booleano
    VOID                  // Para funciones o sentencias sin valor de retorno
};

// Clase base para todos los nodos del AST
struct Node {
    NodeType type;

    explicit Node(NodeType t)
        : type(t)
    {}

    virtual ~Node() = default;

    // Método virtual para imprimir el AST (útil en depuración)
    virtual void print(std::ostream& os, int indent = 0) const {
        os << std::string(indent, ' ') << "Nodo (desconocido)\n";
    }

    // Método virtual para generar código (por defecto no hace nada)
    virtual void generateCode(std::ostream& os) const {}
};

// ----------------------------------------------------------------------------
// Nodo para una lista de sentencias
// ----------------------------------------------------------------------------
struct StatementListNode : public Node {
    std::vector<Node*> statements;

    StatementListNode()
        : Node(NodeType::STATEMENT_LIST)
    {}

    ~StatementListNode() override {
        for (Node* stmt : statements) {
            if (stmt) {
                delete stmt;
            }
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo raíz del programa
// ----------------------------------------------------------------------------
struct ProgramNode : public Node {
    StatementListNode* statementList;

    explicit ProgramNode(StatementListNode* sl)
        : Node(NodeType::PROGRAM),
          statementList(sl)
    {}

    ~ProgramNode() override {
        if (statementList) {
            delete statementList;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales numéricos (enteros)
// ----------------------------------------------------------------------------
struct NumberLiteralNode : public Node {
    int value;

    explicit NumberLiteralNode(int val)
        : Node(NodeType::NUMBER_LITERAL),
          value(val)
    {}

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de punto flotante
// ----------------------------------------------------------------------------
struct FloatLiteralNode : public Node {
    float value;

    explicit FloatLiteralNode(float val)
        : Node(NodeType::FLOAT_LITERAL),
          value(val)
    {}

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de cadena
// ----------------------------------------------------------------------------
struct StringLiteralNode : public Node {
    std::string value;

    explicit StringLiteralNode(const std::string& val)
        : Node(NodeType::STRING_LITERAL),
          value(val)
    {}

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para identificadores (nombres de variables)
// ----------------------------------------------------------------------------
struct IdentifierNode : public Node {
    std::string name;

    explicit IdentifierNode(const std::string& n)
        : Node(NodeType::IDENTIFIER),
          name(n)
    {}

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para operaciones binarias (p. ej. a + b, c > d)
// ----------------------------------------------------------------------------
struct BinaryOperationNode : public Node {
    std::string op; // Operador como cadena (p. ej. "+", "==")
    Node* left;
    Node* right;

    BinaryOperationNode(const std::string& oper, Node* l, Node* r)
        : Node(NodeType::BINARY_OPERATION),
          op(oper),
          left(l),
          right(r)
    {}

    ~BinaryOperationNode() override {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para declaración de variables
// ----------------------------------------------------------------------------
struct VariableDeclarationNode : public Node {
    DataType varType;
    IdentifierNode* identifier;
    Node* initialization; // Expresión opcional de inicialización

    VariableDeclarationNode(DataType vt, IdentifierNode* id, Node* init = nullptr)
        : Node(NodeType::VARIABLE_DECLARATION),
          varType(vt),
          identifier(id),
          initialization(init)
    {}

    ~VariableDeclarationNode() override {
        if (identifier) {
            delete identifier;
        }
        if (initialization) {
            delete initialization;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para asignaciones (p. ej. x = 10)
// ----------------------------------------------------------------------------
struct AssignmentNode : public Node {
    IdentifierNode* identifier;
    Node* expression;

    AssignmentNode(IdentifierNode* id, Node* expr)
        : Node(NodeType::ASSIGNMENT),
          identifier(id),
          expression(expr)
    {}

    ~AssignmentNode() override {
        if (identifier) {
            delete identifier;
        }
        if (expression) {
            delete expression;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para sentencias if-else
// ----------------------------------------------------------------------------
struct IfStatementNode : public Node {
    Node* condition;
    StatementListNode* thenBranch;
    StatementListNode* elseBranch; // Puede ser nullptr si no hay else

    IfStatementNode(Node* cond, StatementListNode* thenB, StatementListNode* elseB = nullptr)
        : Node(NodeType::IF_STATEMENT),
          condition(cond),
          thenBranch(thenB),
          elseBranch(elseB)
    {}

    ~IfStatementNode() override {
        if (condition) {
            delete condition;
        }
        if (thenBranch) {
            delete thenBranch;
        }
        if (elseBranch) {
            delete elseBranch;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para sentencias while
// ----------------------------------------------------------------------------
struct WhileStatementNode : public Node {
    Node* condition;
    StatementListNode* body;

    WhileStatementNode(Node* cond, StatementListNode* b)
        : Node(NodeType::WHILE_STATEMENT),
          condition(cond),
          body(b)
    {}

    ~WhileStatementNode() override {
        if (condition) {
            delete condition;
        }
        if (body) {
            delete body;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para la sentencia print
// ----------------------------------------------------------------------------
struct PrintStatementNode : public Node {
    Node* expression;

    explicit PrintStatementNode(Node* expr)
        : Node(NodeType::PRINT_STATEMENT),
          expression(expr)
    {}

    ~PrintStatementNode() override {
        if (expression) {
            delete expression;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para la sentencia read (placeholder)
// ----------------------------------------------------------------------------
struct ReadStatementNode : public Node {
    IdentifierNode* identifier;

    explicit ReadStatementNode(IdentifierNode* id)
        : Node(NodeType::READ_STATEMENT),
          identifier(id)
    {}

    ~ReadStatementNode() override {
        if (identifier) {
            delete identifier;
        }
    }

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales booleanos
// ----------------------------------------------------------------------------
struct BoolLiteralNode : public Node {
    bool value;

    explicit BoolLiteralNode(bool val)
        : Node(NodeType::BOOL_LITERAL), value(val) {}

    void print(std::ostream& os, int indent = 0) const override;
    void generateCode(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Prototipo para imprimir el AST completo
// ----------------------------------------------------------------------------
void printAST(const Node* root, std::ostream& os);

// Prototipo para generar código desde el AST completo
void generateCodeFromAST(const Node* root, std::ostream& os);

extern std::unordered_map<std::string, DataType> variableTypes;

#endif // AST_HPP
