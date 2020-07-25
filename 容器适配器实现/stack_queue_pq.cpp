#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<deque>
#include <list>
#include<vector>

using namespace std;

template<class T,class Container=deque<T>>
class Stack
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}
	void pop()
	{
		_c.pop_back();
	}
	size_t size() 
	{
		return _c.size();
	}
	const T& top() 
	{
		return _c.back();
	}
	bool empty()
	{
		return _c.empty();
	}
private:
	Container _c;
};

template<class T, class Container = deque<T>>
class Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}
	void pop()
	{
		_c.pop_front();
	}
	size_t size()
	{
		return _c.size()+1;
	}
	const T& back()
	{
		return _c.back();
	}
	const T& front()
	{
		return _c.front();
	}
	bool empty()
	{
		return _c.empty();
	}
private:
	Container _c;
};

class Date
{
public:
	Date(int y,int m,int d)
		:_y(y),
		_m(m),
		_d(d)
	{}
	bool operator >(const Date& d) const
	{
		if (_y > d._y)
		{
			return true;
		}
		else if (_y == d._y)
		{
			if (_m > d._m)
				return true;
			else if (_m == d._m)
			{
				if (_d > d._d)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		return false;
	}
	bool operator <(const Date& d) const
	{
		if (_y < d._y)
		{
			return true;
		}
		else if (_y == d._y)
		{
			if (_m < d._m)
				return true;
			else if (_m == d._m)
			{
				if (_d < d._d)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		return false;
	}
friend ostream& operator<<(ostream& cout,const Date& d)
	{
	cout << d._y << " " << d._m << " " << d._d << " ";
	cout << endl;
	return cout;
	}
private:
	int _y;
	int _m;
	int _d;
};

template<class T>
struct Greater //Ð¡¶Ñ
{
	bool operator()(const T& a, const T& b) const
	{
		return a > b;
	}
};
template<class T>
struct Less //´ó¶Ñ
{
	bool operator()(const T& a, const T& b) const
	{
		return a < b;
	}
};

template<class T,class Compare=Greater<T>,class Container=vector<T>>
class Priority_Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}
	void pop()
	{
		swap(_c[0],_c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}
	const T& top()
	{
		return _c.front();
	}
	size_t size()
	{
		return _c.size();
	}
	bool empty()
	{
		return _c.empty();
	}
private:
	void shiftDown(int partent)
	{
		int child = 2 * partent + 1;
		while (child < _c.size())
		{
			if ((child + 1) < size() &&_cmp(_c[child],_c[child + 1]))
			{
				++child;
			}
			if (_cmp(_c[partent],_c[child]))
			{
				swap(_c[child], _c[partent]);
				partent = child;
				child = 2 * partent + 1;
			}
			else
				break;
		}
	}
	void shiftUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child>0)
		{
			if (_cmp(_c[parent],_c[child]))
			{
				swap(_c[child], _c[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	Container _c;
	Compare _cmp;
};
void test1()
{
	Stack<int,deque<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	while (!st.empty())
	{
		cout<<st.top();
		//cout << endl;
		st.pop();
	}
}
void test2()
{
	Queue<int> qu;
	qu.push(1);
	qu.push(2);
	qu.push(3);
	qu.push(4);
	while (!qu.empty())
	{
		cout << qu.front();
		qu.pop();
	}
}

void test3()
{
	Priority_Queue<int,Less<int>> pq;
	//pq.push(10);
	//pq.push(1);
	//pq.push(12);
	//pq.push(50);
	//pq.push(5);
	//pq.push(100);
	int n = 100;
	for (n = 0; n < 100; n++)
	{
		pq.push(n);
	}
	while (!pq.empty())
	{
     cout << pq.top()<<" ";
	 pq.pop();
	}
	
}
void test4()
{
	Priority_Queue<Date,Greater<Date>,deque<Date>> da;
	da.push(Date(2020, 1, 5));
	da.push(Date(2010, 1, 5));
	da.push(Date(2015, 11, 5));
	da.push(Date(2022, 7, 5));
	da.push(Date(2020, 2, 5));
	while (!da.empty())
	{
		cout << da.top();
		da.pop();
	}
}
int main()
{
	//test2();
	//test1();
	//test3();
	test4();
}