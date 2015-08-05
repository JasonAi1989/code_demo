#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void multi()
{
	int i, x, y, p, q, result = 0, flag = 0;
	printf("input x:");
	while (0 == scanf("%d", &x)) {
		empty_cache();
		printf("input x:");
	}
	printf("input y:");
	while (0 == scanf("%d", &y)) {
		empty_cache();
		printf("input y:");
	}
	if ((x >> 31) & 1)
		p = ~(x - 1);	/* 如为负数，则取其对应原码的正值 */
	else
		p = x;
	if ((y >> 31) & 1)
		q = ~(y - 1);
	else
		q = y;
	if (((x >> 31) & 1) ^ ((y >> 31) & 1))	/* 用补码判断结的正负号 */
		flag = 1;
	for (i = 0; i < 31; i++)
		if ((p >> i) & 1)
			result += q << i;	/* 用移位代替乘法 */
	if (1 == flag)
		result = ~result + 1;
	printf("x * y=%d\n", result);

}
