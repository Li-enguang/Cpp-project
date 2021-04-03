#define _CRT_SECURE_NO_WARNINGS 1

//�����ȷ����㷨

#include "suanfa.h"

void InputPCB(vector<PCB> &PCBList)
{
	do {
		PCB temp;
		cout << endl;
		cout << "�����ʶ��: ";
		cin >> temp.ID;
		cout << "���뵽��ʱ��: ";
	    cin >> temp.ComeTime;
		cout << "�������ʱ��: ";
		cin >> temp.ServerTime;
		//�������ȼ�
		srand((unsigned int)time(NULL));
		temp.pro = rand() % 5;
		PCBList.push_back(temp);

		cout << "�س��������룬������˳� "<<endl;
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
	sort(PCBList.begin(), PCBList.end(), cmp);		//����������ComeTime
	double FinishTime = -1;								//��һ����ҵ�����ʱ��
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		if ((*it).ComeTime < FinishTime)				//��ҵ����ʱ����һ����ҵ��û�н���
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
	sort(PCBList.begin(), PCBList.end(), cmp_pripo);		//�������������ȼ�
	double FinishTime = -1;								//��һ����ҵ�����ʱ��
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		if ((*it).ComeTime < FinishTime)				//��ҵ����ʱ����һ����ҵ��û�н���
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
	printf("�������ܽ�������\n");
	scanf("%d", &n);
	sjp(n);
}

void showinput(vector<PCB> &PCBList)
{
	cout.setf(ios::left);
	cout << endl<<"��ǰ����ӽ����� :  "<<PCBList.size()<<endl<<endl;
	cout << setw(20) << "��ʶ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ID;
	cout << endl << endl;

	cout << setw(20) << "����ʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ComeTime;
	cout << endl << endl;

	cout << setw(20) << "����ʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ServerTime;
	cout << endl << endl;

	cout << setw(20) << "ϵͳ��������ȼ�";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).pro;
	cout << endl << endl;
}

void show(vector<PCB> &PCBList)
{
	double SumTurnoverTime = 0;
	double SumWeightedTurnoverTime = 0;

	cout.setf(ios::left);
	//cout << endl<<"���ν�������Ϊ:  "<<PCBList.size()<<endl<<endl;
	cout << setw(20) << "��ʶ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ID;
	cout << endl<<endl;

	cout << setw(20) << "����ʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ComeTime;
	cout << endl << endl;

	cout << setw(20) << "����ʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).ServerTime;
	cout << endl << endl;

	cout << setw(20) << "���ʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		cout << setw(5) << (*it).FinishTime;
	cout << endl << endl;

	cout << setw(20) << "��תʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).TurnoverTime;
		SumTurnoverTime += (*it).TurnoverTime;;
	}
	cout << endl << endl;

	cout << setw(20) << "��Ȩ��תʱ��";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).WeightedTurnoverTime;
		SumWeightedTurnoverTime += (*it).WeightedTurnoverTime;;
	}
	cout << endl<<endl;

	cout << setw(20) << "ϵͳ��������ȼ�";
	for (vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		cout << setw(5) << (*it).pro;
	}
	cout << endl << endl;
	cout << "ƽ����תʱ��: " << SumTurnoverTime / PCBList.size() << endl << endl;
	cout << "ƽ����Ȩ��תʱ��: " << SumWeightedTurnoverTime / PCBList.size() << endl << endl;
}


bool cmp(const PCB &p1, const PCB &p2) //�Ƚϵ���ʱ��
{
	if(p1.ComeTime==p2.ComeTime)
		return p1.ServerTime < p2.ServerTime;
	return p1.ComeTime < p2.ComeTime;
}
bool cmp_pripo(const PCB &p1, const PCB &p2) //�Ƚ����ȼ�
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
