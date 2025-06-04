
// C Program to demonstrate using a
// normal pointer with const variable
#include <stdio.h>

// Main starts
int main()
{

	// A normal pointer points to const
	const int j = 20;

	const int* ptr = &j;

	// The below assignment is invalid in C++,
	// results in error.In C, the compiler may
	// throw a warning, but casting is implicitly allowed
	printf("*ptr: %d\n", *ptr);

	return 0;
}