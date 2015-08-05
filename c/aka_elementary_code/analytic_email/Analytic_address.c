#include <stdio.h>
#include <string.h>

#define MAX_ADDRES 64
#define MAX_NAME 32
#define MAX_CHARS_LINE 1024

char str[MAX_CHARS_LINE] = { };

int strch(char a);
int str_name(int i);
int str_address(int i);
int analysis_one_line(void);

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		printf("error\n");
		printf("usage:\n command  file_name.html\n ");
	}
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL)
		return 0;
	while (!feof(fp)) {
		fgets(str, MAX_CHARS_LINE, fp);
		analysis_one_line();
	}
	fclose(fp);
	return 0;
}

int analysis_one_line(void)
{
	int i, j, k, n;
	i = j = k = n = 0;

	while (str[i] != '\0') {
		i = strch('@');
		if (0 == i) {
			str[0] = '&';
			continue;
		}
		if (-1 == i)
			break;
		j = str_name(i);
		k = str_address(i);
/*
        if (str[k+1] == '\0'){
            i=k+1;
            continue;
        }   */

		if (-1 == j || -1 == k) {
			str[i] = '&';
			continue;
		}
		for (n = j; n <= k; n++)
			printf("%c", str[n]);
		printf("\n");
		str[i] = '&';
		i = k + 1;
	}

}

int str_name(int i)
{
	int j;
	for (j = i - 1; j >= 0; j--) {
		if (j < i - MAX_NAME-1)
			return -1;
		if (str[j] <= '9' && str[j] >= '0' ||
		    str[j] >= 'a' && str[j] <= 'z' ||
		    str[j] >= 'A' && str[j] <= 'Z' ||
		    str[j] == '_' || str[j] == '.')
			continue;
		else
			break;
	}

        if (j==i-1)
        return -1;
	return j + 1;
}

int str_address(int i)
{
	int j;
	for (j = i + 1;; j++) {
		if (j > i + MAX_ADDRES+1)
			return -1;
		if (str[j] <= '9' && str[j] >= '0' ||
		    str[j] >= 'a' && str[j] <= 'z' ||
		    str[j] >= 'A' && str[j] <= 'Z' ||
		    str[j] == '-' || str[j] == '.')
			continue;
		else
			break;
	}
        if (j==i+1)
        return -1;
	return j - 1;
}

int strch(char a)
{
	int i;
	for (i = 0; i < MAX_CHARS_LINE; i++) {
		if (str[i] == a )
			return i;
		if (str[i] == '\0')
			return -1;
	}
}
