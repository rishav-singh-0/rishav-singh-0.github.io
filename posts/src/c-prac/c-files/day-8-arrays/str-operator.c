#include <stdio.h>


int main() {
    char *str;
    FILE *fptr = fopen("string.txt", "r");
    if (fptr == NULL){ return 1; }
    fgets(str, 50, fptr);
    printf("%s\n", str);
    return 0;
}