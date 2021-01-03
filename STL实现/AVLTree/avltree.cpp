#define _CRT_SECURE_NO_WARNINGS 1
//AVL树：左右子树高度相差不超过 1 （右 - 左）
#include<iostream>
template<class T>
struct AVLtreeNode
{
	T _data;
	AVLtreeNode<T>* _left;
	AVLtreeNode<T>* _right;
	AVLtreeNode<T>* _parent;
	int _bf;//平衡因子

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
		
		//搜索
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
		//插入节点
		cur = new Node(val);
		if (parent->_data > val)
			parent->_left = cur;
		parent->_right = cur;

		//更新他的父节点
		cur->_parent = parent;

		while (parent)
		{
			if (cur == parent->_left) //插到左边了 bf--
				parent->_bf--;
			else  //插到右边了 bf++
				parent->_bf++;

			if (parent->_bf == 0)//说明某一个子树补齐了，不需要更新上面的了
				break;

			else if (parent->_bf == 1 || parent->_bf == -1) //从0 -》1 或者 0 -》-1 继续更新
			{
				cur = cur->_parent;
				parent = cur->_parent;
			}
			else // 2 / -2 进行调整
			{

			}
		}
	}
private:
	Node* _root;
};