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

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTnode* BTcreat(BTdatatype* array,int* idx);

// 二叉树前序遍历 
void BTPrevOrder(BTnode* root);

// 二叉树中序遍历 
void BTInOrder(BTnode* root);

// 二叉树后序遍历
void BTPostOrder(BTnode* root);

// 层序遍历 
void BTLevelOrder(BTnode* root);

// 二叉树节点个数
int BTSize(BTnode* root); 

// 二叉树叶子节点个数 
int BTLeafSize(BTnode* root);

// 二叉树销毁
void BTDestory(BTnode** root);

// 二叉树第k层节点个数 
int BTLevelKSize(BTnode* root, int k);

// 二叉树查找值为x的节点 
BTnode* BTFind(BTnode* root, BTdatatype x);

// 判断二叉树是否是完全二叉树 
int BTComplete(BTnode* root);
