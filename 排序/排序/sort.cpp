#define _CRT_SECURE_NO_WARNINGS 1

#include<stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;

#define N 10
/*
	��������
	ʱ�临�Ӷ� ��1+2+...+n-1  �o(n^2) ���O��n��
	�ռ临�Ӷ� ��o��1��
	�ȶ��� ���ȶ�
	�������� �� ����

	ϣ������
	ʱ�临�Ӷ� ��  �o(n^1.3) ���O��n��
	�ռ临�Ӷ� ��o��1��
	�ȶ��� �����ȶ� --> ����ʱ��ֵͬԪ�ز�һ������һ�飬Ԥ����ᵼ��˳��仯
	�������� �� ���� 

	ѡ������
	ʱ�临�Ӷ� ��  �  ���O��n^2��
	�ռ临�Ӷ� ��o��1��
	�ȶ��� ���ȶ�
	�������� �� ������

	ð������
	ʱ�临�Ӷ� ��  �O��n^2��  ���O��n��--������һ���˳�
	�ռ临�Ӷ� ��o��1��
	�ȶ��� ���ȶ�  --����ֵͬԪ�� λ�ò���
	�������� �� ����

	������
	ʱ�临�Ӷ� �� o(nlogn)
	�ռ临�Ӷ� ��o��1��
	�ȶ��� �����ȶ� 
	�������� �� ����

	��������
	ʱ�临�Ӷ� �� ��� o(nlogn) �������o��n2�� ƽ�� o(nlogn)
	�ռ临�Ӷ� ��o��logn�� ��������ջ �ݹ� ������� o(n)
	�ȶ��� �����ȶ�
	�������� �� ����
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
			int end = i; //������е����һ��λ�ã��տ�ʼ 0
			int key = arr[end + 1]; //����ĵ�һ����������Ԫ��
			while (end >= 0 && arr[end] > key)//ֻҪkey ��ǰһ��С �Ͱ�ǰһ��������
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

		//���ж���Ԥ�������һ�β�������
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
			start = i; //δ�������������
			min = start; //��Сֵ�±�

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
		int flag = 0;// �Ż� ��Ĭ��û��Ԫ�ؽ���
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N - i -1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
					flag = 1;//�н��� flag=1
				}
			}
			if (flag == 0) //һ�������꣬û�н��� ������������ˣ��Ѿ�������
				break;
		}
	}

	void heapsort()
	{
		size_t time_start, time_end;
		time_start = clock();
		int n = N;
		//����
		for (int i = (N - 2) / 2; i >= 0; i--) //�������һ����Ҷ�ӽڵ㿪ʼ
		{
			shiftdown(n,i);
		}

		while (n)
		{
			swap(arr[0], arr[n-1]); //�����Ѷ������һ��Ԫ��
			n--;
			shiftdown(n,0); //����n ������Ԫ�� �Ѿ�����ˣ����õ�����
		}
		time_end = clock();
		cout << "heapsort use " << (time_end - time_start) << "ms" << endl;
	}

	void shiftdown(int n,int parent) //���µ��� ��֤����������
	{
		int child = parent * 2 + 1;//����
		while (child < n)
		{
			if (child + 1 < n && arr[child] < arr[child + 1]) //�Һ��Ӵ��ڣ����� > ��
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
		if (begin >= end) //ֻ��һ��Ԫ��
			return;
		//���ֵ�ǰ����
		int pos=partition(begin, end);
		//����������
		quicksort(begin, pos - 1);
		quicksort(pos + 1,end);
	}
	void quicksort2(int begin, int end)
	{
		if (begin >= end) //ֻ��һ��Ԫ��
			return;
		//���ֵ�ǰ����
		int pos = partition2(begin, end);
		//����������
		quicksort2(begin, pos - 1);
		quicksort2(pos + 1, end);
	}

	//hora���ַ�
	int partition(int begin,int end)
	{
		int mid = getmid(begin, end);
		swap(arr[mid], arr[begin]);
		int key = arr[begin];//��׼ֵ
		int start = begin;
		while (begin < end) 
		{
			//�Ӻ���ǰ�ң��ҵ�һ���Ȼ�׼ֵС��
			while (begin < end&&arr[end] >= key)
				--end;
			//��ǰ�����ߣ��ҵ�һ���Ȼ�׼���
			while (begin < end&&arr[begin] <= key)
				++begin;

			//�ҵ��ˣ�����������
			swap(arr[begin], arr[end]);
		}
		//����ѭ����˵�������ˣ�������ǰ���׼ֵ
		swap(arr[begin], arr[start]);
		//���ػ�׼ֵ��λ��
		return begin;
	}

	//�ڿӷ�
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