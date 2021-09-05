#define _CRT_SECURE_NO_WARNINGS 1
#include <functional>
#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
using namespace std;
void perm(int pos, vector<int> &num, vector<vector<int>> &all_result) {
	if (pos + 1 == num.size()) {
		// 一次全排列的结果
		all_result.push_back(num);
		return;
	}
	for (int i = pos; i < num.size(); ++i) {
		swap(num[pos], num[i]);
		perm(pos + 1, num, all_result);
		swap(num[pos], num[i]);
	}
}
int main() {
	vector<int> num = { 1, 2, 3 };
	vector<vector<int>> all_result;
	perm(0, num, all_result);
	for (auto& s : all_result)
	{
		for (auto& x : s)
			cout << x << " ";
		cout << endl;
	}
}
//int main()
//{
//	//vector<int> arr = { 1,2,3 };
//	string arr = "abc";
//	cout << "全排列如下:" << endl;
//	do {
//		cout << arr << endl;
//	} while (std::next_permutation(arr.begin(), arr.end()));
//	return 0;
//}