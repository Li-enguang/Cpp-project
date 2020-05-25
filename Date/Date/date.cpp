#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

class date
{
public:
	date(int year = 1, int month = 1,int day = 1)
	{
		if (year > 0 && month > 0 && month < 13 && day <= getday(year,month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
	}
	int getday(int year,int month)
	{
		static int arr[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		int day = arr[month];
		if (month==2&&((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			day++;
		}
		return day;
    }

	date& operator+=(int day)
	{
		_day += day;
		while (_day > getday(_year, _month))
		{
			_day = _day - getday(_year, _month);
			_month++;
			if (_month == 13)
			{
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	date& operator-=(int day)
	{
		_day -= -day;
		//while (_day < getday(_year, _month)&&_day>0)
		while(_day<=0)
		{
			_day += getday(_year, _month);
			_month--;
			if (_month == 0)
			{
				_month = 12;
				_year--;
			}
		}
		return *this;

	}
	//前置++ 先++，再返回
	date& operator++()
	{
		return *this+=1;

	}

	//后置++  返回的++前的值
	date operator++(int)
	{
		date ret = date(*this);
		*this += 1;
		return ret;
	}
	void print()
	{
		cout << _year << " " << _month << " " << _day << " " << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void test1()
{
	int a = 0; int b = 0; int c = 0; int num = 0;
	cout << "请输入年月日" << endl;
	cin >> a >> b >> c;
	//date d1(2020,5,20);
	date d1(a, b, c);
	d1.print();
	cout << "请输入加的天数" << endl;
	cin >> num;
	if (num > 0)
	{
		cout << "最终结果为：" << endl;
		d1 = d1.operator+=(num);
		d1.print();
	}
	if (num < 0)
	{
		cout << "最终结果为：" << endl;
		d1 = d1.operator-=(num);
		d1.print();
	}
}

void test2()
{
	int a = 0; int b = 0; int c = 0; int num = 0;
	cout << "请输入年月日" << endl;
	cin >> a >> b >> c;
	//date d1(2020,5,20);
	date d1(a, b, c);
	d1.print();
	++d1;
	//d1.operator++();
	d1.print();
	//测试返回值
	//date ret=d1.operator++(0);
	date ret = d1++;
	ret.print();
}

int main()
{
	test1();
    test2();
	return 0;
}