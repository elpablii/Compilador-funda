// ast.cpp
// Implementación de los métodos de los nodos del AST en español.

#include "ast.hpp"
#include <iostream>

// Función auxiliar para convertir TipoDato a cadena
std::string tipoDatoAString(TipoDato tipo) {
    switch (tipo) {
        case TipoDato::ENTERO:   return "entero";
        case TipoDato::FLOTANTE: return "flotante";
        case TipoDato::CADENA:   return "cadena";
        case TipoDato::VACIO:    return "vacio";
        default:                 return "desconocido";
    }
}

// ------------------- Métodos de impresión del AST -------------------

void ProgramaNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoPrograma:\n";
    if (listaSentencias) {
        listaSentencias->imprimir(os, indent + 2);
    }
}

void ListaSentenciasNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoListaSentencias:\n";
    for (const auto* sentencia : sentencias) {
        if (sentencia) {
            sentencia->imprimir(os, indent + 2);
        } else {
            os << std::string(indent + 2, ' ') << "Sentencia nula\n";
        }
    }
}

void LiteralEnteroNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoLiteralEntero: " << valor << "\n";
}

void LiteralFlotanteNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoLiteralFlotante: " << valor << "\n";
}

void LiteralCadenaNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoLiteralCadena: \"" << valor << "\"\n";
}

void IdentificadorNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoIdentificador: " << nombre << "\n";
}

void OperacionBinariaNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoOperacionBinaria: " << operador << "\n";
    if (izquierda) {
        os << std::string(indent + 2, ' ') << "Izquierda:\n";
        izquierda->imprimir(os, indent + 4);
    }
    if (derecha) {
        os << std::string(indent + 2, ' ') << "Derecha:\n";
        derecha->imprimir(os, indent + 4);
    }
}

void DeclaracionVariableNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoDeclaracionVariable: Tipo=" << tipoDatoAString(tipoVariable) << "\n";
    if (identificador) {
        os << std::string(indent + 2, ' ') << "Identificador:\n";
        identificador->imprimir(os, indent + 4);
    }
    if (inicializacion) {
        os << std::string(indent + 2, ' ') << "Inicialización:\n";
        inicializacion->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ') << "Inicialización: (ninguna)\n";
    }
}

void AsignacionNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoAsignacion:\n";
    if (identificador) {
        os << std::string(indent + 2, ' ') << "Identificador:\n";
        identificador->imprimir(os, indent + 4);
    }
    if (expresion) {
        os << std::string(indent + 2, ' ') << "Expresión:\n";
        expresion->imprimir(os, indent + 4);
    }
}

void SiNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoSi:\n";
    if (condicion) {
        os << std::string(indent + 2, ' ') << "Condición:\n";
        condicion->imprimir(os, indent + 4);
    }
    if (entonces) {
        os << std::string(indent + 2, ' ') << "Entonces:\n";
        entonces->imprimir(os, indent + 4);
    }
    if (sino) {
        os << std::string(indent + 2, ' ') << "Sino:\n";
        sino->imprimir(os, indent + 4);
    } else {
        os << std::string(indent + 2, ' ') << "Sino: (ninguno)\n";
    }
}

void MientrasNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoMientras:\n";
    if (condicion) {
        os << std::string(indent + 2, ' ') << "Condición:\n";
        condicion->imprimir(os, indent + 4);
    }
    if (cuerpo) {
        os << std::string(indent + 2, ' ') << "Cuerpo:\n";
        cuerpo->imprimir(os, indent + 4);
    }
}

void ImprimirNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoImprimir:\n";
    if (expresion) {
        os << std::string(indent + 2, ' ') << "Expresión:\n";
        expresion->imprimir(os, indent + 4);
    }
}

void LeerNode::imprimir(std::ostream& os, int indent) const {
    os << std::string(indent, ' ') << "NodoLeer:\n";
    if (identificador) {
        os << std::string(indent + 2, ' ') << "Identificador destino:\n";
        identificador->imprimir(os, indent + 4);
    }
}

