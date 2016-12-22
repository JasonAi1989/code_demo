#include <stdio.h>
int main()
{
    char i, j = 0;

    for(i = 321; i > 0; i++)
    {
        j++;

        if(j > 500)
        {
            printf("dead loop\n");
            return 0;
        }
    }

    printf("run %d times\n", j);	//63

    return 0;
}
