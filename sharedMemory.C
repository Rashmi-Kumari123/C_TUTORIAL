#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(){
    int shmid;
    char *shmPtr;
    int n;
    if ((shmid = shmget(2041, 32, 0666 | IPC_CREAT) )==  -1)
        exit(1);
    shmPtr = shmat(shmid, NULL, 0);
    if (shmPtr == (char *) -1)
        exit(2);
    printf("writer writing to shared memory ..\n\n");
        for (n=0; n<26; n++)
            shmPtr[n] = 'A' + n;

    sleep(100);
    if (shmct1(shmid, IPC_RMID, NULL) == -1){
        perror("shmct1");
        exit(-1);

    }
    return 0;
    
}