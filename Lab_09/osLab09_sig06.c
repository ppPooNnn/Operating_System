#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int c_pid;

void main()
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        printf("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        c_pid = getpid();
        printf("Child created\n");
        while (1);
        printf("Hello from child :)\n");
    }
    else
    {
        printf("Parent created\n");
        sleep(3);
        printf("Hello from parent :)\n");
        kill(c_pid, SIGKILL);
    }
}