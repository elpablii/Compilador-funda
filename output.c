// Código generado por el compilador
#include <stdio.h>
int main() {
    int x;
    float y;
    char* nombre;
    x = 5;
    y = 2.5;
    nombre = "Sebas";
    printf("%s\n", "Introduce un número:");
    scanf("%d", &x);
    if ((x > 10)) {
    printf("%s\n", "Mayor que 10");
    } else {
    printf("%s\n", "Menor o igual que 10");
    }
    while ((x > 0)) {
    printf("%d\n", x);
    x = (x - 1);
    }
    return 0;
}
