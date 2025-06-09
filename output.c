// Código generado por el compilador
#include <stdio.h>
int main() {
    int x;
    float y;
    char* nombre;
    x = 5;
    y = 2.5;
    nombre = "Sebas";
    printf("%s", "Introduce un número:");
    scanf("%d", &x);
    if ((x > 10)) {
    printf("%s", "Mayor que 10");
    } else {
    printf("%s", "Menor o igual que 10");
    }
    while ((x > 0)) {
    printf("%d", x);
    x = (x - 1);
    }
    return 0;
}
