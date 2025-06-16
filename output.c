// Código generado por el compilador
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    int opcion;
    int a;
    int b;
    int resultado;
    int base;
    int exponente;
    int potencia;
    opcion = 0;
    while ((opcion != 6)) {
    printf("%s\n", "\n=== CALCULADORA STAR WARS ===");
    printf("%s\n", "1. Suma");
    printf("%s\n", "2. Resta");
    printf("%s\n", "3. Multiplicación");
    printf("%s\n", "4. División");
    printf("%s\n", "5. Potencia");
    printf("%s\n", "6. Salir");
    printf("%s\n", "Elige una opción (1-6):");
    scanf("%d", &opcion);
    if ((opcion == 1)) {
    printf("%s\n", "[SUMA] Ingresa el primer número:");
    scanf("%d", &a);
    printf("%s\n", "[SUMA] Ingresa el segundo número:");
    scanf("%d", &b);
    resultado = (a + b);
    printf("%s\n", "Resultado de la suma:");
    printf("%d\n", resultado);
    } else {
    if ((opcion == 2)) {
    printf("%s\n", "[RESTA] Ingresa el primer número:");
    scanf("%d", &a);
    printf("%s\n", "[RESTA] Ingresa el segundo número:");
    scanf("%d", &b);
    resultado = (a - b);
    printf("%s\n", "Resultado de la resta:");
    printf("%d\n", resultado);
    } else {
    if ((opcion == 3)) {
    printf("%s\n", "[MULTIPLICACIÓN] Ingresa el primer número:");
    scanf("%d", &a);
    printf("%s\n", "[MULTIPLICACIÓN] Ingresa el segundo número:");
    scanf("%d", &b);
    resultado = (a * b);
    printf("%s\n", "Resultado de la multiplicación:");
    printf("%d\n", resultado);
    } else {
    if ((opcion == 4)) {
    printf("%s\n", "[DIVISIÓN] Ingresa el numerador:");
    scanf("%d", &a);
    printf("%s\n", "[DIVISIÓN] Ingresa el denominador:");
    scanf("%d", &b);
    if ((b != 0)) {
    resultado = (a / b);
    printf("%s\n", "Resultado de la división:");
    printf("%d\n", resultado);
    } else {
    printf("%s\n", "No se puede dividir entre 0");
    }
    } else {
    if ((opcion == 5)) {
    printf("%s\n", "[POTENCIA] Ingresa la base:");
    scanf("%d", &base);
    printf("%s\n", "[POTENCIA] Ingresa el exponente:");
    scanf("%d", &exponente);
    potencia = 1;
    resultado = 0;
    while ((resultado < exponente)) {
    potencia = (potencia * base);
    resultado = (resultado + 1);
    }
    printf("%s\n", "Resultado de la potencia:");
    printf("%d\n", potencia);
    } else {
    if ((opcion == 6)) {
    printf("%s\n", "¡Hasta pronto, que la fuerza te acompañe!");
    } else {
    printf("%s\n", "Opción no válida. Intenta de nuevo.");
    }
    }
    }
    }
    }
    }
    }
    return 0;
}
