 #define _CRT_SECURE_NO_WARNINGS 1

#include<utility>
#include<vector>
#include<iostream>
using namespace std;

//��ɢ��
//��ϣ���д�Ž��ָ��
//ÿһ����ϣ���λ�ö���һ��������
//���Բ�����ͬ��ϣλ�õ����ݶ������ͬһ����������

//ǰ������
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
		//next��Ϊ��
		if (_node->_next)
			_node = _node->_next;
		//�������ߵ���
		else
		{
			//�ҵ���һ���ǿ������ͷ���
			// 1. ��λ��ǰ�ڵ��ڹ�ϣ���е�λ��
			//kov: ��ȡvalue��key
			keyofValue kov;
			size_t idx = kov(_node->_data) % _pht->_ht.size();

			// 2. �ӱ��е���һ��λ�ÿ�ʼ���ҵ�һ���ǿ������ͷ���
			++idx;
			for (; idx < _pht->_ht.size(); ++idx)
			{
				if (_pht->_ht[idx])
				{
					_node = _pht->_ht[idx];
					break;
				}
			}
			// 3. �ж��Ƿ��ҵ�һ���ǿյ�ͷ���
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

	//����������Ϊ��Ԫ��
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
		//��һ���ǿ�����ͷ�ڵ�
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
		//�������
		checkCapacity();
		//�õ�V��K������λ��
		keyofValue kov;
		int idx = kov(data) % _ht.size();

		//�жϵ�ǰ��ϣͰ�Ƿ����K�ظ���Ԫ��
		Node* cur = _ht[idx];//�õ�ͷ�ڵ�
		while (cur != NULL)
		{
			if (kov(cur->_data) == kov(data))
				return false;
			cur = cur->_next;
		}
		//K���ظ���ͷ��
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
			//����
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
				//ԭ����Ͱ��Ϊ��
				_ht[i] = nullptr;
			}
			swap(_ht, newht);
		}
	}

	Node* find(const V& data)
	{
		keyofValue kov;
		int idx = kov(data) % _ht.size();//����λ��
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
				//ɾ���ýڵ�
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
			//����
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
				//ԭ����Ͱ��Ϊ��
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