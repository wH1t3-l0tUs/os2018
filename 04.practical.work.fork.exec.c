#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("Main before fork()\n");
	int dad = fork();
	if (dad==0)
		exit(0);
	else
	{
		int child = fork();
		if (child == 0)
		{	
			printf("I am first child after fork(), launching free -h\n");
			char *args[]= { "/bin/ps", "-ef" , NULL};
			execvp("/bin/ps", args);
		}
		else
		{
			printf("I am second child after fork(), launching free -h\n");
			char *args[]= { "free", "-h" , NULL};
			execvp("free", args);
		}
	}
	return 0;
}