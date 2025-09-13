#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    long p = fork();
    int s;
    if (p < 0)
        printf("error in fork\n");
    else if (p == 0) {
        // Child process
        // printf("This is child process with PID %d\n", getpid());
        printf("pid %d says hello world\n", getpid());
    } else {
        // Parent process
        sleep(100);
        wait(&s);
        
    }

    
    return 0;
}
