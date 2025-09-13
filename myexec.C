#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    long p = fork();
    if (p < 0)
        printf("error in fork\n");
    
    else if (p == 0) {
        // Child process
        execlp("ls", "myls", NULL);
        printf("Hello\n");
    } else {
        // Parent process
        wait(NULL);
        printf("Chld over\n");
    }

    
    return 0;
}
