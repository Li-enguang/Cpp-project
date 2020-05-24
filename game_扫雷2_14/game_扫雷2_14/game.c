#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void Initboard(char board[ROWS][COLS], int rows, int cols,char set) 
{
	
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}

	}
}

void displayboard(char show[ROWS][COLS], int row, int col)
{
	
	int i = 0;
	int j = 0;
	printf("\n  ");
	for(i=0;i<=row;i++)
	{
		printf("%d  ", i);	
	}
	printf("\n");
	printf("    ===========================\n");
	for (i = 1; i <=row; i++)
	{
		printf("%d ||", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c  ",show[i][j]);
		}
		printf("||");
		printf("\n");
	}
	printf("    ============================\n");

}
void setmine(char mine[ROWS][COLS], int row, int col,int count)
{
	
	system("cls");
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '0'+1;
			count--;
		}
		
	}

}
static int judgemine(char mine[ROWS][COLS], int x,int y,int* count1)
{
	(*count1)--;
		return
			((mine[x - 1][y] + mine[x - 1][y - 1] +
				mine[x][y - 1] + mine[x + 1][y - 1] +
				mine[x + 1][y] + mine[x + 1][y + 1] +
				mine[x][y + 1] + mine[x - 1][y + 1])-8*'0');
		

}
void Recursion(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int *count1)
{
	int res = judgemine(mine, x, y, count1);
	if (res == 0 && show[x][y] == '*')
	{
		show[x][y] = '0';
		int arr[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
		for (int i = 0; i < 8; ++i)
		{
			if (x + arr[i][0] >= 1 && x + arr[i][0] <= ROW && y + arr[i][1] >= 1 && y + arr[i][1] <= COL
				&& show[x + arr[i][0]][y + arr[i][1]] == '*')
				Recursion(mine, show, x + arr[i][0], y + arr[i][1], count1);
		}
	}
	else
		show[x][y] = res + '0';
}

void findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int  row, int col,int count)
{
	int x = 0;
	int y = 0;
	int count1 = ROW * COL-count;
	time_t start, end;
	start = time(NULL);
	while (count1)
	{
		
		printf("请输入要排查的坐标：\n");
		scanf("%d %d", &x, &y);
		system("cls");
		if (show[x][y] != '*')
		{
			printf("此坐标已经排查过，请重新输入！\n");
			displayboard(show, ROW, COL);
			continue;
		}
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '0' + 1)
			{
				printf("很遗憾，你被炸死了\n");
				displayboard(mine, ROW, COL);
				break;
			}
			else
			{
				Recursion(mine, show, x, y, &count1);
				//displayboard(mine, ROW, COL);
				displayboard(show, ROW, COL);
				
			}
		}
		else
		{
			printf("输入有误，请重新输入\n");

		}end = time(NULL);

}
	
	
	if (difftime(end, start)<=60&&count1 == 0)
	{
		printf("恭喜你排雷成功！\n");
		
		printf("用时：%d秒\n", (int)difftime(end, start));
	}
}