
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
//作业结构体
typedef struct PCB
{
	string ID;							//标识符
	double ComeTime;					//到达时间
	double ServerTime;					//服务时间
	double FinishTime;					//完成时间
	double TurnoverTime;				//周转时间
	double WeightedTurnoverTime;	//带权周转时间
	int pro=1;//优先级
}PCB;

void sjp(int n);
void menu();
/*
函数功能：输入作业信息
参数说明：
PCBList		std::vector<PCB>&		PCB链表
*/
void InputPCB(vector<PCB>& PCBList);

/*
函数功能：FCFS算法
参数说明：
PCBList		std::vector<PCB>&		PCB链
*/
void FCFS(vector<PCB>& PCBList);

/*
函数功能：显示结果
参数说明：
PCBList		std::vector<PCB>&		PCB链
*/
void show(vector<PCB>& PCBList);

void SJF(vector<PCB> &PCBList);

void RR();

//展示输入的PCB
void showinput(vector<PCB>& PCBList);

/*
函数功能：比较函数，用于sort()，按ComeTime升序排列
参数说明：
p1			const PCB&				PCB
p2			const PCB&				PCB
*/
bool cmp(const PCB& p1, const PCB&  p2);
bool cmp_pripo(const PCB& p1, const PCB&  p2);

#endif
