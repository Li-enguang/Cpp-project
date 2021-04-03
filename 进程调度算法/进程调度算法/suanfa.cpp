#define _CRT_SECURE_NO_WARNINGS 1

//先来先服务算法

#include "suanfa.h"

void InputPCB(vector<PCB> &PCBList)
{
	do {
		PCB temp;
		cout << endl;
		cout << "输入标识符: ";
		cin >> temp.ID;
		cout << "输入到达时间: ";
	    cin >> temp.ComeTime;
		cout << "输入服务时间: ";
		cin >> temp.ServerTime;
		//给定优先级
		srand((unsigned int)time(NULL));
		temp.pro = rand() % 5;
		PCBList.push_back(temp);

		cout << "回车继续输入，任意键退出 "<<endl;
		int ans;
		ans=_getch();
		if (13== ans)
		{
			system("cls");
			showinput(PCBList);
			continue;
		}
		else if(ans==27)
			break;
	} while (true);
}


void FCFS(vector<PCB> &PCBList)
{
	sort(PCBList.begin(), PCBList.end(), cmp);		//按升序排列ComeTime
	double FinishTime = -1;								//上一个作业的完成时间
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		if ((*it).ComeTime < FinishTime)				//作业到达时，上一个作业还没有结束
			(*it).FinishTime = (*(it - 1)).FinishTime + (*it).ServerTime;
		else
			(*it).FinishTime = (*it).ComeTime + (*it).ServerTime;

		(*it).TurnoverTime = (*it).FinishTime - (*it).ComeTime;
		(*it).WeightedTurnoverTime = (double)(*it).TurnoverTime / (*it).ServerTime;
		FinishTime = (*it).FinishTime;
	}
}

void SJF(vector<PCB> &PCBList)
{
	sort(PCBList.begin(), PCBList.end(), cmp_pripo);		//按升序排列优先级
	double FinishTime = -1;								//上一个作业的完成时间
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		if ((*it).ComeTime < FinishTime)				//作业到达时，上一个作业还没有结束
			(*it).FinishTime = (*(it - 1)).FinishTime + (*it).ServerTime;
		else
			(*it).FinishTime = (*it).ComeTime + (*it).ServerTime;

		(*it).TurnoverTime = (*it).FinishTime - (*it).ComeTime;
		(*it).WeightedTurnoverTime = (double)(*it).TurnoverTime / (*it).ServerTime;
		FinishTime = (*it).FinishTime;
	}
}

void RR()
{
	int n;
	printf("请输入总进程数：\n");
	scanf("%d", &n);
	sjp(n);
}

void showinput(vector<PCB> &PCBList)
{
	cout.setf(ios::left);
	cout << endl<<"当前已添加进程数 :  "<<PCBList.size()<<endl<<endl;
	cout << setw(20) << "标识符";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ID;
	cout << endl << endl;

	cout << setw(20) << "到达时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ComeTime;
	cout << endl << endl;

	cout << setw(20) << "服务时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ServerTime;
	cout << endl << endl;

	cout << setw(20) << "系统分配的优先级";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).pro;
	cout << endl << endl;
}

void show(vector<PCB> &PCBList)
{
	double SumTurnoverTime = 0;
	double SumWeightedTurnoverTime = 0;

	cout.setf(ios::left);
	//cout << endl<<"本次进程总数为:  "<<PCBList.size()<<endl<<endl;
	cout << setw(20) << "标识符";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ID;
	cout << endl<<endl;

	cout << setw(20) << "到达时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ComeTime;
	cout << endl << endl;

	cout << setw(20) << "服务时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ServerTime;
	cout << endl << endl;

	cout << setw(20) << "完成时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).FinishTime;
	cout << endl << endl;

	cout << setw(20) << "周转时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).TurnoverTime;
		SumTurnoverTime += (*it).TurnoverTime;;
	}
	cout << endl << endl;

	cout << setw(20) << "带权周转时间";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).WeightedTurnoverTime;
		SumWeightedTurnoverTime += (*it).WeightedTurnoverTime;;
	}
	cout << endl<<endl;

	cout << setw(20) << "系统分配的优先级";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).pro;
	}
	cout << endl << endl;
	cout << "平均周转时间: " << SumTurnoverTime / PCBList.size() << endl << endl;
	cout << "平均带权周转时间: " << SumWeightedTurnoverTime / PCBList.size() << endl << endl;
}


bool cmp(const PCB &p1, const PCB &p2) //比较到达时间
{
	if(p1.ComeTime==p2.ComeTime)
		return p1.ServerTime < p2.ServerTime;
	return p1.ComeTime < p2.ComeTime;
}
bool cmp_pripo(const PCB &p1, const PCB &p2) //比较优先级
{
	if (p1.pro == p2.pro)
	{
		return p1.ServerTime < p2.ServerTime;
		if (p1.ServerTime == p2.ServerTime)
		{
			return p1.ComeTime < p2.ComeTime;
		}
	}
	return p1.pro < p2.pro;
}
