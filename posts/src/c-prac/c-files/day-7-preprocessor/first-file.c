#include<stdio.h>
// #include "second_file.c"

extern int fun1();
extern int fun2();
//extern int var_1;

int main(){
    //printf("\n%d\t%p", var_1, &var_1);
    fun1();
    fun2();
    
    return 0;
}

