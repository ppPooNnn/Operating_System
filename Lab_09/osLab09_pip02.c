#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 1024

void main()
{
    int pid, nread, pfd1[2], pfd2[2]; char buf[SIZE];
    if (pipe(pfd1) == -1)
    {
        perror("pipe failed"); exit(1);
    }
    if (pipe(pfd2) == -1)
    {
        perror("pipe failed"); exit(1);
    }
    if ((pid = fork()) < 0)
    {
        perror("fork failed"); exit(2);
    }
    if (pid == 0)
    {
        close(pfd1[1]); close(pfd2[0]);
        while ((nread = read(pfd1[0], buf, SIZE)) != 0)
        {
            printf("Child read :\t %s\n", buf);
        }
        close(pfd1[0]);
        
        strcpy(buf, "I am fine thank you :)");
        write(pfd2[1], buf, strlen(buf) + 1);
        close(pfd2[1]);
    }
    else
    {
        close(pfd1[0]); close(pfd2[1]);
        strcpy(buf, "How are you ?");
        write(pfd1[1], buf, strlen(buf) + 1);
        close(pfd1[1]);
        while ((nread = read(pfd2[0], buf, SIZE)) != 0)
        {
            printf("Parent read:\t %s\n", buf);
        }
        close(pfd2[0]);
    }
}