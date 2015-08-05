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
	int fd;
	struct sockaddr_in addr;
	char buf[100];
	
	///////////////////////////////////////////////////////////////
	//创建套接字
	fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//////////////////////////////////////////////////////////////
	//初始化服务器地址，端口，协议
	bzero(&addr, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr("192.168.3.2");

	/////////////////////////////////////////////////////////////
	//连接服务器
	connect(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
	
	/////////////////////////////////////////////////////////////
	//读取
	bzero(buf, sizeof(buf));
	read(fd, buf, sizeof(buf));
	printf("read:[%s]\n", buf);

	////////////////////////////////////////////////////////////
	//写入
	bzero(buf, sizeof(buf));
	strcpy(buf, "hi");
	write(fd, buf, strlen(buf)+1);
	printf("write:[%s]\n", buf);

	///////////////////////////////////////////////////////////
	//结束
	close(fd);
	
	return 0;
}
