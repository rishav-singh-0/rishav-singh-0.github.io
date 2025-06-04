#include <stdio.h>
#include<string.h>


#define SIZE(x) printf("%lu\n", sizeof(x))

void cpy() {
    char str1[] = "1234567890";
    char str2[] = "123456789012345678901234567890";
    // char str1[] = "aaaaaaaaaabbbbbbbbbb";
    // char str2[] = "ccccccccccddddddddddoooooooooo";
 
  
    SIZE(str1); SIZE(str2);
    printf("\n%s\n%s\n", str1, str2);
    strcpy(str1, str2);
    SIZE(str1); SIZE(str2);
    printf("\n%s\n%s\n", str1, str2);
}

void dup(){
    char str1[] = "0123456789";
    char* target = strdup(str1);
	printf("%lu %lu %lu\n", sizeof(str1), sizeof(strdup(str1)), sizeof(target));
	printf("%s", target);
}

void coll(){
    char s1[] = "girst";
    char s2[] = "gIcond";
    
    printf("%d\t%d\n", strcmp(s1, s2), strcoll(s1, s2));
}

int main() {
    // cpy();
    
    // dup();
    coll();
    return 0;
}