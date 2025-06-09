<<<<<<< Updated upstream
# Compilador-funda
Compilador para fundamentos de la computación usando Flex/Bison
=======
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
  enterito x fin
  racional y fin
  textito nombre fin
  ```
- **Inicialización:**
  ```c
  enterito a igual 5 fin
  racional b igual 3.14 fin
  textito saludo igual "Hola" fin
  ```
- **Asignación:**
  ```c
  x igual 10 fin
  y igual 2.5 fin
  nombre igual "Sebas" fin
  ```
- **Operaciones aritméticas:**
  ```c
  x igual x suma 1 fin
  y igual y por 2.0 fin
  a igual a resta 3 fin
  b igual b dividido 2.0 fin
  ```
- **Operaciones de comparación:**
  ```c
  SI (x equivalea 10) { ... }
  SI (y noequivalea 0.0) { ... }
  SI (a mayorcito b) { ... }
  SI (x mayoroigual 5) { ... }
  ```
- **Sentencias de control:**
  ```c
  SI (x menorcito 0) {
      imprima("Positivo") fin
  } entonces {
      imprima("No positivo") fin
  }

  mientras (x menoroigual 10) {
      x igual x suma 1 fin
  }
  ```
- **Entrada/salida:**
  ```c
  imprima("Hola mundo") fin
  imprima(x) fin
  lease(x) fin
  ```

---

## Ejemplo de programa

```c
enterito x fin
racional y fin
textito nombre fin

x igual 5 fin
y igual 2.5 fin
nombre igual "Sebas" fin

imprima("Introduce un número:") fin
lease(x) fin

SI (x mayorcito 10) {
    imprima("Mayor que 10") fin
} entonces {
    imprima("Menor o igual que 10") fin
}

mientras (x mayorcito 0) {
    imprima(x) fin
    x igual x resta 1 fin
}
```

---

## Notas
- El compilador detecta errores léxicos, sintácticos y semánticos (variables no declaradas, tipos incompatibles, etc.).
- El código generado es C estándar y puede ser compilado con GCC.
- Si tienes dudas o quieres extender el lenguaje, revisa los archivos `scanner.l`, `parser.y`, `ast.hpp` y `semantic.cpp`. 
>>>>>>> Stashed changes
