#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
/*����һ�����飬�趨���������±꣬
ͬʱ����һ���м��±�mid��
ÿ�ν����۰���ң���Ҫ���ҵ�����midС��
�����±����mid-1����Ҫ���ҵ�����mid��
�����±����mid+1.��Ҫ���ҵ�������mid����ѭ��ֹͣ��*/
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
		printf("�Ҳ���\n");
	}
	else
	{
		printf("�ҵ���\n�±�Ϊ��%d\n", ret);
	}
	
	return 0;
}
