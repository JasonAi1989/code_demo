#include <stdio.h>

static int name(char s1);
static int domain(char s2);

void get_email(char *str)
{
	char *p = str, *q, *r;
	while (*p) {
		/* 开始为‘@’时，进行下一轮循环 */
		if (*p == '@') {
			if (p == str) {
				p++;
				continue;
			}

			q = p - 1;
			r = p + 1;
			int m = 0, n = 0, i;
			/* name 判断 */
			while (q > str && name(*q) == 1) {
				m++;
				q--;
			}
			/* 判断开头字母的合法性，确定输出的起始位置 */
			if (q == str) {
				if (name(*q) == 1)
					m++;
				else
					q++;
			} else
				q++;
			/* domain 判断 */
			while ((*r != '\0') && domain(*r) == 1) {
				n++;
				r++;
			}
			/* 对可进行输出的条件进行判断，并输出 */
			if ((m >= 1 && m <= 32) && (n >= 1 && n <= 64)) {
				for (i = 0; i < m + n + 1; i++)
					printf("%c", *q++);
				printf("\n");
			}
		}
		p++;
	}

}

static int name(char s1)
{
	if (s1 >= 'a' && s1 <= 'z' || s1 >= 'A' && s1 < 'Z' || s1 == '.'
	    || s1 == '_' || s1 >= '0' && s1 <= '9')
		return 1;
	return 0;
}

static int domain(char s2)
{
	if (s2 >= 'a' && s2 <= 'z' || s2 >= 'A' && s2 <= 'Z' || s2 == '.'
	    || s2 == '-' || s2 >= '0' && s2 <= '9')
		return 1;
	return 0;
}
