#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (fork() < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    sleep(10);

    return 0;
}
