# Makefile para el compilador del lenguaje propio

# Compilador de C++
CXX = g++
# Flags para el compilador de C++
# -std=c++17 para características modernas como std::variant
# -g para información de depuración
# -Wall para todas las advertencias
CXXFLAGS = -std=c++17 -g -Wall 

# Herramienta Flex (analizador léxico)
FLEX = flex
FLEXFLAGS = 

# Herramienta Bison (analizador sintáctico)
# -d para generar el archivo de cabecera (parser.tab.h)
# --report=all para generar un informe detallado de la gramática (parser.output)
BISON = bison
BISONFLAGS = -d --report=all 

# Nombre del ejecutable final
TARGET = mycompiler

# Archivos fuente de C++
SRCS = main.cpp ast.cpp parser.tab.c lex.yy.c 

# Archivos objeto (.o) correspondientes a los fuentes
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.cpp=.o) 

# Archivos generados por Flex y Bison
GENERATED_C_LEX = lex.yy.c
GENERATED_C_PARSE = parser.tab.c
GENERATED_H_PARSE = parser.tab.h 

# Regla principal: construir el ejecutable
all: $(TARGET)

# Regla para enlazar todos los objetos y crear el ejecutable final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para generar el analizador léxico desde scanner.l
# lex.yy.c depende de parser.tab.h porque el scanner usa los tokens definidos por Bison.
$(GENERATED_C_LEX): scanner.l $(GENERATED_H_PARSE)
	$(FLEX) $(FLEXFLAGS) -o $(GENERATED_C_LEX) scanner.l

# Regla para generar el analizador sintáctico desde parser.y
# Esto crea parser.tab.c y parser.tab.h.
# Depende de parser.y y ast.hpp (porque parser.y incluye ast.hpp en su sección %{ %}).
$(GENERATED_C_PARSE) $(GENERATED_H_PARSE): parser.y ast.hpp
	$(BISON) $(BISONFLAGS) -o $(GENERATED_C_PARSE) parser.y

# Reglas explícitas para compilar cada archivo objeto, asegurando dependencias correctas.

lex.yy.o: $(GENERATED_C_LEX) $(GENERATED_H_PARSE) # lex.yy.c incluye parser.tab.h
	$(CXX) $(CXXFLAGS) -c $(GENERATED_C_LEX) -o lex.yy.o

parser.tab.o: $(GENERATED_C_PARSE) ast.hpp $(GENERATED_H_PARSE) # parser.tab.c incluye ast.hpp y define cosas usadas en parser.tab.h
	$(CXX) $(CXXFLAGS) -c $(GENERATED_C_PARSE) -o parser.tab.o

main.o: main.cpp ast.hpp $(GENERATED_H_PARSE) # main.cpp incluye ast.hpp y usa yyparse/ast_root (vía parser.tab.h)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

ast.o: ast.cpp ast.hpp
	$(CXX) $(CXXFLAGS) -c ast.cpp -o ast.o


# Regla para limpiar archivos generados y el ejecutable
clean:
	rm -f $(TARGET) $(OBJS) 
	rm -f $(GENERATED_C_LEX) $(GENERATED_C_PARSE) $(GENERATED_H_PARSE) 
	rm -f parser.output # Archivo de reporte de Bison
	rm -f *.o # Limpieza adicional de objetos si alguno no fue cubierto por $(OBJS)

# Phony targets son aquellos que no representan archivos reales
.PHONY: all clean
