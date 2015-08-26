#ifndef __LIST_H__
#define __LIST_H__

struct _tagLIST
{
	int data;
	struct _tagLIST *next;
};

//�������
struct _tagLIST * list_create();

//��ʼ�����
void list_init(struct _tagLIST *, int);

//������
void list_insert(struct _tagLIST **, struct _tagLIST *);

//ɾ�����
void list_delete(struct _tagLIST *, struct _tagLIST *);

//��ʾ��������
void list_print(struct _tagLIST *);

#endif
