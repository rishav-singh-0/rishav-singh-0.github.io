#include <stdio.h>
#include<string.h>

#define STR_SIZE 10

int str_len(const char *, size_t);

int main() {
    char str[10] = {'a', 'b', 'c', 'd', 'e'};
    // str[5] = 'a';
    
    int len = str_len(str, sizeof(str));
    printf("%d\n", len);
    
    return 0;
}

int str_len(const char *str, size_t max_size){
    int str_length = 0;
    // printf("%ld\t%ld\n", sizeof(*str), max_size);

    if(str==NULL){
        return 0;
    }
    
    int index;
    for(index = 0; str[index]!='\0' && index < max_size; index++){
        str_length+=1;
    }

    return str_length;
}