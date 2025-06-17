# Manual para ejecutar el Compilador ForceCode

Este manual guía paso a paso para compilar y ejecutar los scripts escritos en el lenguaje ForceCode usando este compilador:

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

## 2. Compilar el Compilador ForceCode

Abre una terminal en la carpeta del proyecto y ejecuta:
```sh
wsl make clean; wsl make
```
Esto generará el ejecutable `mycompiler` dentro de la carpeta del proyecto.

---

## 3. Escribir tu Script ForceCode

Crea un archivo de texto (por ejemplo, `mi_script.txt`) usando la sintaxis de ForceCode. Puedes basarte en los ejemplos como `ejemplo_funciones.txt` o `logica_compilador.txt`.

Ahora puedes usar:
- Funciones con `teInvoco`, parámetros y return.
- Llamadas a funciones en cualquier expresión.
- Imprimir varios valores con `palpatine("texto", var, ...);`

---

## 4. Compilar tu Script ForceCode

Ejecuta en la terminal:
```sh
wsl ./mycompiler mi_script.txt
```
Esto generará un archivo `output.c` con el código C equivalente a tu script ForceCode.

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
Siga las instrucciones que aparecen en pantalla.

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

## 8. Ejemplo Completo con Funciones

```c
teInvoco r2d2 suma(r2d2 a, r2d2 b) {
    r2d2 resultado;
    resultado teOtorgamos a luz b;
    return resultado;
}

teInvoco r2d2 main() {
    r2d2 x teOtorgamos 5;
    r2d2 y teOtorgamos 7;
    r2d2 z teOtorgamos suma(x, y);
    palpatine("Suma:", z);
    return 0;
}
```

Comandos:
```sh
wsl make clean; wsl make
wsl ./mycompiler mi_script.txt
wsl gcc output.c -o mi_programa
wsl ./mi_programa
```

---

¡Listo! Con eso puedes ejecutar cualquier script en tu compilador de ForceCode, ahora con soporte para funciones y return.

¿Dudas? Consulta los archivos de ejemplo o el manual ForceCode incluido en el proyecto.
