#include<stdio.h>

int x = 20;
int f1() { x = x+10; return x;}
int f2() { x = x-5;  return x;}

int main(){
    // printf("%lf\n%lf", 1.0*5/3*3, 1.0*5*3/3);
    // int x = 100 + printf("div") - 1*printf("mult");
    // printf("\n%ld\n", x);

    // int p = f1() + f2();
    // printf ("p = %d", p);
    
    int i = 8;
    int p = i++*i++;
    printf("%d\n", p);

    return 0;  
}