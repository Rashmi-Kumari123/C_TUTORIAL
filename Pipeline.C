#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <grep_pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipe1_fds[2]; // For ls -l | grep
    int pipe2_fds[2]; // For grep | output_file

    // Create the first pipe
    if (pipe(pipe1_fds) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    // Create the second pipe
    if (pipe(pipe2_fds) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    // First child process (ls -l)
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) { // Child 1
        close(pipe1_fds[0]); // Close read end of pipe1
        close(pipe2_fds[0]); // Close read end of pipe2
        close(pipe2_fds[1]); // Close write end of pipe2

        dup2(pipe1_fds[1], STDOUT_FILENO); // Redirect stdout to pipe1's write end
        close(pipe1_fds[1]); // Close original write end of pipe1

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls"); // Should not reach here
        exit(EXIT_FAILURE);
    }

    // Second child process (grep <pattern>)
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) { // Child 2
        close(pipe1_fds[1]); // Close write end of pipe1
        close(pipe2_fds[0]); // Close read end of pipe2

        dup2(pipe1_fds[0], STDIN_FILENO);  // Redirect stdin to pipe1's read end
        dup2(pipe2_fds[1], STDOUT_FILENO); // Redirect stdout to pipe2's write end

        close(pipe1_fds[0]); // Close original read end of pipe1
        close(pipe2_fds[1]); // Close original write end of pipe2

        execlp("grep", "grep", argv[1], NULL);
        perror("execlp grep"); // Should not reach here
        exit(EXIT_FAILURE);
    }

    // Third child process (write to file)
    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork3");
        exit(EXIT_FAILURE);
    } else if (pid3 == 0) { // Child 3
        close(pipe1_fds[0]); // Close read end of pipe1
        close(pipe1_fds[1]); // Close write end of pipe1
        close(pipe2_fds[1]); // Close write end of pipe2

        dup2(pipe2_fds[0], STDIN_FILENO); // Redirect stdin to pipe2's read end
        close(pipe2_fds[0]); // Close original read end of pipe2

        // Open file for writing
        int fd_out = open("filtered_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open filtered_output.txt");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO); // Redirect stdout to the file
        close(fd_out); // Close original file descriptor

        // Use cat to simply copy stdin to stdout (which is now the file)
        execlp("cat", "cat", NULL);
        perror("execlp cat"); // Should not reach here
        exit(EXIT_FAILURE);
    }

    // Parent process: close all pipe ends and wait for children
    close(pipe1_fds[0]);
    close(pipe1_fds[1]);
    close(pipe2_fds[0]);
    close(pipe2_fds[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}