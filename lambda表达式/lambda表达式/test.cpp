#define _CRT_SECURE_NO_WARNINGS 1

#include <algorithm>
#include <functional>
#include<iostream>
#include<vector>
using namespace std;
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
	friend ostream& operator<<(ostream& _cout, const Date& d);
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

struct cmp
{
	bool operator()(Date& d1,Date& d2)
	{
		return d1 < d2;
	}
};
void test()
{
	int array[] = { 4,1,8,5,3,7,0,9,2,6 };

	// 默认按照小于比较，排出来结果是升序
	std::sort(array, array + sizeof(array) / sizeof(array[0]));

	// 如果需要降序，需要改变元素的比较规则
	std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
}

void test1()
{
	vector<Date> vc;
	vc.push_back(Date(2020, 11, 1));
	vc.push_back(Date(2018, 1, 11));
	vc.push_back(Date(2021, 11, 1));
	vc.push_back(Date(2022, 11, 1));
	
	sort(vc.begin(), vc.end(), [](Date& d1,Date& d2){
		return d1 < d2;
	});

	
	//sort(vc.begin(), vc.end());
	//sort(vc.begin(), vc.end(),cmp());
	cout << "less<Date>():" << endl;
	for (auto date : vc)
	{
		cout << date << endl;
	}

	sort(vc.begin(), vc.end(),greater<Date>());
	cout << "greater<Date>():" << endl;
	for (auto date : vc)
	{
		cout << date << endl;
	}
}

void test2()
{
	// 最简单的lambda表达式, 该lambda表达式没有任何意义
	[] {};

	// 省略参数列表和返回值类型，返回值类型由编译器推导为int
	int a = 3, b = 4;
	auto fun=[&a,&b]()mutable{
		a = 20;
		b = 30;
		return a + b;
	};
	cout << fun();
	cout << a << b;
	[=] {return a + 3; }; //值传递

	// 省略了返回值类型，无返回值类型
	auto fun1 = [&](int c) {b = a + c; };
	fun1(10);
	cout << a << " " << b << endl; //3 13
	// 各部分都很完善的lambda函数
	auto fun2 = [=, &b](int c)->int {return b += a + c; };
	cout << fun2(10) << endl; // 26
}

struct Add
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};
void test3()
{
	auto fun = [](int a,int b) {
		return a + b;
	};

	fun(10, 20);

	Add add;
	add(10, 20);
}
int main()
{
	test3();
	return 0;
}