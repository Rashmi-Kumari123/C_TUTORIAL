#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        int fd_out = open("stdout.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
        int fd_err = open("stderr.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
        dup2(fd_out, STDOUT_FILENO); close(fd_out);
        dup2(fd_err, STDERR_FILENO); close(fd_err);
        execlp("ls", "ls", "/nonexistent", NULL);
        // execlp("ls", "ls", "/home/rashmi-kumari/Documents", NULL);

        perror("execlp"); exit(1);
    }
    else wait(NULL);
    return 0;
}
