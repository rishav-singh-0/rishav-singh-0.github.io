#include<stdio.h>

int main(){
    int a = 10;
    if(!a)
        {printf("Not valid\n");}
    else
        {printf("Mat kar bhai\n");}

    if(~a)
        {printf("Inversion valid\n");}
    else
        {printf("Mat kar bhai\n");}
    
    // printf("\n%d", printf("\t"));
    
    // char arr[100];
    // scanf("%[^D]s", arr);
    
    // printf(arr);
    
    printf("%d", a*=10+20);
    
}