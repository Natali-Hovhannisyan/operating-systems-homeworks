#include <stdio.h>

struct First {
    char a;
    int b;
    double c;
};

struct Second {
    double c;
    int b;
    char a;
};

struct Third {
    char a;
    double c;
    int b;
};

int main() {
    struct First x;
    struct Second y;
    struct Third z;

    printf("First struct size: %zu\n", sizeof(x));
    printf("a: %p\n", (void *)&x.a);
    printf("b: %p\n", (void *)&x.b);
    printf("c: %p\n", (void *)&x.c);

    printf("\nSecond struct size: %zu\n", sizeof(y));
    printf("c: %p\n", (void *)&y.c);
    printf("b: %p\n", (void *)&y.b);
    printf("a: %p\n", (void *)&y.a);

    printf("\nThird struct size: %zu\n", sizeof(z));
    printf("a: %p\n", (void *)&z.a);
    printf("c: %p\n", (void *)&z.c);
    printf("b: %p\n", (void *)&z.b);

    return 0;
}
