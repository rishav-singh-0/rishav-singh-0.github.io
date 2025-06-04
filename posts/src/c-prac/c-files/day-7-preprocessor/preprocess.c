#include<stdio.h>

#define PRINT(x) ('x')
// #define PRINT(x) ("x")

int main(){
    // int a = sizeof(int);
    // printf("%d", a);

    int a, b = (1, 2);
    printf("%d %d \n", a, b);
    return 0;
}