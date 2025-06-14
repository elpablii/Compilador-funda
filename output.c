// Código generado por el compilador
#include <stdio.h>
int main() {
    int a;
    float b;
    a = 5;
    b = 2.5;
    a = (a + 3);
    b = (b * 2);
    printf("%d\n", a);
    printf("%f\n", b);
    int bandera;
    bandera = 1;
    if (bandera) {
    printf("%s\n", "La bandera es verdadera");
    } else {
    printf("%s\n", "La bandera es falsa");
    }
    int x;
    int y;
    x = 1;
    y = 0;
    int resultado;
    resultado = (x && y);
    printf("%d\n", resultado);
    resultado = (x || y);
    printf("%d\n", resultado);
    resultado = (!x);
    printf("%d\n", resultado);
    int i;
    i = 0;
    while ((i < 3)) {
    printf("%d\n", i);
    i = (i + 1);
    }
    int num;
    int esMayor;
    num = 10;
    esMayor = (num > 5);
    if (esMayor) {
    printf("%s\n", "num es mayor que 5");
    }
    return 0;
}
