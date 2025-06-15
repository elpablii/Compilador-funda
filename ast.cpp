// ast.cpp
// Implementación de los métodos de los nodos del AST.

#include "ast.hpp"
#include <iostream>
#include <unordered_map>

// Función auxiliar para convertir TipoDato a cadena
// Devuelve el nombre textual del tipo de dato
std::string tipoDatoAString(TipoDato dt) {
    switch (dt) {
        case TipoDato::ENTERO:    return "ENTERO";
        case TipoDato::FLOTANTE:  return "FLOTANTE";
        case TipoDato::CADENA:    return "CADENA";
        case TipoDato::BOOLEANO:  return "BOOLEANO";
        case TipoDato::VACIO:     return "VACIO";
        default:                  return "TIPO_DESCONOCIDO";
    }
}

// Imprime el nodo raíz del programa y su lista de instrucciones
void NodoPrograma::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoPrograma:\n";
    if (listaInstrucciones) {
        listaInstrucciones->imprimir(os, indent + 2);
    }
}

// Imprime la lista de instrucciones contenidas en el programa
void NodoListaInstrucciones::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoListaInstrucciones:\n";
    for (const auto* instr : instrucciones) {
        if (instr) {
            instr->imprimir(os, indent + 2);
        } else {
            os << std::string(indent + 2, ' ')
               << "NodoInstruccionNula (instrucción vacía)\n";
        }
    }
}

// Imprime un nodo literal entero
void NodoLiteralEntero::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoLiteralEntero: " << valor << "\n";
}

// Imprime un nodo literal flotante
void NodoLiteralFlotante::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoLiteralFlotante: " << valor << "\n";
}

// Imprime un nodo literal de cadena
void NodoLiteralCadena::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoLiteralCadena: \"" << valor << "\"\n";
}

// Imprime un nodo identificador (nombre de variable)
void NodoIdentificador::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoIdentificador: " << nombre << "\n";
}

void NodoOperacionBinaria::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoOperacionBinaria: " << op << "\n";
    if (izquierda) {
        os << std::string(indent + 2, ' ') << "Izquierda:\n";
        izquierda->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Izquierda: (null)\n";
    }
    if (derecha) {
        os << std::string(indent + 2, ' ') << "Derecha:\n";
        derecha->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Derecha: (null)\n";
    }
}

void NodoDeclaracionVariable::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoDeclaracionVariable: Tipo=" << tipoDatoAString(tipoVar) << "\n";
    if (identificador) {
        os << std::string(indent + 2, ' ')
           << "Identificador:\n";
        identificador->imprimir(os, indent + 4);
    }
    if (inicializacion) {
        os << std::string(indent + 2, ' ')
           << "Inicializacion:\n";
        inicializacion->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Inicializacion: (none)\n";
    }
}

void NodoAsignacion::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoAsignacion:\n";
    if (identificador) {
        os << std::string(indent + 2, ' ')
           << "Identificador:\n";
        identificador->imprimir(os, indent + 4);
    }
    if (expresion) {
        os << std::string(indent + 2, ' ')
           << "Expresion:\n";
        expresion->imprimir(os, indent + 4);
    }
}

void NodoSi::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoSi:\n";
    if (condicion) {
        os << std::string(indent + 2, ' ')
           << "Condicion:\n";
        condicion->imprimir(os, indent + 4);
    }
    if (entonces) {
        os << std::string(indent + 2, ' ')
           << "Entonces:\n";
        entonces->imprimir(os, indent + 4);
    }
    if (sino) {
        os << std::string(indent + 2, ' ')
           << "Sino:\n";
        sino->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ')
           << "Sino: (none)\n";
    }
}

void NodoMientras::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoMientras:\n";
    if (condicion) {
        os << std::string(indent + 2, ' ')
           << "Condicion:\n";
        condicion->imprimir(os, indent + 4);
    }
    if (cuerpo) {
        os << std::string(indent + 2, ' ')
           << "Cuerpo:\n";
        cuerpo->imprimir(os, indent + 4);
    }
}

void NodoImprimir::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoImprimir:\n";
    if (expresion) {
        os << std::string(indent + 2, ' ')
           << "Expresion:\n";
        expresion->imprimir(os, indent + 4);
    }
}

void NodoLeer::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoLeer:\n";
    if (identificador) {
        os << std::string(indent + 2, ' ')
           << "IdentificadorObjetivo:\n";
        identificador->imprimir(os, indent + 4);
    }
}

void NodoLiteralBooleano::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ')
       << "NodoLiteralBooleano: " << (valor ? "true" : "false") << "\n";
}
void NodoLiteralBooleano::generarCodigo(std::ostream& os) const {
    os << (valor ? "1" : "0");
}

std::unordered_map<std::string, TipoDato> tiposVariables;

// Función global para imprimir el AST completo
void imprimirAST(const Nodo* raiz, std::ostream& os) {
    if (raiz) {
        raiz->imprimir(os, 0);
    } else {
        os << "AST está vacío (raíz nula).\n";
    }
}

