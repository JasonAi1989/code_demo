#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define BUF_SIZ     1024

/*int main(int argc, char *argv[])*/
int local_send(char* interface, int protocol, unsigned char *dmac)
{
    int sockfd;
    struct ifreq if_idx;
    struct ifreq if_mac;
    int tx_len = 0;
    char sendbuf[BUF_SIZ];
    struct ether_header *eh = (struct ether_header *) sendbuf; /*structure*/
    struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
    struct sockaddr_ll socket_address;
    char ifName[IFNAMSIZ];

    strcpy(ifName, interface);

    /* Open RAW socket to send on *//*IPv4*/
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(protocol))) == -1) {
        perror("socket");
        exit(-1);
    }

    /* Get the index of the interface to send on *//*0*/
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, ifName, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)/*save INDEX info into if_idx*/
    {
        perror("SIOCGIFINDEX");
        exit(-1);
    }

    /* Get the MAC address of the interface to send on *//*local*//*save MAC info into if_mac*/
    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, ifName, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
    {
        perror("SIOCGIFHWADDR");
        exit(-1);
    }

    /* Construct the Ethernet header */
    memset(sendbuf, 0, BUF_SIZ);
    /* Ethernet header */
    eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
    eh->ether_dhost[0] = dmac[0];
    eh->ether_dhost[1] = dmac[1];
    eh->ether_dhost[2] = dmac[2];
    eh->ether_dhost[3] = dmac[3];
    eh->ether_dhost[4] = dmac[4];
    eh->ether_dhost[5] = dmac[5];

    /* Ethertype field */
    eh->ether_type = htons(protocol);
    tx_len += sizeof(struct ether_header);

    /* Packet data */
    sendbuf[tx_len++] = 'h';
    sendbuf[tx_len++] = 'e';
    sendbuf[tx_len++] = 'l';
    sendbuf[tx_len++] = 'l';
    sendbuf[tx_len++] = 'o';

    /* Index of the network device */
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    /* Address length*/
    socket_address.sll_halen = ETH_ALEN;
    /* Destination MAC */
    socket_address.sll_addr[0] = dmac[0];
    socket_address.sll_addr[1] = dmac[1];
    socket_address.sll_addr[2] = dmac[2];
    socket_address.sll_addr[3] = dmac[3];
    socket_address.sll_addr[4] = dmac[4];
    socket_address.sll_addr[5] = dmac[5];

    /* Send packet */
    int cnt=0;
    while(cnt<5){
        if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
            printf("Send failed\n");
        else
            printf("success!\n");

        cnt++;
    }

    return 0;
}
