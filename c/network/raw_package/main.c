#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

extern int local_recv(char* interface, int protocol);
extern int local_send(char* interface, int protocol, unsigned char *dmac);

void usage()
{
    printf("raw_package -r|s -i <interface name> -p <protocol number> -h <dmac high> -l <dmac low>\n");
}
int main(int argc, char const* argv[])
{
    int c;
    int recv_flag=0;
    int send_flag=0;
    int protocol=0;
    char *interface=NULL;
    unsigned int dmac_h;
    unsigned short dmac_l;

    while((c=getopt(argc, argv, "rsi:p:d:h:l:")) != -1){
        switch(c){
            case 'r':
                recv_flag=1;
                break;
            case 's':
                send_flag=1;
                break;
            case 'i':
                interface=optarg;
            case 'p':
                protocol=atoi(optarg);
                break;
            case 'h':
                dmac_h=ntohl(atoi(optarg));
                break;
            case 'l':
                dmac_l=ntohs(atoi(optarg));
                break;
            default:
                break;
        }
    }

    printf("interface:%s, protocol:%d, dmac_h:%x, dmac_l:%x\n",
            interface, protocol, dmac_h, dmac_l);

    if(recv_flag==1 && send_flag==0){
        if(!interface || !protocol)
            usage();
        else
        {
            local_recv(interface, protocol);
        }
    } else if(recv_flag==0 && send_flag==1){
        if(!interface || !protocol)
            usage();
        else
        {
            unsigned char local_dmac[6];
            memcpy(local_dmac, &dmac_h, 4);
            memcpy(local_dmac+4, &dmac_l, 2);
            printf("%02x:%02x:%02x:%02x:%02x:%02x\n", local_dmac[0], local_dmac[1],local_dmac[2],local_dmac[3],local_dmac[4],local_dmac[5]);
            local_send(interface, protocol, local_dmac);
        }
    } else {
        usage();
    }
    return 0;
}
