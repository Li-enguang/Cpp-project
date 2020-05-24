#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char BTdatatype;

typedef struct BTnode
{
	BTdatatype val;
	struct BTnode* left;
	struct BTnode* right;
}BTnode;

// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
BTnode* BTcreat(BTdatatype* array,int* idx);

// ������ǰ����� 
void BTPrevOrder(BTnode* root);

// ������������� 
void BTInOrder(BTnode* root);

// �������������
void BTPostOrder(BTnode* root);

// ������� 
void BTLevelOrder(BTnode* root);

// �������ڵ����
int BTSize(BTnode* root); 

// ������Ҷ�ӽڵ���� 
int BTLeafSize(BTnode* root);

// ����������
void BTDestory(BTnode** root);

// ��������k��ڵ���� 
int BTLevelKSize(BTnode* root, int k);

// ����������ֵΪx�Ľڵ� 
BTnode* BTFind(BTnode* root, BTdatatype x);

// �ж϶������Ƿ�����ȫ������ 
int BTComplete(BTnode* root);
