#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char string[81];
    
    if(argc!=2)
        {printf("input: ./file1 file2\n");
        return 0;
        }

    if((fp=fopen(argv[1],"w"))==NULL)
        {printf("can't open file\n");
        exit(1);
        }
    
    while(strlen(gets(string))>0)
        {fputs(string,fp);
        fputs("\n",fp);
        }

    fclose(fp);

    return 0;
}
