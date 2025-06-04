// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to read and write
struct person
{
    // double d1;  //8
	int c1; //1
	long int id: 33; //4
	int c2; //1
};

int main ()
{
	FILE *outfile;
	
	// open file for writing
	outfile = fopen ("person.dat", "w");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opened file\n");
		exit (1);
	}

	struct person input1 = {.c1='a', .c2=0xFFFA12, .id=5};
	// struct person input1 = {.c1='a', .c2='b', .id=5, .d1=5.5};
	// struct person input2 = {.c1='c', .c2='d', .id=10, .d1=10.5};
	
    printf("%lu\n", sizeof(struct person));
    printf("%d\n", &input1.c1 - &input1.c2);
	// write struct to file
	fwrite (&input1, sizeof(struct person), 1, outfile);
	// fwrite (&input2, sizeof(struct person), 1, outfile);
	
	if(fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	// close file
	fclose (outfile);

	return 0;
}