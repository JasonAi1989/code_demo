/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/30/2014 02:51:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("arg num should be 2\n");
		return 0;
	}

	char* hostname = argv[1];
	struct hostent *host = gethostbyname(hostname);
	if(host == NULL)
	{
		printf("host is NULL\n");
		return 0;
	}

	char* ip = inet_ntoa(*((struct in_addr*)host->h_addr_list[0]));
	printf("ip is %s\n", ip);
	printf("ip is [%d]", *((struct in_addr*)host->h_addr_list[0]));
}
