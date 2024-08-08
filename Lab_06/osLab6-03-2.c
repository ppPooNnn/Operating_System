#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void main(int argc, char *argv[])
{
	printf("HELLO ...\n... %s\n", argv[2]);
	printf("PID: %d\n", getpid());
}
