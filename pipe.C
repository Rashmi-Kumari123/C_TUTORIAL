#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
int main(){
    int fds[2];
    char buf[38];
    if (pipe(fds)== -1){
        perror("pipe");
        exit(1);


    }printf("writing to file descriptor #%d\n", fds[1]);
    write(fds[1], "testing", 8);
    printf("reading from file descriptor #%d\n", fds[0]);
}
