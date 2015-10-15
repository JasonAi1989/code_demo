#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int flag=1;

void handle_sig_child()//捕捉SIGCHLD信号后的处理fun
{
 int ret; 
 pid_t pid_c;
 pid_c=wait(&ret);//使进程睡眠，直到它的一个子进程退出时唤醒
 flag = 0;   //使主进程中读取的循环推出
 printf("Child proess PID = %d return %d.\n",pid_c,ret);
}

int main()
{
    int pipefd[2];
	pid_t forkfd;
	
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
		execl("/root/aizhaoyu_test.sh", "aizhaoyu_test.sh", NULL);
		
		exit(0);
	}
	else   //father
	{
		char buf[1024];
		int size;
		int sys_record=0;
		
		close(pipefd[1]);
	
		fd_set read_fdst;
		FD_ZERO(&read_fdst);
		FD_SET(pipefd[0], &read_fdst);
		
		flag=1;
		while(flag)
		{
			int nfds = select(pipefd[0]+1, &read_fdst, NULL, NULL, NULL);
			if(nfds == -1)
			{
				sys_record++;
				if(sys_record == 10)
					flag = 0;
					
				usleep(100);
				continue;
			}
		
			if(FD_ISSET(pipefd[0], &read_fdst))
			{
				bzero(buf, sizeof buf);
				int nrd = read(pipefd[0], buf, sizeof buf);
				if(nrd > 0)
				{
					//printf("%s\n", buf);
				}
			}
		}
	}

    return 0;
}
