#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	pid_t id;
	char input = 'z';
	while(input != 'q')
	{
		printf("\nSelect a letter to run a program\n");
		printf("'a' run --> uname -r\n");
		printf("'b' run --> ls -l\n");
		printf("'c' run --> ps -f\n");
		printf("'d' run --> df -h\n");
		printf("Exit a program press 'q'\n");
		printf("Enter a letter to run a program : ");
		scanf(" %c", &input);
	
		//-------------------my code-------------------
		switch(input)
		{
			case 'a' :
				id = fork();
				if(id == 0)
				{
					execlp("uname", "uname", "-r", NULL);
				}
				break;

			case 'b' :
				id = fork();
				if(id == 0)
				{
					execlp("ls", "ls", "-l", NULL);
				}
				break;

			case 'c' :
				id = fork();
				if(id == 0)
				{
					execlp("ps", "ps", "-f", NULL);
				}
				break;
				
			case 'd' :
				id = fork();
				if(id == 0)
				{
					execlp("df", "df", "-h", NULL);
				}
				break;
		}
	
		if(input == 'q')
			break;
		while(wait(NULL) != -1);
		//-------------------end of my code-------------------
	}
}
