#include <stdio.h>

struct data
{
    int x;
    int y;
};


int main() {
    struct data D1, D2;
    D1.x = 50;
    D2  = D1;
    printf("%lu\n", sizeof(D1));
    printf("%d %d\n", &D1, &D2);
    return 0;
}