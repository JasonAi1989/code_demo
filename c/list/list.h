#ifndef __LIST_H__
#define __LIST_H__

struct _tagLIST
{
	int data;
	struct _tagLIST *next;
};

//创建结点
struct _tagLIST * list_create();

//初始化结点
void list_init(struct _tagLIST *, int);

//插入结点
void list_insert(struct _tagLIST **, struct _tagLIST *);

//删除结点
void list_delete(struct _tagLIST *, struct _tagLIST *);

//显示链表内容
void list_print(struct _tagLIST *);

#endif
