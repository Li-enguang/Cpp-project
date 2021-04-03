
//FCFS.h
#ifndef SUANFA_H_
#define SUANFA_H_

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include<string>
#include <queue>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define T 2

using namespace std;
//��ҵ�ṹ��
typedef struct PCB
{
	string ID;							//��ʶ��
	double ComeTime;					//����ʱ��
	double ServerTime;					//����ʱ��
	double FinishTime;					//���ʱ��
	double TurnoverTime;				//��תʱ��
	double WeightedTurnoverTime;	//��Ȩ��תʱ��
	int pro=1;//���ȼ�
}PCB;

void sjp(int n);
void menu();
/*
�������ܣ�������ҵ��Ϣ
����˵����
PCBList		std::vector<PCB>&		PCB����
*/
void InputPCB(vector<PCB>& PCBList);

/*
�������ܣ�FCFS�㷨
����˵����
PCBList		std::vector<PCB>&		PCB��
*/
void FCFS(vector<PCB>& PCBList);

/*
�������ܣ���ʾ���
����˵����
PCBList		std::vector<PCB>&		PCB��
*/
void show(vector<PCB>& PCBList);

void SJF(vector<PCB> &PCBList);

void RR();

//չʾ�����PCB
void showinput(vector<PCB>& PCBList);

/*
�������ܣ��ȽϺ���������sort()����ComeTime��������
����˵����
p1			const PCB&				PCB
p2			const PCB&				PCB
*/
bool cmp(const PCB& p1, const PCB&  p2);
bool cmp_pripo(const PCB& p1, const PCB&  p2);

#endif
