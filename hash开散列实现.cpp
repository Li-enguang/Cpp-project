 #define _CRT_SECURE_NO_WARNINGS 1

#include<utility>
#include<vector>
#include<iostream>
using namespace std;

//开散列
//哈希表中存放结点指针
//每一个哈希表的位置都是一个单链表
//所以产生相同哈希位置的数据都会放入同一个单链表中

//前置声明
template <class K, class V, class keyofValue>
class HashTable;

template<class K>
struct keyofValue
{
	const K& operator() (const K& data)
	{
		return data;
	}
};

template<class V>
struct HashNode
{
	V _data;
	HashNode<V>* _next;
	
	HashNode(const V& data=V())
		:_data(data),
		_next(nullptr)
	{}
};

template <class K,class V,class keyofValue>
struct HashIterator
{
	typedef HashNode<V> Node;
	typedef HashIterator<K,V,keyofValue> Self;

	typedef HashTable<K,V,keyofValue> Htable;

	Node* _node;
	Htable* _pht;

	HashIterator(Node* node, Htable* pht)
		:_node(node)
		,_pht(pht)
	{}

	V& operator*()
	{
		return _node->_data;
	}

	V* operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		//next不为空
		if (_node->_next)
			_node = _node->_next;
		//单链表走到空
		else
		{
			//找到下一个非空链表的头结点
			// 1. 定位当前节点在哈希表中的位置
			//kov: 获取value的key
			keyofValue kov;
			size_t idx = kov(_node->_data) % _pht->_ht.size();

			// 2. 从表中的下一个位置开始查找第一个非空链表的头结点
			++idx;
			for (; idx < _pht->_ht.size(); ++idx)
			{
				if (_pht->_ht[idx])
				{
					_node = _pht->_ht[idx];
					break;
				}
			}
			// 3. 判断是否找到一个非空的头结点
			if (idx >= _pht->_ht.size())
				_node = nullptr;
		}
		return *this;
	}
};

template<class K,class V,class keyofValue>
class HashTable
{
public:

	//迭代器声明为友元类
	template <class K, class V, class keyofValue>
	friend struct HashIterator;

	typedef HashNode<V> Node;
	typedef HashIterator<K, V, keyofValue> iterator;

	HashTable(size_t n = 10)
	{
		_ht.resize(n);
	}

	iterator begin()
	{
		//第一个非空链表头节点
		for (int i = 0; i < _ht.size(); i++)
		{
			if (_ht[i])
			{
				return iterator(_ht[i], this);
			}
		}
		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	bool insert(const V& data)
	{
		//检查容量
		checkCapacity();
		//拿到V的K，计算位置
		keyofValue kov;
		int idx = kov(data) % _ht.size();

		//判断当前哈希桶是否存在K重复的元素
		Node* cur = _ht[idx];//拿到头节点
		while (cur != NULL)
		{
			if (kov(cur->_data) == kov(data))
				return false;
			cur = cur->_next;
		}
		//K不重复，头插
		cur=new Node(data);
		cur->_next = _ht[idx];
		_ht[idx] = cur;

		++_size;
		return true;
	}
	void checkCapacity()
	{
		if (_ht.size() == _size)
		{
			//增容
			int newc = _ht.size() == 0 ? 10 : 2 * _size;
			vector<Node*> newht;
			newht.resize(newc);

			keyofValue kov;
			for (int i = 0; i < _ht.size(); ++i)
			{
				Node* cur = _ht[i];
				while (cur)
				{
					Node* next = cur->_next;
					int idx = kov(cur->_data) % newc;
					cur->_next = newht[idx];
					newht[idx] = cur;
					cur = next;
				}
				//原来的桶置为空
				_ht[i] = nullptr;
			}
			swap(_ht, newht);
		}
	}

	Node* find(const V& data)
	{
		keyofValue kov;
		int idx = kov(data) % _ht.size();//计算位置
		Node* cur = _ht[idx];
		while (cur)
		{
			if (cur->_data == data)
				return cur;
			cur = cur->_next;
		}
		return nullptr;
	}
	bool erase(const K& key)
	{
		int idx = key % _ht.size();
		keyofValue kov;
		Node* cur = _ht[idx];
		Node* prev = nullptr;
		while (cur)
		{
			if (kov(cur->_data) == key)
			{
				//删除该节点
				if (prev == nullptr)
					_ht[idx] = cur->_next;
				else
					prev->_next = cur->_next;
				delete cur;
				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}
	/*void checkCapacity()
	{
		if (_ht.size() == _size)
		{
			//增容
			int newc = _ht.size() == 0 ? 10 : 2 * _size;
			HashTable<K, V, keyofValue> newtable;
			for (int i = 0; i < _ht.size(); ++i)
			{
				Node* cur = _ht[i];
				while (cur)
				{
					Node* next = cur->_next;
					newtable.insert(cur->_data);
					delete cur;
					cur = next;
				}
				//原来的桶置为空
				_ht[i] = nullptr;
			}
			swap(_ht, newtable._ht);
		}
	}*/

private:
	vector<Node*> _ht;
	size_t _size = 0;
};

int main()
{
	HashTable<int, int, keyofValue<int>> hash;
	hash.insert(10);
	hash.insert(5);
	hash.insert(10);
	hash.insert(7);
	hash.insert(4);
	hash.insert(8);
	hash.insert(158);
	hash.insert(105);
	hash.insert(1);
	hash.insert(25);
	hash.insert(17);
	hash.insert(6);
	hash.insert(13);

	HashTable<int, int, keyofValue<int>>::iterator it = hash.begin();
	while (it != hash.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}