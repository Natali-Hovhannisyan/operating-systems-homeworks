#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *array;
    int *temp;

    array = (int *)malloc(10 * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter 10 integers: ");
    for (i = 0; i < 10; i++) {
        scanf("%d", &array[i]);
    }

    temp = (int *)realloc(array, 5 * sizeof(int));

    if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(array);
        array = NULL;
        return 1;
    }

    array = temp;

    printf("Array after resizing: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    array = NULL;

    return 0;
}
