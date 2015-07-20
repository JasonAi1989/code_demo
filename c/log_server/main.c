#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/select.h>

short 	 int srv_port = 5514;
unsigned int check_disk_flag=1;
unsigned int curr_date=0;
unsigned int last_date=0;

#define DEF_DAYS  	0
#define DEF_TIME 	30  //minute
#define TIME_UNIT  	60  //second
#define LEN 		4096
#define ONE_DAY		86400 // 24*60*60

void handle_sig_child();
void handle_sig_check_disk();
void checking_process(int argc, char* argv[]);
int check_disk();
int analysis_command(char* buf);
int check_avail_days(unsigned int days);
void del_old_log(int days);
void add_day(unsigned int *which, unsigned int days);
void socket_process();
int get_fd(int old_fd);
int create_newlog(int date);

//logserver [days] [time]
//days:the logs are avail in the period of days
//time:the gap time of checking the disk
int main(int argc, char* argv[])
{
#if 0
	pid_t forkfd;
	
	signal(SIGCHLD,handle_sig_child);//捕捉SIGCHLD信号,并调取handle_sig_child()进行处理

	if((forkfd=fork()) < 0)
	{
		printf("fork error\n");
	}
	else if(forkfd == 0)  //child, to process the disk check and avail days judgement.
	{
		checking_process(argc, argv);
	}
	else  //father, to process the socket data receive and write the log.
	{
		socket_process();
	}
#endif
	unsigned int date = 20141030;
	for(int i=0; i<10; i++)
	{
		add_day(&date, 1);
		printf("date:%d\n", date);
	}
	
	return 0;
}

void handle_sig_child()//捕捉SIGCHLD信号后的处理fun
{
	int ret; 
	pid_t pid_c;
	pid_c=wait(&ret);//使进程睡眠，直到它的一个子进程退出时唤醒
	printf("Child proess PID = %d return %d.\n",pid_c,ret);
}
void handle_sig_check_disk()//捕捉SIGCHLD信号后的处理fun
{
	int ret; 
	pid_t pid_c;
	pid_c=wait(&ret);
	check_disk_flag = 0;   //使主进程中读取的循环推出
	printf("Child proess PID = %d return %d.\n",pid_c,ret);
}

//to process the disk check and avail days judgement
void checking_process(int argc, char* argv[])
{
	unsigned int days;
	unsigned int time; //the unit is second.
	int argnum;
	
	(argc>3) ? (argnum=3) : (argnum=argc);

	switch(argnum)
	{
	case 1:// no days, no time
		days = DEF_DAYS;
		time = DEF_TIME * TIME_UNIT;
		break;
	case 2://have days, no time
		days = atoi(argv[1]);
		time = DEF_TIME * TIME_UNIT;
		break;
	case 3://hvae days, have time
		days = atoi(argv[1]);
		time = atoi(argv[2]);
		break;
		
	default:
		return;
	}
	
	int over_days=0;
	while(1)
	{
		while(check_disk())
		{
			del_old_log(-1);
		}
		
		if((over_days=check_avail_days(days)) != 0)
		{
			del_old_log(over_days);
		}
		
		sleep(time);
	}
}

//return:0-the disk is fine; 
//		 1-the disk is full, need to delete the old logs
int check_disk()
{
    int pipefd[2];
	pid_t fd;
	int available=0;
	
	signal(SIGCHLD,handle_sig_check_disk);//捕捉SIGCHLD信号,并调取handle_sig_child()进行处理
	
	pipe(pipefd);

	if((fd=fork()) < 0)
	{
		printf("fork error\n");
		return 0;
	}
	else if(fd == 0)  //child
	{
		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		
		printf("test\n");
		execl("/bin/df", "df", "-hl", "/var", NULL);
		
		exit(0);
	}
	else   //father
	{
		char buf[LEN];
		int size;
		
		close(pipefd[1]);
		
		while(check_disk_flag)
		{
			bzero(buf, sizeof buf);
			size = read(pipefd[0], buf, sizeof buf);
			if(size == 0)
				continue;
				
			printf("%s\n", buf);
			available = analysis_command(buf);
		}
		
		if(available < 20)  //del the old log files
		{
			return 1;
		}
		else   //go on writing log
		{
			return 0;
		}
	}
}

//return the available capacity percent
int analysis_command(char* buf)
{
	char fs[LEN], mount[LEN];
	float a,b,c;
	int d;
	char e1,e2,e3;
	char* p=NULL;
	
	bzero(fs, LEN);
	bzero(mount, LEN);
	
	p = strstr(buf, "/dev/");
	if(p == NULL)
	{
		printf("can't find /dev/ in df command\n");
		return 0;
	}	
	sscanf(p,"%s %f%c %f%c %f%c %d%% %s\n", 
		fs, &a, &e1, &b, &e2, &c, &e3, &d, mount);
	printf("%s %0.1f%c %0.1f%c %0.1f%c %d %s\n", fs, a, e1, b, e2, c, e3, d, mount);

	return 100-d;
}

