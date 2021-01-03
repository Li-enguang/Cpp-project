#define _CRT_SECURE_NO_WARNINGS 1

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
	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};

//less 建大堆，重载 <
template<class T>
struct Less 
{
	bool operator()(const T& left,const T& right)
	{
		return left < right;
	}
};

//greater 建小堆，重载 >
template<class T>
struct Greater
{
	bool operator()(const T& left, const T& right) 
	{
		return left > right;
	}
};

//less < 父节点 小于子节点 向下
template<class T,class Container=vector<T>, class Compare = Less<T>>
class priority_queue
{
public:
	priority_queue() //无参构造
	:_c()
	{}

	void shiftdown(int parent) //向下调整父节点 删除时
	{
		int child = parent * 2 + 1;
		while (child < size())
		{
			if(child + 1 < size()&&_com(_c[child],_c[child + 1]))
			//if (child+1<size()&&_c[child] < _c[child + 1])
				child++;
			if (_com(_c[parent],_c[child]))
			//if (_c[parent] < _c[child])
			{
				swap(_c[parent], _c[child]);
				parent = child;
				child= parent * 2 + 1;
			}
			else break;
		}
	}

	void shiftup(int child) //向上调整 插入时
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			if (_com(_c[parent] , _c[child]))
			//if (_c[parent] < _c[child])
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

	void push(const T& val) //队尾入队 尾插
	{
		_c.push_back(val);
		shiftup(size() - 1);
	}

	void pop() //队头出队 头删
	{
		swap(_c[0], _c[size() - 1]);
		_c.pop_back();
		shiftdown(0);
	}

	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}

	T& top() //堆顶元素
	{
		return _c.front();
	}

private:
	Container _c;
	Compare _com;
};
void test()
{
	//priority_queue<int> pq;
	priority_queue<int,vector<int>,Greater<int>> pq;
	pq.push(10);
	pq.push(2);
	pq.push(5);
	pq.push(8);
	pq.push(6);
	pq.push(46);
	pq.push(56);
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

void test2()
{
//	priority_queue<Date> q1;
	priority_queue<Date,vector<Date>,Greater<Date>> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2019, 10, 30));
	q1.push(Date(2019, 8, 30));
	q1.push(Date(2018, 3, 30));
	while (!q1.empty())
	{
		cout << q1.top() <<endl;
		q1.pop();
	}
	cout << endl;
}
int main()
{
	test2();
	return 0;
}