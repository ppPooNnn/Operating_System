#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void INThandler(int sig)
{
    signal(SIGINT, SIG_IGN);
    printf("\nCtrl-C was hit !!!\nWant to quit? [y/n]\n");
    char input;
    input = getchar();
    if(input == 'y' || input == 'Y')
    {
        exit(0);
    }
    else
    {
        signal(SIGINT, INThandler);
    }
}

int main(void)
{
    signal(SIGINT, INThandler);
    while(1)
    {
        pause();
    }
    return 0;
}