#define _BSD_SOURCE

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
#include <strings.h>
#include <signal.h>
#include <pthread.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/time.h>

#define LISTEN_NUM	10
#define ERROR_NUM	10
#define PTHREAD_NUM	LISTEN_NUM

int listen_num = 0;

typedef struct _ppool_data
{
	pthread_t ppid;
	int enable;
	int using_fd;
}ppool_data;

//具体用于读取和写入数据的函数
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
		
		//客户端发送空信息会使此次读取写入操作结束
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

ppool_data ppool[PTHREAD_NUM];

//线程池中每个线程的执行函数
void* pthread_do_detail(void *arg)
{
	ppool_data* data = (ppool_data*) arg;
	
	while(1)
	{
		if(data->enable == 1)
		{
			usleep(100);
			continue;
		}
		else if(data->using_fd == -1)
		{
			printf("using_fd error\n");
			data->enable = 1;
		}
		else
		{
			//读取和写入数据
			do_detail(data->using_fd);
			
			//读取和写入数据结束后，要将条件复原
			data->enable = 1;
			data->using_fd = -1;
			listen_num--;
			
			printf("clear pthread, listened: [%d]\n", listen_num);
		}
	}
	
	return NULL;
}

//初始化线程池
void pthread_pool_init()
{
	bzero(ppool, PTHREAD_NUM);
	int err;

	for(int i=0; i<PTHREAD_NUM; i++)
	{
		ppool[i].enable = 1;
		ppool[i].using_fd = -1;
		err = pthread_create(&ppool[i].ppid, NULL, pthread_do_detail, (void*)&ppool[i]);
		if(err != 0)
		{
			printf("pthread_create error: [%d]\n", i);
			exit(0);
		}
	}
}

//在线程池中遍历找到可用的线程，然后将fd赋值给这个线程，然后将这个线程占用
void pthread_ppool_execl(int fd)
{
	int i=0;
	for(i=0; i<PTHREAD_NUM; i++)
	{
		if(ppool[i].enable == 1)
		{
			listen_num++;
			ppool[i].using_fd = fd;
			ppool[i].enable = 0;
			printf("using pthread [%d], listened: [%d]\n", i, listen_num);
			break;
		}
	}
	
	//线程池已经满
	if(i == PTHREAD_NUM)
	{
		printf("pthread pool is full, listened: [%d]!\n", listen_num);
		return;
	}
}

int main(int argc, char* argv[])
{
	int fd, temp_fd;
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

	pthread_pool_init();

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
	fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//初始化服务器地址，端口，协议
	bzero(addr, sizeof(addr));
	
	addr[0].sin_family = AF_INET;
	addr[0].sin_port = htons(local_port);
	
	//绑定服务器地址
	ret = bind(fd, (struct sockaddr*)&addr[0], sizeof(struct sockaddr));
	if(ret == -1)
	{
        perror("bind:");
		return 1;
	}

	//对服务器绑定的端口进行监听
	ret = listen(fd, LISTEN_NUM);
	if(ret == -1)
	{
        perror("listen:");
		return 1;
	}
	
	//开始等待客户端的连接,会提供进行服务所需的句柄
	while(error_num)
	{
		if(listen_num == LISTEN_NUM)
		{
			usleep(100);
			continue;
		}
		
		len = sizeof(struct sockaddr);
		temp_fd = accept(fd, (struct sockaddr *)&addr[1], &len);	
		if(temp_fd == -1)
		{
			perror("accept:");
			error_num--;
			usleep(100);
			continue;
		}
			
		//将套接字放到线程池中去执行进一步的读取和写入操作
		pthread_ppool_execl(temp_fd);
	}
	
	//结束
	close(fd);
	
	return 0;
}
