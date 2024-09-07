#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SLEEP 3

int flag = 1; int count = 0;

void mySIGhandler(int sig)
{
    signal(SIGKILL, SIG_IGN);
    flag = 0;
}

void main()
{
    clock_t start; pid_t pid;
    signal(SIGKILL, mySIGhandler);
    if ((pid = fork()) < 0)
    {
        printf("fork failed"); exit(1);
    }
    else if (pid == 0)
    {
        sleep(SLEEP);
        printf("Child sending signal ...\n");
        kill(getppid(), SIGKILL);
        exit(0);
    }
    else
    {
        printf("parent waiting signal ...\n");
        start = clock();
        while(flag) count += 1;
        printf("It takes %d loops\n", count);
        printf("It takes %.2f sec.\n", (double)((clock() - start) / CLOCKS_PER_SEC));
    }
}