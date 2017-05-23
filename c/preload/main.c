#include <stdio.h>
#include <string.h>
#include <strings.h>

int main()
{
    char *pwd = "password";
    char buf[100];
    bzero(buf, sizeof(buf));

    scanf("%s", buf);

    if(!strcmp(pwd, buf))
    {
        printf("password is correct\n");
    }
    else
    {
        printf("wrong password\n");
    }

    return 0;
}
