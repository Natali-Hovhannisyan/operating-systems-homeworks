#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    int child = fork();

    if (child == 0) {
        printf("Child finished\n");
        exit(0);
    } else {
        sleep(20);
        printf("Parent finished\n");
    }

    return 0;
}
