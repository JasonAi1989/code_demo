#include <stdio.h>
#include <sys/queue.h>
#include <stdlib.h>

typedef struct _int_node
{
	int data;									//��������ṹ����Ҫ����
	TAILQ_ENTRY(_int_node) int_node_entry_p;   	//���ʵ����������ָ�룬��������ǰ��ڵ㣬���������Ϊ�ڵ��������
}int_node_t;

int main()
{
	//create and init the list head
	TAILQ_HEAD(int_node_head, _int_node) int_node_head_p;
	TAILQ_INIT(&int_node_head_p);
	
	//init the new member
	int_node_t* node_a = malloc(sizeof(int_node_t));
	int_node_t* node_b = malloc(sizeof(int_node_t));
	node_a->data = 10;
	node_b->data = 18;
	
	//insert
	TAILQ_INSERT_TAIL(&int_node_head_p, node_a, int_node_entry_p);  //(ͷָ�룬�½ڵ㣬�ڵ��������)
	TAILQ_INSERT_TAIL(&int_node_head_p, node_b, int_node_entry_p);
	
	//loop
	int_node_t* node_p;
	TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
	{
		printf("data:%d\n", node_p->data);
	}

#if 0  //����ɾ��
	//delete  
	TAILQ_REMOVE(&int_node_head_p, node_a, int_node_entry_p);
	free(node_a);  //TAILQ_REMOVEֻ�ǽ��ڵ�Ӷ������޳�,����Ҫ�ֶ��ͷŽڵ���ڴ�
	node_a = NULL;
	
	//loop
	TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
	{
		printf("2 data:%d\n", node_p->data);
	}
#endif
	
#if 0   //Error   ȫ��ɾ��, ������δ�����������ģ���Ϊremove�����������Ѿ��仯��FOREACH����������
	TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
	{
		TAILQ_REMOVE(&int_node_head_p, node_p, int_node_entry_p);
		free(node_p);  
		node_p = NULL;
	}
	
	if(TAILQ_EMPTY(&int_node_head_p))
	{
		printf("queue clear\n");
	}
#endif
#if 1    //OK ȫ��ɾ��
	int_node_t* node_next_p;
	node_p = TAILQ_FIRST(&int_node_head_p);
	while(node_p)
	{
		node_next_p = TAILQ_NEXT(node_p, int_node_entry_p);
		TAILQ_REMOVE(&int_node_head_p, node_p, int_node_entry_p);
		free(node_p);  
		node_p = node_next_p;
	}

	if(TAILQ_EMPTY(&int_node_head_p))
	{
		printf("queue clear\n");
	}
	else
	{
		TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
		{
			printf("2 data:%d\n", node_p->data);
		}
	}
#endif 

	return 0;
}