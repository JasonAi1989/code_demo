#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("please input target process pid\n");
		return -1;
	}
	
	int pid = atoi(argv[1]);
	
	kill((pid_t)pid, SIGUSR1);
	
	sleep(1);
	
	kill((pid_t)pid, SIGCHLD);
		
	return 0;
}