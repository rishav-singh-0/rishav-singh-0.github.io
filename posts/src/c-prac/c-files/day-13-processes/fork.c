#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid;
    // Create child process
    pid = fork();
    // Display information for child process
    if (pid == 0) {
        printf("Child : Hello I am the child process\n");
        printf("Child : Child’s PID: %d\n", getpid());
        printf("Child : Parent’s PID: %d\n", getppid());
    }
    // Display information for parent process
    else {
        printf("Parent : Hello I am the parent process\n");
        printf("Child : Parent’s PID: %d\n", getpid());
        printf("Parent : Child’s PID: %d\n", pid);
    }
    return 0;
}