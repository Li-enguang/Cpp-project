#define _CRT_SECURE_NO_WARNINGS 1

#include<list>
#include<queue>
#include<deque>
#include<iostream>

using namespace std;

template<class T,class Container=deque<T>>
class Queue
{
public:
	void push(const T& x) //入队
	{
		lst.push_back(x);
	}
	void pop()//出队
	{
		lst.pop_front();
	}
	T& front()//队头
	{
		return lst.front();
	}
	T& back()
	{
		return lst.back();
	}
	bool empty()
	{
		return lst.empty();
	}
	size_t size() 
	{
		return lst.size();
	}
private:
	Container lst;
};
int main()
{
	Queue<int,list<int> > q;

	//Queue<int > q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	while (!q.empty())
	{
		cout << q.front()<<" ";
		q.pop();
	}
}