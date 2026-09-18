#include <stdio.h>

int main() {
    int a = 5;
    int *ptr = &a;

    printf("Value of a: %d\n", a);
    printf("Value of a from pointer: %d\n", *ptr);

    printf("Address of a using variable: %p\n", &a);
    printf("Address of a using pointer: %p\n", ptr);

    *ptr = 10;
     printf("New value of a: %d\n", a);

     return 0;
}
