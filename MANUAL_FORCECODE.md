# Manual de uso del Lenguaje ForceCode

Este manual te enseña a programar usando el compilador temático de ForceCode. Aquí encontrarás la sintaxis, ejemplos y tips para aprovechar todas las características del lenguaje.

## 1. Declaración de variables
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

## 2. Asignación de valores
Utiliza `teOtorgamos` para asignar valores y termina cada instrucción con `;`.
```c
vidas teOtorgamos 3;
energia teOtorgamos 99.9;
mensaje teOtorgamos "¡Bienvenido, Jedi!";
fuerza teOtorgamos obiwan;
```

## 3. Operadores y expresiones
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

## 4. Funciones y return
- Declaración: `teInvoco tipo nombre(parámetros) { ... }`
- Parámetros separados por coma, pueden ser de cualquier tipo ForceCode.
- Retorna un valor con `return valor;`.
- Llama funciones como `resultado teOtorgamos suma(x, y);`

Ejemplo:
```c
teInvoco r2d2 suma(r2d2 a, r2d2 b) {
    r2d2 resultado;
    resultado teOtorgamos a luz b;
    return resultado;
}
```

## 5. Llamada a funciones
Puedes llamar funciones en cualquier expresión:
```c
r2d2 total teOtorgamos suma(3, 4);
```

## 6. Sentencias de control
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

## 7. Entrada y salida
- Imprimir: `palpatine("mensaje", var1, var2, ...);` (puedes imprimir varios valores)
- Leer: `leia(variable);`

Ejemplo:
```c
palpatine("Resultado:", total);
```

## 8. Booleanos
- Verdadero: `obiwan`
- Falso: `anakin`

## 9. Comentarios
- Comentario de línea: `// Esto es un comentario`
- Comentario de bloque: `/* Esto es un comentario largo */`

---

¡Con este manual puedes crear tus propios programas en el lenguaje ForceCode! Para una mayor inspiración o entendimiento, consulte los ejemplos incluidos.
