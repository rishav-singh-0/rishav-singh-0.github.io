#include <stdio.h>

int main() {
    FILE *file1 = fopen("txt_files/first_file.txt", "w");
    fputs("Some random text", file1);
    fclose(file1);
    
    // rename function
    // int retVal = rename("txt_files/first_file.txt", "txt_files/first_file_renamed.txt");
    // printf("%d\n", retVal);
    
    

    return 0;
}