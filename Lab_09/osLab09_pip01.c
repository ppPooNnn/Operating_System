#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 10

void main()
{
    int nread, pfd[2];
    char read_buf[SIZE], write_buf[SIZE * 100];
    if (pipe(pfd) == -1)
    {
        perror("pipe failed\n");
        exit(-1);
    }

    if (fork() == 0)
    {
        close(pfd[1]);
        int cnt = 0;
        while ((nread = read(pfd[0], read_buf, SIZE) != 0))
        {
            // read_buf[SIZE] = '\0';
            printf("Child read at round %d : %s\n", cnt += 1, read_buf);
        }
        close(pfd[0]);
    }
    else
    {
        close(pfd[0]);
        strcpy(write_buf, "HELLO ... CS ... KMITL ... ARE YOU HAPPY?");
        write(pfd[1], write_buf, strlen(write_buf) + 1);
        close(pfd[1]);
        wait(NULL);
    }
}