#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;

    printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());

    // Create Child Process
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed for child");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // This is the Child Process
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());

        // Create Grandchild Process
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("fork failed for grandchild");
            exit(EXIT_FAILURE);
        } else if (grandchild_pid == 0) {
            // This is the Grandchild Process
            printf("Grandchild Process: PID = %d, PPID = %d\n", getpid(), getppid());
            printf("Grandchild Process (PID %d) exiting.\n", getpid());
            exit(EXIT_SUCCESS); // Grandchild terminates
        } else {
            // This is still the Child Process (parent of grandchild)
            printf("Child Process (PID %d) waiting for Grandchild (PID %d).\n", getpid(), grandchild_pid);
            waitpid(grandchild_pid, NULL, 0); // Child waits for grandchild
            printf("Child Process (PID %d) detected Grandchild (PID %d) termination.\n", getpid(), grandchild_pid);
            printf("Child Process (PID %d) exiting.\n", getpid());
            exit(EXIT_SUCCESS); // Child terminates
        }
    } else {
        // This is the Parent Process
        printf("Parent Process (PID %d) waiting for Child (PID %d).\n", getpid(), child_pid);
        waitpid(child_pid, NULL, 0); // Parent waits for child
        printf("Parent Process (PID %d) detected Child (PID %d) termination.\n", getpid(), child_pid);
        printf("Parent Process (PID %d) exiting.\n", getpid());
        exit(EXIT_SUCCESS); // Parent terminates
    }

    return 0;
}