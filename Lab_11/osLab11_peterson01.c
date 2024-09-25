#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "osLab11_peterson.h"

void parentProcess(int *count);
void childProcess(int *count);

int main(int argc, char *argv[]) {
    int shmID, status, *count;
    int round = 10;
    shmID = shmget(IPC_PRIVATE, sizeof(struct Memory),
    IPC_CREAT | 0666);
    count = (int *) shmat(shmID, NULL, 0);
    *count = 99;
    initializePeterson(); // Initialize Peterson's algorithm
    if (fork() == 0) {
        for (int i = 0; i < round; i++) {
            childProcess(count);
        }
        exit(0);
    }
    for (int i = 0; i < round; i++) {
        parentProcess(count);
    }
    wait(&status);
    printf("The final value of count is %d\n", *count);
    removePeterson(); // Remove Peterson's algorithm
    shmdt((void *) count);
    shmctl(shmID, IPC_RMID, NULL);
    return 0;
}

void parentProcess(int *count) {
    enterCriticalSection(0);
    int temp = *count; temp++;
    sleep(rand() % 2);
    *count = temp;
    exitCriticalSection(0);
}

void childProcess(int *count)
{
    enterCriticalSection(1);
    int temp = *count; temp--;
    sleep(rand() % 2);
    *count = temp;
    exitCriticalSection(1);
}