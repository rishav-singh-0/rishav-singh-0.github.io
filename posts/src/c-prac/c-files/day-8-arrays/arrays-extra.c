#include<stdio.h>
#include<string.h>


# define PRINT(x) printf("%lu\n", sizeof(x))

int main(){
    char arr1[5] = {'a', 'b'};
    // printf("\n%d", arr1[1000]);

    // printf("%d\n", arr1[1299]);
    // printf("%d\n", arr1[1300]);
    
    // printf("%lu\n",strlen("12345"));
    // PRINT("12345");
    // PRINT(1);
    // PRINT(1.5);
    // char c = 'w';
    // PRINT('w');
    // PRINT(c);
    
    char str[5];
    str[0]='a'; str[1]='b'; str[2]='c';
    
    for(int i=0; i<5; i++){
        printf("%d:\t%c\t%d\n", i, str[i], str[i]);
    }
}