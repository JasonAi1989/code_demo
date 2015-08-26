#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <poll.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <fcntl.h>
#include <fcntl.h>

#define PORT		3702
#define IP			"192.168.9.150"
#define MULTI_ADDR	"239.255.255.250"

int main(int argc, const char *argv[])
{
	int fd;
	struct sockaddr_in bind_addr, from_addr;
	struct ip_mreq mcast;
	char buf[100];
	socklen_t addrlen;
	int ret;
	
	/////////////////////////////////////////////////////////////////
	//创建套接字
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == fd)
	{
		printf("socket error\n");
		return -1;
	}
	
	/////////////////////////////////////////////////////////////////
	//初始化服务器地址，端口，协议
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(PORT);
	bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//这里必须使用通配地址
	//bind_addr.sin_addr.s_addr = inet_addr(IP);	//这样用将会无法使用多播组
	
	/////////////////////////////////////////////////////////////////
	//绑定本地服务
	bind(fd, (struct sockaddr*)&bind_addr, sizeof(bind_addr));

	/////////////////////////////////////////////////////////////////
	//初始化多播数据接收端网络地址
    mcast.imr_multiaddr.s_addr = inet_addr(MULTI_ADDR);	//指定多播组地址
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);

	/////////////////////////////////////////////////////////////////
	//加入多播,此处可能会因为设备未加入多播网关而返回错误
	ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mcast, sizeof(mcast));
	if(ret < 0)
	{
		perror("setsockopt");
		return -1;
	}
	
	/////////////////////////////////////////////////////////////////
	//接收多播数据
	while(1)
	{
		recvfrom(fd, (void*)buf, sizeof(buf), 0, (struct sockaddr*)&from_addr, &addrlen);
		printf("data:%s\n", buf);
		printf("addr:%s\n", inet_ntoa(from_addr.sin_addr));
		bzero(buf, sizeof(buf));
	}
	
	return 0;
}
