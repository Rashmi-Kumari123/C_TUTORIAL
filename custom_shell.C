
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

// Function to split command into arguments
void parse_command(char *cmd, char **args) {
    int i = 0;
    char *token = strtok(cmd, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL; // execvp() requires NULL-terminated array
}

int main() {
    char input[MAX_INPUT];
    char *cmd1, *cmd2;
    char *args1[MAX_ARGS], *args2[MAX_ARGS];
    int pipefd[2];
    pid_t pid1, pid2;

    while (1) {
        // Shell prompt
        printf("mysh> ");
        fflush(stdout);

        // Take input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Ctrl+D exits
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        // Exit command
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Split into two commands by '|'
        cmd1 = strtok(input, "|");
        cmd2 = strtok(NULL, "|");

        if (cmd1 == NULL || cmd2 == NULL) {
            fprintf(stderr, "Error: Please enter in form cmd1 | cmd2\n");
            continue;
        }

        // Parse both commands into arguments
        parse_command(cmd1, args1);
        parse_command(cmd2, args2);

        // Create pipe
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        // First child: executes command1
        if ((pid1 = fork()) == 0) {
            dup2(pipefd[1], STDOUT_FILENO); // stdout → pipe write end
            close(pipefd[0]);               // close unused read end
            close(pipefd[1]);               // close write end (after dup2)
            execvp(args1[0], args1);
            perror("execvp cmd1"); exit(1);
        }

        // Second child: executes command2
        if ((pid2 = fork()) == 0) {
            dup2(pipefd[0], STDIN_FILENO);  // stdin ← pipe read end
            close(pipefd[1]);               // close unused write end
            close(pipefd[0]);               // close read end (after dup2)
            execvp(args2[0], args2);
            perror("execvp cmd2"); exit(1);
        }

        // Parent closes pipe and waits
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }

    return 0;
}
