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
	int len;
	
	///////////////////////////////////////////////////////////////
	//创建套接字
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//////////////////////////////////////////////////////////////
	//初始化服务器地址，端口，协议
	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8123);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	////////////////////////////////////////////////////////////
	//写入
	bzero(buf, sizeof(buf));
	strcpy(buf, "hello world");
	sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
	printf("sendto:[%s]\n", buf);
#if 0 
	//读取
	bzero(buf, sizeof(buf));
	len = sizeof(addr);
	recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
	printf("recvfrom:[%s]\n", buf);
#endif
	///////////////////////////////////////////////////////////
	//结束
	close(fd);
	
	return 0;
}
