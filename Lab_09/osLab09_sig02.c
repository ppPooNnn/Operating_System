#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void SIGhandler(int sig)
{
    switch (sig)
    {
        case 2:
            printf("Ha Ha Ha ... you can not interrupt me ;P\n");
            break;
        case 3:
            printf("Ha Ha Ha ... you can not quit me ;P\n");
            break;
    }
}

int main(void)
{
    if(signal(SIGQUIT, SIGhandler) == SIG_ERR)
    {
        printf("\ncan't catch SIGQUIT\n");
    }

    if(signal(SIGINT, SIGhandler) == SIG_ERR)
    {
        printf("\ncan't catch SIGINT\n");
    }

    while(1)
    {
        sleep(1);
    }
    return(0);
} 