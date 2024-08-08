#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main()
{
	char *command[] = {"ls", "-a", "-l", NULL};
	printf("PID: %d\n", getpid());
	printf("HELLO ...\n");
	pid_t id = fork();
	if(id == 0)
	{
		//execlp("echo", "echo", "... CS", NULL);
		execv("/usr/bin/ls",command);
	}
	else
	{
		wait(NULL);
		printf("... KMITL\n");
	}
}
