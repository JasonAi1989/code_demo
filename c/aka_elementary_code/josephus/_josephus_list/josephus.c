#include <stdio.h>
#include <stdlib.h>
#include "josephus.h"

int josephus(int m, int n)
{
	int i, cnt = 1, out = 0;
	typedef struct node {
		int nr;
		struct node *next;
	} Node, *PNode;
	PNode thisN = NULL, parent = NULL, head = NULL;

	if (m > n || m < 1 || n < 1)
		return WRONG_IN;

	head = (PNode) malloc(n * sizeof(Node));
	if (head == NULL)
		return MEMORY_OUT;

	parent = head;
	for (i = 1; i < n + 1; i++) {
		parent->nr = i;
		if (i != n) {
			parent->next = parent + 1;
			parent = parent->next;
		} else
			parent->next = head;
	}

	thisN = head;
	while (out < n) {
		while (cnt < m) {
			cnt++;
			parent = thisN;
			thisN = thisN->next;
		}
		cnt = 1;
		out++;
		printf("%3d:%3d out.", out, thisN->nr);
		if (0 == out % 5)
			printf("\n");
		parent->next = thisN->next;
		thisN = parent->next;
	}
	putchar('\n');
	free(head);

	return OK;
}
