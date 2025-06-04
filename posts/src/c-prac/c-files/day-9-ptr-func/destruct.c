#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void beforeMain (void) __attribute__ ((constructor));
void afterMain (void) __attribute__ ((destructor));
_Noreturn int fun();

void beforeMain (void)
{
	printf ("constructor code before main()\n");
}

void afterMain (void)
{
	printf ("destructor after main()\n");
}

void funExit(){
    printf("Inside atexit\n");
}

int main (void)
{
    int a = 5;
    atexit(funExit);
	printf ("start of main\n");
    // exit(1);
    // abort();
    // assert(a==0);
    fun();
    printf("\nEnd of main\n");
	return 0;
}

_Noreturn int fun(){
    static int x = 1;
    printf("Inside _Noreturn\n");
    printf("Value of x = %d\n", x);
    x++;
    // exit(1);
}
