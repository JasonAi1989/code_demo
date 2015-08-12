#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "sort.h"

int main()
{
	data_t  array[]={34,15,17,8,1,5,3,8,6,9,88};
	int num=sizeof(array)/sizeof(int);
	
	int * p = malloc(sizeof(array));
	bzero(p, sizeof(array));
	memcpy(p, array, sizeof(array));
	
	showData(array, num);
	
	bubble((void **)&p, num);  //������������������������⣬���Ը�Ϊʹ���ڴ�����ָ�룬����ܺ������Ƿ�����ջ�ϵ��й�
	
	showData(p, num);
	
	free(p);
	return 0;
}