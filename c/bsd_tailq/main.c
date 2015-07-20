#include <stdio.h>
#include <sys/queue.h>
#include <stdlib.h>

typedef struct _int_node
{
	int data;									//这是这个结构的主要数据
	TAILQ_ENTRY(_int_node) int_node_entry_p;   	//这个实体存放着两个指针，用于连接前后节点，在这里称他为节点中链表点
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
	TAILQ_INSERT_TAIL(&int_node_head_p, node_a, int_node_entry_p);  //(头指针，新节点，节点中链表点)
	TAILQ_INSERT_TAIL(&int_node_head_p, node_b, int_node_entry_p);
	
	//loop
	int_node_t* node_p;
	TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
	{
		printf("data:%d\n", node_p->data);
	}

#if 0  //单个删除
	//delete  
	TAILQ_REMOVE(&int_node_head_p, node_a, int_node_entry_p);
	free(node_a);  //TAILQ_REMOVE只是将节点从队列中剔除,必须要手动释放节点的内存
	node_a = NULL;
	
	//loop
	TAILQ_FOREACH(node_p, &int_node_head_p, int_node_entry_p)
	{
		printf("2 data:%d\n", node_p->data);
	}
#endif
	
#if 0   //Error   全部删除, 下面这段代码是有问题的，因为remove后整个队列已经变化，FOREACH便会出现问题
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
#if 1    //OK 全部删除
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