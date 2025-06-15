// Código generado por el compilador
#include <stdio.h>
int main() {
    int fuerza;
    float midiclorianos;
    char* mensaje;
    int ladoLuz;
    int ladoOscuro;
    fuerza = 10;
    midiclorianos = 20.5;
    mensaje = "Que la fuerza te acompañe";
    ladoLuz = 1;
    ladoOscuro = 0;
    if ((fuerza == 10)) {
    printf("%s\n", "Eres un verdadero Jedi");
    } else {
    printf("%s\n", "Aún eres un padawan");
    }
    while ((fuerza < 20)) {
    fuerza = (fuerza + 1);
    printf("%s\n", "Entrenando con la fuerza...");
    }
    scanf("%d", &fuerza);
    if (ladoLuz) {
    printf("%s\n", "El equilibrio está en la fuerza");
    }
    return 0;
}
