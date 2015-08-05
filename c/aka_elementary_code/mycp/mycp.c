#include <stdio.h>

static int cp_by_char(FILE * src, FILE * dest);
static int cp_by_record(FILE * src, FILE * dest);
static int cp_by_row(FILE * src, FILE * dest);

int mycp(const char *src, const char *dest)
{
	FILE *fp1, *fp2;
	int choice;
	if ((fp1 = fopen(src, "r")) == NULL) {
		printf("can't open:%s\n", src);
		return 1;
	}
	if ((fp2 = fopen(dest, "w")) == NULL) {
		printf("can't open:%s\n", dest);
		return 1;
	}

	while (1) {
		system("clear");
		printf("Please select:\n");
		printf("1.cp by char\n");
		printf("2.cp by record\n");
		printf("3.cp by row\n");
		printf("4.exit\n");
		printf("Your choice [1-4]:");
		if (scanf("%d", &choice) == 0) {
			char ch;
			while ((ch = getchar()) != '\n');
			continue;
		}
		if (choice >= 1 && choice <= 4)
			break;
	}
	switch (choice) {
	case 1:
		if (1 == cp_by_char(fp1, fp2))
			return 1;
		break;
	case 2:
		cp_by_record(fp1, fp2);
		break;
	case 3:
		if (1 == cp_by_row(fp1, fp2))
			return 1;
		break;
	case 4:
		return 1;
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

static int cp_by_char(FILE * src, FILE * dest)
{
	char ch;
	while ((ch = fgetc(src)) != EOF)
		if (EOF == fputc(ch, dest))
			return 1;

	return 0;
}

static int cp_by_record(FILE * src, FILE * dest)
{
	char buff[128];
	while (fread(buff, 1, 1, src) != 0)
		fwrite(buff, 1, 1, dest);

	return 0;
}

static int cp_by_row(FILE * src, FILE * dest)
{
	char string[81];
	while (fgets(string, 81, src) != NULL)
		if (EOF == fputs(string, dest))
			return 1;

	return 0;
}
