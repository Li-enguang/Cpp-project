#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

int n, m; //ϵͳ�н�������n����Դ��������m
int Available[100]; //��Դ��������
int Max[100][100];  //����������
int Allocation[100][100] = { 0 }; //��ǰ�������ÿ�����̵ĸ�����Դ����
int Need[100][100];//��ǰÿ�����̻������ĸ�����Դ����
int Work[100]; //��ǰ�ɷ������Դ
bool Finish[100]; //�����Ƿ����

//��ʾ����
void show_function()
{
	cout << "\n\n*        ����ѡ��        *" << endl;
	cout << "*1.��ʾ��ǰ��Դ���      *" << endl;
	cout << "*2.��ǰ״̬��ȫ���      *" << endl;
	cout << "*3.������Դ����          *" << endl;
	cout << "*4.�˳�����              *" << endl;
	return;
}

//��ʼ��������
void input()
{
	cout << "���������������" << endl;
	cin >> n;
	cout << "��������Դ����������" << endl;
	cin >> m;
	cout << "���������������Դ������" << endl;
	for (int i = 0; i < m; i++)
	{
		cin >> Available[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << "***   �������P" << i << "�ĳ�ʼ��Ϣ   ***" << endl;
		cout << "������ý����������Դ���������" << endl;
		for (int j = 0; j < m; j++)
		{
			cin >> Max[i][j];
		}
		cout << "������ý����ѷ������Դ��������" << endl;
		for (int j = 0; j < m; j++)
		{
			cin >> Allocation[i][j];
		}
	}
	return;
}

//��ʾ��ǰ��Դ���
void show()
{
	//����������Allocation
	cout << "\n***   ��ǰ��Դ�������   ***" << endl;
	cout << "����";
	for (int i = 0; i < m; i++)
	{
		cout << "\t��Դ" << i;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "P" << i;
		for (int j = 0; j < m; j++)
		{
			cout << "\t" << Allocation[i][j];
		}
		cout << endl;
	}
	//����������Need
	cout << "\n***   ��ǰ��Դ�������   ***" << endl;
	cout << "����";
	for (int i = 0; i < m; i++)
	{
		cout << "\t��Դ" << i;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "P" << i;
		for (int j = 0; j < m; j++)
		{
			cout << "\t" << Need[i][j];
		}
		cout << endl;
	}
	//�����������Դ��Available
	cout << "\n***   ��ǰ��Դʣ�����   ***" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << "��Դ" << i << "\t";
	}
	cout << endl;
	for (int j = 0; j < m; j++)
	{
		cout << Available[j] << "\t";
	}
	cout << endl;
	//�������ִ�����
	cout << "\n***   ��ǰ����ִ�����   ***" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "����" << i << "\t";
	}
	cout << endl;
	for (int j = 0; j < n; j++)
	{
		if (Finish[j])
		{
			cout << "true" << "\t";
		}
		else
		{
			cout << "false" << "\t";
		}
	}
	cout << endl;
}

