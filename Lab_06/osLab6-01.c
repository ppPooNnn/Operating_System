#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void main()
{
	printf("#1 P_PID: %d\n", getpid());
	pid_t id = fork();
	if(id == 0)
	{
		printf("#2 C_PID: %d\n", getpid());
		printf("#3 P_PID: %d\n", getppid());
		//sleep(1);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("#4 P_PID: %d\n", getpid());
		printf("#5 C_PID: %d\n", id);
		//sleep(1);
	}
	printf("HELLO CS KMITL");
}
