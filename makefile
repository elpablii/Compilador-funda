# Makefile para compilar el lenguaje propio

# Compilador de C++
CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall

# Flex (analizador léxico)
FLEX      = flex
FLEXFLAGS = 

# Bison (analizador sintáctico)
BISON      = bison
BISONFLAGS = -d --report=all

# Nombre del ejecutable final
TARGET = mycompiler

# Archivos fuente de C++
SRCS_CPP = main.cpp ast.cpp semantic.cpp
SRCS_L    = scanner.l
SRCS_Y    = parser.y

# Archivos generados por Flex/Bison
LEX_C    = lex.yy.c
PARSE_C  = parser.tab.c
PARSE_H  = parser.tab.h
PARSE_OUT = parser.output

# Archivos objeto (.o)
OBJS = main.o ast.o semantic.o parser.tab.o lex.yy.o

# ------------------------------------------------------------------------
# Regla principal: construir el ejecutable
# ------------------------------------------------------------------------
all: $(TARGET)

# ------------------------------------------------------------------------
# Enlazar los objetos y crear el ejecutable
# ------------------------------------------------------------------------
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# ------------------------------------------------------------------------
# Generar analizador léxico (lex.yy.c) a partir de scanner.l
# Depende de parser.tab.h (tokens definidos por Bison)
# ------------------------------------------------------------------------
$(LEX_C): $(SRCS_L) $(PARSE_H)
	$(FLEX) $(FLEXFLAGS) -o $(LEX_C) $(SRCS_L)

# ------------------------------------------------------------------------
# Generar analizador sintáctico (parser.tab.c y parser.tab.h) a partir de parser.y
# Depende de parser.y y ast.hpp (incluido en parser.y)
# ------------------------------------------------------------------------
$(PARSE_C) $(PARSE_H): $(SRCS_Y) ast.hpp
	$(BISON) $(BISONFLAGS) -o $(PARSE_C) $(SRCS_Y)

# ------------------------------------------------------------------------
# Reglas para compilar archivos objeto
# ------------------------------------------------------------------------
# Compilar lex.yy.c
lex.yy.o: $(LEX_C) $(PARSE_H)
	$(CXX) $(CXXFLAGS) -c $(LEX_C) -o lex.yy.o

# Compilar parser.tab.c
parser.tab.o: $(PARSE_C) ast.hpp $(PARSE_H)
	$(CXX) $(CXXFLAGS) -c $(PARSE_C) -o parser.tab.o

# Compilar main.cpp
main.o: main.cpp ast.hpp $(PARSE_H)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Compilar ast.cpp
ast.o: ast.cpp ast.hpp
	$(CXX) $(CXXFLAGS) -c ast.cpp -o ast.o

# Compilar semantic.cpp
semantic.o: semantic.cpp semantic.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -c semantic.cpp -o semantic.o

# ------------------------------------------------------------------------
# Limpiar archivos generados y ejecutable
# ------------------------------------------------------------------------
clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(LEX_C) $(PARSE_C) $(PARSE_H) $(PARSE_OUT)

.PHONY: all clean
