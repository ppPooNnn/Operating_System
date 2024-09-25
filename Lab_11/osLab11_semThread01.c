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
#include "osLab11_peterson.h"

int count = 100;
sem_t mutex;
void *increment(void *param);
void *decrement(void *param);

int main() {
    pthread_t tid1, tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    sem_init(&mutex, 0, 1);
    pthread_create(&tid1, &attr, increment, NULL);
    pthread_create(&tid2, &attr, decrement, NULL);
    /* Not wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("count = %d\n", count);
    sem_destroy(&mutex);
    return 0;
}
void *increment(void *param) {
    int temp;
    sem_wait(&mutex);
    temp = count;
    sleep(rand() % 5); temp+=1;
    count = temp;
    sem_post(&mutex);
    pthread_exit(0);
}

void *decrement(void *param){
    int temp;
    sem_wait(&mutex);
    temp = count;
    sleep(rand() % 5); temp-=1;
    count = temp;
    sem_post(&mutex);
    pthread_exit(0);
}
