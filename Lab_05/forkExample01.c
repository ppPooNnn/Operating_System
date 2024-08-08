#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	fork();
	fork();
	fork();
	pid_t id = getpid();
	printf("Hello CS KMITL !! : ID is %d\n", id);
	sleep(30);
	return 0;
}
