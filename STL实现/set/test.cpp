#define _CRT_SECURE_NO_WARNINGS 1

#include<set>
#include<iostream>
#include<functional>
using namespace std;

template<class T,class cmp>
void printset(set<T,cmp>& s)
{ 
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}


void test2()
{
	set<int> s;
	pair<set<int>::iterator,bool> kv =s.insert(1);
	auto it = kv.first;
	cout << *it;
	s.insert(2);
	s.insert(3);
}
void test()
{
	set<int> s1;

	int arr[] = { 8,6,3,1,2,3,4,12,5,6,7 };
	int len = sizeof(arr) / sizeof(arr[0]);
	set<int,greater<int>> s2(arr, arr + len,greater<int>());
	printset(s2);

	set<int, greater<int>>::reverse_iterator rit = s2.rbegin();
	while (rit!=s2.rend())
	{
		//set 不能修改内容
		//*rit = 1;
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	set<int,greater<int>> s3(s2);
	printset(s3);

	set<int, less<int>> s4(arr, arr + len, less<int>());
	printset(s4);
}

int main()
{
	test2();
	system("pause");
	return 0;
}