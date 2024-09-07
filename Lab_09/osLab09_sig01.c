#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void SIGhandler(int sig);

void main()
{
    signal(SIGQUIT, SIGhandler);
    while(1)
    {
        printf("Going to sleep for a second ...\n");
        sleep(1);
    }
}

void SIGhandler(int sig)
{
    printf("Caught signal %d, coming out ...\n", sig);
    exit(0);
}