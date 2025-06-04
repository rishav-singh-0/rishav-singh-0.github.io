#include<stdio.h>
#include "calc.h"

int main(){
    int num1, num2;

    num1 = 10;
    num2 = 5;

    printf("Add of %d and %d = %d\n", num1, num2, add_num(num1, num2));
    printf("Sub of %d and %d = %d\n", num1, num2, sub_num(num1, num2));
    
    return 0;
}