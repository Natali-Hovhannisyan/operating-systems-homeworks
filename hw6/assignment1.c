#include <stdio.h>

int main() {
    int a = 10;
    char b = 'A';
    double c = 3.14;
    short d = 5;

    printf("int size: %zu bytes\n", sizeof(a));
    printf("int address: %p\n\n", (void *)&a);

    printf("char size: %zu bytes\n", sizeof(b));
    printf("char address: %p\n\n", (void *)&b);

    printf("double size: %zu bytes\n", sizeof(c));
    printf("double address: %p\n\n", (void *)&c);

    printf("short size: %zu bytes\n", sizeof(d));
    printf("short address: %p\n", (void *)&d);

    return 0;
}
