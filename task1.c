#include <stdio.h>

int main() {
    int a = 5;
    int *ptr = &a;

    printf("Value of a: %d\n", a);
    printf("Value of a from pointer: %d\n", *ptr);

    *ptr = 10;
     printf("New value of a: %d\n", a);

     return 0;
}
