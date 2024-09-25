#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

#define NITER 100000

pthread_attr_t attr[2];
pthread_t tid[2];
sem_t mySemaphore;
int cnt;
void * Count(void* a) {
    int i;
    for (i = 0; i < NITER; i++) {
        sem_wait(&mySemaphore);
        cnt++;
        sem_post(&mySemaphore);
    }
    void* lastSeen = malloc(sizeof(int));
    // LastSeen now refers to an actual piece of memory
    if (pthread_self() == tid[0]) {
        *(int *)lastSeen = cnt;
        printf("thr %lu exits. lastSeen = %d\n", pthread_self(),
        *(int *)lastSeen );
        pthread_exit( (void*)lastSeen );
    }
}

int main() {
    sem_init(&mySemaphore, 0, 1);
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    pthread_create(&tid[0],&attr[0], Count, NULL);
    pthread_create(&tid[1],&attr[1], Count, NULL);
    void* returnVal;
    pthread_join(tid[0], &returnVal);
    int x = *(int*)returnVal;
    printf("Last cnt from tid[0] is %d\n", x);
    pthread_join(tid[1], NULL);
    printf("final cnt = %d\n", cnt);
    sem_destroy(&mySemaphore);
    return 0;
}