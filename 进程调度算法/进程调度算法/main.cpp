#define _CRT_SECURE_NO_WARNINGS 1

//main.cpp
#include "suanfa.h"
void menu()
{
	do {
		cout << endl << endl << "欢迎使用本系统,即将为您播放歌曲‘星河-曹思义’" << endl << endl;
		cout << "本系统模拟实现三种调度算法" << endl << endl;
		cout << "调度算法分别为 FCFS RR SJF" << endl << endl;
		cout << "为方便处理，进程信息需要由用户给定" << endl << endl;
		//cout << "温馨提示:操作需要Enter进行确认" << endl << endl;
		cout << "按下ESC可随时退出本系统" << endl << endl;
		cout << "请按下Enter确认进入本系统" << endl << endl;
	} while (_getch() != 13);
	system("cls");
}


int main()
{
	mciSendString(TEXT("open thebk.mp3 alias bk"), NULL, 0, NULL);
	mciSendString(TEXT("play bk repeat"), NULL, 0, NULL);
	vector<PCB> PCBList;

	menu();
	//输入作业信息
	InputPCB(PCBList);

	do{
		system("cls");
		cout << endl << "本次进程总数为:  " << PCBList.size() << endl << endl;
		showinput(PCBList);
		cout << "请选择本次使用的调度算法" << endl<<endl;
		cout << "可选择算法: FCFS RR SJF" << endl<<endl;
		cout << "提示: 大小写均可 " << endl<<endl;
		cout<<" 按下Enter确认进入下一步" << endl;
		string str;
		cin >> str;
		if (str == "fcfs"||str=="FCFS")
		{
			vector<PCB> temp = PCBList;
			//FCFS算法
			FCFS(temp);
			cout << "使用FCFS算法运作结果如下" << endl << endl;

			//显示结果
			show(temp);
		}
		if (str == "RR" || str == "rr")
		{
			
			system("cls");
			//RR算法
			RR();
			//cout << "使用RR算法运作结果如下" << endl << endl;

			//显示结果

		}
		if (str == "SJF" || str == "sjf")
		{
			vector<PCB> temp = PCBList;
			//SJF算法
			SJF(temp);
			cout << "使用SJF算法运作结果如下" << endl << endl;

			//显示结果
			show(temp);
		}
		else
			cout << "输入错误,本系统暂未收录该算法" << endl;
	} while (_getch() != 27);
	return 0;
}
