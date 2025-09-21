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
    int pipe1_fds[2]; // Pipe for ls -l | grep
    int pipe2_fds[2]; // Pipe for grep | output_to_file
    // Create the first pipe
    if (pipe(pipe1_fds) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) { // First child process (ls -l)
        close(pipe1_fds[0]); // Close read end of pipe1
        dup2(pipe1_fds[1], STDOUT_FILENO); // Redirect stdout to write end of pipe1
        close(pipe1_fds[1]); // Close write end of pipe1 (after dup2)

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }
    // Create the second pipe
    if (pipe(pipe2_fds) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // Second child process (grep)
        close(pipe1_fds[1]); // Close write end of pipe1
        dup2(pipe1_fds[0], STDIN_FILENO); // Redirect stdin to read end of pipe1
        close(pipe1_fds[0]); // Close read end of pipe1 (after dup2)

        close(pipe2_fds[0]); // Close read end of pipe2
        dup2(pipe2_fds[1], STDOUT_FILENO); // Redirect stdout to write end of pipe2
        close(pipe2_fds[1]); // Close write end of pipe2 (after dup2)

        execlp("grep", "grep", argv[1], NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork3");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) { // Third child process (write to file)
        close(pipe1_fds[0]); // Close unused pipe ends
        close(pipe1_fds[1]);
        close(pipe2_fds[1]); // Close write end of pipe2

        dup2(pipe2_fds[0], STDIN_FILENO); // Redirect stdin to read end of pipe2
        close(pipe2_fds[0]); // Close read end of pipe2 (after dup2)

        int fd_out = open("filtered_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open filtered_output.txt");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO); // Redirect stdout to the file
        close(fd_out); // Close file descriptor (after dup2)

        // Read from stdin and write to stdout (which is now the file)
        char buffer[4096];
        ssize_t bytes_read;
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        exit(EXIT_SUCCESS);
    }

    // Parent process
    close(pipe1_fds[0]); // Close all pipe ends in the parent
    close(pipe1_fds[1]);
    close(pipe2_fds[0]);
    close(pipe2_fds[1]);

    // Wait for all child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}