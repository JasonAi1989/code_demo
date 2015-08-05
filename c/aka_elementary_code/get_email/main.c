#include <stdio.h>
#include<stdlib.h>
#include "get_email.h"

#define MAX 1024

int main(int argc, char *argv[])
{
	FILE *fp;
	char string[MAX];
	if (2 != argc) {
		printf("intput:./file1 file2\n");
		return 0;
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("can't open file\n");
		exit(0);
	}
	while (fgets(string, MAX, fp) != NULL)
		get_email(string);
	fclose(fp);

	return 0;
}
