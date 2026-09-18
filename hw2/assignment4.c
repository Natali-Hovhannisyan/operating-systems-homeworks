#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int child = fork();
    if (child == 0) {
        execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);
    }

    wait(NULL);
    printf("Parent process done\n");
}
