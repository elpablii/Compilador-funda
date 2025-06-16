#include "semantic.hpp"
#include <iostream>
#include <typeinfo>

struct InfoSimbolo {
    TipoDato tipo;
    bool inicializada;
};

using TablaSimbolos = std::unordered_map<std::string, InfoSimbolo>;

static void recorrerAST(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores);

static TipoDato obtenerTipo(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores) {
    if (!nodo) return TipoDato::VACIO;
    switch (nodo->tipo) {
        case TipoNodo::LITERAL_ENTERO: return TipoDato::ENTERO;
        case TipoNodo::LITERAL_FLOTANTE:  return TipoDato::FLOTANTE;
        case TipoNodo::LITERAL_CADENA: return TipoDato::CADENA;
        case TipoNodo::LITERAL_BOOLEANO:   return TipoDato::BOOLEANO;
        case TipoNodo::OPERACION_BINARIA: {
            auto* bin = static_cast<NodoOperacionBinaria*>(nodo);
            // Aquí no se usan los nombres de tokens, solo los valores de los operadores
            if (bin->op == "&&" || bin->op == "||") {
                TipoDato izq = obtenerTipo(bin->izquierda, tabla, errores);
                TipoDato der = obtenerTipo(bin->derecha, tabla, errores);
                if ((izq == TipoDato::BOOLEANO || izq == TipoDato::ENTERO) && (der == TipoDato::BOOLEANO || der == TipoDato::ENTERO))
                    return TipoDato::BOOLEANO;
                errores.push_back({"Operación lógica entre tipos incompatibles", 0});
                return TipoDato::VACIO;
            }
            if (bin->op == "!") {
                TipoDato izq = obtenerTipo(bin->izquierda, tabla, errores);
                if (izq == TipoDato::BOOLEANO || izq == TipoDato::ENTERO)
                    return TipoDato::BOOLEANO;
                errores.push_back({"Negación lógica sobre tipo incompatible", 0});
                return TipoDato::VACIO;
            }
            if (bin->op == "equilibrio" || bin->op == "rebelde" || bin->op == "highground" || bin->op == "youUnderestimateMyPower" || bin->op == "padawan" || bin->op == "maestro")
                return TipoDato::BOOLEANO;
            TipoDato izq = obtenerTipo(bin->izquierda, tabla, errores);
            TipoDato der = obtenerTipo(bin->derecha, tabla, errores);
            if (izq == der) return izq;
            if ((izq == TipoDato::ENTERO && der == TipoDato::FLOTANTE) ||
                (izq == TipoDato::FLOTANTE && der == TipoDato::ENTERO))
                return TipoDato::FLOTANTE;
            errores.push_back({"Operación entre tipos incompatibles", 0});
            return TipoDato::VACIO;
        }
        case TipoNodo::IDENTIFICADOR: {
            auto* id = static_cast<NodoIdentificador*>(nodo);
            auto it = tabla.find(id->nombre);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + id->nombre, 0});
                return TipoDato::VACIO;
            }
            return it->second.tipo;
        }
        case TipoNodo::OPERACION_UNARIA: // Si tienes nodos unarios
            // Implementar si es necesario
            return TipoDato::VACIO;
        default:
            // Soporte para literales booleanos
            if (dynamic_cast<NodoLiteralBooleano*>(nodo)) return TipoDato::BOOLEANO;
            return TipoDato::VACIO;
    }
}

