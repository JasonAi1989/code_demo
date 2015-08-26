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

int main()
{
	int fd[2];
	struct sockaddr_in addr[2];
	int len;
	char buf[100];
	
	/////////////////////////////////////////////////////////////////
	//创建套接字
	fd[0] = socket(AF_INET, SOCK_STREAM, 0);
	
	/////////////////////////////////////////////////////////////////
	//初始化服务器地址，端口，协议
	bzero(addr, sizeof(addr));
	
	addr[0].sin_family = AF_INET;
	addr[0].sin_port = htons(8123);
	addr[0].sin_addr.s_addr = inet_addr("127.0.0.1");
	
	////////////////////////////////////////////////////////////////
	//绑定服务器地址
	bind(fd[0], (struct sockaddr*)&addr[0], sizeof(struct sockaddr));
	
	////////////////////////////////////////////////////////////////
	//对服务器绑定的端口进行监听
	listen(fd[0], 10);
	
	////////////////////////////////////////////////////////////////
	//开始等待客户端的连接,会提供进行服务所需的句柄
	len = sizeof(struct sockaddr);
	fd[1] = accept(fd[0], (struct sockaddr *)&addr[1], &len);
	
	////////////////////////////////////////////////////////////////
	//开始提供服务，向客户端写入数据
	bzero(buf, sizeof(buf));
	strcpy(buf, "hello");
	write(fd[1], buf, strlen(buf));
	printf("write:[%s]\n", buf);
	
	///////////////////////////////////////////////////////////////
	//从客户端读取数据
	bzero(buf, sizeof(buf));
	read(fd[1], buf, sizeof(buf));
	printf("read:[%s]\n", buf);
	
	//////////////////////////////////////////////////////////////
	//结束
	close(fd[1]);
	close(fd[0]);
	
	return 0;
}