//return:0-the logs are avail
//		 1-over the days, need to delete the old logs
int check_avail_days(unsigned int days)
{
	if(last_date == 0 || days == 0 || curr_date == last_date)
		return 0;
	
	struct tm new_date,old_date;
	
	bzero(&new_date, sizeof(new_date));
	bzero(&old_date, sizeof(old_date));
	
	new_date.tm_mday = curr_date & 0x03;
	new_date.tm_mon  = curr_date>>2 & 0x03 - 1;
	new_date.tm_year = curr_date>>4 & 0x0f - 1900;
	
	old_date.tm_mday = last_date & 0x03;
	old_date.tm_mon  = last_date>>2 & 0x03 - 1;
	old_date.tm_year = last_date>>4 & 0x0f - 1900;
	
	time_t new_time, old_time;
	new_time = mktime(&new_date);
	old_time = mktime(&old_date);
	
	time_t over_time = new_time - old_time;
	int over_days = over_time / ONE_DAY;
	
	if(over_days > days)
		return over_days-days;
	else
		return 0;
}

void del_old_log(int days)
{
	char name[32];
	char command[64];
	
	if(days == -1)  //delete the last log
	{
		bzero(name, sizeof(name));
		bzero(command, sizeof(command));
		sprintf(name, "/var/log/%8d.log", last_date);
		sprintf(command, "rm -rf %s\n", name);
		system(command);
		add_day(&last_date, 1);
	}
	else if(days > 0)  //delete the old logs
	{
		for(int i=0; i<days; i++)
		{
			bzero(name, sizeof(name));
			bzero(command, sizeof(command));
			sprintf(name, "/var/log/%8d.log", last_date);
			sprintf(command, "rm -rf %s\n", name);
			system(command);
			add_day(&last_date, 1);
		}
	}

	return;
}

void add_day(unsigned int *which, unsigned int days)
{
	struct tm new_date;
	char buf1[16],buf2[16];
	char* buf_p;
	
	bzero(&new_date, sizeof(new_date));
	bzero(buf1, sizeof(buf1));
	bzero(buf2, sizeof(buf2));
	
	sprintf(buf1, "%u", *which);
	
	buf_p = buf1;
	strncpy(buf2,buf_p, 4);
	buf_p+=4;
	new_date.tm_year = atoi(buf2) - 1900;
	
	bzero(buf2, sizeof(buf2));
	strncpy(buf2, buf_p, 2);
	buf_p+=2;
	new_date.tm_mon  = atoi(buf2) - 1;
	
	bzero(buf2, sizeof(buf2));
	strncpy(buf2, buf_p, 2);
	new_date.tm_mday = atoi(buf2) + days;
	
	time_t new_time;
	new_time = mktime(&new_date);
	
	struct tm *p = localtime(&new_time);
	
	bzero(&new_date, sizeof(new_date));
	memcpy(&new_date, p, sizeof(new_date));
	
	char time_buf[16];
	bzero(time_buf, sizeof(time_buf));
	sprintf (time_buf, "%04d%02d%02d", (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday);
	*which = atoi(time_buf);
}

//to process the socket data receive and write the log
void socket_process()
{
	int sockfd;
	int bind_flag;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		printf("Error 01: sockfd ");
		exit(-1);
	}

	unsigned long mode=1;
	int ret	= ioctl(sockfd, FIONBIO, &mode);  
	if(ret == -1)  
	{  
		printf("Error 02: ioctlsocket");
		close(sockfd);
		exit(-1);
	}  
	
	struct sockaddr_in	server,their;
	server.sin_family = AF_INET;
	server.sin_port	= htons(srv_port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(server.sin_zero, '\0', 8);

	bind_flag=bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr));

	//printf("bind ip:%s\tport:%i\n",inet_ntoa(server.sin_addr.s_addr), srv_port);

	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	
	char buf[LEN];
	bzero(buf, LEN);
	int resize;
	int the_len = sizeof(struct sockaddr);
	int fd=-1;
	
	while(1)
	{
		if(select(FD_SETSIZE, &rset, NULL, NULL, NULL) == -1)
		{
			perror("select:");
			exit(-1);
		}
		
		if(FD_ISSET(sockfd, &rset))
		{
			resize = recvfrom(sockfd, buf, sizeof(buf)-1, 0,
						(struct sockaddr *)&their, &the_len);
			memset(buf+resize,'\n',1);
			
			fd = get_fd(fd);
			if(fd == -1)
			{
				printf("Error 03: get_fd");
				close(sockfd);
				exit(-1);
			}
			
			if(resize > 0)
			{
				write(fd, buf, resize+1);
			}
		}
	}
}

int get_fd(int old_fd)
{
	if(old_fd == -1 || curr_date == 0)
	{
		old_fd = -1;
		curr_date = 0;
	}
	
	time_t timep;
	struct tm *p;
	char time_buf[16];
	
	bzero(time_buf, sizeof(time_buf));
	
	time(&timep);
	p=localtime(&timep);
	
	sprintf (time_buf, "%4d%2d%2d", (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday);
	printf("date string:%s\n", time_buf);
	
	int date;
	date = atoi(time_buf);
	printf("date int:%d\n", date);
	
	int new_fd=-1;
	if(curr_date == date)
	{
		new_fd = old_fd;
	}
	else
	{
		curr_date = date;
		new_fd = create_newlog(date);
		
		if(old_fd > 0)
			close(old_fd);
	}
	
	if(last_date == 0)
	{
		last_date = curr_date;
	}
	
	return new_fd;
}

int create_newlog(int date)
{
	if(date <= 0)
		return -1;
		
	char name[32];
	bzero(name, sizeof(name));
	
	sprintf(name, "/var/log/%8d.log", date);
	printf("log name:%s\n", name);
	
	int fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(!fd)
	{
		printf("Error : open\n");
		return -1;
	}
	
	return fd;
}