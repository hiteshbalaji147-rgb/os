#include <stdio.h>
#include <unistd.h>
int main() {
    int pid = fork();

    if (pid == 0) {
        printf("This is the child process.\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else if (pid > 0) {
        printf("This is the parent process.\n");
        printf("Parent PID: %d\n", getpid());
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}

