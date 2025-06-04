#include <stdio.h>
#define merge(a, b) b##a

#define VALUE 10
#if VALUE
    int a = 5;
#endif

int main(void)
{
	printf("%d ", a);
	return 0;
}