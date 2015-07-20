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

	printf("IP: %s\n", IPc);
	printf("IP: %u\n", IPi);
}
