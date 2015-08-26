#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thrfxn();

int main(int argc, const char *argv[])
{
	pthread_t tid = 0;

	pthread_create(&tid, NULL, (void *)thrfxn, NULL);

	int i;

	for(i=0; i<5; i++)	
	{
		printf("I'm father\n");
		sleep(1);
	}

	return 0;
}

void *thrfxn()
{
	pthread_detach(pthread_self());

	while(1)
	{
		printf("I'm children\n");
		sleep(1);
	}

	pthread_exit(NULL);
}
