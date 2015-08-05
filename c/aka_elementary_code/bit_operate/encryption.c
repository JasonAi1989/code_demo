#include <stdio.h>
#include <string.h>
#include "common.h"

void encryption()
{
	char s[128];
	printf("input a string:");
	empty_cache();
	while (0 == strlen(gets(s))) {
		system("clear");
		printf("input a string:");
	}
	char *p = s, *q = s;

	while (*p) {
		*p = *p ^ 'x';	/* 加密，即和一个字母取异或 */
		p++;
	}
	printf("encrypted is :%s\n", s);
	while (*q) {
		*q = *q ^ 'x';	/* 解密，即和同一个字母取异或 */
		q++;
	}
	printf("decrypted is :%s\n", s);

}
