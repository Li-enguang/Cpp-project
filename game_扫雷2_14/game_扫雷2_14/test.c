#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
void menu()
{

	printf("***********************************\n");
	printf("***************1.play**************\n");
	printf("***************0.exit**************\n");
	printf("***********************************\n");

}
void game()
{
	int input = 0;
	printf("��ѡ���Ѷȣ�\n1.��\n2.����\n3.����\n");
	scanf("%d", &input);
	int count = input * EASY_COUNT; 
	//sprintf(stCmd, "mode con cols=%d lines=%d", a,b);
	//system(stCmd);
	char mine[ROWS][COLS];//����׵���Ϣ 
	char show[ROWS][COLS];//����Ų�����׵���Ϣ
	Initboard(mine, ROWS, COLS,'0');  //'0'
	Initboard(show, ROWS, COLS,'*');//'*'
	//displayboard(mine, ROW, COL);
	setmine(mine, ROW, COL,count);
	//displayboard(mine, ROW, COL);
	displayboard(show, ROW, COL);
	findmine(mine, show, ROW, COL,count);
}
void test()
{
	srand((unsigned int)time(NULL));
	int input = 0;	
	do
	{
	menu();
	printf("\n��ѡ��\n");
	scanf("%d", &input);
		switch (input) {
		case 1:game(); break;
		case 0:printf("�˳���Ϸ\n"); break;
		default:printf("������������������\n"); break;
		}
	} while (input);

}

int main()
{
	int a = 35; int b = 18;
	char stCmd[128];
	system("color 4A");
	system("mode con: cols=30 lines=12");
	printf("\n\n\n-----��ӭ����ɨ����Ϸ-----\n\n\n");
	printf("----------���Ժ�----------\n\n\n");
	Sleep(1000);
	system("cls");
	system("color 1A");
	sprintf(stCmd, "mode con cols=%d lines=%d", a, b);
	system(stCmd);
	test();
	return 0;
}