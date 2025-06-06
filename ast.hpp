// ast.hpp
// Define la estructura básica para los nodos del Árbol de Sintaxis Abstracta (AST).

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream> // Para std::ostream

// Enumeración para los tipos de nodos del AST
enum class TipoNodo {
    PROGRAMA,
    LISTA_SENTENCIAS,
    DECLARACION_VARIABLE,
    ASIGNACION,
    SI,
    MIENTRAS,
    IMPRIMIR,
    LEER,
    OPERACION_BINARIA,
    OPERACION_UNARIA,
    LITERAL_ENTERO,
    LITERAL_FLOTANTE,
    LITERAL_CADENA,
    IDENTIFICADOR
};

// Enumeración para los tipos de datos del lenguaje
enum class TipoDato {
    ENTERO,
    FLOTANTE,
    CADENA,
    VACIO
};

// Clase base para todos los nodos del AST
struct Nodo {
    TipoNodo tipo;

    explicit Nodo(TipoNodo t)
        : tipo(t)
    {}

    virtual ~Nodo() = default;

    // Método virtual para imprimir el AST (útil en depuración)
    virtual void imprimir(std::ostream& os, int indent = 0) const {
        os << std::string(indent, ' ') << "Nodo (desconocido)\n";
    }

    // Método virtual para generar código (por defecto no hace nada)
    virtual void generarCodigo(std::ostream& os) const {}
};

// ----------------------------------------------------------------------------
// Nodo para una lista de sentencias
// ----------------------------------------------------------------------------
struct ListaSentenciasNode : public Nodo {
    std::vector<Nodo*> sentencias;

    ListaSentenciasNode()
        : Nodo(TipoNodo::LISTA_SENTENCIAS)
    {}

    ~ListaSentenciasNode() override {
        for (Nodo* stmt : sentencias) {
            if (stmt) {
                delete stmt;
            }
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo raíz del programa
// ----------------------------------------------------------------------------
struct ProgramaNode : public Nodo {
    ListaSentenciasNode* listaSentencias;

    explicit ProgramaNode(ListaSentenciasNode* sl)
        : Nodo(TipoNodo::PROGRAMA),
          listaSentencias(sl)
    {}

    ~ProgramaNode() override {
        if (listaSentencias) {
            delete listaSentencias;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales numéricos (enteros)
// ----------------------------------------------------------------------------
struct LiteralEnteroNode : public Nodo {
    int valor;

    explicit LiteralEnteroNode(int val)
        : Nodo(TipoNodo::LITERAL_ENTERO),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de punto flotante
// ----------------------------------------------------------------------------
struct LiteralFlotanteNode : public Nodo {
    float valor;

    explicit LiteralFlotanteNode(float val)
        : Nodo(TipoNodo::LITERAL_FLOTANTE),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de cadena
// ----------------------------------------------------------------------------
struct LiteralCadenaNode : public Nodo {
    std::string valor;

    explicit LiteralCadenaNode(const std::string& val)
        : Nodo(TipoNodo::LITERAL_CADENA),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para identificadores (nombres de variables)
// ----------------------------------------------------------------------------
struct IdentificadorNode : public Nodo {
    std::string nombre;

    explicit IdentificadorNode(const std::string& n)
        : Nodo(TipoNodo::IDENTIFICADOR),
          nombre(n)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para operaciones binarias (p. ej. a + b, c > d)
// ----------------------------------------------------------------------------
struct OperacionBinariaNode : public Nodo {
    std::string operador; // Operador como cadena (p. ej. "+", "==")
    Nodo* izquierda;
    Nodo* derecha;

    OperacionBinariaNode(const std::string& oper, Nodo* l, Nodo* r)
        : Nodo(TipoNodo::OPERACION_BINARIA),
          operador(oper),
          izquierda(l),
          derecha(r)
    {}

    ~OperacionBinariaNode() override {
        if (izquierda) {
            delete izquierda;
        }
        if (derecha) {
            delete derecha;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para declaración de variables
// ----------------------------------------------------------------------------
struct DeclaracionVariableNode : public Nodo {
    TipoDato tipoVariable;
    IdentificadorNode* identificador;
    Nodo* inicializacion; // Expresión opcional de inicialización

    DeclaracionVariableNode(TipoDato vt, IdentificadorNode* id, Nodo* init = nullptr)
        : Nodo(TipoNodo::DECLARACION_VARIABLE),
          tipoVariable(vt),
          identificador(id),
          inicializacion(init)
    {}

    ~DeclaracionVariableNode() override {
        if (identificador) {
            delete identificador;
        }
        if (inicializacion) {
            delete inicializacion;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para asignaciones (p. ej. x = 10)
// ----------------------------------------------------------------------------
struct AsignacionNode : public Nodo {
    IdentificadorNode* identificador;
    Nodo* expresion;

    AsignacionNode(IdentificadorNode* id, Nodo* expr)
        : Nodo(TipoNodo::ASIGNACION),
          identificador(id),
          expresion(expr)
    {}

    ~AsignacionNode() override {
        if (identificador) {
            delete identificador;
        }
        if (expresion) {
            delete expresion;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para sentencias if-else
// ----------------------------------------------------------------------------
struct SiNode : public Nodo {
    Nodo* condicion;
    ListaSentenciasNode* entonces;
    ListaSentenciasNode* sino; // Puede ser nullptr si no hay else

    SiNode(Nodo* cond, ListaSentenciasNode* thenB, ListaSentenciasNode* elseB = nullptr)
        : Nodo(TipoNodo::SI),
          condicion(cond),
          entonces(thenB),
          sino(elseB)
    {}

    ~SiNode() override {
        if (condicion) {
            delete condicion;
        }
        if (entonces) {
            delete entonces;
        }
        if (sino) {
            delete sino;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para sentencias while
// ----------------------------------------------------------------------------
struct MientrasNode : public Nodo {
    Nodo* condicion;
    ListaSentenciasNode* cuerpo;

    MientrasNode(Nodo* cond, ListaSentenciasNode* b)
        : Nodo(TipoNodo::MIENTRAS),
          condicion(cond),
          cuerpo(b)
    {}

    ~MientrasNode() override {
        if (condicion) {
            delete condicion;
        }
        if (cuerpo) {
            delete cuerpo;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para la sentencia print
// ----------------------------------------------------------------------------
struct ImprimirNode : public Nodo {
    Nodo* expresion;

    explicit ImprimirNode(Nodo* expr)
        : Nodo(TipoNodo::IMPRIMIR),
          expresion(expr)
    {}

    ~ImprimirNode() override {
        if (expresion) {
            delete expresion;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para la sentencia read (placeholder)
// ----------------------------------------------------------------------------
struct LeerNode : public Nodo {
    IdentificadorNode* identificador;

    explicit LeerNode(IdentificadorNode* id)
        : Nodo(TipoNodo::LEER),
          identificador(id)
    {}

    ~LeerNode() override {
        if (identificador) {
            delete identificador;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Prototipo para imprimir el AST completo
// ----------------------------------------------------------------------------
void imprimirAST(const Nodo* raiz, std::ostream& os);

// Prototipo para generar código desde el AST completo
void generarCodigoDesdeAST(const Nodo* raiz, std::ostream& os);

#endif // AST_HPP
