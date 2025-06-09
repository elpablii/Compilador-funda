# Compilador de Lenguaje Propio

Este proyecto es un compilador sencillo para un lenguaje propio, implementado con **Flex** (análisis léxico), **Bison** (análisis sintáctico) y **C++** (AST, análisis semántico y generación de código C). El compilador es compatible con sistemas Linux.

---

## Requisitos
- Linux (probado en Ubuntu, WSL, etc.)
- `g++` (C++17 o superior)
- `gcc` (para compilar el código C generado)
- `flex`
- `bison`

Puedes instalar los requisitos en Ubuntu con:
```sh
sudo apt update
sudo apt install build-essential flex bison
```

---

## Instalación y compilación

1. Clona o descarga este repositorio.
2. Abre una terminal en la carpeta del proyecto.
3. Ejecuta:
   ```sh
   make clean
   make
   ```
   Esto generará el ejecutable `mycompiler`.

---

## Uso del compilador

1. Escribe tu programa en un archivo de texto, por ejemplo `ejemplo.txt`.
2. Ejecuta el compilador:
   ```sh
   ./mycompiler ejemplo.txt
   ```
   Si no hay errores, se generará un archivo `output.c` con el código C equivalente.
3. Compila el código C generado:
   ```sh
   gcc output.c -o programa
   ```
4. Ejecuta el programa:
   ```sh
   ./programa
   ```

---

## Sintaxis soportada

- **Declaración de variables:**
  ```c
  enteros x;
  flotantes y;
  texto nombre;
  ```
- **Inicialización:**
  ```c
  enteros a = 5;
  flotantes b = 3.14;
  texto saludo = "Hola";
  ```
- **Asignación:**
  ```c
  x = 10;
  y = 2.5;
  nombre = "Sebas";
  ```
- **Operaciones aritméticas:**
  ```c
  x = x + 1;
  y = y * 2.0;
  a = a - 3;
  b = b / 2.0;
  ```
- **Operaciones de comparación:**
  ```c
  if (x == 10) { ... }
  if (y != 0.0) { ... }
  if (a < b) { ... }
  if (x >= 5) { ... }
  ```
- **Sentencias de control:**
  ```c
  if (x > 0) {
      print("Positivo");
  } else {
      print("No positivo");
  }

  while (x < 10) {
      x = x + 1;
  }
  ```
- **Entrada/salida:**
  ```c
  print("Hola mundo");
  print(x);
  read(x);
  ```

---

## Ejemplo de programa

```c
enteros x;
flotantes y;
texto nombre;

x = 5;
y = 2.5;
nombre = "Sebas";

print("Introduce un número:");
read(x);

if (x > 10) {
    print("Mayor que 10");
} else {
    print("Menor o igual que 10");
}

while (x > 0) {
    print(x);
    x = x - 1;
}
```

---

## Notas
- El compilador detecta errores léxicos, sintácticos y semánticos (variables no declaradas, tipos incompatibles, etc.).
- El código generado es C estándar y puede ser compilado con GCC.
- Si tienes dudas o quieres extender el lenguaje, revisa los archivos `scanner.l`, `parser.y`, `ast.hpp` y `semantic.cpp`. 