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

int main(int argc, char* argv[])
{
	int fd[2];
	struct sockaddr_in addr[2];
	int len;
	char buf[100];
	unsigned short local_port;
	int ret;
	
	//cheak args
	if(argc != 3)
	{
		printf("Absent args: [local ip] [local port]\n");
		return 1;
	}
	
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
	ret = listen(fd[0], 10);
	if(ret == -1)
	{
        perror("listen:");
		return 1;
	}
	
	//开始等待客户端的连接,会提供进行服务所需的句柄
	len = sizeof(struct sockaddr);
	fd[1] = accept(fd[0], (struct sockaddr *)&addr[1], &len);
	
    while(1)
    {
		//从客户端读取数据
		bzero(buf, sizeof(buf));
		read(fd[1], buf, sizeof(buf));
		printf("read:[%s]\n", buf);

		//开始提供服务，向客户端写入数据
		bzero(buf, sizeof(buf));
		strcpy(buf, "hello");
		write(fd[1], buf, strlen(buf));
		printf("write:[%s]\n", buf);
    }

	//结束
	close(fd[1]);
	close(fd[0]);
	
	return 0;
}
