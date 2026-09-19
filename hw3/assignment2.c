#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>

int main() {
    int status;

    int child1 = fork();

    if (child1 == 0) {
        printf("Child 1 id: %jd\n", (intmax_t)getpid());
        exit(0);
    } else {
        wait(&status);
        printf("Child 1 exit status: %d\n", WEXITSTATUS(status));
    }

    int child2 = fork();

    if (child2 == 0) {
        printf("Child 2 id: %jd\n", (intmax_t)getpid());
        exit(0);
    } else {
        waitpid(child2, &status, 0);
        printf("Child 2 exit status: %d\n", WEXITSTATUS(status));
    }

    printf("Parent id: %jd\n", (intmax_t)getpid());

    return 0;
}
