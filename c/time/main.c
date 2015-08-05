#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int main()
{
	struct timezone tz;
	struct timeval  tv;
	
//	gettimeofday(&tv, &tz);
    tv.tv_sec = 1438679608;
	char* tp = ctime(&(tv.tv_sec));
	
	printf("time A: [%s]\n", tp);
	
	///////
	
	time_t		now;
	struct tm	*tm;
	char		buf[100], *format = "%a %b %d %T %Z (%z) %Y";
	
	time(&now);
	tm = localtime(&now);
	strftime(buf, 100, format, tm);
	
	printf("time B: [%s]\n", buf);
	
	return 0;
}
