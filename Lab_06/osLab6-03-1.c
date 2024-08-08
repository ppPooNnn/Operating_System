#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void main()
{
	printf("PID: %d\n", getpid());
	char *argv[] = {"myProgram", "CS", "KMITL", NULL};
	execvp("myProgram", argv);
	printf("Bye Bye ...\n");
}
