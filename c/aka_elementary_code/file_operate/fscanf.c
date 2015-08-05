#include <stdio.h>
#include <stdlib.h>

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

    if((fp=fopen(argv[1],"r"))==NULL)
        {printf("can't open file\n");
        exit(1);
        }

    while(fscanf(fp,"%s %d %f",name,&num,&score)!=EOF)
    printf("%-20s %6d %6.2f\n",name,num,score);

    fclose(fp);

    return 0;
}
