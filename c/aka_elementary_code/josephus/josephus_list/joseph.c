#include <stdio.h>
#include <stdlib.h>
#include "joseph.h"
#define NEW (struct node*)malloc(sizeof(struct node))

/* n是玩游戏的人数,m是报的数 */
int joseph(int m, int n)
{
	int i, cnt = 0, out = 0;
	struct node {
		int nr;
		int flag;
		struct node *next;
	};
	struct node *head, *new, *this = NULL;

	if (m > n || m < 1 || n < 1)
		return WRONG_IN;
	for (i = 1; i <= n; i++) {
		new = NEW;
		if (new == NULL)
			return MEMORY_OUT;
		new->nr = i;
		new->flag = 1;
		new->next = NULL;
		if (this == NULL) {
			this = new;
			head = this;
		} else {
			this->next = new;
			this = new;
		}
	}

	while (out < n) {
		this = head;
		while (this != NULL) {
			if (1 == this->flag) {
				cnt++;
				if (m == cnt) {
					cnt = 0;
					this->flag = 0;
					out++;
					printf("%3d:%3d out.", out,
					       this->nr);
					if (0 == out % 5)
						printf("\n");
				}
			}
			this = this->next;
		}
	}
	printf("\n");

	return OK;
}
