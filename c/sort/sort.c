#include <stdio.h>

#include "sort.h"

//sort the value from small to big
int bubble(void **buf, uint32_t elementNumber)
{
	if(!buf || !*buf|| elementNumber==0)
		return RET_ERR;
	
	data_t *data = *(data_t **)buf;		
	
	for(uint32_t i=0; i<elementNumber; i++)
	{
		for(uint32_t j=0; j<elementNumber-i-1; j++)
		{
			if(data[j] > data[j+1])
			{
				data_t temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;				
			}			
		}		
	}

	return RET_OK;
}

int showData(void *buf, uint32_t elementNumber)
{
	if(!buf || elementNumber==0)
		return RET_ERR;
	
	data_t *data = (data_t*)buf;
	
	for(uint32_t i=0; i<elementNumber; i++)
	{
		printf("data[%lu]=%d\n", i, data[i]);		
	}
	
	return RET_OK;
}