#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void print_even() {
    printf("Child Process: First 20 Even Numbers:\n");
    for (int i = 1; i <= 20; i++) {
        printf("%d ", 2 * i);
    }
    printf("\n");
}


int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}


void print_prime() {
    printf("Parent Process: First 10 Prime Numbers:\n");
    int count = 0, num = 2;
    while (count < 10) {
        if (is_prime(num)) {
            printf("%d ", num);
            count++;
        }
        num++;
    }
    printf("\n");
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        print_even();
    } 
    else if (pid > 0) {
        // Parent process
        wait(NULL);  // wait for child to finish
        print_prime();
    } 
    else {
        printf("Fork failed!\n");
    }

    return 0;
}
