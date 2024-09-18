#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char *shm_addr; int isLoop = 1;
void SIGHandler(int sig)
{
    signal(sig, SIG_IGN);
    printf("-\tSIGHandler on server catch a singal %d from client ...\n", sig);
    isLoop = 0; signal(sig, SIGHandler);
}

void main()
{
    signal(SIGUSR1, SIGHandler);
    key_t key = ftok(".", 99);
    int shm_id = shmget(key, 1024, 0666 | IPC_CREAT);
    shm_addr = (char *) shmat(shm_id, NULL, 0);
    sprintf(shm_addr, "%d", getpid());
    printf("(1) [Server] Writing the server pid = %s from shared memory ...\n", shm_addr);
    while (isLoop); isLoop = 1;
    int client_pid = atoi(shm_addr);
    printf("(4) [Server] Reading the client pid = %s from shared memory ...\n", shm_addr);
    kill(client_pid, SIGUSR2);
    printf("-\tServer send a signal %d to client ...\n", SIGUSR2);
    while (isLoop);
    printf("(6) [Server] Reading data \"%s\" from shared memory ...\n", shm_addr);
    shmdt(shm_addr);
    shmctl(shm_id, IPC_RMID, NULL);
}