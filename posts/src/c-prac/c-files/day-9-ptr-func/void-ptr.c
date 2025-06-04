#include<stdio.h>

int main()
{
    int a = 2;
    void * ptr = &a;
    
    printf("%p\n", ptr);
    // printf("%f\n", ptr);
    // printf("%o\n", ptr);
    printf("%p\n", (int *)ptr+1);
    
    printf("%o\n", 3.14);
    printf("%p\n", 16.5);
}