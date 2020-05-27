#define _CRT_SECURE_NO_WARNINGS 1

/*
*****此代码实现了一些日期类函数接口*******
*****给了几个测试用例，读者可以自行测试***
***** 此代码主要运用运算符重载 ***********
*****作者 ： Li-en-G  欢迎大家使用 *******
*/

#include<iostream>
using namespace std;

class date
{
public:

	//全缺省构造函数
	date(int year = 1, int month = 1, int day = 1)
	{
		if (year > 0 && month > 0 && month < 13 && day <= getday(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
	}

	//获取该月天数
	int getday(int year, int month)
	{
		static int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = arr[month];
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			day++;
		}
		return day;
	}

	//加上一个天数
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
	//减去一个天数
	date& operator-=(int day)
	{
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_month = 12;
				_year--;
			}
			_day += getday(_year, _month);
		}
		return *this;

	}

	int getyear_day(int year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			return 366;
		}
		return 365;
	}

	int getusedday(const date& date)
	{
		int num = 1;
		int day = 0;
		for(num;num<date._month;num++)
		{
			day = day + getday(date._year, num);
		}
		day = day + date._day;
		return day;
	}


	//计算两日期相差天数
	//版本一 ：
	/*int operator-(const date& d)
	{
		int day=0;
		date& a = *this;
		date b = d;
		if (b == a)
		{
			return day;
		}
		else if (a > b)
		{
			if (a._year == b._year)
			{
				return  getusedday(a)-getusedday(b);
			}
			else
			{
				int i = getyear_day(b._year) - getusedday(b);
				for (b._year=b._year+1; b._year <a._year; b._year++)
				{
					day = getyear_day(b._year) + day;
				}
				day = day + i + getusedday(a);
				return day;
			}
		}
		else if(b>a)
		{
			date tmp = a;
			a = b;
			b = tmp;
			a-b;
		}
	}*/

	//版本二 ： 代码复用
	int operator-(const date& d)
	{
		date& a = *this;
		date b = d;
		int num = 0;
		while (a > b)
		{
			--a;
			num++;
		}
		while (a < b)
		{
			--b;
			num++;
		}
		return num;
	}

	//前置++ 先++，再返回
	date& operator++()
	{
		return *this+=1;
	}

	//后置++  返回的++前的值
	date operator++(int)
	{
		date ret = *this;
		*this += 1;
		return ret;
	}

	//前置--
	date& operator--()
	{
		return *this -= 1;

	}
	//后置--
	date operator--(int)
	{
		date ret = *this;
		*this -= 1;
		return ret;
	}

	date operator+(int day)
	{
		date ret=*this;
		ret += day;
		return ret;
	}

	date operator-(int day)
	{
		date ret = *this;
		ret -= day;
		return ret;
	}

	//判断相等
	bool operator==(const date& date)
	{

		return _year == date._year&&_month == date._month&&_day == date._day;
	}

	//判断是否大于
	bool operator>(const date& date)
	{
		if (_year > date._year)
		{
			return true;
		}
		else if (_year == date._year)
		{
			if (_month > date._month)
			{
				return true;
			}
			else if (_month == date._month)
			{
				if (_day > date._day)
					return true;
			}
			else if (_month < date._month)
			{
				return false;
			}
		}
		return false;
	}

	bool operator>=(const date& date)
	{
		return (*this > date) || (*this == date);
	}

	bool operator<(const date& date)
	{
		return !(*this >= date);
	}

	bool operator<=(const date& date)
	{
		return !(*this > date);
	}

	bool operator!=(const date& date)
	{
		return !(*this == date);
	}

	void print()
	{
		cout << _year << " " << _month << " " << _day << " " << endl;
	}

	//输出重载
	friend ostream& operator<<(ostream& out, const date& date)
	{
	out << date._year<<" "<<date._month<<" "<<date._day<<endl;
	return out;
	}
	//输入重载
	friend istream& operator>>(istream& in, date& date)
	{
	in>> date._year >>date._month >>date._day;
	return in;
	}
	
private:
	int _year;
	int _month;
	int _day;
};

void test4()
{
	date d1(2021,4,23);
	date d2(2021,4, 21);
	cout << (d1 < d2);
	cout << (d1 <= d2);
	cout << (d1 >= d2);
	cout << (d1 > d2);
}
void test5()
{
	date d2(2021,5,27);
	date d1(2020,1,2);
	cout << (d1 - d2);

}
void test1()
{
	date d1;
	int num=0;
	cout << "请输入年月日" << endl;
	cin >> d1;
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
	date d1;
	int num = 0;
	cout << "请输入年月日" << endl;
	cin >> d1;
	++d1;
	cout << d1;
	cout << d1++;
	cout << d1;
}

void test3()
{
	date d3;
	cin >> d3;
	cout<<(d3 + 20);
	cout << d3;
}
int main()
{
	//test1();
    //test2();
	//test3();
	//test4();
	test5();
	return 0;
}