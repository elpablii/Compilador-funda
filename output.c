// Código generado por el compilador
#include <stdio.h>
int main() {
    int numero;
    float raiz;
<<<<<<< Updated upstream
    printf("%s", "=== Analizador de Número ===\n");
=======
    printf("%s", "=== Análisis de Número ===\n");
>>>>>>> Stashed changes
    printf("%s", "Ingrese un número entero: ");
    scanf("%d", &numero);
    printf("%s", "Valor ingresado: ");
    printf("%d", numero);
    printf("%s", "\n");
    if ((numero > 0)) {
    printf("%s", "El número es positivo.\n");
    raiz = (numero / 2);
    int i;
    i = 0;
    while ((i <= 10)) {
    raiz = ((raiz + (numero / raiz)) / 2);
    i = (i + 1);
    }
    printf("%s", "Raíz cuadrada aproximada: ");
    printf("%f", raiz);
    printf("%s", "\n");
    } else {
    if ((numero == 0)) {
<<<<<<< Updated upstream
    printf("%s", "El número es cero.\n");
    } else {
    printf("%s", "El número es negativo.\n");
=======
    printf("%s", "El número es cero. No se puede calcular la raíz cuadrada.\n");
    } else {
    printf("%s", "El número es negativo. No se puede calcular la raíz cuadrada.\n");
>>>>>>> Stashed changes
    }
    }
    printf("%s", "Fin del análisis.\n");
    return 0;
}
