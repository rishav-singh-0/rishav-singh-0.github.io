#include <stdio.h>

void writeMessage(char *name) {
   printf("Hello, %s\n", name);
}

int main() {
    writeMessage("Dave");
    writeMessage((char *)"Victoria");
        return 0;
}