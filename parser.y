//Bison

%{
<<<<<<< Updated upstream
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
=======
// parser.y (skeleton en C++ para Bison)
// Ahora el lenguaje usa palabras clave personalizadas:
// enterito, racional, textito, SI, entonces, mientras, imprima, lease
// igual, suma, resta, por, dividido, equivalea, noequivalea, menoroigual, mayoroigual, mayorcito, menorcito, fin
// Ejemplo de declaración: enterito x fin; racional y fin; textito nombre fin;
// Ejemplo de uso: x igual 5 fin
// Condicional: SI (x mayorcito 10) { ... } entonces { ... }
// Bucle: mientras (x mayorcito 0) { ... }
// Imprimir: imprima(x) fin
// Leer: lease(x) fin
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

extern int yylex();
void yyerror(const char *msg);
extern int yylineno;


//Estructura para la información en la tabla de simbolos

struct SymbolInfo{

    enum Type { UNKNOWN, INTEGER, FLOAT } type;
    union Value{
        int iVal;
        double fVal;
    } value;
    bool initialized;
    std::string typeName;

    SymbolInfo() : type(UNKNOWN), initialized(false) { value.fVal = 0.0; typeName = "desconocido";}
} 

// tabla de simbolos

std::map<std::string, SymbolInfo> tabla_simbolos;

//Función auxiliar para convertir tipo enum a string (para errores)

std::string typeEnumToString(SymbolInfo::Type t) {
    if (t == SymbolInfo::INTEGER) return "entero (zi)";
    if (t == SymbolInfo::FLOAT) return "flotante (fl)";
    return "desconocido";
}

%}


%language "c++"

%union {
    int tero;
    double fval;
    std::string* ide;
}
//Definicion de tokens
%token <tero> ENTERO
%token <fval> FLOTANTE_LITERAL
%token <ide> ID

%token IGUAL SUMA MENOS MULTIPLICACION DIVIDE
%token PRTSII PRTSID PUNTO_COMA FINL
// tipo de las declaraciones

%token ZETA
%token FLOTANTE_KEYWORD


//Precedencias
%left SUMA MENOS
%left MULTIPLICACION DIVIDE
%left NEGATIVO

%%

programa:
    | programa linea
;
linea:
    declaracion PUNTO_COMA  FINL
    | asignamiento PUNTO_COMA FINL
    | prtsi PUNTO_COMA FINL {std::cout << "Resultado expresión (línea " << yylineno << "): " << $1 << std::endl;}
    | FINL
    | error FINL            { yyerrok; std::cout << "Error recuperado en línea." << std::endl; }
    
;

declaracion:
    ZETA ID {
        std::string varName = *$2;
        if (tabla_simbolos.count(varName)) {
            yyerror(("Error semántico: Variable '" + varName + "' ya declarada.").c_str());
        } else {
            SymbolInfo info;
            info.type = SymbolInfo::INTEGER;
            info.typeName = "entero (zi)";
            info.initialized = false;
            tabla_simbolos[varName] = info;
            std::cout << "Variable '" << varName << "' declarada como " << info.typeName << "." << std::endl;
        }
        delete $2;
    }
    | FLOTANTE_KEYWORD ID { // NUEVA REGLA PARA FLOTANTES
        std::string varName = *$2;
        if (tabla_simbolos.count(varName)) {
            yyerror(("Error semántico: Variable '" + varName + "' ya declarada.").c_str());
        } else {
            SymbolInfo info;
            info.type = SymbolInfo::FLOAT;
            info.typeName = "flotante (fl)";
            info.initialized = false;
            tabla_simbolos[varName] = info;
            std::cout << "Variable '" << varName << "' declarada como " << info.typeName << "." << std::endl;
        }
        delete $2; // Liberar la memoria del string
    }
;

asignamiento:
    ID IGUAL prtsi {
        std::string varName = *$1;
        if (tabla_simbolos.find(varName) == tabla_simbolos.end()) {
            yyerror(("Error semántico: Variable '" + varName + "' no ha sido declarada.").c_str());
        } else {
            SymbolInfo& info = tabla_simbolos[varName];
            double exprVal = $3;

            if (info.type == SymbolInfo::INTEGER) {
                
                info.value.iVal = static_cast<int>(exprVal);
                std::cout << "Asignado " << info.value.iVal << " (de " << exprVal << ") a la variable entera '" << varName << "'." << std::endl;
            } else if (info.type == SymbolInfo::FLOAT) {
                info.value.fVal = exprVal;
                std::cout << "Asignado " << info.value.fVal << " a la variable flotante '" << varName << "'." << std::endl;
            } else {
                 yyerror(("Error semántico: Tipo desconocido para la variable '" + varName + "' en asignación.").c_str());
            }
            info.initialized = true;
        }
        delete $1; // Liberar memoria
    } 


prtsi:
    ENTERO { $$ = static_cast<double>($1); }  
    | FLOTANTE_LITERAL { $$ = $1; }
    | ID {
        std::string varName = *$1;
        if (tabla_simbolos.find(varName) == tabla_simbolos.end()) {
            yyerror(("Error semántico: Variable '" + varName + "' no declarada usada en expresión.").c_str());
            $$ = 0.0; // Valor de error o lanzar excepción
        } else {
            const SymbolInfo& info = tabla_simbolos.at(varName);
            if (!info.initialized) {
                 
                 std::cout << "Advertencia semántica: Variable '" << varName << "' usada sin inicializar (usando valor por defecto 0 o 0.0)." << std::endl;
            }

            if (info.type == SymbolInfo::INTEGER) {
                $$ = static_cast<double>(info.value.iVal);
            } else if (info.type == SymbolInfo::FLOAT) {
                $$ = info.value.fVal;
            } else {
                yyerror(("Error semántico: Variable '" + varName + "' de tipo no numérico ("+ info.typeName +") usada en expresión aritmética.").c_str());
                $$ = 0.0; // Valor de error
            }
        }
        delete $1; // Liberar memoria
    }

    | prtsi SUMA prtsi         { $$ = $1 + $3; }  
    | prtsi MENOS prtsi        { $$ = $1 - $3; }  
    | prtsi MULTIPLICACION prtsi        { $$ = $1 * $3; }  
    | prtsi DIVIDE prtsi        {
                                  if ($3 == 0.0) {
                                    yyerror("Error semántico: División por cero.");
                                  
                                  } else {

                                    $$ = $1 / $3;
                                  }
                                }  
    | PRTSII prtsi PRTSID       { $$ = $2; } 
;

%%

void yyerror(const char *msg) {
    std::cerr << "Error (línea " << yylineno << "): " << msg << std::endl;
}

int main() {
    std::cout << "=== Inicio del Compilador ===" << std::endl;
    std::cout << "Introduce código (zi <id>; fl <id>; <id> = <expr>; <expr>; )" << std::endl;
    std::cout << "Cada sentencia debe terminar con ; y un ENTER." << std::endl;
    std::cout << "----------------------------" << std::endl;
    int result = yyparse();
    std::cout << "----------------------------" << std::endl;
    if (result == 0) {
        std::cout << "=== Compilación (interpretación directa) exitosa ===" << std::endl;
    } else {
        std::cout << "=== Compilación fallida con " << result << " error(es) sintáctico(s) graves ===" << std::endl;
    }
    return result;
}


