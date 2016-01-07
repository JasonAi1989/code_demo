#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "sort.h"

int main()
{
	data_t  array[] ={34,15,17,8,1,5,3,8,6,9,88};
	int num = sizeof(array)/sizeof(int);
	
	int * p = malloc(sizeof(array));
	bzero(p, sizeof(array));
	memcpy(p, array, sizeof(array));
	
	showData(array, num);
	
	//bubble((void **)&p, num);  //Êý×é×öÊäÈëÊä³ö²ÎÊý»áÓÐÎÊÌâ£¬ËùÒÔ¸ÄÎªÊ¹ÓÃÄÚ´æ·ÖÅäµÄÖ¸Õë£¬Õâ¿ÉÄÜºÍÊý×éÊÇ·ÖÅäÔÚÕ»ÉÏµÄÓÐ¹Ø
	//insertion((void**)&p, num);
	//selection((void**)&p, num);
	merge_sort((void**)&p, num);
	
	showData(p, num);
	
	free(p);
	return 0;
}