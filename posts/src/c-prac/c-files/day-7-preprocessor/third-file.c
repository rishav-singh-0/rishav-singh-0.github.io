#include<stdio.h>

static int var_1 = 1;

int fun2(){
    printf("\n%d\t%p", var_1, &var_1);
}