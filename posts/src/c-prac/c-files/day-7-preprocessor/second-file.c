#include<stdio.h>

#define VAR1 "10"
#define VAR2 "20"
#define VAR3 "30"

static int var_1 = 5;

int fun1(){
    printf("\n%d\t%p", var_1, &var_1);
}