// Imprime el AST completo
template<typename T>
void imprimirASTImpl(const T* raiz, std::ostream& os) {
    if (raiz) {
        raiz->imprimir(os, 0);
    } else {
        os << "El AST está vacío (raíz nula).\n";
    }
}

void imprimirAST(const Nodo* raiz, std::ostream& os) {
    imprimirASTImpl(raiz, os);
}

// ------------------- Métodos de generación de código -------------------

void ProgramaNode::generarCodigo(std::ostream& os) const {
    os << "#include <stdio.h>\n";
    os << "int main() {\n";
    if (listaSentencias) listaSentencias->generarCodigo(os);
    os << "    return 0;\n";
    os << "}\n";
}

void ListaSentenciasNode::generarCodigo(std::ostream& os) const {
    for (const auto* sentencia : sentencias) {
        if (sentencia) sentencia->generarCodigo(os);
    }
}

void LiteralEnteroNode::generarCodigo(std::ostream& os) const {
    os << valor;
}

void LiteralFlotanteNode::generarCodigo(std::ostream& os) const {
    os << valor;
}

void LiteralCadenaNode::generarCodigo(std::ostream& os) const {
    os << '"' << valor << '"';
}

void IdentificadorNode::generarCodigo(std::ostream& os) const {
    os << nombre;
}

void OperacionBinariaNode::generarCodigo(std::ostream& os) const {
    os << "(";
    if (izquierda) izquierda->generarCodigo(os);
    os << " " << operador << " ";
    if (derecha) derecha->generarCodigo(os);
    os << ")";
}

void DeclaracionVariableNode::generarCodigo(std::ostream& os) const {
    std::string tipo;
    switch (tipoVariable) {
        case TipoDato::ENTERO: tipo = "int"; break;
        case TipoDato::FLOTANTE: tipo = "float"; break;
        case TipoDato::CADENA: tipo = "char*"; break;
        default: tipo = "int"; break;
    }
    os << "    " << tipo << " ";
    if (identificador) identificador->generarCodigo(os);
    if (inicializacion) {
        os << " = ";
        inicializacion->generarCodigo(os);
    }
    os << ";\n";
}

void AsignacionNode::generarCodigo(std::ostream& os) const {
    os << "    ";
    if (identificador) identificador->generarCodigo(os);
    os << " = ";
    if (expresion) expresion->generarCodigo(os);
    os << ";\n";
}

void SiNode::generarCodigo(std::ostream& os) const {
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

void MientrasNode::generarCodigo(std::ostream& os) const {
    os << "    while (";
    if (condicion) condicion->generarCodigo(os);
    os << ") {\n";
    if (cuerpo) cuerpo->generarCodigo(os);
    os << "    }\n";
}

void ImprimirNode::generarCodigo(std::ostream& os) const {
    os << "    printf(";
    if (expresion) {
        // Determinar el tipo para el formato
        // Por simplicidad, solo diferenciamos entre cadena y otros
        if (expresion->tipo == TipoNodo::LITERAL_CADENA) {
            os << "\"%s\", ";
            expresion->generarCodigo(os);
        } else if (expresion->tipo == TipoNodo::LITERAL_FLOTANTE) {
            os << "\"%f\", ";
            expresion->generarCodigo(os);
        } else {
            os << "\"%d\", ";
            expresion->generarCodigo(os);
        }
    }
    os << ");\n";
}

void LeerNode::generarCodigo(std::ostream& os) const {
    os << "    scanf(";
    // Por simplicidad, solo diferenciamos entre int y float
    os << "\"%d\", &";
    if (identificador) identificador->generarCodigo(os);
    os << ");\n";
}

void generarCodigoDesdeAST(const Nodo* raiz, std::ostream& os) {
    if (raiz) raiz->generarCodigo(os);
}

