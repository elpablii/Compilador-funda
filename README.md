# Compilador Star Wars

¡Bienvenido a tu compilador temático de Star Wars! Este proyecto implementa un compilador para un lenguaje propio, usando Flex, Bison y C++. Todas las palabras clave y tokens están inspirados en el universo de Star Wars, haciendo el aprendizaje de compiladores mucho más divertido.

## Características principales
- **Tokens temáticos**: Palabras clave como `r2d2` (entero), `c3p0` (flotante), `jedi` (if), `sith` (else), `obiwan` (verdadero), `anakin` (falso), y muchas más.
- **Declaración de variables**: enteros, flotantes, cadenas y booleanos.
- **Operaciones aritméticas y lógicas**: suma (`luz`), resta (`oscuridad`), multiplicación (`unlimitedPower`), división (`lightsable`), y operadores lógicos.
- **Sentencias de control**: `jedi` (if), `sith` (else), `cloneWar` (while), `stormTroopers` (for).
- **Entrada/salida**: `palpatine` (imprimir), `leia` (leer).
- **Generación de código C estándar**.

## Ejemplo de código Star Wars
```c
r2d2 luke;
c3p0 fuerza;
booleano ladoOscuro;
luke teOtorgamos 5 unknownRegion
fuerza teOtorgamos 2.5 unknownRegion
ladoOscuro teOtorgamos obiwan unknownRegion
jedi (ladoOscuro) {
    palpatine("¡La fuerza te acompaña, Luke!") unknownRegion
}
```

## Compilación y ejecución
1. Instala dependencias (en Linux/WSL):
   ```sh
   sudo apt update
   sudo apt install build-essential flex bison
   ```
2. Compila el compilador:
   ```sh
   make clean
   make
   ```
3. Usa el compilador con un archivo de ejemplo:
   ```sh
   ./mycompiler ejemplo_starwars.txt
   ```
4. Compila y ejecuta el código C generado:
   ```sh
   gcc output.c -o programa
   ./programa
   ```

## Manual de uso: ¿Cómo programar en el Lenguaje Star Wars?

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
Utiliza `teOtorgamos` para asignar valores y termina cada instrucción con `unknownRegion` o `;`.
```c
vidas teOtorgamos 3 unknownRegion
energia teOtorgamos 99.9 unknownRegion
mensaje teOtorgamos "¡Bienvenido, Jedi!" unknownRegion
fuerza teOtorgamos obiwan unknownRegion
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
vidas teOtorgamos vidas luz 1 unknownRegion
```

### 4. Sentencias de control
- If: `jedi (condición) { ... }`
- Else: `sith { ... }`
- While: `cloneWar (condición) { ... }`

Ejemplo:
```c
jedi (fuerza) {
    palpatine("¡La fuerza está contigo!") unknownRegion
} sith {
    palpatine("¡Únete al lado luminoso!") unknownRegion
}
```

### 5. Entrada y salida
- Imprimir: `palpatine("mensaje") unknownRegion`
- Leer: `leia(variable) unknownRegion`

### 6. Booleanos
- Verdadero: `obiwan`
- Falso: `anakin`

### 7. Comentarios
- Comentario de línea: `// Esto es un comentario`
- Comentario de bloque: `/* Esto es un comentario largo */`

---

¡Con estos comandos puedes crear tus propios programas en el lenguaje Star Wars! Consulta los ejemplos incluidos para más inspiración.

## Créditos
Desarrollado por el equipo de compiladores. ¡Que la fuerza te acompañe!