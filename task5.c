#include <stdio.h>
#include <string.h>

int main() {
   char str[] = "Hello";
   char *ptr = str;

   for (int i = 0; i < strlen(str); i++) {
       printf("%c\n", *(ptr + i));
   }

   ptr = str;
   int count = 0;
   for (; *ptr != '\0'; ptr++) {
       count++;
   }
   printf("Number of characters is %d\n", count);

   return 0;
}

