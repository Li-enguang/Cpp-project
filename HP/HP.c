#define _CRT_SECURE_NO_WARNINGS 1

#include"Hp.h"

void hpcreat(heap* hp, Hpdatatype* array, int size)
{
	hp->_array = (Hpdatatype*)malloc(sizeof(Hpdatatype)*size);
	memcpy(hp->_array,array,sizeof(Hpdatatype)*size);
	hp->_size = size;
	hp->_capacity = size;

	//建堆 
	for (int partent = (size - 2) / 2; partent >= 0; partent--)
	{
		shiftdown(hp->_array, size, partent);
	}

}

void Swap(Hpdatatype* array,int child,int partent)
{
	int cur = array[child];
	array[child]=array[partent];
	array[partent] = cur;
}

void  shiftup(Hpdatatype* array, int child)
{
	int partent = (child - 1) / 2;
	while (child > 0) {
		if (array[child] < array[partent])
		{
			Swap(array, child, partent);
			child = partent;
			partent = (child - 1) / 2;
		}
		else
			break;
	}
}

void hppush(heap* hp,Hpdatatype data)
{
	if (hp->_size == hp->_capacity)
	{
		hp->_capacity *= 2;
		hp->_array = (Hpdatatype*)realloc(hp->_array, sizeof(Hpdatatype)*hp->_capacity);
		hp->_size++;
	}
	hp->_array[hp->_size-1] = data;
	shiftup(hp->_array, hp->_size-1);

}

void shiftdown(Hpdatatype* array, int size, int partent) //小堆向下调整
{
	int child = partent * 2 + 1;
	while (child < size)
	{
	if (child+1<size&&array[child] > array[child + 1])
	{
		child = child + 1;
	}

	
		if (array[child] <array[partent])
		{
			Swap(array, child, partent);
			partent = child;
		    child = partent * 2 + 1;
		}
		else 
		{
			break;
		}
	}


}

void hppop(heap* hp) 
{
	int tmp = hp->_array[0];
	hp->_array[0] = hp->_array[hp->_size-1];
	hp->_array[hp->_size-1]=tmp;
	hp->_size--;
	shiftdown(hp->_array, hp->_size, 0);

}


void hpprint(heap* hp)
{
	int i = 0;
	int k = 0;
	for (i = 0; i < hp->_size; i++)
	{
		printf("%d ", hp->_array[i]);
		
		if(i == k)
		{
			k = 2 * k + 2;
			printf("\n");
		}
	}

}