# Compilador ForceCode

¡Bienvenido al compilador ForceCode! Este proyecto implementa un compilador para un lenguaje propio, usando Flex, Bison y C++. Todas las palabras clave y tokens están inspirados en el universo de Star Wars, haciendo el aprendizaje de compiladores mucho más divertido de hacer.

## Características principales
- **Tokens temáticos**: Palabras clave como `r2d2` (entero), `c3p0` (flotante), `jedi` (if), `sith` (else), `obiwan` (verdadero), `anakin` (falso), y muchas más.
- **Declaración de variables**: enteros, flotantes, cadenas y booleanos.
- **Operaciones aritméticas y lógicas**: suma (`luz`), resta (`oscuridad`), multiplicación (`unlimitedPower`), división (`lightsable`), y operadores lógicos.
- **Sentencias de control**: `jedi` (if), `sith` (else), `cloneWar` (while).
- **Funciones**: Definición con `teInvoco`, parámetros, return y llamadas a funciones.
- **Entrada/salida**: `palpatine` (imprimir, acepta múltiples argumentos), `leia` (leer).
- **Generación de código C estándar**.

## Ejemplo de código Star Wars
```c
teInvoco r2d2 suma(r2d2 a, r2d2 b) {
    return a luz b;
}

teInvoco r2d2 main() {
    r2d2 x teOtorgamos 5;
    r2d2 y teOtorgamos 7;
    r2d2 z teOtorgamos suma(x, y);
    palpatine("Suma:", z);
    return 0;
}
```

## Compilación y ejecución
1. Instala las dependencias (en Linux/WSL):
   ```sh
   sudo apt update
   sudo apt install build-essential flex bison
   ```
2. Compila el compilador:
   ```sh
   wsl make clean; wsl make
   ```
3. Usa el compilador con un archivo de ejemplo:
   ```sh
   wsl ./mycompiler ejemplo_funciones.txt
   ```
4. Compila y ejecuta el código C generado:
   ```sh
   wsl gcc output.c -o programa
   wsl ./programa
   ```

## Manual de uso: ¿Cómo programar en el Lenguaje ForceCode?

### 1. Declaración de variables
- `r2d2` — Entero
- `c3p0` — Flotante
- `deathStar` — Cadena
- `booleano` — Booleano

Ejemplo:
```c
r2d2 vidas;
c3p0 energia;
deathStar mensaje;
booleano fuerza;
```

### 2. Asignación de valores
Utiliza `teOtorgamos` para asignar valores y termina cada instrucción con `;`.
```c
vidas teOtorgamos 3;
energia teOtorgamos 99.9;
mensaje teOtorgamos "¡Bienvenido, Jedi!";
fuerza teOtorgamos obiwan;
```

### 3. Operadores y expresiones
- Suma: `luz`
- Resta: `oscuridad`
- Multiplicación: `unlimitedPower`
- División: `lightsable`
- Igualdad: `equilibrio`
- Diferente: `rebelde`
- Menor: `highground`
- Mayor: `youUnderestimateMyPower`
- Menor o igual: `padawan`
- Mayor o igual: `maestro`

Ejemplo:
```c
vidas teOtorgamos vidas luz 1;
```

### 4. Funciones y return
- Declaración: `teInvoco tipo nombre(parámetros) { ... }`
- Parámetros separados por coma, pueden ser de cualquier tipo Star Wars.
- Retorna un valor con `return valor;`.
- Llama funciones como `resultado teOtorgamos suma(x, y);`

Ejemplo:
```c
teInvoco r2d2 suma(r2d2 a, r2d2 b) {
    return a luz b;
}
```

### 5. Llamada a funciones
Puedes invocar funciones en cualquier expresión:
```c
r2d2 total teOtorgamos suma(3, 4);
```

### 6. Sentencias de control
- If: `jedi (condición) { ... }`
- Else: `sith { ... }`
- While: `cloneWar (condición) { ... }`

Ejemplo:
```c
jedi (fuerza) {
    palpatine("¡La fuerza está contigo!");
} sith {
    palpatine("¡Únete al lado luminoso!");
}
```

### 7. Entrada y salida
- Imprimir: `palpatine("mensaje", var1, var2, ...);` (puedes imprimir varios valores)
- Leer: `leia(variable);`

Ejemplo:
```c
palpatine("Resultado:", total);
```

### 8. Booleanos
- Verdadero: `obiwan`
- Falso: `anakin`

### 9. Comentarios
- Comentario de línea: `// Esto es un comentario`
- Comentario de bloque: `/* Esto es un comentario largo */`

---

## Manuales y ejemplos
- Consulta `MANUAL_EJECUCION.md` para instrucciones detalladas de compilación y ejecución.
- Consulta `MANUAL_FORCECODE.md` para la referencia completa del lenguaje.
- Ejemplos: `ejemplo_funciones.txt`, `logica_compilador.txt`, `ejemplo_starwars.txt`.

