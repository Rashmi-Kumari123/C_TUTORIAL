#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
    key_t key;

    if ((msqid = msgget(42, 0644)) == -1) { // connect to the queue
        perror("msgget");
        exit(1);
    }
   
    printf("Robin: ready to receive messages!\n");

    while(1) { // Because robin never quits !
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Robin: \"%s\"\n", buf.mtext);
    }

    return 0;
}