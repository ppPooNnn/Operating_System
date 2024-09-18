#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void clientProcess(int shm_addr[]);

void main(int argc, char *argv[])
{
    int shm_id, *shm_addr;
    pid_t pid;
    if (argc != 5)
    {
        printf("Use : %s #1 #2 #3 #4\n", argv[0]); exit(1);
    }
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        printf("*** shmget error (server) ***\n"); exit(1);
    }
    shm_addr = (int *)shmat(shm_id, NULL, 0);
    if (shm_addr == NULL)
    {
        printf("*** shmat error (server) ***\n"); exit(1);
    }
    shm_addr[0] = atoi(argv[1]);
    shm_addr[1] = atoi(argv[2]);
    shm_addr[2] = atoi(argv[3]);
    shm_addr[3] = atoi(argv[4]);
    printf("Server has filled %d %d %d %d in shared memory ...\n", shm_addr[0], shm_addr[1], shm_addr[2], shm_addr[3]);
    printf("Server is about to fork a child process ...\n");
    if ((pid = fork()) < 0)
    {
        printf("*** fork error (server) ***\n"); exit(1);
    }
    else if (pid == 0)
    {
        clientProcess(shm_addr); exit(0);
    }
    else
    {
        wait(NULL);
        printf("Server has detected the completion of its child ...\n");
        shmdt((void *) shm_addr);
        printf("Server has detached its shared memory ...\n");
        shmctl(shm_id, IPC_RMID, NULL);
        printf("Server has removed its shared memory ...\n");
        printf("Server exits ...\n");
    }
}

void clientProcess(int shm_addr[])
{
    printf("\tClient process started\n");
    printf("\tClient found %d %d %d %d in shared memory\n", shm_addr[0], shm_addr[1], shm_addr[2], shm_addr[3]);
    printf("\tClient is about to exit\n");
}