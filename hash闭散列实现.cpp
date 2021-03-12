#define _CRT_SECURE_NO_WARNINGS 1

#include<utility>
#include<vector>
#include<iostream>
using namespace std;

enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template<class K, class V>
struct Node
{
public:
	pair<K, V> _kv= pair<K, V>();
	State _state= EMPTY;
};

template<class K,class V>
class HashTabke
{
public:
	typedef Node<K, V> Node;
	HashTabke(size_t n = 5)
		:_size(0)
	{
		_ht.resize(n);
	}
	bool insert(const pair<K,V>& kv)
	{
		//检查容量
		CheckCapacity();
		//哈希函数计算位置，这里用除留余数法
		int idx = kv.first%_ht.size();

		while (_ht[idx]._state == EXIST)
		{
			//如果存在看k是否相同
			if (_ht[idx]._state == EXIST && _ht[idx]._kv.first == kv.first)
				return false;
			//如果存在 但K不相同 继续++
			++idx;
			if (idx == _ht.size())
				idx = 0;
		}
		//状态为空或者删除
		_ht[idx]._kv = kv;
		_ht[idx]._state = EXIST;
		++_size;
		return true;
	}

	Node* find(const K& key)
	{
		int idx = key % _ht.size();
		while (_ht[idx]._state!=EMPTY)
		{
			if (_ht[idx]._state == EXIST && key == _ht[idx]._kv.first)
				return &_ht[idx];
			++idx;
			if (idx == _ht.size())
				idx = 0;
		}
		return nullptr;
	}

	bool erase(const K& key)
	{
		Node* cur = find(key);
		if (cur)
		{
			//删除 只修改状态 
			cur->_state = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	void CheckCapacity()
	{
		if (_ht.size() == 0 || _size * 10 / _ht.size() >= 7)
		{
			int newc = _ht.size() == 0 ? 5 : 2 * _ht.size();

			HashTabke<K, V> newht(newc);
			//遍历旧表
			for (int i = 0; i < _ht.size(); i++)
			{
				if (_ht[i]._state == EXIST)
				{
					newht.insert(_ht[i]._kv); //插入新表
				}
				swap(_ht, newht._ht);
			}
		}
	}

private:
	vector<Node> _ht;
	size_t _size;
};

void test()
{
	HashTabke<int, int> ht;
	ht.insert(make_pair(5, 5));
	ht.insert(make_pair(15, 15));
	ht.insert(make_pair(10, 10));
	ht.erase(5);
	ht.insert(make_pair(5, 5));

}

//int main()
//{
//	test();
//	return 0;
//}