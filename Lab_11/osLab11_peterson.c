#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "osLab11_peterson.h"

static struct Memory *ptr;
static int shmID = 0;
void initializePeterson()
{
    shmID = shmget(IPC_PRIVATE, sizeof(struct Memory), IPC_CREAT | 0666);
    if (shmID < 0)
    {
        printf("*** shmget error (server) ***\n"); exit(1);
    }
    ptr = (struct Memory *) shmat(shmID, NULL, 0);
    if (ptr == NULL)
    {
        printf("*** shmat error (server) ***\n"); exit(1);

        ptr -> turn = 0;
        ptr -> flag[0] = FALSE;
        ptr -> flag[1] = FALSE;
    }
}

void removePeterson()
{
    shmdt((void *) ptr);
    shmctl(shmID, IPC_RMID, NULL);
}

void enterCriticalSection(int i)
{
    int j = 0;
    if (i == 0)
    {
        j = 1;
    }
    else
    {
        j = 0;
    }

    ptr -> turn = j;
    ptr -> flag[i] = TRUE;
    while (ptr -> flag[j] && ptr -> turn == j);
}

int exitCriticalSection(int i)
{
    ptr -> flag[i] = FALSE;
}
