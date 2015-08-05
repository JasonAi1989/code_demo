#include <stdio.h>

void empty_cache(void)
{
	char ch;
	while ((ch = getchar()) != '\n');
}
