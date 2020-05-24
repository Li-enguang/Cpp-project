#include <stdio.h>
void test() {
	static int i = 0; i++;
	printf("%d ", i);
} int main() 

{    
	 int i = 0;
	for(i=0; i<10; i++) 
	{
		test();
	}
	return 0; 
}
