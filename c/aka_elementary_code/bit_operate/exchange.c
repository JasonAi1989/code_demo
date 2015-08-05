#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

void exchange()
{
	char string[128];
	printf("input a string:");
	empty_cache();
	while (0 == strlen(gets(string))) {
		system("clear");
		printf("input a string:");
	}
	char *p = string;
	while (*p)
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			*p = (*p) ^ (0x01 << 5);	/* 大小写字母只有第5位不同 */
			p++;
		} else
			p++;
	printf("exchanged is:%s\n", string);

}
