#include<stdio.h>
int main(){
  int a=100.8f;
  long double f=10;
  printf("Int %ld %ld %ld", sizeof(int), sizeof(long), sizeof(long long));
  printf("\nFloat %ld %ld %ld", sizeof(float), sizeof(double), sizeof(long double));
  printf("\n%u", (unsigned int)-1);
}

