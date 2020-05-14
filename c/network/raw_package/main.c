#include <sys/socket.h>
#include <netinet/ether.h>
#include <stdio.h>  // perror

int main(int argc,char *argv[])
{
	int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL) );
	if(sock_raw_fd < 0){
		perror("socket");
		return -1;
	}
/*
 *    struct ifreq req;
 *    strncpy(req.ifr_name, "team0.1024", IFNAMSIZ);
 *    if(-1 == ioctl(sock_raw_fd, SIOCGIFINDEX, &req))
 *    {
 *        perror("ioctl");
 *        close(sock_raw_fd);
 *        exit(-1);
 *    }
 *
 *    req.ifr_flags |= IFF_PROMISC;
 *    if(-1 == ioctl(sock_raw_fd, SIOCSIFINDEX, &req))
 *    {
 *        perror("ioctl");
 *        close(sock_raw_fd);
 *        exit(-1);
 *    }
 */

	unsigned char buf[1024] = {0};
	int len = recvfrom(sock_raw_fd, buf, sizeof(buf), 0, NULL, NULL);
	printf("len = %d\n", len);
	return 0;
}
