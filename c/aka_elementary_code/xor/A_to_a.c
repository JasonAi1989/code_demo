#include <stdio.h>


char * trans(char *a);
int main(int argc, const char *argv[])
{
    char str[256];
    printf("input :\n");
    scanf("%s",str);
    printf("%s\n",trans(str));
    return 0;
}

char * trans(char *a)
{   int i,j;
    int y;

    for (j=0;a[j] != '\0';j++)
    if (a[j]>='a'&&a[j]<='z'||a[j]>='A'&&a[j]<='Z')
       a[j]=a[j] ^ 0x20;
    return a;

}
