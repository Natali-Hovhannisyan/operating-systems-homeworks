#include <stdio.h>

void swap(int *a, int *b) {
    int x;
    x = *a;
    *a = *b;
    *b = x;
}


int main() {
    int a = 5;
    int b = 10;
    printf("Values before swap a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("Values after swap a=%d, b=%d\n", a, b);
    return 0;
}
