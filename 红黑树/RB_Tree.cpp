typedef enum{RED = 0,BLACK = 1} ColorType;
typedef int KeyType;
typedef struct rb_node
{
	rb_node *leftchild;
	rb_node *parent;
	rb_node *rightchild;
	ColorType color;
	KeyType key;
}rb_node;
typedef struct
{
	rb_node *head;
	rb_node *Nil;
	int cursize;
}RBTree;
rb_node * Buynode(rb_node *pa = NULL,ColorType color = RED)
{
	rb_node *s = (rb_node*)malloc(sizeof(rb_node));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(rb_node));
	s->parent = pa;
	s->color = color;
	return s;
}
void Freenode(rb_node *p)
{
	free(p);
}

rb_node * FindValue(RBTree *ptree,KeyType kx)
{
	rb_node *ptr = NULL;
	if(ptree == NULL || ptree->head == NULL)
		return ptr;
	ptr = ptree->head->parent;
	while(ptr != ptree->Nil  && ptr->key != kx)
	{
		ptr = kx < ptr->key? ptr->leftchild:ptr->rightchild;
	}
	return ptr;
}
rb_node * Search(RBTree *ptree,rb_node *ptr,KeyType kx)
{
	if(ptr == ptree->Nil  || ptr->key == kx) 
		return ptr;
	else if(kx < ptr->key) 
		return Search(ptree,ptr->leftchild,kx);
	else 
		return Search(ptree,ptr->rightchild,kx);
}
AVLNode * SearchValue(RBTree *ptree,KeyType kx)
{
	if(ptree == NULL || ptree->head == NULL)
		return NULL;
	else
		return Search(ptree,ptree->head->parent,kx);
}

void RotateLeft(RBTree *ptree,rb_node *ptr)
{
	rb_node *newroot = ptr->rightchild;
	newroot->parent = ptr->parent;//1
	ptr->rightchild = newroot->leftchild;
	if(newroot->leftchild != ptree->Nil)
	{
		newroot->leftchild->parent = ptr;
	}
	newroot->leftchild = ptr;
	if(ptree->head->parent == ptr)
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
	ptr->parent = newroot;
}

void RotateRight(RBTree *ptree, rb_node *ptr)
{
	rb_node *newroot = ptr->leftchild;
	newroot->parent = ptr->parent;//1
	ptr->leftchild = newroot->rightchild;
	if(newroot->rightchild != ptree->Nil)
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

void Insert_Item(RBTree *ptree,rb_node *pa,KeyType kx)
{
	rb_node *s = Buynode(pa,RED);
	s->key = kx;
	s->leftchild = ptree->Nil;
	s->rightchild = ptree->Nil;
	
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
	rb_node *_X = s;
	rb_node *_Y = NULL;
	for(;_X != ptree->head->parent && _X->parent->color == RED;)
	{
		if(_X->parent == _X->parent->parent->rightchild) // right
		{
			_Y = _X->parent->parent->leftchild;
			if(_Y->color == RED)
			{
				_Y->color = BLACK;
				_X->parent->color = BLACK;
				_X->parent->parent->color =RED;
				_X = _X->parent->parent;
			}
			else
			{
				if(_X == _X->parent->leftchild)
				{
					_X = _X->parent;
					RotateRight(ptree,_X);
				}
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				RotateLeft(ptree,_X->parent->parent);
			}
		}
		else // left
		{
			_Y = _X->parent->parent->rightchild;
			if(_Y->color == RED)
			{
				_Y->color = BLACK;
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				_X = _X->parent->parent;
			}
			else
			{
				if(_X == _X->parent->rightchild)
				{
					_X =_X->parent;
					RotateLeft(ptree,_X);
				}
				_X->parent->color = BLACK;
				_X->parent->parent->color = RED;
				RotateRight(ptree,_X->parent->parent);
			}
		}
	}
	ptree->head->parent->color = BLACK;
}
bool Insert(RBTree *ptree,KeyType kx)
{
	if(ptree == NULL || ptree->head == NULL)
		return false;
	if(ptree->head->parent == ptree->Nil ) // root
	{
		rb_node *s = Buynode(ptree->head,BLACK);
		s->key = kx;
		s->leftchild = ptree->Nil;
		s->rightchild = ptree->Nil;
		ptree->head->parent = s;
		ptree->head->leftchild = s;
		ptree->head->rightchild = s;
		ptree->cursize = 1;
		return true;
	}
	
	rb_node *pa = ptree->head; // head
	rb_node *p = pa->parent; // root
	while(p != ptree->Nil  && p->key != kx)
	{
		pa = p;
		p = kx <p->key? p->leftchild:p->rightchild;
	}
	if(p != ptree->Nil  && p->key == kx) return false;

	Insert_Item(ptree,pa,kx);
	ptree->cursize+=1;
	return true;
}

///
void InOrder(rb_node *ptr)
{
	if(ptr != NULL)
	{
		InOrder(ptr->leftchild);
		cout<<ptr->key<<" ";
		InOrder(ptr->rightchild);
	}
}
//
void InOrder(RBTree *ptree)
{
	if(ptree != NULL && ptree->head != NULL)
	{
		InOrder(ptree->head->parent);
	}
	cout<<endl;
}

rb_node * Min(RBTree *ptree)
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
rb_node * Max(RBTree *ptree)
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
rb_node * Next(RBTree *ptree,rb_node *ptr)
{
	if(ptr == NULL || ptr == ptree->head)
	{
		return ptree->head;
	}
	if(ptr->rightchild != ptree->Nil)
	{
		ptr = ptr->rightchild;
		while(ptr->leftchild != ptree->Nil)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}else
	{
		rb_node *pa = ptr->parent;
		while(pa != ptree->head && pa->leftchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		return pa;
	}
}
rb_node * Prev(RBTree *ptree, rb_node *ptr)
{
	if(ptr == NULL || ptr == ptree->head)
	{
		return ptree->head;
	}
	if(ptr->leftchild != ptree->Nil)
	{
		ptr = ptr->leftchild;
		while(ptr->rightchild != Nil)
		{
			ptr = ptr->rightchild;
		}
		return ptr;
	}
	else
	{
		rb_node *pa = ptr->parent;
		while(pa != ptree->head && pa->rightchild != ptr)
		{
			ptr = pa;
			pa = pa->parent;
		}
		return pa;
	}
}
void NiceInOrder(RBTree *ptree)
{
	for(rb_node *p = Min(ptree); 
		p != NULL && p != ptree->head;
		p = Next(ptree,p))
	{
		cout<<p->key<<" ";
	}
	cout<<endl;
}
void ResNiceInOrder(RBTree *ptree)
{
	for(rb_node *p = Max(ptree);
		p != NULL && p != ptree->head;
		p = Prev(ptree,p))
	{
		cout<<p->key<<" ";
	}
	cout<<endl;
}
bool Remove(RBTree *ptree, KeyType kx)
{
// 同学们自己完成

}
void Init_RBTree(RBTree *ptree)
{
	if(ptree == NULL) exit(1);
	ptree->Nil = Buynode(NULL,BLACK);
	ptree->head = Buynode(ptree->Nil,RED);
	ptree->head->leftchild = ptree->Nil;
	ptree->head->rightchild = ptree->Nil;
	ptree->cursize = 0;
}

int main()
{
	RBTree myt;
	Init_RBTree(&myt);
	return 0;
}