#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <net/if.h>

#define INTERFACE_NAME "enp0s3"

int parse_packet(unsigned char *buf_p, int data_size);

int main(int argc,char *argv[])
{
	int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL) );
	if(sock_raw_fd < 0){
		perror("socket");
		return -1;
	}

    struct ifreq req;
    strncpy(req.ifr_name, INTERFACE_NAME, IFNAMSIZ);
    if(-1 == ioctl(sock_raw_fd, SIOCGIFFLAGS, &req))
    {
        perror("ioctl");
        close(sock_raw_fd);
        exit(-1);
    }

    req.ifr_flags |= IFF_PROMISC;
    if(-1 == ioctl(sock_raw_fd, SIOCSIFFLAGS, &req))
    {
        perror("ioctl");
        close(sock_raw_fd);
        exit(-1);
    }

    if(setsockopt(sock_raw_fd, SOL_SOCKET, SO_BINDTODEVICE, INTERFACE_NAME, strlen(INTERFACE_NAME)+1) == -1){
        perror("setsockopt");
        close(sock_raw_fd);
        exit(-1);
    }

    /* Allow the socket to be reused - incase connection is closed prematurely */
    int sockopt;
    if (setsockopt(sock_raw_fd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(sock_raw_fd);
        exit(-1);
    }

    struct sockaddr_in saddr;
    int saddr_size, data_size;
    while(1)
    {
        saddr_size = sizeof (struct sockaddr);
        unsigned char buf[65536] = {0};
        //we can't receive the src addr info here, since this is raw packet, the kernel may provide
        //the wrong info for src addr. The best way is to analyze the whole received msg by userself
        data_size = recvfrom(sock_raw_fd, buf, sizeof(buf), 0, NULL, NULL);
        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        else{
            printf("Received %d bytes\n", data_size);

        //Huge code to process the packet
        parse_packet(buf, data_size);

        //Send it out through "eth1" here

        }
    }

    close(sock_raw_fd);
    return 0;
}

int parse_packet(unsigned char *buf_p, int data_size)
{
    static int counter=1;

    struct ether_header *eh = (struct ether_header *) buf_p;

    printf("dmac:%x:%x:%x:%x:%x:%x\n", eh->ether_dhost[0], eh->ether_dhost[1],
            eh->ether_dhost[2],eh->ether_dhost[3],eh->ether_dhost[4],eh->ether_dhost[5]);
    printf("smac:%x:%x:%x:%x:%x:%x\n", eh->ether_shost[0], eh->ether_shost[1],
            eh->ether_shost[2],eh->ether_shost[3],eh->ether_shost[4],eh->ether_shost[5]);
    printf("etype:%x\n", eh->ether_type);

    printf("counter:%d\n", counter);

    if(counter == 10)
        return 1;

    char filename[10];
    memset(filename, 0, 10);
    sprintf(filename, "%d.txt", counter);

    int fd=open(filename, O_WRONLY|O_CREAT);
    int write_size=write(fd, buf_p, data_size);
    printf("write size:%d\n", write_size);
    close(fd);

    counter++;
    return 0;
}
