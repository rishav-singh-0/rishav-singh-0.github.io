#include <stdio.h>

typedef struct{
    union{
        short int var1[2];
        int var2;
    };
    int var3;
} st;

void print_st(st st0){
    printf("Var1[0]: %x\nVar1[1]: %x\nVar2: %x\nVar3: %d\n", st0.var1[0], st0.var1[1], st0.var2, st0.var3);
}

int main() {
    print_st((st){.var2 = 0xaabb0a05, .var3=40});
    return 0;
}