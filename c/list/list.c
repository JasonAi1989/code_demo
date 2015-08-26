#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

//创建一个链表结点
struct _tagLIST * list_create()
{
	struct _tagLIST *pnode;

	pnode = malloc(sizeof(struct _tagLIST));
	bzero(pnode, sizeof(struct _tagLIST));

	pnode->data = 0;
	pnode->next = NULL;

	return pnode;
}

//初始化链表结点
void list_init(struct _tagLIST *pnode, int data)
{
	if(NULL == pnode)
	{
		return;
	}

	pnode->data = data;
	pnode->next = NULL;
}

//插入结点，头指针需要是二维指针（一维指针指向的是实体，二维指针指向的是指针）
void list_insert(struct _tagLIST **phead, struct _tagLIST *pnode)
{
	if(NULL == pnode)
	{
		return;
	}

	if(NULL == phead)
	{
		*phead = pnode;
	}
	else
	{
		pnode->next = *phead;
		*phead = pnode;
	}
}

//删除结点
void list_delete(struct _tagLIST *phead, struct _tagLIST *pnode)
{
	if((NULL == phead)
			|| (NULL == pnode))
	{
		return;
	}
	
	struct _tagLIST *pre_node = phead;
	struct _tagLIST *tmp = pre_node->next;
	struct _tagLIST *old_node = NULL;

	if(phead == pnode)
	{
		old_node = phead;
		phead = phead->next;
		free(old_node);

		return;
	}

	while(NULL != tmp)
	{
		if(tmp == pnode)
		{
			old_node = tmp;
			tmp = tmp->next;
			pre_node->next = tmp;
			free(old_node);
			break;
		}
		else
		{
			tmp = tmp->next;
			pre_node = pre_node->next;
		}
	}

	return;
}

//显示链表内容
void list_print(struct _tagLIST *phead)
{
	struct _tagLIST *tmp = phead;

	while(NULL != tmp)
	{
		printf("data:[%d]\n", tmp->data);
		tmp = tmp->next;
	}
}

