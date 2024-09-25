#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "osLab11_peterson.h"

void childProcess(int *);
void parentProcess(int *);
int main(int argc, char *argv[])
{
    int shmID, status, *count;
    pid_t pid;
    shmID = shmget(IPC_PRIVATE, sizeof(struct Memory), IPC_CREAT | 0666);
    if (shmID < 0)
    {
        printf("*** shmget error (server) ***\n"); exit(1);
    }
    count = (int *) shmat(shmID, NULL, 0);
    if ((int) *count == -1) {
        printf("*** shmat error (server) ***\n"); exit(1);
    }
    *count = 5;
    initializePeterson(); // Initialize shared memory for Peterson
    pid = fork();
    if (pid < 0) {
        printf("*** fork error (server) ***\n");
        exit(1);
    }
    else if (pid == 0) {
        childProcess(count); // Child process do
        exit(0);
    }
    parentProcess(count); // Parent process do
    wait(&status);
    printf("The final value of count is %d\n", *count);
    removePeterson(); // Remove shared memory for Peterson
    shmdt((void *) count); // Remove shared memory
    shmctl(shmID, IPC_RMID, NULL);
    return 0;
}

void parentProcess(int *count) {
    enterCriticalSection(0);
    int temp = *count; temp++;
    sleep(rand() % 4);
    *count = temp;
    exitCriticalSection(0);
}
void childProcess(int *count) {
    enterCriticalSection(1);
    int temp = *count; temp--;
    sleep(rand() % 4);
    *count = temp;
    exitCriticalSection(1);
}