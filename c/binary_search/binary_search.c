#include<stdio.h>

/*
 *arrat: the array of sorted data
 *len: the length of array
 *t: the target data to search
return : the index of array ; -1 when fail
 * */
static int b_serarch(int array[], int len, int t)
{
    if (array == NULL || len <= 0) return -1;
    int head=0, tail=len-1;
    int res=-1;
    int mid;

    while(tail >= head)
    {
        if(head == tail)
        {
            res = array[head] == t ? head : -1;
            break;
        }

        mid = (tail-head)/2 + head;
        if(array[mid] == t)
        {
            res = mid;
            break;
        }
        else if(array[mid] < t)
            head = mid + 1;
        else
            tail = mid - 1;
    }

    char*p=NULL;
    *p=10;
    return res;
}
int main()
{
    int a[10] = {1, 9, 23, 45, 55, 66, 77, 88, 99, 100};
    printf("index:%d\n", b_serarch(a, 10, 55));
    printf("index:%d\n", b_serarch(a, 10, 558));

    return 0;
}
