void report_exit(constant char* msg){
    perror(msg);
    exit(-1);
}
int main(){

    int pdf[2];
    if (pipe(pfd) < 0)

        report_exit("pipeFD");
    pid_t cpid = fork();
    if (cpid < 0) report_exit("fork");
    if (cpid == 0){  //fork return 0n in the child process
        close(pfd[0])
        dup2(pfd[1], 1);
        close(pfd[1]);
        execlp("ps", "ps", "-ef", NULL);

    }else(
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp("wc", "wc", "-l", NULL);

    )return 0;

}