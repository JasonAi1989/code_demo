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
	//�����׽���
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == fd)
	{
		printf("socket error\n");
		return -1;
	}
	
	/////////////////////////////////////////////////////////////////
	//��ʼ����������ַ���˿ڣ�Э��
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(PORT);
	bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//�������ʹ��ͨ���ַ
	//bind_addr.sin_addr.s_addr = inet_addr(IP);	//�����ý����޷�ʹ�öಥ��
	
	/////////////////////////////////////////////////////////////////
	//�󶨱��ط���
	bind(fd, (struct sockaddr*)&bind_addr, sizeof(bind_addr));

	/////////////////////////////////////////////////////////////////
	//��ʼ���ಥ���ݽ��ն������ַ
    mcast.imr_multiaddr.s_addr = inet_addr(MULTI_ADDR);	//ָ���ಥ���ַ
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);

	/////////////////////////////////////////////////////////////////
	//����ಥ,�˴����ܻ���Ϊ�豸δ����ಥ���ض����ش���
	ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mcast, sizeof(mcast));
	if(ret < 0)
	{
		perror("setsockopt");
		return -1;
	}
	
	/////////////////////////////////////////////////////////////////
	//���նಥ����
	while(1)
	{
		recvfrom(fd, (void*)buf, sizeof(buf), 0, (struct sockaddr*)&from_addr, &addrlen);
		printf("data:%s\n", buf);
		printf("addr:%s\n", inet_ntoa(from_addr.sin_addr));
		bzero(buf, sizeof(buf));
	}
	
	return 0;
}
