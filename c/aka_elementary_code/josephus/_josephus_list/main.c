#include <stdio.h>
#include "josephus.h"

int main(int argc, char *argv[])
{
	int m, n, ret;

	if (3 != argc) {
		printf("input(m<n):./file m n\n");
		return 0;
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	if (m > n || m < 1 || n < 1) {
		printf("input(m<n):./file m n\n");
		return 0;
	}
	ret = josephus(m, n);
	switch (ret) {
	case WRONG_IN:
		printf("wrong input!\n");
		break;
	case MEMORY_OUT:
		printf("memory out!\n");
		break;
	case OK:
		return 0;
	}

	return 0;
}
