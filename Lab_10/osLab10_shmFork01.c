#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    int *count, shm_id;

    // shm_id = shmget(key, sizeof(int), 0666 | IPC_CREAT);
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    count = (int *) shmat(shm_id, NULL, 0);
    count[0] = 100;
    if (fork() == 0)
    {
        int temp = count[0]; sleep(1);
        temp -= 1; count[0] = temp;
        printf("temp = %d\n", temp);
        printf("Child decrements value  at %p\n", &count);
        exit(0);
    }
    // wait(NULL);
    int temp = count[0]; sleep(1);
    temp += 1; count[0] = temp;
    printf("temp = %d\n", temp);
    printf("Parent increments value at %p\n", &count);
    sleep(3); printf("final answer is %d\n", count[0]);
    shmdt(count);
    shmctl(shm_id, IPC_RMID, NULL);
}