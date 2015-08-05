#include <stdio.h>
#include <stdlib.h>

int jose(int num,int out)
{
    typedef struct Node{
            int val;
            struct Node * next;
    }Node,* PNode;
    int i,count;
    PNode  head = NULL,p = NULL,cu = NULL,ne = NULL;
                        //head is the head of link, p is 
                        //primary of the link, cu is 
                        //current of the link
    head =(Node *)malloc(sizeof(Node) * num);
    if (head == NULL)
    {
        printf("cannot malloc\n");
        return 0;
    }
    
    p = head;
    for (i=1;i<num+1;i++)
    {
        p->val = i;
        if (i!=num)
        {
            p->next = (p+1);
            p++;
        }else{
            p->next = head;
        }
    }


    cu = head;
    for (i=0;i<num;i++)
    {
        count=0;
        while(1)
        {
            count++;
            if (count == out)
            {
                printf("%3d:%5d\n",i+1,cu->val);
                p->next = cu->next;
                cu=p->next;
                break;
            }
            p = cu;
            cu = cu->next;
        }
        
    }


    

   free(head);
}

int main(int argc, const char *argv[])
{
    int num,out;
  //  if (argc != 3)
  //  {    printf("error\n");
  //      return 0;
  //  }

  //  num = atoi(argv[1]);
   // out = atoi(argv[2]);
    
    jose(100,2);

    return 0;
}
