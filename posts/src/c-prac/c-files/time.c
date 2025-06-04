#include <stdio.h>

int main() {
    // printf("%s\t%s", __TIME__, __DATE__);
    int hr, min, sec;
    sscanf(__TIME__, "%d:%d:%d", &hr, &min, &sec);
    printf("%d, %d, %d\n", hr, min, sec);
    
    char month[4];
    int day, year;
    sscanf(__DATE__, "%s %d %d", month, &day, &year);
    printf("%s, %d, %d", month, day, year);

    return 0;
}