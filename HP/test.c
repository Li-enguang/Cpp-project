#define _CRT_SECURE_NO_WARNINGS 1
#include"Hp.h"

int main()
{
	int array[] = {100,15,25,23,50,20,21,18,30,10,5};
	heap hp;
	hpcreat(&hp,array,sizeof(array)/sizeof(array[0]));
	hpprint(&hp);
	//hppush(&hp, 2);
	printf("\n");
	hppop(&hp);
	hpprint(&hp);
	return 0;
}