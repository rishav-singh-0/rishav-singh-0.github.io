#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* f1 = fopen("string.txt", "r");

    char str[50];
    
    for(int i=0; i<50; i++){
        str[i] = fgetc(f1);
        printf("%d\t%c\n", str[i], str[i]);
    }
    printf("%s", str);
    fclose(f1);

    return 0;
}