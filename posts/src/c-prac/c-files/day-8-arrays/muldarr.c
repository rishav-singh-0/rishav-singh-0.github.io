#include<stdio.h>
int main() {
    int a[][2] = {1, 2, 3, 4, 5, 6, 7};
    printf("%lu\n", sizeof(a)/sizeof(int)); // prints 8*sizeof(int)
    printf("%d\n", *(a[0]+2));
    return 0;
}