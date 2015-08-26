#include <stdio.h>
#include <string.h>
#include "sha1.h"

int main(int argc, const char *argv[])
{
	char* p = "abc";
	unsigned char buf[20];

	sha1_digest(buf, p);	

	printf("oring string:%s\n", p);
	int i;

	printf("md by SHA1:");
	for(i=0; i<20; i++)
	{
		printf("%.2x ", buf[i]);	
	}
	printf("\n");
	return 0;
}
