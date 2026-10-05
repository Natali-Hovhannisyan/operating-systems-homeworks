#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    char **strings;
    char **temp;

    strings = (char **)malloc(3 * sizeof(char *));

    if (strings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            while (i > 0) {
                i--;
                free(strings[i]);
            }

            free(strings);
            strings = NULL;
            return 1;
        }
    }

    printf("Enter 3 strings: ");
    for (i = 0; i < 3; i++) {
        scanf("%50s", strings[i]);
    }

    printf("First 3 strings: ");
    for (i = 0; i < 3; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n");

    temp = (char **)realloc(strings, 5 * sizeof(char *));

    if (temp == NULL) {
        printf("Memory reallocation failed.\n");

        for (i = 0; i < 3; i++) {
            free(strings[i]);
        }
        free(strings);
        strings = NULL;
        return 1;
    }

    strings = temp;

    for (i = 3; i < 5; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            while (i > 0) {
                i--;
                free(strings[i]);
            }

            free(strings);
            strings = NULL;
            return 1;
        }
    }

    printf("Enter 2 more strings: ");
    for (i = 3; i < 5; i++) {
        scanf("%50s", strings[i]);
    }

    printf("All strings: ");
    for (i = 0; i < 5; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n");

    for (i = 0; i < 5; i++) {
        free(strings[i]);
        strings[i] = NULL;
    }

    free(strings);
    strings = NULL;

    return 0;
}
