#include <stdio.h>

struct Data
{
    int x;
    int y;
};

void printData(struct Data* data){
    printf("%d, %d\n", data->x, data->y);
}

int main() {
    struct Data arr[3] = {{1, 2}, {3, 4}};
    printf("%lu\n", sizeof(arr));
    printData(&arr[0]);
    printData(&arr[1]);
    printData(&arr[2]);
    return 0;
}