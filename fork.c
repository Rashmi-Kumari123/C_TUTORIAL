#include <stdio.h>
#include <unistd.h>

int main() {
    long p = fork();
    if (p < 0)
        printf("error in fork\n");
    else if (p == 0) {
        // Child process
        // printf("hello world\n");
        printf("This is child process with PID %d\n", getpid());
    } else {
        // Parent process
        printf("This is parent process with PID %d\n", getpid());
    }

    
    return 0;
}
