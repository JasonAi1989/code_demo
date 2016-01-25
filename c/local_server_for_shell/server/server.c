#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>


int flag=1;

void handle_sig_child()//捕捉SIGCHLD信号后的处理fun
{
	int ret; 
	pid_t pid_c;
	pid_c=wait(&ret);//使进程睡眠，直到它的一个子进程退出时唤醒
	flag = 0;   //使主进程中读取的循环推出
	printf("Child proess PID = %d return %d.\n",pid_c,ret);
}

void local_execl()
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
		fflush(stdout);
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
		
			sys_record=0;
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
}

static int server(char* local_IP, int local_port)
{
	int fd[2];
	int fd_listen;
	int fd_work;
	struct sockaddr_in addr[2];
	int len;
	char buf[100];
	unsigned short port;
	int ret;
	
	signal(SIGUSR1, local_execl);
	
	bzero(&addr, sizeof(addr));
	ret=inet_aton(local_IP, &(addr[0].sin_addr));
	if(ret == 0)
	{
		printf("Error IP: %s\n", local_IP);
		return -1;
	}
	
	port=atoi(local_port);
	if(port == 0)
	{
		printf("Error port: %s\n", local_port);
		return -1;
	}

	addr[0].sin_family = AF_INET;
	addr[0].sin_port = htons(port);

	fd_listen = socket(AF_INET, SOCK_STREAM, 0);
	
	ret = bind(fd_listen, (struct sockaddr*)&addr[0], sizeof(struct sockaddr));
	if(ret == -1)
	{
        perror("bind:");
        close(fd_listen);
		return -1;
	}

	ret = listen(fd_listen, 10);
	if(ret == -1)
	{
        perror("listen:");
        close(fd_listen);
		return -1;
	}
	
	len = sizeof(struct sockaddr);
	fd_work = accept(fd_listen, (struct sockaddr *)&addr[1], &len);
	
    while(1)
    {
		//´Ó¿Í»§¶Ë¶ÁÈ¡Êý¾Ý
		bzero(buf, sizeof(buf));
		read(fd_work, buf, sizeof(buf));
		printf("read:[%s]\n", buf);

		if (strlen(buf)>0)
		{
			
			
		}

		//¿ªÊ¼Ìá¹©·þÎñ£¬Ïò¿Í»§¶ËÐ´ÈëÊý¾Ý
		bzero(buf, sizeof(buf));
		strcpy(buf, "hello");
		write(fd_work, buf, strlen(buf));
		printf("write:[%s]\n", buf);
    }

	//½áÊø
	close(fd_work);
	close(fd_listen);
	
	return 0;
}

int SFS_create_server(char* local_IP, int local_port)
{
	if (local_IP ==NULL || strlen(local_IP) == 0)
	{
		return -1;
	}
	if (local_port<=0 || local_port>65535)
	{
		return -1;
	}

	pid_t pid;


	pid=fork();
	if (pid == 0) //child
	{
		local_execl();
	}
	else if (pid > 0) //father
	{
		server(local_IP, local_port);
	}
	else
	{
		printf("fork error!\n");
	}

	return 0;
}
