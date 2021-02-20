#define _CRT_SECURE_NO_WARNINGS 1

#include<stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;

#define N 10
/*
	插入排序
	时间复杂度 ：1+2+...+n-1  最坏o(n^2) 最好O（n）
	空间复杂度 ：o（1）
	稳定性 ：稳定
	数据敏感 ： 敏感

	希尔排序
	时间复杂度 ：  最坏o(n^1.3) 最好O（n）
	空间复杂度 ：o（1）
	稳定性 ：不稳定 --> 分组时相同值元素不一定分在一组，预排序会导致顺序变化
	数据敏感 ： 敏感 

	选择排序
	时间复杂度 ：  最坏  最好O（n^2）
	空间复杂度 ：o（1）
	稳定性 ：稳定
	数据敏感 ： 不敏感

	冒泡排序
	时间复杂度 ：  最坏O（n^2）  最好O（n）--》遍历一遍退出
	空间复杂度 ：o（1）
	稳定性 ：稳定  --》相同值元素 位置不变
	数据敏感 ： 敏感

	堆排序
	时间复杂度 ： o(nlogn)
	空间复杂度 ：o（1）
	稳定性 ：不稳定 
	数据敏感 ： 敏感

	快速排序
	时间复杂度 ： 最好 o(nlogn) 最坏理论上o（n2） 平均 o(nlogn)
	空间复杂度 ：o（logn） 函数调用栈 递归 极端情况 o(n)
	稳定性 ：不稳定
	数据敏感 ： 敏感
*/

class SortArr
{
public:
	SortArr()
	{
		srand((unsigned int)time(NULL));
		for (int i = 0; i < N; i++)
		{
			arr[i] = rand() % (N*2);
		}
	}

	void insertsort()
	{
		size_t time_start, time_end;
		time_start = clock();

		for (int i = 0; i < N-1; i++)
		{
			int end = i; //有序队列的最后一个位置，刚开始 0
			int key = arr[end + 1]; //无序的第一个，待插入元素
			while (end >= 0 && arr[end] > key)//只要key 比前一个小 就把前一个往后移
			{
				arr[end + 1] = arr[end];
				end--;
			}
			arr[end + 1] = key;
		}

		time_end = clock();
		cout << "insertsort use " << (time_end - time_start) << "ms" << endl;
	}

	void shellsort()
	{
		size_t time_start, time_end;
		time_start = clock();

		//进行多轮预排序，最后一次插入排序
		int gap = N/2;
		while (gap)
		{
			for (int i = 0; i < N - gap; i++)
			{
				int end = i;
				int key = arr[end + gap];
				while(end>=0&&arr[end] > key)
				{
					arr[end + gap] = arr[end];
					end-=gap;
				}
				arr[end + gap] = key;
			}
			gap /= 2;
		}

		time_end = clock();
		cout << "shellsort use " << (time_end - time_start) << "ms" << endl;
	}

	void selectsort()
	{
		size_t time_start, time_end;
		time_start = clock();

		int min,start;
		for (int i = 0; i < N; i++)
		{
			start = i; //未排序数据最左边
			min = start; //最小值下标

			for (int j=start+1; j < N; ++j)
			{
				if ( arr[j] < arr[min])
				{
					 min = j;
				}
			}
			swap(arr[min],arr[i]);
		}
		time_end = clock();
		cout << "selectsort use " << (time_end - time_start) << "ms" << endl;
	}

	void high_selectsort()
	{
		size_t time_start, time_end;
		time_start = clock();

		int begin = 0;
		int end = N - 1;

		while (begin < end)
		{
			int min = begin;
			int max = begin;
			for (int i = begin + 1; i <= end; i++)
			{
				if (arr[i] >= max)max = i;
				if (arr[i] < min)min = i;
			}
			swap(arr[begin], arr[min]);
			if (max == begin)max = min;
			begin++;
			end--;
		}
		time_end = clock();
		cout << "high_selectsort use " << (time_end - time_start) << "ms" << endl;
	}

