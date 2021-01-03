#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<deque>

using namespace std;

template<class T,class Container=deque<T>>
class Stack
{
public:
	void push(const T& x)// ÈëÕ»
	{
		_v.push_back(x);
	}
	void pop()//³öÕ»
	{
		_v.pop_back();
	}
	T& top()//Õ»¶¥ÔªËØ
	{
		return _v.back();
	}
	bool empty()
	{
		return _v.empty();
	}
private:
	Container _v;
};

void test1()
{
	//Stack<char, vector<char>> s;
	Stack<char> s;
	s.push('1');
	s.push('2');
	s.push('3');
	s.push('4');
	s.push('5');
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

int main()
{
	test1();
	return 0;
}