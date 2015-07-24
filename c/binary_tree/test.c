#include <stdio.h>
#include "binary_tree.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	Tree root=NULL;
	unsigned int seed = 1024;
	Element data;
	
	for(int i=0; i<20; i++)
	{
		srand(i);
		data = rand() % 20;
		seed = data;

		insert_node(&root, data);
	}

	print_tree(root);
#if 1
	Element del;
	while(1)
	{
		printf("input the delete number:");
		scanf("%u", &del);

		delete_node(&root, del);

		print_tree(root);
	}
#endif
}

