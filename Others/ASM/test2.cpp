#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	int b;
	printf("%d",b);
	void* a;
	a=malloc(100);
	printf("%d\n",sizeof(int));
	free(NULL);
	return 0;
}