#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "osLab10_myShm.h"
void main(int argc, char *argv[]) {
    key_t shm_key; int shm_id;
    struct Memory *shm_ptr;
    if (argc != 5) {
    printf("Use: %s #1 #2 #3 #4\n", argv[0]); exit(1);
    }
    shm_key = ftok(".", 111);
    shm_id = shmget(shm_key, sizeof(struct Memory), IPC_CREAT | 0666);
    if (shm_id < 0) { printf("*** shmget error ***\n"); exit(1); }
    printf("Server has received a shared memory of four integers ...\n");
    shm_ptr = (struct Memory *) shmat(shm_id, NULL, 0);
    if (shm_ptr == NULL) { printf("*** shmat error ***\n"); exit(1); }
    printf("Server has attached the shared memory ...\n");
    shm_ptr->status = NOT_READY; // Sync server and client
    shm_ptr->data[0] = atoi(argv[1]);
    shm_ptr->data[1] = atoi(argv[2]);
    shm_ptr->data[2] = atoi(argv[3]);
    shm_ptr->data[3] = atoi(argv[4]);
    printf("Server has filled %d %d %d %d to shared memory ...\n",
                    shm_ptr->data[0],
                    shm_ptr->data[1],
                    shm_ptr->data[2],
                    shm_ptr->data[3]);
    shm_ptr->status = FILLED; // Sync server and client
    printf("Please start the client in another windows ...\n");
    while (shm_ptr->status != TAKEN) sleep(1);
    printf("Server has detected the completion of client ...\n");
    shmdt((void *) shm_ptr);
    printf("Server has detached its shared memory ...\n");
    shmctl(shm_id, IPC_RMID, NULL);
    printf("Server has removed its shared memory ...\n");
    printf("Server exits ...\n");
}