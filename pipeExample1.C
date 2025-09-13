#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void report_exit(const char* msg) {
    perror(msg);
    exit(1);
}

int main() {
    int pfd[2];   
    if (pipe(pfd) < 0) 
        report_exit("pipe");

    pid_t c1 = fork();
    if (c1 < 0) report_exit("fork");

    if (c1 == 0) {
        // Child 1 → run "ps -ef"
        close(pfd[0]);             
        dup2(pfd[1], STDOUT_FILENO); 
        close(pfd[1]);              
        execlp("ps", "ps", "-ef", NULL);
        report_exit("exec ps");     
    }

    pid_t c2 = fork();
    if (c2 < 0) report_exit("fork");

    if (c2 == 0) {
        // Child 2 → run "more"
        close(pfd[1]);              
        dup2(pfd[0], STDIN_FILENO);  
        close(pfd[0]);              
        execlp("more", "more", NULL);
        report_exit("exec more");
    }

    // Parent → close both ends of pipe
    close(pfd[0]);
    close(pfd[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    return 0;
}
