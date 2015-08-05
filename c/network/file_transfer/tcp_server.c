#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

#define SIZE_STR 1024
#define portnumber 3333

int fgets_m(char *buffer,int new_fd);
int chose(int new_fd,char *buffer);
int cheak(char *buffer,int new_fd);


int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd,ch; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	char buffer[SIZE_STR];
    	

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	bzero(&server_addr,sizeof(struct sockaddr_in)); 
	server_addr.sin_family=AF_INET;                 
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
    server_addr.sin_port=htons(portnumber);        
    if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 


	while(1) 
	{ 
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),(unsigned int*)&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		} 
		printf("Server get connection from %s\n",(char *)inet_ntoa(client_addr.sin_addr)); 		

        switch (chose(new_fd,buffer))
       		 {
            case 2:ch = cheak(buffer,new_fd);		//检查更新
                    break;
            case 1:fgets_m(buffer,new_fd);			//下载
                    break;
    
        	}   

        if(1==ch)
            fgets_m(buffer,new_fd);
			
		close(new_fd); 
	} 

	close(sockfd); 
	exit(0); 
} 


int fgets_m(char *buffer,int new_fd)  		//下载文件
{
    int count = 0;
    FILE *fp=fopen("movielist.txt","r");
    int ssend=0;

    while(!feof(fp))
    {
        if((fgets(buffer,SIZE_STR,fp)) == NULL)
            break;
        
        printf("%s\n",buffer);
        ssend=send(new_fd,buffer,strlen(buffer),0);
        if(ssend<0||ssend==0)
        {
            printf("send() failer\n");
            break;
        }
        else
            count=count + ssend;

        
    }
    printf("send byte:[%d]\n",count);
    fclose(fp);
    return 0;
}


int chose(int new_fd,char *buffer)
{
    int num;
    recv(new_fd,buffer,SIZE_STR,0);
    num = atoi(buffer);
    return num;

}

int cheak(char *buffer,int new_fd)
{
    int num;
    FILE *fp=fopen("movielist.txt","r");
    while(!feof(fp))
    {
        if(fgets(buffer,SIZE_STR,fp) == NULL)
            break;
        if(strstr(buffer,"Version") != NULL)
        {
            send(new_fd,buffer,strlen(buffer),0);
            break;
        }
    }
    fclose(fp);
    recv(new_fd,buffer,SIZE_STR,0);
    num = atoi(buffer);
    switch(num)
    {
        case 0:return 0;
        case 1:return 1;
    }
    return 0;
}
