#include <stdio.h>


char * encrypt(char *a);
int main(int argc, const char *argv[])
{
    char str[1024];
    printf("input :\n");
    scanf("%s",str);
    printf("%s\n",encrypt(str));

    printf("%s\n",encrypt(str));
    return 0;
}

char * encrypt(char *a)
{   int j;

    for (j=0;a[j] != '\0';j++)
        a[j]=a[j] ^ 1021;
    return a;

}
