#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[100];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;

    // if ((msqid = msgget(42, 0644 | IPC_CREAT)) == -1) {
    if ((msqid = msgget(42, 0644)) == -1) {
        perror("msgget");
        exit(1);
    }
    printf("Enter lines of text, ^D to quit:\n");
   
    buf.mtype = 2;

    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        int len = strlen(buf.mtext);
//printf("%d \n", buf.mtext[len-1]);
        /* ignore newline at end, if it exists */
        if (buf.mtext[len-1] == '\n')
            buf.mtext[len-1] = '\0';
        if (msgsnd(msqid, &buf, len+1, 0) == -1)  /* +1 for '\0' */
            perror("msgsnd");
    }
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
