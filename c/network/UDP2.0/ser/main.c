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

int main(int argc, char const* argv[])
{
	int fd;
	struct sockaddr_in addr[2];
	int len;
	char buf[100];
	char *p=NULL;

	/////////////////////////////////////////////////////////////////
	//创建套接字
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	/////////////////////////////////////////////////////////////////
	//初始化服务器地址，端口，协议
    if(argc==3)
    {
        addr[0].sin_family      = AF_INET;
        addr[0].sin_port        = htons(atoi(argv[2]));
        addr[0].sin_addr.s_addr = inet_addr(argv[1]);
    }
    else
    {
        addr[0].sin_family      = AF_INET;
        addr[0].sin_port        = htons(8123);
        addr[0].sin_addr.s_addr = inet_addr("127.0.0.1");
    }

	////////////////////////////////////////////////////////////////
	//绑定服务器地址
	bind(fd, (struct sockaddr*)&addr[0], sizeof(struct sockaddr));

	////////////////////////////////////////////////////////////////
	//接收数据
	bzero(buf, sizeof(buf));
	int ret = recvfrom(fd, (void*)buf, 100, 0, (struct sockaddr*)&addr[1], &len);
	printf("1 ret:%d, len:%d, buf:%s\n", ret, len, buf);

	////////////////////////////////////////////////////////////////
	//发送数据
	p = "I'm uncle";
	sendto(fd, (void*)p, strlen(p)+1, 0, (struct sockaddr*)&addr[1], len);

	close(fd);
	return 0;
}
