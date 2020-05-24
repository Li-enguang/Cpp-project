#define _CRT_SECURE_NO_WARNINGS 1

#include"BinaryTree.h"

//����
BTnode* BTcreat(BTdatatype* array,int* idx)
{
	if (array[*idx] != '#')
	{
		BTnode* root = (BTnode*)malloc(sizeof(BTnode));
		root->val=array[*idx];
		(*idx)++;
		root->left=BTcreat(array, idx);
		(*idx)++;
		root->right = BTcreat(array, idx);
		return root;
	}
	else
		return NULL;
}

//ǰ�����
void BTPrevOrder(BTnode* root)
{
	if (root)
	{
		printf("%c ", root->val);
		BTPrevOrder(root->left);
		BTPrevOrder(root->right);
	}
}

// ������������� 
void BTInOrder(BTnode* root)
{
	if (root)
	{
		
		BTInOrder(root->left);
		printf("%c ", root->val);
		BTInOrder(root->right);
	}

}

// �������������
void BTPostOrder(BTnode* root)
{
	if (root)
	{
		BTPostOrder(root->left);
		BTPostOrder(root->right);
		printf("%c ", root->val);
	}
}

//�������
void BTLevelOrder(BTnode* root)
{
	
	if (root)
	{
		printf("%c", root->val);
		BTnode* left = root->left;
		BTnode* right = root->right;
		BTLevelOrder(root->left);
		BTLevelOrder(root->right);
	}
}

//�ڵ����
int BTSize(BTnode* root)
{
	if (root == NULL)
		return 0;
	else
		return BTSize(root->left) + BTSize(root->right) + 1;
}

// ������Ҷ�ӽڵ���� 
int BTLeafSize(BTnode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL&&root->right==NULL)
	{
		return 1;
	}
	return BTLeafSize(root->left)+BTLeafSize(root->right);
	

}

// ����������
void BTDestory(BTnode** root)
{
	BTnode* cur = *root;
	if (cur)
	{
		BTDestory(&cur->left);
		BTDestory(&cur->right);
	}
	free(cur);
	*root = NULL;
}


// ��������k��ڵ���� 
int BTLevelKSize(BTnode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;

	return BTLevelKSize(root->left, k - 1) + BTLevelKSize(root->right, k - 1);

}

// ����������ֵΪx�Ľڵ� 
BTnode* BTFind(BTnode* root, BTdatatype x)
{
	BTnode* cur = NULL;
	if (root == NULL)
		return NULL;
	if (root->val == x)
	{
		cur = root;
		return cur;
	}
	BTFind(root->left, x);
	BTFind(root->right, x);
}

// �ж϶������Ƿ�����ȫ������ 
int BTComplete(BTnode* root)
{

}