static void recorrerAST(Nodo* nodo, TablaSimbolos& tabla, std::vector<ErrorSemantico>& errores) {
    if (!nodo) return;
    switch (nodo->tipo) {
        case TipoNodo::PROGRAMA: {
            auto* prog = static_cast<NodoPrograma*>(nodo);
            recorrerAST(prog->listaInstrucciones, tabla, errores);
            break;
        }
        case TipoNodo::LISTA_INSTRUCCIONES: {
            auto* list = static_cast<NodoListaInstrucciones*>(nodo);
            for (auto* stmt : list->instrucciones)
                recorrerAST(stmt, tabla, errores);
            break;
        }
        case TipoNodo::DECLARACION_VARIABLE: {
            auto* decl = static_cast<NodoDeclaracionVariable*>(nodo);
            std::string nombre = decl->identificador->nombre;
            if (tabla.count(nombre)) {
                errores.push_back({"Variable redeclarada: " + nombre, 0});
            } else {
                tabla[nombre] = {decl->tipoVar, decl->inicializacion != nullptr};
            }
            if (decl->inicializacion) {
                TipoDato tipoInit = obtenerTipo(decl->inicializacion, tabla, errores);
                // Permitir asignación entre int y bool
                if (!((decl->tipoVar == tipoInit) ||
                      (decl->tipoVar == TipoDato::ENTERO && tipoInit == TipoDato::BOOLEANO) ||
                      (decl->tipoVar == TipoDato::BOOLEANO && tipoInit == TipoDato::ENTERO) ||
                      tipoInit == TipoDato::VACIO)) {
                    errores.push_back({"Inicialización de tipo incompatible para variable: " + nombre, 0});
                }
            }
            break;
        }
        case TipoNodo::ASIGNACION: {
            auto* asig = static_cast<NodoAsignacion*>(nodo);
            std::string nombre = asig->identificador->nombre;
            auto it = tabla.find(nombre);
            if (it == tabla.end()) {
                errores.push_back({"Variable no declarada: " + nombre, 0});
            } else {
                TipoDato tipoExpr = obtenerTipo(asig->expresion, tabla, errores);
                // Permitir asignación entre int y bool
                if (!((it->second.tipo == tipoExpr) ||
                      (it->second.tipo == TipoDato::ENTERO && tipoExpr == TipoDato::BOOLEANO) ||
                      (it->second.tipo == TipoDato::BOOLEANO && tipoExpr == TipoDato::ENTERO) ||
                      tipoExpr == TipoDato::VACIO)) {
                    errores.push_back({"Asignación de tipo incompatible a variable: " + nombre, 0});
                }
                it->second.inicializada = true;
            }
            break;
        }
        case TipoNodo::INSTRUCCION_IF: {
            auto* ifs = static_cast<NodoSi*>(nodo);
            recorrerAST(ifs->condicion, tabla, errores);
            recorrerAST(ifs->entonces, tabla, errores);
            if (ifs->sino) recorrerAST(ifs->sino, tabla, errores);
            break;
        }
        case TipoNodo::INSTRUCCION_WHILE: {
            auto* wh = static_cast<NodoMientras*>(nodo);
            recorrerAST(wh->condicion, tabla, errores);
            recorrerAST(wh->cuerpo, tabla, errores);
            break;
        }
        case TipoNodo::INSTRUCCION_IMPRIMIR: {
            auto* pr = static_cast<NodoImprimir*>(nodo);
            if (pr->expresiones) {
                for (auto* e : *pr->expresiones) {
                    recorrerAST(e, tabla, errores);
                }
            }
            break;
        }
        case TipoNodo::INSTRUCCION_LEER: {
            auto* rd = static_cast<NodoLeer*>(nodo);
            std::string nombre = rd->identificador->nombre;
            if (!tabla.count(nombre)) {
                errores.push_back({"Variable no declarada para leer: " + nombre, 0});
            }
            break;
        }
        case TipoNodo::FUNCION: {
            auto* fun = static_cast<NodoFuncion*>(nodo);
            // Nuevo ámbito para parámetros
            TablaSimbolos tablaLocal = tabla;
            if (fun->parametros) {
                for (auto* p : *fun->parametros) {
                    std::string nombre = p->identificador->nombre;
                    tablaLocal[nombre] = {p->tipoVar, true};
                }
            }
            recorrerAST(fun->cuerpo, tablaLocal, errores);
            break;
        }
        case TipoNodo::RETURN: {
            auto* ret = static_cast<NodoReturn*>(nodo);
            if (ret->valor) obtenerTipo(ret->valor, tabla, errores);
            break;
        }
        case TipoNodo::LLAMADA_FUNCION: {
            auto* call = static_cast<NodoLlamadaFuncion*>(nodo);
            if (call->argumentos) {
                for (auto* arg : *call->argumentos) {
                    if (arg) obtenerTipo(arg, tabla, errores);
                }
            }
            break;
        }
        default: break;
    }
}

bool analizarSemantica(Nodo* root, std::vector<ErrorSemantico>& errores) {
    TablaSimbolos tabla;
    recorrerAST(root, tabla, errores);
    return errores.empty();
}