#include "semantic.hpp"
#include <iostream>
#include <typeinfo>

// Estructura para la información de cada símbolo en la tabla
struct InfoSimbolo {
    TipoDato tipo;
    bool inicializada;
};

using TablaSimbolos = std::unordered_map<std::string, InfoSimbolo>;

// Prototipos internos
static void recorrerAST(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores);
static TipoDato obtenerTipo(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores);

// Determina el tipo de un nodo de expresión
static TipoDato obtenerTipo(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores) {
    if (!nodo) return TipoDato::VACIO;
    switch (nodo->tipo) {
        case TipoNodo::LITERAL_ENTERO:   return TipoDato::ENTERO;
        case TipoNodo::LITERAL_FLOTANTE: return TipoDato::FLOTANTE;
        case TipoNodo::LITERAL_CADENA:   return TipoDato::CADENA;
        case TipoNodo::IDENTIFICADOR: {
            auto* id = static_cast<IdentificadorNode*>(nodo);
            auto it = tabla.find(id->nombre);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + id->nombre, 0});
                return TipoDato::VACIO;
            }
            return it->second.tipo;
        }
        case TipoNodo::OPERACION_BINARIA: {
            auto* bin = static_cast<OperacionBinariaNode*>(nodo);
            TipoDato izq = obtenerTipo(bin->izquierda, tabla, errores);
            TipoDato der = obtenerTipo(bin->derecha, tabla, errores);
            if (izq == der) return izq;
            if ((izq == TipoDato::ENTERO && der == TipoDato::FLOTANTE) ||
                (izq == TipoDato::FLOTANTE && der == TipoDato::ENTERO))
                return TipoDato::FLOTANTE;
            errores.push_back({"Operación entre tipos incompatibles", 0});
            return TipoDato::VACIO;
        }
        default: return TipoDato::VACIO;
    }
}

// Recorre el AST y verifica reglas semánticas
static void recorrerAST(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores) {
    if (!nodo) return;
    switch (nodo->tipo) {
        case TipoNodo::PROGRAMA: {
            auto* prog = static_cast<ProgramaNode*>(nodo);
            recorrerAST(prog->listaSentencias, tabla, errores);
            break;
        }
        case TipoNodo::LISTA_SENTENCIAS: {
            auto* lista = static_cast<ListaSentenciasNode*>(nodo);
            for (auto* sentencia : lista->sentencias)
                recorrerAST(sentencia, tabla, errores);
            break;
        }
        case TipoNodo::DECLARACION_VARIABLE: {
            auto* decl = static_cast<DeclaracionVariableNode*>(nodo);
            std::string nombre = decl->identificador->nombre;
            if (tabla.count(nombre)) {
                errores.push_back({"Variable redeclarada: " + nombre, 0});
            } else {
                tabla[nombre] = {decl->tipoVariable, decl->inicializacion != nullptr};
            }
            if (decl->inicializacion) {
                TipoDato tipoInit = obtenerTipo(decl->inicializacion, tabla, errores);
                if (tipoInit != decl->tipoVariable && tipoInit != TipoDato::VACIO) {
                    errores.push_back({"Inicialización de tipo incompatible para variable: " + nombre, 0});
                }
            }
            break;
        }
        case TipoNodo::ASIGNACION: {
            auto* asig = static_cast<AsignacionNode*>(nodo);
            std::string nombre = asig->identificador->nombre;
            auto it = tabla.find(nombre);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + nombre, 0});
            } else {
                TipoDato tipoExpr = obtenerTipo(asig->expresion, tabla, errores);
                if (tipoExpr != it->second.tipo && tipoExpr != TipoDato::VACIO) {
                    errores.push_back({"Asignación de tipo incompatible a variable: " + nombre, 0});
                }
                it->second.inicializada = true;
            }
            break;
        }
        case TipoNodo::SI: {
            auto* si = static_cast<SiNode*>(nodo);
            recorrerAST(si->condicion, tabla, errores);
            recorrerAST(si->entonces, tabla, errores);
            if (si->sino) recorrerAST(si->sino, tabla, errores);
            break;
        }
        case TipoNodo::MIENTRAS: {
            auto* mientras = static_cast<MientrasNode*>(nodo);
            recorrerAST(mientras->condicion, tabla, errores);
            recorrerAST(mientras->cuerpo, tabla, errores);
            break;
        }
        case TipoNodo::IMPRIMIR: {
            auto* imp = static_cast<ImprimirNode*>(nodo);
            recorrerAST(imp->expresion, tabla, errores);
            break;
        }
        case TipoNodo::LEER: {
            auto* leer = static_cast<LeerNode*>(nodo);
            std::string nombre = leer->identificador->nombre;
            if (!tabla.count(nombre)) {
                errores.push_back({"Variable no declarada para leer: " + nombre, 0});
            }
            break;
        }
        default: break;
    }
}

// Función principal de análisis semántico
bool analizarSemantica(Nodo* raiz, std::vector<ErrorSemantico>& errores) {
    TablaSimbolos tabla;
    recorrerAST(raiz, tabla, errores);
    return errores.empty();
}