# Manual para Ejecutar tus Scripts en el Compilador Star Wars

Este manual te guía paso a paso para compilar y ejecutar tus scripts escritos en el lenguaje Star Wars usando tu compilador personalizado.

---

## 1. Pre-requisitos

- Tener instalado **WSL** (Windows Subsystem for Linux) con una distribución Linux (por ejemplo, Ubuntu).
- Tener instalados los siguientes paquetes en WSL:
  - `build-essential` (incluye gcc, g++)
  - `flex`
  - `bison`

Puedes instalar todo con:
```sh
sudo apt update
sudo apt install build-essential flex bison
```

---

## 2. Compilar el Compilador Star Wars

Abre una terminal en la carpeta del proyecto y ejecuta:
```sh
wsl make clean; wsl make
```
Esto generará el ejecutable `mycompiler` dentro de la carpeta del proyecto.

---

## 3. Escribir tu Script Star Wars

Crea un archivo de texto (por ejemplo, `mi_script.txt`) usando la sintaxis Star Wars. Puedes basarte en los ejemplos como `ejemplo_starwars.txt` o `logica_compilador.txt`.

---

## 4. Compilar tu Script Star Wars

Ejecuta en la terminal:
```sh
wsl ./mycompiler mi_script.txt
```
Esto generará un archivo `output.c` con el código C equivalente a tu script Star Wars.

---

## 5. Compilar el Código C Generado

Compila el archivo C usando gcc:
```sh
wsl gcc output.c -o mi_programa
```
Esto creará el ejecutable `mi_programa`.

---

## 6. Ejecutar tu Programa

Ejecuta tu programa con:
```sh
wsl ./mi_programa
```
Sigue las instrucciones que aparecen en pantalla.

---

## 7. Consejos y Solución de Problemas

- Si modificas tu script, repite los pasos 4, 5 y 6.
- Si cambias la gramática o el compilador, repite desde el paso 2.
- Si ves errores de sintaxis, revisa que tu script siga la sintaxis Star Wars (consulta los ejemplos y el manual).
- Si tienes problemas con permisos, puedes dar permisos de ejecución con:
  ```sh
  wsl chmod +x mycompiler mi_programa
  ```

---

## 8. Ejemplo Completo

```sh
wsl make clean; wsl make
wsl ./mycompiler logica_compilador.txt
wsl gcc output.c -o calculadora
wsl ./calculadora
```

---

¡Listo! Así puedes ejecutar cualquier script en tu compilador Star Wars.

¿Dudas? Consulta los archivos de ejemplo o el manual Star Wars incluido en el proyecto.
