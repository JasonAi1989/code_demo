#include <stdio.h>
#include <string.h>
#include "base64.h"

int main(int argc, const char *argv[])
{
	char *buf = "aGVsbG8gd29ybGQ=";
	char BASE64[30];
	int len;
	
	base64_decode(buf, BASE64, strlen(buf), &len);
	
	printf("orignal buf:%s\n", buf);
	printf("decoded message length:%d\n", len);
	printf("decoded message by base64:%s\n", BASE64);
	
	return 0;
}
