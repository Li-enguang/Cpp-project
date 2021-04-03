#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>

using namespace std;

/*
短作业优先调度算法从就绪队列中选择一个估计运行时间最短的进程，
将处理机分配给它，使之立即执行，
直到完成或发生某事件而阻塞时，才释放处理机。
*/

//进程个数
const int N = 5;
//进程结构体
struct Process
{
	string name;//进程名
	int arriveTime;//进程到达时间
	int runTime;//进程运行时间
	int startTime;//进程开始时间
	int finishTime;//运行结束时间
	bool isfinished;//是否运行完成
};

//打印所有进程信息
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

//按照到达时间排序
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
//按照开始时间排序
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

	//按照进程到达时间排序并打印输出
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
			//num：统计当前可执行进程的个数
			int num = 0;
			//若num=1
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
				//找出当前运行时间最短的进程
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

	//按照进程开始运行时间排序并打印输出
	SortedByStartTime(&Proc[0]);
	PrintProcess(&Proc[0]);
}
*/