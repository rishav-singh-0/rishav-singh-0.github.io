#include <stdio.h>

int fun(int a, int b){

    return a+b;
}
int fun(int a){

    return a;
}
int fun(){

    return 0;
}

int main() {
    printf("%d\n", fun(1));
    printf("%d\n", fun(1, 2));
    printf("%d\n", fun());
    
    return 0;
}
