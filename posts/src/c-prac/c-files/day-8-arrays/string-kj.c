#include <stdio.h>
#include <string.h>

int main()
{
	// Strings Declared
	// char str1[] = "1234567890";
	// char str2[] = "123456789012345678901234567890";
    char str1[] = "aaaaaaaaaabbbbbbbbbb";
    char str2[] = "ccccccccccddddddddddoooooooooo";

    printf("str1: %s --- %ld\nstr2: %s --- %ld\n",str1,sizeof(str1),str2,sizeof(str2));

    printf("%p---%p ==> %ld \n",str1, str2, str2-str1);
	// String copy used
	strcpy(str1, str2);

	printf("str1: %s --- %ld\nstr2: %s --- %ld\n",str1,sizeof(str1),str2,sizeof(str2));

    return 0;
}