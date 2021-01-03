#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>
using namespace std;

struct date
{
public:
	date(int y=1900,int m=1,int d=1)
		:_y(y)
		,_m(m)
		,_d(d)
	{}
	int _y;
	int _m;
	int _d;
};
template<class T>
struct ListNode
{
	ListNode(const T& val=T())
	{
		_data = val;
		_prev = nullptr;
		_next = nullptr;
	}
	T _data;
	ListNode<T>* _prev;
	ListNode<T>* _next; 
};

template<class T>
struct Listiterator
{
	typedef ListNode<T> Node;
	//封装一个节点
	Node* _node;
	Listiterator(Node* node)
		:_node(node)
	{}
	
	Listiterator(const Listiterator<T>& lit) //用一个迭代器构造另一个
		:_node(lit._node)
	{}

	T& operator*()
	{
		//cout << this->_node->_data;
		return _node->_data;
	}

	Listiterator<T>& operator++() //返回迭代器 前置++
	{
		_node = _node->_next;
		return *this;
	}

	Listiterator<T>& operator--() //返回迭代器 前置--
	{
		_node = _node->_prev;
		return *this;
	}

	Listiterator<T> operator++(int) //后置++ 因为后置++返回原来的迭代器
	{
		Listiterator<T> tmp(*this);//拷贝构造一个迭代器
		_node = _node->_next;
		return tmp;
	}

	bool operator!=(const Listiterator<T>& it)
	{
		return _node != it._node;
	}
	bool operator ==(const Listiterator<T>& it)
	{
		return _node == it._node;
	}
	T* operator ->() 
	{
		return &this->_node->_data;
	}
};

template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef Listiterator<T> iterator;
	typedef const Listiterator<T> const_iterator;
	List()
	{
		_header = new Node;
		_header->_prev = _header->_next = _header;
	}
	List(size_t n, const T& val = T()) 
	{
		_header = new Node;
		_header->_prev = _header->_next = _header;
		while (n--)
		{
			push_back(val);
		}
	}
	List(iterator first, iterator last)
	{
		_header = new Node;
		_header->_prev = _header->_next = _header;

		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	List(const List<T>& ls) //拷贝构造
	{
		_header = new Node;
		_header->_prev = _header->_next = _header;

		List<T> tmp(ls.begin(), ls.end()); //创建临时变量
		this->Swap(tmp);
	}

	List<T>& operator=(List<T> ls)
	{
		//ls.push_back(T());
		this->Swap(ls);
		return *this;
	}

	void clear()
	{
		iterator it = begin();
		while (it != end())
		{
			it=erase(it);
		}
	}

	void Swap(List<T>& ls) //交换两个对象的头
	{
		swap(this->_header, ls._header);
	}

	void push_back(const T& val)
	{
		insert(--begin(), val);
	}

	iterator insert(iterator pos,const T& val=T())
	{
		Node* prev = pos._node->_prev;
		Node* cur = new Node(val);

		cur->_next = pos._node;
		pos._node->_prev = cur;

		prev->_next = cur;
		cur->_prev = prev;
		return iterator(cur);
	}

	iterator erase(iterator pos) //返回下一个节点的位置
	{
		Node* next = pos._node->_next;

		pos._node->_prev->_next = next;
		next->_prev = pos._node->_prev;

		delete pos._node;
		return iterator(next);
	}

	//此处支持整形数据的打印
	void print()
	{
		Node* cur = _header->_next;
		while (cur!=_header)
		{
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}
	iterator begin()
	{
		return iterator(_header->_next);
	}
	iterator end()
	{
		return iterator(_header);
	}
	const_iterator begin() const
	{
		return const_iterator(_header->_next);
	}
	const_iterator end() const
	{
		return const_iterator(_header);
	}
	~List()
	{
		clear();
		delete _header;
		_header = nullptr;
	}
private:
	Node* _header;
};

void test2()
{
	cout << "创建一个date类型的对象ls：" << endl;
	List<date> ls(3);
	List<date>::iterator it = ls.begin();
	while (it != ls.end())
	{
		cout << it->_y << " " << it->_m << " " << it->_d;
		++it;
		cout << endl;
	}

	cout << "date类型：用ls拷贝构造ls2： " << endl;
	List<date> ls2(ls);
	List<date>::iterator it2 = ls2.begin();
	while (it2 != ls2.end())
	{
		cout << it2->_y << " " << it2->_m << " " << it2->_d;
		++it2;
		cout << endl;
	}

	cout << "date类型 :带参构造一个对象d1：" << endl;
	date d1(2, 2, 2);
	List<date> ls3(3,d1);
	it2 = ls3.begin();
	while (it2 != ls3.end())
	{
		cout << it2->_y << " " << it2->_m << " " << it2->_d;
		++it2;
		cout << endl;
	}

	cout << "date类型： 赋值运算符重载ls3=ls2：" << endl;
	ls3 = ls2;
	it2 = ls3.begin();
	while (it2 != ls3.end())
	{
		cout << it2->_y << " " << it2->_m << " " << it2->_d;
		++it2;
		cout << endl;
	}

	cout << "调用插入 ：" << endl;
	date d2(2020, 6, 18);
	ls3.insert(ls3.begin(),d2);
	ls3.insert(ls3.begin(),d1);
	ls3.insert(ls3.begin(),d1);
	ls3.erase(ls3.begin());
	it2 = ls3.begin();
	while (it2 != ls3.end())
	{
		cout << it2->_y << " " << it2->_m << " " << it2->_d;
		++it2;
		cout << endl;
	}
	ls3.clear();
	cout << "调用清空：" << endl;
	it2 = ls3.begin();
	while (it2 != ls3.end())
	{
		cout << it2->_y << " " << it2->_m << " " << it2->_d;
		++it2;
		cout << endl;
	}
}
void test1()
{
	List<date> d;
	d.push_back(date(2000,1,1));
	d.push_back(date(1,1,1));
	d.push_back(date(2,2,2));

	//d.push_back("1900")
	List<date>::iterator it = d.end();
	cout << it->_y << " " << it->_m << " " << it->_d;
	 it = ++d.begin();
	cout << it->_y << " " << it->_m << " " << it->_d;

	//while (it != d.end())
	//{
	//	//cout << (*it)._y << " "<<(*it)._m<<" "<<(*it)._d<<" ";
	//	cout << it->_y << " " << it->_m << " " << it->_d;
	//	cout << endl;
	//	++it;
	//}
}
void test()
{ 
	List<string> l;
	l.push_back("123");
	l.push_back("1230");
	l.push_back("1231");
	l.push_back("1233");
	List<string>::iterator it = l.begin();
	while (it != l.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << "清空后" << endl;
	l.clear();
	l.print();
}
int main()
{
	//List<int> lst;
	//lst.push_back(1);
	//lst.push_back(2);
	//lst.push_back(3);
	//lst.push_back(3);
	//lst.push_back(3);
	////lst.print();
	//List<int>::iterator it = lst.begin();
	//while (it!=lst.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	test2();
	return 0;
}