#define _CRT_SECURE_NO_WARNINGS 1

//main.cpp
#include "suanfa.h"
void menu()
{
	do {
		cout << endl << endl << "��ӭʹ�ñ�ϵͳ,����Ϊ�����Ÿ������Ǻ�-��˼�塯" << endl << endl;
		cout << "��ϵͳģ��ʵ�����ֵ����㷨" << endl << endl;
		cout << "�����㷨�ֱ�Ϊ FCFS RR SJF" << endl << endl;
		cout << "Ϊ���㴦��������Ϣ��Ҫ���û�����" << endl << endl;
		//cout << "��ܰ��ʾ:������ҪEnter����ȷ��" << endl << endl;
		cout << "����ESC����ʱ�˳���ϵͳ" << endl << endl;
		cout << "�밴��Enterȷ�Ͻ��뱾ϵͳ" << endl << endl;
	} while (_getch() != 13);
	system("cls");
}


int main()
{
	mciSendString(TEXT("open thebk.mp3 alias bk"), NULL, 0, NULL);
	mciSendString(TEXT("play bk repeat"), NULL, 0, NULL);
	vector<PCB> PCBList;

	menu();
	//������ҵ��Ϣ
	InputPCB(PCBList);

	do{
		system("cls");
		cout << endl << "���ν�������Ϊ:  " << PCBList.size() << endl << endl;
		showinput(PCBList);
		cout << "��ѡ�񱾴�ʹ�õĵ����㷨" << endl<<endl;
		cout << "��ѡ���㷨: FCFS RR SJF" << endl<<endl;
		cout << "��ʾ: ��Сд���� " << endl<<endl;
		cout<<" ����Enterȷ�Ͻ�����һ��" << endl;
		string str;
		cin >> str;
		if (str == "fcfs"||str=="FCFS")
		{
			vector<PCB> temp = PCBList;
			//FCFS�㷨
			FCFS(temp);
			cout << "ʹ��FCFS�㷨�����������" << endl << endl;

			//��ʾ���
			show(temp);
		}
		if (str == "RR" || str == "rr")
		{
			
			system("cls");
			//RR�㷨
			RR();
			//cout << "ʹ��RR�㷨�����������" << endl << endl;

			//��ʾ���

		}
		if (str == "SJF" || str == "sjf")
		{
			vector<PCB> temp = PCBList;
			//SJF�㷨
			SJF(temp);
			cout << "ʹ��SJF�㷨�����������" << endl << endl;

			//��ʾ���
			show(temp);
		}
		else
			cout << "�������,��ϵͳ��δ��¼���㷨" << endl;
	} while (_getch() != 27);
	return 0;
}
