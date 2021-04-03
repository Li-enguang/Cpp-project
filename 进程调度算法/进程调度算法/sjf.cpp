#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>

using namespace std;

/*
����ҵ���ȵ����㷨�Ӿ���������ѡ��һ����������ʱ����̵Ľ��̣�
����������������ʹ֮����ִ�У�
ֱ����ɻ���ĳ�¼�������ʱ�����ͷŴ������
*/

//���̸���
const int N = 5;
//���̽ṹ��
struct Process
{
	string name;//������
	int arriveTime;//���̵���ʱ��
	int runTime;//��������ʱ��
	int startTime;//���̿�ʼʱ��
	int finishTime;//���н���ʱ��
	bool isfinished;//�Ƿ��������
};

//��ӡ���н�����Ϣ
void PrintProcess(Process *A)
{
	cout << "name" << " " << "arriveTime" << " " << "runTime" << " " 
		<< "startTime" << " " << "endTime" << " " << "isfinished" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << A->name << "   " << A->arriveTime << "\t\t" << A->runTime << "\t" 
			<< A->startTime << "\t  " << A->finishTime << "\t  " << A->isfinished << endl;
		A++;

	}
}

//���յ���ʱ������
void SortedByArrivedTime(Process *A)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if ((A + j)->arriveTime < (A + i)->arriveTime)
			{
				string Na;
				int aT, rT, sT;
				int edT;
				bool isF;

				Na = (A + i)->name;
				(A + i)->name = (A + j)->name;
				(A + j)->name = Na;

				aT = (A + i)->arriveTime;
				(A + i)->arriveTime = (A + j)->arriveTime;
				(A + j)->arriveTime = aT;

				rT = (A + i)->runTime;
				(A + i)->runTime = (A + j)->runTime;
				(A + j)->runTime = rT;

				sT = (A + i)->startTime;
				(A + i)->startTime = (A + j)->startTime;
				(A + j)->startTime = sT;

				edT = (A + i)->finishTime;
				(A + i)->finishTime = (A + j)->finishTime;
				(A + j)->finishTime = edT;

				isF = (A + i)->isfinished;
				(A + i)->isfinished = (A + j)->isfinished;
				(A + j)->isfinished = isF;
			}
		}
	}
}
//���տ�ʼʱ������
void SortedByStartTime(Process *A)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if ((A + j)->startTime < (A + i)->startTime)
			{
				string Na;
				int aT, rT, sT;
				int edT;
				bool isF;

				Na = (A + i)->name;
				(A + i)->name = (A + j)->name;
				(A + j)->name = Na;

				aT = (A + i)->arriveTime;
				(A + i)->arriveTime = (A + j)->arriveTime;
				(A + j)->arriveTime = aT;

				rT = (A + i)->runTime;
				(A + i)->runTime = (A + j)->runTime;
				(A + j)->runTime = rT;

				sT = (A + i)->startTime;
				(A + i)->startTime = (A + j)->startTime;
				(A + j)->startTime = sT;

				edT = (A + i)->finishTime;
				(A + i)->finishTime = (A + j)->finishTime;
				(A + j)->finishTime = edT;

				isF = (A + i)->isfinished;
				(A + i)->isfinished = (A + j)->isfinished;
				(A + j)->isfinished = isF;
			}
		}
	}
}
/*
int main()
{
	Process Proc[N] = {
		{"P1",5,7},
		{"P2",4,4},
		{"P3",3,1},
		{"P4",2,4},
		{"P5",1,5}
	};

	//���ս��̵���ʱ�����򲢴�ӡ���
	SortedByArrivedTime(&Proc[0]);
	PrintProcess(&Proc[0]);
	int finishALL = 0;
	int CurrentTime = 0;
	int i = 0;
	while (finishALL < N)
	{
		if (CurrentTime > Proc[0].arriveTime && finishALL == 0)
		{
			CurrentTime = Proc[0].arriveTime;
			Proc[0].startTime = Proc[0].arriveTime;
			Proc[0].finishTime = CurrentTime + Proc[0].runTime;
			CurrentTime = CurrentTime + Proc[0].runTime;
			Proc[0].isfinished = 1;
			finishALL++;
			i++;
		}
		else if (CurrentTime > Proc[i].arriveTime && finishALL > 0)
		{
			//num��ͳ�Ƶ�ǰ��ִ�н��̵ĸ���
			int num = 0;
			//��num=1
			int temp;
			for (int j = 0; j < N; j++)
			{
				if (Proc[j].isfinished == 1)
				{
					continue;
				}
				if (CurrentTime >= Proc[j].arriveTime)
				{
					num++;
					temp = j;
				}
			}
			if (num == 1)
			{
				//CurrentTime = Proc[temp].arriveTime;
				Proc[temp].startTime = CurrentTime;
				Proc[temp].finishTime = CurrentTime + Proc[temp].runTime;
				Proc[temp].isfinished = 1;
				finishALL++;
				i++;
			}
			else if (num > 1)
			{
				int minProcess = 0;
				int k;
				//�ҳ���ǰ����ʱ����̵Ľ���
				for (k = 0; k < N; k++)
				{
					if (Proc[k].isfinished == 1)
					{
						continue;
					}
					else
					{
						if (Proc[k].runTime < Proc[minProcess].runTime)
						{
							minProcess = k;
						}
					}
				}
				//CurrentTime = CurrentTime+Proc[k].runTime;
				Proc[minProcess].startTime = CurrentTime;
				Proc[minProcess].finishTime = CurrentTime + Proc[minProcess].runTime;
				CurrentTime = Proc[minProcess].finishTime;
				Proc[minProcess].isfinished = 1;
				finishALL++;
			}
		}
		else
		{
			CurrentTime++;
		}
	}

	//���ս��̿�ʼ����ʱ�����򲢴�ӡ���
	SortedByStartTime(&Proc[0]);
	PrintProcess(&Proc[0]);
}
*/