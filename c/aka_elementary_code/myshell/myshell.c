#include <stdio.h>
#include <stdlib.h>

char *myshell(char *s)
{
	char *p = s, *q = s, *r, *str = s;
	int flag = 0, flag1 = 0, flag2 = 0, flag3 = 0;

	system("clear");
	printf("$:");
	puts(s);
	printf("show the command:\n");

	/* 清除'<' '>'之后的空格 */
	while (*q) {
		if (*q == '<' || *q == '>') {
			flag = 1;
			break;
		} else
			*p++ = *q++;
	}
	if (flag == 1) {
		while (*q) {
			if (*q != ' ')
				*p++ = *q++;
			else
				q++;
		}
		*p = '\0';
	}
	/* 像单词一样的拆分字符串 */
	while (*s) {
		if ((*s != ' ')
		    && (*(s + 1) == ' ' || *(s + 1) == '<'
			|| *(s + 1) == '>' || *(s + 1) == '\0')) {
			r = s;
			int i, m = 0;
			for (; r > str; r--) {
				if (*r == ' ' || *r == '<' || *r == '>')
					break;
				m++;
			}
			/* 对单词的类型进行判断 */
			if (r == str) {	/* 指令前没空格 */
				flag1 = 1;
				printf("command:");
				for (i = 0; i < m + 1; i++)
					printf("%c", *(r + i));
			} else if (flag1 == 0) { /* 指令前有空格 */
				flag1 = 1;
				printf("command:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));

			} else if (*r == ' ') {	/* 以空格开始的单词 */
				printf(",argument:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
			} else if (*r == '<') {	/* 以非空格开始的单词 */
				printf("\nin-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
				flag2 = 1;

			} else if (*r == '>') {
				printf("\nout-file:");
				for (i = 0; i < m; i++)
					printf("%c", *(r + 1 + i));
				flag3 = 1;
			}
		}
		s++;
	}
	if (flag2 == 0)
		printf("\nin-file:NULL");
	if (flag3 == 0)
		printf("\nout-file:NULL");
	printf("\n");
	return str;
}
