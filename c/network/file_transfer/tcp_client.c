#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>  

#define SIZE_STR 1024
#define portnumber 3333

int download(char *buffer,int sockfd);
int connect_m(int num,int way);
int updates(char *buffer,int sockfd);
int analysis(void);
void empty_cache(void);
int find(const char *str,FILE *fp);
int find_more(FILE *fp,int num);
int count_ip(char *str_ip,int way);
int auto_updates(void);

int main(int argc, char *argv[]) 
{
    int num;
    
    while(1)
    {
        printf("Please input your chose:\n");
        printf("1.Download the file from server.\n");
        printf("2.File updates(manual).\n");
	printf("3.File updates(automatic)---'q' is over.\n");
        printf("4.File analysis\n");
        printf("5.exit\n");

        scanf("%d",&num);

	empty_cache();
#if 0
	if(2==num)
	{
		printf("1.Manual update\n");	//手动更新
		printf("2.Automatic Updates\n");	//自动更新
		scanf("%d",)
	}

#endif
        switch(num)
        {
            case 1:connect_m(num,0);
                    break;
            case 2:connect_m(num,0);
                    break;
	    case 3:auto_updates();    	//way=1 为自动更新模式
		    break;
            case 4:if(analysis() == -1)
                        return 0;
                    break;
            case 5:return 0;
            default:printf("input error\n");
                    break;
        }
    }
}   

int connect_m(int num,int way)
{
	int sockfd; 
	char buffer[SIZE_STR]; 
	struct sockaddr_in server_addr; 
	struct hostent *host; 
    char argv1[1024];    
    int up;

	count_ip(argv1,way);
    host=gethostbyname(argv1);
#if 0
    printf("please input the server's IP\n");
    scanf("%s",argv1);

    empty_cache();

    if ((host=gethostbyname(argv1)) == NULL)
        {
            printf("Gethostname error\n");
            return -1;
        }
#endif

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{ 
		printf("Socket Error\n"); 
		return 0; 
	} 

	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family=AF_INET;        
	server_addr.sin_port=htons(portnumber);  	
    server_addr.sin_addr=*((struct in_addr *)host->h_addr);
	
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		printf("Connect Error\n"); 
		return 0; 
	} 
   switch (num)
	{            //num=1,download
        case 1:strcpy(buffer ,"1");
			   send(sockfd,buffer,strlen(buffer),0);
			   download(buffer,sockfd);
               printf("&&&Download Success&&&\n\n");
               break;
        case 2:strcpy(buffer,"2");				//updates
			   send(sockfd,buffer,strlen(buffer),0);	           	  
               up = updates(buffer,sockfd);
             	switch(up)
             	{
                case -1:close(sockfd);  
                        return 0;
                case 0:printf("&&&Is already the newest version, no update&&&\n\n");
                        break;

                case 1:download(buffer,sockfd);
                        printf("&&&Has been updated&&&\n\n");
                       break;
             	}
    }
	close(sockfd); 
	return 0; 
} 


int download(char *buffer,int sockfd)
{
    FILE *fp = fopen("client.txt","w+");
    int clen ;
    int count=0;

    while (1)
    {
        clen = recv(sockfd,buffer,strlen(buffer),0);
        if(clen<0)
        {
            printf("recv is error\n");
            return -1;
        }
        if(0==clen)
        {
            printf("\nrecrive bytes [%d]\n",count);
            fclose(fp);
		    return sockfd; 
        }

        buffer[clen] = '\0';
        fputs(buffer,fp);
        count = count+clen;
    }
}

int updates(char *buffer,int sockfd)
{
    char buffer1[SIZE_STR];
    int ch;

    FILE *fp = fopen("client.txt","r");
    if(fp ==NULL)
    {    printf("&&&No local file,please download!!&&&\n\n");
         return -1;  
    }
    
    recv(sockfd,buffer,SIZE_STR,0);
    while(!feof(fp))
    {
        if(fgets(buffer1,SIZE_STR,fp)==NULL)
            break;
        if(strstr(buffer1,"Version") !=NULL)
            break;
    }
    fclose(fp);
    ch = strncmp(buffer,buffer1,strlen(buffer));

    switch(ch)
    {
        case 0:
        case -1:strcpy(buffer,"0");
                break;
        case 1:strcpy(buffer,"1");
                break;
    }
    send(sockfd,buffer,strlen(buffer),0);       //0-keep,1-update

    if (1==ch)
        return 1;
    return 0;

}


