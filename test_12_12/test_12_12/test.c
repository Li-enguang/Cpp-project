#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
/*定义一个数组，设定它的左右下标，
同时定义一个中间下标mid，
每次进行折半查找，若要查找的数比mid小，
则右下标等于mid-1，若要查找的数比mid大，
则左下标等于mid+1.若要查找的数等于mid，则循环停止。*/
int binary_search(int arr[], int k, int sz)
{
	int left = 0;
	int right = sz - 1;
	int mid = (left + right) / 2;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] == k)
		{
			return mid;
		}
		else if (arr[mid] < k)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int k ;
	scanf("%d",&k);
	int ret = binary_search(arr, k, sz);
	if (ret == -1)
	{
		printf("找不到\n");
	}
	else
	{
		printf("找到了\n下标为：%d\n", ret);
	}
	
	return 0;
}
