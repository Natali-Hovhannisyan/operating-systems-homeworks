#include <stdio.h>

struct Normal {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct Packed1 {
    char a;
    int b;
    double c;
};

#pragma pack(2)
struct Packed2 {
    char a;
    int b;
    double c;
};

#pragma pack(4)
struct Packed4 {
    char a;
    int b;
    double c;
};

#pragma pack()

int main() {
    struct Normal x;
    struct Packed1 y;
    struct Packed2 z;
    struct Packed4 w;

    printf("Normal size: %zu\n", sizeof(x));
    printf("a: %p\n", (void *)&x.a);
    printf("b: %p\n", (void *)&x.b);
    printf("c: %p\n", (void *)&x.c);

    printf("\nPack(1) size: %zu\n", sizeof(y));
    printf("a: %p\n", (void *)&y.a);
    printf("b: %p\n", (void *)&y.b);
    printf("c: %p\n", (void *)&y.c);

    printf("\nPack(2) size: %zu\n", sizeof(z));
    printf("a: %p\n", (void *)&z.a);
    printf("b: %p\n", (void *)&z.b);
    printf("c: %p\n", (void *)&z.c);

    printf("\nPack(4) size: %zu\n", sizeof(w));
    printf("a: %p\n", (void *)&w.a);
    printf("b: %p\n", (void *)&w.b);
    printf("c: %p\n", (void *)&w.c);

    return 0;
}
