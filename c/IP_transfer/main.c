/*
 * =====================================================================================
 *
 *       Filename:  IPc2i.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/15/2014 02:11:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void printf_bin(unsigned int val)
{
    int count=32;

    printf("bin IP:");
    while(count--)
    {
        if(val>>count & 0x1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}
int main()
{
	printf("please choose the transfer direction:\n1:char to int\n2:int to char\nplease input the number:");
	int num;
	scanf("%d", &num);

	char IPc[20];
	unsigned int IPi=0;

	bzero(IPc, sizeof IPc);
	
	if(num == 1)
	{
		printf("transfer the char to int IP\nplease input the string IP:");
		scanf("%s", IPc);
		IPi = inet_addr(IPc);
	}
	else if(num ==2)
	{
		printf("transfer the int to char IP\nplease input the int IP:");
		scanf("%u", &IPi);

		printf("test: %u\n",IPi);

		struct in_addr addr;
		addr.s_addr = IPi;
		
		char* ipstr = inet_ntoa(addr);
		strcpy(IPc, ipstr);
	}

    printf("Host byte order:\n");
	printf("str IP: %s\n", IPc);
	printf("int IP: %u\n", IPi);
	printf("hex IP: %x\n", IPi);
    printf_bin(IPi);

    printf("Network byte order:\n");
    unsigned int n_IPi = htonl(IPi); 
    char n_IPc[20];
    bzero(n_IPc, sizeof n_IPc);
	struct in_addr addr;
	addr.s_addr = n_IPi;
		
	char* ipstr = inet_ntoa(addr);
	strcpy(n_IPc, ipstr);

	printf("str IP: %s\n", n_IPc);
	printf("int IP: %u\n", n_IPi);
	printf("hex IP: %x\n", n_IPi);
    printf_bin(n_IPi);
}
