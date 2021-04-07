#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Hpdatatype;

typedef struct TheHeap
{
	Hpdatatype* _array;
	int _size;
	int _capacity;
}heap;

void hpcreat(heap* hp,Hpdatatype* array,int size);

void shiftdown(Hpdatatype* array,int size,int partent);

void  shiftup(Hpdatatype* array, int child);

void hppush(heap* hp, Hpdatatype data);

void hppop(heap* hp); // 仅支持删除栈顶元素

void Swap(Hpdatatype* array, int child, int partent);

void hpprint(heap* hp);