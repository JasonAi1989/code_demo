#include <stdio.h>
/*
	此文主要讲解6中主要的比较排序算法，包括：冒泡排序、插入排序、选择排序、归并排序、堆排序和快速排序
*/

/*
冒泡排序：每轮（第二层遍历）的目的是将大数向后移动，在后方形成已排序队列
时间复杂度为 n2
*/
void bubble_sort(int a[], int n)
{
    int i, j, temp;
    for (j = 0; j < n - 1; j++)
        for (i = 0; i < n - 1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
}

/*
插入排序：在前方形成已排序队列，每轮（第二层遍历）拿出未排序队列的第一个元素和前面的已排序队列进行比较，注意，已排序队列要通过倒序的方式进行遍历比较，将大数依次向后移动，然后将取出的元素插入到已排序队列中
时间复杂度为 n2
*/
void insertion_sort(int a[], int n)
{
	int i, j, key;
	for(j = 1; j < n; j++)
	{
		key = a[j];
		i = j-1;
		while(i>=0 && a[i] > key)
		{
			a[i+1] = a[i];
			i--;
		}
		
		a[i+1] = key;
	}
}

/*
选择排序：在前方形成已排序队列，每轮（第二层遍历）从未排序队列中找出当前第n小的元素，然后和第n位置的元素交换
时间复杂度为 n2
*/
void selection_sort(int a[], int n)
{
	int i, j, index, min;
	for(j=0; j<n-1; j++)
	{
		min = a[j];
		index = j;
		for(i=j+1; i<n; i++)
		{
			if(min > a[i])
			{
				min = a[i];
				index = i;
			}
		}
		
		if(index != j)
		{
			a[index] = a[j];
			a[j] = min;			
		}
	}
}

/*
归并排序：使用分治法进行排序
分割的时间复杂度为 lgn；
合并时相当于对所有元素进行了一次遍历，时间复杂度为 n
因此归并算法的整体时间复杂度为 nlgn
但是归并算法为非原地排序算法，他用到了 n 的额外存储空间
*/
//p,q,r均为数组的索引
void merge(int a[], int p, int q, int r)
{
	int n1 = q-p+1;
	int n2 = r-q;
	
	int left[n1];
	int right[n2];
	
	int i, j, k, min;
	for(i=0; i<n1; i++)
	{
		left[i] = a[i+p];
	}
	for(i=0; i<n2; i++)
	{
		right[i] = a[i+q+1];
	}
	
	i=0;
	j=0;
	k=p;
	while(i < n1 || j < n2)
	{
		if(i < n1 && j < n2)
		{
			if(left[i] <= right[j])
			{
				min = left[i];
				i++;				
			}
			else
			{
				min = right[j];
				j++;
			}
		}
		else if(i == n1 && j < n2)
		{
			min = right[j];
			j++;
		}
		else
		{
			min = left[i];
			i++;
		}
		
		a[k] = min;
		k++;
	}
}
void divide(int a[], int p, int r)
{
	if(p < r)
	{
		int q = (p+r)/2;
		
		divide(a, p, q);
		divide(a, q+1, r);
		merge(a, p, q, r);
	}
}

void merge_sort(int a[], int n)
{
	divide(a, 0, n-1);
}

/*
堆排序:通过二叉堆的特性进行排序
	最大堆：所有父节点的数值大于等于子节点的数值，因此根节点的数值最大
	最小堆：所有父节点的数值小于等于子节点的数值，因此根节点的数值最小
使用最大堆性质取出根节点的值，放到队列的最后，然后重建最大堆。
重建最大堆的时间复杂度为lgn，遍历n次便能依次取出最大值，因此堆算法的时间复杂度为 nlgn，
并且堆排序为原地排序，不适用额外存储空间。
堆排序和选择排序很相似，都是找到队列中的最大值或者最小值，然后和对应位置的值进行交换，
不同的是对这个最大值或最小值选取的策略不同，简单选择排序使用线性比较的方式，而堆排序使用堆结构
*/	
#define PARENT(i) 	((i)/2)
#define LEFT(i)		(2*(i))
#define RIGHT(i)	(2*(i)+1)

void max_heapify(int a[], int index, int heap_size)
{
	if(index >= heap_size)
		return;
	
	int l,r,index_largest;
	l = LEFT(index);
	r = RIGHT(index);
	
	if(l < heap_size && a[l] >= a[index])
	{
		index_largest = l;	
	}
	else
	{
		index_largest = index;
	}
	
	if(r < heap_size && a[r] > a[index_largest])
	{
		index_largest = r;
	}
	
	if(index_largest != index)
	{
		int temp = a[index_largest];
		a[index_largest] = a[index];
		a[index] = temp;
		
		max_heapify(a, index_largest, heap_size);
	}
}

void build_max_heap(int a[], int heap_size)
{
	int i;
	for(i=heap_size/2; i>=0; i--)
	{
		max_heapify(a, i, heap_size);
	}
}

void heap_sort(int a[], int n)
{
	int heap_size = n;
	int i, temp;
	
	build_max_heap(a, heap_size);  //建堆，时间复杂度为 n
	
	for(i = n-1; i>0; i--)
	{
		temp = a[i];   //交换元素
		a[i] = a[0];
		a[0] = temp;
		
		heap_size--;  //减小堆
		
		max_heapify(a, 0, heap_size);  //维护堆性质，时间复杂度为 lgn
	}	
}

/*
快速排序
平均时间复杂度为  nlgn，并且为原地排序算法，和堆排序相比，快速排序拥有更小的常数因子，因此在各个系统中常用此算法。
快速排序的缺点是，最坏情况的运行时间复杂度为 n2
快速排序使用的也是分治法，但和归并算法不同，快速排序算法中加入了主元的概念，通过主元将元素分为小数值分组和大数值分组，
如此这样划分下去，便自动实现了排序的目的
*/
//p, r均为数组下标，返回值为最后主元在数组中的下标
int partition(int a[], int p, int r)
{
	int i,j,key,temp;
	
	i = p-1;
	j = p;
	key = a[r];
	
	for(j=p; j<=r-1; j++)
	{
		if(a[j] <= key)
		{
			temp = a[j];
			a[j] = a[i+1];
			a[i+1] = temp;
			
			i++;
		}
	}
	
	a[r] = a[i+1];
	a[i+1] = key;
	i++;
	
	return i;
}

void quick(int a[], int p, int r)
{
	if(p < r)
	{
		int q = partition(a, p, r);
		quick(a, p, q-1);
		quick(a, q+1, r);
	}
}

void quick_sort(int a[], int n)
{
	quick(a, 0, n-1);
}

/*
上述6种排序算法中：
时间复杂度为n2的算法：冒泡排序，插入排序，选择排序（简单选择排序）
时间复杂度为nlgn的算法：归并排序，堆排序，快速排序

除了归并排序外，其余均是原地排序算法

快速排序拥有更小的常数因子，但是最坏情况的时间复杂度为n2
*/

int main()
{
	int a[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int b[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int c[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int d[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int e[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int f[] = {8, 10, 9, 3, 89, 45, 23, 44, 3, 22};
	int n = sizeof(a)/sizeof(int);
	
	printf("n:%d\n", n);
	printf("original array:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	bubble_sort(a, n);
	insertion_sort(b, n);
	selection_sort(c, n);
	merge_sort(d, n);
	heap_sort(e, n);
	quick_sort(f, n);

	printf("bubble_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	
	printf("insertion_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
	
	printf("selection_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", c[i]);
	}
	printf("\n");
	
	printf("merge_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", d[i]);
	}
	printf("\n");
	
	printf("heap_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", e[i]);
	}
	printf("\n");
	
	printf("quick_sort:\t\t");
	for(int i=0; i<n; i++)
	{
		printf("%d ", f[i]);
	}
	printf("\n");
	
	return 1;
}