//�ж��ǲ������н��̾���ִ����
bool judge_end(bool *finish)
{
	bool flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (finish[i] != true)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

//״̬��ȫ���
void safety(int *result)
{
	int ji = 1;
	//��ʼ��Work
	for (int i = 0; i < m; i++)
	{
		Work[i] = Available[i];
	}
	//��ʼ��finish��finish���ڱ��β����б���ǲ������н��̶�ִ����
	bool finish[100];
	for (int i = 0; i < n; i++)
	{
		finish[i] = Finish[i];
	}
	int flag1 = 0;
	bool flag2 = 1;
	for (int i = 0; i < n; i++)
	{
		//��ѭ���¿�ʼʱ��������ѭ����ǰ��û�н����κν���
		if (i == 0)
			flag1 = 0;
		//�����Ѿ���ɵĽ���
		if (finish[i] == true)
			continue;
		//Work��Need�Ƚ�
		int flag3 = 1;
		for (int j = 0; j < m; j++)
		{
			if (Work[j] < Need[i][j])
			{
				flag3 = 0;
				break;
			}
		}
		//����Դ������������һ����
		if (flag3 != 1)
		{
			//�ǲ��Ǳ���ѭ������һ����û�ܽ���
			if (i == n - 1 && flag1 != 1)
			{
				//����һ����û�ܽ�����ԭ��
				//�ǲ���ȫ�������Ѿ���ִ������
				if (judge_end(finish))
					break;
				else
				{
					//����û�����Ľ��̵��޷�����
					flag2 = 0;
					break;
				}
			}
			continue;
		}
		else
		{
			//����Դ������ִ����ý��̣��ͷŸý���ռ�õ���Դ
			result[ji] = i;
			ji++;
			for (int j = 0; j < m; j++)
			{
				Work[j] = Work[j] + Allocation[i][j];
			}
			finish[i] = true;
			flag1 = 1;//�����һ���ҵ��˿���ִ����Ľ���
			i = -1;//��ͷ�ٿ�ʼ�������̼���
		}
	}
	result[0] = flag2;
	return;
}

//��Դ����
bool allocate(int number, int *  request)
{
	int flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (request[i] > Need[number][i])
		{
			flag = 0;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "������ڸý��̻���Ҫ����Դ�������󲻺Ϸ�" << endl;
		return 0;
	}
	flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (request[i] > Available[i])
		{
			flag = 0;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "������ڵ�ǰϵͳʣ�����Դ�������󲻺Ϸ�" << endl;
		return 0;
	}

	// ���Է���
	for (int i = 0; i < m; i++)
	{
		Need[number][i] = Need[number][i] - request[i];
		Allocation[number][i] = Allocation[number][i] + request[i];
		Available[i] = Available[i] - request[i];
	}

	//��ȫ���ж�
	int *result = (int*)malloc(sizeof(int) * 101);
	memset(result, -1, sizeof(int) * 101);
	safety(result);
	if (result[0])
	{
		cout << "���ڴ˰�ȫ���У�";
		cout << "P" << result[1];
		for (int i = 2;; i++)
		{
			if (result[i] == -1)
			{
				break;
			}
			cout << " --> P" << result[i];
		}
		cout << endl;
		return 1;
	}
	else
	{
		cout << "���ݰ�ȫ�Լ�飬���η��䲻��ȫ" << endl;
		//��������
		for (int i = 0; i < m; i++)
		{
			Need[number][i] = Need[number][i] + request[i];
			Allocation[number][i] = Allocation[number][i] - request[i];
			Available[i] = Available[i] + request[i];
		}
		return 0;
	}
}

void end(int number)
{
	int flag = 1;
	for (int i = 0; i < m; i++)
	{
		if (Need[number][i] != 0)
		{
			flag = 0;
			break;
		}
	}
	//������������Ѿ�����Ҫ�ٷ�����Դ��
	//ִ����ý��̣��ͷ��ѷ�����Դ
	if (flag == 1)
	{
		cout << "***     ����P" << number << "ִ����ɣ�    ***" << endl;
		Finish[number] = true;
		for (int i = 0; i < m; i++)
		{
			Available[i] = Available[i] + Allocation[number][i];
			Allocation[number][i] = 0;
		}
	}
}

int main()
{
	cout << "******************************" << endl;
	cout << "***   ��ӭ�������м��㷨   ***" << endl;
	cout << "***1.��ʾ��ǰ��Դ���      ***" << endl;
	cout << "***2.��ǰ״̬��ȫ���      ***" << endl;
	cout << "***3.������Դ����          ***" << endl;
	cout << "***4.�˳�����              ***" << endl;
	cout << "******************************\n" << endl;

	memset(Finish, false, sizeof(Finish));
	//��ʼ��������
	input();
	//����Need�����ʣ��Ŀ���������ԴAvailable
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
			Available[j] = Available[j] - Allocation[i][j];
		}
	}


	int flag;
	while (true)
	{
		//����ѡ��
		show_function();
		cout << "��ѡ���ܣ�";
		cin >> flag;
		if (flag == 1)
		{
			//��ʾ��ǰ��Դ���
			//������ǰ��Դ�����������Դʣ�����
			show();
		}
		else if (flag == 2)
		{
			//��ǰ״̬��ȫ���
			int *result = (int*)malloc(sizeof(int) * 101);
			memset(result, -1, sizeof(int) * 101);
			safety(result);

			if (result[0] == 1)
			{
				cout << "���ڴ˰�ȫ���У�";
				cout << "P" << result[1];
				for (int i = 2;; i++)
				{
					if (result[i] == -1)
					{
						break;
					}
					cout << " --> P" << result[i];
				}
				cout << endl;
				cout << "***       �˿�״̬��ȫ       ***" << endl;

			}
			else
			{
				cout << "***      �˿�״̬����ȫ��    ***" << endl;
			}
		}
		else if (flag == 3)
		{
			//������Դ����
			int *request = (int*)malloc(sizeof(int) * 100);
			int number;
			cout << "�����뷢������Ľ��̣�P";
			cin >> number;
			cout << "�������������Դ��������" << endl;
			for (int i = 0; i < m; i++)
			{
				cin >> request[i];
			}
			if (allocate(number, request))
			{
				cout << "***  �÷��䰲ȫ������ɹ��� ***" << endl;
				//�ɹ�����Ľ��̣�����ɵľ���ɣ��ͷ�ռ�õ���Դ
				end(number);
			}
			else
			{
				cout << "***        ����ʧ�ܣ�       ***" << endl;
			}

		}
		else if (flag == 4)
		{
			//�˳�����
			cout << "�ɹ��˳���" << endl;
			break;

		}
	}
	system("pause");
	return 0;
}