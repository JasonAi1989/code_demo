#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void handle_chld()
{
	printf("get SIGCHLD\n");
}
void handle_usr1()
{
	printf("get SIGUSR1\n");
}


int main()
{
	signal(SIGUSR1,handle_usr1);	//10
	signal(SIGCHLD,handle_chld);  	//17
	
	while(1)
		sleep(1);
	
	return 0;
}