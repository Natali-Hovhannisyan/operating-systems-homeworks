#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int ret = fork();
    if (ret == 0) {
        execl("/usr/bin/ls", "ls", NULL);
    }
    else {
        wait(NULL);
        printf("Parent process done\n");
    }
    return 0;
}
