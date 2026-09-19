#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    int child = fork();
    if (child == 0) {
        printf("Child id: %jd\n", (intmax_t)getpid());
    } else {
        printf("Parent id: %jd\n", (intmax_t)getpid());
    }
    return 0;
}
