#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *myfunc(void *argv)
{
    printf("From thread process ...\n");
    int toProcess = atoi(argv) * 2;
    int *csum = (int *)malloc(sizeof(int));
    *csum = 0;
    for(int i = 0; i <= toProcess; i++)
    {
        *csum += i;
    }
    printf("csum = %d\n", *csum);
    pthread_exit((void *)csum);
}

void main(int argc, char** argv)
{
    pthread_t tid;
    int *csum;
    int msum = 0;
    int toProcess = atoi(argv[1]);
    pthread_create(&tid, NULL, myfunc, (void *)argv[1]);
    pthread_join(tid,(void **)&csum);
    printf("From main process ...\n");
    for(int i = 0; i <= toProcess; i++)
    {
        msum += i;
    }
    printf("msum = %d\n", msum);

    printf("Difference csum and msum = %d\n", *csum - msum);

    free(csum);
}