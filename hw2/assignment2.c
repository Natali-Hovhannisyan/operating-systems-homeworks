#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int child1 = fork();
    if (child1 == 0) {
        execl("/usr/bin/ls", "ls", NULL);
    }

    wait(NULL);

    int child2 = fork();

    if (child2 == 0) {
        execl("/usr/bin/date", "date", NULL);
    }

    wait(NULL);
    printf("Parent process done\n");
    return 0;
}
