#include <limits.h>
#include <stdio.h>
 
int main()
{
    // printf("minimum int value = %d\n"
    //        "maximum int value = %d\n"
    //        "size of int in bytes = %zu\n"
    //        "size of int in bits = %zu",
    //        INT_MIN, INT_MAX, sizeof(int),
    //        sizeof(int) * CHAR_BIT);
  unsigned int i = 2147483648;
  printf("%d", i);
  printf("\nUINT_MAX + 1 = %u", UINT_MAX + 1);
}
