#include <stdio.h>
#include <stdlib.h>

char buff[32768];

int main(int argc,char *argv[])
{
    FILE *fp1,*fp2;
    unsigned int bfsz=32768;
    unsigned long i=0;

    
    if(3!=argc)
        {printf("input :./file src_file dest_file\n");
        return 0;
        }
    if((fp1=fopen(argv[1],"rb"))==0)
        {printf("can't open file %s.",argv[1]);
        exit(1);
        }
    if((fp2=fopen(argv[2],"wb"))==0)
        {printf("can't open file %s.",argv[2]);
        exit(1);
        }

    while(bfsz)
    {if(fread(buff,bfsz,1,fp1))
         {fwrite(buff,bfsz,1,fp2);
         i=i+bfsz;
         }
         else
         {fseek(fp1,i,0);
         bfsz=bfsz/2;
         }
     }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
