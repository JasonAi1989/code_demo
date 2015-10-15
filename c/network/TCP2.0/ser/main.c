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
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define LISTEN_NUM	10
#define ERROR_NUM	10

int fork_num=0;
int listen_num = 0;

void handle_sig_child()//捕捉SIGCHLD信号后的处理fun
{
	int ret; 
	pid_t pid_c;
	pid_c=wait(&ret);//使进程睡眠，直到它的一个子进程退出时唤醒
	fork_num--;
	listen_num--;
	
	printf("listerned: [%d], forked: [%d]\n", listen_num, fork_num);
	printf("Child proess PID = %d return %d.\n",pid_c,ret);
}

void do_detail(int fd)
{
	if(fd < 0)
		return;
	
	char buf[100];
	
	while(1)
    {
		//从客户端读取数据
		bzero(buf, sizeof(buf));
		read(fd, buf, sizeof(buf));
		
		if(strlen(buf) == 0)
			break;
		
		printf("fd [%d] read:[%s]\n", fd, buf);

		//开始提供服务，向客户端写入数据
		bzero(buf, sizeof(buf));
		strcpy(buf, "hello");
		write(fd, buf, strlen(buf));
		printf("fd [%d] write:[%s]\n", fd, buf);
    }

	close(fd);
	
	return;
}

int main(int argc, char* argv[])
{
	int fd[2];
	struct sockaddr_in addr[2];
	int len;
	
	unsigned short local_port;
	int ret;

	int error_num = ERROR_NUM;
	
	//cheak args
	if(argc != 3)
	{
		printf("Absent args: [local ip] [local port]\n");
		return 1;
	}
	
	signal(SIGCHLD,handle_sig_child);//捕捉SIGCHLD信号,并调取handle_sig_child()进行处理
	
	bzero(&addr, sizeof(addr));
	ret=inet_aton(argv[1], &(addr[0].sin_addr));
	if(ret == 0)
	{
		printf("Error IP: %s\n", argv[1]);
		return 1;
	}
	
	local_port=atoi(argv[2]);
	if(local_port == 0)
	{
		printf("Error port: %s\n", argv[2]);
		return 1;
	}
	
	//创建套接字
	fd[0] = socket(AF_INET, SOCK_STREAM, 0);
	
	//初始化服务器地址，端口，协议
	bzero(addr, sizeof(addr));
	
	addr[0].sin_family = AF_INET;
	addr[0].sin_port = htons(local_port);
	
	//绑定服务器地址
	ret = bind(fd[0], (struct sockaddr*)&addr[0], sizeof(struct sockaddr));
	if(ret == -1)
	{
        perror("bind:");
		return 1;
	}

	//对服务器绑定的端口进行监听
	ret = listen(fd[0], LISTEN_NUM);
	if(ret == -1)
	{
        perror("listen:");
		return 1;
	}
	
	//开始等待客户端的连接,会提供进行服务所需的句柄
	while(listen_num == LISTEN_NUM || error_num)
	{
		len = sizeof(struct sockaddr);
		fd[1] = accept(fd[0], (struct sockaddr *)&addr[1], &len);		
		if(fd[1] == -1)
		{
			perror("accept:");
			error_num--;
			continue;
		}
		
		pid_t forkid = fork();
		if(forkid == 0) //child
		{
			do_detail(fd[1]);
			
			exit(0);
		}
		else if(forkid > 0) //father
		{
			fork_num++;
			listen_num++;
			printf("listerned: [%d], forked: [%d]\n", listen_num, fork_num);
			continue;
		}
		else
		{
			perror("fork:");
			error_num--;
			continue;
		}
	}
	
	while(fork_num)
	{
		usleep(100);
	}
	
	//结束
	close(fd[0]);
	
	return 0;
}
