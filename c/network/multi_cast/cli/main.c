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

#define PORT 3702
#define MULTI_ADDR	"239.255.255.250"

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
	//初始化多播组的地址，仅用于发送数据
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(MULTI_ADDR);

	////////////////////////////////////////////////////////////
	//发送数据
	bzero(buf, sizeof(buf));
	strcpy(buf, "hi");
	sendto(fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
	printf("sendto:[%s]\n", buf);

	///////////////////////////////////////////////////////////
	//结束
	close(fd);
	
	return 0;
}
