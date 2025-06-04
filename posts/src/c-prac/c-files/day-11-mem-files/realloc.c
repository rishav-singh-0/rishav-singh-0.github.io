#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(2*sizeof(int));
    int *ptr1 = malloc(2*sizeof(int));
    printf("%p %lu\n", ptr, sizeof(ptr));
    printf("%p %lu\n", ptr1, sizeof(ptr1));
    ptr = realloc(ptr, 500*sizeof(int));
    printf("%p %lu\n", ptr, sizeof(ptr));
    
    free(ptr);
    free(ptr1);

    return 0;
}