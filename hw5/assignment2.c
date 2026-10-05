#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int i;
    int sum = 0;
    double average;
    int *array;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The number must be greater than 0.\n");
        return 1;
    }

    array = (int *)calloc(n, sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Array after calloc: ");
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        sum = sum + array[i];
    }

    average = (double)sum / n;

    printf("Updated array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Average of the array: %.1f\n", average);

    free(array);
    array = NULL;

    return 0;
}
