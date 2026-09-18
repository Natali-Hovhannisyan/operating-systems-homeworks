#include <stdio.h>


int main() {
   int a = 5;
   int *ptr1 = &a;
   int **ptr2 = &ptr1;

   printf("Value of a using pointer %d\n", *ptr1);
   printf("Value of a using double pointer %d\n", **ptr2);

   return 0;
}

