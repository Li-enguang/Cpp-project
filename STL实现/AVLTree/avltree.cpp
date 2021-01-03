#define _CRT_SECURE_NO_WARNINGS 1
//AVL�������������߶������� 1 ���� - ��
#include<iostream>
template<class T>
struct AVLtreeNode
{
	T _data;
	AVLtreeNode<T>* _left;
	AVLtreeNode<T>* _right;
	AVLtreeNode<T>* _parent;
	int _bf;//ƽ������

	AVLtreeNode(const T& val = T())
		:_data(val)
		, _left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
	{}
};

template<class T>
class AVLTree
{
public:
	typedef AVLtreeNode<T> Node;

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

	}
	bool insert(const T& val)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		
		//����
		while (cur)
		{
			if (cur->_data == val)
				return false;
			else if (cur->_data > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_data < val)
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		//����ڵ�
		cur = new Node(val);
		if (parent->_data > val)
			parent->_left = cur;
		parent->_right = cur;

		//�������ĸ��ڵ�
		cur->_parent = parent;

		while (parent)
		{
			if (cur == parent->_left) //�嵽����� bf--
				parent->_bf--;
			else  //�嵽�ұ��� bf++
				parent->_bf++;

			if (parent->_bf == 0)//˵��ĳһ�����������ˣ�����Ҫ�����������
				break;

			else if (parent->_bf == 1 || parent->_bf == -1) //��0 -��1 ���� 0 -��-1 ��������
			{
				cur = cur->_parent;
				parent = cur->_parent;
			}
			else // 2 / -2 ���е���
			{

			}
		}
	}
private:
	Node* _root;
};