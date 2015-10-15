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
	int fd;
	struct sockaddr_in addr;
	char buf[100];
	unsigned short dst_port;
	int ret;
	
	//cheak args
	if(argc != 3)
	{
		printf("Absent args: [dst ip] [dst port]\n");
		return 1;
	}
	
	bzero(&addr, sizeof(addr));
	ret=inet_aton(argv[1], &(addr.sin_addr));
	if(ret == 0)
	{
		printf("Error IP: %s\n", argv[1]);
		return 1;
	}
	
	dst_port=atoi(argv[2]);
	if(dst_port == 0)
	{
		printf("Error port: %s\n", argv[2]);
		return 1;
	}
	
	//创建套接字
	fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//初始化服务器地址，端口，协议
	addr.sin_family = AF_INET;
	addr.sin_port = htons(dst_port);

#if 0
    struct timeval timeo = {2, 0};
    socklen_t len = sizeof(timeo);

    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeo, len);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);

    getsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, &len);
    printf("timeout:%lu.%lu\n", timeo.tv_sec, timeo.tv_usec);
#endif
	/////////////////////////////////////////////////////////////
	//连接服务器
	ret = connect(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
    if(ret == -1)
    {
        perror("con:");
		return 1;
    }

#if 1	
    while(1)
    {
		//写入
		bzero(buf, sizeof(buf));
		strcpy(buf, "hi");
		write(fd, buf, strlen(buf)+1);
		printf("write:[%s]\n", buf);
#endif
#if 1    
		//读取
		bzero(buf, sizeof(buf));
		read(fd, buf, sizeof(buf));
		printf("read:[%s]\n", buf);
#endif

		sleep(5);
    }

	close(fd);
	
	return 0;
}
