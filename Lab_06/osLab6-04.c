#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main(int argc, char *argv[])
{
	pid_t c_pid, gc_pid;
	c_pid = fork();
	if(c_pid < 0)
	{
		printf("Fork Failed\n");
	}
	else if(c_pid == 0)
	{
		gc_pid = fork();
		if(gc_pid == 0)
		{
			printf("Number: 1\n");
			execl("/usr/bin/whoami", argv[1], NULL);
			exit(0);
		}
		printf("Number: 2\n");
	}
	else
	{
		printf("Number: 3\n");
		wait(NULL);
		printf("Number: 4\n");
		exit(0);
	}
}
