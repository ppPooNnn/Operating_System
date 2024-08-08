#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t id;
	int i = 0;
	int sum = 0;
	int num;
	printf("Enter a positive number : ");
	scanf("%d", &num);

	if(num <= 0)
	{
		printf("You did not enter a positive number\n");
		exit(1);
	}

	if((id = fork()) > 0)
	{
		for(i = 1; i <= num; i++)
		{
			sum += i;
		}
		wait(NULL);
		printf("I'm parent, my sum = %d\n", sum);
	}
	else
	{
		for(i = 1; i <= 2 * num; i++)
		{
			sum += i;
		}
		printf("I'm child, my sum = %d\n", sum);
		exit(0);
	}
	return 0;
}
