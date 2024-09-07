#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

signed long prev, i;
void SIGUSRhandler(int sig)
{
    printf("Received SIGUSR1. The max is %ld! = %ld\n",  i - 1, prev);
    exit(0);
}

int main(void)
{
    signed long curr;
    signal(SIGUSR1, SIGUSRhandler);
    for (prev = i = 1; ; i++, prev = curr)
    {
        curr = prev * i;
        if (curr < prev)
        {
            raise(SIGUSR1);
        }
        else
            printf("%ld! = %ld (%ld)\n", i, curr, prev);
    }
    return 0;
}