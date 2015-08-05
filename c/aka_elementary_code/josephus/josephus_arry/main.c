#include <stdio.h>
#include <stdlib.h>
#include "josephus.h"

int main(int argc, char *argv[])
{
	int m, n;		/* n是玩游戏的人数,m是报的数 */
	if (3 != argc) {
		printf("input(m<n): ./file m n\n");
		return 0;
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	if (m > n || m < 1 || n < 1) {
		printf("input(m<n): ./file m n\n");
		return 0;
	}
	if (josephus(m, n) == WRONG_IN)
		printf("wrong input!\n");

	return 0;
}
