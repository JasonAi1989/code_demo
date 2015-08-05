#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <net/if.h>
#include <net/if_arp.h>
#include "access_rules.h"
 
#define MAXINTERFACES 64    /* ���ӿ��� */

void add_ac_rule(struct ac_rule_list** head, struct ac_rule* data)
{
	if(head == NULL || data == NULL)
		return;
		
	struct ac_rule_list* new_rule = malloc(sizeof(struct ac_rule_list));
	new_rule->next = *head;
	new_rule->prev = NULL;
	if(*head != NULL)
		(*head)->prev = new_rule;
	new_rule->rule = malloc(sizeof(struct ac_rule));
	memcpy(new_rule->rule, data, sizeof(struct ac_rule));
	*head = new_rule;
}

void del_ac_rule(struct ac_rule_list** head, unsigned int index)
{
	if(*head == NULL || index == 0)
		return;
	
	unsigned int count;
	struct ac_rule_list* p = *head;
	for(count=1; p != NULL; count++,p = p->next)
	{
		if(index == count)
		{
			if(p->rule)
				free(p->rule);
				
			if(p->next == NULL)	//The last node
			{
				p->prev->next = NULL;
				free(p);

				return;
			}
			else if(p->prev == NULL) //The first node
			{
				p->next->prev = NULL;
				*head = p->next;
				free(p);

				return;
			}
			else
			{
				p->next->prev = p->prev;
				p->prev->next = p->next;
				
				return;
			}
		}
	}
}

void destroy_rule_list(struct ac_rule_list** head)
{
	struct ac_rule_list* p = *head;
	struct ac_rule_list* tmp;
	
	while(p)
	{
		if(p->rule)
			free(p->rule);
		tmp = p;
		p = p->next;
		free(tmp);
	}
}

int get_local_rules(struct ac_rule_list** head)
{
	int fd;         /* �׽��� */
	int if_len;     /* �ӿ����� */
	struct ifreq buf[MAXINTERFACES];    /* ifreq�ṹ���� */
	struct ifconf ifc;                  /* ifconf�ṹ */

    /* ����IPv4��UDP�׽���fd */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket(AF_INET, SOCK_DGRAM, 0)");
        return -1;
    }
 
    /* ��ʼ��ifconf�ṹ */
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t) buf;
 
    /* ��ýӿ��б� */
    if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1)
    {
        perror("SIOCGIFCONF ioctl");
        return -1;
    }
 
    if_len = ifc.ifc_len / sizeof(struct ifreq); /* �ӿ����� */
	
    while (if_len-- > 0) /* ����ÿ���ӿ� */
    {
		struct ac_rule rule;
		bzero(&rule, sizeof(rule));
		rule.enable = 1;
		
		//��Ч�Ľӿ���
		if(buf[if_len].ifr_name[0] == 0x0)
		{
			continue;
		}
		
        /* ��ýӿڱ�־ */
        if (!(ioctl(fd, SIOCGIFFLAGS, (char *) &buf[if_len])))
        {
            /* �ӿ�״̬ */
            if (! (buf[if_len].ifr_flags & IFF_UP) )
            {
                continue;
            }
        }
        else
        {
			continue;
        }

		/* IP��ַ */
        if (!(ioctl(fd, SIOCGIFADDR, (char *) &buf[if_len])))
        {
			int addr = ((struct sockaddr_in*)&(buf[if_len].ifr_addr))->sin_addr.s_addr;
			if(addr == 0 || addr == 16777343)  //"0.0.0.0" or "127.0.0.1"
				continue;
				
			rule.dst_addr = addr;
        }
        else
        {
			continue;
        }
#if 0
		printf("interface name:%s\n", buf[if_len].ifr_name); /* �ӿ����� */
        printf("IP address:%s\n", rule.dst_addr);
		printf("\n\n");
#endif	
		
		add_ac_rule(head, &rule);
    }//�Cwhile end
 
    //�ر�socket
    close(fd);
    return 0;
}

#if 1
void print_rule_list(struct ac_rule_list* head)
{
	if(head == NULL)
		return;
		
	struct ac_rule_list* p = head;
	
	while(p)
	{
		if(p->rule)
		{
			printf("enable: %d\n",   p->rule->enable);
			printf("dst addr: %d\n", p->rule->dst_addr);
			printf("src addr: %d\n", p->rule->src_addr);
			printf("dst port: %d\n", p->rule->dst_port);
			printf("src port: %d\n", p->rule->src_port);
		}
		
		p = p->next;		
	}
}
int main()
{
	struct ac_rule_list* rule_list_head=NULL;
	
	if(get_local_rules(&rule_list_head))
	{
		printf("get local rules error!\n");
	}
	else
	{
		print_rule_list(rule_list_head);
	}

	return 1;
}
#endif
