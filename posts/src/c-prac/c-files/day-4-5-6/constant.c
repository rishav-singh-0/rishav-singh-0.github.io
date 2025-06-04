#include<stdio.h>

int main(void)
{
	// const volatile int local = 10;
	// int *ptr = (int*) &local;

	// printf("Initial value of local : %d \n", local);

	// *ptr = 100;

	// printf("Modified value of local: %d \n", local);

    int a = 10;
    int *const bar=&a;  // constant pointer to int 
    printf("%lu %d", bar,*bar);
    // bar = &a;
	return 0;
}
