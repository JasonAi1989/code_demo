#ifndef SORT_H_
#define SORT_H_

//define the short type
#if 1
typedef signed char 			int8_t;
typedef unsigned char 			uint8_t;
typedef signed int 				int16_t;
typedef unsigned int 			uint16_t;
typedef signed long int 		int32_t;
typedef unsigned long int 		uint32_t;
typedef signed long long int 	int64_t;
typedef unsigned long long int 	uint64_t;
#endif

//return value
#define RET_ERR	-1
#define RET_OK	0

#define data_t int  //self define

int bubble(void **buf, uint32_t elementNumber);
int insertion(void **buf, uint32_t elementNumber);
int selection(void **buf, uint32_t elementNumber);
int merge_sort(void **buf, uint32_t elementNumber); //divide and conquer

int showData(void *buf, uint32_t elementNumber);

#endif