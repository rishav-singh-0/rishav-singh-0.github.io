
// C program for variable length members in structures in
// GCC before C99
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of type student
struct student {
	int stud_id;
	int name_len;
	int struct_size;
	char stud_name[0];
	// variable length array must be
	// last.
};

// Memory allocation and initialisation of structure
struct student* createStudent(struct student* s, int id,
							char a[])
{
	s = malloc(sizeof(*s) + sizeof(char) * strlen(a));

	s->stud_id = id;
	s->name_len = strlen(a);
	strcpy(s->stud_name, a);

	s->struct_size
		= (sizeof(*s)
		+ sizeof(char) * strlen(s->stud_name));

  printf("\n s = %d\n", sizeof(*s));
  printf("\n char = %d", sizeof(char));
  printf("\n char0 = %d", sizeof(s->stud_name));
  printf("\n len = %d\n", strlen(a));
  printf("\n Allocated_Struct_size::: %d %d\n", sizeof(s), s->struct_size);

	return s;
}

// Print student details
void printStudent(struct student* s)
{
	printf("Student_id : %d\n"
		"Stud_Name : %s\n"
		"Name_Length: %d\n"
		"Allocated_Struct_size: %d\n\n",
		s->stud_id, s->stud_name, s->name_len,
		s->struct_size);

	// Value of Allocated_Struct_size here is in bytes.
}

// Driver Code
int main()
{
	struct student *s1, *s2;

	s1 = createStudent(s1, 523, "Sanjayulsha");
	s2 = createStudent(s2, 535, "Cherry");

	printStudent(s1);
	printStudent(s2);

	// size in bytes
	printf("Size of Struct student: %lu\n",
		sizeof(struct student));
	// size in bytes
	printf("Size of Struct pointer: %lu", sizeof(s1));

	free(s1);
	free(s2);
	
	return 0;
}