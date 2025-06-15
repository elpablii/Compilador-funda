// ast.hpp
// Define la estructura básica para los nodos del Árbol de Sintaxis Abstracta (AST).

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream> // Para std::ostream
#include <unordered_map>

// Enumeración para los tipos de nodos del AST
enum class TipoNodo {
    PROGRAMA,
    LISTA_INSTRUCCIONES,
    DECLARACION_VARIABLE,
    ASIGNACION,
    INSTRUCCION_IF,
    INSTRUCCION_WHILE,
    INSTRUCCION_IMPRIMIR,
    INSTRUCCION_LEER,       // Lectura (placeholder: requiere más infraestructura)
    OPERACION_BINARIA,
    OPERACION_UNARIA,      // Por ejemplo, -num
    LITERAL_ENTERO,
    LITERAL_FLOTANTE,
    LITERAL_CADENA,
    LITERAL_BOOLEANO,         // Nuevo tipo de nodo para booleanos
    IDENTIFICADOR
};

// Enumeración para los tipos de datos del lenguaje
enum class TipoDato {
    ENTERO,
    FLOTANTE,
    CADENA,
    BOOLEANO,                 // Nuevo tipo booleano
    VACIO                  // Para funciones o sentencias sin valor de retorno
};

// Clase base para todos los nodos del AST
struct Nodo {
    TipoNodo tipo;

    explicit Nodo(TipoNodo t)
        : tipo(t)
    {}

    virtual ~Nodo() = default;

    // Método virtual para imprimir el AST (útil en depuración)
    virtual void imprimir(std::ostream& os, int indent = 0) const = 0;

    // Método virtual para generar código
    virtual void generarCodigo(std::ostream& os) const = 0;
};

// ----------------------------------------------------------------------------
// Nodo para una lista de instrucciones
// ----------------------------------------------------------------------------
struct NodoListaInstrucciones : public Nodo {
    std::vector<Nodo*> instrucciones;

    NodoListaInstrucciones()
        : Nodo(TipoNodo::LISTA_INSTRUCCIONES)
    {}

    ~NodoListaInstrucciones() override {
        for (Nodo* instr : instrucciones) {
            if (instr) {
                delete instr;
            }
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo raíz del programa
// ----------------------------------------------------------------------------
struct NodoPrograma : public Nodo {
    NodoListaInstrucciones* listaInstrucciones;

    explicit NodoPrograma(NodoListaInstrucciones* li)
        : Nodo(TipoNodo::PROGRAMA),
          listaInstrucciones(li)
    {}

    ~NodoPrograma() override {
        if (listaInstrucciones) {
            delete listaInstrucciones;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales numéricos (enteros)
// ----------------------------------------------------------------------------
struct NodoLiteralEntero : public Nodo {
    int valor;

    explicit NodoLiteralEntero(int val)
        : Nodo(TipoNodo::LITERAL_ENTERO),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de punto flotante
// ----------------------------------------------------------------------------
struct NodoLiteralFlotante : public Nodo {
    float valor;

    explicit NodoLiteralFlotante(float val)
        : Nodo(TipoNodo::LITERAL_FLOTANTE),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales de cadena
// ----------------------------------------------------------------------------
struct NodoLiteralCadena : public Nodo {
    std::string valor;

    explicit NodoLiteralCadena(const std::string& val)
        : Nodo(TipoNodo::LITERAL_CADENA),
          valor(val)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para identificadores
// ----------------------------------------------------------------------------
struct NodoIdentificador : public Nodo {
    std::string nombre;

    explicit NodoIdentificador(const std::string& n)
        : Nodo(TipoNodo::IDENTIFICADOR),
          nombre(n)
    {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para operaciones binarias
// ----------------------------------------------------------------------------
struct NodoOperacionBinaria : public Nodo {
    std::string op; // Operador como cadena (p. ej. "+", "==")
    Nodo* izquierda;
    Nodo* derecha;

    NodoOperacionBinaria(const std::string& oper, Nodo* l, Nodo* r)
        : Nodo(TipoNodo::OPERACION_BINARIA),
          op(oper),
          izquierda(l),
          derecha(r)
    {}

    ~NodoOperacionBinaria() override {
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
struct NodoDeclaracionVariable : public Nodo {
    TipoDato tipoVar;
    NodoIdentificador* identificador;
    Nodo* inicializacion; // Expresión opcional de inicialización

    NodoDeclaracionVariable(TipoDato tv, NodoIdentificador* id, Nodo* init = nullptr)
        : Nodo(TipoNodo::DECLARACION_VARIABLE),
          tipoVar(tv),
          identificador(id),
          inicializacion(init)
    {}

    ~NodoDeclaracionVariable() override {
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
// Nodo para asignaciones
// ----------------------------------------------------------------------------
struct NodoAsignacion : public Nodo {
    NodoIdentificador* identificador;
    Nodo* expresion;

    NodoAsignacion(NodoIdentificador* id, Nodo* expr)
        : Nodo(TipoNodo::ASIGNACION),
          identificador(id),
          expresion(expr)
    {}

    ~NodoAsignacion() override {
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
// Nodo para sentencias if
// ----------------------------------------------------------------------------
struct NodoSi : public Nodo {
    Nodo* condicion;
    Nodo* entonces;
    Nodo* sino; // Puede ser nullptr si no hay else

    NodoSi(Nodo* cond, Nodo* ent, Nodo* si = nullptr)
        : Nodo(TipoNodo::INSTRUCCION_IF),
          condicion(cond),
          entonces(ent),
          sino(si)
    {}

    ~NodoSi() override {
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
struct NodoMientras : public Nodo {
    Nodo* condicion;
    Nodo* cuerpo;

    NodoMientras(Nodo* cond, Nodo* cuer)
        : Nodo(TipoNodo::INSTRUCCION_WHILE),
          condicion(cond),
          cuerpo(cuer)
    {}

    ~NodoMientras() override {
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
// Nodo para imprimir
// ----------------------------------------------------------------------------
struct NodoImprimir : public Nodo {
    Nodo* expresion;

    explicit NodoImprimir(Nodo* expr)
        : Nodo(TipoNodo::INSTRUCCION_IMPRIMIR),
          expresion(expr)
    {}

    ~NodoImprimir() override {
        if (expresion) {
            delete expresion;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para leer
// ----------------------------------------------------------------------------
struct NodoLeer : public Nodo {
    NodoIdentificador* identificador;

    explicit NodoLeer(NodoIdentificador* id)
        : Nodo(TipoNodo::INSTRUCCION_LEER),
          identificador(id)
    {}

    ~NodoLeer() override {
        if (identificador) {
            delete identificador;
        }
    }

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Nodo para literales booleanos
// ----------------------------------------------------------------------------
struct NodoLiteralBooleano : public Nodo {
    bool valor;

    explicit NodoLiteralBooleano(bool v)
        : Nodo(TipoNodo::LITERAL_BOOLEANO), valor(v) {}

    void imprimir(std::ostream& os, int indent = 0) const override;
    void generarCodigo(std::ostream& os) const override;
};

// ----------------------------------------------------------------------------
// Prototipo para imprimir el AST completo
// ----------------------------------------------------------------------------
void printAST(const Nodo* root, std::ostream& os);

// Prototipo para generar código desde el AST completo
void generateCodeFromAST(const Nodo* root, std::ostream& os);

// Declaraciones de utilidad global en español
void imprimirAST(Nodo* raiz, std::ostream& os);
void generarCodigoDesdeAST(Nodo* raiz, std::ostream& os);

extern std::unordered_map<std::string, TipoDato> variableTypes;

#endif // AST_HPP
