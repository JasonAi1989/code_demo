#include "list.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
	struct _tagLIST *head = NULL, *p1, *p2;
	int i;

	for(i=1; i<10; i++)
	{
		p1 = list_create();
		list_init(p1, i);
		list_insert(&head, p1);

		if(5 == i)
		{
			p2 = p1;
		}
	}

	list_print(head);
	printf("---------------------\n");

	list_delete(head, p2);
	
	list_print(head);

	return 0;
}
