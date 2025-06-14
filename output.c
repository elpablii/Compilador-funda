// Código generado por el compilador
#include <stdio.h>
int main() {
    int fuerza;
    float midiclorianos;
    char* mensaje;
    int ladoLuz;
    int ladoOscuro;
    printf("%s\n", "--- Prueba de asignación e impresión ---");
    fuerza = 5;
    printf("%d\n", fuerza);
    midiclorianos = 3.14;
    printf("%f\n", midiclorianos);
    mensaje = "Hola desde la galaxia";
    printf("%s\n", mensaje);
    printf("%s\n", "--- Prueba de operaciones matemáticas ---");
    fuerza = (fuerza + 10);
    printf("%d\n", fuerza);
    fuerza = (fuerza - 2);
    printf("%d\n", fuerza);
    fuerza = (fuerza * 3);
    printf("%d\n", fuerza);
    fuerza = (fuerza / 2);
    printf("%d\n", fuerza);
    printf("%s\n", "--- Prueba de input ---");
    printf("%s\n", "Introduce un valor para fuerza:");
    scanf("%d", &fuerza);
    printf("%d\n", fuerza);
    printf("%s\n", "--- Prueba de lógica y condicionales ---");
    ladoLuz = 1;
    ladoOscuro = 0;
    if ((fuerza == 10)) {
    printf("%s\n", "La fuerza está equilibrada");
    } else {
    printf("%s\n", "La fuerza NO está equilibrada");
    }
    if (ladoLuz) {
    printf("%s\n", "El lado luminoso prevalece");
    } else {
    printf("%s\n", "El lado oscuro prevalece");
    }
    printf("%s\n", "--- Prueba de ciclo while ---");
    while ((fuerza < 10)) {
    printf("%d\n", fuerza);
    fuerza = (fuerza + 1);
    }
    return 0;
}
