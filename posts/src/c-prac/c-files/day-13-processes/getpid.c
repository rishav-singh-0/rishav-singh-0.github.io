#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // Prints id of current process
    printf("Process ID = %d\n", getpid());
    sleep(3);
    while(1){
        printf("%c", rand()%125);
    }
    return 0;
}