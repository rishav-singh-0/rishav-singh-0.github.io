#include <stdio.h>

void swap(char **str1, char **str2){
    // char *str1 = 1000;
    printf("%p\t%p\n", str1, str2);
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

int main() {
    char *s1 = "one";
    char *s2 = "two";
    
    // char *ptr = &s1;
    
    // printf("%lu\t%lu\n%lu\t%lu\n", s1, &s1, s2, &s2);
    printf("%p\t%s\n%p\t%s\n", s1, s1, s2, s2);
    // printf("%lu\t%lu\t%lu\n", &s1[0], &s2[0], ptr);
    
    swap(&s1, &s2);
    printf("%p\t%s\n%p\t%s\n", s1, s1, s2, s2);

    return 0;
}