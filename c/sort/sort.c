#include <stdio.h>

#include "sort.h"

/**
 * 冒泡排序，升序  n^2
 * @param  buf           [description]
 * @param  elementNumber [description]
 * @return               [description]
 */
int bubble(void **buf, uint32_t elementNumber)
{
    if(!buf || !*buf || elementNumber == 0)
        return RET_ERR;

    data_t *data = *(data_t **)buf;

    for(uint32_t i = 0; i < elementNumber; i++)
    {
        for(uint32_t j = 0; j < elementNumber - i - 1; j++)
        {
            if(data[j] > data[j + 1])
            {
                data_t temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    return RET_OK;
}

/**
 * 插入排序，升序  n^2
 * @param  buf           the buf  that need to be sorted
 * @param  elementNumber : the number of  buf elements
 * @return               RET_ERR or  RET_OK
 */
int insertion(void **buf, uint32_t elementNumber)
{
    if(!buf || !*buf || elementNumber == 0)
        return RET_ERR;

    data_t *data = *(data_t **)buf;

    for(uint32_t i = 1; i < elementNumber; i++)
    {
        data_t key = data[i];

        uint32_t j = i - 1;
        while(j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }

    return RET_OK;
}

/**
 * 选择排序，升序  n^2
 * @param  buf           [description]
 * @param  elementNumber [description]
 * @return               [description]
 */
int selection(void **buf, uint32_t elementNumber)
{

    //pseudo-code
    /*
    for i <- 1 to length[A]-1
        do key <- A[i]
        for j <- i+1 to length[A]
            do key <- max{key, A[j]}
            do index = index of key

        A[i] <-> A[index]
    */

    if(!buf || !*buf || elementNumber == 0)
        return RET_ERR;

    data_t *data = *(data_t **)buf;

    for(uint32_t i=0; i<elementNumber-1; i++)
    {
        data_t key = data[i];
        uint32_t index = i;
        for (uint32_t j = i+1; j < elementNumber; j++)
        {
            if (key > data[j])
            {
                key = data[j];
                index = j; 
            }
        }

        data_t temp = data[i];
        data[i] = data[index];
        data[index] = temp;
    }

    return RET_OK;
}

//////////////////
/**
 * 合并排序中合并数组的函数，这个函数是合并排序中的关键
 * @param  buf 数组
 * @param  p   数组下标
 * @param  q   数组下标
 * @param  r   数组下标，p<=q<r
 * @return     [description]
 */
int merge(void **buf, uint32_t p, uint32_t q, uint32_t r)
{
    //pseudo-code
    /*  
    n1 <- q-p+1;
    n2 <- r-q;

    create L[n1], R[n2]

    for i <- 1 to n1 
        do L[i] <- A[p+i]

    for j <- 1 to n2
        do R[j] <- A[q+1+j]

    i <- 1
    j <- 1

    for k <- p to r
        if i != n1 && (j == n2 || L[i] < R[j])
            A[k] <- L[i]
            i++
        else
            A[k] <- R[j]
            j++
    */

    if(!buf || !*buf)
        return RET_ERR;

    data_t *data = *(data_t **)buf;

    uint32_t n1 = q-p+1;
    uint32_t n2 = r-q;

    data_t left[n1], right[n2];
    int i,j;

    for (i = 0; i < n1; ++i)
    {
        left[i] = data[p+i];
    }

    for (j = 0; j < n2; ++j)
    {
        right[j] = data[q+1+j];
    }

    i=0;
    j=0;

    for (int k = p; k <= r; ++k)
    {
        //这里的判断要格外注意，可以使用哨兵值法或者比对长度法进行
        //值取完的判断，这里使用的是比对长度法进行的判断
        if (i != n1 && (j == n2 || left[i] <= right[j]))
        {
            data[k] = left[i];
            i++;
        }
        else
        {
            data[k] = right[j];
            j++;
        }
    }

    return RET_OK;
}

/**
 * 合并排序中分解数组的函数，这是一个递归函数
 * @param  buf 数组
 * @param  p   数组下标
 * @param  r   数组下标，p<r
 * @return     [description]
 */
void divide(void **buf, uint32_t p, uint32_t r)
{
    if (p < r)
    {
        uint32_t q = (p+r)/2;
        divide(buf, p, q);
        divide(buf, q+1, r);
        merge(buf, p, q, r);
    } 
}

/**
 * 合并排序，分治法，升序  nlgn
 * @param  buf           [description]
 * @param  elementNumber [description]
 * @return               [description]
 */
int merge_sort(void **buf, uint32_t elementNumber)
{
    if (elementNumber == 0)
    {
        return RET_ERR;
    }

    divide(buf, 0, elementNumber-1);
    return RET_OK;
}



///////////////
/**
 * [showData description]
 * @param  buf           [description]
 * @param  elementNumber [description]
 * @return               [description]
 */
int showData(void *buf, uint32_t elementNumber)
{
    if(!buf || elementNumber == 0)
        return RET_ERR;

    data_t *data = (data_t *)buf;

    for(uint32_t i = 0; i < elementNumber; i++)
    {
        printf("data[%lu]=%d\n", i, data[i]);
    }

    return RET_OK;
}

//test
//
//
//sdfsdf