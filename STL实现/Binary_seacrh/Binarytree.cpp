#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

template<class T>
struct BsNode
{
public:
	BsNode(const T& val=T())
		:_data(val)
		, _left(nullptr)
		,_right(nullptr)
	{}
	T _data;
	BsNode<T>* _left;
	BsNode<T>* _right;
};

template<class T>
class Bstree
{
public:
	typedef BsNode<T> Node;

	Bstree()
		:_root(nullptr)
	{}

	Node* find(const T& val)
	{
		if (_root == nullptr) return _root;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data = val)
				return cur;
			else if (cur->_data > val)
			{
				cur = cur->_left;
			}
			else
				cur = cur->_right;
		}
		return nullptr;
	}

	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_data == val)
				return false;
			else if (cur->_data > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{ 
				parent = cur;
				cur = cur->_right;		
			}
		}
		cur = new Node(val);
		if (parent->_data > val)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
	}

	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	void _inorder(Node* cur)
	{
		if (cur)
		{
			_inorder(cur->_left);
			cout << cur->_data << " ";
			_inorder(cur->_right);
		}
	}

	bool erase(const T& val)
	{
		if (_root == nullptr)
			return false;
		//先找到这个节点和他的父节点
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (cur->_data == val) //找到这个点，退出循环
				break;
			else if (cur->_data > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		//循环走完，cur是空的，说明数据不存在
		if (cur == nullptr)
			return false;
		
		//下面开始删除、
		//1.删除一个叶子
		if (cur->_left == nullptr&&cur->_right == nullptr)
		{
			//是否为根节点
			if (cur != _root)
			{
				if (parent->_left == cur)
				{
					parent->_left = nullptr;
				}
				parent->_right = nullptr;
			}
			else
				_root = nullptr;
			delete cur;
		}
		//2.删除非叶子：左孩子不存在，右孩子存在
		else if (cur->_left == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				parent->_right = cur->_right;
			}
			else
				_root = cur->_right;
			delete cur;
		}

		//3.删除非叶子：右孩子不存在，左孩子存在
		else if (cur->_right == nullptr)
		{
			if (cur != _root)
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				parent->_right = cur->_left;
			}
			else
				_root = cur->_left;
			delete cur;
		}

		//4.删除非叶子，左右都存在
		else
		{
			Node* mostright; //左子树的最右节点
			mostright = cur->_left;
			parent = cur;

			while (mostright->_right)
			{
				parent = mostright;
				mostright = mostright->_right;
			}
			//找到了最右节点
			//待删除节点的值= 最右节点的值 ，删除最右节点
			cur->_data = mostright->_data;
			if (parent->_left == mostright)
			{
				parent->_left = mostright->_left;
			}
			else if (parent->_right == mostright)
			{
				parent->_right = mostright->_left;
			}
			delete mostright;
		}
		return true;
	}
private:
	Node* _root;
};

int main()
{
	Bstree<int> bst;
	bst.insert(0);
	bst.insert(5);
	bst.insert(7);
	bst.insert(3);
	bst.insert(1);
	bst.insert(8);
	bst.insert(6);
	bst.insert(2);

	bst.inorder();
	bst.erase(0);
	bst.inorder();
}