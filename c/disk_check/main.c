#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define LEN 1024
int flag=1;

void handle_sig_child()//捕捉SIGCHLD信号后的处理fun
{
	int ret; 
	pid_t pid_c;
	pid_c=wait(&ret);//使进程睡眠，直到它的一个子进程退出时唤醒
	flag = 0;   //使主进程中读取的循环推出
	printf("Child proess PID = %d return %d.\n",pid_c,ret);
}

//return the available capacity percent
int analysis_command(char* buf)
{
	char fs[LEN], mount[LEN];
	float a,b,c;
	int d;
	char e1,e2,e3;
	char* p=NULL;
	
	bzero(fs, LEN);
	bzero(mount, LEN);
	
	p = strstr(buf, "/dev/");
	if(p == NULL)
	{
		printf("can't find /dev/ in df command\n");
		return 0;
	}	
	sscanf(p,"%s %f%c %f%c %f%c %d% %s\n", 
		fs, &a, &e1, &b, &e2, &c, &e3, &d, mount);
	printf("%s %0.1f%c %0.1f%c %0.1f%c %d %s\n", fs, a, e1, b, e2, c, e3, d, mount);

	return 100-d;
}

int main()
{
    int pipefd[2];
	pid_t forkfd;
	int available=0;
	
	signal(SIGCHLD,handle_sig_child);//捕捉SIGCHLD信号,并调取handle_sig_child()进行处理
	
	pipe(pipefd);

	if((forkfd=fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(forkfd == 0)  //child
	{
		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		
		printf("test\n");
		execl("/bin/df", "df", "-hl", "/var", NULL);
		
		exit(0);
	}
	else   //father
	{
		char buf[1024];
		int size;
		
		close(pipefd[1]);
		
		while(flag)
		{
			bzero(buf, sizeof buf);
			size = read(pipefd[0], buf, sizeof buf);
			if(size == 0)
				continue;
				
			printf("%s\n", buf);
			available = analysis_command(buf);
		}
		
		if(available < 20)  //del the old log files
		{
		
		}
		else   //go on writing log
		{
		
		}
		
	}
    return 0;
}

