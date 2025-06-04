#include <stdio.h>

int main() {
    FILE * f1 = fopen("text_file.txt", "r");
    // FILE *f2;
    // f2 = f1;

    char str[20];
    printf("%ld\n", ftell(f1));
    printf("%s", fgets(str, 20, f1));

    printf("%ld\n", ftell(f1));
    printf("%s", fgets(str, 20, f1));

    printf("%ld\n", ftell(f1));
    printf("%s", fgets(str, 20, f1));

    printf("%ld\n", ftell(f1));
    printf("%s", fgets(str, 20, f1));

    printf("%ld\n", ftell(f1));
    fclose(f1);
    
    // printf("%s", fgets(str, 10, f2));
    // fclose(f2);

    return 0;
}