int analysis(void)
{
    int num;
    FILE *fp = NULL;
    
    while(1)
    {
        if((fp = fopen("client.txt","r+")) ==NULL)
        {   
            printf("No local file,please download!!\n");
            return 0;
        }
        printf("please input find ways:\n");
        printf("1.Name\n");
        printf("2.Director\n");
        printf("3.Year\n");
        printf("4.search the move by name in all\n");
        printf("5.search the move by director in all\n");
        printf("6.search the move by year in all\n");
        printf("7.Back to previous level\n");
        printf("8.EXIT\n");

        scanf("%d",&num);

        empty_cache();

        switch(num)
        {
            case 1:find("Name",fp);
                    fclose(fp);
                    break;
            case 2:find("Director",fp);
                    fclose(fp);
                    break;
            case 3:find("Year",fp);
                    fclose(fp);
                    break;
            case 4:printf("please input the name:\n");
                    find_more(fp,num);
                    break;
            case 5:printf("please input the director:\n");
                    find_more(fp,num);
                    break;
            case 6:printf("please input the year:\n");
                    find_more(fp,num);
                    break;

            case 7:fclose(fp);
                    return 0;
            case 8:fclose(fp);
                    return -1;
            default: printf("error\n");
                    fclose(fp);
                    break;
        
        }
    }
}

int find(const char *str,FILE *fp)		//
{
    char buffer[SIZE_STR];
    char *p;

    while(!feof(fp))
    {
        if(fgets(buffer,SIZE_STR,fp) == NULL)
            return 0;

        if((p = strstr(buffer,str)) == NULL)
            continue;
        
        printf("%s\n",p);
    }

return 0;
}

int find_more(FILE *fp,int num)   		//复杂解析
{
    char buffer[SIZE_STR];
    int flag =0;
    int count = 0;
    int st = 0;
    char str[SIZE_STR];
    
    struct {
        char name[SIZE_STR];
        char director[SIZE_STR];
        char year[SIZE_STR];
    }black;

    scanf("%s",str);

    empty_cache();

    while(!feof(fp))
    {
        if(fgets(buffer,SIZE_STR,fp) ==NULL)
            break;
        if(strstr(buffer,"Name") != NULL)
            strncpy(black.name,buffer,strlen(buffer)+1);
        else if(strstr(buffer,"Director") != NULL)
            strncpy(black.director,buffer,strlen(buffer)+1);
        else if(strstr(buffer,"Year") != NULL)
        {
            strncpy(black.year,buffer,strlen(buffer)+1);
            st = 1;
        }
        else 
            continue;

        if(!st)   //If you do not keep a full structure will not continue!!
            continue;

        switch(num)             //If there is a match,flag=1
        {
            case 4:if(strstr(black.name,str) == NULL)
                        break;
                   else
                        flag = 1;
                        break;
            case 5:if(strstr(black.director,str) == NULL)
                        break;
                   else
                        flag = 1;
                        break;
            case 6:if(strstr(black.year,str) == NULL)
                        break;
                   else
                        flag = 1;
                        break;
        }
        if(flag)
        {
            printf("%s\n",black.name);
            printf("%s\n",black.director);
            printf("%s\n",black.year);

            flag = 0;
            count ++;
        }

        st = 0;         //it is important!!
    }

    if(0==count)
        printf("can't find the movie\n");

    return 0;
}

#if 1 
int count_ip(char *str_ip,int way)
{
    char argv1[SIZE_STR];
    static char argv2[SIZE_STR]={};
    static int count = 0;
    char ch;

    if(0 == count)
    {
        printf("please input the server's IP:\n");
        scanf("%s",argv1);
        empty_cache();

        if (gethostbyname(argv1) == NULL)
        {
            printf("Gethostname error\n");
            return -1;
        }

        strcpy(argv2,argv1);
        strcpy(str_ip,argv1);
        count ++;
        return 0;
    }


    while(0!=count&&0==way)
    {
        printf("Is called the old IP:[%s]\n",argv2);
        printf("Y or N\n");
        
        ch = getchar();
        if (ch == 'Y'||ch=='y')
        {
             strcpy(str_ip,argv2);
             printf("Old save is useing!!\n");
             break;
        }
        if(ch=='N'||ch=='n')
        {
             printf("please input the server's IP:\n");
             scanf("%s",argv1);
             empty_cache();
        }
        if (gethostbyname(argv1) == NULL)
        {
             printf("Gethostname error\n");
             return -1;
        }   

        strcpy(argv2,argv1);
        strcpy(str_ip,argv1);
        break;   
    }
    
    while(0!=count&&1==way)
    {
	strcpy(str_ip,argv2);
	break;
    }

    return 0;
}
#endif

void empty_cache(void)
{
    char ch;
    while((ch=getchar()) != '\n');
}


int auto_updates(void)
{
    long int count =1;
    while(1)
    {
	connect_m(2,1);
	printf("%ldth update\n",count);
	printf("'q' is over!!\n");
	sleep(5);
	count ++;
//	if(getchar()=='q')
//	     break;
    }
    return 0;
} 

