#include <stdio.h>

#define DEST_LEN 10
#define SRC_LEN 10

int string_copy(char *, int , const char *, int);

int main() {

    int copied_string;
    char src_string[10] = {'a', 'b', 'c', 'd', 'e', '\0'};
    char src_string_no_null[10] = {'a', 'b', 'c', 'd'};
    char dest_string[10];

    // Case 1: des > src
    copied_string = string_copy(dest_string, 10, src_string, 5);
    printf("Case 1 (des > src): %d\n", copied_string);

    // Case 2: des < src
    copied_string = string_copy(dest_string, 5, src_string, 10);
    printf("Case 2 (des < src): %d\n", copied_string);

    // Case 3: des = src
    copied_string = string_copy(dest_string, 5, src_string, 5);
    printf("Case 3 (des = src): %d\n", copied_string);

    // Case 4: des > src without null
    copied_string = string_copy(dest_string, 10, src_string_no_null, 5);
    printf("Case 4 (des > src without null): %d\n", copied_string);

    // Case 5: des < src without null
    copied_string = string_copy(dest_string, 5, src_string_no_null, 10);
    printf("Case 5 (des < src without null): %d\n", copied_string);

    // Case 6: des = src without null
    copied_string = string_copy(dest_string, 5, src_string_no_null, 5);
    printf("Case 6 (des = src without null): %d\n", copied_string);

    // Case 7
    copied_string = string_copy(dest_string, 5, NULL, 5);
    printf("Case 7 (src string = NULL): %d\n", copied_string);

    // Case 8
    copied_string = string_copy(NULL, 5, src_string_no_null, 5);
    printf("Case 8 (dest string = NULL): %d\n", copied_string);

    // Case 9
    copied_string = string_copy(dest_string, 0, src_string_no_null, 5);
    printf("Case 9 (dest_len = 0): %d\n", copied_string);

    // Case 10
    copied_string = string_copy(dest_string, 5, src_string_no_null, 0);
    printf("Case 10 (src_len = 0): %d\n", copied_string);
    
    return 0;
}

int string_copy(char *dest_str_ptr, int dest_max_len, const char *src_str_ptr, int src_max_len){
    int copied_len=0;
    
    // destination check
    if(dest_max_len==0 || dest_str_ptr==NULL){
        printf("Destination check failed!\n");
        return 0;
    }
    
    // source check
    if(src_max_len==0 || src_str_ptr==NULL){
        dest_str_ptr[copied_len] = '\0';
        printf("Source check failed!\n");
        return 0;
    }
    
    int max_len = dest_max_len;
    if(src_max_len < dest_max_len){
        max_len = src_max_len + 1;  // +1 because there is a room for adding '\0' after copying
    }

    for (copied_len = 0; copied_len < max_len-1 && src_str_ptr[copied_len]!='\0'; copied_len++){
        // printf("%c\n", src_str_ptr[copied_len]);
        dest_str_ptr[copied_len] = src_str_ptr[copied_len];
    }

    dest_str_ptr[copied_len] = '\0';
    return copied_len;
}
