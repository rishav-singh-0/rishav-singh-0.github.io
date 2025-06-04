#include<stdio.h>
inline int mul(int a, int b) //inline function declaration
{
   return(a*b);
}

int main(){
   int c;
   c=mul(2,3);
   printf("Multiplication:%d ",c);
   return 0;
}
