# Compilador de Lenguaje Propio — Última Actualización

Este proyecto es un compilador para un lenguaje propio, implementado con Flex, Bison y C++. Ahora soporta variables booleanas, operaciones lógicas y aritméticas, y genera código C limpio y funcional.

## Características principales
- Declaración de variables: enteros, flotantes, cadenas y booleanos
- Operaciones aritméticas: +, -, *, /
- Operaciones lógicas: &&, ||, !
- Comparaciones: ==, !=, <, >, <=, >=
- Sentencias de control: if, else, while
- Entrada/salida: print, read
- Análisis léxico (Flex), sintáctico (Bison) y semántico (C++)
- Generación de código C estándar

## Ejemplo de uso
```c
enteros a;
flotantes b;
booleano bandera;
a = 5;
b = 2.5;
bandera = true;
if (bandera) {
    print("La bandera es verdadera");
}
```

## Compilación y ejecución
1. Instala dependencias en Linux/WSL:
   ```sh
   sudo apt update
   sudo apt install build-essential flex bison
   ```
2. Compila el compilador:
   ```sh
   make clean
   make
   ```
3. Usa el compilador:
   ```sh
   ./mycompiler ejemplos_booleanos.txt
   ```
4. Compila y ejecuta el código C generado:
   ```sh
   gcc output.c -o programa
   ./programa
   ```

## Créditos
Desarrollado por el equipo de compiladores, versión "Última Actualización".