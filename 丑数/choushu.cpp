#define _CRT_SECURE_NO_WARNINGS 1
#include <functional>
#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;

int index = 500;
vector<int> result(index, 0);
void GetUglyNumber_Solution(int index) {
	if (index < 7) return;
	//vector<int> result(index, 0);
	result[0] = 1;
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < index; ++i) {
		int minNum = min(min(result[x] * 2, result[y] * 3), result[z] * 5);
		if (minNum == result[x] * 2) 
			x++;
		if (minNum == result[y] * 3) 
			y++;
		if (minNum == result[z] * 5) 
			z++;
		result[i] = minNum;
	}
	//return result[index - 1];
}
int main()
{
	GetUglyNumber_Solution(index);
	for (auto x : result)
	{
		cout << x << " ";
	}
	return 0;
}