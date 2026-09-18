#include <stdio.h>

int main() {
    int arr[5] =  {1, 2, 3, 4, 5};
    int *ptr = arr;

    printf("Original array\n");

    for (int i = 0; i < 5; i++) {
        printf("Value at ptr + %d: %d\n", i, *(ptr + i));
    }

    for (int i = 0; i < 5; i++) {
        *(ptr + i) += (i+1)*10;
    }

   printf("New array\n");
    for (int i = 0; i < 5; i++) {
        printf("New values with pointer %d, with array name, : %d\n", *(ptr + i), arr[i]);
    }

    return 0;
}
