#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;

    int child1 = fork();

    if (child1 == 0) {
        exit(1);
    }

    int child2 = fork();

    if (child2 ==0) {
        exit(2);
    }

    waitpid(child1, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child 1 exited normally with status %d\n", WEXITSTATUS(status));
    } else {
        printf("Child 1 exited with an error\n");
    }

    waitpid(child2, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child2 exited normally with status %d\n", WEXITSTATUS(status));
    } else {
        printf("child 2 exited with an error\n");
    }

    return 0;
}
