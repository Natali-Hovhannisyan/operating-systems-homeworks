#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int child = fork();
    if (child == 0) {
        execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);
    }

    wait(NULL);
    printf("Parent process done\n");
    return 0;
}
