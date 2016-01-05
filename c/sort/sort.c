#include <stdio.h>

#include "sort.h"

//升序
//bubble-sort
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

//升序
//insertion-sort
int insertion(void **buf, uint32_t elementNumber)
{
	if(!buf || !*buf|| elementNumber==0)
		return RET_ERR;
	
	data_t *data = *(data_t **)buf;		
	
	for(uint32_t i=1; i<elementNumber; i++)
	{
		data_t key = data[i];
		
		uint32_t j = i-1;
		while(j >= 0 && data[j]>key)
		{
			data[j+1] = data[j];
			j--;
		}
		data[j+1] = key;
	}

	return RET_OK;
}


///////////////
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