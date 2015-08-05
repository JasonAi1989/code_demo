#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char string[81];
    
    if(argc!=2)
        {printf("input: ./file1 file2\n");
        return 0;
        }

    if((fp=fopen(argv[1],"r"))==NULL)
        {printf("can't open file\n");
        exit(1);
        }
    
    while(fgets(string,81,fp)!=NULL)
        printf("%s",string);
        

    fclose(fp);

    return 0;
}
