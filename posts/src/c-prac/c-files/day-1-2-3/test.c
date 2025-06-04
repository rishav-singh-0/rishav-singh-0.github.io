#include<stdio.h>
  
#define N 10
  
int main()
{
    // This is fine.
    for (size_t n = 0; n < N; ++n) {
        printf("%d ", n);
    }
    printf("\n");
          
    // But reverse cycles are tricky for unsigned 
    // types as they can lead to infinite loops.
    for (size_t n = N-1; n > 0; n--)
        printf("%d ", n);
}