	void bubblesort()
	{
		int flag = 0;// 优化 ：默认没有元素交换
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N - i -1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
					flag = 1;//有交换 flag=1
				}
			}
			if (flag == 0) //一轮排序完，没有交换 可以提起结束了，已经有序了
				break;
		}
	}

	void heapsort()
	{
		size_t time_start, time_end;
		time_start = clock();
		int n = N;
		//建堆
		for (int i = (N - 2) / 2; i >= 0; i--) //从最后面一个非叶子节点开始
		{
			shiftdown(n,i);
		}

		while (n)
		{
			swap(arr[0], arr[n-1]); //交换堆顶和最后一个元素
			n--;
			shiftdown(n,0); //传入n 最后面的元素 已经最大了，不用调整了
		}
		time_end = clock();
		cout << "heapsort use " << (time_end - time_start) << "ms" << endl;
	}

	void shiftdown(int n,int parent) //向下调整 保证父亲是最大的
	{
		int child = parent * 2 + 1;//左孩子
		while (child < n)
		{
			if (child + 1 < n && arr[child] < arr[child + 1]) //右孩子存在，且右 > 左
			{
				++child;
			}	
			if (arr[child] > arr[parent])
			{
				swap(arr[child], arr[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}	

	}

	void quicksort()
	{
		size_t time_start, time_end;
		time_start = clock();
		quicksort(0, N - 1);
		time_end = clock();
		cout << "quicksort use " << (time_end - time_start) << "ms" << endl;
	}
	void quicksort2()
	{
		size_t time_start, time_end;
		time_start = clock();
		quicksort2(0, N - 1);
		time_end = clock();
		cout << "quicksort2 use " << (time_end - time_start) << "ms" << endl;
	}
	void quicksort(int begin,int end)
	{
		if (begin >= end) //只有一个元素
			return;
		//划分当前区间
		int pos=partition(begin, end);
		//划分子区间
		quicksort(begin, pos - 1);
		quicksort(pos + 1,end);
	}
	void quicksort2(int begin, int end)
	{
		if (begin >= end) //只有一个元素
			return;
		//划分当前区间
		int pos = partition2(begin, end);
		//划分子区间
		quicksort2(begin, pos - 1);
		quicksort2(pos + 1, end);
	}

	//hora划分法
	int partition(int begin,int end)
	{
		int mid = getmid(begin, end);
		swap(arr[mid], arr[begin]);
		int key = arr[begin];//基准值
		int start = begin;
		while (begin < end) 
		{
			//从后往前找，找第一个比基准值小的
			while (begin < end&&arr[end] >= key)
				--end;
			//从前往后走，找第一个比基准大的
			while (begin < end&&arr[begin] <= key)
				++begin;

			//找到了，交换这两个
			swap(arr[begin], arr[end]);
		}
		//跳出循环，说明相遇了，交换当前与基准值
		swap(arr[begin], arr[start]);
		//返回基准值的位置
		return begin;
	}

	//挖坑法
	int partition2(int begin,int end)
	{
		int mid = getmid(begin, end);
		swap(arr[mid], arr[begin]);
		int key = arr[begin];
		while (begin < end)
		{
			while (begin < end&&key <= arr[end])
				end--;
			arr[begin] = arr[end];
			while (begin < end&&key >= arr[begin])
				begin++;
			arr[end] = arr[begin];
		}
		arr[begin] = key;
		return begin;
	}

	void printarray()
	{
		for (int i = 0; i < N; i++)
		{
			cout << arr[i]<<" ";
		}
		cout << endl;
	}

	template<class T>
	void swap(T&a,T&b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	int getmid(int begin,int end)
	{
		int mid = begin + (end - begin) / 2;
		if (arr[begin] < arr[mid])
		{
			if (arr[mid] < arr[end])
				return mid;
			else
			{
				if (arr[end] > arr[begin])
					return end;
				return begin;
			}
		}
		else //begin >= mid
		{
			if (arr[mid] > arr[end])
				return mid;
			else
			{
				if (arr[end] > arr[begin])
					return begin;
				return end;
			}
		}
	}
private:
	int arr[N];
};

int main()
{
	SortArr arr;
	arr.insertsort();
	return 0;
}