// Implementación de generación de código para cada nodo
void NodoPrograma::generarCodigo(std::ostream& os) const {
    os << "#include <stdio.h>\n";
    os << "int main() {\n";
    if (listaInstrucciones) listaInstrucciones->generarCodigo(os);
    os << "    return 0;\n";
    os << "}\n";
}

void NodoListaInstrucciones::generarCodigo(std::ostream& os) const {
    for (const auto* instr : instrucciones) {
        if (instr) instr->generarCodigo(os);
    }
}

void NodoLiteralEntero::generarCodigo(std::ostream& os) const {
    os << valor;
}

void NodoLiteralFlotante::generarCodigo(std::ostream& os) const {
    os << valor;
}

void NodoLiteralCadena::generarCodigo(std::ostream& os) const {
    os << '"' << valor << '"';
}

void NodoIdentificador::generarCodigo(std::ostream& os) const {
    os << nombre;
}

void NodoOperacionBinaria::generarCodigo(std::ostream& os) const {
    if (op == "!") {
        os << "(!";
        if (izquierda) izquierda->generarCodigo(os);
        os << ")";
        return;
    }
    os << "(";
    if (izquierda) izquierda->generarCodigo(os);
    os << " " << op << " ";
    if (derecha) derecha->generarCodigo(os);
    os << ")";
}

void NodoDeclaracionVariable::generarCodigo(std::ostream& os) const {
    std::string tipo;
    switch (tipoVar) {
        case TipoDato::ENTERO: tipo = "int"; break;
        case TipoDato::FLOTANTE: tipo = "float"; break;
        case TipoDato::CADENA: tipo = "char*"; break;
        case TipoDato::BOOLEANO: tipo = "int"; break; // Representar booleanos como int en C
        default: tipo = "int"; break;
    }
    if (identificador) tiposVariables[identificador->nombre] = tipoVar;
    os << "    " << tipo << " ";
    if (identificador) identificador->generarCodigo(os);
    if (inicializacion) {
        os << " = ";
        inicializacion->generarCodigo(os);
    }
    os << ";\n";
}

void NodoAsignacion::generarCodigo(std::ostream& os) const {
    os << "    ";
    if (identificador) identificador->generarCodigo(os);
    os << " = ";
    if (expresion) expresion->generarCodigo(os);
    os << ";\n";
}

void NodoSi::generarCodigo(std::ostream& os) const {
    os << "    if (";
    if (condicion) condicion->generarCodigo(os);
    os << ") {\n";
    if (entonces) entonces->generarCodigo(os);
    os << "    }";
    if (sino) {
        os << " else {\n";
        sino->generarCodigo(os);
        os << "    }";
    }
    os << "\n";
}

void NodoMientras::generarCodigo(std::ostream& os) const {
    os << "    while (";
    if (condicion) condicion->generarCodigo(os);
    os << ") {\n";
    if (cuerpo) cuerpo->generarCodigo(os);
    os << "    }\n";
}

void NodoImprimir::generarCodigo(std::ostream& os) const {
    os << "    printf(";
    if (expresion) {
        TipoDato tipo = TipoDato::ENTERO;
        if (expresion->tipo == TipoNodo::IDENTIFICADOR) {
            auto* id = static_cast<const NodoIdentificador*>(expresion);
            auto it = tiposVariables.find(id->nombre);
            if (it != tiposVariables.end()) tipo = it->second;
        } else if (expresion->tipo == TipoNodo::LITERAL_CADENA) {
            tipo = TipoDato::CADENA;
        } else if (expresion->tipo == TipoNodo::LITERAL_FLOTANTE) {
            tipo = TipoDato::FLOTANTE;
        } else if (expresion->tipo == TipoNodo::LITERAL_BOOLEANO) {
            tipo = TipoDato::BOOLEANO;
        }
        switch (tipo) {
            case TipoDato::CADENA:
                os << "\"%s\\n\", ";
                break;
            case TipoDato::FLOTANTE:
                os << "\"%f\\n\", ";
                break;
            case TipoDato::BOOLEANO:
                os << "\"%d\\n\", ";
                break;
            default:
                os << "\"%d\\n\", ";
        }
        expresion->generarCodigo(os);
    }
    os << ");\n";
}

void NodoLeer::generarCodigo(std::ostream& os) const {
    os << "    scanf(\"%d\", &";
    if (identificador && identificador->tipo == TipoNodo::IDENTIFICADOR) {
        identificador->generarCodigo(os);
    }
    os << ");\n";
}

// Implementación de utilidad global en español
void imprimirAST(Nodo* raiz, std::ostream& os) {
    if (raiz) raiz->imprimir(os);
}

void generarCodigoDesdeAST(Nodo* raiz, std::ostream& os) {
    if (raiz) raiz->generarCodigo(os);
}
