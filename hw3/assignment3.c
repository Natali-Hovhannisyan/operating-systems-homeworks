#include <stdio.h>
#include <stdlib.h>

void first(void)
{
    printf("atexit() successful\n");
}

void second(void)
{
    printf("Another atexit() successful\n");
}

int main()
{
    atexit(first);
    atexit(second);

    exit(0);

    printf("This will never run\n");
}
