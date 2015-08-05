#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    char name[20];
    int num;
    float score;
    
    if(2!=argc)
        {printf("input :./file1 file2\n");
        return 0;
        }
    if((fp=fopen(argv[1],"w"))==NULL)
        {printf("can't open file\n");
        exit(1);
        }
    printf("type mame,num,score:");
    scanf("%s %d %f",name,&num,&score);

    while(strlen(name)>1)
    {fprintf(fp,"%s %d %f",name,num,score);
    printf("type name,num,score:");
    scanf("%s %d %f",name,&num,&score);
    }

    fclose(fp);

    return 0;
}
