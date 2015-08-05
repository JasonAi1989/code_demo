#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void d2b()
{
	int i, j, binary, decimal;
	printf("input a decimal:");
	while (0 == scanf("%d", &decimal)) {
		empty_cache();
		system("clear");
		printf("input a decimal:");
	}
	printf("turned to binary is:");
	if (0 == decimal)
		printf("%d", decimal);
	else {
		if ((decimal >> 31) & 1) {
			binary = ~(decimal - 1);	/* 取负数原码对应的正值 */
			printf("-");
		} else
			binary = decimal;
		for (i = 30; i >= 0; i--)
			if ((binary >> i) & 1)
				break;
		for (j = i; j >= 0; j--)
			printf("%d", ((binary >> j) & 1));
	}
	printf("\n");

}
