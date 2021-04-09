// AVL
#include<iostream>
#include<malloc.h>
using namesapce std;
typedef int KeyType;
typedef struct AVLNode
{
	AVLNode *leftchild;
	AVLNode *parent;
	AVLNode *rightchild;
	int balance; // right - left => 0 1 -1 
	KeyType key;
}AVLNode;
typedef struct
{
	AVLNode *head;
	int cursize;
}AVLTree;

AVLNode * Buynode()
{ 
	AVLNode *s = (AVLNode*)malloc(sizeof(AVLNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(AVLNode));
	return s;
}
void Freenode(AVLNode *p)
{
	free(p);
}

void Init_AVLTree(AVLTree *ptree)
{
	if(ptree == NULL) 
	{
		exit(1);
	}
	ptree->head = Buynode();
	ptree->cursize = 0;
}
AVLNode * FindValue(AVLTree *ptree,KeyType kx)
{
	AVLNode *ptr = NULL;
	if(ptree == NULL || ptree->head == NULL)
		return ptr;
	ptr = ptree->head->parent;
	while(ptr != NULL && ptr->key != kx)
	{
		ptr = kx < ptr->key? ptr->leftchild:ptr->rightchild;
	}
	return ptr;
}
AVLNode * Search(AVLNode *ptr,KeyType kx)
{
	if(ptr == NULL || ptr->key == kx) 
		return ptr;
	else if(kx < ptr->key) 
		return Search(ptr->leftchild,kx);
	else 
		return Search(ptr->rightchild,kx);
}
AVLNode * SearchValue(AVLTree *ptree,KeyType kx)
{
	if(ptree == NULL || ptree->head == NULL)
		return NULL;
	else
		return Search(ptree->head->parent,kx);
}

void RotateLeft(AVLTree *ptree,AVLNode *ptr)
{
	AVLNode *newroot = ptr->rightchild;
	newroot->parent = ptr->parent; //1
    ptr->rightchild = newroot->leftchild;
	if(newroot->leftchild != NULL)
	{
		newroot->leftchild->parent = ptr;
	}

    newroot->leftchild = ptr;
	if(ptree->head->parent == ptr) // root
	{
		ptree->head->parent = newroot;
	}
	else
	{
		if(ptr->parent->rightchild == ptr)
		{
			ptr->parent->rightchild = newroot;
		}
		else
		{
			ptr->parent->leftchild = newroot;
		}
	}
	ptr->parent = newroot; // 3
}

void RotateRight(AVLTree *ptree, AVLNode *ptr)
{
	AVLNode *newroot = ptr->leftchild;
	newroot->parent = ptr->parent;//1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != NULL)
	{
		newroot->rightchild->parent = ptr;
	}
	newroot->rightchild = ptr;
	if(ptree->head->parent == ptr) // root;
	{
		ptree->head->parent = newroot;
	}
	else
	{
		if(ptr->parent->leftchild == ptr)
		{
			ptr->parent->leftchild = newroot;
		}
		else
		{
			ptr->parent->rightchild = newroot;
		}
	}
	ptr->parent = newroot;// 3
}
void RightBalance(AVLTree *ptree,AVLNode *ptr)
{
	AVLNode *rightsub = ptr->rightchild, *leftsub = NULL;
	switch(rightsub->balance)
	{
	case 0: cout<<"Right already balance "<<endl; break;
	case 1: 
		ptr->balance = 0;
		rightsub->balance = 0;
		RotateLeft(ptree,ptr);
		break;
	case -1:
		leftsub = rightsub->leftchild;
		switch(leftsub->balance)
		{
		case 0: 
			ptr->balance = 0;
			rightsub->balance = 0;
			break;
		case 1:
			ptr->balance = -1;
			rightsub->balance = 0;
			break;
		case -1: 
			ptr->balance = 0;
			rightsub->balance = 1;
			break;
		}
		leftsub->balance = 0;
		RotateRight(ptree,rightsub);
		RotateLeft(ptree,ptr);
		break;
	}
}
void LeftBalance(AVLTree *ptree,AVLNode *ptr)
{
	AVLNode *leftsub = ptr->leftchild, *rightsub = NULL;
	switch(leftsub->balance)
	{
	case 0: cout<<"left already balance "<<endl; break;
	case -1:
		ptr->balance = 0;
		leftsub->balance = 0;
		RotateRight(ptree,ptr);
		break;
	case 1: 
		rightsub = leftsub->rightchild;
		switch(rightsub->balance)
		{
		case 0:
			ptr->balance = 0;
			leftsub->balance = 0;
			break;
		case 1:
			ptr->balance = 0;
			leftsub->balance = -1;
			break;
		case -1:
			ptr->balance = 1;
			leftsub->balance = 0;
			break;
		}
		rightsub->balance = 0;
		RotateLeft(ptree,leftsub);
		RotateRight(ptree,ptr);
		break;
	}
}

void Insert_Item(AVLTree *ptree,AVLNode *pa,KeyType kx)
{
	AVLNode *s = Buynode();
	s->parent = pa;
	s->key = kx;
	s->balance = 0;
	if(s->key < pa->key)
	{
		pa->leftchild = s;
		if(s->key < ptree->head->leftchild->key)
		{
			ptree->head->leftchild = s;
		}
	}
	else
	{
		pa->rightchild = s;
		if(s->key > ptree->head->rightchild->key)
		{
			ptree->head->rightchild = s;
		}
	}
	//////////////////////////////////////
	AVLNode *_X = s;
	AVLNode *_Y = s->parent;
	int tall = 1;
	for(;tall == 1 && _Y != ptree->head;)
	{
		if(_Y->rightchild == _X)
		{
			switch(_Y->balance)
			{
			case 0: _Y->balance = 1; break;
			case -1:
				_Y->balance = 0; 
				tall = 0;
				break;
			case 1: 
				RightBalance(ptree,_Y);
				tall = 0;
				break;
			}
		}
		else
		{
			switch(_Y->balance)
			{
			case 0: _Y->balance = -1; break;
			case 1: 
				_Y->balance = 0; 
				tall = 0;
				break;
			case -1:
				LeftBalance(ptree,_Y); 
				tall = 0;
				break;
			}
		}
		_X = _Y;
		_Y = _Y->parent;
	}
}
AVLNode * MakeRoot(KeyType kx)
{
	AVLNode *s = Buynode();
	s->key = kx;
        return s;
}
bool Insert(AVLTree *ptree,KeyType kx)
{
	if(ptree == NULL || ptree->head == NULL)
		return false;
	if(ptree->head->parent == NULL) // root
	{// 
		AVLNode *s = MakeRoot(kx);
		s->parent = ptree->head;
		ptree->head->parent = s;
		ptree->head->leftchild = s;
		ptree->head->rightchild = s;
		ptree->cursize = 1;
		return true;
	}
	
	AVLNode *pa = ptree->head; // head
	AVLNode *p = pa->parent; // root
	while(p != NULL && p->key != kx)
	{
		pa = p;
		p = kx <p->key? p->leftchild:p->rightchild;
	}
	if(p != NULL && p->key == kx) return false;

	Insert_Item(ptree,pa,kx);
	ptree->cursize+=1;
	return true;
}

void InOrder(AVLNode *ptr)
{
	if(ptr != NULL)
	{
		InOrder(ptr->leftchild);
		cout<<ptr->key<<" ";
		InOrder(ptr->rightchild);
	}
}
void InOrder(AVLTree *ptree)
{
	if(ptree != NULL && ptree->head != NULL)
	{
		InOrder(ptree->head->parent);
	}
	cout<<endl;
}

AVLNode * Min(AVLTree *ptree)
{
	if(ptree == NULL || ptree->head == NULL)
	{
		return NULL;
	}
	else
	{
		return ptree->head->leftchild;
	}
}
AVLNode * Max(AVLTree *ptree)
{
	if(ptree == NULL || ptree->head == NULL)
	{
		return NULL;
	}
	else
	{
		return ptree->head->rightchild;
	}
}
AVLNode * Next(AVLTree *ptree,AVLNode *ptr)
{
	if(ptr == NULL || ptr == ptree->head)
	{
		return ptree->head;
	}
	if(ptr->rightchild != NULL)
	{
		ptr = ptr->rightchild;
		while(ptr->leftchild != NULL)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}else
	{
		AVLNode *pa = ptr->parent;
		while(pa != ptree->head && pa->leftchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		return pa;
	}
}
AVLNode * Prev(AVLTree *ptree, AVLNode *ptr)
{
	if(ptr == NULL || ptr == ptree->head)
	{
		return ptree->head;
	}
	if(ptr->leftchild != NULL)
	{
		ptr = ptr->leftchild;
		while(ptr->rightchild != NULL)
		{
			ptr = ptr->rightchild;
		}
		return ptr;
	}
	else
	{
		AVLNode *pa = ptr->parent;
		while(pa != ptree->head && pa->rightchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		return pa;
	}
}
void NiceInOrder(AVLTree *ptree)
{
	for(AVLNode *p = Min(ptree); 
		p != NULL && p != ptree->head;
		p = Next(ptree,p))
	{
		cout<<p->key<<" ";
	}
	cout<<endl;
}
void ResNiceInOrder(AVLTree *ptree)
{
	for(AVLNode *p = Max(ptree);
		p != NULL && p != ptree->head;
		p = Prev(ptree,p))
	{
		cout<<p->key<<" ";
	}
	cout<<endl;
}
bool Remove(AVLTree *ptree, KeyType kx)
{
// 同学们自己完成
}
int main()
{
	KeyType ar[]={16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int n = sizeof(ar)/sizeof(ar[0]);
	AVLTree myt;
	KeyType kx = 12;
	Init_AVLTree(&myt);

	for(int i = 0;i<n;++i)
	{
		cout<<Insert(&myt,ar[i]);
	}
	cout<<endl;

	NiceInOrder(&myt);

	return 0;
}